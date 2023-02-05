#include "TH1F.h"
#include "TRandom.h"

void Proportions(Int_t nGen = 1E5) {
  gRandom->SetSeed();
  TH1F *h = new TH1F("h", "Proportions", 5, 0, 5);
  for (int i = 0; i < nGen; ++i) {
    double x = gRandom->Rndm();
    if (x < 0.1) {
      h->Fill(0);
    } else {
        if(x < 0.3) {
            h->Fill(1);
        } else {
            if(x < 0.7) {
                h->Fill(2);
            } else {
                if (x < 0.95) {
                    h->Fill(3);
                } else {
                    h->Fill(4);
                }
            }
        }
    }
  }
  h->SetFillColor(kAzure);
  h->Draw();
}