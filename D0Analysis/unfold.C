#include <string>
#include <iomanip>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "TROOT.h"
#include "TRint.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TPaveText.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TGraph.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TUnfoldSys.h"
#include "TSpline.h"
#include "TMath.h"

#pragma once

#define TITLE_FONTSIZE 26
#define LABEL_FONTSIZE 18

#define LEFT_MARGIN 0.17
#define RIGHT_MARGIN 0.03
#define TOP_MARGIN 0.05
#define BOTTOM_MARGIN 0.13

TStyle* createMyStyle() {
  TStyle *myStyle = new TStyle("myStyle", "myStyle");

  // For the canvas:
  myStyle->SetCanvasBorderMode(0);
  myStyle->SetCanvasColor(kWhite);
  myStyle->SetCanvasDefH(800); //Height of canvas
  myStyle->SetCanvasDefW(800); //Width of canvas
  myStyle->SetCanvasDefX(0);   //POsition on screen
  myStyle->SetCanvasDefY(0);

  // For the Pad:
  myStyle->SetPadBorderMode(0);
  myStyle->SetPadColor(kWhite);
  myStyle->SetPadGridX(false);
  myStyle->SetPadGridY(false);
  myStyle->SetGridColor(0);
  myStyle->SetGridStyle(3);
  myStyle->SetGridWidth(1);

  // For the frame:
  myStyle->SetFrameBorderMode(0);
  myStyle->SetFrameBorderSize(1);
  myStyle->SetFrameFillColor(0);
  myStyle->SetFrameFillStyle(0);
  myStyle->SetFrameLineColor(1);
  myStyle->SetFrameLineStyle(1);
  myStyle->SetFrameLineWidth(1);

  // For the histo:
  myStyle->SetHistLineStyle(1);
  myStyle->SetHistLineWidth(2);
  myStyle->SetEndErrorSize(2);

  //For the fit/function:
  myStyle->SetFitFormat("5.4g");
  myStyle->SetFuncColor(2);
  myStyle->SetFuncStyle(1);
  myStyle->SetFuncWidth(1);

  // For the statistics box:
  myStyle->SetOptFile(0);
  myStyle->SetStatColor(kWhite);
  //myStyle->SetStatFont(43);
  //myStyle->SetStatFontSize(0.025);
  myStyle->SetStatTextColor(1);
  myStyle->SetStatFormat("6.4g");
  myStyle->SetStatBorderSize(1);
  myStyle->SetStatH(0.12);
  myStyle->SetStatW(0.3);
  myStyle->SetStatY(0.92);
  myStyle->SetStatX(0.94);

  //For the date:
  myStyle->SetOptDate(0);

  // Margins:
  myStyle->SetPadTopMargin(TOP_MARGIN);
  myStyle->SetPadBottomMargin(BOTTOM_MARGIN);
  myStyle->SetPadLeftMargin(LEFT_MARGIN);
  myStyle->SetPadRightMargin(RIGHT_MARGIN);

  // For the Global title:
  myStyle->SetOptTitle(0);
  myStyle->SetTitleFont(63);
  myStyle->SetTitleColor(1);
  myStyle->SetTitleTextColor(1);
  myStyle->SetTitleFillColor(10);
  myStyle->SetTitleBorderSize(0);
  myStyle->SetTitleAlign(33); 
  myStyle->SetTitleX(1);
  myStyle->SetTitleFontSize(TITLE_FONTSIZE);

  // For the axis titles:

  myStyle->SetTitleColor(1, "XYZ");
  myStyle->SetTitleFont(43, "XYZ");
  myStyle->SetTitleSize(TITLE_FONTSIZE, "XYZ");
  myStyle->SetTitleYOffset(2.5); 
  myStyle->SetTitleXOffset(1.5);

  myStyle->SetLabelColor(1, "XYZ");
  myStyle->SetLabelFont(43, "XYZ");
  myStyle->SetLabelOffset(0.01, "YZ");
  myStyle->SetLabelOffset(0.015, "X");
  myStyle->SetLabelSize(LABEL_FONTSIZE, "XYZ");

  myStyle->SetAxisColor(1, "XYZ");
  myStyle->SetStripDecimals(kTRUE);
  myStyle->SetTickLength(0.03, "XYZ");
  myStyle->SetNdivisions(510, "XYZ");
  myStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  myStyle->SetPadTickY(1);

  myStyle->SetOptLogx(0);
  myStyle->SetOptLogy(0);
  myStyle->SetOptLogz(0);

  myStyle->SetHatchesSpacing(1.3);
  myStyle->SetHatchesLineWidth(1);

  myStyle->cd();

  return myStyle;
}

void leg_style(TLegend *leg,
    //int text_size = 0.035,
    //int text_font = 43,
    int text_align = 22,
    int fill_style = 1,
    int fill_color = 10,
    int line_color = 0,
    int line_width = 0,
    int border_size = 1) {

  //leg->SetTextSize(text_size);
  //leg->SetTextFont(text_font);
  leg->SetTextAlign(text_align);
  leg->SetFillStyle(fill_style);
  leg->SetFillColor(fill_color);
  leg->SetLineColor(line_color);
  leg->SetLineWidth(line_width);
  leg->SetBorderSize(border_size);
}

void h_myStyle(TH1 *h,
               int line_width=2,
               int line_color=1,
               int line_style=1, 
               int fill_color=50,
               int fill_style=1001,
               float y_min=-1111.,
               float y_max=-1111.,
               int ndivx=510,
               int ndivy=510,
               int marker_style=20,
               int marker_color=1,
               float marker_size=1.2,
               int optstat=0,
               const char* xtitle="") {
  
  h->SetLineWidth(line_width);
  h->SetLineColor(line_color);
  h->SetLineStyle(line_style);
  h->SetFillColor(fill_color);
  h->SetFillStyle(fill_style);
  h->SetMaximum(y_max);
  h->SetMinimum(y_min);
  h->GetXaxis()->SetNdivisions(ndivx);
  h->GetYaxis()->SetNdivisions(ndivy);
  h->GetYaxis()->SetTitleOffset(2.5);
  
  h->SetMarkerStyle(marker_style);
  h->SetMarkerColor(marker_color);
  h->SetMarkerSize(marker_size);
  h->SetStats(optstat);
  
  double binSize = h->GetXaxis()->GetBinWidth(1);
  std::stringstream ss;
  ss << "Events / (" << std::fixed << std::setprecision(2) << binSize << " GeV/c)";
  h->GetYaxis()->SetTitle(ss.str().c_str());
  h->GetXaxis()->SetTitle(xtitle);
}

void sp_myStyle(TSpline *gr,
                const char* name="",
                int line_width=2,
                int line_color=1,
                int line_style=1, 
                int fill_color=50,
                int fill_style=1001,
                int marker_style=20,
                int marker_color=1,
                double marker_size=1.2) {
  
  gr->SetLineWidth(line_width);
  gr->SetLineColor(line_color);
  gr->SetLineStyle(line_style);
  gr->SetFillColor(fill_color);
  gr->SetFillStyle(fill_style);
  
  gr->SetMarkerStyle(marker_style);
  gr->SetMarkerColor(marker_color);
  gr->SetMarkerSize(marker_size);
  
  gr->SetName(name);
  
}

void gr_myStyle(TGraph *gr,
                const char* name="",
                int line_width=2,
                int line_color=1,
                int line_style=1, 
                int fill_color=50,
                int fill_style=1001,
                double y_min=-1111.,
                double y_max=-1111.,
                int ndivx=510,
                int ndivy=510,
                int marker_style=20,
                int marker_color=1,
                double marker_size=1.2,
                const char* xtitle="",
                const char* ytitle="") {
  
  gr->SetLineWidth(line_width);
  gr->SetLineColor(line_color);
  gr->SetLineStyle(line_style);
  gr->SetFillColor(fill_color);
  gr->SetFillStyle(fill_style);
  gr->SetMaximum(y_max);
  gr->SetMinimum(y_min);
  gr->GetXaxis()->SetNdivisions(ndivx);
  gr->GetYaxis()->SetNdivisions(ndivy);
  
  gr->SetMarkerStyle(marker_style);
  gr->SetMarkerColor(marker_color);
  gr->SetMarkerSize(marker_size);
  
  gr->GetXaxis()->SetTitle(xtitle);
  gr->GetYaxis()->SetTitle(ytitle);
  
  gr->SetName(name);
  
}

void cms_style_bis(double lumi = 15.2, bool isData = true){
  std::string status = "Simulation preliminary";
  if (isData) status = "Preliminary";
  TPaveText* pt_exp = new TPaveText(LEFT_MARGIN, 1 - 0.5 * TOP_MARGIN, 1 - RIGHT_MARGIN, 1, "brNDC");
  pt_exp->SetFillStyle(0);
  pt_exp->SetBorderSize(0);
  pt_exp->SetMargin(0);
  pt_exp->SetTextFont(62);
  pt_exp->SetTextSize(0.75 * TOP_MARGIN);
  pt_exp->SetTextAlign(13);
  TString d = TString::Format("CMS #font[52]{#scale[0.76]{%s}}", status.c_str());
  pt_exp->AddText(d);
  pt_exp->Draw();

  TString lumi_s = TString::Format("%3.1f fb^{-1} (8 TeV)", lumi);
  TPaveText* pt_lumi = new TPaveText(LEFT_MARGIN, 1 - 0.5 * TOP_MARGIN, 1 - RIGHT_MARGIN, 1, "brNDC");
  pt_lumi->SetFillStyle(0);
  pt_lumi->SetBorderSize(0);
  pt_lumi->SetMargin(0);
  pt_lumi->SetTextFont(42);
  pt_lumi->SetTextSize(0.6 * TOP_MARGIN);
  pt_lumi->SetTextAlign(33);
  pt_lumi->AddText(lumi_s);
  pt_lumi->Draw();

}


//---------------------------------------------------------------
int unfold(TString date = "", TString version = "", bool inBatch = true)
//---------------------------------------------------------------
{  
  if (date.Length() > 0 && version.Length() > 0)  {
 
    TStyle* my_style = createMyStyle();
    my_style->cd();
    if (inBatch) gROOT->SetBatch(true);
    TH1::SetDefaultSumw2();
    
    TString outDir = date+"/v"+version+"/UnfoldNoMu/";
    gROOT->ProcessLine(".! mkdir "+outDir);
    
    /* Step 1: get histos */
    
    float lumi = (19.705+19.690)/2.; 
    float xsection = 107.6722; 
    float ngen = 31004465.;
    float factor = 1000.*lumi*xsection/ngen;
    
    TFile* fiMC = TFile::Open(date+"/v"+version+"/MyAnaAll/TTJets_SemiLeptMGDecays.root");
    TH2F* histoMC_reco_true = (TH2F*)fiMC->Get("PtCh-nomu-b-jets");
    TH1F* histoMC_reco = (TH1F*)fiMC->Get("PtChReco-nomu-b-jets");
    TH1F* histoMC_true = (TH1F*)fiMC->Get("PtChTrue-nomu-b-jets");
    
    histoMC_reco_true->Scale(factor);
    histoMC_reco->Scale(factor);
    histoMC_true->Scale(factor); 
    
    TFile* fiData = TFile::Open(date+"/v"+version+"/MyAnaAll/Run2012ABCD.root");
    TH1F* histoData_reco = (TH1F*)fiData->Get("PtChReco-nomu-b-jets");
    
    int nGen = histoMC_true->GetNbinsX(); 
    double xminGen = histoMC_true->GetXaxis()->GetXmin(); 
    double xmaxGen = histoMC_true->GetXaxis()->GetXmax(); 
    
    
    /* Step 2: unfold */
    
    TUnfoldSys unfold(histoMC_reco_true,TUnfold::kHistMapOutputHoriz,
                      TUnfold::kRegModeSize,TUnfold::kEConstraintNone);
    
    // define the input vector (the measured data distribution)
    unfold.SetInput(histoData_reco); 
    
    // run the unfolding
    Int_t nScan = 30;
    TSpline *logTauX,*logTauY;
    TGraph *lCurve;
    // this method scans the parameter tau and finds the kink in the L curve
    // finally, the unfolding is done for the best choice of tau
    Int_t iBest = unfold.ScanLcurve(nScan,0.,0.,&lCurve,&logTauX,&logTauY);
    
    // save graphs with one point to visualize best choice of tau
    Double_t t[1],x[1],y[1];
    logTauX->GetKnot(iBest,t[0],x[0]);
    logTauY->GetKnot(iBest,t[0],y[0]);
    TGraph *bestLcurve = new TGraph(1,x,y);
    TGraph *bestLogTauLogChi2 = new TGraph(1,t,x);
    
    // get unfolding output
    // Reminder: there are
    //   nGen+2  Generator level bins
    // But we are not interested in the additional bins.
    // The mapping is required to get the proper errors and correlations
    
    // Here a mapping is defined from the nGen+2 bins to nGen bins.
    Int_t *binMap = new Int_t[nGen+2];
    binMap[0] = -1;    // underflow bin should be ignored
    binMap[nGen+1] = -1; // overflow bin should be ignored
    for(Int_t i = 1; i <= nGen; i++) {
      binMap[i] = i;  // map inner bins to output histogram bins
    }
    
    // this returns the unfolding output
    // The errors included at this point are:
    //    * statistical errros
    //    * background subtraction errors
    TH1F *histUnfoldStatBgr=new TH1F("PT(unfold,signal,stat+bgr)",";Pt(gen)",
                                     nGen,xminGen,xmaxGen);
    unfold.GetOutput(histUnfoldStatBgr,binMap);
    
    // retreive error matrix of statistical errors only
    TH2F *histEmatStat = new TH2F("ErrMat(stat)",";Pt(gen);Pt(gen)",
                                  nGen,xminGen,xmaxGen,nGen,xminGen,xmaxGen);
    unfold.GetEmatrixInput(histEmatStat,binMap);
    
    // unfolded data with statistical errors
    TH1F *histoData_unfold = new TH1F("PT(unfold,signal,stat)",";Pt(gen)",
                                      nGen,xminGen,xmaxGen);
    
    for(Int_t i = 0; i < nGen+2; i++) {
      Double_t c = histUnfoldStatBgr->GetBinContent(i);
      
      // histogram with unfolded data and stat errors
      histoData_unfold->SetBinContent(i,c);
      histoData_unfold->SetBinError
      (i,TMath::Sqrt(histEmatStat->GetBinContent(i,i)));
    }
    
    // create histogram with correlation matrix
    TH2F *histCorr = new TH2F("Corr(total)",";Pt(gen);Pt(gen)",
                              nGen,xminGen,xmaxGen,nGen,xminGen,xmaxGen);
    for(Int_t i = 0; i < nGen+2; i++) {
      Double_t ei, ej;
      ei = TMath::Sqrt(histEmatStat->GetBinContent(i,i));
      if(ei <= 0.0) continue;
      for(Int_t j = 0; j < nGen+2; j++) {
        ej = TMath::Sqrt(histEmatStat->GetBinContent(j,j));
        if(ej <= 0.0) continue;
        histCorr->SetBinContent(i,j, histEmatStat->GetBinContent(i,j)/ei/ej);
      }
    }
    
    /* Step 3: plots */
    
    TLatex* channel_tex = new TLatex(0.22, 0.9, "e/#mu + Jets channel"); 
    channel_tex->SetNDC(true);
    channel_tex->SetTextFont(43);
    channel_tex->SetTextSize(TITLE_FONTSIZE - 6);  
    
    TCanvas *cn_xcheck = new TCanvas("cn_xcheck","cn_xcheck",800,800); 
    cn_xcheck->cd();  
    h_myStyle(histoMC_reco, 0, 430, 1, 430, 3002, 0, 1.1*histoMC_reco->GetMaximum(), 510, 510, 20, 430, 1.2, 1, "p_{T}(#pi^{#pm}) (GeV/c)");
    h_myStyle(histoMC_true, 0, 801, 1, 801, 3002, 0, 1.1*histoMC_true->GetMaximum(), 510, 510, 20, 801, 1.2, 1, "p_{T}(#pi^{#pm}) (GeV/c)");
    h_myStyle(histoData_reco, 0, 602, 1, 602, 3002, 0, 1.1*histoData_reco->GetMaximum(), 510, 510, 20, 602, 1.2, 1, "p_{T}(#pi^{#pm}) (GeV/c)");
    h_myStyle(histoData_unfold, 0, 629, 1, 629, 3002, 0, 1.1*histoData_unfold->GetMaximum(), 510, 510, 20, 629, 1.2, 1, "p_{T}(#pi^{#pm}) (GeV/c)");
    histoMC_reco->Draw("e");
    histoMC_true->Draw("esame");
    histoData_reco->Draw("esame");
    histoData_unfold->Draw("esame");
    TLegend *leg_xcheck = new TLegend(0.6,0.76,0.89,0.88);
    leg_style(leg_xcheck, 12);
    leg_xcheck->AddEntry(histoData_reco,"Reconstructed data - Run 2012 A,B,C,D", "LP");
    leg_xcheck->AddEntry(histoData_unfold,"Unfolded data - Run 2012 A,B,C,D", "LP");
    leg_xcheck->AddEntry(histoMC_reco,"Reconstructed MG+PY6 Z2* Semilept. t#bar{t}", "LP");
    leg_xcheck->AddEntry(histoMC_true,"Generated MG+PY6 Z2* Semilept. t#bar{t}", "LP");
    leg_xcheck->Draw(); 
    channel_tex->Draw("same");
    cms_style_bis(lumi, true);
    cn_xcheck->SaveAs(outDir+"Xchecks.C");
    cn_xcheck->SaveAs(outDir+"Xchecks.eps");
    cn_xcheck->SaveAs(outDir+"Xchecks.pdf");

    // show tau (regularization strength) as a function of chi**2
    TCanvas *cn_tau = new TCanvas("cn_tau","cn_tau",800,800);
    cn_tau->cd();
    sp_myStyle(logTauX,"logTauX",1,9,1,9,1001,20,9,0.1);
    logTauX->Draw("AL");
    bestLogTauLogChi2->SetMarkerColor(50);
    bestLogTauLogChi2->SetMarkerStyle(21);
    bestLogTauLogChi2->SetMarkerSize(1.2);
    bestLogTauLogChi2->Draw("ep");
    channel_tex->Draw("same");
    cms_style_bis(lumi, true);
    cn_tau->SaveAs(outDir+"TauVsChi2.C");
    cn_tau->SaveAs(outDir+"TauVsChi2.eps");
    cn_tau->SaveAs(outDir+"TauVsChi2.pdf");
    
    // show the L curve (matrix of regularization conditions)
    TCanvas *cn_lcurve = new TCanvas("cn_lcurve","cn_lcurve",800,800);
    cn_lcurve->cd();
    gr_myStyle(lCurve,"lCurve",1,9,1,9,1001,xminGen,xmaxGen,510,510,20,9,0.1,"L_{x}^{curve}","L_{y}^{curve}");
    lCurve->Draw("AL");
    bestLcurve->SetMarkerColor(50);
    bestLcurve->SetMarkerStyle(21);
    bestLcurve->SetMarkerSize(1.2);
    bestLcurve->Draw("ep");  
    channel_tex->Draw("same");
    cms_style_bis(lumi, true);
    cn_lcurve->SaveAs(outDir+"LCurve.C");
    cn_lcurve->SaveAs(outDir+"LCurve.eps");
    cn_lcurve->SaveAs(outDir+"LCurve.pdf");
    
    // show the correlation matrix
    TCanvas *cn_corr = new TCanvas("cn_corr","cn_corr",800,800);
    cn_corr->cd();
    histCorr->SetStats(kFALSE);
    histCorr->GetXaxis()->SetTitle("p_{T}^{gen}(#pi^{#pm})");
    histCorr->GetYaxis()->SetTitle("p_{T}^{reco}(#pi^{#pm})");
    histCorr->GetXaxis()->SetLabelSize(0.05);
    histCorr->GetXaxis()->SetTitleSize(0.05);
    histCorr->GetXaxis()->SetTitleOffset(1.);
    histCorr->GetYaxis()->SetLabelSize(0.05);
    histCorr->GetYaxis()->SetTitleSize(0.045);
    histCorr->GetYaxis()->SetTitleOffset(1.);
    histCorr->Draw("CONT4 COLZ");
    channel_tex->Draw("same");
    cms_style_bis(lumi, true);
    cn_corr->SaveAs(outDir+"Correlation.C");
    cn_corr->SaveAs(outDir+"Correlation.eps");
    cn_corr->SaveAs(outDir+"Correlation.pdf");
    
    // show the error matrix
    TCanvas *cn_err = new TCanvas("cn_err","cn_err",800,800);
    cn_err->cd();
    histEmatStat->SetStats(kFALSE);
    histEmatStat->GetXaxis()->SetTitle("p_{T}^{gen}(#pi^{#pm})");
    histEmatStat->GetYaxis()->SetTitle("p_{T}^{reco}(#pi^{#pm})");
    histEmatStat->GetXaxis()->SetLabelSize(0.05);
    histEmatStat->GetXaxis()->SetTitleSize(0.05);
    histEmatStat->GetXaxis()->SetTitleOffset(1.);
    histEmatStat->GetYaxis()->SetLabelSize(0.05);
    histEmatStat->GetYaxis()->SetTitleSize(0.045);
    histEmatStat->GetYaxis()->SetTitleOffset(1.);
    histEmatStat->Draw("CONT4 COLZ");    
    channel_tex->Draw("same");
    cms_style_bis(lumi, true);
    cn_err->SaveAs(outDir+"ErrorStat.C");
    cn_err->SaveAs(outDir+"ErrorStat.eps");
    cn_err->SaveAs(outDir+"ErrorStat.pdf");
    
    
    /* Step 4: compute the weights histoData_unfold/histoData_reco */
    
    //file definition
    ofstream outFile(outDir+"Weights.txt"); // bin et weight
    TFile *outRoot = TFile::Open(outDir+"Weights.root","recreate");
    TH1F *hWeight = new TH1F("Reco2Unfold","Reco2Unfold",nGen,xminGen,xmaxGen);
    for (int ibin = 1; ibin <= nGen; ibin++) {
      float weight = 1.;
      if (histoData_unfold->GetBinContent(ibin) > 1e-6 && histoData_reco->GetBinContent(ibin) > 1e-6)
        weight = histoData_unfold->GetBinContent(ibin)/histoData_reco->GetBinContent(ibin);
      hWeight->SetBinContent(ibin, weight);
      outFile << ibin << "\t" << weight << endl;
    }
    outRoot->cd();
    hWeight->Write();
    outRoot->Close();
    outFile << endl;
    outFile.close();
    
    
    /* Step 5: cleaning */

    if (!inBatch) getchar();

    delete hWeight;
    delete outRoot;
    
    delete cn_err;
    delete cn_corr;
    delete cn_lcurve;
    delete cn_tau;
    delete cn_xcheck;
    delete leg_xcheck;
    delete channel_tex;
    
    delete histCorr;
    delete histoData_unfold;
    delete histEmatStat;
    delete histUnfoldStatBgr;
    delete [] binMap;
    delete bestLcurve;
    delete bestLogTauLogChi2;
    delete logTauX;
    delete logTauY;
    delete lCurve;

    delete histoData_reco;
    fiData->Close();
    delete fiData;
    
    delete histoMC_true;
    delete histoMC_reco;
    delete histoMC_reco_true;
    fiMC->Close();
    delete fiMC;
    
    return 0;
  }
  else 
    return 1;
}
