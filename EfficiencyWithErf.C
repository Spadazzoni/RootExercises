#include "TCanvas.h"
#include "TColor.h"
#include "TF1.h"
#include "TH1F.h"
#include "TRandom.h"

Double_t MyErf(Double_t *x, Double_t *par) {
  Float_t xx = x[0];
  Double_t res = TMath::Erf(xx);
  return res;
}

void EfficiencyWithErf(Int_t nGen = 1E5) {
  gRandom->SetSeed();
  TH1F *hGen = new TH1F("hGen", "Generated Events", 100, 0, 5);
  hGen->Sumw2();
  hGen->SetFillColor(kGreenRedViolet);
  TH1F *hAcc = new TH1F("hAcc", "Accepted Entries", 100, 0, 5);
  hAcc->Sumw2();
  hAcc->SetFillColor(kBlueRedYellow);
  TF1 *f = new TF1("f", MyErf, -2, 7, 0);
  TCanvas *c = new TCanvas("c", "MyCanvas", 200, 200, 900, 300);
  c->Divide(3, 1);
  for (int i = 0; i < nGen; ++i) {
    Double_t x = gRandom->Uniform(0., 5);
    Double_t e = gRandom->Rndm();
    if (e < f->Eval(x)) {
      hAcc->Fill(x);
    }
    hGen->Fill(x);
  }
  TH1F *hEff = new TH1F(*hGen);
  hEff->SetName("hEff");
  hEff->SetTitle("Efficiency Effects");
  hEff->Divide(hAcc, hGen, 1, 1);
  c->cd(1);
  hGen->Sumw2(kFALSE);
  hGen->Draw();
  c->cd(2);
  hAcc->Sumw2(kFALSE);
  hAcc->Draw();
  c->cd(3);
  hEff->Sumw2(kFALSE);
  hEff->Draw();
}