#include "TCanvas.h"
#include "TColor.h"
#include "TF1.h"
#include "TH1F.h"
#include "TRandom.h"

Double_t MyErf(Double_t *x, Double_t *par) {
  Float_t xx = x[0];
  return TMath::Erf(xx);
}

Double_t ProfErf(Double_t *x, Double_t *par) {
  return ((TMath::Erf((x[0] - par[0]) / par[1] + 1)) / 2) * par[2];
}

void EfficiencyExp(Int_t nGen = 1E5) {
  gRandom->SetSeed();
  TH1F *htot[3];
  TString name[3] = {"hGen", "hAcc", "hEff"};
  TString title[3] = {"Generated Entries", "Accepted Entries",
                      "Efficiency Effects"};
  EColorPalette color[3] = {kPlum, kGreyScale, kAlpine};
  for (int i = 0; i < 3; ++i) {
    htot[i] = new TH1F(name[i], title[i], 100, 0, 10);
    htot[i]->GetXaxis()->SetTitle("X axis");
    htot[i]->GetYaxis()->SetTitle("Entries");
    htot[i]->SetFillColor(color[i]);
    htot[i]->Sumw2();
  }
  // TF1 *f = new TF1("f", MyErf, 0, 10, 0);
  TF1 *f = new TF1("f", ProfErf, 0, 10, 3);
  f->SetParameters(5, .5, .7);
  TCanvas *c = new TCanvas("c", "MyCanvas", 200, 200, 900, 300);
  c->Divide(3, 1);
  for (int i = 0; i < nGen; ++i) {
    Double_t x = gRandom->Exp(1);
    Double_t eff = gRandom->Rndm();
    if (eff < f->Eval(x)) {
      htot[1]->Fill(x);
    }
    htot[0]->Fill(x);
  }
  htot[2]->Divide(htot[1], htot[0], 1, 1);
  for (int i = 0; i < 3; ++i) {
    c->cd(i + 1);
    htot[i]->Sumw2(kFALSE);
    htot[i]->Draw();
  }
  std::cout << "Integral Efficiency: "
            << htot[1]->Integral() / htot[0]->Integral() << '\n';
}