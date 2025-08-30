#include "TFile.h"
#include "TTree.h"
#include <vector>
#include <iostream>

//plotting time histrogram using hits
void hitTime() 
{    
    TCanvas *c1 = new TCanvas();
    double ecalTimeRange = 20; //in ns
    TH1F* histTimeEcal = new TH1F("ECAL","", 100, 0, ecalTimeRange);

    TCanvas *c2 = new TCanvas();
    double hcalTimeRange = 20; //in ns
    TH1F* histTimeHcal = new TH1F("HCAL","", 100, 0, ecalTimeRange);

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
        histTimeEcal->Fill(EcalTime);
    }

    Long64_t nEntriesHCAL = treeHCAL->GetEntries();
    for (size_t i = 0; i < nEntriesHCAL; ++i)
    {
        treeHCAL->GetEntry(i);
        histTimeHcal->Fill(HcalTime);
    }

    c1->SetTickx();
    c1->SetTicky();
    c1->SetGridx();
    c1->SetGridy();
    histTimeEcal->GetXaxis()->SetTitle("Time (ns)");
    histTimeEcal->GetYaxis()->SetTitle("Hits");
    c1->cd();
    histTimeEcal->Draw();
    c1->Update();

    c2->SetTickx();
    c2->SetTicky();
    c2->SetGridx();
    c2->SetGridy();
    histTimeHcal->GetXaxis()->SetTitle("Time (ns)");
    histTimeHcal->GetYaxis()->SetTitle("Hits");
    c2->cd();
    histTimeHcal->Draw();
    c2->Update();

    file->Close();
}
