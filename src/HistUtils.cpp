#include "./HistUtils.h"
#include "./FileUtils.h"
#include "./StringUtils.h"

//#include <TObject.h>
#include <TRandom3.h>
#include <TList.h>

#include <iostream>

using namespace HistUtils;

Double_t HistUtils::getMeanY(TH1 *hist) {
  Double_t sum = 0;
  for (int i = 1; i <= hist->GetNbinsX(); i++) {
    sum += hist->GetBinContent(i);
  }
  return sum / hist->GetNbinsX();
}

TH1* HistUtils::cropHistogram(TH1 *hist, Double_t minX, Double_t maxX) {
  Int_t minBin = hist->GetXaxis()->FindBin(minX);
  if (minBin == 0)
    minBin = 1;

  Int_t maxBin = hist->GetXaxis()->FindBin(maxX);
  if (maxBin == hist->GetNbinsX() + 1)
    maxBin = hist->GetNbinsX();

  return cropHistogram(hist, minBin, maxBin);
}

TH1* HistUtils::cropHistogram(TH1 *hist, Int_t minBin, Int_t maxBin) {
  TString histName = hist->GetName();
  TUUID uid = TUUID();
  TString uidSuffix = uid.AsString();
  histName += "_";
  histName += uidSuffix(0, 4);

  TString histTitle = hist->GetTitle();
  histTitle += " (cropped)";
  Double_t lowEdge = hist->GetXaxis()->GetBinLowEdge(minBin);
  Double_t upEdge = hist->GetXaxis()->GetBinUpEdge(maxBin);
  TH1 *cropHist = new TH1D(histName.Data(), histTitle.Data(), maxBin - minBin + 1, lowEdge, upEdge);

  for (Int_t i = 1; i <= cropHist->GetXaxis()->GetNbins(); i++) {
    Double_t content = hist->GetBinContent(i + minBin - 1);
    cropHist->SetBinContent(i, content);
  }

  return cropHist;
}

void HistUtils::invertHist(TH1 *hist) {
  for (int i = 1; i <= hist->GetXaxis()->GetNbins(); i++) {
    if (hist->GetBinContent(i) >= 0) {
      hist->SetBinContent(i, 0);
    } else {
      Double_t binContent = hist->GetBinContent(i);
      hist->SetBinContent(i, -binContent);
    }
  }
}

TH2* HistUtils::makeHistStack(TList* histList, Double_t axisMin, Double_t axisMax, const char *name) {
  TH1 *firstHist = (TH1*) histList->At(0);
  if (!firstHist)
    return NULL;

  Int_t nHists = histList->GetSize();

  TString histName = name;
  if (histName.Length() == 0) {
    histName = StringUtils::getSafeName("histStack");
  }
  TH2 *histQueue = new TH2D(histName.Data(), "", firstHist->GetXaxis()->GetNbins(),
                            firstHist->GetXaxis()->GetBinLowEdge(1),
                            firstHist->GetXaxis()->GetBinUpEdge(firstHist->GetXaxis()->GetNbins()), nHists, axisMin,
                            axisMax);
  Int_t y = 1;
  for (TObject *object : *histList) {
    TH1* hist = (TH1*) object;
    for (int x = 1; x <= hist->GetXaxis()->GetNbins(); x++) {
      for (int c = 0; c < hist->GetBinContent(x); c++) {
        histQueue->Fill(hist->GetBinCenter(x),
                        (axisMax - axisMin) / (2 * nHists) + (y - 1) * (axisMax - axisMin) / nHists);
      }
    }
    y++;
  }
  return histQueue;
}
