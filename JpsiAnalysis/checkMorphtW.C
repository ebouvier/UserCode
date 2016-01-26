#include <iomanip>
#include <string>
#include <sstream>

#include "TROOT.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "TLine.h"
#include "TPolyLine.h"
#include "TH1.h"
#include "TF1.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TString.h"
#include "TFitResult.h"
#include "TFile.h"
#include "TTree.h"

#pragma once

#define TITLE_FONTSIZE 26
#define LABEL_FONTSIZE 18

#define LEFT_MARGIN 0.17
#define RIGHT_MARGIN 0.03
#define TOP_MARGIN 0.05
#define BOTTOM_MARGIN 0.13

/*
 * Comparing the 3-prong mass
 * for single-top tW-channel
 * for all the top quark masses
 */

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

void leg_myStyle(TLegend *leg,
    //int text_size = 0.035,
    //int text_font = 43,
    int text_align = 12,
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
    int optstat=0,
    TString xtitle="") {

  h->SetLineWidth(3);
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

  h->GetYaxis()->SetTitle("Events / (10 GeV)");
  h->GetXaxis()->SetTitle(xtitle);
}

void cms_myStyle(double lumi = 19.7,bool isData = false){
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
int checkMorphtW(TString date = "16Jan24", TString version = "Ref")
//---------------------------------------------------------------
{
  TH1::SetDefaultSumw2(kTRUE);
  float lumi = (19705.+19690.)/2.;
  float xsec = 11.1;
  float brDilep   = 0.1071;
  float brSemilep = 0.2206;

  TString indir = date+"/"+version+"/MyAnaAll/"; 

  vector<float> mtop; mtop.push_back(166.5); mtop.push_back(169.5); mtop.push_back(171.5); mtop.push_back(172.5); mtop.push_back(173.5); mtop.push_back(175.5); mtop.push_back(178.5); 
  vector<int> color; color.push_back(419); color.push_back(862); color.push_back(602); color.push_back(56); color.push_back(907); color.push_back(807); color.push_back(800); 

  TFile* fT_tW    = TFile::Open(indir+"T_tW-channel.root");
  TFile* fTbar_tW = TFile::Open(indir+"Tbar_tW-channel.root");

  TH1F* hT_tW    = (TH1F*)fT_tW->Get("MTriLept-allPair");
  TH1F* hTbar_tW = (TH1F*)fTbar_tW->Get("MTriLept-allPair");

  TH1F *hRef = new TH1F("MTriLept-allPair", "MTriLept-allPair", 25, 0., 250.);
  hRef->SetXTitle("M(J/#psi+l) (GeV)");
  hRef->SetYTitle("Events / (10 GeV)");
  hRef->Add(hT_tW, xsec*lumi/497658.);
  hRef->Add(hTbar_tW, xsec*lumi/493460.);
  h_myStyle(hRef,38,1,38,0,0.,5.,510,510,20,38,1.2,0.,"M(J/#psi+l) (GeV)");

  TString outdir = date+"/"+version+"/XcheckMorphtW/";
  gROOT->ProcessLine(".! mkdir "+outdir);

  TStyle* my_style = createMyStyle();
  my_style->cd();
  TString channel = "e/#mu/ee/#mu#mu/e#mu + Jets channel";
  TLatex* channel_tex = new TLatex(0.58, 0.9, channel);
  channel_tex->SetNDC(true);
  channel_tex->SetTextFont(43);
  channel_tex->SetTextSize(TITLE_FONTSIZE - 6);

  TCanvas *cn_172 = new TCanvas("cn_172", "cn_172", 800, 800);
  cn_172->cd();
  TLegend *leg_172 = new TLegend(0.58,0.56,0.93,0.68,NULL,"brNDC");
  leg_172->SetTextSize(0.025);
  leg_myStyle(leg_172);
  leg_172->SetHeader("Single top tW-channel");
  leg_172->AddEntry(hRef, "without morphing", "l");
  hRef->SetBinErrorOption(TH1::kPoisson);
  hRef->Draw("e");

  TCanvas *cn_all = new TCanvas("cn_all", "cn_all", 800, 800);
  cn_all->cd();
  TLegend *leg_all = new TLegend(0.65,0.4,0.9,0.8,NULL,"brNDC");
  leg_all->SetTextSize(0.025);
  leg_myStyle(leg_all);
  leg_all->SetHeader("#splitline{Single top tW-channel}{(morphing)}");

  for (unsigned int itop = 0; itop < mtop.size(); itop++) {

    TFile* fTToDilepton    = TFile::Open(indir+TString::Format("TToDilepton_tW-channel_mass%.1f",mtop[itop]).ReplaceAll(".","_")+".root");
    TFile* fTToThadWlep    = TFile::Open(indir+TString::Format("TToThadWlep_tW-channel_mass%.1f",mtop[itop]).ReplaceAll(".","_")+".root");
    TFile* fTToTlepWhad    = TFile::Open(indir+TString::Format("TToTlepWhad_tW-channel_mass%.1f",mtop[itop]).ReplaceAll(".","_")+".root");
    TFile* fTBarToDilepton = TFile::Open(indir+TString::Format("TBarToDilepton_tW-channel_mass%.1f",mtop[itop]).ReplaceAll(".","_")+".root");
    TFile* fTBarToThadWlep = TFile::Open(indir+TString::Format("TBarToThadWlep_tW-channel_mass%.1f",mtop[itop]).ReplaceAll(".","_")+".root");
    TFile* fTBarToTlepWhad = TFile::Open(indir+TString::Format("TBarToTlepWhad_tW-channel_mass%.1f",mtop[itop]).ReplaceAll(".","_")+".root");

    TH1F* hTToDilepton    = (TH1F*)fTToDilepton->Get("MTriLept-allPair"); 
    TH1F* hTToThadWlep    = (TH1F*)fTToThadWlep->Get("MTriLept-allPair"); 
    TH1F* hTToTlepWhad    = (TH1F*)fTToTlepWhad->Get("MTriLept-allPair"); 
    TH1F* hTBarToDilepton = (TH1F*)fTBarToDilepton->Get("MTriLept-allPair"); 
    TH1F* hTBarToThadWlep = (TH1F*)fTBarToThadWlep->Get("MTriLept-allPair"); 
    TH1F* hTBarToTlepWhad = (TH1F*)fTBarToTlepWhad->Get("MTriLept-allPair"); 

    TH1F *hMorph = new TH1F("MTriLept-allPair", "MTriLept-allPair", 25, 0., 250.);
    hMorph->SetXTitle("M(J/#psi+l) (GeV)");
    hMorph->SetYTitle("Events / (10 GeV)");
    hMorph->Add(hTToDilepton, brDilep*xsec*lumi);
    hMorph->Add(hTToThadWlep, brSemilep*xsec*lumi);
    hMorph->Add(hTToTlepWhad, brSemilep*xsec*lumi);
    hMorph->Add(hTBarToDilepton, brDilep*xsec*lumi);
    hMorph->Add(hTBarToThadWlep, brSemilep*xsec*lumi);
    hMorph->Add(hTBarToTlepWhad, brSemilep*xsec*lumi);
    h_myStyle(hMorph,color[itop],1,color[itop],0,0.,5.,510,510,20,color[itop],1.2,0.,"M(J/#psi+l) (GeV)");

    if (fabs(mtop[itop]-172.5) < 1e-6) {
      cn_172->cd();
      hMorph->Draw("histsame");
      leg_172->AddEntry(hMorph, "with morphing", "l");
    } else {
      cn_all->cd();
      if (itop == 0)
        hMorph->Draw("hist");
      else
        hMorph->Draw("histsame");
      leg_all->AddEntry(hMorph, TString::Format("M_{t} = %4.1f GeV",mtop[itop]), "l");
    }

  }

  cn_172->cd();
  leg_172->Draw("same");
  channel_tex->Draw("same");
  cms_myStyle();
  cn_172->SaveAs(outdir+"MidMT.C");
  cn_172->SaveAs(outdir+"MidMT.pdf");
  cn_172->SaveAs(outdir+"MidMT.jpg");
  cn_172->SaveAs(outdir+"MidMt.eps");

  cn_all->cd();
  leg_all->Draw("same");
  channel_tex->Draw("same");
  cms_myStyle();
  cn_all->SaveAs(outdir+"AllMT.C");
  cn_all->SaveAs(outdir+"AllMT.pdf");
  cn_all->SaveAs(outdir+"AllMT.jpg");
  cn_all->SaveAs(outdir+"AllMt.eps");

  return 0;
}
