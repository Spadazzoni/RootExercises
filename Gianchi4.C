#include "TCanvas.h"
#include "TF1.h"
#include "TH1F.h"
#include "TRandom.h"

void Gianchi4() {
  gRandom->SetSeed();
  TCanvas *c = new TCanvas("c", "MyCanvas", 200, 200, 550, 450);
  TH1F *htot[3];
  TString name[3] = {"1", "2", "Eff"};
  for (int i = 0; i < 2; ++i) {
    htot[i] = new TH1F("h" + name[i], "Histo " + name[i], 1000, 0, 10);
    htot[i]->Sumw2();
  }
  TF1 *f = new TF1("f", "0.1*x*exp(-x)", 0, 10);
  for (int i = 0; i < 1E7; ++i) {
    Double_t x = gRandom->Gaus(5, 1);
    Double_t y = gRandom->Rndm();
    if (y < f->Eval(x)) {
      htot[1]->Fill(x);
    }
    htot[0]->Fill(x);
  }
  htot[2] = new TH1F(*htot[0]);
  htot[2]->SetName("h" + name[2]);
  htot[2]->SetTitle(name[2]);
  htot[2]->Divide(htot[1], htot[0], 1, 1, "b");
  htot[2]->Draw("hist");
  htot[2]->Draw("e same");
}