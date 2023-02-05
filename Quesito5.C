#include "TBenchmark.h"
#include "TH1F.h"
#include "TRandom.h"

void Quesito5() {
  gRandom->SetSeed();
  TBenchmark *b = new TBenchmark();
  TH1F *h1 = new TH1F("h1", "gRandom", 100, -5, 5);
  TH1F *h2 = new TH1F("h2", "FillRandom", 100, -5, 5);
  b->Start("Single Entries");
  for (int i = 0; i < 1E5; ++i) {
    h1->Fill(gRandom->Gaus(0, 1));
  }
  b->Show("Single Entries");
  b->Start("FillRandom");
  h2->FillRandom("gaus", 1E5);
  b->Show("FillRandom");
}