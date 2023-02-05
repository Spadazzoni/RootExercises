#include "TCanvas.h"
#include "TColor.h"
#include "TColorGradient.h"
#include "TF1.h"
#include "TH1F.h"
#include "TRandom.h"

void Quesito4() {
  gRandom->SetSeed();
  TCanvas *c = new TCanvas("c", "MyCanvas", 200, 200, 500, 500);
  TH1F *h = new TH1F("h", "MyHisto", 100, 0, 10);
  h->SetFillColor(kRainBow);
  TF1 *f = new TF1("f", "x", 0, 10);
  h->FillRandom("f", 1E5);
  h->Draw();
}