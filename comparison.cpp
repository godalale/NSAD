#include <iostream>
#include <TFile.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TLegend.h>

void comparison() {
    // Open ROOT files
    TFile *file1 = TFile::Open("output1.root");
    TFile *file2 = TFile::Open("output2.root");
    TFile *file3 = TFile::Open("output3.root");
    TFile *file4 = TFile::Open("output4.root");

    // Retrieve histograms
    TH1D *h_pt1 = (TH1D*)file1->Get("h_pt");
    TH1D *h_pt2 = (TH1D*)file2->Get("h_pt");
    TH1D *h_pt3 = (TH1D*)file3->Get("h_pt");
    TH1D *h_pt4 = (TH1D*)file4->Get("h_pt");

    TH1D *h_y1 = (TH1D*)file1->Get("h_y");
    TH1D *h_y2 = (TH1D*)file2->Get("h_y");
    TH1D *h_y3 = (TH1D*)file3->Get("h_y");
    TH1D *h_y4 = (TH1D*)file4->Get("h_y");

    // Create canvas for pT comparison
    TCanvas *c1 = new TCanvas("c1", "pT Comparison", 800, 600);
    h_pt1->SetLineColor(kRed);
    h_pt2->SetLineColor(kBlue);
    h_pt3->SetLineColor(kGreen);
    h_pt4->SetLineColor(kBlack);

    h_pt1->Draw();
    h_pt2->Draw("SAME");
    h_pt3->Draw("SAME");
    h_pt4->Draw("SAME");

    TLegend *leg1 = new TLegend(0.7, 0.7, 0.9, 0.9);
    leg1->AddEntry(h_pt1, "ISR=on, FSR=on", "l");
    leg1->AddEntry(h_pt2, "ISR=off, FSR=on", "l");
    leg1->AddEntry(h_pt3, "ISR=on, FSR=off", "l");
    leg1->AddEntry(h_pt4, "ISR=off, FSR=off", "l");
    leg1->Draw();

    c1->SaveAs("pT_comparison.png");

    // Create canvas for rapidity comparison
    TCanvas *c2 = new TCanvas("c2", "Rapidity Comparison", 800, 600);
    h_y1->SetLineColor(kRed);
    h_y2->SetLineColor(kBlue);
    h_y3->SetLineColor(kGreen);
    h_y4->SetLineColor(kBlack);

    h_y1->Draw();
    h_y2->Draw("SAME");
    h_y3->Draw("SAME");
    h_y4->Draw("SAME");

    TLegend *leg2 = new TLegend(0.7, 0.7, 0.9, 0.9);
    leg2->AddEntry(h_y1, "ISR=on, FSR=on", "l");
    leg2->AddEntry(h_y2, "ISR=off, FSR=on", "l");
    leg2->AddEntry(h_y3, "ISR=on, FSR=off", "l");
    leg2->AddEntry(h_y4, "ISR=off, FSR=off", "l");
    leg2->Draw();

    c2->SaveAs("rapidity_comparison.png");

    // Close files
    file1->Close();
    file2->Close();
    file3->Close();
    file4->Close();
}

int main() {
    compare_isr_fsr();
    return 0;
}
