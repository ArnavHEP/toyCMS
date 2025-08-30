#include "TFile.h"
#include "TTree.h"
#include <vector>
#include <iostream>

// For reconstructing energy of ecal hits
void ecalEnergy() 
{
    int EcalEventID;
    double EcalX, EcalY, EcalZ, EcalTime, EcalEnergyDep;

    //Finding energy scales

    TFile* file1 = new TFile("calibration_beam_10gev_500events.root");
    int evt1 = 500; 
    double beamEnergy = 10;
    
    TTree* treeECAL1 = dynamic_cast<TTree*>(file1->Get("ECAL"));
    treeECAL1->SetBranchAddress("x", &EcalX);
    treeECAL1->SetBranchAddress("y", &EcalY);
    treeECAL1->SetBranchAddress("z", &EcalZ);
    treeECAL1->SetBranchAddress("Time", &EcalTime);
    treeECAL1->SetBranchAddress("EnergyDep", &EcalEnergyDep);
    treeECAL1->SetBranchAddress("EventID", &EcalEventID);

    double TotalEnergy = 0;
    Long64_t nEntries1 = treeECAL1->GetEntries();
	for (Long64_t j = 0; j < nEntries1; ++j)  
	{
	    treeECAL1->GetEntry(j);
        TotalEnergy += EcalEnergyDep;
	}

    double EnergyScale = 0;
    EnergyScale = beamEnergy/(TotalEnergy/evt1);
    cout << "Energy Scale : " << EnergyScale << endl;

    file1->Close();


    //ECAL run to measure 

    int evt2 = 500; 
    TFile* file2 = new TFile("gamma_500events.root");

    TTree* treeECAL2 = dynamic_cast<TTree*>(file2->Get("ECAL"));
    treeECAL2->SetBranchAddress("x", &EcalX);
    treeECAL2->SetBranchAddress("y", &EcalY);
    treeECAL2->SetBranchAddress("z", &EcalZ);
    treeECAL2->SetBranchAddress("Time", &EcalTime);
    treeECAL2->SetBranchAddress("EnergyDep", &EcalEnergyDep);
    treeECAL2->SetBranchAddress("EventID", &EcalEventID);

    double e[evt2];
    Int_t totalE;

    for(Int_t i = 0; i < evt2; i++)
    {
        e[i] = 0;
    }

    Long64_t nEntries2 = treeECAL2->GetEntries(); 
	for (Long64_t j = 0; j < nEntries2; ++j)  
	{
	    treeECAL2->GetEntry(j);
        e[EcalEventID-1] += EnergyScale*EcalEnergyDep;
        totalE += (EnergyScale*EcalEnergyDep)/evt2;
	}

    file2->Close();


    //plotting histograms

    int bins = 100;
    int events = 500;

    TH1F* oldHist = (TH1F*)gROOT->FindObject("Energy");
    if (oldHist) delete oldHist;

    TCanvas *ce = new TCanvas();
    TH1F* Energy_GeV = new TH1F("Energy","", bins, 0, totalE/500);

    for(Int_t i = 0; i < events; i++)
    {
       Energy_GeV->Fill(e[i]);
    }

    cout << "Reconstructed Energy : " << Energy_GeV->GetMean() << " GeV" << endl << endl;
    
    ce->SetTickx();
	ce->SetTicky();
	ce->SetGridx();
	ce->SetGridy();
	Energy_GeV->SetFillColor(kGreen-9);
    Energy_GeV->GetXaxis()->SetTitle("Energy");
    Energy_GeV->GetYaxis()->SetTitle("Events");
    Energy_GeV->Draw();
}

