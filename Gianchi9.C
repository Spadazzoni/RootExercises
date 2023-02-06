#include "TCanvas.h"
#include "TF1.h"
#include "TH1F.h"
#include "TRandom.h"

void Gianchi9() {
  gRandom->SetSeed();
  TCanvas *c = new TCanvas("c", "MyCanvas", 200, 200, 900, 300);
  c->Divide(3, 1);
  TH1F *htot[3];
  TString name[3] = {"1", "2", "Eff"};
  for (int i = 0; i < 2; ++i) {
    htot[i] = new TH1F("h" + name[i], "Histo " + name[i], 100, 0, 10);
    htot[i]->Sumw2();
  }
  TF1 *f = new TF1("f", "x/10", 0, 10);
  for (int i = 0; i < 1E5; ++i) {
    Double_t x = gRandom->Gaus(5, 1);
    Double_t y = gRandom->Rndm();
    if (y < f->Eval(x)) {
      htot[1]->Fill(x);
    }
    htot[0]->Fill(x);
  }
  htot[2] = new TH1F(*htot[0]);
  htot[2]->SetName(name[2]);
  htot[2]->SetTitle(name[2]);
  htot[2]->Divide(htot[1], htot[0], 1, 1, "b");
  for (int i = 0; i < 3; ++i) {
    Double_t y = gRandom->Uniform(0, 255);
    c->cd(i + 1);
    htot[i]->SetFillColor(y);
    htot[i]->Draw("histo");
  }
}