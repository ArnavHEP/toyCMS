#include "TFile.h"
#include "TTree.h"
#include <vector>
#include <iostream>

//plotting energy histrogram using hits
void hitEnergy() 
{    
    TCanvas *c1 = new TCanvas();
    double ecalEnergyRange = 10; //in MeV
    TH1F* histEnergyEcal = new TH1F("ECAL","", 100, 0, ecalEnergyRange);

    TCanvas *c2 = new TCanvas();
    double hcalEnergyRange = 10; //in MeV
    TH1F* histEnergyHcal = new TH1F("HCAL","", 100, 0, hcalEnergyRange);

    int EcalEventID, HcalLayerNo, HcalEventID;
    double EcalX, EcalY, EcalZ, EcalTime, EcalEnergyDep, HcalTime, HcalEnergyDep;

    TFile* file = new TFile("output.root");

    TTree* treeECAL = dynamic_cast<TTree*>(file->Get("ECAL"));
    treeECAL->SetBranchAddress("x", &EcalX);
    treeECAL->SetBranchAddress("y", &EcalY);
    treeECAL->SetBranchAddress("z", &EcalZ);
    treeECAL->SetBranchAddress("Time", &EcalTime);
    treeECAL->SetBranchAddress("EnergyDep", &EcalEnergyDep);
    treeECAL->SetBranchAddress("EventID", &EcalEventID);

    TTree* treeHCAL = dynamic_cast<TTree*>(file->Get("HCAL"));
    treeHCAL->SetBranchAddress("LayerNo", &HcalLayerNo);
    treeHCAL->SetBranchAddress("Time", &HcalTime);
    treeHCAL->SetBranchAddress("EnergyDep", &HcalEnergyDep);
    treeHCAL->SetBranchAddress("EventID", &HcalEventID);
   
    Long64_t nEntriesECAL = treeECAL->GetEntries();
    for (size_t i = 0; i < nEntriesECAL; ++i)
    {
        treeECAL->GetEntry(i);
        if (EcalTime<20) //time cut (in ns)
        {
            histEnergyEcal->Fill(EcalEnergyDep);
        }        
        
    }

    Long64_t nEntriesHCAL = treeHCAL->GetEntries();
    for (size_t i = 0; i < nEntriesHCAL; ++i)
    {
        treeHCAL->GetEntry(i);
        if (HcalTime<20) //time cut (in ns)
        {
            histEnergyHcal->Fill(HcalEnergyDep);
        }
    }

    c1->SetTickx();
    c1->SetTicky();
    c1->SetGridx();
    c1->SetGridy();
    histEnergyEcal->GetXaxis()->SetTitle("Energy Deposited (MeV)");
    histEnergyEcal->GetYaxis()->SetTitle("Hits");
    histEnergyEcal->SetFillColor(kGreen-9);
    c1->cd();
    histEnergyEcal->Draw();
    c1->Update();

    c2->SetTickx();
    c2->SetTicky();
    c2->SetGridx();
    c2->SetGridy();
    histEnergyHcal->GetXaxis()->SetTitle("Energy Deposited (MeV)");
    histEnergyHcal->GetYaxis()->SetTitle("Hits");
    histEnergyHcal->SetFillColor(kGreen-9);
    c2->cd();
    histEnergyHcal->Draw();
    c2->Update();

    file->Close();
}
