#include "TCanvas.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TRandom.h"

void UncorrelatedExtractions(Int_t nGen = 1E5) {
  gRandom->SetSeed();
  TH2F *h1 = new TH2F("h1", "Distribution of #varphi and #theta (unbiased)",
                      100, 0, 2 * M_PI, 100, 0, M_PI);
  TH2F *h2 = new TH2F("h2", "Distribution of #varphi and #theta (biased)", 100,
                      0, 2 * M_PI, 100, 0, M_PI);
  TH3F *h3 = new TH3F("h3", "Distribution of #varphi and #theta (unbiased)",
                      100, -1, 1, 100, -1, 1, 100, -1, 1);
  TH3F *h4 = new TH3F("h4", "Distribution of #varphi and #theta (biased)", 100,
                      -1, 1, 100, -1, 1, 100, -1, 1);
  h1->GetXaxis()->SetTitle("#varphi");
  h1->GetYaxis()->SetTitle("#theta");
  h2->GetXaxis()->SetTitle("#varphi");
  h2->GetYaxis()->SetTitle("#theta");
  for (int i = 0; i < nGen; ++i) {
    double phi = gRandom->Uniform(0, 2 * M_PI);
    double theta = gRandom->Uniform(0, M_PI);
    double BiasedTheta = phi / 2;
    h1->Fill(phi, theta);
    h2->Fill(phi, BiasedTheta);
    h3->Fill(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
    h4->Fill(sin(BiasedTheta) * cos(phi), sin(BiasedTheta) * sin(phi),
             cos(BiasedTheta));
  }
  TCanvas *c = new TCanvas("c", "MyCanvas", 200, 200, 700, 600);
  c->Divide(2, 2);
  c->cd(1);
  h1->Draw();
  c->cd(2);
  h2->Draw();
  c->cd(3);
  h3->Draw();
  c->cd(4);
  h4->Draw();
}