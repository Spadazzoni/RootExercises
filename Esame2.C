#include <iostream>

#include "TCanvas.h"
#include "TFile.h"
#include "TH1F.h"
#include "TRandom.h"

void Esame2() {
  gRandom->SetSeed();
  TCanvas *c = new TCanvas("c", "MyCanvas", 200, 200, 550, 450);
  TFile *file = new TFile("Proportions.root", "recreate");
  TH1F *h = new TH1F("h", "Proportions", 5, 0, 5);
  for (int i = 0; i < 1E7; ++i) {
    Double_t y = gRandom->Rndm();
    if (y < 0.1) {
      h->Fill(0);
    } else if (y < 0.35) {
      h->Fill(1);
    } else if (y < 0.5) {
      h->Fill(2);
    } else if (y < 0.7) {
      h->Fill(3);
    } else {
      h->Fill(4);
    }
  }
  std::cout << "Bin 1: " << h->GetBinContent(1) / 1E7 << " +/- "
            << h->GetBinError(1) / 1E7 << '\n';
  std::cout << "Bin 2: " << h->GetBinContent(2) / 1E7 << " +/- "
            << h->GetBinError(2) / 1E7 << '\n';
  std::cout << "Bin 3: " << h->GetBinContent(3) / 1E7 << " +/- "
            << h->GetBinError(3) / 1E7 << '\n';
  std::cout << "Bin 4: " << h->GetBinContent(4) / 1E7 << " +/- "
            << h->GetBinError(4) / 1E7 << '\n';
  std::cout << "Bin 5: " << h->GetBinContent(5) / 1E7 << " +/- "
            << h->GetBinError(5) / 1E7 << '\n';
  h->SetFillColor(kPink);
  h->DrawCopy();
  h->Write();
  file->Close();
}