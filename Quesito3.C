#include <iostream>

#include "TCanvas.h"
#include "TH1F.h"
#include "TRandom.h"

void Quesito3() {
  gRandom->SetSeed();
  TH1F *h = new TH1F("h", "Proportions", 4, 0, 4);
  for (int i = 0; i < 1E6; ++i) {
    Double_t y = gRandom->Rndm();
    if (y < 0.6) {
      h->Fill(0);
    } else {
      if (y < 0.9) {
        h->Fill(1);
      } else {
        if (y < 0.99) {
          h->Fill(2);
        } else {
          h->Fill(3);
        }
      }
    }
  }
  std::cout << "/////////RESULTS//////////" << '\n';
  std::cout << "Entries Bin 1: " << h->GetBinContent(1) << " +/- "
            << h->GetBinError(1) << '\n';
  std::cout << "Entries Bin 2: " << h->GetBinContent(2) << " +/- "
            << h->GetBinError(2) << '\n';
  std::cout << "Entries Bin 3: " << h->GetBinContent(3) << " +/- "
            << h->GetBinError(3) << '\n';
  std::cout << "Entries Bin 4: " << h->GetBinContent(4) << " +/- "
            << h->GetBinError(4) << '\n';
  h->Draw();
}