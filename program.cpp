#include "Pythia8/Pythia.h"
#include "TFile.h"
#include "TH1D.h"
#include <iostream>
#include <string>

using namespace Pythia8;

// Function to generate events and fill histograms
void generateEvents(const std::string& configFile, const std::string& outputFile) {
    // Initialize Pythia with a configuration file
    Pythia pythia;
    pythia.readFile(configFile);
    pythia.readString("Beams:idA = 2212");
    pythia.init();

    int numEvents = pythia.mode("Main:numberOfEvents");

    // Create ROOT file and histograms
    TFile *rootFile = new TFile(outputFile.c_str(), "RECREATE");
    TH1D *h_pt = new TH1D("h_pt", "Higgs pT", 100, 0, 500);
    TH1D *h_y = new TH1D("h_y", "Higgs rapidity", 100, -5, 5);

    // Event loop
    for (int i = 0; i < numEvents; ++i) {
        if (!pythia.next()) continue;

        // Loop through the event record in reverse order
        for (int j = pythia.event.size() - 1; j >= 0; --j) {
            if (pythia.event[j].id() == 25) {  // Higgs boson
                h_pt->Fill(pythia.event[j].pT());
                h_y->Fill(pythia.event[j].y());
                break;  // Exit the loop after the first (last in record) Higgs is found
            }
        }
    }

    // Write histograms to file
    rootFile->Write();
    rootFile->Close();

    pythia.stat();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " config_file output_file" << std::endl;
        return 1;
    }

    std::string configFile = argv[1];
    std::string outputFile = argv[2];

    // Generate events and fill histograms
    generateEvents(configFile, outputFile);

    return 0;
}
