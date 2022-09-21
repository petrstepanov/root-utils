#include "FitUtils.h"
#include <TMath.h>

#include <TH1.h>
#include <TAxis.h>
// #include <TCanvas.h>

//#include <iostream>
//#include <iomanip>
//#include <fstream>

FitUtils::CrystalBallFunctionObject::CrystalBallFunctionObject(Bool_t _isReversed) {
  isReversed = _isReversed;
}

Double_t FitUtils::CrystalBallFunctionObject::operator()(double *_x, double *par) {
  // https://en.wikipedia.org/wiki/Crystal_Ball_function
  LongDouble_t x = _x[0];
  LongDouble_t a = par[0];
  LongDouble_t n = par[1];
  LongDouble_t mean = par[2];
  LongDouble_t sigma = par[3];
  LongDouble_t norm = par[4];

  LongDouble_t abs_a = TMath::Abs(a);

  LongDouble_t A = TMath::Power(n / abs_a, n) * TMath::Exp(-abs_a * abs_a / 2);
  LongDouble_t B = n / abs_a - abs_a;
  LongDouble_t C = n / abs_a / (n - 1) * TMath::Exp(-abs_a * abs_a / 2);
  LongDouble_t D = TMath::Sqrt(TMath::PiOver2()) * (1 + TMath::Erf(abs_a / TMath::Sqrt2()));
  LongDouble_t N = 1 / sigma / (C + D);

  // Regular Crystal Ball
  if (!isReversed) {
    if (x - mean > -a * sigma) {
      // Gauss
      return norm * N * TMath::Exp(-TMath::Power(x - mean, (LongDouble_t) 2) / 2 / TMath::Power(sigma, (LongDouble_t) 2));
    }
    // Power
    return norm * N * A * TMath::Power(B - (x - mean) / sigma, -n);
  }

  // Reversed Crystal Ball
  if (x - mean < a * sigma) {
    // Gauss
    return norm * N * TMath::Exp(-TMath::Power(x - mean, (LongDouble_t) 2) / 2 / TMath::Power(sigma, (LongDouble_t) 2));
  }
  // Power
  return norm * N * A * TMath::Power(B + (x - mean) / sigma, -n);
}

using namespace FitUtils;

TF1* FitUtils::fitHistWithROOTCrystalBall(TH1 *hist, Bool_t inverted) {
  Double_t minX = hist->GetXaxis()->GetBinLowEdge(hist->GetXaxis()->GetFirst());
  Double_t maxX = hist->GetXaxis()->GetBinUpEdge(hist->GetXaxis()->GetLast());
  TF1 *f = new TF1("fBallRoot", "crystalballn", minX, maxX);

  f->SetParameters(inverted ? -1 : 1, 3, hist->GetBinCenter(hist->GetMaximumBin()), hist->GetRMS() / 10);
  // hist->Fit(f);
  return f;
}

TF1* FitUtils::getCrystalBallFunction(TH1 *hist, Bool_t reversed) {
  TF1 *fBall = new TF1();
  CrystalBallFunctionObject *fFunctionObject = new CrystalBallFunctionObject(reversed);
  Double_t minX = hist->GetXaxis()->GetBinLowEdge(1);
  Double_t maxX = hist->GetXaxis()->GetBinUpEdge(hist->GetNbinsX());
//  Double_t intervalX = maxX-minX;
  fBall = new TF1("fBall", *fFunctionObject, minX, maxX, 5);    // create TF1 class.

  fBall->SetNpx(500);

  fBall->SetParName(0, "a");
  fBall->SetParameter(0, 1);
  fBall->SetParLimits(0, 1E-2, 1E2);

  fBall->SetParName(1, "n");
  fBall->SetParameter(1, 1);
  fBall->SetParLimits(1, 1, 20);

  fBall->SetParName(2, "mean");
  Double_t mean = hist->GetBinCenter(hist->GetMaximumBin());
  fBall->SetParameter(2, mean);
  fBall->SetParLimits(2, mean - 2 * hist->GetRMS(), mean + 2 * hist->GetRMS());

  fBall->SetParName(3, "sigma");
  fBall->SetParameter(3, hist->GetRMS() / 2);
  fBall->SetParLimits(3, hist->GetRMS() / 4, hist->GetRMS());

  fBall->SetParName(4, "norm");
  Double_t integral = hist->Integral("width");
  fBall->SetParameter(4, integral);
  fBall->SetParLimits(4, integral * 0.9, integral * 1.1);

  // hist->Fit(fBall);
  // Abnormal termination of minimization.
  // Solution: increase the fitting range. Specify function range (-10000, 10000) and pass "R" parameter
  //           also use Long Double vs Double in the fitting function evaluate()

  return fBall;
//  m = edepHist->GetFunction("fBall")->GetParameter(2); // mean
//  Dm = edepHist->GetFunction("fBall")->GetParError(2); // mean error
//  s = edepHist->GetFunction("fBall")->GetParameter(3); // sigma
//  Ds = edepHist->GetFunction("fBall")->GetParError(3); // sigma error

}
