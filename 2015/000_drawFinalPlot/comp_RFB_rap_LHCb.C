#include "TFile.h"
#include <TROOT.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TH1.h>
#include <TH2.h>
#include <TLegend.h>
#include <TMath.h>
#include <TPaveText.h>
#include <TText.h>
#include <TLatex.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>

#include "KYOcommonOptFinal.h"
#include <TBox.h>
//#include <vector>
//#include <list>
//#include <algorithm>
//#include <stdlib.h>

using namespace std;

void formRapArr(Double_t binmin, Double_t binmax, string* arr);
void formAbsRapArr(Double_t binmin, Double_t binmax, string* arr);
void formPtArr(Double_t binmin, Double_t binmax, string* arr);

int comp_RFB_rap_LHCb(Int_t runCode=0)
{
	gROOT->Macro("./JpsiStyleForFinalResult.C");

	// set info.
	const Double_t br = 0.0593 ;
	const Double_t brErr = 0.0006;
	Double_t lumi_nb;
	Double_t lumi_nb_err;
	Double_t lumi_mub;
	Double_t lumi_mub_err;
	string runstring;
	string lumistring;
	string cmsstring = "CMS preliminary";
	string beamstring = "pPb #sqrt{s_{NN}} = 5.02 TeV";
	if (runCode ==0) { runstring = "All"; lumi_nb =34.622; lumi_nb_err=1.2; }
	else if (runCode == 1) { runstring = "Pbp"; lumi_nb =20.7; lumi_nb_err=0.7; }//1stRun
	else if (runCode == 2) { runstring = "pPb"; lumi_nb = 14.0; lumi_nb_err=0.5; }//2ndRun
	lumistring = Form("L_{int} = %.1f nb^{-1}", lumi_nb);
	lumi_mub = lumi_nb * 1000; // (nb)^{-1} -> {#mub}^{-1}
	lumi_mub_err = lumi_nb_err * 1000; // (nb)^{-1} -> {#mub}^{-1}
	
	// read our RFB_rap graph
	TFile *inFile_pr = new TFile("RFB_8rap9pt2gev/RFB_rap_isPrompt1.root");
	TFile *inFile_np = new TFile("RFB_8rap9pt2gev/RFB_rap_isPrompt0.root");
	TGraphAsymmErrors* gRFB_pr_sys_lowpt = (TGraphAsymmErrors*)inFile_pr->Get("gRFB_sys_lowpt"); 	
	TGraphAsymmErrors* gRFB_pr_lowpt = (TGraphAsymmErrors*)inFile_pr->Get("gRFB_lowpt"); 	
	TGraphAsymmErrors* gRFB_pr_sys_highpt = (TGraphAsymmErrors*)inFile_pr->Get("gRFB_sys_highpt"); 	
	TGraphAsymmErrors* gRFB_pr_highpt = (TGraphAsymmErrors*)inFile_pr->Get("gRFB_highpt"); 	
	TGraphAsymmErrors* gRFB_np_sys_lowpt = (TGraphAsymmErrors*)inFile_np->Get("gRFB_sys_lowpt"); 	
	TGraphAsymmErrors* gRFB_np_lowpt = (TGraphAsymmErrors*)inFile_np->Get("gRFB_lowpt"); 	
	TGraphAsymmErrors* gRFB_np_sys_highpt = (TGraphAsymmErrors*)inFile_np->Get("gRFB_sys_highpt"); 	
	TGraphAsymmErrors* gRFB_np_highpt = (TGraphAsymmErrors*)inFile_np->Get("gRFB_highpt"); 	
	gRFB_pr_sys_lowpt->SetName("gRFB_pr_sys_lowpt");
	gRFB_pr_lowpt->SetName("gRFB_pr_lowpt");
	gRFB_pr_sys_highpt->SetName("gRFB_pr_sys_highpt");
	gRFB_pr_highpt->SetName("gRFB_pr_highpt");
	gRFB_np_sys_lowpt->SetName("gRFB_np_sys_lowpt");
	gRFB_np_lowpt->SetName("gRFB_np_lowpt");
	gRFB_np_sys_highpt->SetName("gRFB_np_sys_highpt");
	gRFB_np_highpt->SetName("gRFB_np_highpt");
	cout << "gRFB_pr_sys_lowpt = " << gRFB_pr_sys_lowpt << endl;
	cout << "gRFB_pr_lowpt = " << gRFB_pr_lowpt << endl;
	cout << "gRFB_pr_sys_highpt = " << gRFB_pr_sys_highpt << endl;
	cout << "gRFB_pr_highpt = " << gRFB_pr_highpt << endl;
	cout << "gRFB_np_sys_lowpt = " << gRFB_np_sys_lowpt << endl;
	cout << "gRFB_np_lowpt = " << gRFB_np_lowpt << endl;
	cout << "gRFB_np_sys_highpt = " << gRFB_np_sys_highpt << endl;
	cout << "gRFB_np_highpt = " << gRFB_np_highpt << endl;

	///////////////////////////////////////////////////
	///////////////////// LHCb ////////////////////////
	///////////////////////////////////////////////////
	Double_t lhcb_px[] = {2.75, 3.25, 3.75};
	//Double_t lhcb_px_binW[] = {0.25, 0.25, 0.25};
	Double_t lhcb_ex[] = {0., 0., 0.};
	Double_t lhcb_py_pr[] = {0.72, 0.62, 0.64};
	Double_t lhcb_py_np[] = {0.92, 0.84, 0.72};

	Double_t lhcb_ey_pr[] = { 0.05, 0.03, 0.04};
	Double_t lhcb_ey_np[] = {0.11, 0.08, 0.09};
	//Double_t lhcb_exsys[] = {0.04, 0.04, 0.04};
	Double_t lhcb_exsys[] = {0.03, 0.03, 0.03};
	Double_t lhcb_eysys_pr[] = {0.07, 0.04, 0.04};
	Double_t lhcb_eysys_np[] = {0.09, 0.08, 0.07};
	
	const Int_t nBin_lhcb = sizeof(lhcb_px)/sizeof(Double_t);
	cout << "nBin_lhcb : " << nBin_lhcb << endl; 
	///////////////////////////////////////////////////
	///////////////////// ALICE ////////////////////////
	///////////////////////////////////////////////////
	Double_t alice_px[] = {(2.96+3.15)/2, (3.15+3.34)/2, (3.34+3.53)/2};
	Double_t alice_ex[] = {0., 0., 0.};
	Double_t alice_py[] = {0.58, 0.6, 0.61};
	Double_t alice_ey[] = {0.03, 0.02, 0.03};
	//Double_t alice_exsys[] = {0.04, 0.04, 0.04};
	Double_t alice_exsys[] = {0.03, 0.03, 0.03};
	Double_t alice_eysys[] = {0.06, 0.05, 0.06};
	
	const Int_t nBin_alice = sizeof(alice_px)/sizeof(Double_t);
	cout << "nBin_alice : " << nBin_alice << endl; 

	////////////////////
	////// Draw Plots
	////////////////////

	//TLegend *legUR = new TLegend(0.52, 0.55, 0.85, 0.92); //upper left
	TLegend *legUR = new TLegend(0.52, 0.55, 0.86, 0.92); //upper left
	SetLegendStyle(legUR);
	TLegend *legUL = new TLegend(0.20, 0.73, 0.40, 0.92); //upper left
	SetLegendStyle(legUL);
	TLegend *legUM = new TLegend(0.40, 0.75, 0.58, 0.90); //upper middle
	SetLegendStyle(legUM);
//	TLegend *legBL = new TLegend(0.20, 0.20, 0.48, 0.37); //bottom left
	TLegend *legBL = new TLegend(0.18, 0.18, 0.48, 0.48); //bottom left
	SetLegendStyle(legBL);
	TLegend *legBM = new TLegend(0.40, 0.20, 0.58, 0.37); //bottom middle
	SetLegendStyle(legBM);
	TLegend *legMR = new TLegend(0.54, 0.34, 0.87, 0.57); //bottom left
	SetLegendStyle(legMR);

	TLatex* latex = new TLatex();
	latex->SetNDC();
	latex->SetTextAlign(12);
	latex->SetTextSize(0.04);

	TBox * globalbox = new TBox(0.5, 6.4, 1.5, 13.6);
	globalbox->SetFillColor(kYellow);

	/// LHCb /////
	TGraphAsymmErrors * gRFB_lhcb_pr_sys;
	TGraphAsymmErrors * gRFB_lhcb_pr;
	TGraphAsymmErrors * gRFB_lhcb_np_sys;
	TGraphAsymmErrors * gRFB_lhcb_np;
	TGraphAsymmErrors * gRFB_alice_sys;
	TGraphAsymmErrors * gRFB_alice;

	////////////////////////////////////////////////////////////////////////////////////
	// prompt
	TCanvas *c_pr = new TCanvas("c_pr","", 200, 10, 800, 600);
	c_pr->cd();
	gPad->SetLogy(0);
	// 1) lowpt
	gRFB_pr_sys_lowpt->SetTitle("");
	gRFB_pr_sys_lowpt->GetXaxis()->SetTitle("|y_{CM}|");
	gRFB_pr_sys_lowpt->GetXaxis()->CenterTitle();
	gRFB_pr_sys_lowpt->GetXaxis()->SetLimits(0.0,4.5);
	gRFB_pr_sys_lowpt->GetYaxis()->SetTitle("R_{FB}");
	gRFB_pr_sys_lowpt->SetMinimum(0.0);
	gRFB_pr_sys_lowpt->SetMaximum(1.4);
	gRFB_pr_sys_lowpt->SetFillColor(kRed-9);
	gRFB_pr_sys_lowpt->Draw("A2");
	
	// 2) highpt
	gRFB_pr_sys_highpt->SetFillColor(kTeal+7);
	gRFB_pr_sys_highpt->Draw("2");

	// 3) lhcb
	gRFB_lhcb_pr_sys = new TGraphAsymmErrors(nBin_lhcb, lhcb_px, lhcb_py_pr, lhcb_exsys, lhcb_exsys, lhcb_eysys_pr, lhcb_eysys_pr);	
	gRFB_lhcb_pr_sys->SetFillColor(kAzure-9);
	gRFB_lhcb_pr_sys->Draw("2");

	SetGraphStyle(gRFB_pr_lowpt,1,3);
	gRFB_pr_lowpt->Draw("P");
	
	SetGraphStyle(gRFB_pr_highpt,0,5);
	gRFB_pr_highpt->SetMarkerSize(1.7);
	gRFB_pr_highpt->Draw("P");

	gRFB_lhcb_pr = new TGraphAsymmErrors(nBin_lhcb, lhcb_px, lhcb_py_pr, lhcb_ex, lhcb_ex, lhcb_ey_pr, lhcb_ey_pr);	
	SetGraphStyle(gRFB_lhcb_pr,2,10);
	gRFB_lhcb_pr->Draw("P");

	// 3) alice
	gRFB_alice_sys = new TGraphAsymmErrors(nBin_alice, alice_px, alice_py, alice_exsys, alice_exsys, alice_eysys, alice_eysys);	
	gRFB_alice_sys->SetFillColor(kMagenta);
	gRFB_alice_sys->SetLineColor(kMagenta);
	gRFB_alice_sys->SetFillStyle(3002);
	gRFB_alice_sys->Draw("2");

	gRFB_alice = new TGraphAsymmErrors(nBin_alice, alice_px, alice_py, alice_ex, alice_ex, alice_ey, alice_ey);	
	SetGraphStyle(gRFB_alice,2,10);
	gRFB_alice->SetMarkerColor(kMagenta);
	gRFB_alice->SetMarkerStyle(25);
	gRFB_alice->Draw("P");

	dashedLine(0.0,1.0,4.5,1.0,1,1);

	legBL -> SetHeader("Prompt J/#psi");
	legBL -> AddEntry(gRFB_pr_lowpt,"CMS :6.5 < p_{T} < 10 [GeV/c]","lp");
	legBL -> AddEntry(gRFB_pr_highpt,"CMS :10 < p_{T} < 30 [GeV/c]","lp");
	legBL -> AddEntry(gRFB_lhcb_pr,"LHCb : 0 < p_{T} < 14 [GeV/c]","lp");
	legBL -> AddEntry(gRFB_alice,"ALICE : 0 < p_{T} < 15 [GeV/c] (Prompt + Non-prompt)","lp");
	legBL -> Draw();
	c_pr->Update();
	c_pr->SaveAs("comparisonLHCb/comp_RFB_rap_LHCb_pr.pdf");
	legBL->Clear();
	//c_pr->Clear();

	////////////////////////////////////////////////////////////////////////////////////
	// non-prompt
	TCanvas *c_np = new TCanvas("c_np","", 200, 10, 800, 600);
	c_np->cd();
	gPad->SetLogy(0);
	// 1) lowpt
	gRFB_np_sys_lowpt->SetTitle("");
	gRFB_np_sys_lowpt->GetXaxis()->SetTitle("|y_{CM}|");
	gRFB_np_sys_lowpt->GetXaxis()->CenterTitle();
	gRFB_np_sys_lowpt->GetXaxis()->SetLimits(0.0,4.5);
	gRFB_np_sys_lowpt->GetYaxis()->SetTitle("R_{FB}");
	gRFB_np_sys_lowpt->SetMinimum(0.0);
	gRFB_np_sys_lowpt->SetMaximum(1.4);
	gRFB_np_sys_lowpt->SetFillColor(kRed-9);
	gRFB_np_sys_lowpt->Draw("A2");
	
	// 2) highpt
	gRFB_np_sys_highpt->SetFillColor(kTeal+7);
	gRFB_np_sys_highpt->Draw("2");

	// 3) lhcb
	gRFB_lhcb_np_sys = new TGraphAsymmErrors(nBin_lhcb, lhcb_px, lhcb_py_np, lhcb_exsys, lhcb_exsys, lhcb_eysys_np, lhcb_eysys_np);	
	gRFB_lhcb_np_sys->SetFillColor(kAzure-9);
	gRFB_lhcb_np_sys->Draw("2");

	SetGraphStyle(gRFB_np_lowpt,1,3);
	gRFB_np_lowpt->Draw("P");
	
	SetGraphStyle(gRFB_np_highpt,0,5);
	gRFB_np_highpt->SetMarkerSize(1.7);
	gRFB_np_highpt->Draw("P");

	gRFB_lhcb_np = new TGraphAsymmErrors(nBin_lhcb, lhcb_px, lhcb_py_np, lhcb_ex, lhcb_ex, lhcb_ey_np, lhcb_ey_np);	
	SetGraphStyle(gRFB_lhcb_np,2,10);
	gRFB_lhcb_np->Draw("P");

	dashedLine(0.0,1.0,4.5,1.0,1,1);

	legBL -> SetHeader("Non-prompt J/#psi");
	legBL -> AddEntry(gRFB_np_lowpt,"CMS :6.5 < p_{T} < 10 [GeV/c]","lp");
	legBL -> AddEntry(gRFB_np_highpt,"CMS :10 < p_{T} < 30 [GeV/c]","lp");
	legBL -> AddEntry(gRFB_lhcb_np,"LHCb : p_{T} < 14 [GeV/c]","lp");
	legBL -> Draw();
	c_np->Update();
	c_np->SaveAs("comparisonLHCb/comp_RFB_rap_LHCb_np.pdf");
	legBL->Clear();
	//c_np->Clear();

	return 0;
}

void formRapArr(Double_t binmin, Double_t binmax, string* arr) {
	Double_t intMin, intMax; 
	Double_t fracMin = modf(binmin, &intMin);
	Double_t fracMax = modf(binmax, &intMax);
	if ( fracMin == 0 && fracMax == 0 ) {
		*arr = Form("%.0f < y_{CM} < %.0f", binmin, binmax);
	} else if ( fracMin != 0 && fracMax == 0 ) {
		*arr = Form("%.2f < y_{CM} < %.0f", binmin, binmax);
	} else if ( fracMin == 0 && fracMax != 0 ) {
		*arr = Form("%.0f < y_{CM} < %.2f", binmin, binmax);
	} else {
		*arr = Form("%.2f < y_{CM} < %.2f", binmin, binmax);
	}
}

void formAbsRapArr(Double_t binmin, Double_t binmax, string* arr) {
	Double_t intMin, intMax; 
	Double_t fracMin = modf(binmin, &intMin);
	Double_t fracMax = modf(binmax, &intMax);
	if ( fracMin == 0 && fracMax == 0 ) {
		*arr = Form("%.0f < |y_{CM}| < %.0f", binmin, binmax);
	} else if ( fracMin != 0 && fracMax == 0 ) {
		*arr = Form("%.2f < |y_{CM}| < %.0f", binmin, binmax);
	} else if ( fracMin == 0 && fracMax != 0 ) {
		*arr = Form("%.0f < |y_{CM}| < %.2f", binmin, binmax);
	} else {
		*arr = Form("%.2f < |y_{CM}| < %.2f", binmin, binmax);
	}
}

void formPtArr(Double_t binmin, Double_t binmax, string* arr) {
	Double_t intMin, intMax; 
	Double_t fracMin = modf(binmin, &intMin);
	Double_t fracMax = modf(binmax, &intMax);
	if ( fracMin == 0 && fracMax == 0 ) {
		*arr = Form("%.0f < p_{T} < %.0f [GeV/c]", binmin, binmax);
	} else if ( fracMin != 0 && fracMax == 0 ) {
		*arr = Form("%.1f < p_{T} < %.0f [GeV/c]", binmin, binmax);
	} else if ( fracMin == 0 && fracMax != 0 ) {
		*arr = Form("%.0f < p_{T} < %.1f [GeV/c]", binmin, binmax);
	} else {
		*arr = Form("%.1f < p_{T} < %.1f [GeV/c]", binmin, binmax);
	}
}

