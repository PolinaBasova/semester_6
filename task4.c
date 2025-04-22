#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <TMath.h>
#include <TH1F.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TStyle.h>


using namespace std;

void t4(){
    TCanvas *c1 = new TCanvas();
    c1->Divide(2,3);
    c1->cd(1);
    TH1F * h = new TH1F("h","",100,-2, 2);
    TF1 *data = new TF1("data","TMath::Gaus(x, 0, 1, 1) ", -2, 2);
    h->FillRandom("data", 100);
    h->Draw();
    TF1 * func = new TF1("func","pol2",-2,2);
    TFitResultPtr r;
    r = h->Fit("func","LS","ep");
    cout<<"p= "<<r->Prob()<<"  chi2= "<<r->Chi2()<<"  ndf= "<<r->Ndf()<<endl;

    c1->cd(2); 
    TF1 * fchi2 = new TF1("fchi2","30000*ROOT::Math::chisquared_pdf(x,97)",0,300);
    TH1F * hchi2 = new TH1F("hchi2","",100, 0, 300);
    TLine line;
    for(int i=0;i<10000;i++){     
        h->Reset();
        h->FillRandom("data",100);
        r = h->Fit("func","LSQN");
        hchi2->Fill(r->Chi2());
    }
    fchi2->Draw();
    hchi2->Draw("same");
    line.DrawLine(TMath::ChisquareQuantile(0.95,97),0,TMath::ChisquareQuantile(0.95,97),800);
    cout<<"chi2_max = "<<TMath::ChisquareQuantile(0.95,97)<<endl;
    double fcn;
    fcn = r->MinFcnValue();

    c1->cd(3);

    TH1F * hfcn_true = new TH1F("hfcn_true","",100,0,150);
    TH1F * hfcn_false = new TH1F("hfcn_false","",100,0,150);
    int nfcn; int j;
    for(int i=0;i<10000;i++){
        h->Reset();
        h->FillRandom("data",gRandom->Poisson(100));
        r = h->Fit("func","LSQN");
        hfcn_false->Fill(r->MinFcnValue());
    }
    nfcn = 0; 
    for(int i=0;i<10000;i++){
        h->Reset();
        h->FillRandom("data",gRandom->Poisson(100));
        r = h->Fit("func","LSQN");
        hfcn_true->Fill(r->MinFcnValue());
        if(r->MinFcnValue()>fcn) nfcn++;
    }

    for(j=50;j>0;j--){
        if(hfcn_true->Integral(j,100) >500) break;
    }

    hfcn_false->SetLineColor(kRed);
    hfcn_true->Draw();
    hfcn_false->Draw("same");
    
    cout<<"p= "<<nfcn/10000.<<"  fcn= "<<fcn<<" fcn_max= "<<hfcn_true->GetBinCenter(j)<< " p_false= "<<hfcn_false->Integral(1,j)/10000.<<endl;

    c1->cd(4);

    TH1F *htest_true = new TH1F("htest_true","",100,0,1);
    TH1F *htest_false = new TH1F("htest_false","",100,0,1);
    TH1F *h4 = new TH1F("h4","",100,-2,2);
    h4->FillRandom("func",100000);
    double p;

    for(int i=0;i<10000;i++){
        h->Reset();
        h->FillRandom("data",100);
        p = h->KolmogorovTest(h4);
        htest_true->Fill(p);
    }
    for(int i=0;i<10000;i++){
        h->Reset();
        h->FillRandom("func",100);
        p = h->KolmogorovTest(h4);
        htest_false->Fill(p);
    }
    htest_false->SetLineColor(kRed);
    htest_false->Draw();
    htest_true->Draw("same");
    cout<< "p_false = "<<htest_false->Integral(6,100)/10000.<<endl;

    c1->cd(5);

    htest_false->Reset();
    htest_true->Reset();
    for(int i=0;i<10000;i++){
        h->Reset();
        h->FillRandom("data",100);
        p = h->AndersonDarlingTest(h4);
        htest_true->Fill(p);
    }
    for(int i=0;i<10000;i++){
        h->Reset();
        h->FillRandom("func",100);
        p = h->AndersonDarlingTest(h4);
        htest_false->Fill(p);
    }
    htest_false->SetLineColor(kRed);
    htest_false->Draw();
    htest_true->Draw("same");
    cout<< "p_false= "<<htest_false->Integral(6,100)/10000.<<endl;

    c1->Draw();

}
