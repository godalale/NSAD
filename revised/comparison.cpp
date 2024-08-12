#include <iostream>
#include <TFile.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <THStack.h>

void comparison() {
    // Open ROOT files
    TFile *file1 = TFile::Open("revision00.root");
    TFile *file2 = TFile::Open("revision01.root");
    TFile *file3 = TFile::Open("revision10.root");
    TFile *file4 = TFile::Open("revision11.root");

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
    TCanvas *c1 = new TCanvas("c1", "pT Comparison", 1200, 600);
    
    // Create THStack for pT histograms
    THStack *stack_pt = new THStack("stack_pt", "pT Comparison");
    h_pt1->SetLineColor(kRed);
    h_pt2->SetLineColor(kBlue);
    h_pt3->SetLineColor(kGreen+2);
    h_pt4->SetLineColor(kBlack);

    stack_pt->Add(h_pt1);
    stack_pt->Add(h_pt2);
    stack_pt->Add(h_pt3);
    stack_pt->Add(h_pt4);

    stack_pt->Draw("NOSTACK");
    stack_pt->GetXaxis()->SetTitle("p_T");
    stack_pt->GetYaxis()->SetTitle("Events");
    stack_pt->GetXaxis()->SetRangeUser(0., 300.);
    //c1->SetLogy(1);

    TLegend *leg1 = new TLegend(0.7, 0.7, 0.9, 0.9);
    leg1->AddEntry(h_pt1, "ISR=off, FSR=off", "l");
    leg1->AddEntry(h_pt2, "ISR=off, FSR=on", "l");
    leg1->AddEntry(h_pt3, "ISR=on, FSR=off", "l");
    leg1->AddEntry(h_pt4, "ISR=on, FSR=on", "l");
    leg1->Draw();

    c1->SaveAs("pT_comparison_revised.pdf");

    // Create canvas for rapidity comparison
    TCanvas *c2 = new TCanvas("c2", "Rapidity Comparison", 1200, 600);

    // Create THStack for rapidity histograms
    THStack *stack_y = new THStack("stack_y", "Rapidity Comparison");
    h_y1->SetLineColor(kRed);
    h_y2->SetLineColor(kBlue);
    h_y3->SetLineColor(kGreen+2);
    h_y4->SetLineColor(kBlack);

    stack_y->Add(h_y1);
    stack_y->Add(h_y2);
    stack_y->Add(h_y3);
    stack_y->Add(h_y4);

    stack_y->Draw("NOSTACK");
    stack_y->GetXaxis()->SetTitle("y");
    stack_y->GetYaxis()->SetTitle("Events");
    //c2->SetLogy(1);

    TLegend *leg2 = new TLegend(0.7, 0.7, 0.9, 0.9);
    leg2->AddEntry(h_y1, "ISR=off, FSR=off", "l");
    leg2->AddEntry(h_y2, "ISR=off, FSR=on", "l");
    leg2->AddEntry(h_y3, "ISR=on, FSR=off", "l");
    leg2->AddEntry(h_y4, "ISR=on, FSR=on", "l");
    leg2->Draw();

    c2->SaveAs("rapidity_comparison_revised.pdf");

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