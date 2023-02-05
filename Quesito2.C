#include "TF1.h"
#include "TH1F.h"
#include "TRandom.h"

Double_t GausExp(Double_t *x, Double_t *par) {
  return par[0] * TMath::Exp(-(x[0] - par[1]) * (x[0] - par[1]) /
                             (2 * par[2] * par[2])) +
         par[3] * TMath::Exp(-x[0] * par[4]);
}

void Quesito2() {
  TH1F *htot[2];
  TString name[2] = {" 1", " 2"};
  TF1 *f = new TF1("f", GausExp, 0, 5, 5);
  // f->SetParameters(1 / sqrt(2 * M_PI * 0.25), 2.5, 0.25, 979, 1);
  f->SetParameter(1, 2.5);
  f->SetParameter(2, 0.25);
  f->SetParameter(4, 1);
  for (int i = 0; i < 2; ++i) {
    htot[i] = new TH1F("h" + name[i], "Gaus" + name[i], 500, 0, 5);
  }
  for (int i = 0; i < 1E6; ++i) {
    htot[0]->Fill(gRandom->Gaus(2.5, 0.25));
  }
  for (int i = 0; i < 1E5; ++i) {
    htot[1]->Fill(gRandom->Exp(1));
  }
  TH1F *hSum = new TH1F(*htot[0]);
  hSum->SetName("hSum");
  hSum->SetTitle("Sum");
  hSum->Add(htot[1], htot[0], 1, 1);
  hSum->Fit(f, "Q");

  std::cout << "Par1: " << f->GetParameter(0) << " +/- " << f->GetParError(0)
            << '\n';
  std::cout << "Par2: " << f->GetParameter(1) << " +/- " << f->GetParError(1)
            << '\n';
  std::cout << "Par3: " << f->GetParameter(2) << " +/- " << f->GetParError(2)
            << '\n';
  std::cout << "Par4: " << f->GetParameter(3) << " +/- " << f->GetParError(3)
            << '\n';
  std::cout << "Par5: " << f->GetParameter(4) << " +/- " << f->GetParError(4)
            << '\n';
  std::cout << "Reduced chisquare: " << f->GetChisquare() / f->GetNDF() << '\n';
}