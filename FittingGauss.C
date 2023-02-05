#include "TCanvas.h"
#include "TF1.h"
#include "TFitResult.h"
#include "TH1F.h"
#include "TLegend.h"
#include "TMatrixD.h"
#include "TRandom.h"
#include "TStyle.h"

Double_t GaussForFitting(Double_t *x, Double_t *par) {
  Float_t xx = x[0];
  Float_t result =
      par[0] * exp(-(xx - par[1]) * (xx - par[1]) / (2 * par[2] * par[2]));
  return result;
}

void FittingGauss(int nGen = 1E5) {
  gRandom->SetSeed();
  gStyle->SetOptStat(2210);
  gStyle->SetOptFit(1111);
  TH1F *htot[2];
  TString names[2] = {" 1", " 2"};
  EColor colors[2] = {kBlue, kOrange};
  TF1 *f1 = new TF1("f1", GaussForFitting, -5, 5, 3);
  f1->SetParameters(1 / (sqrt(2 * M_PI)), 0, 1);
  TF1 *f2 = new TF1("f2", "gaus", -5, 5);
  TString fnames[2] = {"f1", "gaus"};
  TF1 *ftot[2] = {f1, f2};
  TCanvas *c = new TCanvas("c", "MyCanvasTest", 200, 200, 1000, 600);
  c->Divide(2, 1);
  TLegend *l = new TLegend(.25, .1, "Legend");
  for (int i = 0; i < 2; ++i) {
    htot[i] = new TH1F("h" + names[i], "Gaussian Distribution" + names[i], 100,
                       -5, 5);
    htot[i]->FillRandom(fnames[i], nGen);
    htot[i]->Fit(ftot[i], "QS0");
    htot[i]->SetFillColor(colors[i]);
    htot[i]->GetXaxis()->SetTitle("X axis");
    htot[i]->GetYaxis()->SetTitle("Entries");
    c->cd(i + 1);
    htot[i]->Draw();
    ftot[i]->Draw("same");
  }
  TFitResultPtr res = htot[0]->Fit("f1", "QS0");
  TMatrixD cor = res->GetCorrelationMatrix();
  l->AddEntry(htot[1], "Histo");
  l->AddEntry(f2, "Fit");
  c->cd(2);
  l->Draw();
  std::cout << "----FIT RESULTS-----" << '\n';
  std::cout << "Width:  " << f1->GetParameter(0) << " +/- "
            << f1->GetParError(0) << '\n';
  std::cout << "Mean:  " << f1->GetParameter(1) << " +/- " << f1->GetParError(1)
            << '\n';
  std::cout << "RMS:  " << f1->GetParameter(2) << " +/- " << f1->GetParError(2)
            << '\n';
  std::cout << "Chisquare:  " << f1->GetChisquare() << '\n';
  std::cout << "Degrees of Freedom:  " << f1->GetNDF() << '\n';
  std::cout << "Reduced Chisquare:  " << f1->GetChisquare() / f1->GetNDF()
            << '\n';
  std::cout << "Probability of Chisquare:  " << f1->GetProb() << '\n';
  cor.Print();
}