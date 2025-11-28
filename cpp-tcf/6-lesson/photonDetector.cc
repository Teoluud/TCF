#include "TH1D.h"
#include "TCanvas.h"
#include "TApplication.h"
#include <fstream>
#include <iostream>
#include <vector>

void photonDetector()
{
    double a = 0.2; //mm
    double d = 1000; //mm
    std::vector<double> xVector;
    TH1D *histo = new TH1D("histogram", "photon detection", 250, -11, 11);

    double x = -666;

    std::ifstream inputFile("InterfPattern.txt");
    while(true)
    {
        inputFile >> x;
        if (inputFile.eof() == true) break;
        xVector.push_back(x);
        histo->Fill(x);
    }
    inputFile.close();

    //TApplication theApp ("theApp", 0, 0);
    TCanvas *canvas = new TCanvas("", "", 800, 800);
    canvas->cd();
    histo->Draw("hist");
    //theApp.Run();
    
    TH1D *histo2 = new TH1D("histogram2", "zoom", 50, 1.5, 5.2);
    for (int i = 0; i < xVector.size(); ++i)
    {
        x = xVector.at(i);
        if (x >= 1.7 && x <= 5)
            histo2->Fill(x);
    }

    double x0 = histo->GetMean();
    double x1 = histo2->GetMean();

    canvas->SaveAs("photonDetector.png");

    double deltaX = (x1 - x0); // mm
    std::cout << deltaX << std::endl;
    double lambda = (a * deltaX / d)*1e6; // nm
    std::cout << "Lambda = " << lambda << " nm.\n";

    delete histo;
    delete histo2;
    delete canvas;
}

int main()
{
    photonDetector();
}