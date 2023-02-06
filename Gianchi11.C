#include "TBenchmark.h"
#include "TH1F.h"
#include "TRandom.h"

void Gianchi11() {
  gRandom->SetSeed();
  TBenchmark *b = new TBenchmark();
  TH1F *h = new TH1F("h", "MyHisto", 100, -5, 5);
  b->Start("Single Entries");
  for (int i = 0; i < 1E5; ++i) {
    h->Fill(gRandom->Gaus(0, 1));
  }
  b->Show("Single Entries");
  h->Clear();
  b->Start("Single Entries + init.");
  for (int i = 0; i < 1E5; ++i) {
    Double_t x = gRandom->Gaus(0, 1);
    h->Fill(x);
  }
  b->Show("Single Entries + init.");
  h->Clear();
  b->Start("FillRandom");
  h->FillRandom("gaus", 1E5);
  b->Show("FillRandom");
}