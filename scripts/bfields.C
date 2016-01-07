//
//  
//
//  Created by Paul Schütze
//
//

#include "TCanvas.h"
#include "TROOT.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TLegend.h"
#include "TFile.h"
#include "TH1D.h"
#include "TSystem.h"
#include "TRandom.h"
#include "TString.h"

#include <cstdlib>
#include <fstream>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;


int bfields(const char* runlistinput, const char* bdirinput){
    
    cout << "Wohoo -.- Ganz grosser Sport" << endl;

    TString runlistname;
    runlistname += gSystem->pwd();
    if( !runlistname.EndsWith("/") ) runlistname += "/";
    runlistname += runlistinput;

    cout << "Your runlist is at " << runlistname << endl;

    // Find the right folder.
    TString foldername;
    foldername += runlistname;

    foldername.Remove(foldername.Last('/')+1, foldername.Length()-foldername.Last('/')-1);

    // Some Parameters

    double bfield;
    enum direction {x,y};
    direction bdir;

    if(strcmp(bdirinput,"x")){
        bdir = x;
    }else if(strcmp(bdirinput,"y")){
        bdir = y;
    }else{
        cout << "Usage: bfields(runlist, Bdirection(x,y))" << endl;
        cout << "You did: bfields(" << runlistinput << ", " << bdirinput <<")" << endl;
        return 0;
    }




    ifstream runlist;
    runlist.open(runlistname);

    vector<double> bfieldvaluesX;
    vector<double> bfieldvaluesY;
    vector<int> runnrvalues;
    string str;
    double strval;
    string line;

    int counter=0;

    if(bdir)
    int colBfields = 5;

    while (!runlist.eof()) {

//        runlist >> str;
        getline(runlist, line);

        //cout << line << endl;

        counter=0;

        while(line.length()>0){

            stringstream linestream(line);
            linestream >> str;

            line.erase(0,str.length()+1);

//            cout << str << endl;

            if(counter==4){
                try{
                    bfieldvaluesX.push_back(stod(str, NULL));
                }catch(std::exception& e)
                {
//                    cout << "Could not convert string to double: " << str << endl;
                }
//                if(bfieldvalues.size()>0)cout << "Bfield is " << bfieldvalues.at(bfieldvalues.size()-1) << endl;
            }else if(counter==5){
                try{
                    bfieldvaluesY.push_back(stod(str, NULL));
                }catch(std::exception& e)
                {
//                    cout << "Could not convert string to double: " << str << endl;
                }
            }else if(counter==0){
                try{
                    runnrvalues.push_back(stoi(str, NULL));
                }catch(std::exception& e)
                {
//                    cout << "Could not convert string to int: " << str << endl;
                }
            }
            //cout << counter << ". " << str << endl;

            counter++;
        }

    }

    runlist.close();
    

    // Now go through the runfiles.

    unsigned int nruns;
    nruns = runnrvalues.size();

    int runnr;

    cout << "Found " << nruns << " runs. Reading them..." << endl;


    // Create Histograms and plots here




    for(unsigned int i=0; i<nruns; i++){

        runnr = runnrvalues.at(i);

        TString filename;
        filename+=foldername;
        char buffer[100];
        sprintf(buffer, "pixelav-r%04i.out.root", runnr);

        filename+=buffer;

        TFile *source = new TFile(filename);


        // Open Histograms from Evrd here and fill values to your histos


        TH1D* hncol = (TH1D*)gDirectory->Get("hncol");
        hncol->SetName("hncol");


        TH1D* hnrow = (TH1D*)gDirectory->Get("hnrow");
        hnrow->SetName("hnrow");




    }
    
//    TCanvas* can = new TCanvas("Momentum vs. current", "Momentum vs. current", 800,600);
//    GcurrmomMeas->SetTitle("Momentum vs. current");
//    GcurrmomMeas->GetXaxis()->SetTitle("Current [A]");
//    GcurrmomMeas->GetYaxis()->SetRangeUser(0,6.6);
//    GcurrmomMeas->GetYaxis()->SetTitle("Momentum [GeV]");
//    GcurrmomMeas->SetMarkerStyle(5);
//    GcurrmomMeas->SetMarkerColor(kBlue);
//    GcurrmomTab->SetMarkerStyle(5);
//    GcurrmomTab->SetMarkerColor(kRed);
    
//    // Linear fit:
//    TF1* linfit = new TF1("Linear Fit","[0]+[1]*x",0,200);
//    linfit->SetLineColor(kBlack);
//    linfit->SetLineWidth(1);
//    GcurrmomMeas->Fit(linfit);
    
    
//    //Legend:
//    TLegend* leg = new TLegend(0.13,0.78,0.43,0.93);
//    //leg->SetBorderSize(0);
//    //leg->SetTextSize(0.07);
//    //leg->SetFillColor(10);
//    //leg->SetLineColor(1);
//    leg->AddEntry(GcurrmomMeas,"Measurement","pe");
//    leg->AddEntry(GcurrmomTab,"Table at TB21","p");
//    leg->AddEntry(linfit,"Linear Fit to measurement","l");
    
    
//    GcurrmomMeas->DrawClone("APE");
//    GcurrmomTab->DrawClone("SameP");
//    leg->DrawClone("Same");
    
    
//    //linfit->DrawClone("Same");
    
//    can->SaveAs("MomCurr.pdf");
//    can->Close();
    
//    resultcalc(val0, val1, val2, val3, val4, val5, GcurrmomTab);
    
//    //deflection(p,I,thetaout, xout, thetain, xin, dx);
    
    
    
    return 0;
        
}
