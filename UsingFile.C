#include "TFile.h"
#include "RootClass.h"

void UsingFile() {
    R__LOAD_LIBRARY(RootClass_C.so);
    TFile *file = new TFile("Histo.root", "read");
    RootClass* hist = (RootClass*)file->Get("A");
    hist->ShowHisto();
}