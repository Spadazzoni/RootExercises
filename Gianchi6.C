#include "TCanvas.h"
#include "TF1.h"
#include "TH1F.h"
#include "TRandom.h"

void Gianchi6() {
  gRandom->SetSeed();
  TCanvas *c = new TCanvas("c", "MyCanvas", 200, 200, 550, 450);
  TH1F *h = new TH1F("h", "sin(x) + x^{2}", 100, 0, 10);
  TF1 *f = new TF1("f", "sin(x)+x*x", 0, 10);
  h->FillRandom("f", 1E5);
  h->SetFillColor(kOrange);
  h->Draw();
}