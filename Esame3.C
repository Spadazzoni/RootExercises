#include "TBenchmark.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TH1F.h"
#include "TRandom.h"

Double_t MyF(Double_t *x, Double_t *par) {
  if (x[0] >= 0 && x[0] < 1) {
    return x[0] / 2.;
  } else {
    return 0.5;
  }
}

void Esame3() {
  gRandom->SetSeed();
  TBenchmark *b = new TBenchmark();
  TH1F *h = new TH1F("h", "Histo", 100, 0, 2);
  TF1 *f = new TF1("f", MyF, 0, 2, 0);
  b->Start("FillRandom");
  h->FillRandom("f", 1E6);
  b->Show("FillRandom");
}