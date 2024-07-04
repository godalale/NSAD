#include "Pythia8/Pythia.h"

using namespace Pythia8;

// Function to generate events and fill histograms
void generateEvents(const std::string& configFile, const std::string& outputFile, int numEvents = 10000) {
    // Initialize Pythia with a configuration file
    Pythia pythia;
    pythia.readFile(configFile);
    pythia.init();

    // Create ROOT file and histograms
    TFile *rootFile = new TFile(outputFile.c_str(), "RECREATE");
    TH1D *h_pt = new TH1D("h_pt", "Higgs pT", 100, 0, 500);
    TH1D *h_y = new TH1D("h_y", "Higgs rapidity", 100, -5, 5);

    // Event loop
    for (int i = 0; i < numEvents; ++i) {
        if (!pythia.next()) continue;

        for (int j = 0; j < pythia.event.size(); ++j) {
            if (pythia.event[j].id() == 25) {  // Higgs boson
                h_pt->Fill(pythia.event[j].pT());
                h_y->Fill(pythia.event[j].y());
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