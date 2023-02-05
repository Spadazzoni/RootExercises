#ifndef ROOTCLASS_H
#define ROOTCLASS_H

#include "TF1.h"
#include "TH1F.h"
#include "TRandom.h"

class RootClass : public TObject {
 public:
  RootClass(TH1F*);
  RootClass();
  ~RootClass();
  void Generate(TF1*, Int_t);
  void ShowHisto() const;
  TH1F* GetHisto() const;

 private:
  TH1F* fHisto;
  ClassDef(RootClass, 1);
};

#endif