#include <iostream>
#include <vector>
#include "TRandom3.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TStyle.h"
#include "TLegend.h"

void ohmLaw(const int N = 10, const double R = 10.0, const double smearing = 0.10, const int nExperiments = 10000)
{
    std::vector<double> sigmaV(N);
    std::vector<double> I(N);
    std::vector<double> VTrue(N);

    for (int i = 0; i < N; i++)
    {
        I[i] = (double)(i + 1);
        VTrue[i] = R*I[i];
        sigmaV[i] = smearing * VTrue[i];
    }
    std::vector<double> VFirst(N);    // V
    TRandom3 randGen(42);
    for (int i = 0; i < N; i++)
    {
        VFirst[i] = randGen.Gaus(VTrue[i], sigmaV[i]);
    }

    TGraphErrors* firstGraph = new TGraphErrors(N, I.data(), VFirst.data(), 0, sigmaV.data());
    firstGraph->SetMarkerSize(0.8);
    firstGraph->SetMarkerStyle(20);
    firstGraph->SetTitle("Model based on first simulation;I [A]; V [V]");
    firstGraph->Fit("pol1", "Q");
    TF1* firstFit = firstGraph->GetFunction("pol1");
    double aFit = firstFit->GetParameter(0);
    double bFit = firstFit->GetParameter(1);
    double errAFit = firstFit->GetParError(0);
    double errBFit = firstFit->GetParError(1);

    /*
    std::cout << "V = (" << aFit << " +/- " << errAFit << ") + (" 
              << bFit << " +/- " << errBFit << ")*I\n";
    */

    // Multiple experiments to evaluate chi-squared distribution
    std::vector<double> VModel(N);
    std::vector<double> sigmaVModel (N);

    for (int i = 0; i < N; i++)
    {
        VModel[i] = aFit + bFit * I[i];
        sigmaVModel[i] = smearing * VModel[i];
    }

    TH1D* chiSquareHisto = new TH1D("chiSquareHisto", "Chi-Square Distribution", 50, 0, 30);
    std::vector<double> VSample(N);
    double chi2;
    TF1* fitFunc = new TF1("fitFunc", "pol1", 0, 11);
    // Multiple experiments loop
    for (int exp = 0; exp < nExperiments; exp++)
    {
        for (int i = 0; i < N; i++)
        {
            VSample[i] = randGen.Gaus(VModel[i], sigmaVModel[i]);
        }
        TGraphErrors* gr = new TGraphErrors(N, I.data(), VSample.data(), 0, sigmaVModel.data());
        gr->Fit(fitFunc, "QN");
        chi2 = fitFunc->GetChisquare();
        chiSquareHisto->Fill(chi2);

        delete gr;
    }

    double scale = 1.0 / (chiSquareHisto->Integral() * chiSquareHisto->GetBinWidth(1));
    chiSquareHisto->Scale(scale);
    gStyle->SetOptStat(1111); // Shows stats box
    chiSquareHisto->SetLineColor(kBlue+1);
    chiSquareHisto->SetFillColorAlpha(kBlue+1, 0.3);
    chiSquareHisto->SetLineWidth(2);

    TCanvas* canvas = new TCanvas("canvas", "canvas", 1000, 600);
    chiSquareHisto->Draw("HIST");

    // Theoretical chi-squared distribution
    int dof = N - 2;
    TF1* trueChiSquare = new TF1("trueChiSquare", "ROOT::Math::chisquared_pdf(x, [0])", 0, 30);
    trueChiSquare->SetParameter(0, dof);
    trueChiSquare->SetLineWidth(3);
    trueChiSquare->Draw("SAME");

    TLegend *leg = new TLegend(0.55, 0.65, 0.85, 0.85);
    leg->AddEntry(chiSquareHisto, "Simulated Experiments", "f");
    leg->AddEntry(trueChiSquare, Form("Theoretical #chi^{2} (dof=%d)", dof), "l");
    leg->Draw();

    std::cout << "Done. Mean Chi2: " << chiSquareHisto->GetMean() << " (Expected: " << dof << ")" << std::endl;
}