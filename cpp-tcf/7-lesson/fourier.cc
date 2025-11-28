#include "TF1.h"
#include "TMath.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TLegend.h"

void fourier(const int maxOrder = 10, const double L = 2*TMath::Pi(), const int nPoints = 1000)
{

    // function to expand
    TF1 *f = new TF1("f", "x*x", -L, L);
    f->SetLineColor(kBlack);
    f->SetLineWidth(6);

    // a0 coefficient
    double a0 = 1.0 / (2*L) * TF1("tmp", "x*x", -L, L).Integral(-L, L);

    // a_n coefficients
    double a[maxOrder + 1];
    for (int n = 1; n <= maxOrder; n++)
    {
        TF1 aIntegrand("aIntegrand", "x*x*cos([0]*x)", -L, L);
        aIntegrand.SetParameter(0, n * TMath::Pi() / L);
        a[n] = 1.0 / L * aIntegrand.Integral(-L, L);
    }

    // b_n coefficients
    double b[maxOrder + 1];
    for (int n = 1; n <= maxOrder; n++)
    {
        TF1 bIntegrand("bIntegrand", "x*x*sin([0]*x)", -L, L);
        bIntegrand.SetParameter(0, n * TMath::Pi() / L);
        b[n] = 1.0 / L * bIntegrand.Integral(-L, L);
    }
    
    TCanvas *canvas = new TCanvas("canvas", "canvas", 1000, 1000);
    //canvas->Print("fourier.gif[");

    TGraph *g[maxOrder+1];
    for (int n = 1; n <= maxOrder; n++)
    {
        g[n] = new TGraph();
        g[n]->SetLineWidth(2);
        g[n]->SetLineColor(n+1);
    }

    for (int i = 0; i < nPoints; i++)
    {
        double x = -L + (2*L) * i/(nPoints-1);

        double partialSum[maxOrder + 1];
        for (int n = 1; n <= maxOrder; n++)
            partialSum[n] = a0;
        
        for (int n = 1; n <= maxOrder; n++)
        {
            for (int k = 1; k <= n; k++)
            {
                partialSum[n] += a[k]*cos(k*TMath::Pi()*x/L) + b[k]*sin(k*TMath::Pi()*x/L);
            }
            g[n]->SetPoint(i, x, partialSum[n]);
        }
    }

    f->SetTitle("Fourier series of x^{2};x;f(x)");

    f->Draw();

    for (int n = 1; n <= maxOrder; n++) g[n]->Draw("L SAME");

    // Legend
    TLegend *leg = new TLegend(0.7,0.5,0.95,0.9);
    leg->AddEntry(f,"f(x)=x^{2}","l");
    for (int n = 1; n <= maxOrder; n++) {
        TString label = Form("N = %d", n);
        leg->AddEntry(g[n], label, "l");
    }
    leg->Draw();

    //canvas->Print("fourier.gif]");
}