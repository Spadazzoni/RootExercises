#include "TCanvas.h"
#include "TF1.h"
#include "TH1F.h"
#include "TRandom.h"

void Quesito1() {
  TH1F *htot[3];
  TF1 *f = new TF1("f", "0.1*x", 0, 10);
  TString name[2] = {" 1", " 2"};
  TCanvas *c = new TCanvas("c", "MyCanvas", 200, 200, 900, 300);
  c->Divide(3, 1);
  for (int i = 0; i < 2; ++i) {
    htot[i] = new TH1F("h" + name[i], "Gauss" + name[i], 100, 0, 10);
    htot[i]->Sumw2();
  }
  for (int i = 0; i < 1E5; ++i) {
    Double_t x = gRandom->Gaus(5, 1);
    Double_t y = gRandom->Rndm();
    if (y < f->Eval(x)) {
      htot[1]->Fill(x);
    }
    htot[0]->Fill(x);
  }
  htot[2] = new TH1F(*htot[0]);
  htot[2]->SetName("h 3");
  htot[2]->SetTitle("Eff");
  htot[2]->Divide(htot[1], htot[0], 1, 1, "B");
  for (int i = 0; i < 3; ++i) {
    c->cd(i + 1);
    htot[i]->Sumw2(kFALSE);
    htot[i]->Draw();
  }
}