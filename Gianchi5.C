#include "TCanvas.h"
#include "TF1.h"
#include "TH1F.h"
#include "TRandom.h"
#include "TStyle.h"

Double_t GausAndExp(Double_t *x, Double_t *par) {
  return par[0] * TMath::Exp(-(x[0] - par[1]) * (x[0] - par[1]) /
                             (2 * par[2] * par[2])) +
         par[3] * TMath::Exp(-x[0] * par[4]);
}

void Gianchi5() {
  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(2210);
  gRandom->SetSeed();
  TCanvas *c = new TCanvas("c", "MyCanvas", 200, 200, 550, 450);
  TH1F *htot[3];
  TF1 *f = new TF1("f", GausAndExp, 0, 5, 5);
  f->SetParameter(1, 2);
  f->SetParameter(2, 0.5);
  f->SetParameter(4, 1);
  TString name[3] = {"1", "2", "Sum"};
  for (int i = 0; i < 2; ++i) {
    htot[i] = new TH1F("h" + name[i], "Hist " + name[i], 500, 0, 5);
    htot[i]->Sumw2();
  }
  for (int i = 0; i < 1E6; ++i) {
    htot[0]->Fill(gRandom->Gaus(2, 0.5));
  }
  for (int i = 0; i < 1E5; ++i) {
    htot[1]->Fill(gRandom->Exp(1));
  }
  htot[2] = new TH1F(*htot[0]);
  htot[2]->SetName("h" + name[2]);
  htot[2]->SetTitle(name[2]);
  htot[2]->Add(htot[0], htot[1], 1, 1);
  htot[2]->Fit(f, "Q");
  std::cout << "///////////FIT RESULTS///////////" << '\n';
  std::cout << "Parameter 1: " << f->GetParameter(0) << " +/- "
            << f->GetParError(0) << '\n';
  std::cout << "Parameter 2: " << f->GetParameter(1) << " +/- "
            << f->GetParError(1) << '\n';
  std::cout << "Parameter 3: " << f->GetParameter(2) << " +/- "
            << f->GetParError(2) << '\n';
  std::cout << "Parameter 4: " << f->GetParameter(3) << " +/- "
            << f->GetParError(3) << '\n';
  std::cout << "Parameter 5: " << f->GetParameter(4) << " +/- "
            << f->GetParError(4) << '\n';
  std::cout << "Reduced ChiSquare: " << f->GetChisquare() / f->GetNDF() << '\n';
}