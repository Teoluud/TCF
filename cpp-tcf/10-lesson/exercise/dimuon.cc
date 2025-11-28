#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TF1.h"
#include "TStyle.h"
#include "TMarker.h"
#include <iostream>

void dimuon()
{
    TFile* file = new TFile("dimuontree.root", "READ");
    TTree* tree = (TTree*)file->Get("tree");
    
    float mass;
    float dcaMuons;
    float dcaPV;
    
    tree->SetBranchAddress("mass", &mass);
    tree->SetBranchAddress("dcaMuons", &dcaMuons);
    tree->SetBranchAddress("dcaPV", &dcaPV);

    // Define histograms
    double muonsCutMin = 0.0;
    double muonsCutMax = 0.24;
    int nBinsMuons = 24;
    double PVCutMin = 0.0;
    double PVCutMax = 0.20;
    int nBinsPV = 40;
    TH2F* hTotal = new TH2F("hTotal", "Total Events Passing Cuts", 
                            nBinsMuons, muonsCutMin, muonsCutMax, 
                            nBinsPV, PVCutMin, PVCutMax);
    TH2F* hBkg   = new TH2F("hBkg", "Background Events",
                            nBinsMuons, muonsCutMin, muonsCutMax, 
                            nBinsPV, PVCutMin, PVCutMax);
    TH2F* hSignif = new TH2F("hSignif", "Significance Map;Muon Cut; PV Cut",
                            nBinsMuons, muonsCutMin, muonsCutMax,
                            nBinsPV, PVCutMin, PVCutMax);

    
    // Read file
    Long64_t nEntries = tree->GetEntries();
    std::cout << "Scanning " << nEntries << " events to fill histograms..." << std::endl;

    for (Long64_t k = 0; k < nEntries; k++)
    {
        tree->GetEntry(k);

        // For every event, check which bins (cuts) it satisfies
        for (int i = 1; i <= nBinsMuons; i++)
        {
            // Get the cut value of bin i
            double cutMuon = hTotal->GetXaxis()->GetBinUpEdge(i);

            // Pre-check:
            // Check Signal Region OR Sideband Region
            bool isSignalMuon = (TMath::Abs(dcaMuons) < cutMuon);
            bool isSidebandMuon = (dcaMuons > (0.5 - cutMuon) && dcaMuons < (0.5 + cutMuon));
            if (!isSignalMuon && !isSidebandMuon) continue;

            // Actual check
            for (int j = 1; j <= nBinsPV; j++)
            {
                double cutPV = hTotal->GetYaxis()->GetBinUpEdge(j);
                if (TMath::Abs(dcaPV) < cutPV)
                {
                    if (isSignalMuon) hTotal->Fill(cutMuon - 0.001, cutPV - 0.001);
                    if (isSidebandMuon) hBkg->Fill(cutMuon - 0.001, cutPV - 0.001);
                    // We subtract 0.001 to ensure we fill "inside" the bin we defined
                }
            }
        }
    }

    // Calculate Significance
    double bestMu = 0.0;
    double bestPV = 0.0;
    double maxSig = 0.0;
    
    for (int i = 1; i <= nBinsMuons; i++)
    {
        for (int j = 1; j <= nBinsPV; j++)
        {
            double nTot = hTotal->GetBinContent(i, j);
            double nBkgVal = hBkg->GetBinContent(i, j);

            if (nTot == 0) continue;

            double signal = nTot - nBkgVal;
            if (signal < 0) signal = 0;

            double sig = signal / TMath::Sqrt(nTot);
            hSignif->SetBinContent(i, j, sig);

            if (sig > maxSig)
            {
                maxSig = sig;
                bestMu = hTotal->GetXaxis()->GetBinUpEdge(i);
                bestPV = hTotal->GetYaxis()->GetBinUpEdge(j);
            }
        }
    }

    // Visualization of the optimization
    TCanvas* cOpt = new TCanvas("cOpt", "Optimization", 600, 600);
    gStyle->SetOptStat(0);
    cOpt->cd();
    hSignif->Draw("COLZ");
    TMarker* m = new TMarker(bestMu, bestPV, 29);
    m->SetMarkerSize(2); m->SetMarkerColor(kRed); m->Draw();

    std::cout << "Best Cuts Found: Muon < " << bestMu << ", PV < " << bestPV << std::endl;

    // Fit
    TCanvas* cFinal = new TCanvas("cFinal", "Final Fit", 800, 600);
    cFinal->SetLogy();

    TH1F* hMass = new TH1F("hMass", "Dimuon Mass Spectrum;mass (GeV/c^{2})", 100, 2.0, 5.0);
    tree->Draw("mass >> hMass", Form("abs(dcaMuons) < %f && abs(dcaPV) < %f", bestMu, bestPV));

    TF1* finalFit = new TF1("finalFit", "gaus(0) + gaus(3) + expo(6)", 2.0, 5.0);
    // Set J/psi peak parameters
    finalFit->SetParameter(0, hMass->GetMaximum()); // Height
    finalFit->SetParameter(1, 3.09);                // Mean
    finalFit->SetParameter(2, 0.2);                 // Sigma
    finalFit->SetParLimits(2, 0., 1.);
    // Set psi(2S) peak parameters
    finalFit->SetParameter(3, hMass->GetMaximum() / 5.0);
    finalFit->SetParameter(4, 3.68);
    finalFit->SetParameter(5, 0.2);
    finalFit->SetParLimits(5, 0., 1.);

    hMass->Draw("E");
    hMass->Fit("finalFit", "Q");

    double binW = hMass->GetBinWidth(1);
    double jpsiCount  = (finalFit->GetParameter(0) * finalFit->GetParameter(2) * TMath::Sqrt(2*TMath::Pi())) / binW;
    double psi2sCount = (finalFit->GetParameter(3) * finalFit->GetParameter(5) * TMath::Sqrt(2*TMath::Pi())) / binW;

    double jpsiError = TMath::Sqrt(jpsiCount);
    double psi2sError = TMath::Sqrt(psi2sCount);

    std::cout << "---------------- RESULTS ----------------" << std::endl;
    std::cout << Form("J/psi:   (%0.f +/- %0.f) events", jpsiCount, jpsiError) << std::endl;
    std::cout << Form("Psi(2S): (%0.f +/- %0.f) events", psi2sCount, psi2sError) << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
}