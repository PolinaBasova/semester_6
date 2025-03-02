#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <TMath.h>
#include <TH1D.h>
#include <TF1.h>
#include <TCanvas.h>

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
        if (Dev > sqrt(50)) StDev1+=1;// 500*0.32 = 160  
        if (Dev > 2*sqrt(50)) StDev2+=1; //500*0.05 = 25
        if (Dev > 3*sqrt(50)) StDev3+=1; //500*0.003 = 1.5
    }
    cout << StDev1 << "\n";
    cout << StDev2 << "\n";
    cout << StDev3 << "\n";
    s->SaveAs("task1.png");

    int N = 10;
    auto f1 = new TF1("f1","TMath::Gaus(x, [mean], [sigma], 1) ", 0, 20);
    f1->SetNpx(100000);
    f1->SetParameter("mean", N);
    f1->SetParameter("sigma",sqrt(N));
    auto f2 = new TF1("f2","TMath::Poisson(x, [mean]) ", 0, 20);
    f2->SetNpx(100000);
    f2->SetParameter("mean", N);
    f1 -> GetHistogram() -> Draw();
    f2 -> SetLineColor(kGreen);
    f2 -> GetHistogram() -> Draw("same");
    s-> SaveAs("task2.png");

    
    auto f3 = new TF1("f3","10*TMath::Binomial([n], x) * ([p])^x * (1-[p])^([n]-x) ", 0, 100);
    auto f4 = new TF1("f2","TMath::Poisson(x, [mean]) ", 0, 100);
    f3->SetNpx(100); f4->SetNpx(100);
    f3->SetParameter("n", 1000);
    f3->SetParameter("p", 0.01);
    f4->SetParameter("mean", 10);
    f3 -> GetHistogram() -> Draw();
    f4 -> SetLineColor(kGreen);
    f4 -> GetHistogram() -> Draw("same");
    s-> SaveAs("task3.png");

    N = 10;
    double norm = TMath::Gamma(N/2)*TMath::Power(2.,N/2);
    auto f5 = new TF1("f5","pow(x,[N]/2-1)*exp(-0.5*x)/[norm]", 0, 100);
    f5->SetParameter("N", N);
    f5->SetParameter("norm", norm);
    auto f6 = new TF1("f6","TMath::Gaus(x, [mean], [sigma], 1)", 0, 100);
    f6->SetParameter("mean", N);
    f6->SetParameter("sigma",sqrt(2*N));
    f6 -> GetHistogram() -> Draw();
    f5 -> SetLineColor(kGreen);
    f5 -> GetHistogram() -> Draw("same");
    s-> SaveAs("task4.png");

}
