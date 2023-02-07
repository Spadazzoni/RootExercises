#include <iostream>

#include "TCanvas.h"
#include "TH1F.h"
#include "TRandom.h"

void Esame1() {
  gRandom->SetSeed();
  TH1F *htot[3];
  TString name[3] = {"1", "2", "Eff"};
  TCanvas *c = new TCanvas("c", "MyCanvas", 200, 200, 900, 300);
  for (int i = 0; i < 2; ++i) {
    htot[i] = new TH1F("h" + name[i], "Histo" + name[i], 1000, 0, 10);
    htot[i]->Sumw2();
  }
  c->Divide(3, 1);
  for (int i = 0; i < 1E6; ++i) {
    Double_t x = gRandom->Gaus(5, 0.5);
    Double_t y = gRandom->Rndm();
    htot[0]->Fill(x);
    if (x < 1) {
      if (y < 0.02) {
        htot[1]->Fill(x);
      }
    } else if (x >= 1 && x < 5) {
      if (y < x / 50.) {
        htot[1]->Fill(x);
      }
    } else if (x >= 5 && x <= 10) {
      if (y < 0.1) {
        htot[1]->Fill(x);
      }
    }
  }
  htot[2] = new TH1F(*htot[0]);
  htot[2]->SetName(name[2]);
  htot[2]->SetTitle("Histo" + name[2]);
  htot[2]->Divide(htot[1], htot[0], 1, 1, "b");
  for (int i = 0; i < 3; ++i) {
    c->cd(i + 1);
    htot[i]->SetFillColor(kPink);
    htot[i]->Draw("histo");
    htot[i]->Draw("e same");
  }
  Double_t eff = htot[1]->Integral() / htot[0]->Integral();
  std::cout << "Integral Efficiency: " << eff << " +/- "
            << sqrt(eff * (1 - eff)) / 1E5 << '\n';
}