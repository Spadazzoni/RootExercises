#include "TF1.h"
#include "TH1F.h"
#include "TRandom.h"

Double_t GausAndUnif(Double_t *x, Double_t *par) {
  return par[0] * TMath::Exp(-(x[0] - par[1]) * (x[0] - par[1]) /
                             (2 * par[2] * par[2])) +
         par[3];
}

void Esame5() {
  gRandom->SetSeed();
  TH1F *htot[3];
  TString name[3] = {"Gauss", "Exp", "Sum"};
  TF1 *f = new TF1("f", GausAndUnif, 0, 5, 4);
  f->SetParameter(1, 2.5);
  f->SetParameter(2, 0.25);
  for (int i = 0; i < 2; ++i) {
    htot[i] = new TH1F("h" + name[i], name[i], 500, 0, 5);
    htot[i]->Sumw2();
  }
  for (int i = 0; i < 1E6; ++i) {
    htot[0]->Fill(gRandom->Gaus(2.5, 0.25));
  }
  for (int i = 0; i < 1E4; ++i) {
    htot[1]->Fill(gRandom->Uniform(0, 5));
  }
  htot[2] = new TH1F(*htot[0]);
  htot[2]->SetName("h" + name[2]);
  htot[2]->SetTitle(name[2]);
  htot[2]->Add(htot[0], htot[1], 1, 1);
  htot[2]->Fit(f, "Q");
  std::cout << "Parameter 1: " << f->GetParameter(0) << " +/- "
            << f->GetParError(0) << '\n';
  std::cout << "Parameter 2: " << f->GetParameter(1) << " +/- "
            << f->GetParError(1) << '\n';
  std::cout << "Parameter 3: " << f->GetParameter(2) << " +/- "
            << f->GetParError(2) << '\n';
  std::cout << "Parameter 4: " << f->GetParameter(3) << " +/- "
            << f->GetParError(3) << '\n';
  std::cout << "Reduced Chisquare: " << f->GetChisquare() / f->GetNDF() << '\n';
}