#include "TCanvas.h"
#include "TF1.h"
#include "TH1F.h"
#include "TRandom.h"

void Esame4() {
  gRandom->SetSeed();
  TH1F *htot[3];
  TCanvas *c = new TCanvas("c", "MyCanvas", 200, 200, 550, 450);
  TString name[3] = {"Gen", "Acc", "Eff"};
  TF1 *f = new TF1("f", "x/5", 0, 5);
  for (int i = 0; i < 2; ++i) {
    htot[i] = new TH1F("h" + name[i], name[i], 1000, 0, 5);
    htot[i]->Sumw2();
  }
  for (int i = 0; i < 1E7; ++i) {
    Double_t x = gRandom->Exp(1);
    Double_t y = gRandom->Rndm();
    htot[0]->Fill(x);
    if (y < f->Eval(x)) {
      htot[1]->Fill(x);
    }
  }
  htot[2] = new TH1F(*htot[0]);
  htot[0]->SetName("h" + name[2]);
  htot[0]->SetTitle(name[2]);
  htot[0]->Divide(htot[1], htot[0], 1, 1, "b");
  htot[0]->SetFillColor(kYellow);
  htot[0]->Draw("histo");
  htot[0]->Draw("e same");
}