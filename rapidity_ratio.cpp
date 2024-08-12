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
    TH1D *h_y1 = (TH1D*)file1->Get("h_y");
    TH1D *h_y2 = (TH1D*)file2->Get("h_y");
    TH1D *h_y3 = (TH1D*)file3->Get("h_y");
    TH1D *h_y4 = (TH1D*)file4->Get("h_y");

    // h_y1->Rebin(2);
    // h_y2->Rebin(2);
    // h_y3->Rebin(2);
    // h_y4->Rebin(2);

    TH1D *h_ratio2 = (TH1D*)h_y2->Clone("h_ratio2");
    TH1D *h_ratio3 = (TH1D*)h_y3->Clone("h_ratio3");
    TH1D *h_ratio4 = (TH1D*)h_y4->Clone("h_ratio4");

    h_ratio2->Divide(h_y1);  
    h_ratio3->Divide(h_y1);  
    h_ratio4->Divide(h_y1); 

    h_ratio2->Rebin(4);
    h_ratio3->Rebin(4);
    h_ratio4->Rebin(4);

    h_ratio2->SetStats(0);
    h_ratio3->SetStats(0);
    h_ratio4->SetStats(0);

    TCanvas *c = new TCanvas("c", "Rapidity Ratio Comparison", 1200, 600);

    h_ratio2->SetLineColor(kBlue);
    h_ratio3->SetLineColor(kGreen+2);
    h_ratio4->SetLineColor(kBlack);

    h_ratio2->Draw("HIST");
    h_ratio3->Draw("HIST SAME");
    h_ratio4->Draw("HIST SAME");

    // Set axis titles
    h_ratio2->GetXaxis()->SetTitle("y");
    h_ratio2->GetYaxis()->SetTitle("Ratio to ISR=off, FSR=off");

    // Add legend
    TLegend *leg = new TLegend(0.35, 0.8, 0.65, 0.9);
    leg->AddEntry(h_ratio2, "ISR=off, FSR=on / ISR=off, FSR=off", "l");
    leg->AddEntry(h_ratio3, "ISR=on, FSR=off / ISR=off, FSR=off", "l");
    leg->AddEntry(h_ratio4, "ISR=on, FSR=on / ISR=off, FSR=off", "l");
    leg->Draw();

    // Save the canvas as a PDF
    c->SaveAs("rapidity_ratio.pdf");

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
