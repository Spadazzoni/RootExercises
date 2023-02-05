#include "RootClass.h"
#include "TFile.h"

void RootClassMain(Int_t nGen = 1E5) {
  R__LOAD_LIBRARY(RootClass_C.so);
  TFile *file = new TFile("Histo.root","recreate");
  TH1F *h1 = new TH1F("h", "Histo", 100, -5, 5);
  TF1 *f = new TF1("f", "x", 0, 1);
  RootClass *h2 = new RootClass(h1);
  h2->Generate(f, nGen);
  h2->ShowHisto();
  h2->Write("A");
  file->Close();
}