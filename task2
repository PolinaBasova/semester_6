#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <TMath.h>
#include <TH1D.h>
#include <TF1.h>
#include <TCanvas.h>
#include "TString.h"

using namespace std;

double lnL(double n, double mu){
    return 2*( mu - n + n*log(n/mu) ); 
}

void t2(){
    TCanvas *s = new TCanvas();
    TH1D *hist = new TH1D("hist", "hist", 40, -100, 100);
    TF1 *func = new TF1("func","[0]+[1]*(x/100.)+[2]*(x/100.)**2+[3]*(x/100.)**3+[4]*(x/100.)**4",-100,100);
    func->SetParameters(10,-6,3,7,-3);

    for (int j=3; j<=5; j++){

        int N = pow(10,j);
        hist->FillRandom("func", N);
        hist->Draw();
        //points in the middle of bins 200/40 = 5 -> -102.5+5*bin_number
        double lnLsum_prev = 1000000;
        int deg;
        for (deg = 1; deg<=22; deg++){ 
        TF1 *polynom = new TF1("", Form("pol%d", deg), -100, 100);
        hist->Fit( polynom,"SQ","same",-100, 100 );
        //if i use "L" in options max deg = 5, then Warning in <Fit>: Abnormal termination of minimization.
        //if i use "S" max deg = 22, but there is default chi-square method 
        //so i need to write: 
        double lnLsum = 0.;
        for (int i = 1; i<=40; i++){
            lnLsum += lnL(hist->GetBinContent(i), polynom->Eval(-102.5+5*i));
        }
        //cout << fabs(lnLsum-lnLsum_prev) << "\n";
        if ((lnLsum_prev-lnLsum) < 3.84) break;
        lnLsum_prev = lnLsum;
        }
        cout <<"N = "<< N <<" min degree: " << deg-1 << endl;
        s->Draw();
    }
}
