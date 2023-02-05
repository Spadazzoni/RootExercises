#include "TBenchmark.h"
#include "TH1F.h"
#include "TRandom.h"

void Benchmarking(Int_t nGen = 1E8) {
  TH1F *h = new TH1F("h", "Benchmarking", 100, -3, 3);
  TBenchmark *b = new TBenchmark();
  b->Start("FillRandom");
  h->FillRandom("gaus", nGen);
  b->Show("FillRandom");
  h->Clear();
  b->Start("gRandom->Gaus");
  for (int i = 0; i < nGen; ++i) {
    h->Fill(gRandom->Gaus(0, 1));
  }
  b->Show("gRandom->Gaus");
}