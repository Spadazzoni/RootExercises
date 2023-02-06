#include "TCanvas.h"
#include "TF1.h"
#include "TH1F.h"
#include "TRandom.h"

Double_t myF(Double_t *x, Double_t *par) {
  if (x[0] >= 0 && x[0] < 5) {
    return x[0] / 5.;
  } else {
    return 1.;
  }
}

void Gianchi8() {
  gRandom->SetSeed();
  TCanvas *c = new TCanvas("c", "MyCanvas", 200, 200, 550, 450);
  TH1F *h = new TH1F("h", "MyHisto", 100, 0, 10);
  TF1 *f = new TF1("f", myF, 0, 10, 0);
  h->FillRandom("f", 1E5);
  h->SetFillColor(kPink);
  h->Draw();
}