#include "RootClass.h"

RootClass::RootClass(TH1F* Histo) : fHisto{new TH1F(*Histo)} {}
RootClass::RootClass() : fHisto{new TH1F("h", "Histo", 100, -5, 5)} {}
RootClass::~RootClass() { delete fHisto; }
void RootClass::Generate(TF1* f, Int_t NGen) {
  fHisto->GetXaxis()->SetRangeUser(f->GetXmin(), f->GetXmax());
  fHisto->FillRandom(f->GetName(), NGen);
}
void RootClass::ShowHisto() const { fHisto->DrawCopy(); }
TH1F* RootClass::GetHisto() const { return fHisto; }
ClassImp(RootClass);