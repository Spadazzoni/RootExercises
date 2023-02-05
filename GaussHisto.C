void myMacro(int nGen = 1E5) {
    TH1F *h = new TH1F("h","Gaus", 100, -5, 5);
    h->FillRandom("gaus", nGen);
    h->SetFillColor(kAquamarine);
    h->SetLineStyle(1);
    h->SetLineColor(kOrange);
    h->GetXaxis()->SetTitle("Asse X");
    h->GetYaxis()->SetTitle("Occorrenze");
    TCanvas *c = new TCanvas("c","MyCanvas", 200, 200, 700, 400);
    c->Divide(2,1);
    c->cd(1);
    h->Draw();
    c->cd(2);
    h->SetMarkerStyle(20);
    h->Draw("E same");
}