#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <TMath.h>
#include <TH1D.h>
#include <TF1.h>
#include <TCanvas.h>
#include "TGraph.h"

using namespace std;

void t1(){
    TCanvas *s = new TCanvas();
    TH1D *graph = new TH1D("graph", "graph", 500, -1, 1);
    graph->FillRandom("pol0",25000);
    graph->Draw();
    int StDev1 = 0; int StDev2 = 0; int StDev3 = 0;
    double Dev = 0;
    for (int i = 1; i<=100; i++){
        //deviation from the mean = 25000/500 for uniform distribution
        Dev = fabs(graph->GetBinContent(i) - 50); 
        //for gauss sigma=sqrt(mean)
        if (Dev > sqrt(50)) StDev1+=1;// 100*0.32  
        if (Dev > 2*sqrt(50)) StDev2+=1; //100*0.05 
        if (Dev > 3*sqrt(50)) StDev3+=1; //100*0.003 
    }
    cout << StDev1 << "\n";
    cout << StDev2 << "\n";
    cout << StDev3 << "\n";
    s->SaveAs("Task1.png");

    int N = 10;
    auto Gaus1 = new TF1("Gaus1","TMath::Gaus(x, [mean], [sigma], 1) ", 0, 200);
    Gaus1->SetNpx(100000);
    Gaus1->SetParameter("mean", N);
    Gaus1->SetParameter("sigma",sqrt(N));
    auto Poisson1 = new TF1("Poisson1","TMath::Poisson(x, [mean]) ", 0, 200);
    Poisson1->SetNpx(100000);
    Poisson1->SetParameter("mean", N);
    Gaus1 -> GetHistogram() -> Draw();
    Poisson1 -> SetLineColor(kGreen);
    Poisson1 -> GetHistogram() -> Draw("same");
    s-> SaveAs("Task1Gauss&&Poisson.png");

    N = 100;
    auto Binom2 = new TF1("Binom2","ROOT::Math::binomial_pdf( x, [p], [n])", 0, 100);
    auto Poisson2 = new TF1("Poisson2","TMath::Poisson(x, [mean]) ", 0, 100);
    Binom2->SetNpx(100); Poisson2->SetNpx(100);
    Binom2->SetParameter("n", 1000);
    Binom2->SetParameter("p", 0.01);
    Poisson2->SetParameter("mean", 10);
    Binom2 -> GetHistogram() -> Draw();
    Poisson2 -> SetLineColor(kGreen);
    Poisson2 -> GetHistogram() -> Draw("same");
    s-> SaveAs("Task1Binom&&Poisson.png");

    N = 50;
    auto ChiSq3 = new TF1("ChiSq3","ROOT::Math::chisquared_pdf(x,[N])", 0, 200);
    ChiSq3->SetParameter("N", N);
    auto Gaus3 = new TF1("Gaus3","TMath::Gaus(x, [mean], [sigma], 1)", 0, 200);
    Gaus3->SetParameter("mean", N);
    Gaus3->SetParameter("sigma",sqrt(2*N));
    Gaus3 -> GetHistogram() -> Draw();
    ChiSq3 -> SetLineColor(kGreen);
    ChiSq3 -> GetHistogram() -> Draw("same");
    s-> SaveAs("Task1Chisq&&Gaus.png");

}
