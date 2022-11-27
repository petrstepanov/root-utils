#include "FitUtils.h"
#include <TMath.h>

#include <TH1.h>
#include <TAxis.h>
// #include <TCanvas.h>

//#include <iostream>
//#include <iomanip>
//#include <fstream>

using namespace TMath;

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
    // Gauss (same)
    return norm * N * TMath::Exp(-TMath::Power(x - mean, (LongDouble_t) 2) / 2 / TMath::Power(sigma, (LongDouble_t) 2));
  }
  // Power
  return norm * N * A * TMath::Power(B + (x - mean) / sigma, -n);
}

using namespace FitUtils;

//TF1* FitUtils::fitHistWithROOTCrystalBall(TH1 *hist, Bool_t inverted) {
//  Double_t minX = hist->GetXaxis()->GetBinLowEdge(hist->GetXaxis()->GetFirst());
//  Double_t maxX = hist->GetXaxis()->GetBinUpEdge(hist->GetXaxis()->GetLast());
//  TF1 *f = new TF1("fBallRoot", "crystalball", minX, maxX);
//
//  f->SetParameters(inverted ? -1 : 1, 3, hist->GetBinCenter(hist->GetMaximumBin()), hist->GetRMS() / 10);
//  // hist->Fit(f);
//  return f;
//}

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
  fBall->SetParameter(1, 1E-3);
  fBall->SetParLimits(1, 1, 30);

  fBall->SetParName(2, "mean");
  Double_t mean = hist->GetMean();
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
}

TVector2 FitUtils::getCrystalBallMean(TF1* cball){
  Double_t xMin = cball->GetXmin();
  Double_t xMax = cball->GetXmax();

  Double_t mean = cball->Mean(xMin, xMax);
  Double_t meanErr = cball->GetParError(2);

  return TVector2(mean, meanErr);

  /*
  Double_t a = cball->GetParameter(0);
  Double_t n = cball->GetParameter(1);
  Double_t Mu = cball->GetParameter(2);
  Double_t Sigma = cball->GetParameter(3);

  Double_t Pi = TMath::Pi();
  Double_t E = TMath::E();

  Double_t intXfX = 0;
  if (!isReversed) {
    // Crystal Ball function. Refer to the "./wolfram/crystal-ball.nb"
    intXfX = (a*(-1 + n)*(2*Sigma + Power(E,Power(a,2)/2.)*Sqrt(2*Pi)*Mu*(1 + Erf(a/Sqrt(2)))))/
        (2*n + a*Power(E,Power(a,2)/2.)*(-1 + n)*Sqrt(2*Pi)*(1 + Erf(a/Sqrt(2)))) -
       (2*n*Power(n/a,n)*Sigma*(-(a*(-2 + n)*Mu) + Power(a,2)*(-2 + n)*Sigma + n*Sigma))/
        (a*(-2 + n)*Power(-a + n/a + Mu/Sigma,n)*Power((n*Sigma)/(a*Mu - Power(a,2)*Sigma + n*Sigma),n)*
          (2*n*Sigma + a*Power(E,Power(a,2)/2.)*(-1 + n)*Sqrt(2*Pi)*Sigma*(1 + Erf(a/Sqrt(2)))));
  }
  else {
    // Reversed Crystal Ball function. Refer to the "./wolfram/crystal-ball-reversed.nb"
    intXfX = (a*(-1 + n)*(-2*Sigma + Power(E,Power(a,2)/2.)*Sqrt(2*Pi)*Mu*(1 + Erf(a/Sqrt(2)))))/
        (2*n + a*Power(E,Power(a,2)/2.)*(-1 + n)*Sqrt(2*Pi)*(1 + Erf(a/Sqrt(2)))) +
       (2*n*Sigma*(a*(-2 + n)*Mu + Power(a,2)*(-2 + n)*Sigma + n*Sigma))/
        (a*(-2 + n)*Power(-(a/(a*Mu + Power(a,2)*Sigma - n*Sigma)),n)*Power(-Mu - a*Sigma + (n*Sigma)/a,n)*
          (2*n*Sigma + a*Power(E,Power(a,2)/2.)*(-1 + n)*Sqrt(2*Pi)*Sigma*(1 + Erf(a/Sqrt(2)))));
  }

  TVector2 mean(intXfX, cball->GetParError(2));
  return mean; */
}

TVector2 FitUtils::getCrystalBallDispersion(TF1* cball){
  Double_t xMin = cball->GetXmin();
  Double_t xMax = cball->GetXmax();

  Double_t variance = cball->Variance(xMin, xMax);
  Double_t dispersion = TMath::Sqrt(variance);
  Double_t dispersionErr = cball->GetParError(3);

  return TVector2(dispersion, dispersionErr);
  /*
  Double_t a = cball->GetParameter(0);
  Double_t n = cball->GetParameter(1);
  Double_t Mu = cball->GetParameter(2);
  Double_t Sigma = cball->GetParameter(3);

  Double_t Pi = TMath::Pi();
  Double_t E = TMath::E();

  // Refer to the ./wolfram/crystal-ball.nb
  Double_t intX2fX = 0;
  if (!isReversed) {
    // Crystal Ball function. Refer to the "./wolfram/crystal-ball.nb"
    intX2fX = (a*(-1 + n)*Power(Sigma,2)*(-2*a + Power(E,Power(a,2)/2.)*Sqrt(2*Pi)*(1 + Erf(a/Sqrt(2)))))/
        (2*n + a*Power(E,Power(a,2)/2.)*(-1 + n)*Sqrt(2*Pi)*(1 + Erf(a/Sqrt(2)))) +
       (2*n*(Power(a,4)*(-3 + n)*(-2 + n) + 2*Power(a,2)*(-3 + n)*n + 2*Power(n,2))*Power(Sigma,3))/
        (Power(a,2)*(-3 + n)*(-2 + n)*(2*n*Sigma + a*Power(E,Power(a,2)/2.)*(-1 + n)*Sqrt(2*Pi)*Sigma*(1 + Erf(a/Sqrt(2)))));
  }
  else {
    // Reversed Crystal Ball function. Refer to the "./wolfram/crystal-ball-reversed.nb"
    intX2fX = (a*(-1 + n)*Power(Sigma,2)*(-2*a + Power(E,Power(a,2)/2.)*Sqrt(2*Pi)*(1 + Erf(a/Sqrt(2)))))/
        (2*n + a*Power(E,Power(a,2)/2.)*(-1 + n)*Sqrt(2*Pi)*(1 + Erf(a/Sqrt(2)))) +
       (2*n*(Power(a,4)*(-3 + n)*(-2 + n) + 2*Power(a,2)*(-3 + n)*n + 2*Power(n,2))*Power(Sigma,3))/
        (Power(a,2)*(-3 + n)*(-2 + n)*(2*n*Sigma + a*Power(E,Power(a,2)/2.)*(-1 + n)*Sqrt(2*Pi)*Sigma*(1 + Erf(a/Sqrt(2)))));
  }
  // Dispersion (standard deviation) is square root of the function variance
  Double_t dispersion = TMath::Sqrt(intX2fX);
  TVector2 std(dispersion, cball->GetParError(3));
  return std; */
}

TF1* FitUtils::getCrystalBallGaussFunction(TF1* cball){
  LongDouble_t a = cball->GetParameter(0);
  LongDouble_t n = cball->GetParameter(1);
  LongDouble_t mean = cball->GetParameter(2);
  LongDouble_t sigma = cball->GetParameter(3);
  LongDouble_t norm = cball->GetParameter(4);

  LongDouble_t abs_a = TMath::Abs(a);

  LongDouble_t C = n / abs_a / (n - 1) * TMath::Exp(-abs_a * abs_a / 2);
  LongDouble_t D = TMath::Sqrt(TMath::PiOver2()) * (1 + TMath::Erf(abs_a / TMath::Sqrt2()));
  LongDouble_t N = 1 / sigma / (C + D);

  // COMPOSE GAUSSIAN PART

  // Create normalized gaussian ROOT function ("gaussn"!)
  TString cballGaussName = TString::Format("%s-gauss", cball->GetName());
  TF1* cballGauss = new TF1(cballGaussName.Data(), "gausn", cball->GetXmin(), cball->GetXmax());
  cballGauss->SetNpx(cball->GetNpx());

  // Calculate gaussian "constant" - basically integral. How? Multiply and divide gaussian formula on the gaussian normalization factor.
  Double_t gaussContribution = N*sigma*TMath::Sqrt(2*TMath::Pi());
  cballGauss->SetParameter(0, norm * gaussContribution);

  // Set other gaussian parameters from the crystal ball function
  cballGauss->SetParameter(1, mean);
  cballGauss->SetParameter(2, sigma);

  return cballGauss;
}

TVector2 FitUtils::evalResolution(Double_t mean, Double_t meanErr, Double_t std, Double_t stdErr){
  Double_t r = std / mean * 100;  // Resolution
  Double_t Dr = 100 * TMath::Sqrt(TMath::Power(1 / mean * stdErr, 2) + TMath::Power(std / mean / mean * meanErr, 2)); // Indirect error

  TVector2 resolution(r, Dr);
  return resolution;
}

TVector2 FitUtils::getCrystalBallResolution(TF1* cball, ResolutionType rt){
  if (rt == ResolutionType::CBFunctionMomenta){
    TVector2 mean = getCrystalBallMean(cball);
    TVector2 std = getCrystalBallDispersion(cball);
    TVector2 cbResolution = evalResolution(mean.X(), mean.Y(), std.X(), std.Y());
    return cbResolution;
  }

  Double_t gausMean = cball->GetParameter(2);
  Double_t gausMeanErr = cball->GetParError(2);
  Double_t gausSigma = cball->GetParameter(3);
  Double_t gausSigmaErr = cball->GetParError(3);
  TVector2 gausResolution = FitUtils::evalResolution(gausMean, gausMeanErr, gausSigma, gausSigmaErr);
  return gausResolution;

}
