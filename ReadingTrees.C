#include "TCanvas.h"
#include "TFile.h"
#include "TH1F.h"
#include "TTree.h"

void ReadingTrees() {
  TFile *f = new TFile("Trees.root", "read");
  TTree *t = (TTree *)f->Get("t");
  t->Print();
  // si possono disegnare automaticamente
  //  i branch in funzione del loro nome
  TCanvas *c1 = new TCanvas("c1", "MyCanvas1", 200, 200, 900, 300);
  TCanvas *c2 = new TCanvas("c2", "MyCanvas2", 200, 200, 900, 300);
  TH1F *h = new TH1F("h", "Histos from Tree", 100, 7, 13);
  c1->Divide(3, 1);
  c2->Divide(3, 1);
  c1->cd(1);
  t->Draw("x>>h");
  c1->cd(2);
  t->Draw("y");
  c1->cd(3);
  t->Draw("z");
  c2->cd();
  c2->cd(1);
  t->Draw("sqrt(x*y+z)");
  c2->cd(2);
  t->Draw("y:x");
  c2->cd(3);
  t->Draw("z:y:x");
}