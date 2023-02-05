#include "TBenchmark.h"
#include "TMath.h"
#include "TRandom.h"
#include "TTree.h"
#include "TFile.h"

void WritingTrees(Int_t nGen = 1E5) {
  gRandom->SetSeed();
  TTree *t = new TTree("t", "MyTree");
  TBenchmark *b = new TBenchmark();
  TFile *f = new TFile("Trees.root", "recreate");
  Float_t x;
  Float_t y;
  Float_t z;
  // Branch("nome del branch", indirizzo del branch, leaflist)
  // la leaflist è la concatenzione del nome delle variabili
  // del branch e dei rispettivi tipi, separati da '/'
  // F ad esempio è un 32 bit floating point
  t->Branch("x", &x, "x/F");
  t->Branch("y", &y, "y/F");
  t->Branch("z", &z, "z/F");
  b->Start("Filling the Tree");
  for (long int i = 0; i < nGen; ++i) {
    x = gRandom->Gaus(10,1);
    y = TMath::Erf(x) / sqrt(x);
    z = x * exp(y);
    t->Fill();
  }
  b->Show("Filling the Tree");
  t->Write();
  f->Close();
}