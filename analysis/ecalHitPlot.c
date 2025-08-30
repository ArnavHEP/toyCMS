#include "TFile.h"
#include "TTree.h"
#include <vector>
#include <iostream>

//For plotting ecal hits in a x-y scatter plot
void ecalHitPlot() 
{
    int ecalRingCrystals = 90; 
    int ecalRowCrystals = 80;
    int EcalEventID, EcalCrystalNo;
    double EcalX, EcalY, EcalZ, EcalTime, EcalEnergyDep;

    TCanvas *can = new TCanvas();
	TH2F* dt = new TH2F("","", ecalRowCrystals, 0, ecalRowCrystals, ecalRingCrystals, 0, ecalRingCrystals);

    TFile* file = new TFile("output.root");
    TTree* treeECAL = dynamic_cast<TTree*>(file->Get("ECAL"));
    treeECAL->SetBranchAddress("CrystalNo", &EcalCrystalNo);
    treeECAL->SetBranchAddress("x", &EcalX);
    treeECAL->SetBranchAddress("y", &EcalY);
    treeECAL->SetBranchAddress("z", &EcalZ);
    treeECAL->SetBranchAddress("Time", &EcalTime);
    treeECAL->SetBranchAddress("EnergyDep", &EcalEnergyDep);
    treeECAL->SetBranchAddress("EventID", &EcalEventID);
    
    Long64_t nEntriesECAL = treeECAL->GetEntries();
    for (size_t i = 0; i < nEntriesECAL; ++i)
    {
        treeECAL->GetEntry(i);
        //solving the cellID
        int x = EcalCrystalNo/100;
        int y = EcalCrystalNo%100;
        dt->Fill(x,y);        
    }

    can->SetTickx();
	can->SetTicky();
	can->SetGridx();
	can->SetGridy();
 
    dt->SetTitle("ECAL");
    dt->GetXaxis()->SetTitle("theta");
    dt->GetYaxis()->SetTitle("phi");

    dt->Draw("colz");
    file->Close();
}
