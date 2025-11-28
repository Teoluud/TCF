#include <iostream>
#include "TF1.h"
#include "TRandom3.h"
#include "TString.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TMath.h"
/*
TString getFormula()
{
    TString formula;
    std::cout << "Input the function you want to integrate: ";
    std::cin >> formula;
    return formula;
}
*/
void integration(TString formula, Double_t xMin, Double_t xMax, const Int_t nPoints = 1000000)
{
    /*
    TString formula = getFormula();
    Double_t xMin, xMax;
    std::cout << "Input the integration range: ";
    std::cin >> xMin >> xMax; 
    */
    TF1* function = new TF1("function", formula, xMin, xMax);
    TRandom3 randGen(42);
    Double_t yMax = function->GetMaximum(xMin, xMax);
    Double_t yMin = function->GetMinimum(xMin, xMax);
    if (yMin > 0) yMin = 0;
    
    // MonteCarlo loop
    Int_t nPosHits = 0;
    Int_t nNegHits = 0;

    TGraph* hitsGraph = new TGraph();
    TGraph* missesGraph = new TGraph();
    
    for (int i = 0; i < nPoints; i++)
    {
        // Generate a random point inside a box
        Double_t x = xMin + randGen.Rndm() * (xMax - xMin);
        Double_t y = yMin + randGen.Rndm() * (yMax - yMin);

        // Check if the point is "under" the curve
        if (y >= 0 && y <= function->Eval(x))
        {
            nPosHits++;
            hitsGraph->SetPoint(hitsGraph->GetN(), x, y);
        }
        
        else if (y < 0 && y >= function->Eval(x))
        {
            nNegHits++;
            hitsGraph->SetPoint(hitsGraph->GetN(), x, y);
        }

        else
        {
            missesGraph->SetPoint(missesGraph->GetN(), x, y);
        }
    }
    
    Int_t nHits = nPosHits - nNegHits;
    Double_t boxArea = (xMax - xMin) * (yMax - yMin);
    Double_t integral =  boxArea * (double) nHits / nPoints;
    
    // Graphic representation
    hitsGraph->SetMarkerStyle(20);
    hitsGraph->SetMarkerSize(0.5);
    hitsGraph->SetMarkerColor(kGreen + 2);
    missesGraph->SetMarkerStyle(20);
    missesGraph->SetMarkerSize(0.5);
    missesGraph->SetMarkerColor(kRed);
    
    TCanvas* c1 = new TCanvas("c1", "Hit and Miss Integration", 1000, 800);
    function->SetLineColor(kBlue);
    function->SetLineWidth(5);
    function->Draw();
    hitsGraph->Draw("P SAME");
    missesGraph->Draw("P SAME");
    
    // Calculate statistical error
    Int_t nAbsHits = nPosHits + nNegHits;
    Double_t p = (double) nAbsHits / nPoints;
    Double_t integralError = boxArea * TMath::Sqrt(p * (1-p)/ nPoints);

    std::cout << Form("The integral of %s between [%f,%f] = %f +/- %f", 
                        formula.Data(), xMin, xMax, integral, integralError) 
              << std::endl;
    std::cout << "Analytical result: " << function->Integral(xMin, xMax) << std::endl;
}