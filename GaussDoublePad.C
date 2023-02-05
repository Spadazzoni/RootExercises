#include "TH1F.h"
#include "TF1.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TStyle.h"

Double_t MyGauss(Double_t *x, Double_t *par) {
  Float_t xx = x[0];
  Double_t val =
      par[0] * exp(-(xx - par[1]) * (xx - par[1]) / (2 * par[2] * par[2]));
  return val;
}

void GaussDoublePad(int nGen = 1E5) {
  gRandom->SetSeed();
  gStyle->SetOptStat(2210);
  TH1F *htot[2];
  TString names[2] = {" 1", " 2"};
  EColor color[2] = {kBlue, kRed};
  TF1 *f = new TF1("f", MyGauss, -5, 5, 3);
  f->SetParameters(1 / (sqrt(2 * M_PI)), 0, 1);
  TCanvas *c = new TCanvas("c", "MyCanvas", 200, 200, 700, 600);
  c->Divide(1, 2);
  for (int i = 0; i < 2; ++i) {
    htot[i] = new TH1F("h" + names[i], "Gaussian Distribution" + names[i], 100,
                       -5, 5);
    htot[i]->SetFillColor(color[i]);
    htot[i]->FillRandom("f", nGen);
    htot[i]->GetXaxis()->SetTitle("X axis");
    htot[i]->GetYaxis()->SetTitle("Entries");
    c->cd(i + 1);
    htot[i]->Draw();
    htot[i]->SetMarkerStyle(20);
    htot[i]->Draw("E same");
  }
}