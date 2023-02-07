#include "TCanvas.h"
#include "TF1.h"
#include "TH1F.h"
#include "TRandom.h"

void Esame6() {
  gRandom->SetSeed();
  TCanvas *c = new TCanvas("c", "MyCanvas", 200, 200, 550, 450);
  TH1F *h = new TH1F("h", "#sqrt{x} + x^{2}", 100, 0, 10);
  TF1 *f = new TF1("f", "sqrt(x)+x*x", 0, 10);
  h->FillRandom("f", 1E7);
  h->SetFillColor(kOrange);
  h->Draw();
}