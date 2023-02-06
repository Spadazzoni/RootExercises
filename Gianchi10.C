#include "TCanvas.h"
#include "TColor.h"
#include "TF1.h"
#include "TH1F.h"
#include "TRandom.h"

Double_t MyGausExp(Double_t *x, Double_t *par) {
  return par[0] * TMath::Exp(-(x[0] - par[1]) * (x[0] - par[1]) /
                             (2 * par[2] * par[2])) +
         par[3] * TMath::Exp(-x[0] * par[4]);
}

void Gianchi10() {
  gRandom->SetSeed();
  EColor col[3] = {kOrange, kPink, kGreen};
  TCanvas *c = new TCanvas("c", "MyCanvas", 200, 200, 900, 300);
  c->Divide(3, 1);
  TString name[3] = {"1", "2", "Sum"};
  TH1F *htot[3];
  TF1 *f = new TF1("f", MyGausExp, 0, 5, 5);
  f->SetParameter(1, 2.5);
  f->SetParameter(2, 0.25);
  f->SetParameter(4, 1);
  for (int i = 0; i < 2; ++i) {
    htot[i] = new TH1F("h" + name[i], "Histo" + name[i], 500, 0, 5);
    htot[i]->Sumw2();
  }
  for (int i = 0; i < 1E6; ++i) {
    htot[0]->Fill(gRandom->Gaus(2.5, 0.25));
  }
  for (int i = 0; i < 1E5; ++i) {
    htot[1]->Fill(gRandom->Exp(1));
  }
  htot[2] = new TH1F(*htot[0]);
  htot[2]->SetName(name[2]);
  htot[2]->SetTitle(name[2]);
  htot[2]->Add(htot[0], htot[1], 1, 1);
  htot[2]->Fit(f, "Q0");
  for (int i = 0; i < 3; ++i) {
    c->cd(i + 1);
    htot[i]->SetFillColor(col[i]);
    htot[i]->Draw("histo");
    if (i == 2) {
      f->SetLineColor(kPink);
      f->Draw("same");
    }
  }
  std::cout << "//////FIT RESULTS/////////" << '\n';
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
  std::cout << "Reduced Chisquare: " << f->GetChisquare() / f->GetNDF() << '\n';
}