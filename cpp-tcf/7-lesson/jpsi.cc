#include <iostream>
#include <fstream>
#include "TH1D.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TFitResult.h"
#include "TFitResultPtr.h"

void jpsi()
{
    TH1D *hist = new TH1D("hist", "Invariant mass distribution", 100, 1.3, 5);

    double readValue;

    std::ifstream inputFile("jpsimass.txt");
    while (inputFile >> readValue)
        hist->Fill(readValue);
    
    TF1 *modelfit = new TF1("modelfit", "gaus(0) + pol1(3) + gaus(5)", 1, 5);
    modelfit->SetNpx(5000);
    modelfit->SetParameters(8e3,3.1,0.14,50e3,-1e3, 1e3, 3.6, 0.14);
    modelfit->SetParLimits(2, 0, 1); // force std dev > 0
    modelfit->SetParLimits(7, 0, 1); // force std dev > 0
    TFitResultPtr r = hist->Fit(modelfit,"RMSL");

    TCanvas *can = new TCanvas("canvas","canvas",1000,1000);
    can->SetMargin(0.15,0.05,0.1,0.1);
    can->cd();

    hist->GetXaxis()->SetTitle("m_{#mu^{+}#mu^{-}}");
    hist->GetYaxis()->SetTitle("counts");
    hist->Draw("E");

    double chi2 = r.Get()->Chi2();
    int ndf = r.Get()->Ndf();
    double prob = r.Get()->Prob();
    double maximumLikelihood = std::exp(- r.Get()->MinFcnValue());

    std::cout << "Chi^2/NdF = " << chi2 << "/" << ndf << std::endl;
    std::cout << "p-value: " << prob << std::endl;
}