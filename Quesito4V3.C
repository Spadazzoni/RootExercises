#include "TCanvas.h"
#include "TF1.h"
#include "TH1F.h"
#include "TRandom.h"

Double_t MyFunc(Double_t *x, Double_t *par) {
  if (x[0] >= 0 && x[0] < 5) {
    return x[0] / 5.;
  } else {
    return 1.;
  }
}

void Quesito4V3() {
  gRandom->SetSeed();
  TCanvas *c = new TCanvas("c", "MyCanvas", 200, 200, 500, 500);
  TH1F *h = new TH1F("h", "Funzione a tratti", 100, 0, 10);
  TF1 *f = new TF1("f", MyFunc, 0, 10, 0);
  h->FillRandom("f", 1E5);
  h->SetFillColor(kGreen);
  h->Draw();
}