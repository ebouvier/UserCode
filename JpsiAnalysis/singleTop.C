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
 * for single-top decay channels
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

  double binSize = h->GetXaxis()->GetBinWidth(1);
  std::stringstream ss;
  ss << "Events / " << std::fixed << std::setprecision(2) << binSize;
  h->GetYaxis()->SetTitle(ss.str().c_str());
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
int singleTop(TString date = "15Dec15", TString version = "SingleTop")
//---------------------------------------------------------------
{
  TH1::SetDefaultSumw2(kTRUE);
  double lumi = 19.7;

  TString indir = date+"/"+version+"/MyAnaAll/"; 

  TFile* fi_T_t       = TFile::Open(indir+"T_t-channel.root");
  TFile* fi_Tbar_t    = TFile::Open(indir+"Tbar_t-channel.root");
  TFile* fi_T_tW      = TFile::Open(indir+"T_tW-channel.root");
  TFile* fi_Tbar_tW   = TFile::Open(indir+"Tbar_tW-channel.root");

  TH1F* good_T_t     = (TH1F*)fi_T_t->Get("MTriLept-goodPair");
  TH1F* all_T_t      = (TH1F*)fi_T_t->Get("MTriLept-allPair");
  TH1F* good_Tbar_t  = (TH1F*)fi_Tbar_t->Get("MTriLept-goodPair");
  TH1F* all_Tbar_t   = (TH1F*)fi_Tbar_t->Get("MTriLept-allPair");
  TH1F* good_T_tW    = (TH1F*)fi_T_tW->Get("MTriLept-goodPair");
  TH1F* all_T_tW     = (TH1F*)fi_T_tW->Get("MTriLept-allPair");
  TH1F* good_Tbar_tW = (TH1F*)fi_Tbar_tW->Get("MTriLept-goodPair");
  TH1F* all_Tbar_tW  = (TH1F*)fi_Tbar_tW->Get("MTriLept-allPair");

  TH1F* good_t  = (TH1F*)good_T_t->Clone(); good_t->SetBinErrorOption(TH1::kPoisson);
  good_t->Add(good_Tbar_t,(56.4*1935072.)/(30.7*3758227.));
  TH1F* all_t   = (TH1F*)all_T_t->Clone(); all_t->SetBinErrorOption(TH1::kPoisson);
  all_t->Add(all_Tbar_t,(56.4*1935072.)/(30.7*3758227.));
  TH1F* good_tW = (TH1F*)good_T_tW->Clone(); good_tW->SetBinErrorOption(TH1::kPoisson);
  good_tW->Add(good_Tbar_tW,493460./497658.);
  TH1F* all_tW  = (TH1F*)all_T_tW->Clone(); all_tW->SetBinErrorOption(TH1::kPoisson);
  all_tW->Add(all_Tbar_tW,493460./497658.);

  good_t->Scale(1./all_t->Integral());
  good_tW->Scale(1./all_tW->Integral());
  all_t->Scale(1./all_t->Integral());
  all_tW->Scale(1./all_tW->Integral());

  h_myStyle(all_t,862,1,862,1001,-1111.,-1111.,510,510,20,862,1.2,0.,"M(J/#psi+l) (GeV)");
  h_myStyle(good_t,862,2,862,1001,-1111.,-1111.,510,510,20,862,1.2,0.,"M(J/#psi+l) (GeV)");
  h_myStyle(all_tW,611,1,611,1001,-1111.,-1111.,510,510,20,611,1.2,0.,"M(J/#psi+l) (GeV)");
  h_myStyle(good_tW,611,2,611,1001,-1111.,-1111.,510,510,20,611,1.2,0.,"M(J/#psi+l) (GeV)");

  TStyle* my_style = createMyStyle();
  my_style->cd();

  TString outdir = date+"/"+version+"/Plots/";
  gROOT->ProcessLine(".! mkdir "+outdir);

  TCanvas *cn = new TCanvas("cn", "cn", 800, 800);
  cn->cd();
  all_t->Draw("e");
  good_t->Draw("esame");
  all_tW->Draw("esame");
  good_tW->Draw("esame");
  TLegend *leg_t = new TLegend(0.58,0.56,0.93,0.68,NULL,"brNDC");
  leg_t->SetTextSize(0.025);
  leg_myStyle(leg_t);
  leg_t->SetHeader("t channel");
  leg_t->AddEntry(all_t,  "all pairings", "l");
  leg_t->AddEntry(good_t, "good pairings", "l");
  leg_t->Draw("same");
  TLegend *leg_tW = new TLegend(0.58,0.68,0.93,0.8,NULL,"brNDC");
  leg_tW->SetTextSize(0.025);
  leg_myStyle(leg_tW);
  leg_tW->SetHeader("tW channel");
  leg_tW->AddEntry(all_tW,  "all pairings", "l");
  leg_tW->AddEntry(good_tW, "good pairings", "l");
  leg_tW->Draw("same");
  TString channel = "e/#mu/ee/#mu#mu/e#mu + Jets channel";
  TLatex* channel_tex = new TLatex(0.58, 0.9, channel);
  channel_tex->SetNDC(true);
  channel_tex->SetTextFont(43);
  channel_tex->SetTextSize(TITLE_FONTSIZE - 6);
  channel_tex->Draw("same");
  cms_myStyle();
  cn->SaveAs(outdir+"singleTopBehavior.C");
  cn->SaveAs(outdir+"singleTopBehavior.pdf");
  cn->SaveAs(outdir+"singleTopBehavior.jpg");
  cn->SaveAs(outdir+"singleTopBehavior.eps");

  return 0;
}
