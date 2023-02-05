#include "TCanvas.h"
#include "TF2.h"
#include "TGraphErrors.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TList.h"

Double_t MyGauss2D(Double_t *x, Double_t *par) {
  Float_t xx = x[0];
  Float_t yy = x[1];
  Double_t res = par[0] *
                 exp(-(xx - par[1]) * (xx - par[1]) / (2 * par[2] * par[2])) *
                 exp(-(yy - par[1]) * (yy - par[1]) / (2 * par[2] * par[2]));
  return res;
}

void ListTest(int NGen = 1E5) {
  TCanvas *c = new TCanvas("c", "MyCanvas", 200, 200, 1000, 600);
  c->Divide(2, 2);
  const Int_t NPoints = 4;
  const Float_t x[NPoints] = {1, 2, 3, 4};
  const Float_t y[NPoints] = {1, 4, 9, 16};
  const Float_t ex[NPoints] = {0.1, 0.1, 0.1, 0.1};
  const Float_t ey[NPoints] = {0.2, 0.2, 0.2, 0.2};
  TF2 *f = new TF2("f", MyGauss2D, -5, 5, -5, 5, 3);
  f->SetParameters(1 / sqrt(2 * M_PI), 0, 1);
  TList *l = new TList();
  TH1F *h1 = new TH1F("h1", "Gaussian Distribution 1", 100, -5, 5);
  TH1F *h2 = new TH1F("h2", "Gaussian Distribution 2", 100, -5, 5);
  TH2F *h3 =
      new TH2F("h2", "Distribuzione Gaussiana 2D", 100, -5, 5, 100, -5, 5);
  TGraphErrors *g = new TGraphErrors(NPoints, x, y, ex, ey);
  h1->FillRandom("gaus", NGen);
  h2->FillRandom("gaus", NGen);
  h3->FillRandom("f", NGen);
  l->Add(h1);
  l->Add(h2);
  l->Add(h3);
  l->Add(g);
  for (int i = 0; i < 4; ++i) {
    c->cd(i + 1);
    if (l->At(i)->InheritsFrom("TH2")) {
      l->At(i)->Draw("surf1 cyl");
    } else {
      l->At(i)->Draw();
    }
  }
  l->Print();
}