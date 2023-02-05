#include "TCanvas.h"
#include "TH1F.h"
#include "TRandom.h"

void Efficiency(Int_t nGen = 1E5) {
  gRandom->SetSeed();
  TH1F *hGen = new TH1F("hGen", "Generated Entries", 100, -1, 6);
  TH1F *hAcc = new TH1F("hAcc", "Accepted Entries", 100, -1, 6);
  hGen->Sumw2();
  hAcc->Sumw2();
  hGen->SetFillColor(kYellow);
  hAcc->SetFillColor(kOrange);
  TCanvas *c = new TCanvas("c", "MyCanvas", 200, 200, 900, 300);
  c->Divide(3, 1);
  for (int i = 0; i < nGen; ++i) {
    Double_t eff = gRandom->Rndm();
    Double_t x = gRandom->Gaus(2.5, 1);
    if (eff < 0.7) {
      hAcc->Fill(x);
    }
    hGen->Fill(x);
  }
  TH1F *hEff = new TH1F(*hGen);
  hEff->SetName("hEff");
  hEff->SetTitle("Efficiency effects");
  hEff->SetFillColor(kGreen);
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