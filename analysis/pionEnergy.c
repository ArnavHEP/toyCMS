#include "TFile.h"
#include "TTree.h"
#include <vector>
#include <iostream>

//uses both ECAL and HCAL to reconstruct energy
void pionEnergy() 
{
    Int_t EcalEventID, HcalEventID, HcalLayerNo;
    double EcalX, EcalY, EcalZ, EcalTime, EcalEnergyDep, HcalTime, HcalEnergyDep;

    //Finding energy scale of ECAL

    TFile* file1 = new TFile("ECAL_calibration_beam_10gev_500events.root");
    int evt1 = 500; 
    double beamEnergy1 = 10;
    
    TTree* treeECAL1 = dynamic_cast<TTree*>(file1->Get("ECAL"));
    treeECAL1->SetBranchAddress("x", &EcalX);
    treeECAL1->SetBranchAddress("y", &EcalY);
    treeECAL1->SetBranchAddress("z", &EcalZ);
    treeECAL1->SetBranchAddress("Time", &EcalTime);
    treeECAL1->SetBranchAddress("EnergyDep", &EcalEnergyDep);
    treeECAL1->SetBranchAddress("EventID", &EcalEventID);

    double TotalEnergyECAL = 0;
    Long64_t nEntries1 = treeECAL1->GetEntries();
	for (Long64_t j = 0; j < nEntries1; ++j)  
	{
	    treeECAL1->GetEntry(j);
        TotalEnergyECAL += EcalEnergyDep;
	}

    double EnergyScaleECAL = 0;
    EnergyScaleECAL = beamEnergy1/(TotalEnergyECAL/evt1);
    cout << "Energy Scale for ECAL : " << EnergyScaleECAL << endl;

    file1->Close();


    //Finding energy scale of HCAL

    int evt2 = 500; 
    double beamEnergy2 = 10;
    TFile* file2 = new TFile("HCAL_calibration_beam_10gev_500events.root");
    TTree* treeHCAL1 = dynamic_cast<TTree*>(file2->Get("HCAL"));

    treeHCAL1->SetBranchAddress("LayerNo", &HcalLayerNo);
    treeHCAL1->SetBranchAddress("Time", &HcalTime);
    treeHCAL1->SetBranchAddress("EnergyDep", &HcalEnergyDep);
    treeHCAL1->SetBranchAddress("EventID", &HcalEventID);

    double TotalEnergyHCAL = 0;
    Long64_t nEntries2 = treeHCAL1->GetEntries();
	for (Long64_t j = 0; j < nEntries2; ++j)  
	{
	    treeHCAL1->GetEntry(j);
        TotalEnergyHCAL += HcalEnergyDep;
	}

    double EnergyScaleHCAL = 0;
    EnergyScaleHCAL = beamEnergy2/(TotalEnergyHCAL/evt2);
    cout << "Energy Scale for HCAL : " << EnergyScaleHCAL << endl;

    file2->Close();


    //Pion Run to measure 

    int evt3 = 500;
    TFile* file3 = new TFile("pion_500events.root");
    
    TTree* treeECAL2 = dynamic_cast<TTree*>(file3->Get("ECAL"));
    treeECAL2->SetBranchAddress("x", &EcalX);
    treeECAL2->SetBranchAddress("y", &EcalY);
    treeECAL2->SetBranchAddress("z", &EcalZ);
    treeECAL2->SetBranchAddress("Time", &EcalTime);
    treeECAL2->SetBranchAddress("EnergyDep", &EcalEnergyDep);
    treeECAL2->SetBranchAddress("EventID", &EcalEventID);

    TTree* treeHCAL2 = dynamic_cast<TTree*>(file3->Get("HCAL"));
    treeHCAL2->SetBranchAddress("LayerNo", &HcalLayerNo);
    treeHCAL2->SetBranchAddress("Time", &HcalTime);
    treeHCAL2->SetBranchAddress("EnergyDep", &HcalEnergyDep);
    treeHCAL2->SetBranchAddress("EventID", &HcalEventID);

    double e[evt3], h[evt3];
    Int_t totalE, totalH;

    for(Int_t i = 0; i < evt3; i++)
    {
        e[i] = 0;
        h[i] = 0;
    }

    Long64_t nEntries3 = treeECAL2->GetEntries(); 
	for (Long64_t j = 0; j < nEntries3; ++j)  
	{
	    treeECAL2->GetEntry(j);
        e[EcalEventID-1] += EnergyScaleECAL*EcalEnergyDep;
        totalE += (EnergyScaleECAL*EcalEnergyDep)/evt3;
	}

    Long64_t nEntries4 = treeHCAL2->GetEntries();
	for (Long64_t j = 0; j < nEntries4; ++j)  
	{
        treeHCAL2->GetEntry(j);
        h[HcalEventID-1] += EnergyScaleHCAL*HcalEnergyDep;
        totalH += (EnergyScaleHCAL*HcalEnergyDep)/evt3;
	}

    file3->Close();


    //plotting histograms

    int bins = 100;
    int events = 500;

    TH1F* oldHist1 = (TH1F*)gROOT->FindObject("ECAL_Energy");
    if (oldHist1) delete oldHist1;
    TH1F* oldHist2 = (TH1F*)gROOT->FindObject("HCAL_Energy");
    if (oldHist2) delete oldHist2;

    TCanvas *ECAL_Canvas = new TCanvas();
    TH1F* ECAL_Energy = new TH1F("ECAL_Energy","", bins, 0, totalE/50);
    for(Int_t i = 0; i < events; i++)
    {
       ECAL_Energy->Fill(e[i]);
    }

    ECAL_Canvas->SetTickx();
	ECAL_Canvas->SetTicky();
	ECAL_Canvas->SetGridx();
	ECAL_Canvas->SetGridy();
	ECAL_Energy->SetFillColor(kGreen-9);
    ECAL_Energy->GetXaxis()->SetTitle("Energy");
    ECAL_Energy->GetYaxis()->SetTitle("Events");
    ECAL_Energy->Draw();


    TCanvas *HCAL_Canvas = new TCanvas();
    TH1F* HCAL_Energy = new TH1F("HCAL_Energy","", bins, 0, totalE/50);
    for(Int_t i = 0; i < events; i++)
    {
       HCAL_Energy->Fill(h[i]);
    }

    HCAL_Canvas->SetTickx();
	HCAL_Canvas->SetTicky();
	HCAL_Canvas->SetGridx();
	HCAL_Canvas->SetGridy();
	HCAL_Energy->SetFillColor(kGreen-9);
    HCAL_Energy->GetXaxis()->SetTitle("Energy");
    HCAL_Energy->GetYaxis()->SetTitle("Events");
    HCAL_Energy->Draw();

    cout << "Reconstructed Energy : " << ECAL_Energy->GetMean() + HCAL_Energy->GetMean() << " GeV" << endl << endl;
}

