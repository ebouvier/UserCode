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
#include "TCanvas.h"
#include "TMath.h"

#pragma once

#define TITLE_FONTSIZE 26
#define LABEL_FONTSIZE 18

//#define LEFT_MARGIN 0.17
//#define RIGHT_MARGIN 0.03
#define LEFT_MARGIN 0.09
#define RIGHT_MARGIN 0.11
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

void cms_style_bis(bool isData = true){
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

  TString lumi_s = "(8 TeV)";
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
int migration(TString date = "", TString version = "", bool inBatch = true)
//---------------------------------------------------------------
{  
  if (date.Length() > 0 && version.Length() > 0)  {
 
    TStyle* my_style = createMyStyle();
    my_style->cd();
    my_style->SetPalette(55);
    TLatex* channel_tex = new TLatex(0.12, 0.9, "e/#mu + Jets channel"); 
    channel_tex->SetNDC(true);
    channel_tex->SetTextFont(43);
    channel_tex->SetTextSize(TITLE_FONTSIZE - 6);  
    if (inBatch) gROOT->SetBatch(true);

    TString outDir = date+"/v"+version+"/Migration/";
    gROOT->ProcessLine(".! mkdir "+outDir);
    TFile *outRoot = TFile::Open(outDir+"Matrices.root","recreate");
    ofstream outTxt(outDir+"Chi2.txt"); // eta^gen chi2    
    ofstream outTxt2(outDir+"Matrices.txt"); // pT reco vert, pT gen horiz; 10 bins between 0 and 100    

    TFile* fiMC = TFile::Open(date+"/v"+version+"/MyAnaAll/TTJets_SemiLeptMGDecays.root");

    // Tracks, no mu
    outTxt << "|\\eta^{gen}(tracks, no \\mu)| \t \\chi^{2}" << endl;
    outTxt2 << "## Tracks, no mu \n" << endl;

    TH2F* _h_unfold_tr_M2p4toM1p5_pt = (TH2F*)fiMC->Get("PtCh-M2p4toM1p5-nomu-b-jets");
    TH2F* _h_unfold_tr_P1p5toP2p4_pt = (TH2F*)fiMC->Get("PtCh-P1p5toP2p4-nomu-b-jets");
    double chi_tr_1p5to2p4 = _h_unfold_tr_M2p4toM1p5_pt->Chi2Test(_h_unfold_tr_P1p5toP2p4_pt,"WW OF UF CHI2/NDF");
    outTxt << "[1.5; 2.4] \t" << chi_tr_1p5to2p4 << endl;
    outTxt2 << "### 1.5 < |eta| < 2.4" << endl;
    for (int ireco = 1; ireco <= _h_unfold_tr_M2p4toM1p5_pt->GetNbinsY(); ireco++) {
      for (int igen = 1; igen <= _h_unfold_tr_M2p4toM1p5_pt->GetNbinsX(); igen++) {
        outTxt2 << _h_unfold_tr_M2p4toM1p5_pt->GetBinContent(igen,ireco) + _h_unfold_tr_P1p5toP2p4_pt->GetBinContent(igen,ireco) << "\t";
      }
      outTxt2 << endl;
    }
    outTxt2 << endl;

    TCanvas *cn_tr_M2p4toM1p5 = new TCanvas("cn_tr_M2p4toM1p5","cn_tr_M2p4toM1p5",800,800);
    cn_tr_M2p4toM1p5->cd();
    /*
    cn_tr_M2p4toM1p5->SetLeftMargin(0.09);
    cn_tr_M2p4toM1p5->SetRightMargin(0.11);
    */
    cn_tr_M2p4toM1p5->SetLogz();
    _h_unfold_tr_M2p4toM1p5_pt->SetStats(kFALSE);
    _h_unfold_tr_M2p4toM1p5_pt->GetXaxis()->SetLabelSize(0.025);
    _h_unfold_tr_M2p4toM1p5_pt->GetYaxis()->SetLabelSize(0.025);
    _h_unfold_tr_M2p4toM1p5_pt->GetXaxis()->SetTitleOffset(1.2);
    _h_unfold_tr_M2p4toM1p5_pt->GetYaxis()->SetTitleOffset(1.2);
    _h_unfold_tr_M2p4toM1p5_pt->Draw("COLZ");
    channel_tex->Draw("same");
    cms_style_bis(false);
    cn_tr_M2p4toM1p5->SaveAs(outDir+"Migration_Tr_M2p4toM1p5.C");
    cn_tr_M2p4toM1p5->SaveAs(outDir+"Migration_Tr_M2p4toM1p5.eps");
    cn_tr_M2p4toM1p5->SaveAs(outDir+"Migration_Tr_M2p4toM1p5.pdf");
    TCanvas *cn_tr_P1p5toP2p4 = new TCanvas("cn_tr_P1p5toP2p4","cn_tr_P1p5toP2p4",800,800);
    cn_tr_P1p5toP2p4->cd();
    /*
    cn_tr_P1p5toP2p4->SetLeftMargin(0.09);
    cn_tr_P1p5toP2p4->SetRightMargin(0.11);
    */
    cn_tr_P1p5toP2p4->SetLogz();
    _h_unfold_tr_P1p5toP2p4_pt->SetStats(kFALSE);
    _h_unfold_tr_P1p5toP2p4_pt->GetXaxis()->SetLabelSize(0.025);
    _h_unfold_tr_P1p5toP2p4_pt->GetYaxis()->SetLabelSize(0.025);
    _h_unfold_tr_P1p5toP2p4_pt->GetXaxis()->SetTitleOffset(1.2);
    _h_unfold_tr_P1p5toP2p4_pt->GetYaxis()->SetTitleOffset(1.2);
    _h_unfold_tr_P1p5toP2p4_pt->Draw("COLZ");
    channel_tex->Draw("same");
    cms_style_bis(false);
    cn_tr_P1p5toP2p4->SaveAs(outDir+"Migration_Tr_P1p5toP2p4.C");
    cn_tr_P1p5toP2p4->SaveAs(outDir+"Migration_Tr_P1p5toP2p4.eps");
    cn_tr_P1p5toP2p4->SaveAs(outDir+"Migration_Tr_P1p5toP2p4.pdf");
    
    TH2F* _h_unfold_tr_M1p5toM1_pt = (TH2F*)fiMC->Get("PtCh-M1p5toM1-nomu-b-jets");
    TH2F* _h_unfold_tr_P1toP1p5_pt = (TH2F*)fiMC->Get("PtCh-P1toP1p5-nomu-b-jets");
    double chi_tr_1to1p5 = _h_unfold_tr_M1p5toM1_pt->Chi2Test(_h_unfold_tr_P1toP1p5_pt,"WW OF UF CHI2/NDF");
    outTxt << "[1.0; 1.5] \t" << chi_tr_1to1p5 << endl;
    outTxt2 << "### 1.0 < |eta| < 1.5" << endl;
    for (int ireco = 1; ireco <= _h_unfold_tr_M1p5toM1_pt->GetNbinsY(); ireco++) {
      for (int igen = 1; igen <= _h_unfold_tr_M1p5toM1_pt->GetNbinsX(); igen++) {
        outTxt2 << _h_unfold_tr_M1p5toM1_pt->GetBinContent(igen,ireco) + _h_unfold_tr_P1toP1p5_pt->GetBinContent(igen,ireco) << "\t";
      }
      outTxt2 << endl;
    }
    outTxt2 << endl;

    TCanvas *cn_tr_M1p5toM1 = new TCanvas("cn_tr_M1p5toM1","cn_tr_M1p5toM1",800,800);
    cn_tr_M1p5toM1->cd();
    /*
    cn_tr_M1p5toM1->SetLeftMargin(0.09);
    cn_tr_M1p5toM1->SetRightMargin(0.11);
    */
    cn_tr_M1p5toM1->SetLogz();
    _h_unfold_tr_M1p5toM1_pt->SetStats(kFALSE);
    _h_unfold_tr_M1p5toM1_pt->GetXaxis()->SetLabelSize(0.025);
    _h_unfold_tr_M1p5toM1_pt->GetYaxis()->SetLabelSize(0.025);
    _h_unfold_tr_M1p5toM1_pt->GetXaxis()->SetTitleOffset(1.2);
    _h_unfold_tr_M1p5toM1_pt->GetYaxis()->SetTitleOffset(1.2);
    _h_unfold_tr_M1p5toM1_pt->Draw("COLZ");
    channel_tex->Draw("same");
    cms_style_bis(false);
    cn_tr_M1p5toM1->SaveAs(outDir+"Migration_Tr_M1p5toM1.C");
    cn_tr_M1p5toM1->SaveAs(outDir+"Migration_Tr_M1p5toM1.eps");
    cn_tr_M1p5toM1->SaveAs(outDir+"Migration_Tr_M1p5toM1.pdf");
    TCanvas *cn_tr_P1toP1p5 = new TCanvas("cn_tr_P1toP1p5","cn_tr_P1toP1p5",800,800);
    cn_tr_P1toP1p5->cd();
    /*
    cn_tr_P1toP1p5->SetLeftMargin(0.09);
    cn_tr_P1toP1p5->SetRightMargin(0.11);
    */
    cn_tr_P1toP1p5->SetLogz();
    _h_unfold_tr_P1toP1p5_pt->SetStats(kFALSE);
    _h_unfold_tr_P1toP1p5_pt->GetXaxis()->SetLabelSize(0.025);
    _h_unfold_tr_P1toP1p5_pt->GetYaxis()->SetLabelSize(0.025);
    _h_unfold_tr_P1toP1p5_pt->GetXaxis()->SetTitleOffset(1.2);
    _h_unfold_tr_P1toP1p5_pt->GetYaxis()->SetTitleOffset(1.2);
    _h_unfold_tr_P1toP1p5_pt->Draw("COLZ");
    channel_tex->Draw("same");
    cms_style_bis(false);
    cn_tr_P1toP1p5->SaveAs(outDir+"Migration_Tr_P1toP1p5.C");
    cn_tr_P1toP1p5->SaveAs(outDir+"Migration_Tr_P1toP1p5.eps");
    cn_tr_P1toP1p5->SaveAs(outDir+"Migration_Tr_P1toP1p5.pdf");

    TH2F* _h_unfold_tr_M1to0_pt = (TH2F*)fiMC->Get("PtCh-M1to0-nomu-b-jets");
    TH2F* _h_unfold_tr_0toP1_pt = (TH2F*)fiMC->Get("PtCh-0toP1-nomu-b-jets");
    double chi_tr_0to1 = _h_unfold_tr_M1to0_pt->Chi2Test(_h_unfold_tr_0toP1_pt,"WW OF UF CHI2/NDF");
    outTxt << "[0; 1] \t" << chi_tr_0to1 << endl;
    outTxt2 << "### 0 < |eta| < 1.0" << endl;
    for (int ireco = 1; ireco <= _h_unfold_tr_M1to0_pt->GetNbinsY(); ireco++) {
      for (int igen = 1; igen <= _h_unfold_tr_M1to0_pt->GetNbinsX(); igen++) {
        outTxt2 << _h_unfold_tr_M1to0_pt->GetBinContent(igen,ireco) + _h_unfold_tr_0toP1_pt->GetBinContent(igen,ireco) << "\t";
      }
      outTxt2 << endl;
    }
    outTxt2 << endl;

    TCanvas *cn_tr_M1to0 = new TCanvas("cn_tr_M1to0","cn_tr_M1to0",800,800);
    cn_tr_M1to0->cd();
    /*
    cn_tr_M1to0->SetLeftMargin(0.09);
    cn_tr_M1to0->SetRightMargin(0.11);
    */
    cn_tr_M1to0->SetLogz();
    _h_unfold_tr_M1to0_pt->SetStats(kFALSE);
    _h_unfold_tr_M1to0_pt->GetXaxis()->SetLabelSize(0.025);
    _h_unfold_tr_M1to0_pt->GetYaxis()->SetLabelSize(0.025);
    _h_unfold_tr_M1to0_pt->GetXaxis()->SetTitleOffset(1.2);
    _h_unfold_tr_M1to0_pt->GetYaxis()->SetTitleOffset(1.2);
    _h_unfold_tr_M1to0_pt->Draw("COLZ");
    channel_tex->Draw("same");
    cms_style_bis(false);
    cn_tr_M1to0->SaveAs(outDir+"Migration_Tr_M1to0.C");
    cn_tr_M1to0->SaveAs(outDir+"Migration_Tr_M1to0.eps");
    cn_tr_M1to0->SaveAs(outDir+"Migration_Tr_M1to0.pdf");
    TCanvas *cn_tr_0toP1 = new TCanvas("cn_tr_0toP1","cn_tr_0toP1",800,800);
    cn_tr_0toP1->cd();
    /*
    cn_tr_0toP1->SetLeftMargin(0.09);
    cn_tr_0toP1->SetRightMargin(0.11);
    */
    cn_tr_0toP1->SetLogz();
    _h_unfold_tr_0toP1_pt->SetStats(kFALSE);
    _h_unfold_tr_0toP1_pt->GetXaxis()->SetLabelSize(0.025);
    _h_unfold_tr_0toP1_pt->GetYaxis()->SetLabelSize(0.025);
    _h_unfold_tr_0toP1_pt->GetXaxis()->SetTitleOffset(1.2);
    _h_unfold_tr_0toP1_pt->GetYaxis()->SetTitleOffset(1.2);
    _h_unfold_tr_0toP1_pt->Draw("COLZ");
    channel_tex->Draw("same");
    cms_style_bis(false);
    cn_tr_0toP1->SaveAs(outDir+"Migration_Tr_0toP1.C");
    cn_tr_0toP1->SaveAs(outDir+"Migration_Tr_0toP1.eps");
    cn_tr_0toP1->SaveAs(outDir+"Migration_Tr_0toP1.pdf");

    outRoot->cd();
    _h_unfold_tr_M2p4toM1p5_pt->Write();
    _h_unfold_tr_M1p5toM1_pt->Write();
    _h_unfold_tr_M1to0_pt->Write();
    _h_unfold_tr_0toP1_pt->Write();
    _h_unfold_tr_P1toP1p5_pt->Write();
    _h_unfold_tr_P1p5toP2p4_pt->Write();
    
    
    // Soft mu
    
    outTxt << endl;
    outTxt << "|\\eta^{gen}(soft \\mu)| \t \\chi^{2}" << endl;
    outTxt2 << endl;
    outTxt2 << "## Soft mu \n" << endl;

    TH2F* _h_unfold_mu_M2p4toM1p5_pt = (TH2F*)fiMC->Get("PtSoftMu-M2p4toM1p5-b-jets");
    TH2F* _h_unfold_mu_P1p5toP2p4_pt = (TH2F*)fiMC->Get("PtSoftMu-P1p5toP2p4-b-jets");
    double chi_mu_1p5to2p4 = _h_unfold_mu_M2p4toM1p5_pt->Chi2Test(_h_unfold_mu_P1p5toP2p4_pt,"WW OF UF CHI2/NDF");
    outTxt << "[1.5; 2.4] \t" << chi_mu_1p5to2p4 << endl;
    outTxt2 << "### 1.5 < |eta| < 2.4" << endl;
    for (int ireco = 1; ireco <= _h_unfold_mu_M2p4toM1p5_pt->GetNbinsY(); ireco++) {
      for (int igen = 1; igen <= _h_unfold_mu_M2p4toM1p5_pt->GetNbinsX(); igen++) {
        outTxt2 << _h_unfold_mu_M2p4toM1p5_pt->GetBinContent(igen,ireco) + _h_unfold_mu_P1p5toP2p4_pt->GetBinContent(igen,ireco) << "\t";
      }
      outTxt2 << endl;
    }
    outTxt2 << endl;

    TCanvas *cn_mu_M2p4toM1p5 = new TCanvas("cn_mu_M2p4toM1p5","cn_mu_M2p4toM1p5",800,800);
    cn_mu_M2p4toM1p5->cd();
    /*
    cn_mu_M2p4toM1p5->SetLeftMargin(0.09);
    cn_mu_M2p4toM1p5->SetRightMargin(0.11);
    */
    cn_mu_M2p4toM1p5->SetLogz();
    _h_unfold_mu_M2p4toM1p5_pt->SetStats(kFALSE);
    _h_unfold_mu_M2p4toM1p5_pt->GetXaxis()->SetLabelSize(0.025);
    _h_unfold_mu_M2p4toM1p5_pt->GetYaxis()->SetLabelSize(0.025);
    _h_unfold_mu_M2p4toM1p5_pt->GetXaxis()->SetTitleOffset(1.2);
    _h_unfold_mu_M2p4toM1p5_pt->GetYaxis()->SetTitleOffset(1.2);
    _h_unfold_mu_M2p4toM1p5_pt->Draw("COLZ");
    channel_tex->Draw("same");
    cms_style_bis(false);
    cn_mu_M2p4toM1p5->SaveAs(outDir+"Migration_Mu_M2p4toM1p5.C");
    cn_mu_M2p4toM1p5->SaveAs(outDir+"Migration_Mu_M2p4toM1p5.eps");
    cn_mu_M2p4toM1p5->SaveAs(outDir+"Migration_Mu_M2p4toM1p5.pdf");
    TCanvas *cn_mu_P1p5toP2p4 = new TCanvas("cn_mu_P1p5toP2p4","cn_mu_P1p5toP2p4",800,800);
    cn_mu_P1p5toP2p4->cd();
    /*
    cn_mu_P1p5toP2p4->SetLeftMargin(0.09);
    cn_mu_P1p5toP2p4->SetRightMargin(0.11);
    */
    cn_mu_P1p5toP2p4->SetLogz();
    _h_unfold_mu_P1p5toP2p4_pt->SetStats(kFALSE);
    _h_unfold_mu_P1p5toP2p4_pt->GetXaxis()->SetLabelSize(0.025);
    _h_unfold_mu_P1p5toP2p4_pt->GetYaxis()->SetLabelSize(0.025);
    _h_unfold_mu_P1p5toP2p4_pt->GetXaxis()->SetTitleOffset(1.2);
    _h_unfold_mu_P1p5toP2p4_pt->GetYaxis()->SetTitleOffset(1.2);
    _h_unfold_mu_P1p5toP2p4_pt->Draw("COLZ");
    channel_tex->Draw("same");
    cms_style_bis(false);
    cn_mu_P1p5toP2p4->SaveAs(outDir+"Migration_Mu_P1p5toP2p4.C");
    cn_mu_P1p5toP2p4->SaveAs(outDir+"Migration_Mu_P1p5toP2p4.eps");
    cn_mu_P1p5toP2p4->SaveAs(outDir+"Migration_Mu_P1p5toP2p4.pdf");

    TH2F* _h_unfold_mu_M1p5toM1_pt = (TH2F*)fiMC->Get("PtSoftMu-M1p5toM1-b-jets");
    TH2F* _h_unfold_mu_P1toP1p5_pt = (TH2F*)fiMC->Get("PtSoftMu-P1toP1p5-b-jets");
    double chi_mu_1to1p5 = _h_unfold_mu_M1p5toM1_pt->Chi2Test(_h_unfold_mu_P1toP1p5_pt,"WW OF UF CHI2/NDF");
    outTxt << "[1.0; 1.5] \t" << chi_mu_1to1p5 << endl;
    outTxt2 << "### 1.0 < |eta| < 1.5" << endl;
    for (int ireco = 1; ireco <= _h_unfold_mu_M1p5toM1_pt->GetNbinsY(); ireco++) {
      for (int igen = 1; igen <= _h_unfold_mu_M1p5toM1_pt->GetNbinsX(); igen++) {
        outTxt2 << _h_unfold_mu_M1p5toM1_pt->GetBinContent(igen,ireco) + _h_unfold_mu_P1toP1p5_pt->GetBinContent(igen,ireco) << "\t";
      }
      outTxt2 << endl;
    }
    outTxt2 << endl;

    TCanvas *cn_mu_M1p5toM1 = new TCanvas("cn_mu_M1p5toM1","cn_mu_M1p5toM1",800,800);
    cn_mu_M1p5toM1->cd();
    /*
    cn_mu_M1p5toM1->SetLeftMargin(0.09);
    cn_mu_M1p5toM1->SetRightMargin(0.11);
    */
    cn_mu_M1p5toM1->SetLogz();
    _h_unfold_mu_M1p5toM1_pt->SetStats(kFALSE);
    _h_unfold_mu_M1p5toM1_pt->GetXaxis()->SetLabelSize(0.025);
    _h_unfold_mu_M1p5toM1_pt->GetYaxis()->SetLabelSize(0.025);
    _h_unfold_mu_M1p5toM1_pt->GetXaxis()->SetTitleOffset(1.2);
    _h_unfold_mu_M1p5toM1_pt->GetYaxis()->SetTitleOffset(1.2);
    _h_unfold_mu_M1p5toM1_pt->Draw("COLZ");
    channel_tex->Draw("same");
    cms_style_bis(false);
    cn_mu_M1p5toM1->SaveAs(outDir+"Migration_Mu_M1p5toM1.C");
    cn_mu_M1p5toM1->SaveAs(outDir+"Migration_Mu_M1p5toM1.eps");
    cn_mu_M1p5toM1->SaveAs(outDir+"Migration_Mu_M1p5toM1.pdf");
    TCanvas *cn_mu_P1toP1p5 = new TCanvas("cn_mu_P1toP1p5","cn_mu_P1toP1p5",800,800);
    cn_mu_P1toP1p5->cd();
    /*
    cn_mu_P1toP1p5->SetLeftMargin(0.09);
    cn_mu_P1toP1p5->SetRightMargin(0.11);
    */
    cn_mu_P1toP1p5->SetLogz();
    _h_unfold_mu_P1toP1p5_pt->SetStats(kFALSE);
    _h_unfold_mu_P1toP1p5_pt->GetXaxis()->SetLabelSize(0.025);
    _h_unfold_mu_P1toP1p5_pt->GetYaxis()->SetLabelSize(0.025);
    _h_unfold_mu_P1toP1p5_pt->GetXaxis()->SetTitleOffset(1.2);
    _h_unfold_mu_P1toP1p5_pt->GetYaxis()->SetTitleOffset(1.2);
    _h_unfold_mu_P1toP1p5_pt->Draw("COLZ");
    channel_tex->Draw("same");
    cms_style_bis(false);
    cn_mu_P1toP1p5->SaveAs(outDir+"Migration_Mu_P1toP1p5.C");
    cn_mu_P1toP1p5->SaveAs(outDir+"Migration_Mu_P1toP1p5.eps");
    cn_mu_P1toP1p5->SaveAs(outDir+"Migration_Mu_P1toP1p5.pdf");

    TH2F* _h_unfold_mu_M1to0_pt = (TH2F*)fiMC->Get("PtSoftMu-M1to0-b-jets");
    TH2F* _h_unfold_mu_0toP1_pt = (TH2F*)fiMC->Get("PtSoftMu-0toP1-b-jets");
    double chi_mu_0to1 = _h_unfold_mu_M1to0_pt->Chi2Test(_h_unfold_mu_0toP1_pt,"WW OF UF CHI2/NDF");
    outTxt << "[0; 1] \t" << chi_mu_0to1 << endl;
    outTxt2 << "### 0 < |eta| < 1.0" << endl;
    for (int ireco = 1; ireco <= _h_unfold_mu_M1to0_pt->GetNbinsY(); ireco++) {
      for (int igen = 1; igen <= _h_unfold_mu_M1to0_pt->GetNbinsX(); igen++) {
        outTxt2 << _h_unfold_mu_M1to0_pt->GetBinContent(igen,ireco) + _h_unfold_mu_0toP1_pt->GetBinContent(igen,ireco) << "\t";
      }
      outTxt2 << endl;
    }
    outTxt2 << endl;

    TCanvas *cn_mu_M1to0 = new TCanvas("cn_mu_M1to0","cn_mu_M1to0",800,800);
    cn_mu_M1to0->cd();
    /*
    cn_mu_M1to0->SetLeftMargin(0.09);
    cn_mu_M1to0->SetRightMargin(0.11);
    */
    cn_mu_M1to0->SetLogz();
    _h_unfold_mu_M1to0_pt->SetStats(kFALSE);
    _h_unfold_mu_M1to0_pt->GetXaxis()->SetLabelSize(0.025);
    _h_unfold_mu_M1to0_pt->GetYaxis()->SetLabelSize(0.025);
    _h_unfold_mu_M1to0_pt->GetXaxis()->SetTitleOffset(1.2);
    _h_unfold_mu_M1to0_pt->GetYaxis()->SetTitleOffset(1.2);
    _h_unfold_mu_M1to0_pt->Draw("COLZ");
    channel_tex->Draw("same");
    cms_style_bis(false);
    cn_mu_M1to0->SaveAs(outDir+"Migration_Mu_M1to0.C");
    cn_mu_M1to0->SaveAs(outDir+"Migration_Mu_M1to0.eps");
    cn_mu_M1to0->SaveAs(outDir+"Migration_Mu_M1to0.pdf");
    TCanvas *cn_mu_0toP1 = new TCanvas("cn_mu_0toP1","cn_mu_0toP1",800,800);
    cn_mu_0toP1->cd();
    /*
    cn_mu_0toP1->SetLeftMargin(0.09);
    cn_mu_0toP1->SetRightMargin(0.11);
    */
    cn_mu_0toP1->SetLogz();
    _h_unfold_mu_0toP1_pt->SetStats(kFALSE);
    _h_unfold_mu_0toP1_pt->GetXaxis()->SetLabelSize(0.025);
    _h_unfold_mu_0toP1_pt->GetYaxis()->SetLabelSize(0.025);
    _h_unfold_mu_0toP1_pt->GetXaxis()->SetTitleOffset(1.2);
    _h_unfold_mu_0toP1_pt->GetYaxis()->SetTitleOffset(1.2);
    _h_unfold_mu_0toP1_pt->Draw("COLZ");
    channel_tex->Draw("same");
    cms_style_bis(false);
    cn_mu_0toP1->SaveAs(outDir+"Migration_Mu_0toP1.C");
    cn_mu_0toP1->SaveAs(outDir+"Migration_Mu_0toP1.eps");
    cn_mu_0toP1->SaveAs(outDir+"Migration_Mu_0toP1.pdf");

    outRoot->cd();
    _h_unfold_mu_M2p4toM1p5_pt->Write();
    _h_unfold_mu_M1p5toM1_pt->Write();
    _h_unfold_mu_M1to0_pt->Write();
    _h_unfold_mu_0toP1_pt->Write();
    _h_unfold_mu_P1toP1p5_pt->Write();
    _h_unfold_mu_P1p5toP2p4_pt->Write();

    if (!inBatch) getchar();
    
    outTxt2 << endl;
    outTxt2.close();
    outTxt << endl;
    outTxt.close();
    outRoot->Close();
    fiMC->Close();
    delete cn_tr_M2p4toM1p5;
    delete cn_tr_M1p5toM1;
    delete cn_tr_M1to0; 
    delete cn_tr_0toP1; 
    delete cn_tr_P1toP1p5; 
    delete cn_tr_P1p5toP2p4; 
    delete cn_mu_M2p4toM1p5;
    delete cn_mu_M1p5toM1;
    delete cn_mu_M1to0; 
    delete cn_mu_0toP1; 
    delete cn_mu_P1toP1p5; 
    delete cn_mu_P1p5toP2p4; 
    
    return 0;
  } else
    return 1;
    
 }

