#include "TCanvas.h"
#include "TH1F.h"
#include "TRandom.h"

void Quesito1V2() {
  gRandom->SetSeed();
  TH1F *htot[3];
  TString name[3] = {" 1", "2 ", " 3"};
  TCanvas *c = new TCanvas("c", "MyCanvas", 200, 200, 900, 300);
  c->Divide(3, 1);
  for (int i = 0; i < 2; ++i) {
    htot[i] = new TH1F("h" + name[i], "Gauss" + name[i], 100, 0, 10);
    htot[i]->Sumw2();
  }
  for (int i = 0; i < 1E5; ++i) {
    Double_t x = gRandom->Gaus(5, 1);
    Double_t y = gRandom->Rndm();
    if (x >= 0 && x <= 5) {
      if (y < 0.3) {
        htot[1]->Fill(x);
      }
    }
    if (x > 5) {
      if (y < 0.7) {
        htot[1]->Fill(x);
      }
    }
    htot[0]->Fill(x);
  }
  htot[2] = new TH1F(*htot[0]);
  htot[2]->SetName("h" + name[2]);
  htot[2]->SetTitle("Eff");
  htot[2]->Divide(htot[1], htot[2], 1, 1, "b");
  for (int i = 0; i < 3; ++i) {
    c->cd(i + 1);
    htot[i]->Sumw2(kFALSE);
    htot[i]->Draw();
  }
}