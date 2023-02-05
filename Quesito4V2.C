#include "TCanvas.h"
#include "TF1.h"
#include "TH1F.h"
#include "TRandom.h"

void Quesito4V2() {
  gRandom->SetSeed();
  TCanvas *c = new TCanvas("c", "MyCanvas", 200, 200, 1000, 450);
  c->Divide(2, 1);
  TH1F *h1 = new TH1F("h1", "MyHisto1", 100, 0, 10);  // me
  TH1F *h2 = new TH1F("h2", "MyHisto2", 100, 0, 10);  // Oancia
  TF1 *f1 = new TF1("f1", "x/5", 0, 5);
  TF1 *f2 = new TF1("f2", "1.", 5, 10);
  TF1 *f3 =
      new TF1("f3", "(x < 5 && x >= 0)*x/5. + (x >= 5 && x <= 10)", 0, 10);
  h2->FillRandom("f3", 1E5);
  for (int i = 0; i < 1E5; ++i) {
    Double_t x = gRandom->Rndm();
    if (x < 0.5) {
      h1->Fill(f1->GetRandom());
    } else {
      h1->Fill(f2->GetRandom());
    }
  }
  c->cd(1);
  h1->SetFillColor(kGreen);
  h1->Draw();
  c->cd(2);
  h2->SetFillColor(kYellow);
  h2->Draw();
}