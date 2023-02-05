#include "TCanvas.h"
#include "TH1F.h"
#include "TRandom.h"

void Smearing(Int_t nGen = 1E5) {
  gRandom->SetSeed();
  const Double_t mean = 1.5;
  TH1F *h1 = new TH1F("h1", "Smearing effects on a fixed value", 50, 0, 3);
  TH1F *h2 =
      new TH1F("h2", "Smearing effects on an Uniform distribution", 50, 0, 3);
  h1->SetFillColor(kOrange);
  h2->SetFillColor(kAzure);
  TCanvas *c = new TCanvas("c", "MyCanvas", 200, 200, 700, 600);
  c->Divide(1, 2);
  for (int i = 0; i < nGen; ++i) {
    h1->Fill(gRandom->Gaus(mean, 0.1));
    h2->Fill(gRandom->Gaus(gRandom->Uniform(0.5, 2.5), 0.1));
  }
  c->cd(1);
  h1->Draw();
  c->cd(2);
  h2->Draw();
}