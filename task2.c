#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <TMath.h>
#include <TH1F.h>
#include <TF1.h>
#include <TCanvas.h>
#include "TString.h"


using namespace std;

TF1 *polynom(int deg, double N){
    TF1 *polynom5 = new TF1("","[0]+[1]*(x/100.)+[2]*(x/100.)**2+[3]*(x/100.)**3+[4]*(x/100.)**4+[5]*(x/100.)**5", -100, 100);
    TF1 *polynom4 = new TF1("","[0]+[1]*(x/100.)+[2]*(x/100.)**2+[3]*(x/100.)**3+[4]*(x/100.)**4", -100, 100);
    TF1 *polynom3 = new TF1("","[0]+[1]*(x/100.)+[2]*(x/100.)**2+[3]*(x/100.)**3", -100, 100);
    TF1 *polynom2 = new TF1("","[0]+[1]*(x/100.)+[2]*(x/100.)**2", -100, 100);
    TF1 *polynom1 = new TF1("","[0]+[1]*(x/100.)", -100, 100);
    TF1 *polynom0 = new TF1("","[0]", -100, 100);
    polynom5->SetParameters(N/40., 0, 0, 0, 0, 0);
    polynom4->SetParameters(N/40., 0, 0, 0, 0);
    polynom3->SetParameters(N/40., 0, 0, 0);
    polynom2->SetParameters(N/40., 0, 0);
    polynom1->SetParameters(N/40., 0);
    polynom0->SetParameters(N/40.);
    if (deg == 0) return polynom0; 
    if (deg == 1) return polynom1; 
    if (deg == 2) return polynom2; 
    if (deg == 3) return polynom3; 
    if (deg == 4) return polynom4;
    if (deg == 5) return polynom5;  
}

void t2_2(){
    TCanvas *s = new TCanvas();
    TH1F *hist = new TH1F("hist", "task2", 40, -100, 100);
    TF1 *func = new TF1("func","[0]+[1]*(x/100.)+[2]*(x/100.)**2+[3]*(x/100.)**3+[4]*(x/100.)**4",-100,100);
    func->SetParameters(10,-6,3,7,-3);

    for (int j=3; j<=5; j++){

        int N = pow(10,j);
        hist->FillRandom("func", N);
        hist->Draw();
        double lnLsum_prev = 1000000;
        int deg;
        for (deg = 1; deg<=5; deg++){ 
            TF1 *f = polynom(deg, N);
            hist->Fit(f,"LQ","same",-100, 100);
            double lnLsum = hist->Chisquare(f, "L");
            if ((lnLsum_prev-lnLsum) < 3.84) break;
            lnLsum_prev = lnLsum;
        }
        cout <<"N = "<< N <<" min degree: " << deg-1 << endl;
        s->Draw();
        //s->SaveAs("task2.png");
    }

}
