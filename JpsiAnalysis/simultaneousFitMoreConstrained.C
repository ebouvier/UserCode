#include <iomanip>
#include <string>
#include <sstream>

#include "TROOT.h"
#include "TArrow.h"
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
#include "RooAbsReal.h"
#include "RooDataHist.h"
#include "RooDataSet.h"
#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooGamma.h"
#include "RooArgList.h"
#include "RooAddPdf.h"
#include "RooPlot.h"
#include "RooFormulaVar.h"
#include "RooConstVar.h"
#include "RooCategory.h"
#include "RooSimultaneous.h"
#include "RooMinuit.h"
#include "RooFitResult.h"
#include "RooMCStudy.h"

#pragma once

#define TITLE_FONTSIZE 26
#define LABEL_FONTSIZE 18

#define LEFT_MARGIN 0.17
#define RIGHT_MARGIN 0.03
#define TOP_MARGIN 0.05
#define BOTTOM_MARGIN 0.13

#define NCPU 8 // keep in mind that other people may want to work

/*
 * Simultaneous fit with a gaussian+gamma unbinned likelihood fit
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
  ss << "Events / " << std::fixed << std::setprecision(2) << binSize;
  h->GetYaxis()->SetTitle(ss.str().c_str());
  h->GetXaxis()->SetTitle(xtitle);
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

void cms_myStyle(double lumi = 19.7,bool isData = true){
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
double *treat(TString outDir, TString inDir, TString fileData, double lumi, TString decay,
    int nevt, double *mtop, double *mtlim, vector<double> mtoys, const unsigned int nsample, bool blind) 
  //---------------------------------------------------------------
{

  using namespace RooFit;
  // reduce RooFit's verbosity on the INFO level
  RooMsgService::instance().getStream(1).removeTopic(Minimization);
  RooMsgService::instance().getStream(1).removeTopic(Plotting);
  RooMsgService::instance().getStream(1).removeTopic(ObjectHandling);
  RooMsgService::instance().getStream(1).removeTopic(Eval);
  RooMsgService::instance().getStream(1).removeTopic(Fitting);
  RooMsgService::instance().setSilentMode(true);
  RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);

  TString channel = " + Jets channel";

  //---- simultaneous fit parameters
  double p0_mean_gaus_i, p0_mean_gaus_c, p0_mean_gaus_s;
  double p1_mean_gaus_i, p1_mean_gaus_c, p1_mean_gaus_s;
  double p0_width_gaus_i, p0_width_gaus_c, p0_width_gaus_s;
  double p1_width_gaus_i, p1_width_gaus_c, p1_width_gaus_s;
  double p0_ncat_i, p0_ncat_c, p0_ncat_s;
  double p0_gamma_gam_i, p0_gamma_gam_c, p0_gamma_gam_s;
  double p0_beta_gam_i, p0_beta_gam_c, p0_beta_gam_s;
  double p0_mu_gam_i, p0_mu_gam_c, p0_mu_gam_s;

  if (fileData.Contains("ElectronHad")) {
    if (decay.Contains("semi", TString::kIgnoreCase))
      channel = "e"+channel;
    if (decay.Contains("di", TString::kIgnoreCase))
      channel = "ee/e#mu"+channel;
    if (decay.Contains("all", TString::kIgnoreCase))
      channel = "e/ee/e#mu"+channel;
    //---- simultaneous fit parameters
    p0_mean_gaus_i = -9.; p0_mean_gaus_c = -7; p0_mean_gaus_s = -5.;
    p1_mean_gaus_i = 0.37; p1_mean_gaus_c = 0.47; p1_mean_gaus_s = 0.57;
    p0_width_gaus_i = -3.; p0_width_gaus_c = -1.; p0_width_gaus_s = 1.;
    p1_width_gaus_i = 0.1; p1_width_gaus_c = 0.12; p1_width_gaus_s = 0.14;
    p0_ncat_i = 0.3; p0_ncat_c = 0.45; p0_ncat_s = 0.6;
    p0_gamma_gam_i = 2.2; p0_gamma_gam_c = 2.6; p0_gamma_gam_s = 3.;
    p0_beta_gam_i = 30.; p0_beta_gam_c = 34.; p0_beta_gam_s = 38.;
    p0_mu_gam_i = 7.; p0_mu_gam_c = 8.5; p0_mu_gam_s = 10.;
  }
  if (fileData.Contains("MuHad")) {
    if (decay.Contains("semi", TString::kIgnoreCase))
      channel = "#mu"+channel;
    if (decay.Contains("di", TString::kIgnoreCase))
      channel = "#mu#mu/#mue"+channel;
    if (decay.Contains("all", TString::kIgnoreCase))
      channel = "#mu/#mu#mu/#mue"+channel;
    //---- simultaneous fit parameters
    p0_mean_gaus_i = -4.; p0_mean_gaus_c = 0.; p0_mean_gaus_s = 4.;
    p1_mean_gaus_i = 0.33; p1_mean_gaus_c = 0.43; p1_mean_gaus_s = 0.53;
    p0_width_gaus_i = -16; p0_width_gaus_c = -8.; p0_width_gaus_s = 0.;
    p1_width_gaus_i = 0.1; p1_width_gaus_c = 0.15; p1_width_gaus_s = 0.2;
    p0_ncat_i = 0.3; p0_ncat_c = 0.45; p0_ncat_s = 0.6;
    p0_gamma_gam_i = 2.3; p0_gamma_gam_c = 2.5; p0_gamma_gam_s = 2.7;
    p0_beta_gam_i = 28.; p0_beta_gam_c = 34.; p0_beta_gam_s = 40.;
    p0_mu_gam_i = 9.; p0_mu_gam_c = 10.5; p0_mu_gam_s = 12.;
  }
  if (fileData.Contains("Run")) {
    if (decay.Contains("semi", TString::kIgnoreCase))
      channel = "e/#mu"+channel;
    if (decay.Contains("di", TString::kIgnoreCase))
      channel = "ee/#mu#mu/e#mu"+channel;
    if (decay.Contains("all", TString::kIgnoreCase))
      channel = "e/#mu/ee/#mu#mu/e#mu"+channel;
    //---- simultaneous fit parameters
    p0_mean_gaus_i = -8.; p0_mean_gaus_c = -2.; p0_mean_gaus_s = 4.;
    p1_mean_gaus_i = 0.34; p1_mean_gaus_c = 0.44; p1_mean_gaus_s = 0.54;
    p0_width_gaus_i = -16; p0_width_gaus_c = -8.; p0_width_gaus_s = 0.;
    p1_width_gaus_i = 0.1; p1_width_gaus_c = 0.15; p1_width_gaus_s = 0.2;
    p0_ncat_i = 0.3; p0_ncat_c = 0.45; p0_ncat_s = 0.6;
    p0_gamma_gam_i = 2.4; p0_gamma_gam_c = 2.55; p0_gamma_gam_s = 2.7;
    p0_beta_gam_i = 28.; p0_beta_gam_c = 34.5; p0_beta_gam_s = 41.;
    p0_mu_gam_i = 8.; p0_mu_gam_c = 9.; p0_mu_gam_s = 10.;
  }

  gROOT->ProcessLine(".! mkdir "+outDir);

  TLatex* channel_tex = new TLatex(0.22, 0.9, channel);
  channel_tex->SetNDC(true);
  channel_tex->SetTextFont(43);
  channel_tex->SetTextSize(TITLE_FONTSIZE - 6);

  vector<double> nentries;

  //=========================
  //    Global variables
  //=========================

  //---- Variables
  RooRealVar mt("mt","M_{t}",173.,mtlim[0],mtlim[1], "GeV");
  RooRealVar mtl("mass", "M_{J/#psi+l}", 0., 250., "GeV");
  RooRealVar weight("weight", "weight", 0., 2.);

  //---- Parametrization
  RooRealVar p0_mean_gaus("p0_mean_gaus","p0_mean_gaus",p0_mean_gaus_c,p0_mean_gaus_i,p0_mean_gaus_s);
  RooRealVar p1_mean_gaus("p1_mean_gaus","p1_mean_gaus",p1_mean_gaus_c,p1_mean_gaus_i,p1_mean_gaus_s);
  RooRealVar p0_width_gaus("p0_width_gaus","p0_width_gaus",p0_width_gaus_c,p0_width_gaus_i,p0_width_gaus_s);
  RooRealVar p1_width_gaus("p1_width_gaus","p1_width_gaus",p1_width_gaus_c,p1_width_gaus_i,p1_width_gaus_s);
  RooRealVar p0_ncat("p0_ncat","p0_ncat",p0_ncat_c,p0_ncat_i,p0_ncat_s);
  RooConstVar p1_ncat("p1_ncat","p1_ncat",0.);
  RooRealVar p0_gamma_gam("p0_gamma_gam","p0_gamma_gam",p0_gamma_gam_c,p0_gamma_gam_i,p0_gamma_gam_s);
  RooConstVar p1_gamma_gam("p1_gamma_gam","p1_gamma_gam",0.);
  RooRealVar p0_beta_gam("p0_beta_gam","p0_beta_gam",p0_beta_gam_c,p0_beta_gam_i,p0_beta_gam_s);
  RooConstVar p1_beta_gam("p1_beta_gam","p1_beta_gam",0.);
  RooRealVar p0_mu_gam("p0_mu_gam","p0_mu_gam",p0_mu_gam_c,p0_mu_gam_i,p0_mu_gam_s);
  RooConstVar p1_mu_gam("p1_mu_gam","p1_mu_gam",0.);

  RooCategory mc_sample("mc_sample","mc_sample") ;


  //=========================
  //    PDF for each mtop
  //=========================

  RooConstVar mt_0("mt_0","mt_0",mtop[0]);
  TFile *fi_0 = TFile::Open(inDir+TString::Format("All_%d_5.root",(int)floor(mtop[0])));
  TTree *tree_0 = (TTree*)fi_0->Get("MTriLept");
  nentries.push_back(tree_0->GetEntries());
  RooDataSet *dataset_0 = new RooDataSet("dataset_0", "dataset_0", RooArgSet(mtl, weight), Import(*tree_0), WeightVar(weight));
  mc_sample.defineType("mt0");

  RooFormulaVar mean_gaus_0("mean_gaus_0","@0+@1*@2",RooArgList(p0_mean_gaus,p1_mean_gaus,mt_0));
  RooFormulaVar width_gaus_0("width_gaus_0","@0+@1*@2",RooArgList(p0_width_gaus,p1_width_gaus,mt_0));
  RooFormulaVar ncat_0("ncat_0","@0+@1*@2",RooArgList(p0_ncat,p1_ncat,mt_0));
  RooFormulaVar gamma_gam_0("gamma_gam_0","@0+@1*@2",RooArgList(p0_gamma_gam,p1_gamma_gam,mt_0));
  RooFormulaVar beta_gam_0("beta_gam_0","@0+@1*@2",RooArgList(p0_beta_gam,p1_beta_gam,mt_0));
  RooFormulaVar mu_gam_0("mu_gam_0","@0+@1*@2",RooArgList(p0_mu_gam,p1_mu_gam,mt_0));

  RooGaussian pdf_gaus_0("pdf_gaus_0","pdf_gaus_0",mtl,mean_gaus_0,width_gaus_0);
  RooGamma pdf_gam_0("pdf_gam_0","pdf_gam_0",mtl,gamma_gam_0,beta_gam_0,mu_gam_0);
  RooAddPdf model_0("model_0","model_0",RooArgList(pdf_gaus_0,pdf_gam_0),RooArgList(ncat_0)) ;


  RooConstVar mt_1("mt_1","mt_1",mtop[1]);
  TFile *fi_1 = TFile::Open(inDir+TString::Format("All_%d_5.root",(int)floor(mtop[1])));
  TTree *tree_1 = (TTree*)fi_1->Get("MTriLept");
  nentries.push_back(tree_1->GetEntries());
  RooDataSet *dataset_1 = new RooDataSet("dataset_1", "dataset_1", RooArgSet(mtl, weight), Import(*tree_1), WeightVar(weight));
  mc_sample.defineType("mt1");

  RooFormulaVar mean_gaus_1("mean_gaus_1","@0+@1*@2",RooArgList(p0_mean_gaus,p1_mean_gaus,mt_1));
  RooFormulaVar width_gaus_1("width_gaus_1","@0+@1*@2",RooArgList(p0_width_gaus,p1_width_gaus,mt_1));
  RooFormulaVar ncat_1("ncat_1","@0+@1*@2",RooArgList(p0_ncat,p1_ncat,mt_1));
  RooFormulaVar gamma_gam_1("gamma_gam_1","@0+@1*@2",RooArgList(p0_gamma_gam,p1_gamma_gam,mt_1));
  RooFormulaVar beta_gam_1("beta_gam_1","@0+@1*@2",RooArgList(p0_beta_gam,p1_beta_gam,mt_1));
  RooFormulaVar mu_gam_1("mu_gam_1","@0+@1*@2",RooArgList(p0_mu_gam,p1_mu_gam,mt_1));

  RooGaussian pdf_gaus_1("pdf_gaus_1","pdf_gaus_1",mtl,mean_gaus_1,width_gaus_1);
  RooGamma pdf_gam_1("pdf_gam_1","pdf_gam_1",mtl,gamma_gam_1,beta_gam_1,mu_gam_1);
  RooAddPdf model_1("model_1","model_1",RooArgList(pdf_gaus_1,pdf_gam_1),RooArgList(ncat_1)) ;


  RooConstVar mt_2("mt_2","mt_2",mtop[2]);
  TFile *fi_2 = TFile::Open(inDir+TString::Format("All_%d_5.root",(int)floor(mtop[2])));
  TTree *tree_2 = (TTree*)fi_2->Get("MTriLept");
  nentries.push_back(tree_2->GetEntries());
  RooDataSet *dataset_2 = new RooDataSet("dataset_2", "dataset_2", RooArgSet(mtl, weight), Import(*tree_2), WeightVar(weight));
  mc_sample.defineType("mt2");

  RooFormulaVar mean_gaus_2("mean_gaus_2","@0+@1*@2",RooArgList(p0_mean_gaus,p1_mean_gaus,mt_2));
  RooFormulaVar width_gaus_2("width_gaus_2","@0+@1*@2",RooArgList(p0_width_gaus,p1_width_gaus,mt_2));
  RooFormulaVar ncat_2("ncat_2","@0+@1*@2",RooArgList(p0_ncat,p1_ncat,mt_2));
  RooFormulaVar gamma_gam_2("gamma_gam_2","@0+@1*@2",RooArgList(p0_gamma_gam,p1_gamma_gam,mt_2));
  RooFormulaVar beta_gam_2("beta_gam_2","@0+@1*@2",RooArgList(p0_beta_gam,p1_beta_gam,mt_2));
  RooFormulaVar mu_gam_2("mu_gam_2","@0+@1*@2",RooArgList(p0_mu_gam,p1_mu_gam,mt_2));

  RooGaussian pdf_gaus_2("pdf_gaus_2","pdf_gaus_2",mtl,mean_gaus_2,width_gaus_2);
  RooGamma pdf_gam_2("pdf_gam_2","pdf_gam_2",mtl,gamma_gam_2,beta_gam_2,mu_gam_2);
  RooAddPdf model_2("model_2","model_2",RooArgList(pdf_gaus_2,pdf_gam_2),RooArgList(ncat_2)) ;


  RooConstVar mt_3("mt_3","mt_3",mtop[3]);
  TFile *fi_3 = TFile::Open(inDir+TString::Format("All_%d_5.root",(int)floor(mtop[3])));
  TTree *tree_3 = (TTree*)fi_3->Get("MTriLept");
  nentries.push_back(tree_3->GetEntries());
  RooDataSet *dataset_3 = new RooDataSet("dataset_3", "dataset_3", RooArgSet(mtl, weight), Import(*tree_3), WeightVar(weight));
  mc_sample.defineType("mt3");

  RooFormulaVar mean_gaus_3("mean_gaus_3","@0+@1*@2",RooArgList(p0_mean_gaus,p1_mean_gaus,mt_3));
  RooFormulaVar width_gaus_3("width_gaus_3","@0+@1*@2",RooArgList(p0_width_gaus,p1_width_gaus,mt_3));
  RooFormulaVar ncat_3("ncat_3","@0+@1*@2",RooArgList(p0_ncat,p1_ncat,mt_3));
  RooFormulaVar gamma_gam_3("gamma_gam_3","@0+@1*@2",RooArgList(p0_gamma_gam,p1_gamma_gam,mt_3));
  RooFormulaVar beta_gam_3("beta_gam_3","@0+@1*@2",RooArgList(p0_beta_gam,p1_beta_gam,mt_3));
  RooFormulaVar mu_gam_3("mu_gam_3","@0+@1*@2",RooArgList(p0_mu_gam,p1_mu_gam,mt_3));

  RooGaussian pdf_gaus_3("pdf_gaus_3","pdf_gaus_3",mtl,mean_gaus_3,width_gaus_3);
  RooGamma pdf_gam_3("pdf_gam_3","pdf_gam_3",mtl,gamma_gam_3,beta_gam_3,mu_gam_3);
  RooAddPdf model_3("model_3","model_3",RooArgList(pdf_gaus_3,pdf_gam_3),RooArgList(ncat_3)) ;


  RooConstVar mt_4("mt_4","mt_4",mtop[4]);
  TFile *fi_4 = TFile::Open(inDir+TString::Format("All_%d_5.root",(int)floor(mtop[4])));
  TTree *tree_4 = (TTree*)fi_4->Get("MTriLept");
  nentries.push_back(tree_4->GetEntries());
  RooDataSet *dataset_4 = new RooDataSet("dataset_4", "dataset_4", RooArgSet(mtl, weight), Import(*tree_4), WeightVar(weight));
  mc_sample.defineType("mt4");

  RooFormulaVar mean_gaus_4("mean_gaus_4","@0+@1*@2",RooArgList(p0_mean_gaus,p1_mean_gaus,mt_4));
  RooFormulaVar width_gaus_4("width_gaus_4","@0+@1*@2",RooArgList(p0_width_gaus,p1_width_gaus,mt_4));
  RooFormulaVar ncat_4("ncat_4","@0+@1*@2",RooArgList(p0_ncat,p1_ncat,mt_4));
  RooFormulaVar gamma_gam_4("gamma_gam_4","@0+@1*@2",RooArgList(p0_gamma_gam,p1_gamma_gam,mt_4));
  RooFormulaVar beta_gam_4("beta_gam_4","@0+@1*@2",RooArgList(p0_beta_gam,p1_beta_gam,mt_4));
  RooFormulaVar mu_gam_4("mu_gam_4","@0+@1*@2",RooArgList(p0_mu_gam,p1_mu_gam,mt_4));

  RooGaussian pdf_gaus_4("pdf_gaus_4","pdf_gaus_4",mtl,mean_gaus_4,width_gaus_4);
  RooGamma pdf_gam_4("pdf_gam_4","pdf_gam_4",mtl,gamma_gam_4,beta_gam_4,mu_gam_4);
  RooAddPdf model_4("model_4","model_4",RooArgList(pdf_gaus_4,pdf_gam_4),RooArgList(ncat_4)) ;


  RooConstVar mt_5("mt_5","mt_5",mtop[5]);
  TFile *fi_5 = TFile::Open(inDir+TString::Format("All_%d_5.root",(int)floor(mtop[5])));
  TTree *tree_5 = (TTree*)fi_5->Get("MTriLept");
  nentries.push_back(tree_5->GetEntries());
  RooDataSet *dataset_5 = new RooDataSet("dataset_5", "dataset_5", RooArgSet(mtl, weight), Import(*tree_5), WeightVar(weight));
  mc_sample.defineType("mt5");

  RooFormulaVar mean_gaus_5("mean_gaus_5","@0+@1*@2",RooArgList(p0_mean_gaus,p1_mean_gaus,mt_5));
  RooFormulaVar width_gaus_5("width_gaus_5","@0+@1*@2",RooArgList(p0_width_gaus,p1_width_gaus,mt_5));
  RooFormulaVar ncat_5("ncat_5","@0+@1*@2",RooArgList(p0_ncat,p1_ncat,mt_5));
  RooFormulaVar gamma_gam_5("gamma_gam_5","@0+@1*@2",RooArgList(p0_gamma_gam,p1_gamma_gam,mt_5));
  RooFormulaVar beta_gam_5("beta_gam_5","@0+@1*@2",RooArgList(p0_beta_gam,p1_beta_gam,mt_5));
  RooFormulaVar mu_gam_5("mu_gam_5","@0+@1*@2",RooArgList(p0_mu_gam,p1_mu_gam,mt_5));

  RooGaussian pdf_gaus_5("pdf_gaus_5","pdf_gaus_5",mtl,mean_gaus_5,width_gaus_5);
  RooGamma pdf_gam_5("pdf_gam_5","pdf_gam_5",mtl,gamma_gam_5,beta_gam_5,mu_gam_5);
  RooAddPdf model_5("model_5","model_5",RooArgList(pdf_gaus_5,pdf_gam_5),RooArgList(ncat_5)) ;


  //=========================
  //    Simultaneous fit
  //=========================

  RooDataSet combMC("combMC","combined mc",mtl,Index(mc_sample),Import("m0",*dataset_0),Import("m1",*dataset_1),Import("m2",*dataset_2),Import("m3",*dataset_3),Import("m4",*dataset_4),Import("m5",*dataset_5)) ;

  RooSimultaneous simPdf("simPdf","simultaneous pdf",mc_sample);
  simPdf.addPdf(model_0,"m0");
  simPdf.addPdf(model_1,"m1");
  simPdf.addPdf(model_2,"m2");
  simPdf.addPdf(model_3,"m3");
  simPdf.addPdf(model_4,"m4");
  simPdf.addPdf(model_5,"m5");

  RooAbsReal* simNll = simPdf.createNLL(combMC, NumCPU(NCPU), SumW2Error(kTRUE));
  RooMinuit minuit_mc(*simNll);
  minuit_mc.setPrintLevel(-1); 
  minuit_mc.setPrintEvalErrors(-1);
  minuit_mc.migrad();
  minuit_mc.hesse();
  //minuit_mc.minos(); //optional
  RooFitResult *simRes = minuit_mc.save();

  double cor_mean_gaus = simRes->correlation("p0_mean_gaus","p1_mean_gaus"); 
  double cor_width_gaus = simRes->correlation("p0_width_gaus","p1_width_gaus"); 
  double cor_ncat = simRes->correlation("p0_ncat","p1_ncat"); 
  double cor_gamma_gam = simRes->correlation("p0_gamma_gam","p1_gamma_gam"); 
  double cor_beta_gam = simRes->correlation("p0_beta_gam","p1_beta_gam"); 
  double cor_mu_gam = simRes->correlation("p0_mu_gam","p1_mu_gam"); 


  //=========================
  //    Plot pdf result
  //=========================

  TCanvas *cn_0 = new TCanvas("cn_pdf_mc_0","cn_pdf_mc_0",800,800);
  cn_0->cd();
  RooPlot* frame_0 = mtl.frame() ;
  combMC.plotOn(frame_0,Cut("mc_sample==mc_sample::m0"),Binning(50), DataError(RooAbsData::SumW2)) ;
  simPdf.plotOn(frame_0,Slice(mc_sample,"m0"),ProjWData(mc_sample,combMC),FillColor(38),VisualizeError(*simRes)) ;
  simPdf.plotOn(frame_0,Slice(mc_sample,"m0"),ProjWData(mc_sample,combMC),LineColor(9)) ;
  simPdf.plotOn(frame_0,Slice(mc_sample,"m0"),Components(pdf_gam_0),ProjWData(mc_sample,combMC),LineStyle(kDashed),LineColor(kBlue));
  simPdf.plotOn(frame_0,Slice(mc_sample,"m0"),Components(pdf_gaus_0),ProjWData(mc_sample,combMC),LineStyle(kDashed),LineColor(kRed));
  frame_0->Draw();
  TLegend *leg_0 = new TLegend(0.58,0.82,0.9,0.9,NULL,"brNDC");
  leg_0->SetHeader(TString::Format("M_{t} = %4.1f GeV",mtop[0]));
  leg_0->SetTextSize(0.035);
  leg_myStyle(leg_0);
  leg_0->Draw("same");
  channel_tex->Draw("same");
  cms_myStyle(lumi, false);
  TString out_0 = outDir+TString::Format("Pdf_%d_5", (int)mtop[0]);
  cn_0->SaveAs(out_0+".pdf");
  cn_0->SaveAs(out_0+".C");
  cn_0->SaveAs(out_0+".jpg");
  cn_0->SaveAs(out_0+".eps");

  TCanvas *cn_1 = new TCanvas("cn_pdf_mc_1","cn_pdf_mc_1",800,800);
  cn_1->cd();
  RooPlot* frame_1 = mtl.frame() ;
  combMC.plotOn(frame_1,Cut("mc_sample==mc_sample::m1"),Binning(50), DataError(RooAbsData::SumW2)) ;
  simPdf.plotOn(frame_1,Slice(mc_sample,"m1"),ProjWData(mc_sample,combMC),FillColor(38),VisualizeError(*simRes)) ;
  simPdf.plotOn(frame_1,Slice(mc_sample,"m1"),ProjWData(mc_sample,combMC),LineColor(9)) ;
  simPdf.plotOn(frame_1,Slice(mc_sample,"m1"),Components(pdf_gam_1),ProjWData(mc_sample,combMC),LineStyle(kDashed),LineColor(kBlue));
  simPdf.plotOn(frame_1,Slice(mc_sample,"m1"),Components(pdf_gaus_1),ProjWData(mc_sample,combMC),LineStyle(kDashed),LineColor(kRed));
  frame_1->Draw();
  TLegend *leg_1 = new TLegend(0.58,0.82,0.9,0.9,NULL,"brNDC");
  leg_1->SetHeader(TString::Format("M_{t} = %4.1f GeV",mtop[1]));
  leg_1->SetTextSize(0.035);
  leg_myStyle(leg_1);
  leg_1->Draw("same");
  channel_tex->Draw("same");
  cms_myStyle(lumi, false);
  TString out_1 = outDir+TString::Format("Pdf_%d_5", (int)mtop[1]);
  cn_1->SaveAs(out_1+".pdf");
  cn_1->SaveAs(out_1+".C");
  cn_1->SaveAs(out_1+".jpg");
  cn_1->SaveAs(out_1+".eps");

  TCanvas *cn_2 = new TCanvas("cn_pdf_mc_2","cn_pdf_mc_2",800,800);
  cn_2->cd();
  RooPlot* frame_2 = mtl.frame() ;
  combMC.plotOn(frame_2,Cut("mc_sample==mc_sample::m2"),Binning(50), DataError(RooAbsData::SumW2)) ;
  simPdf.plotOn(frame_2,Slice(mc_sample,"m2"),ProjWData(mc_sample,combMC),FillColor(38),VisualizeError(*simRes)) ;
  simPdf.plotOn(frame_2,Slice(mc_sample,"m2"),ProjWData(mc_sample,combMC),LineColor(9)) ;
  simPdf.plotOn(frame_2,Slice(mc_sample,"m2"),Components(pdf_gam_2),ProjWData(mc_sample,combMC),LineStyle(kDashed),LineColor(kBlue));
  simPdf.plotOn(frame_2,Slice(mc_sample,"m2"),Components(pdf_gaus_2),ProjWData(mc_sample,combMC),LineStyle(kDashed),LineColor(kRed));
  frame_2->Draw();
  TLegend *leg_2 = new TLegend(0.58,0.82,0.9,0.9,NULL,"brNDC");
  leg_2->SetHeader(TString::Format("M_{t} = %4.1f GeV",mtop[2]));
  leg_2->SetTextSize(0.035);
  leg_myStyle(leg_2);
  leg_2->Draw("same");
  channel_tex->Draw("same");
  cms_myStyle(lumi, false);
  TString out_2 = outDir+TString::Format("Pdf_%d_5", (int)mtop[2]);
  cn_2->SaveAs(out_2+".pdf");
  cn_2->SaveAs(out_2+".C");
  cn_2->SaveAs(out_2+".jpg");
  cn_2->SaveAs(out_2+".eps");

  TCanvas *cn_3 = new TCanvas("cn_pdf_mc_3","cn_pdf_mc_3",800,800);
  cn_3->cd();
  RooPlot* frame_3 = mtl.frame() ;
  combMC.plotOn(frame_3,Cut("mc_sample==mc_sample::m3"),Binning(50), DataError(RooAbsData::SumW2)) ;
  simPdf.plotOn(frame_3,Slice(mc_sample,"m3"),ProjWData(mc_sample,combMC),FillColor(38),VisualizeError(*simRes)) ;
  simPdf.plotOn(frame_3,Slice(mc_sample,"m3"),ProjWData(mc_sample,combMC),LineColor(9)) ;
  simPdf.plotOn(frame_3,Slice(mc_sample,"m3"),Components(pdf_gam_3),ProjWData(mc_sample,combMC),LineStyle(kDashed),LineColor(kBlue));
  simPdf.plotOn(frame_3,Slice(mc_sample,"m3"),Components(pdf_gaus_3),ProjWData(mc_sample,combMC),LineStyle(kDashed),LineColor(kRed));
  frame_3->Draw();
  TLegend *leg_3 = new TLegend(0.58,0.82,0.9,0.9,NULL,"brNDC");
  leg_3->SetHeader(TString::Format("M_{t} = %4.1f GeV",mtop[3]));
  leg_3->SetTextSize(0.035);
  leg_myStyle(leg_3);
  leg_3->Draw("same");
  channel_tex->Draw("same");
  cms_myStyle(lumi, false);
  TString out_3 = outDir+TString::Format("Pdf_%d_5", (int)mtop[3]);
  cn_3->SaveAs(out_3+".pdf");
  cn_3->SaveAs(out_3+".C");
  cn_3->SaveAs(out_3+".jpg");
  cn_3->SaveAs(out_3+".eps");

  TCanvas *cn_4 = new TCanvas("cn_pdf_mc_4","cn_pdf_mc_4",800,800);
  cn_4->cd();
  RooPlot* frame_4 = mtl.frame() ;
  combMC.plotOn(frame_4,Cut("mc_sample==mc_sample::m4"),Binning(50), DataError(RooAbsData::SumW2)) ;
  simPdf.plotOn(frame_4,Slice(mc_sample,"m4"),ProjWData(mc_sample,combMC),FillColor(38),VisualizeError(*simRes)) ;
  simPdf.plotOn(frame_4,Slice(mc_sample,"m4"),ProjWData(mc_sample,combMC),LineColor(9)) ;
  simPdf.plotOn(frame_4,Slice(mc_sample,"m4"),Components(pdf_gam_4),ProjWData(mc_sample,combMC),LineStyle(kDashed),LineColor(kBlue));
  simPdf.plotOn(frame_4,Slice(mc_sample,"m4"),Components(pdf_gaus_4),ProjWData(mc_sample,combMC),LineStyle(kDashed),LineColor(kRed));
  frame_4->Draw();
  TLegend *leg_4 = new TLegend(0.58,0.82,0.9,0.9,NULL,"brNDC");
  leg_4->SetHeader(TString::Format("M_{t} = %4.1f GeV",mtop[4]));
  leg_4->SetTextSize(0.035);
  leg_myStyle(leg_4);
  leg_4->Draw("same");
  channel_tex->Draw("same");
  cms_myStyle(lumi, false);
  TString out_4 = outDir+TString::Format("Pdf_%d_5", (int)mtop[4]);
  cn_4->SaveAs(out_4+".pdf");
  cn_4->SaveAs(out_4+".C");
  cn_4->SaveAs(out_4+".jpg");
  cn_4->SaveAs(out_4+".eps");

  TCanvas *cn_5 = new TCanvas("cn_pdf_mc_5","cn_pdf_mc_5",800,800);
  cn_5->cd();
  RooPlot* frame_5 = mtl.frame() ;
  combMC.plotOn(frame_5,Cut("mc_sample==mc_sample::m5"),Binning(50), DataError(RooAbsData::SumW2)) ;
  simPdf.plotOn(frame_5,Slice(mc_sample,"m5"),ProjWData(mc_sample,combMC),FillColor(38),VisualizeError(*simRes)) ;
  simPdf.plotOn(frame_5,Slice(mc_sample,"m5"),ProjWData(mc_sample,combMC),LineColor(9)) ;
  simPdf.plotOn(frame_5,Slice(mc_sample,"m5"),Components(pdf_gam_5),ProjWData(mc_sample,combMC),LineStyle(kDashed),LineColor(kBlue));
  simPdf.plotOn(frame_5,Slice(mc_sample,"m5"),Components(pdf_gaus_5),ProjWData(mc_sample,combMC),LineStyle(kDashed),LineColor(kRed));
  frame_5->Draw();
  TLegend *leg_5 = new TLegend(0.58,0.82,0.9,0.9,NULL,"brNDC");
  leg_5->SetHeader(TString::Format("M_{t} = %4.1f GeV",mtop[5]));
  leg_5->SetTextSize(0.035);
  leg_myStyle(leg_5);
  leg_5->Draw("same");
  channel_tex->Draw("same");
  cms_myStyle(lumi, false);
  TString out_5 = outDir+TString::Format("Pdf_%d_5", (int)mtop[5]);
  cn_5->SaveAs(out_5+".pdf");
  cn_5->SaveAs(out_5+".C");
  cn_5->SaveAs(out_5+".jpg");
  cn_5->SaveAs(out_5+".eps");

  TCanvas *cn_comp = new TCanvas("cn_comp","cn_comp",800,800);
  cn_comp->cd();
  RooPlot* frame_comp = mtl.frame();
  model_0.plotOn(frame_comp,LineColor(419),Name("model0"));
  model_1.plotOn(frame_comp,LineColor(862),Name("model1"));
  model_2.plotOn(frame_comp,LineColor(602),Name("model2"));
  model_3.plotOn(frame_comp,LineColor(907),Name("model3"));
  model_4.plotOn(frame_comp,LineColor(807),Name("model4"));
  model_5.plotOn(frame_comp,LineColor(800),Name("model5"));
  frame_comp->SetYTitle("P_{sig}");
  frame_comp->Draw();
  TLegend *leg_comp = new TLegend(0.55,0.5,0.9,0.9,NULL,"brNDC");
  leg_comp->SetTextSize(0.035);
  leg_comp->AddEntry(frame_comp->findObject("model0"), TString::Format("M_{t} = %4.1f GeV",mtop[0]), "l");
  leg_comp->AddEntry(frame_comp->findObject("model1"), TString::Format("M_{t} = %4.1f GeV",mtop[1]), "l");
  leg_comp->AddEntry(frame_comp->findObject("model2"), TString::Format("M_{t} = %4.1f GeV",mtop[2]), "l");
  leg_comp->AddEntry(frame_comp->findObject("model3"), TString::Format("M_{t} = %4.1f GeV",mtop[3]), "l");
  leg_comp->AddEntry(frame_comp->findObject("model4"), TString::Format("M_{t} = %4.1f GeV",mtop[4]), "l");
  leg_comp->AddEntry(frame_comp->findObject("model5"), TString::Format("M_{t} = %4.1f GeV",mtop[5]), "l");
  leg_myStyle(leg_comp);
  leg_comp->Draw("same");
  channel_tex->Draw("same");
  cms_myStyle(lumi, false);
  TString out_comp = outDir+"Pdf_All";
  cn_comp->SaveAs(out_comp+".pdf");
  cn_comp->SaveAs(out_comp+".C");
  cn_comp->SaveAs(out_comp+".jpg");
  cn_comp->SaveAs(out_comp+".eps");

  //==========================
  //    Parametrization
  //==========================

  const unsigned int npoints = 460;
  double x[npoints];
  for (unsigned int i = 0; i < npoints; i++) x[i] = mtlim[0] + (mtlim[1]-mtlim[0])*(double)i/(double)npoints;

  TCanvas *cn_par_0 = new TCanvas("cn_par_0","cn_par_0",800,800);
  cn_par_0->cd();
  double y_mean_gaus[npoints]; double yi_mean_gaus[npoints]; double ys_mean_gaus[npoints];
  for (unsigned int i = 0; i < npoints; i++) {
    y_mean_gaus[i] = p0_mean_gaus.getVal() + p1_mean_gaus.getVal()*x[i];
    yi_mean_gaus[i] = y_mean_gaus[i] - sqrt(pow(p0_mean_gaus.getError(),2.)+2.*p0_mean_gaus.getError()*p1_mean_gaus.getError()*cor_mean_gaus*x[i]+pow(p1_mean_gaus.getError()*x[i],2.));
    ys_mean_gaus[i] = y_mean_gaus[i] + sqrt(pow(p0_mean_gaus.getError(),2.)+2.*p0_mean_gaus.getError()*p1_mean_gaus.getError()*cor_mean_gaus*x[i]+pow(p1_mean_gaus.getError()*x[i],2.));
  }
  TGraph *gr_mean_gaus = new TGraph(npoints,x,y_mean_gaus);
  gr_mean_gaus->Fit("pol1","Q","");
  TF1 *fit_mean_gaus = gr_mean_gaus->GetFunction("pol1");
  fit_mean_gaus->SetLineColor(9);
  TGraph *gr_mean_gaus_i = new TGraph(npoints,x,yi_mean_gaus);
  gr_mean_gaus_i->Fit("pol2","Q","");
  TF1 *fit_mean_gaus_i = gr_mean_gaus_i->GetFunction("pol2");
  TGraph *gr_mean_gaus_s = new TGraph(npoints,x,ys_mean_gaus);
  gr_mean_gaus_s->Fit("pol2","Q","");
  TF1 *fit_mean_gaus_s = gr_mean_gaus_s->GetFunction("pol2");
  gr_myStyle(gr_mean_gaus,"gr_mean_gaus",1,9,1,9,1001,40.,110.,510,510,20,9,0.1,"M_{t} (GeV)","#mu (GeV)");
  gr_mean_gaus->Draw("AP");
  fit_mean_gaus_i->SetLineColor(38); fit_mean_gaus_i->SetLineStyle(2); fit_mean_gaus_i->SetLineWidth(2);
  fit_mean_gaus_i->Draw("same");
  fit_mean_gaus_s->SetLineColor(38); fit_mean_gaus_s->SetLineStyle(2); fit_mean_gaus_s->SetLineWidth(2);
  fit_mean_gaus_s->Draw("same");
  gr_mean_gaus->GetXaxis()->SetRangeUser(mtlim[0],mtlim[1]);
  TLegend *leg_par_0 = new TLegend(0.3,0.78,0.85,0.88,NULL,"brNDC");
  leg_par_0->SetTextSize(0.035);
  leg_par_0->SetHeader("Mean of the Gaussian");
  leg_par_0->AddEntry(gr_mean_gaus, TString::Format("#mu = %2.0f + %2.2f#upointM_{t}",p0_mean_gaus.getVal(),p1_mean_gaus.getVal()), "l");
  leg_myStyle(leg_par_0);
  leg_par_0->Draw("same");
  channel_tex->Draw("same");
  cms_myStyle(lumi, false);
  TString out_par_0 = outDir+"Parameter_gaussian_mean";
  cn_par_0->SaveAs(out_par_0+".pdf");
  cn_par_0->SaveAs(out_par_0+".C");
  cn_par_0->SaveAs(out_par_0+".jpg");
  cn_par_0->SaveAs(out_par_0+".eps");

  TCanvas *cn_par_1 = new TCanvas("cn_par_1","cn_par_1",800,800);
  cn_par_1->cd();
  double y_width_gaus[npoints]; double yi_width_gaus[npoints]; double ys_width_gaus[npoints];
  for (unsigned int i = 0; i < npoints; i++) {
    y_width_gaus[i] = p0_width_gaus.getVal() + p1_width_gaus.getVal()*x[i];
    yi_width_gaus[i] = y_width_gaus[i] - sqrt(pow(p0_width_gaus.getError(),2.)+2.*p0_width_gaus.getError()*p1_width_gaus.getError()*cor_width_gaus*x[i]+pow(p1_width_gaus.getError()*x[i],2.));
    ys_width_gaus[i] = y_width_gaus[i] + sqrt(pow(p0_width_gaus.getError(),2.)+2.*p0_width_gaus.getError()*p1_width_gaus.getError()*cor_width_gaus*x[i]+pow(p1_width_gaus.getError()*x[i],2.));
  }
  TGraph *gr_width_gaus = new TGraph(npoints,x,y_width_gaus);
  gr_width_gaus->Fit("pol1","Q","");
  TF1 *fit_width_gaus = gr_width_gaus->GetFunction("pol1");
  fit_width_gaus->SetLineColor(9);
  TGraph *gr_width_gaus_i = new TGraph(npoints,x,yi_width_gaus);
  gr_width_gaus_i->Fit("pol2","Q","");
  TF1 *fit_width_gaus_i = gr_width_gaus_i->GetFunction("pol2");
  TGraph *gr_width_gaus_s = new TGraph(npoints,x,ys_width_gaus);
  gr_width_gaus_s->Fit("pol2","Q","");
  TF1 *fit_width_gaus_s = gr_width_gaus_s->GetFunction("pol2");
  gr_myStyle(gr_width_gaus,"gr_width_gaus",1,9,1,9,1001,10.,30.,510,510,20,9,0.1,"M_{t} (GeV)","#sigma (GeV)");
  gr_width_gaus->Draw("AP");
  fit_width_gaus_i->SetLineColor(38); fit_width_gaus_i->SetLineStyle(2); fit_width_gaus_i->SetLineWidth(2);
  fit_width_gaus_i->Draw("same");
  fit_width_gaus_s->SetLineColor(38); fit_width_gaus_s->SetLineStyle(2); fit_width_gaus_s->SetLineWidth(2);
  fit_width_gaus_s->Draw("same");
  gr_width_gaus->GetXaxis()->SetRangeUser(mtlim[0],mtlim[1]);
  TLegend *leg_par_1 = new TLegend(0.3,0.78,0.85,0.88,NULL,"brNDC");
  leg_par_1->SetTextSize(0.035);
  leg_par_1->SetHeader("Width of the Gaussian");
  leg_par_1->AddEntry(gr_width_gaus, TString::Format("#sigma = %2.0f + %2.2f#upointM_{t}",p0_width_gaus.getVal(),p1_width_gaus.getVal()), "l");
  leg_myStyle(leg_par_1);
  leg_par_1->Draw("same");
  channel_tex->Draw("same");
  cms_myStyle(lumi, false);
  TString out_par_1 = outDir+"Parameter_gaussian_width";
  cn_par_1->SaveAs(out_par_1+".pdf");
  cn_par_1->SaveAs(out_par_1+".C");
  cn_par_1->SaveAs(out_par_1+".jpg");
  cn_par_1->SaveAs(out_par_1+".eps");

  TCanvas *cn_par_2 = new TCanvas("cn_par_2","cn_par_2",800,800);
  cn_par_2->cd();
  double y_ncat[npoints]; double yi_ncat[npoints]; double ys_ncat[npoints];
  for (unsigned int i = 0; i < npoints; i++) {
    y_ncat[i] = p0_ncat.getVal() + p1_ncat.getVal()*x[i];
    yi_ncat[i] = y_ncat[i] - sqrt(pow(p0_ncat.getError(),2.));
    ys_ncat[i] = y_ncat[i] + sqrt(pow(p0_ncat.getError(),2.));
  }
  TGraph *gr_ncat = new TGraph(npoints,x,y_ncat);
  gr_ncat->Fit("pol1","Q","");
  TF1 *fit_ncat = gr_ncat->GetFunction("pol1");
  fit_ncat->SetLineColor(9);
  TGraph *gr_ncat_i = new TGraph(npoints,x,yi_ncat);
  gr_ncat_i->Fit("pol2","Q","");
  TF1 *fit_ncat_i = gr_ncat_i->GetFunction("pol2");
  TGraph *gr_ncat_s = new TGraph(npoints,x,ys_ncat);
  gr_ncat_s->Fit("pol2","Q","");
  TF1 *fit_ncat_s = gr_ncat_s->GetFunction("pol2");
  gr_myStyle(gr_ncat,"gr_ncat",1,9,1,9,1001,0.,1.,510,510,20,9,0.1,"M_{t} (GeV)","#alpha");
  gr_ncat->Draw("AP");
  fit_ncat_i->SetLineColor(38); fit_ncat_i->SetLineStyle(2); fit_ncat_i->SetLineWidth(2);
  fit_ncat_i->Draw("same");
  fit_ncat_s->SetLineColor(38); fit_ncat_s->SetLineStyle(2); fit_ncat_s->SetLineWidth(2);
  fit_ncat_s->Draw("same");
  gr_ncat->GetXaxis()->SetRangeUser(mtlim[0],mtlim[1]);
  TLegend *leg_par_2 = new TLegend(0.3,0.78,0.85,0.88,NULL,"brNDC");
  leg_par_2->SetTextSize(0.035);
  leg_par_2->SetHeader("Relative contribution of the Gaussian");
  leg_par_2->AddEntry(gr_ncat, TString::Format("#alpha = %2.2f + %2.4f#upointM_{t}",p0_ncat.getVal(),p1_ncat.getVal()), "l");
  leg_myStyle(leg_par_2);
  leg_par_2->Draw("same");
  channel_tex->Draw("same");
  cms_myStyle(lumi, false);
  TString out_par_2 = outDir+"Parameter_gaussian_relcont";
  cn_par_2->SaveAs(out_par_2+".pdf");
  cn_par_2->SaveAs(out_par_2+".C");
  cn_par_2->SaveAs(out_par_2+".jpg");
  cn_par_2->SaveAs(out_par_2+".eps");

  TCanvas *cn_par_3 = new TCanvas("cn_par_3","cn_par_3",800,800);
  cn_par_3->cd();
  double y_gamma_gam[npoints]; double yi_gamma_gam[npoints]; double ys_gamma_gam[npoints];
  for (unsigned int i = 0; i < npoints; i++) {
    y_gamma_gam[i] = p0_gamma_gam.getVal() + p1_gamma_gam.getVal()*x[i];
    yi_gamma_gam[i] = y_gamma_gam[i] - sqrt(pow(p0_gamma_gam.getError(),2.));
    ys_gamma_gam[i] = y_gamma_gam[i] + sqrt(pow(p0_gamma_gam.getError(),2.));
  }
  TGraph *gr_gamma_gam = new TGraph(npoints,x,y_gamma_gam);
  gr_gamma_gam->Fit("pol1","Q","");
  TF1 *fit_gamma_gam = gr_gamma_gam->GetFunction("pol1");
  fit_gamma_gam->SetLineColor(9);
  TGraph *gr_gamma_gam_i = new TGraph(npoints,x,yi_gamma_gam);
  gr_gamma_gam_i->Fit("pol2","Q","");
  TF1 *fit_gamma_gam_i = gr_gamma_gam_i->GetFunction("pol2");
  TGraph *gr_gamma_gam_s = new TGraph(npoints,x,ys_gamma_gam);
  gr_gamma_gam_s->Fit("pol2","Q","");
  TF1 *fit_gamma_gam_s = gr_gamma_gam_s->GetFunction("pol2");
  gr_myStyle(gr_gamma_gam,"gr_gamma_gam",1,9,1,9,1001,0.,5.,510,510,20,9,0.1,"M_{t} (GeV)","#gamma");
  gr_gamma_gam->Draw("AP");
  fit_gamma_gam_i->SetLineColor(38); fit_gamma_gam_i->SetLineStyle(2); fit_gamma_gam_i->SetLineWidth(2);
  fit_gamma_gam_i->Draw("same");
  fit_gamma_gam_s->SetLineColor(38); fit_gamma_gam_s->SetLineStyle(2); fit_gamma_gam_s->SetLineWidth(2);
  fit_gamma_gam_s->Draw("same");
  gr_gamma_gam->GetXaxis()->SetRangeUser(mtlim[0],mtlim[1]);
  TLegend *leg_par_3 = new TLegend(0.3,0.78,0.85,0.88,NULL,"brNDC");
  leg_par_3->SetTextSize(0.035);
  leg_par_3->SetHeader("Shape parameter of the gamma distribution");
  leg_par_3->AddEntry(gr_gamma_gam, TString::Format("#gamma = %2.1f + %2.4f#upointM_{t}",p0_gamma_gam.getVal(),p1_gamma_gam.getVal()), "l");
  leg_myStyle(leg_par_3);
  leg_par_3->Draw("same");
  channel_tex->Draw("same");
  cms_myStyle(lumi, false);
  TString out_par_3 = outDir+"Parameter_gamma_shape";
  cn_par_3->SaveAs(out_par_3+".pdf");
  cn_par_3->SaveAs(out_par_3+".C");
  cn_par_3->SaveAs(out_par_3+".jpg");
  cn_par_3->SaveAs(out_par_3+".eps");

  TCanvas *cn_par_4 = new TCanvas("cn_par_4","cn_par_4",800,800);
  cn_par_4->cd();
  double y_beta_gam[npoints]; double yi_beta_gam[npoints]; double ys_beta_gam[npoints];
  for (unsigned int i = 0; i < npoints; i++) {
    y_beta_gam[i] = p0_beta_gam.getVal() + p1_beta_gam.getVal()*x[i];
    yi_beta_gam[i] = y_beta_gam[i] - sqrt(pow(p0_beta_gam.getError(),2.));
    ys_beta_gam[i] = y_beta_gam[i] + sqrt(pow(p0_beta_gam.getError(),2.));
  }
  TGraph *gr_beta_gam = new TGraph(npoints,x,y_beta_gam);
  gr_beta_gam->Fit("pol1","Q","");
  TF1 *fit_beta_gam = gr_beta_gam->GetFunction("pol1");
  fit_beta_gam->SetLineColor(9);
  TGraph *gr_beta_gam_i = new TGraph(npoints,x,yi_beta_gam);
  gr_beta_gam_i->Fit("pol2","Q","");
  TF1 *fit_beta_gam_i = gr_beta_gam_i->GetFunction("pol2");
  TGraph *gr_beta_gam_s = new TGraph(npoints,x,ys_beta_gam);
  gr_beta_gam_s->Fit("pol2","Q","");
  TF1 *fit_beta_gam_s = gr_beta_gam_s->GetFunction("pol2");
  gr_myStyle(gr_beta_gam,"gr_beta_gam",1,9,1,9,1001,0.,60.,510,510,20,9,0.1,"M_{t} (GeV)","#beta (GeV)");
  gr_beta_gam->Draw("AP");
  fit_beta_gam_i->SetLineColor(38); fit_beta_gam_i->SetLineStyle(2); fit_beta_gam_i->SetLineWidth(2);
  fit_beta_gam_i->Draw("same");
  fit_beta_gam_s->SetLineColor(38); fit_beta_gam_s->SetLineStyle(2); fit_beta_gam_s->SetLineWidth(2);
  fit_beta_gam_s->Draw("same");
  gr_beta_gam->GetXaxis()->SetRangeUser(mtlim[0],mtlim[1]);
  TLegend *leg_par_4 = new TLegend(0.3,0.78,0.85,0.88,NULL,"brNDC");
  leg_par_4->SetTextSize(0.035);
  leg_par_4->SetHeader("Scale parameter of the gamma distribution");
  leg_par_4->AddEntry(gr_beta_gam, TString::Format("#beta = %2.2f + %2.2f#upointM_{t}",p0_beta_gam.getVal(),p1_beta_gam.getVal()), "l");
  leg_myStyle(leg_par_4);
  leg_par_4->Draw("same");
  channel_tex->Draw("same");
  cms_myStyle(lumi, false);
  TString out_par_4 = outDir+"Parameter_gamma_scale";
  cn_par_4->SaveAs(out_par_4+".pdf");
  cn_par_4->SaveAs(out_par_4+".C");
  cn_par_4->SaveAs(out_par_4+".jpg");
  cn_par_4->SaveAs(out_par_4+".eps");

  TCanvas *cn_par_5 = new TCanvas("cn_par_5","cn_par_5",800,800);
  cn_par_5->cd();
  double y_mu_gam[npoints]; double yi_mu_gam[npoints]; double ys_mu_gam[npoints];
  for (unsigned int i = 0; i < npoints; i++) {
    y_mu_gam[i] = p0_mu_gam.getVal() + p1_mu_gam.getVal()*x[i];
    yi_mu_gam[i] = y_mu_gam[i] - sqrt(pow(p0_mu_gam.getError(),2.));
    ys_mu_gam[i] = y_mu_gam[i] + sqrt(pow(p0_mu_gam.getError(),2.));
  }
  TGraph *gr_mu_gam = new TGraph(npoints,x,y_mu_gam);
  gr_mu_gam->Fit("pol1","Q","");
  TF1 *fit_mu_gam = gr_mu_gam->GetFunction("pol1");
  fit_mu_gam->SetLineColor(9);
  TGraph *gr_mu_gam_i = new TGraph(npoints,x,yi_mu_gam);
  gr_mu_gam_i->Fit("pol2","Q","");
  TF1 *fit_mu_gam_i = gr_mu_gam_i->GetFunction("pol2");
  TGraph *gr_mu_gam_s = new TGraph(npoints,x,ys_mu_gam);
  gr_mu_gam_s->Fit("pol2","Q","");
  TF1 *fit_mu_gam_s = gr_mu_gam_s->GetFunction("pol2");
  gr_myStyle(gr_mu_gam,"gr_mu_gam",1,9,1,9,1001,0.,30.,510,510,20,9,0.1,"M_{t} (GeV)","#mu (GeV)");
  gr_mu_gam->Draw("AP");
  fit_mu_gam_i->SetLineColor(38); fit_mu_gam_i->SetLineStyle(2); fit_mu_gam_i->SetLineWidth(2);
  fit_mu_gam_i->Draw("same");
  fit_mu_gam_s->SetLineColor(38); fit_mu_gam_s->SetLineStyle(2); fit_mu_gam_s->SetLineWidth(2);
  fit_mu_gam_s->Draw("same");
  gr_mu_gam->GetXaxis()->SetRangeUser(mtlim[0],mtlim[1]);
  TLegend *leg_par_5 = new TLegend(0.3,0.78,0.85,0.88,NULL,"brNDC");
  leg_par_5->SetTextSize(0.035);
  leg_par_5->SetHeader("Shift parameter of the gamma distribution");
  leg_par_5->AddEntry(gr_mu_gam, TString::Format("#mu = %2.0f + %2.2f#upointM_{t}",p0_mu_gam.getVal(),p1_mu_gam.getVal()), "l");
  leg_myStyle(leg_par_5);
  leg_par_5->Draw("same");
  channel_tex->Draw("same");
  cms_myStyle(lumi, false);
  TString out_par_5 = outDir+"Parameter_gamma_shift";
  cn_par_5->SaveAs(out_par_5+".pdf");
  cn_par_5->SaveAs(out_par_5+".C");
  cn_par_5->SaveAs(out_par_5+".jpg");
  cn_par_5->SaveAs(out_par_5+".eps");


  //===========================
  //    Data
  //===========================

  //---- Dataset
  TString dataName = inDir;
  if (blind)
    dataName += "All_172_5.root";
  else 
    dataName += fileData;
  TFile *data_fi = TFile::Open(dataName);
  TTree *data_tree = (TTree*)data_fi->Get("MTriLept");
  RooDataSet *data_dataset = new RooDataSet("data_dataset", "data_dataset", RooArgSet(mtl, weight), Import(*data_tree), WeightVar(weight));

  //---- Fit des data avec un seul parametre : la masse du top
  mt.setVal(172.5);
  RooConstVar mean_gaus_p0("mean_gaus_p0","mean_gaus_p0",p0_mean_gaus.getVal());
  RooConstVar mean_gaus_p1("mean_gaus_p1","mean_gaus_p1",p1_mean_gaus.getVal());
  RooFormulaVar mean_gaus("mean_gaus","@0+@1*@2",RooArgList(mean_gaus_p0,mean_gaus_p1,mt));
  RooConstVar width_gaus_p0("width_gaus_p0","width_gaus_p0",p0_width_gaus.getVal());
  RooConstVar width_gaus_p1("width_gaus_p1","width_gaus_p1",p1_width_gaus.getVal());
  RooFormulaVar width_gaus("width_gaus","@0+@1*@2",RooArgList(width_gaus_p0,width_gaus_p1,mt));
  RooGaussian pdf_gaus("pdf_gaus","pdf_gaus",mtl,mean_gaus,width_gaus);

  RooConstVar gamma_gamma_0("gamma_gamma_0","gamma_gamma_0",p0_gamma_gam.getVal());
  RooConstVar gamma_gamma_1("gamma_gamma_1","gamma_gamma_1",p1_gamma_gam.getVal());
  RooFormulaVar gamma_gamma("gamma_gamma","@0+@1*@2",RooArgList(gamma_gamma_0,gamma_gamma_1,mt));
  RooConstVar beta_gamma_0("beta_gamma_0","beta_gamma_0",p0_beta_gam.getVal());
  RooConstVar beta_gamma_1("beta_gamma_1","beta_gamma_1",p1_beta_gam.getVal());
  RooFormulaVar beta_gamma("beta_gamma","@0+@1*@2",RooArgList(beta_gamma_0,beta_gamma_1,mt));
  RooConstVar mu_gamma_0("mu_gamma_0","mu_gamma_0",p0_mu_gam.getVal());
  RooConstVar mu_gamma_1("mu_gamma_1","mu_gamma_1",p1_mu_gam.getVal());
  RooFormulaVar mu_gamma("mu_gamma","@0+@1*@2",RooArgList(mu_gamma_0,mu_gamma_1,mt));
  RooGamma pdf_gamma("pdf_gamma","pdf_gamma",mtl,gamma_gamma,beta_gamma,mu_gamma);

  RooConstVar ncat_p0("ncat_p0","ncat_p0",p0_ncat.getVal());
  RooConstVar ncat_p1("ncat_p1","ncat_p1",p1_ncat.getVal());
  RooFormulaVar ncat("ncat","@0+@1*@2",RooArgList(ncat_p0,ncat_p1,mt));
  RooAddPdf model("model","sumpdf",RooArgList(pdf_gaus,pdf_gamma),RooArgList(ncat));

  RooAbsReal* nll_res = model.createNLL(*data_dataset, NumCPU(NCPU), SumW2Error(kTRUE));
  RooMinuit m_res(*nll_res);
  m_res.setPrintLevel(-1); 
  m_res.setPrintEvalErrors(-1);
  m_res.migrad();
  m_res.hesse();
  //m_res.minos(); //optional
  RooFitResult *result_final = m_res.save();


  double *mtop_res = new double[2];
  mtop_res[0] = mt.getVal(); 
  mtop_res[1] = mt.getError(); 

  //===========================
  //    Results
  //===========================

  //---- Fit and likelihood

  TCanvas *cn_fit_data = new TCanvas("cn_fit_data","cn_fit_data",800,800);
  cn_fit_data->cd();
  RooPlot* frame = mtl.frame();
  data_dataset->plotOn(frame,Binning(25), DataError(RooAbsData::SumW2));
  model.plotOn(frame,FillColor(38),VisualizeError(*result_final)) ;
  model.plotOn(frame,LineColor(9)) ;
  model.plotOn(frame,Components(pdf_gamma),LineStyle(kDashed),LineColor(kBlue));
  model.plotOn(frame,Components(pdf_gaus),LineStyle(kDashed),LineColor(kRed));
  frame->Draw();
  TLegend *leg_fit_data = new TLegend(0.58,0.82,0.9,0.9,NULL,"brNDC");
  leg_fit_data->SetHeader(TString::Format("M_{t} = (%3.1f #pm %1.1f) GeV", mt.getVal(), mt.getError()));
  leg_myStyle(leg_fit_data);
  leg_fit_data->Draw("same");
  channel_tex->Draw("same");
  TString out_fit_data = outDir;
  if (blind) {
    out_fit_data += "Fit_BlindedData";
    cms_myStyle(lumi,false);
  }
  else {
    out_fit_data += "Fit_UnblindedData";
    cms_myStyle(lumi,true);
  }
  cn_fit_data->SaveAs(out_fit_data+".pdf");
  cn_fit_data->SaveAs(out_fit_data+".C");
  cn_fit_data->SaveAs(out_fit_data+".jpg");
  cn_fit_data->SaveAs(out_fit_data+".eps");

  TCanvas *cn_nll_data = new TCanvas("cn_nll_data","cn_nll_data",800,800);
  cn_nll_data->cd();
  RooPlot *likeframe = mt.frame();
  nll_res->plotOn(likeframe,ShiftToZero(),LineColor(9));
  likeframe->SetYTitle("-log(L/L_{max})");
  likeframe->Draw();
  TLegend *leg_nll_data = new TLegend(0.58,0.82,0.9,0.9,NULL,"brNDC");
  leg_nll_data->SetHeader(TString::Format("M_{t} = (%3.1f #pm %1.1f) GeV", mt.getVal(), mt.getError()));
  leg_myStyle(leg_nll_data);
  leg_nll_data->Draw("same");
  channel_tex->Draw("same");
  TString out_nll_data = outDir;
  if (blind) {
    out_nll_data += "Nll_BlindedData";
    cms_myStyle(lumi,false);
  }
  else {
    out_nll_data += "Nll_UnblindedData";
    cms_myStyle(lumi,true);
  }
  cn_nll_data->SaveAs(out_nll_data+".pdf");
  cn_nll_data->SaveAs(out_nll_data+".C");
  cn_nll_data->SaveAs(out_nll_data+".jpg");
  cn_nll_data->SaveAs(out_nll_data+".eps");

  TCanvas *cn_res_data = new TCanvas("cn_res_data","cn_res_data",800,800);
  cn_res_data->cd();
  double ymax = 110.;
  if (blind) {
    if (outDir.Contains("FitMoreConstrainedEl", TString::kIgnoreCase))
      ymax = 16000.;
    if (outDir.Contains("FitMoreConstrainedMu", TString::kIgnoreCase))
      ymax = 18000.;
    if (outDir.Contains("FitMoreConstrainedAll", TString::kIgnoreCase))
      ymax = 35000.;
  } else {
    if (outDir.Contains("FitMoreConstrainedEl", TString::kIgnoreCase))
      ymax = 52.;
    if (outDir.Contains("FitMoreConstrainedMu", TString::kIgnoreCase))
      ymax = 60.;
    if (outDir.Contains("FitMoreConstrainedAll", TString::kIgnoreCase))
      ymax = 110.;
  }
  frame->GetYaxis()->SetRangeUser(0., ymax);
  frame->Draw();
  TLegend *leg_res_data = new TLegend(0.56,0.44,0.9,0.52,NULL,"brNDC");
  leg_res_data->SetHeader(TString::Format("M_{t} = (%3.2f #pm %1.2f) GeV", mt.getVal(), mt.getError()));
  leg_res_data->SetTextSize(0.04);
  leg_myStyle(leg_res_data);
  leg_res_data->Draw("same");
  channel_tex->Draw("same");
  if (blind) {
    cms_myStyle(lumi, false);
  }
  else { 
    cms_myStyle(lumi,true);
  }
  TPad *inset_pad = new TPad("inset_pad","inset_pad", 0.55,0.55,0.93,0.92);
  inset_pad->Draw();
  inset_pad->cd();
  inset_pad->SetMargin(1.5*LEFT_MARGIN, 0.1*RIGHT_MARGIN, 1.5*BOTTOM_MARGIN, 0.1*TOP_MARGIN);
  RooPlot *likeframe_zoom = mt.frame(mt.getVal()-3.*mt.getError(), mt.getVal()+3.*mt.getError());
  nll_res->plotOn(likeframe_zoom,ShiftToZero(),LineColor(9));
  likeframe_zoom->SetYTitle("-log(L/L_{max})");
  likeframe_zoom->SetTitleOffset(3.,"X");
  likeframe_zoom->SetTitleOffset(3.,"Y");
  likeframe_zoom->SetTitleSize(LABEL_FONTSIZE+2,"XY");
  likeframe_zoom->GetXaxis()->SetNdivisions(503);
  likeframe_zoom->GetYaxis()->SetNdivisions(506);
  likeframe_zoom->Draw();
  TString out_res_data = outDir;
  if (blind) {
    out_res_data += "FitNll_BlindedData";
  }
  else { 
    out_res_data += "FitNll_UnblindedData";
  }
  cn_res_data->SaveAs(out_res_data+".pdf");
  cn_res_data->SaveAs(out_res_data+".C");
  cn_res_data->SaveAs(out_res_data+".jpg");
  cn_res_data->SaveAs(out_res_data+".eps");

  //---- Parameters
  cn_par_0->cd();
  const unsigned int r = 1; double mt_v[r] = {mt.getVal()}; double mt_e[r] = {mt.getError()};
  double mean_gaus_v[r] = {mean_gaus.getVal()}; double mean_gaus_e[r] = {mt.getError()*p1_mean_gaus.getVal()};
  TGraphErrors *gr_mean_gaus_res = new TGraphErrors(r,mt_v,mean_gaus_v,mt_e,mean_gaus_e);
  gr_myStyle(gr_mean_gaus_res,"gr_mean_gaus_res",1,46,1,46,1001,-1111.,-1111.,510,510,20,46,1.1,"","");
  gr_mean_gaus_res->Draw("Psame");
  TString out_res_0 = outDir;
  if (blind)
    out_res_0 += "BlindedParameter_gaussian_mean";
  else 
    out_res_0 += "UnblindedParameter_gaussian_mean";
  cn_par_0->SaveAs(out_res_0+".pdf");
  cn_par_0->SaveAs(out_res_0+".C");
  cn_par_0->SaveAs(out_res_0+".jpg");
  cn_par_0->SaveAs(out_res_0+".eps");

  cn_par_1->cd();
  double width_gaus_v[r] = {width_gaus.getVal()}; double width_gaus_e[r] = {mt.getError()*p1_width_gaus.getVal()};
  TGraphErrors *gr_width_gaus_res = new TGraphErrors(r,mt_v,width_gaus_v,mt_e,width_gaus_e);
  gr_myStyle(gr_width_gaus_res,"gr_width_gaus_res",1,46,1,46,1001,-1111.,-1111.,510,510,20,46,1.1,"","");
  gr_width_gaus_res->Draw("Psame");
  TString out_res_1 = outDir;
  if (blind)
    out_res_1 += "BlindedParameter_gaussian_width";
  else
    out_res_1 += "UnblindedParameter_gaussian_width";
  cn_par_1->SaveAs(out_res_1+".pdf");
  cn_par_1->SaveAs(out_res_1+".C");
  cn_par_1->SaveAs(out_res_1+".jpg");
  cn_par_1->SaveAs(out_res_1+".eps");

  cn_par_2->cd();
  double ncat_v[r] = {ncat.getVal()}; double ncat_e[r] = {mt.getError()*p1_ncat.getVal()};
  TGraphErrors *gr_ncat_res = new TGraphErrors(r,mt_v,ncat_v,mt_e,ncat_e);
  gr_myStyle(gr_ncat_res,"gr_ncat_res",1,46,1,46,1001,-1111.,-1111.,510,510,20,46,1.1,"","");
  gr_ncat_res->Draw("Psame");
  TString out_res_2 = outDir;
  if (blind)
    out_res_2 += "BlindedParameter_gaussian_relcont";
  else 
    out_res_2 += "UnblindedParameter_gaussian_relcont";
  cn_par_2->SaveAs(out_res_2+".pdf");
  cn_par_2->SaveAs(out_res_2+".C");
  cn_par_2->SaveAs(out_res_2+".jpg");
  cn_par_2->SaveAs(out_res_2+".eps");

  cn_par_3->cd();
  double gamma_gamma_v[r] = {gamma_gamma.getVal()}; double gamma_gamma_e[r] = {mt.getError()*p1_gamma_gam.getVal()};
  TGraphErrors *gr_gamma_gamma_res = new TGraphErrors(r,mt_v,gamma_gamma_v,mt_e,gamma_gamma_e);
  gr_myStyle(gr_gamma_gamma_res,"gr_gamma_gamma_res",1,46,1,46,1001,-1111.,-1111.,510,510,20,46,1.1,"","");
  gr_gamma_gamma_res->Draw("Psame");
  TString out_res_3 = outDir;
  if (blind)
    out_res_3 += "BlindedParameter_gamma_shape";
  else 
    out_res_3 += "UnblindedParameter_gamma_shape";
  cn_par_3->SaveAs(out_res_3+".pdf");
  cn_par_3->SaveAs(out_res_3+".C");
  cn_par_3->SaveAs(out_res_3+".jpg");
  cn_par_3->SaveAs(out_res_3+".eps");

  cn_par_4->cd();
  double beta_gamma_v[r] = {beta_gamma.getVal()}; double beta_gamma_e[r] = {mt.getError()*p1_beta_gam.getVal()};
  TGraphErrors *gr_beta_gamma_res = new TGraphErrors(r,mt_v,beta_gamma_v,mt_e,beta_gamma_e);
  gr_myStyle(gr_beta_gamma_res,"gr_beta_gamma_res",1,46,1,46,1001,-1111.,-1111.,510,510,20,46,1.1,"","");
  gr_beta_gamma_res->Draw("Psame");
  TString out_res_4 = outDir;
  if (blind)
    out_res_4 += "BlindedParameter_gamma_scale";
  else 
    out_res_4 += "UnblindedParameter_gamma_scale";
  cn_par_4->SaveAs(out_res_4+".pdf");
  cn_par_4->SaveAs(out_res_4+".C");
  cn_par_4->SaveAs(out_res_4+".jpg");
  cn_par_4->SaveAs(out_res_4+".eps");

  cn_par_5->cd();
  double mu_gamma_v[r] = {mu_gamma.getVal()}; double mu_gamma_e[r] = {mt.getError()*p1_mu_gam.getVal()};
  TGraphErrors *gr_mu_gamma_res = new TGraphErrors(r,mt_v,mu_gamma_v,mt_e,mu_gamma_e);
  gr_myStyle(gr_mu_gamma_res,"gr_mu_gamma_res",1,46,1,46,1001,-1111.,-1111.,510,510,20,46,1.1,"","");
  gr_mu_gamma_res->Draw("Psame");
  TString out_res_5 = outDir;
  if (blind)
    out_res_5 += "BlindedParameter_gamma_shift";
  else 
    out_res_5 += "UnblindedParameter_gamma_shift";
  cn_par_5->SaveAs(out_res_5+".pdf");
  cn_par_5->SaveAs(out_res_5+".C");
  cn_par_5->SaveAs(out_res_5+".jpg");
  cn_par_5->SaveAs(out_res_5+".eps");


  //===========================
  //    Toys
  //===========================

  vector<double> TTbar;
  TTbar.push_back(mtop_res[0]);
  const unsigned int nttbar = mtoys.size();
  unsigned int n172p5 = 0;
  for (unsigned int ittbar = 0; ittbar < nttbar; ittbar++) {
    TTbar.push_back(mtoys[ittbar]);
    if (mtoys[ittbar] < 172.5) 
      ++n172p5;
  }
  double mttbar[nttbar]; double mean_pull[nttbar]; double width_pull[nttbar]; double mean_residual[nttbar]; double width_residual[nttbar]; double mean_pull_e[nttbar]; double width_pull_e[nttbar]; double mean_residual_e[nttbar]; double width_residual_e[nttbar];
  double nentrie = 0.;
  for (unsigned int ittbar = 0; ittbar < nentries.size(); ittbar++) {
    nentrie += nentries[ittbar];
  }
  if (nentries.size() != 0) nentrie = nentrie / (double) nentries.size();

  for (unsigned int ittbar = 0; ittbar <= nttbar; ittbar++) {
    if (ittbar > 0) mttbar[ittbar-1] = TTbar[ittbar];
    mt.setVal(TTbar[ittbar]);
    double mti_v[1] = {mt.getVal()};

    //---- Generation of a data-sized sample
    RooMCStudy* mcs = new RooMCStudy(model,mtl);
    mcs->generate(nsample,nevt,kTRUE);

    TH1F* hist_residual = new TH1F("Residual","Residual",100,-20,20);
    TH1F* hist_pull = new TH1F("Pull","Pull",50,-5,5);
    TH1F* hist_mean = new TH1F("Mean","Mean",mtlim[1]-mtlim[0],mtlim[0],mtlim[1]);
    TH1F* hist_err = new TH1F("Error","Error",70,1.,8.);

    for(unsigned int isample = 0; isample < nsample; isample++) {
      RooAbsData* gen_dataset = (RooDataSet*)mcs->genData(isample);
      model.fitTo(*gen_dataset, Save(), SumW2Error(kTRUE), PrintLevel(-1), PrintEvalErrors(-1));  

      //---- fill des histos
      hist_residual->Fill(mt.getVal()-mti_v[0]);
      hist_pull->Fill((mt.getVal()-mti_v[0])/mt.getError());
      hist_mean->Fill(mt.getVal());
      hist_err->Fill(mt.getError());
    }

    TCanvas *cn_mean = new TCanvas("cn_mean","cn_mean",800,800);
    cn_mean->cd();
    h_myStyle(hist_mean, 0, 38, 1, 38, 3002, 0, 1.1*hist_mean->GetMaximum(), 510, 510, 20, 38, 1.2, 1, "#tilde{M}_{t}^{toy} (GeV)");
    hist_mean->Draw("hist");
    TLegend *leg_mean = new TLegend(0.7,0.62,0.9,0.7,NULL,"brNDC");
    leg_mean->SetTextSize(0.025);
    //leg_mean->SetHeader(TString::Format("Generated at M_{t} = %4.2f GeV", mti_v[0]));
    leg_mean->AddEntry((TObject*)0,"Generated at","");
    leg_mean->AddEntry((TObject*)0,TString::Format("M_{t} = %4.2f GeV", mti_v[0]),"");
    leg_myStyle(leg_mean);
    leg_mean->Draw("same");
    channel_tex->Draw("same");
    TString out_mean = outDir;
    if (ittbar > 0) {
      if (fabs(floor(TTbar[ittbar]) - TTbar[ittbar]) < 1e-6) {
        out_mean += TString::Format("Toys_%d_Mean", (int)TTbar[ittbar]);
        cms_myStyle(lumi, false);
      }
      else {
        out_mean +=TString::Format("Toys_%d_5_Mean", (int)TTbar[ittbar]);
        cms_myStyle(lumi, false);
      }
    }
    else {
      if (blind) { 
        out_mean += "BlindedToys_Mean";
        cms_myStyle(lumi, false);
      }
      else { 
        out_mean += "UnblindedToys_Mean";
        cms_myStyle(lumi, true);
        double y2_mean = hist_mean->GetBinContent(1.+(mtop_res[0]-mtlim[0])/(mtlim[1]-mtlim[0])*hist_mean->GetNbinsX());
        double y1_mean = y2_mean;
        if (fileData.Contains("Run")) 
          y1_mean += 30.;
        else
          y1_mean += 20.;
        TArrow ar_mean(mtop_res[0], y1_mean, mtop_res[0], y2_mean, 0.025, "|>");
        ar_mean.SetAngle(40);
        ar_mean.SetLineWidth(3);
        ar_mean.SetLineColor(38);
        ar_mean.SetFillColor(38);
        ar_mean.DrawClone();
      }
    }
    cn_mean->SaveAs(out_mean+".pdf");
    cn_mean->SaveAs(out_mean+".C");
    cn_mean->SaveAs(out_mean+".jpg");
    cn_mean->SaveAs(out_mean+".eps");

    TCanvas *cn_err = new TCanvas("cn_err","cn_err",800,800);
    cn_err->cd();
    h_myStyle(hist_err, 0, 38, 1, 38, 3002, 0, 1.1*hist_err->GetMaximum(), 510, 510, 20, 38, 1.2, 1, "#Delta#tilde{M}_{t}^{toy} (GeV)");
    hist_err->Draw("hist");
    TLegend *leg_err = new TLegend(0.7,0.62,0.9,0.7,NULL,"brNDC");
    leg_err->SetTextSize(0.025);
    leg_err->SetHeader(TString::Format("Toys of #approx%d events", nevt));
    leg_myStyle(leg_err);
    leg_err->Draw("same");
    channel_tex->Draw("same");
    TString out_err = outDir;
    if (ittbar > 0) {
      if (fabs(floor(TTbar[ittbar]) - TTbar[ittbar]) < 1e-6) {
        out_err += TString::Format("Toys_%d_Error", (int)TTbar[ittbar]);
        cms_myStyle(lumi, false);
      }
      else {
        out_err +=TString::Format("Toys_%d_5_Error", (int)TTbar[ittbar]);
        cms_myStyle(lumi, false);
      }
    }
    else {
      if (blind) {
        out_err += "BlindedToys_Error";
        cms_myStyle(lumi, false);
      }
      else { 
        out_err += "UnblindedToys_Error";
        cms_myStyle(lumi, true);
        double y2_err = hist_err->GetBinContent(1.+(mtop_res[1]-1.)/(8.-1.)*hist_err->GetNbinsX());
        double y1_err = y2_err;
        if (fileData.Contains("Run")) 
          y1_err += 100.;
        else
          y1_err += 50.;
        TArrow ar_err(mtop_res[1], y1_err, mtop_res[1], y2_err, 0.025, "|>");
        ar_err.SetAngle(40);
        ar_err.SetLineWidth(3);
        ar_err.SetLineColor(38);
        ar_err.SetFillColor(38);
        ar_err.DrawClone();
      }
    }
    cn_err->SaveAs(out_err+".pdf");
    cn_err->SaveAs(out_err+".C");
    cn_err->SaveAs(out_err+".jpg");
    cn_err->SaveAs(out_err+".eps");

    TCanvas *cn_pull = new TCanvas("cn_pull","cn_pull",800,800);
    cn_pull->cd();
    h_myStyle(hist_pull, 0, 38, 1, 38, 3002, 0, 1.1*hist_pull->GetMaximum(), 510, 510, 20, 38, 1.2, 1, "(#tilde{M}_{t}^{toy}-M_{t}^{gen})/#Delta#tilde{M}_{t}^{toy}");
    hist_pull->Draw("hist");
    hist_pull->Fit("gaus","Q","");
    TF1 *fit_pull_gaus = hist_pull->GetFunction("gaus");
    fit_pull_gaus->SetLineColor(38); fit_pull_gaus->SetLineWidth(2);
    fit_pull_gaus->Draw("same");
    TLegend *leg_pull = new TLegend(0.67,0.62,0.9,0.7,NULL,"brNDC");
    leg_pull->SetTextSize(0.025);
    leg_pull->SetHeader("Gaussian fit parameters:");
    leg_pull->AddEntry((TObject*)0, TString::Format("#mu = (%4.3f #pm %4.3f) GeV",fit_pull_gaus->GetParameter(1),fit_pull_gaus->GetParError(1)), "");
    leg_pull->AddEntry((TObject*)0, TString::Format("#sigma = (%4.3f #pm %4.3f) GeV",fit_pull_gaus->GetParameter(2),fit_pull_gaus->GetParError(2)), "");
    leg_myStyle(leg_pull);
    leg_pull->Draw("same");
    channel_tex->Draw("same");
    TString out_pull = outDir;
    if (ittbar > 0) {
      if (fabs(floor(TTbar[ittbar]) - TTbar[ittbar]) < 1e-6) {
        out_pull += TString::Format("Toys_%d_Pull", (int)TTbar[ittbar]);
        cms_myStyle(lumi, false);
    }
      else {
        out_pull +=TString::Format("Toys_%d_5_Pull", (int)TTbar[ittbar]);
        cms_myStyle(lumi, false);
      }
    }
    else {
      if (blind) {
        out_pull += "BlindedToys_Pull";
        cms_myStyle(lumi, false);
      }
      else {
        out_pull += "UnblindedToys_Pull";
        cms_myStyle(lumi, true);
      }
    }
    cn_pull->SaveAs(out_pull+".pdf");
    cn_pull->SaveAs(out_pull+".C");
    cn_pull->SaveAs(out_pull+".jpg");
    cn_pull->SaveAs(out_pull+".eps");

    TCanvas *cn_residual = new TCanvas("cn_residual","cn_residual",800,800);
    cn_residual->cd();
    h_myStyle(hist_residual, 0, 38, 1, 38, 3002, 0, 1.1*hist_residual->GetMaximum(), 510, 510, 20, 38, 1.2, 1, "#tilde{M}_{t}^{toy}-M_{t}^{gen} (GeV)");
    hist_residual->Draw("hist");
    hist_residual->Fit("gaus","Q","");
    TF1 *fit_residual_gaus = hist_residual->GetFunction("gaus");
    fit_residual_gaus->SetLineColor(38); fit_residual_gaus->SetLineWidth(2);
    fit_residual_gaus->Draw("same");
    TLegend *leg_residual = new TLegend(0.67,0.62,0.9,0.7,NULL,"brNDC");
    leg_residual->SetTextSize(0.025);
    leg_residual->SetHeader("Gaussian fit parameters:");
    leg_residual->AddEntry((TObject*)0, TString::Format("#mu = (%4.3f #pm %4.3f) GeV",fit_residual_gaus->GetParameter(1),fit_residual_gaus->GetParError(1)), "");
    leg_residual->AddEntry((TObject*)0, TString::Format("#sigma = (%4.3f #pm %4.3f) GeV",fit_residual_gaus->GetParameter(2),fit_residual_gaus->GetParError(2)), "");
    leg_myStyle(leg_residual);
    leg_residual->Draw("same");
    channel_tex->Draw("same");
    TString out_residual = outDir;
    if (ittbar > 0) {
      if (fabs(floor(TTbar[ittbar]) - TTbar[ittbar]) < 1e-6) {
        out_residual += TString::Format("Toys_%d_Residual", (int)TTbar[ittbar]);
        cms_myStyle(lumi, false);
      }
      else {
        out_residual +=TString::Format("Toys_%d_5_Residual", (int)TTbar[ittbar]);
        cms_myStyle(lumi, false);
      }
    }
    else {
      if (blind) {
        out_residual += "BlindedToys_Residual";
        cms_myStyle(lumi, false);
      }
      else {
        out_residual += "UnblindedToys_Residual";
        cms_myStyle(lumi, true);
      }
    }
    cn_residual->SaveAs(out_residual+".pdf");
    cn_residual->SaveAs(out_residual+".C");
    cn_residual->SaveAs(out_residual+".jpg");
    cn_residual->SaveAs(out_residual+".eps");

    if (ittbar > 0) {
      double scale_mean = sqrt(1.+(double)nsample*(double)nevt/(double)nentrie);
      double scale_width = sqrt(1.+(double)nsample*(double)nevt*(double)nevt/((double)nentrie*(double)nentrie));
      mean_pull[ittbar-1] = fit_pull_gaus->GetParameter(1);
      width_pull[ittbar-1] = fit_pull_gaus->GetParameter(2);
      mean_residual[ittbar-1] = fit_residual_gaus->GetParameter(1);
      width_residual[ittbar-1] = fit_residual_gaus->GetParameter(2);
      mean_pull_e[ittbar-1] = fit_pull_gaus->GetParError(1)*scale_mean;
      width_pull_e[ittbar-1] = fit_pull_gaus->GetParError(2)*scale_width;
      mean_residual_e[ittbar-1] = fit_residual_gaus->GetParError(1)*scale_mean;
      width_residual_e[ittbar-1] = fit_residual_gaus->GetParError(2)*scale_width;
    }

  }

  TCanvas *cn_gr_mean_res = new TCanvas("cn_gr_mean_res","cn_gr_mean_res",800,800);
  cn_gr_mean_res->cd();
  TGraphErrors *gr_mean_res = new TGraphErrors(nttbar,mttbar,mean_residual,0,mean_residual_e);
  gr_myStyle(gr_mean_res,"gr_mean_res",1,9,1,9,1001,-3.,3.,510,510,20,9,1.1,"M_{t}^{gen} (GeV)","residual mean (GeV)");
  TFitResultPtr fitptr_mean_res = gr_mean_res->Fit("pol1","FSQ","");
  TF1 *fit_mean_res = gr_mean_res->GetFunction("pol1");
  double err_up_mean_res[nttbar];
  double err_down_mean_res[nttbar];
  double errval_mean_res[nttbar];
  fitptr_mean_res->GetConfidenceIntervals(nttbar,1,1,mttbar,errval_mean_res,0.68);
  for(unsigned int i = 0; i < nttbar; ++i) {
    double error = errval_mean_res[i];
    err_up_mean_res[i] = fit_mean_res->Eval(mttbar[i])+error;
    err_down_mean_res[i] = fit_mean_res->Eval(mttbar[i])-error;
  }
  TGraph *gr_up_mean_res = new TGraph(nttbar,mttbar,err_up_mean_res);
  gr_up_mean_res->Fit("pol2","Q","");
  TF1 *fit_up_mean_res = gr_up_mean_res->GetFunction("pol2");
  TGraph *gr_down_mean_res = new TGraph(nttbar,mttbar,err_down_mean_res);
  gr_down_mean_res->Fit("pol2","Q","");
  TF1 *fit_down_mean_res = gr_down_mean_res->GetFunction("pol2");  
  fit_mean_res->SetLineColor(9);
  fit_up_mean_res->SetLineColor(29); fit_up_mean_res->SetLineStyle(2); fit_up_mean_res->SetLineWidth(2);
  fit_down_mean_res->SetLineColor(29); fit_down_mean_res->SetLineStyle(2); fit_down_mean_res->SetLineWidth(2);
  gr_mean_res->Draw("AP");
  fit_mean_res->Draw("same");
  fit_up_mean_res->Draw("same");
  fit_down_mean_res->Draw("same");
  TLegend *leg_mean_res = new TLegend(0.4,0.78,0.9,0.88,NULL,"brNDC");
  leg_mean_res->SetTextSize(0.055);
  leg_mean_res->SetHeader(TString::Format("c = (%0.3f #pm %0.3f) GeV",fit_mean_res->Eval(172.5),mean_residual_e[n172p5]));
  leg_myStyle(leg_mean_res);
  leg_mean_res->Draw("same");
  channel_tex->Draw("same");
  cms_myStyle(lumi, false);
  TString out_gr_mean_res =outDir+"Mean_Residual";
  cn_gr_mean_res->SaveAs(out_gr_mean_res+".pdf");
  cn_gr_mean_res->SaveAs(out_gr_mean_res+".C");
  cn_gr_mean_res->SaveAs(out_gr_mean_res+".jpg");
  cn_gr_mean_res->SaveAs(out_gr_mean_res+".eps");

  TCanvas *cn_gr_width_pull = new TCanvas("cn_gr_width_pull","cn_gr_width_pull",800,800);
  cn_gr_width_pull->cd();
  TGraphErrors *gr_width_pull = new TGraphErrors(nttbar,mttbar,width_pull,0,width_pull_e);
  gr_myStyle(gr_width_pull,"gr_width_pull",1,9,1,9,1001,0.7,1.3,510,510,20,9,1.1,"M_{t}^{gen} (GeV)","pull width");
  TFitResultPtr fitptr_width_pull = gr_width_pull->Fit("pol1","FSQ","");
  TF1 *fit_width_pull = gr_width_pull->GetFunction("pol1");
  double err_up_width_pull[nttbar];
  double err_down_width_pull[nttbar];
  double errval_width_pull[nttbar];
  fitptr_width_pull->GetConfidenceIntervals(nttbar,1,1,mttbar,errval_width_pull,0.68);
  for(unsigned int i=0; i<nttbar; ++i) {
    double error = errval_width_pull[i];
    err_up_width_pull[i] = fit_width_pull->Eval(mttbar[i])+error;
    err_down_width_pull[i] = fit_width_pull->Eval(mttbar[i])-error;
  }
  TGraph *gr_up_width_pull = new TGraph(nttbar,mttbar,err_up_width_pull);
  gr_up_width_pull->Fit("pol2","Q","");
  TF1 *fit_up_width_pull = gr_up_width_pull->GetFunction("pol2");
  TGraph *gr_down_width_pull = new TGraph(nttbar,mttbar,err_down_width_pull);
  gr_down_width_pull->Fit("pol2","Q","");
  TF1 *fit_down_width_pull = gr_down_width_pull->GetFunction("pol2");  
  fit_width_pull->SetLineColor(9);
  fit_up_width_pull->SetLineColor(29); fit_up_width_pull->SetLineStyle(2); fit_up_width_pull->SetLineWidth(2);
  fit_down_width_pull->SetLineColor(29); fit_down_width_pull->SetLineStyle(2); fit_down_width_pull->SetLineWidth(2);
  gr_width_pull->Draw("AP");
  fit_width_pull->Draw("same");
  fit_up_width_pull->Draw("same");
  fit_down_width_pull->Draw("same");
  TLegend *leg_width_pull = new TLegend(0.4,0.78,0.9,0.88,NULL,"brNDC");
  leg_width_pull->SetTextSize(0.055);
  leg_width_pull->SetHeader(TString::Format("c = %0.3f #pm %0.3f",fit_width_pull->Eval(172.5),width_pull_e[n172p5]));
  leg_myStyle(leg_width_pull);
  leg_width_pull->Draw("same");
  channel_tex->Draw("same");
  cms_myStyle(lumi, false);
  TString out_gr_width_pull =outDir+"Width_Pull";
  cn_gr_width_pull->SaveAs(out_gr_width_pull+".pdf");
  cn_gr_width_pull->SaveAs(out_gr_width_pull+".C");
  cn_gr_width_pull->SaveAs(out_gr_width_pull+".jpg");
  cn_gr_width_pull->SaveAs(out_gr_width_pull+".eps");

  TCanvas *cn_gr_mean_pull = new TCanvas("cn_gr_mean_pull","cn_gr_mean_pull",800,800);
  cn_gr_mean_pull->cd();
  TGraphErrors *gr_mean_pull = new TGraphErrors(nttbar,mttbar,mean_pull,0,mean_pull_e);
  gr_myStyle(gr_mean_pull,"gr_mean_pull",1,9,1,9,1001,-1.,1.,510,510,20,9,1.1,"M_{t}^{gen} (GeV)","pull mean");
  TFitResultPtr fitptr_mean_pull = gr_mean_pull->Fit("pol1","FSQ","");
  TF1 *fit_mean_pull = gr_mean_pull->GetFunction("pol1");
  double err_up_mean_pull[nttbar];
  double err_down_mean_pull[nttbar];
  double errval_mean_pull[nttbar];
  fitptr_mean_pull->GetConfidenceIntervals(nttbar,1,1,mttbar,errval_mean_pull,0.68);
  for(unsigned int i=0; i<nttbar; ++i) {
    double error = errval_mean_pull[i];
    err_up_mean_pull[i] = fit_mean_pull->Eval(mttbar[i])+error;
    err_down_mean_pull[i] = fit_mean_pull->Eval(mttbar[i])-error;
  }
  TGraph *gr_up_mean_pull = new TGraph(nttbar,mttbar,err_up_mean_pull);
  gr_up_mean_pull->Fit("pol2","Q","");
  TF1 *fit_up_mean_pull = gr_up_mean_pull->GetFunction("pol2");
  TGraph *gr_down_mean_pull = new TGraph(nttbar,mttbar,err_down_mean_pull);
  gr_down_mean_pull->Fit("pol2","Q","");
  TF1 *fit_down_mean_pull = gr_down_mean_pull->GetFunction("pol2");  
  fit_mean_pull->SetLineColor(9);
  fit_up_mean_pull->SetLineColor(29); fit_up_mean_pull->SetLineStyle(2); fit_up_mean_pull->SetLineWidth(2);
  fit_down_mean_pull->SetLineColor(29); fit_down_mean_pull->SetLineStyle(2); fit_down_mean_pull->SetLineWidth(2);
  gr_mean_pull->Draw("AP");
  fit_mean_pull->Draw("same");
  fit_up_mean_pull->Draw("same");
  fit_down_mean_pull->Draw("same");
  TLegend *leg_mean_pull = new TLegend(0.4,0.78,0.9,0.88,NULL,"brNDC");
  leg_mean_pull->SetTextSize(0.055);
  leg_mean_pull->SetHeader(TString::Format("c = %0.3f #pm %0.3f",fit_mean_pull->Eval(172.5),mean_pull_e[n172p5]));
  leg_myStyle(leg_mean_pull);
  leg_mean_pull->Draw("same");
  channel_tex->Draw("same");
  cms_myStyle(lumi, false);
  TString out_gr_mean_pull =outDir+"Mean_Pull";
  cn_gr_mean_pull->SaveAs(out_gr_mean_pull+".pdf");
  cn_gr_mean_pull->SaveAs(out_gr_mean_pull+".C");
  cn_gr_mean_pull->SaveAs(out_gr_mean_pull+".jpg");
  cn_gr_mean_pull->SaveAs(out_gr_mean_pull+".eps");

  TCanvas *cn_gr_width_res = new TCanvas("cn_gr_width_res","cn_gr_width_res",800,800);
  cn_gr_width_res->cd();
  TGraphErrors *gr_width_res = new TGraphErrors(nttbar,mttbar,width_residual,0,width_residual_e);
  gr_myStyle(gr_width_res,"gr_width_res",1,9,1,9,1001,1.,8.,510,510,20,9,1.1,"M_{t}^{gen} (GeV)","residual width (GeV)");
  TFitResultPtr fitptr_width_res = gr_width_res->Fit("pol1","FSQ","");
  TF1 *fit_width_res = gr_width_res->GetFunction("pol1");
  double err_up_width_res[nttbar];
  double err_down_width_res[nttbar];
  double errval_width_res[nttbar];
  fitptr_width_res->GetConfidenceIntervals(nttbar,1,1,mttbar,errval_width_res,0.68);
  for(unsigned int i=0; i<nttbar; ++i) {
    double error = errval_width_res[i];
    err_up_width_res[i] = fit_width_res->Eval(mttbar[i])+error;
    err_down_width_res[i] = fit_width_res->Eval(mttbar[i])-error;
  }
  TGraph *gr_up_width_res = new TGraph(nttbar,mttbar,err_up_width_res);
  gr_up_width_res->Fit("pol2","Q","");
  TF1 *fit_up_width_res = gr_up_width_res->GetFunction("pol2");
  TGraph *gr_down_width_res = new TGraph(nttbar,mttbar,err_down_width_res);
  gr_down_width_res->Fit("pol2","Q","");
  TF1 *fit_down_width_res = gr_down_width_res->GetFunction("pol2");  
  fit_width_res->SetLineColor(9);
  fit_up_width_res->SetLineColor(29); fit_up_width_res->SetLineStyle(2); fit_up_width_res->SetLineWidth(2);
  fit_down_width_res->SetLineColor(29); fit_down_width_res->SetLineStyle(2); fit_down_width_res->SetLineWidth(2);
  gr_width_res->Draw("AP");
  fit_width_res->Draw("same");
  fit_up_width_res->Draw("same");
  fit_down_width_res->Draw("same");
  TLegend *leg_width_res = new TLegend(0.4,0.78,0.9,0.88,NULL,"brNDC");
  leg_width_res->SetTextSize(0.055);
  leg_width_res->SetHeader(TString::Format("c = (%0.3f #pm %0.3f) GeV",fit_width_res->Eval(172.5),width_residual_e[n172p5]));
  leg_myStyle(leg_width_res);
  leg_width_res->Draw("same");
  channel_tex->Draw("same");
  cms_myStyle(lumi, false);
  TString out_gr_width_res =outDir+"Width_Residual";
  cn_gr_width_res->SaveAs(out_gr_width_res+".pdf");
  cn_gr_width_res->SaveAs(out_gr_width_res+".C");
  cn_gr_width_res->SaveAs(out_gr_width_res+".jpg");
  cn_gr_width_res->SaveAs(out_gr_width_res+".eps");

  data_fi->Close(); fi_0->Close(); fi_1->Close(); fi_2->Close(); fi_3->Close(); fi_4->Close(); fi_5->Close();
  return mtop_res;
}

//---------------------------------------------------------------
double *combi(double mt1, double dmt1, double mt2, double dmt2)
//---------------------------------------------------------------
{
  double dmt = pow((pow(dmt1,-2.)+pow(dmt2,-2.)),-0.5);
  double mt = (pow(dmt1,-2.)*mt1+pow(dmt2,-2.)*mt2)/(pow(dmt1,-2.)+pow(dmt2,-2.));

  double *mean_err = new double[2];
  mean_err[0] = mt;
  mean_err[1] = dmt;
  return mean_err;
}

//---------------------------------------------------------------
int simultaneousFitMoreConstrained(TString date = "", TString version = "", TString decay = "",
    bool blind = true, int nEvtEl = -1, int nEvtMu = -1)
//---------------------------------------------------------------
{  
  TH1::SetDefaultSumw2(kTRUE);

  if (date.Length() > 0 && version.Length() > 0 && decay.Length() > 0)  {

    cout << "/!\\ you should have run mergeMC.C and mergeChannels.py before \n" << endl; 

    double mtop[6] = {166.5, 169.5, 171.5, 173.5, 175.5, 178.5};
    vector<double> mtoys; mtoys.push_back(167.); mtoys.push_back(169.); mtoys.push_back(171.); mtoys.push_back(172.5); mtoys.push_back(174.); mtoys.push_back(176.); mtoys.push_back(178);
    double mtlim[2] = {130, 216};
    const unsigned int nsample = 3000.;
    int nevt[3] = {0, 0, 0};

    vector<TString> fileData; fileData.push_back("ElectronHadASingleElectronBCD.root"); fileData.push_back("MuHadASingleMuBCD.root"); fileData.push_back("Run2012ABCD.root");
    // vector<TString> inDir(3, date+"/v"+version+"/"); inDir[0] += "MyAnaEl/"; inDir[1] += "MyAnaMu/"; inDir[2] += "MyAnaAll/";
    vector<TString> inDir(3, date+"/"+version+"/"); inDir[0] += "MyAnaEl/"; inDir[1] += "MyAnaMu/"; inDir[2] += "MyAnaAll/";
    // vector<TString> outDir = date+"/v"+version+"/"; outDir[0] += "SimultaneousFitEl/"; outDir[1] += "SimultaneousFitMu/"; outDir[2] += "SimultaneousFitAll/";
    vector<TString> outDir(3, date+"/"+version+"/"); outDir[0] += "SimultaneousFitMoreConstrainedEl/"; outDir[1] += "SimultaneousFitMoreConstrainedMu/"; outDir[2] += "SimultaneousFitMoreConstrainedAll/";
    TString histName = "NJets20";

    if (nEvtEl > 0 && nEvtMu > 0) {
      nevt[0] = nEvtEl;
      nevt[1] = nEvtMu;
      nevt[2] = nEvtEl + nEvtMu;
    }
    else {
      for (unsigned int iCh = 0; iCh < fileData.size()-1; iCh++) {
        TFile *file = TFile::Open(inDir[iCh]+fileData[iCh]);
        TH1D* hist = (TH1D*)file->Get(histName);
        nevt[iCh] = floor(hist->Integral());
        delete hist;
        file->Close(); delete file;
      }
      nevt[2] = nevt[0] + nevt[1];
    }

    if (blind)
      cout << "Running the blinded analysis: \"data\" is the full-stat MC sample generated at 173.5 GeV " << endl; 
    else  
      cout << "Running the unblinded analysis: \"data\" is Run2012ABCD" << endl; 
    cout << "Performing a simultaneous unbinned likelihood fit (gaussian+gamma function) for M_{t} = "<< mtop[0] << ", " << mtop[1] << ", " << mtop[2] << ", " << mtop[3] << ", " << mtop[4] << ", " << mtop [5] << " GeV" << endl;
    cout << "Toys for leading e type: " << nsample << " toys of Poisson(" << nevt[0] << ") events" << endl;
    cout << "Toys for leading #mu type: " << nsample << " toys of Poisson(" << nevt[1] << ") events" << endl;
    cout << "Toys both types: " << nsample << " toys of Poisson(" << nevt[2] << ") events" << endl;
    cout << "for M_{t} = " << mtoys[0] << ", " << mtoys[1] << ", " << mtoys[2] << ", " << mtoys[3] << ", " << mtoys[4] << ", " << mtoys[5] << ", " << mtoys[6] << " GeV" << endl;

    cout << "\n===================================================\n" <<endl;

    getchar();

    TStyle* my_style = createMyStyle();
    my_style->cd();
    gROOT->SetBatch(true);

    double *mtop_el = treat(outDir[0], inDir[0], fileData[0], 19.7, decay, nevt[0], mtop, mtlim, mtoys, nsample, blind); 
    double *mtop_mu = treat(outDir[1], inDir[1], fileData[1], 19.7, decay, nevt[1], mtop, mtlim, mtoys, nsample, blind); 
    double *mtop_all = treat(outDir[2], inDir[2], fileData[2], 19.7, decay, nevt[2], mtop, mtlim, mtoys, nsample, blind); 

    cout << "\n===================================================\n" <<endl;

    double *mtop_combi = combi(mtop_el[0], mtop_el[1], mtop_mu[0], mtop_mu[1]); 
    TString result1 = TString::Format("Combining decay channels AFTER fits: \n \t \t \t M_{t} = (%3.3f #pm %3.3f) GeV", mtop_combi[0], mtop_combi[1]);
    cout << result1 << endl;
    TString result2 = TString::Format("Combining decay channels BEFORE fits: \n \t \t \t M_{t} = (%3.3f #pm %3.3f) GeV", mtop_all[0], mtop_all[1]);
    cout << result2 << endl;

    return 0;
  }
  else 
    return 1;
}



