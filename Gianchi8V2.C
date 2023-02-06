#include "TCanvas.h"
#include "TF1.h"
#include "TH1F.h"
#include "TRandom.h"

Double_t MyF(Double_t *x, Double_t *par) {
  if (x[0] >= 0 && x[0] < 5) {
    return x[0] / 5.;
  } else {
    return 1.;
  }
}

void Gianchi8V2() {
  gRandom->SetSeed();
  TCanvas *c = new TCanvas("c", "MyCanvas", 200, 200, 1010, 450);
  c->Divide(2, 1);
  TH1F *hAcc = new TH1F("hAcc", "MyHistoAcc", 100, 0, 10);
  TH1F *hGen = new TH1F("hGen", "MyHistoGen", 100, 0, 10);
  hAcc->Sumw2();
  hGen->Sumw2();
  TF1 *f = new TF1("f", MyF, 0, 10, 0);
  for (int i = 0; i < 1E5; ++i) {
    Double_t x = f->GetRandom();
    Double_t y = gRandom->Rndm();
    if (x >= 0 && x <= 3) {
      if (y < 0.3) {
        hAcc->Fill(x);
      }
    } else {
      if (y < 0.7) {
        hAcc->Fill(x);
      }
    }
    hGen->Fill(x);
  }
  TH1F *hEff = new TH1F("hEff", "Eff", 100, 0, 10);
  hEff->Divide(hAcc, hGen, 1, 1, "b");
  hEff->SetFillColor(kPink);
  c->cd(1);
  hAcc->SetFillColor(kOrange);
  hAcc->Draw("histo");
  c->cd(2);
  hEff->Draw("histo");
}