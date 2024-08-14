#include <iostream>
#include <TFile.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TLegend.h>

void comparison() {
    // Open ROOT files
    TFile *file1 = TFile::Open("config00.root");
    TFile *file2 = TFile::Open("config01.root");
    TFile *file3 = TFile::Open("config10.root");
    TFile *file4 = TFile::Open("config11.root");

    // Retrieve histograms
    TH1D *h_pt1 = (TH1D*)file1->Get("h_pt");
    TH1D *h_pt2 = (TH1D*)file2->Get("h_pt");
    TH1D *h_pt3 = (TH1D*)file3->Get("h_pt");
    TH1D *h_pt4 = (TH1D*)file4->Get("h_pt");

    TH1D *h_ratio2 = (TH1D*)h_pt2->Clone("h_ratio2");
    TH1D *h_ratio3 = (TH1D*)h_pt3->Clone("h_ratio3");
    TH1D *h_ratio4 = (TH1D*)h_pt4->Clone("h_ratio4");

    h_ratio2->Divide(h_pt1);
    h_ratio3->Divide(h_pt1); 
    h_ratio4->Divide(h_pt1);

    h_ratio2->Rebin(4);
    h_ratio3->Rebin(4);
    h_ratio4->Rebin(4);

    h_ratio2->Scale(0.25);
    h_ratio3->Scale(0.25);
    h_ratio4->Scale(0.25);  

    h_ratio2->SetStats(0);
    h_ratio3->SetStats(0);
    h_ratio4->SetStats(0);

    TCanvas *c = new TCanvas("c", "pT Ratio Comparison", 1200, 600);

    h_ratio2->SetLineColor(kBlue);
    h_ratio3->SetLineColor(kGreen+2);
    h_ratio4->SetLineColor(kBlack);

    h_ratio2->Draw("HIST");
    h_ratio3->Draw("HIST SAME");
    h_ratio4->Draw("HIST SAME");

    // Set axis titles
    h_ratio2->GetXaxis()->SetTitle("p_T");
    h_ratio2->GetYaxis()->SetTitle("Ratio to ISR=off, FSR=off");

    h_ratio2->GetYaxis()->SetRangeUser(0., 13.);
    h_ratio3->GetYaxis()->SetRangeUser(0., 13.);
    h_ratio4->GetYaxis()->SetRangeUser(0., 13.);

    // Add legend
    TLegend *leg = new TLegend(0.7, 0.7, 0.9, 0.9);
    leg->AddEntry(h_ratio2, "ISR=off, FSR=on / ISR=off, FSR=off", "l");
    leg->AddEntry(h_ratio3, "ISR=on, FSR=off / ISR=off, FSR=off", "l");
    leg->AddEntry(h_ratio4, "ISR=on, FSR=on / ISR=off, FSR=off", "l");
    leg->Draw();

    // Save the canvas as a PDF
    c->SaveAs("pT_ratio.pdf");

    // Close files
    file1->Close();
    file2->Close();
    file3->Close();
    file4->Close();
}

int main() {
    comparison();
    return 0;
}
