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
 * Simple fit with a gaussian+gamma unbinned likelihood fit
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
double *treat(TString fileData, double lumi, int nevt, vector<double> mtop, double *mtlim, vector<double> mtoys, const unsigned int nsample, TString date, TString version, bool blind) 
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

  TString indir = date+"/v"+version+"/";
  TString outdir = indir;
  TString channel = " + Jets channel";

  if (fileData.Contains("ElectronHad")) {
    outdir += "SimpleFitEl/";
    indir += "MyAnaEl/";
    channel = "e"+channel;
  }
  if (fileData.Contains("MuHad")) {
    outdir += "SimpleFitMu/";
    indir += "MyAnaMu/";
    channel = "#mu"+channel;
  }
  if (fileData.Contains("Run")) {
    outdir += "SimpleFitAll/";
    indir += "MyAnaAll/";
    channel = "l"+channel;
  }

  gROOT->ProcessLine(".! mkdir "+outdir);

  TLatex* channel_tex = new TLatex(0.22, 0.9, channel);
  channel_tex->SetNDC(true);
  channel_tex->SetTextFont(43);
  channel_tex->SetTextSize(TITLE_FONTSIZE - 6);

  vector<int> color; color.push_back(419); color.push_back(862); color.push_back(602); color.push_back(907); color.push_back(807); color.push_back(800);
  assert(color.size() == mtop.size());

  vector<double> nentries;

  //=========================
  //    Global variables
  //=========================

  //---- Variables
  RooRealVar mt("mt","M_{t}",173.,mtlim[0],mtlim[1], "GeV/c^{2}");
  RooRealVar mtl("mass", "M_{J/#psi+l}", 0., 250., "GeV/c^{2}");
  RooRealVar weight("weight", "weight", 0., 2.);

  //=========================
  //    PDF for each mtop
  //=========================

  const unsigned int numberOfPoints = mtop.size();
  double x[numberOfPoints];
  double mean_gaus_val[numberOfPoints]; double width_gaus_val[numberOfPoints]; double ncat_val[numberOfPoints];
  double gamma_gamma_val[numberOfPoints]; double beta_gamma_val[numberOfPoints]; double mu_gamma_val[numberOfPoints];
  double mean_gaus_err[numberOfPoints]; double width_gaus_err[numberOfPoints]; double ncat_err[numberOfPoints];
  double gamma_gamma_err[numberOfPoints]; double beta_gamma_err[numberOfPoints]; double mu_gamma_err[numberOfPoints];

  TCanvas *cn_comp = new TCanvas("cn_comp","cn_comp",800,800);
  RooPlot* frame_comp = mtl.frame();
  frame_comp->SetYTitle("P_{sig}");
  TLegend *leg_comp = new TLegend(0.6,0.5,0.9,0.9,NULL,"brNDC");
  leg_comp->SetTextSize(0.025);

  for (unsigned int ind = 0; ind < numberOfPoints; ind++) { 
    x[ind] = mtop[ind];

    //---- Dataset
    TFile *mc_fi = TFile::Open(indir+TString::Format("All_%d_5.root",(int)floor(mtop[ind])));
    TTree *mc_tree = (TTree*)mc_fi->Get("MTriLept");
    nentries.push_back(mc_tree->GetEntries());
    RooDataSet *mc_dataset = new RooDataSet("mc_dataset", "mc_dataset", RooArgSet(mtl, weight), Import(*mc_tree), WeightVar(weight));

    //---- Gaussian
    RooRealVar mc_mean_gaus("mc_mean_gaus", "mc_mean_gaus",70.,50.,90.) ;
    RooRealVar mc_width_gaus("mc_width_gaus", "mc_width_gaus",20.,10.,30.) ;
    RooGaussian mc_pdf_gaus("mc_pdf_gaus","mc_pdf_gaus",mtl,mc_mean_gaus,mc_width_gaus);

    //---- Gamma
    RooRealVar mc_gamma_gamma("mc_gamma_gamma","mc_gamma_gamma",3.,1.,5.);
    RooRealVar mc_beta_gamma("mc_beta_gamma","mc_beta_gamma",30.,20.,40.);
    RooRealVar mc_mu_gamma("mc_mu_gamma","mc_mu_gamma",5.,0.,17.);
    RooGamma mc_pdf_gamma("mc_pdf_gamma","mc_pdf_gamma",mtl,mc_gamma_gamma,mc_beta_gamma,mc_mu_gamma);

    //---- Model
    RooRealVar mc_ncat("mc_ncat","mc_ncat",0.3,0.,1.) ;
    RooAddPdf mc_model("mc_model","mc_sumpdf",RooArgList(mc_pdf_gaus,mc_pdf_gamma),RooArgList(mc_ncat)) ;

    //--- Fit
    RooAbsReal* mcNll = mc_model.createNLL(*mc_dataset, NumCPU(NCPU));
    RooMinuit minuit_mc(*mcNll);
    minuit_mc.setPrintLevel(-1); 
    minuit_mc.setPrintEvalErrors(-1);
    minuit_mc.migrad();
    minuit_mc.hesse();
    //minuit_mc.minos(); //optional
    RooFitResult *mc_res = minuit_mc.save();
    mean_gaus_val[ind] = mc_mean_gaus.getVal(); width_gaus_val[ind] = mc_width_gaus.getVal(); ncat_val[ind] = mc_ncat.getVal();
    gamma_gamma_val[ind] = mc_gamma_gamma.getVal(); beta_gamma_val[ind] = mc_beta_gamma.getVal(); mu_gamma_val[ind] = mc_mu_gamma.getVal();  
    mean_gaus_err[ind] = mc_mean_gaus.getError(); width_gaus_err[ind] = mc_width_gaus.getError(); ncat_err[ind] = mc_ncat.getError();
    gamma_gamma_err[ind] = mc_gamma_gamma.getError(); beta_gamma_err[ind] = mc_beta_gamma.getError(); mu_gamma_err[ind] = mc_mu_gamma.getError();  

    //--- Plot
    TCanvas *mc_cn = new TCanvas(TString::Format("cn_pdf_mc_%d", ind),TString::Format("cn_pdf_mc_%d",ind),800,800);
    mc_cn->cd();
    RooPlot* mc_frame = mtl.frame() ;
    mc_dataset->plotOn(mc_frame,Binning(50));
    mc_model.plotOn(mc_frame,FillColor(38),VisualizeError(*mc_res)) ;
    mc_model.plotOn(mc_frame,LineColor(9));
    mc_model.plotOn(mc_frame,Components(mc_pdf_gamma),LineStyle(kDashed),LineColor(kBlue));
    mc_model.plotOn(mc_frame,Components(mc_pdf_gaus),LineStyle(kDashed),LineColor(kRed));
    mc_frame->Draw();
    TLegend *mc_leg = new TLegend(0.58,0.82,0.9,0.9,NULL,"brNDC");
    mc_leg->SetHeader(TString::Format("M_{t} = %4.1f GeV/c^{2}",mtop[ind]));
    leg_myStyle(mc_leg);
    mc_leg->Draw("same");
    channel_tex->Draw("same");
    cms_myStyle(lumi, false);
    TString mc_out = outdir+TString::Format("Pdf_%d_5", (int)mtop[ind]);
    mc_cn->SaveAs(mc_out+".pdf");
    mc_cn->SaveAs(mc_out+".C");
    mc_cn->SaveAs(mc_out+".jpg");
    mc_cn->SaveAs(mc_out+".eps");

    mc_model.plotOn(frame_comp,LineColor(color[ind]),Name(TString::Format("model%d",ind)));
    leg_comp->AddEntry(frame_comp->findObject(TString::Format("model%d",ind)), TString::Format("M_{t} = %4.1f GeV/c^{2}",mtop[ind]), "l");

    mc_fi->Close();
  }

  cn_comp->cd();
  frame_comp->Draw();
  leg_myStyle(leg_comp);
  leg_comp->Draw("same");
  channel_tex->Draw("same");
  cms_myStyle(lumi, false);
  TString out_comp = outdir+"Pdf_All";
  cn_comp->SaveAs(out_comp+".pdf");
  cn_comp->SaveAs(out_comp+".C");
  cn_comp->SaveAs(out_comp+".jpg");
  cn_comp->SaveAs(out_comp+".eps");

  //==========================
  //    Parametrization
  //==========================

  //---- Linear fits wrt mt
  TGraphErrors *gr_mean_gaus = new TGraphErrors(numberOfPoints,x,mean_gaus_val,0,mean_gaus_err);
  TFitResultPtr fitptr_mean_gaus = gr_mean_gaus->Fit("pol1","FS","");
  TF1 *fit_mean_gaus = gr_mean_gaus->GetFunction("pol1");
  fit_mean_gaus->SetLineColor(9);
  Double_t err_mean_gaus_up[numberOfPoints];
  Double_t err_mean_gaus_down[numberOfPoints];
  Double_t errval_mean_gaus[numberOfPoints];
  fitptr_mean_gaus->GetConfidenceIntervals(numberOfPoints,1,1,x,errval_mean_gaus,0.68);
  for(unsigned int k = 0; k < numberOfPoints; ++k) {
    double error = errval_mean_gaus[k];
    err_mean_gaus_up[k] = fit_mean_gaus->Eval(x[k])+error;
    err_mean_gaus_down[k] = fit_mean_gaus->Eval(x[k])-error;
  }
  TGraph *gr_mean_gaus_up = new TGraph(numberOfPoints,x,err_mean_gaus_up);
  gr_mean_gaus_up->Fit("pol2","Q","");
  TF1 *fit_mean_gaus_up = gr_mean_gaus_up->GetFunction("pol2");
  TGraph *gr_mean_gaus_down = new TGraph(numberOfPoints,x,err_mean_gaus_down);
  gr_mean_gaus_down->Fit("pol2","Q","");
  TF1 *fit_mean_gaus_down = gr_mean_gaus_down->GetFunction("pol2");  

  TCanvas *cn_par_0 = new TCanvas("cn_par_0","cn_par_0",800,800);
  cn_par_0->cd();
  gr_myStyle(gr_mean_gaus,"gr_mean_gaus",1,9,1,9,1001,40.,110.,510,510,20,9,0.1,"M_{t} (GeV/c^{2})","#mu (GeV/c^{2})");
  gr_mean_gaus->Draw("AP");
  fit_mean_gaus_up->SetLineColor(38); fit_mean_gaus_up->SetLineStyle(2); fit_mean_gaus_up->SetLineWidth(2);
  fit_mean_gaus_up->Draw("same");
  fit_mean_gaus_down->SetLineColor(38); fit_mean_gaus_down->SetLineStyle(2); fit_mean_gaus_down->SetLineWidth(2);
  fit_mean_gaus_down->Draw("same");
  TLegend *leg_par_0 = new TLegend(0.4,0.82,0.9,0.9,NULL,"brNDC");
  leg_par_0->SetTextSize(0.025);
  leg_par_0->SetHeader("Mean of the Gaussian");
  leg_par_0->AddEntry(gr_mean_gaus, TString::Format("#mu = %2.0f + %2.2f#upointM_{t}",fit_mean_gaus->GetParameter(0),fit_mean_gaus->GetParameter(1)), "l");
  leg_myStyle(leg_par_0);
  leg_par_0->Draw("same");
  channel_tex->Draw("same");
  cms_myStyle(lumi, false);
  TString out_par_0 = outdir+"Parameter_gaussian_mean";
  cn_par_0->SaveAs(out_par_0+".pdf");
  cn_par_0->SaveAs(out_par_0+".C");
  cn_par_0->SaveAs(out_par_0+".jpg");
  cn_par_0->SaveAs(out_par_0+".eps");


  TGraphErrors *gr_width_gaus = new TGraphErrors(numberOfPoints,x,width_gaus_val,0,width_gaus_err);
  TFitResultPtr fitptr_width_gaus = gr_width_gaus->Fit("pol1","FS","");
  TF1 *fit_width_gaus = gr_width_gaus->GetFunction("pol1");
  fit_width_gaus->SetLineColor(9);
  Double_t err_width_gaus_up[numberOfPoints];
  Double_t err_width_gaus_down[numberOfPoints];
  Double_t errval_width_gaus[numberOfPoints];
  fitptr_width_gaus->GetConfidenceIntervals(numberOfPoints,1,1,x,errval_width_gaus,0.68);
  for(unsigned int k = 0; k < numberOfPoints; ++k) {
    double error = errval_width_gaus[k];
    err_width_gaus_up[k] = fit_width_gaus->Eval(x[k])+error;
    err_width_gaus_down[k] = fit_width_gaus->Eval(x[k])-error;
  }
  TGraph *gr_width_gaus_up = new TGraph(numberOfPoints,x,err_width_gaus_up);
  gr_width_gaus_up->Fit("pol2","Q","");
  TF1 *fit_width_gaus_up = gr_width_gaus_up->GetFunction("pol2");
  TGraph *gr_width_gaus_down = new TGraph(numberOfPoints,x,err_width_gaus_down);
  gr_width_gaus_down->Fit("pol2","Q","");
  TF1 *fit_width_gaus_down = gr_width_gaus_down->GetFunction("pol2");  

  TCanvas *cn_par_1 = new TCanvas("cn_par_1","cn_par_1",800,800);
  cn_par_1->cd();
  gr_myStyle(gr_width_gaus,"gr_width_gaus",1,9,1,9,1001,10.,30.,510,510,20,9,0.1,"M_{t} (GeV/c^{2})","#sigma (GeV/c^{2})");
  gr_width_gaus->Draw("AP");
  fit_width_gaus_up->SetLineColor(38); fit_width_gaus_up->SetLineStyle(2); fit_width_gaus_up->SetLineWidth(2);
  fit_width_gaus_up->Draw("same");
  fit_width_gaus_down->SetLineColor(38); fit_width_gaus_down->SetLineStyle(2); fit_width_gaus_down->SetLineWidth(2);
  fit_width_gaus_down->Draw("same");
  TLegend *leg_par_1 = new TLegend(0.4,0.82,0.9,0.9,NULL,"brNDC");
  leg_par_1->SetTextSize(0.025);
  leg_par_1->SetHeader("Width of the Gaussian");
  leg_par_1->AddEntry(gr_width_gaus, TString::Format("#sigma = %2.0f + %2.2f#upointM_{t}",fit_width_gaus->GetParameter(0),fit_width_gaus->GetParameter(1)), "l");
  leg_myStyle(leg_par_1);
  leg_par_1->Draw("same");
  channel_tex->Draw("same");
  cms_myStyle(lumi, false);
  TString out_par_1 = outdir+"Parameter_gaussian_width";
  cn_par_1->SaveAs(out_par_1+".pdf");
  cn_par_1->SaveAs(out_par_1+".C");
  cn_par_1->SaveAs(out_par_1+".jpg");
  cn_par_1->SaveAs(out_par_1+".eps");


  TGraphErrors *gr_ncat = new TGraphErrors(numberOfPoints,x,ncat_val,0,ncat_err);
  TFitResultPtr fitptr_ncat = gr_ncat->Fit("pol1","FS","");
  TF1 *fit_ncat = gr_ncat->GetFunction("pol1");
  fit_ncat->SetLineColor(9);
  Double_t err_ncat_up[numberOfPoints];
  Double_t err_ncat_down[numberOfPoints];
  Double_t errval_ncat[numberOfPoints];
  fitptr_ncat->GetConfidenceIntervals(numberOfPoints,1,1,x,errval_ncat,0.68);
  for(unsigned int k = 0; k < numberOfPoints; ++k) {
    double error = errval_ncat[k];
    err_ncat_up[k] = fit_ncat->Eval(x[k])+error;
    err_ncat_down[k] = fit_ncat->Eval(x[k])-error;
  }
  TGraph *gr_ncat_up = new TGraph(numberOfPoints,x,err_ncat_up);
  gr_ncat_up->Fit("pol2","Q","");
  TF1 *fit_ncat_up = gr_ncat_up->GetFunction("pol2");
  TGraph *gr_ncat_down = new TGraph(numberOfPoints,x,err_ncat_down);
  gr_ncat_down->Fit("pol2","Q","");
  TF1 *fit_ncat_down = gr_ncat_down->GetFunction("pol2");  

  TCanvas *cn_par_2 = new TCanvas("cn_par_2","cn_par_2",800,800);
  cn_par_2->cd();
  gr_myStyle(gr_ncat,"gr_ncat",1,9,1,9,1001,0.,1.,510,510,20,9,0.1,"M_{t} (GeV/c^{2})","#alpha");
  gr_ncat->Draw("AP");
  fit_ncat_up->SetLineColor(38); fit_ncat_up->SetLineStyle(2); fit_ncat_up->SetLineWidth(2);
  fit_ncat_up->Draw("same");
  fit_ncat_down->SetLineColor(38); fit_ncat_down->SetLineStyle(2); fit_ncat_down->SetLineWidth(2);
  fit_ncat_down->Draw("same");
  TLegend *leg_par_2 = new TLegend(0.4,0.82,0.9,0.9,NULL,"brNDC");
  leg_par_2->SetTextSize(0.025);
  leg_par_2->SetHeader("Relative contribution of the Gaussian");
  leg_par_2->AddEntry(gr_ncat, TString::Format("#alpha = %2.2f + %2.4f#upointM_{t}",fit_ncat->GetParameter(0),fit_ncat->GetParameter(1)), "l");
  leg_myStyle(leg_par_2);
  leg_par_2->Draw("same");
  channel_tex->Draw("same");
  cms_myStyle(lumi, false);
  TString out_par_2 = outdir+"Parameter_gaussian_relcont";
  cn_par_2->SaveAs(out_par_2+".pdf");
  cn_par_2->SaveAs(out_par_2+".C");
  cn_par_2->SaveAs(out_par_2+".jpg");
  cn_par_2->SaveAs(out_par_2+".eps");


  TGraphErrors *gr_gamma_gamma = new TGraphErrors(numberOfPoints,x,gamma_gamma_val,0,gamma_gamma_err);
  TFitResultPtr fitptr_gamma_gamma = gr_gamma_gamma->Fit("pol1","FS","");
  TF1 *fit_gamma_gamma = gr_gamma_gamma->GetFunction("pol1");
  fit_gamma_gamma->SetLineColor(9);
  Double_t err_gamma_gamma_up[numberOfPoints];
  Double_t err_gamma_gamma_down[numberOfPoints];
  Double_t errval_gamma_gamma[numberOfPoints];
  fitptr_gamma_gamma->GetConfidenceIntervals(numberOfPoints,1,1,x,errval_gamma_gamma,0.68);
  for(unsigned int k = 0; k < numberOfPoints; ++k) {
    double error = errval_gamma_gamma[k];
    err_gamma_gamma_up[k] = fit_gamma_gamma->Eval(x[k])+error;
    err_gamma_gamma_down[k] = fit_gamma_gamma->Eval(x[k])-error;
  }
  TGraph *gr_gamma_gamma_up = new TGraph(numberOfPoints,x,err_gamma_gamma_up);
  gr_gamma_gamma_up->Fit("pol2","Q","");
  TF1 *fit_gamma_gamma_up = gr_gamma_gamma_up->GetFunction("pol2");
  TGraph *gr_gamma_gamma_down = new TGraph(numberOfPoints,x,err_gamma_gamma_down);
  gr_gamma_gamma_down->Fit("pol2","Q","");
  TF1 *fit_gamma_gamma_down = gr_gamma_gamma_down->GetFunction("pol2");  

  TCanvas *cn_par_3 = new TCanvas("cn_par_3","cn_par_3",800,800);
  cn_par_3->cd();
  gr_myStyle(gr_gamma_gamma,"gr_gamma_gamma",1,9,1,9,1001,0.,5.,510,510,20,9,0.1,"M_{t} (GeV/c^{2})","#gamma");
  gr_gamma_gamma->Draw("AP");
  fit_gamma_gamma_up->SetLineColor(38); fit_gamma_gamma_up->SetLineStyle(2); fit_gamma_gamma_up->SetLineWidth(2);
  fit_gamma_gamma_up->Draw("same");
  fit_gamma_gamma_down->SetLineColor(38); fit_gamma_gamma_down->SetLineStyle(2); fit_gamma_gamma_down->SetLineWidth(2);
  fit_gamma_gamma_down->Draw("same");
  TLegend *leg_par_3 = new TLegend(0.4,0.82,0.9,0.9,NULL,"brNDC");
  leg_par_3->SetTextSize(0.025);
  leg_par_3->SetHeader("Shape parameter of the gamma distribution");
  leg_par_3->AddEntry(gr_gamma_gamma, TString::Format("#gamma = %2.0f + %2.4f#upointM_{t}",fit_gamma_gamma->GetParameter(0),fit_gamma_gamma->GetParameter(1)), "l");
  leg_myStyle(leg_par_3);
  leg_par_3->Draw("same");
  channel_tex->Draw("same");
  cms_myStyle(lumi, false);
  TString out_par_3 = outdir+"Parameter_gamma_shape";
  cn_par_3->SaveAs(out_par_3+".pdf");
  cn_par_3->SaveAs(out_par_3+".C");
  cn_par_3->SaveAs(out_par_3+".jpg");
  cn_par_3->SaveAs(out_par_3+".eps");


  TGraphErrors *gr_beta_gamma = new TGraphErrors(numberOfPoints,x,beta_gamma_val,0,beta_gamma_err);
  TFitResultPtr fitptr_beta_gamma = gr_beta_gamma->Fit("pol1","FS","");
  TF1 *fit_beta_gamma = gr_beta_gamma->GetFunction("pol1");
  fit_beta_gamma->SetLineColor(9);
  Double_t err_beta_gamma_up[numberOfPoints];
  Double_t err_beta_gamma_down[numberOfPoints];
  Double_t errval_beta_gamma[numberOfPoints];
  fitptr_beta_gamma->GetConfidenceIntervals(numberOfPoints,1,1,x,errval_beta_gamma,0.68);
  for(unsigned int k = 0; k < numberOfPoints; ++k) {
    double error = errval_beta_gamma[k];
    err_beta_gamma_up[k] = fit_beta_gamma->Eval(x[k])+error;
    err_beta_gamma_down[k] = fit_beta_gamma->Eval(x[k])-error;
  }
  TGraph *gr_beta_gamma_up = new TGraph(numberOfPoints,x,err_beta_gamma_up);
  gr_beta_gamma_up->Fit("pol2","Q","");
  TF1 *fit_beta_gamma_up = gr_beta_gamma_up->GetFunction("pol2");
  TGraph *gr_beta_gamma_down = new TGraph(numberOfPoints,x,err_beta_gamma_down);
  gr_beta_gamma_down->Fit("pol2","Q","");
  TF1 *fit_beta_gamma_down = gr_beta_gamma_down->GetFunction("pol2");  

  TCanvas *cn_par_4 = new TCanvas("cn_par_4","cn_par_4",800,800);
  cn_par_4->cd();
  gr_myStyle(gr_beta_gamma,"gr_beta_gamma",1,9,1,9,1001,0.,60.,510,510,20,9,0.1,"M_{t} (GeV/c^{2})","#beta (GeV/c^{2})");
  gr_beta_gamma->Draw("AP");
  fit_beta_gamma_up->SetLineColor(38); fit_beta_gamma_up->SetLineStyle(2); fit_beta_gamma_up->SetLineWidth(2);
  fit_beta_gamma_up->Draw("same");
  fit_beta_gamma_down->SetLineColor(38); fit_beta_gamma_down->SetLineStyle(2); fit_beta_gamma_down->SetLineWidth(2);
  fit_beta_gamma_down->Draw("same");
  TLegend *leg_par_4 = new TLegend(0.4,0.82,0.9,0.9,NULL,"brNDC");
  leg_par_4->SetTextSize(0.025);
  leg_par_4->SetHeader("Scale parameter of the gamma distribution");
  leg_par_4->AddEntry(gr_beta_gamma, TString::Format("#beta = %2.0f + %2.2f#upointM_{t}",fit_beta_gamma->GetParameter(0),fit_beta_gamma->GetParameter(1)), "l");
  leg_myStyle(leg_par_4);
  leg_par_4->Draw("same");
  channel_tex->Draw("same");
  cms_myStyle(lumi, false);
  TString out_par_4 = outdir+"Parameter_gamma_scale";
  cn_par_4->SaveAs(out_par_4+".pdf");
  cn_par_4->SaveAs(out_par_4+".C");
  cn_par_4->SaveAs(out_par_4+".jpg");
  cn_par_4->SaveAs(out_par_4+".eps");


  TGraphErrors *gr_mu_gamma = new TGraphErrors(numberOfPoints,x,mu_gamma_val,0,mu_gamma_err);
  TFitResultPtr fitptr_mu_gamma = gr_mu_gamma->Fit("pol1","FS","");
  TF1 *fit_mu_gamma = gr_mu_gamma->GetFunction("pol1");
  fit_mu_gamma->SetLineColor(9);
  Double_t err_mu_gamma_up[numberOfPoints];
  Double_t err_mu_gamma_down[numberOfPoints];
  Double_t errval_mu_gamma[numberOfPoints];
  fitptr_mu_gamma->GetConfidenceIntervals(numberOfPoints,1,1,x,errval_mu_gamma,0.68);
  for(unsigned int k = 0; k < numberOfPoints; ++k) {
    double error = errval_mu_gamma[k];
    err_mu_gamma_up[k] = fit_mu_gamma->Eval(x[k])+error;
    err_mu_gamma_down[k] = fit_mu_gamma->Eval(x[k])-error;
  }
  TGraph *gr_mu_gamma_up = new TGraph(numberOfPoints,x,err_mu_gamma_up);
  gr_mu_gamma_up->Fit("pol2","Q","");
  TF1 *fit_mu_gamma_up = gr_mu_gamma_up->GetFunction("pol2");
  TGraph *gr_mu_gamma_down = new TGraph(numberOfPoints,x,err_mu_gamma_down);
  gr_mu_gamma_down->Fit("pol2","Q","");
  TF1 *fit_mu_gamma_down = gr_mu_gamma_down->GetFunction("pol2");  

  TCanvas *cn_par_5 = new TCanvas("cn_par_5","cn_par_5",800,800);
  cn_par_5->cd();
  gr_myStyle(gr_mu_gamma,"gr_mu_gamma",1,9,1,9,1001,0.,30.,510,510,20,9,0.1,"M_{t} (GeV/c^{2})","#mu (GeV/c^{2})");
  gr_mu_gamma->Draw("AP");
  fit_mu_gamma_up->SetLineColor(38); fit_mu_gamma_up->SetLineStyle(2); fit_mu_gamma_up->SetLineWidth(2);
  fit_mu_gamma_up->Draw("same");
  fit_mu_gamma_down->SetLineColor(38); fit_mu_gamma_down->SetLineStyle(2); fit_mu_gamma_down->SetLineWidth(2);
  fit_mu_gamma_down->Draw("same");
  TLegend *leg_par_5 = new TLegend(0.4,0.82,0.9,0.9,NULL,"brNDC");
  leg_par_5->SetTextSize(0.025);
  leg_par_5->SetHeader("Shift parameter of the gamma distribution");
  leg_par_5->AddEntry(gr_mu_gamma, TString::Format("#mu = %2.0f + %2.2f#upointM_{t}",fit_mu_gamma->GetParameter(0),fit_mu_gamma->GetParameter(1)), "l");
  leg_myStyle(leg_par_5);
  leg_par_5->Draw("same");
  channel_tex->Draw("same");
  cms_myStyle(lumi, false);
  TString out_par_5 = outdir+"Parameter_gamma_shift";
  cn_par_5->SaveAs(out_par_5+".pdf");
  cn_par_5->SaveAs(out_par_5+".C");
  cn_par_5->SaveAs(out_par_5+".jpg");
  cn_par_5->SaveAs(out_par_5+".eps");


  //===========================
  //    Data
  //===========================

  //---- Dataset
  TString dataName = indir;
  if (blind)
    dataName += "All_172_5.root";
  else 
    dataName += fileData;
  TFile *data_fi = TFile::Open(dataName);
  TTree *data_tree = (TTree*)data_fi->Get("MTriLept");
  RooDataSet *data_dataset = new RooDataSet("data_dataset", "data_dataset", RooArgSet(mtl, weight), Import(*data_tree), WeightVar(weight));

  //---- Fit des data avec un seul parametre : la masse du top
  mt.setVal(172.5);
  RooConstVar mean_gaus_0("mean_gaus_0","mean_gaus_0",fit_mean_gaus->GetParameter(0));
  RooConstVar mean_gaus_1("mean_gaus_1","mean_gaus_1",fit_mean_gaus->GetParameter(1));
  RooFormulaVar mean_gaus("mean_gaus","@0+@1*@2",RooArgList(mean_gaus_0,mean_gaus_1,mt));
  RooConstVar width_gaus_0("width_gaus_0","width_gaus_0",fit_width_gaus->GetParameter(0));
  RooConstVar width_gaus_1("width_gaus_1","width_gaus_1",fit_width_gaus->GetParameter(1));
  RooFormulaVar width_gaus("width_gaus","@0+@1*@2",RooArgList(width_gaus_0,width_gaus_1,mt));
  RooGaussian pdf_gaus("pdf_gaus","pdf_gaus",mtl,mean_gaus,width_gaus);

  RooConstVar gamma_gamma_0("gamma_gamma_0","gamma_gamma_0",fit_gamma_gamma->GetParameter(0));
  RooConstVar gamma_gamma_1("gamma_gamma_1","gamma_gamma_1",fit_gamma_gamma->GetParameter(1));
  RooFormulaVar gamma_gamma("gamma_gamma","@0+@1*@2",RooArgList(gamma_gamma_0,gamma_gamma_1,mt));
  RooConstVar beta_gamma_0("beta_gamma_0","beta_gamma_0",fit_beta_gamma->GetParameter(0));
  RooConstVar beta_gamma_1("beta_gamma_1","beta_gamma_1",fit_beta_gamma->GetParameter(1));
  RooFormulaVar beta_gamma("beta_gamma","@0+@1*@2",RooArgList(beta_gamma_0,beta_gamma_1,mt));
  RooConstVar mu_gamma_0("mu_gamma_0","mu_gamma_0",fit_mu_gamma->GetParameter(0));
  RooConstVar mu_gamma_1("mu_gamma_1","mu_gamma_1",fit_mu_gamma->GetParameter(1));
  RooFormulaVar mu_gamma("mu_gamma","@0+@1*@2",RooArgList(mu_gamma_0,mu_gamma_1,mt));
  RooGamma pdf_gamma("pdf_gamma","pdf_gamma",mtl,gamma_gamma,beta_gamma,mu_gamma);

  RooConstVar ncat_0("ncat_0","ncat_0",fit_ncat->GetParameter(0));
  RooConstVar ncat_1("ncat_1","ncat_1",fit_ncat->GetParameter(1));
  RooFormulaVar ncat("ncat","@0+@1*@2",RooArgList(ncat_0,ncat_1,mt));
  RooAddPdf model("model","sumpdf",RooArgList(pdf_gaus,pdf_gamma),RooArgList(ncat)) ;

  RooAbsReal* nll_res = model.createNLL(*data_dataset, NumCPU(NCPU));
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
  data_dataset->plotOn(frame,Binning(25));
  model.plotOn(frame,FillColor(38),VisualizeError(*result_final)) ;
  model.plotOn(frame,LineColor(9)) ;
  model.plotOn(frame,Components(pdf_gamma),LineStyle(kDashed),LineColor(kBlue));
  model.plotOn(frame,Components(pdf_gaus),LineStyle(kDashed),LineColor(kRed));
  frame->Draw();
  TLegend *leg_fit_data = new TLegend(0.58,0.82,0.9,0.9,NULL,"brNDC");
  leg_fit_data->SetHeader(TString::Format("M_{t} = (%3.1f #pm %1.1f) GeV/c^{2}", mt.getVal(), mt.getError()));
  leg_myStyle(leg_fit_data);
  leg_fit_data->Draw("same");
  channel_tex->Draw("same");
  TString out_fit_data = outdir;
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
  leg_nll_data->SetHeader(TString::Format("M_{t} = (%3.1f #pm %1.1f) GeV/c^{2}", mt.getVal(), mt.getError()));
  leg_myStyle(leg_nll_data);
  leg_nll_data->Draw("same");
  channel_tex->Draw("same");
  TString out_nll_data = outdir;
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
  frame->Draw();
  TLegend *leg_res_data = new TLegend(0.58,0.42,0.9,0.5,NULL,"brNDC");
  leg_res_data->SetHeader(TString::Format("M_{t} = (%3.1f #pm %1.1f) GeV/c^{2}", mt.getVal(), mt.getError()));
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
  likeframe->SetTitleOffset(3.,"X");
  likeframe->SetTitleOffset(4.,"Y");
  likeframe->SetTitleSize(LABEL_FONTSIZE,"XY");
  likeframe->GetXaxis()->SetNdivisions(506);
  likeframe->Draw();
  TString out_res_data = outdir;
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
  double mean_gaus_v[r] = {mean_gaus.getVal()}; double mean_gaus_e[r] = {mt.getError()*fit_mean_gaus->GetParameter(1)};
  TGraphErrors *gr_mean_gaus_res = new TGraphErrors(r,mt_v,mean_gaus_v,mt_e,mean_gaus_e);
  gr_myStyle(gr_mean_gaus_res,"gr_mean_gaus_res",1,46,1,46,1001,-1111.,-1111.,510,510,20,46,1.1,"","");
  gr_mean_gaus_res->Draw("Psame");
  TString out_res_0 = outdir;
  if (blind)
    out_res_0 += "BlindedParameter_gaussian_mean";
  else 
    out_res_0 += "UnblindedParameter_gaussian_mean";
  cn_par_0->SaveAs(out_res_0+".pdf");
  cn_par_0->SaveAs(out_res_0+".C");
  cn_par_0->SaveAs(out_res_0+".jpg");
  cn_par_0->SaveAs(out_res_0+".eps");

  cn_par_1->cd();
  double width_gaus_v[r] = {width_gaus.getVal()}; double width_gaus_e[r] = {mt.getError()*fit_width_gaus->GetParameter(1)};
  TGraphErrors *gr_width_gaus_res = new TGraphErrors(r,mt_v,width_gaus_v,mt_e,width_gaus_e);
  gr_myStyle(gr_width_gaus_res,"gr_width_gaus_res",1,46,1,46,1001,-1111.,-1111.,510,510,20,46,1.1,"","");
  gr_width_gaus_res->Draw("Psame");
  TString out_res_1 = outdir;
  if (blind)
    out_res_1 += "BlindedParameter_gaussian_width";
  else
    out_res_1 += "UnblindedParameter_gaussian_width";
  cn_par_1->SaveAs(out_res_1+".pdf");
  cn_par_1->SaveAs(out_res_1+".C");
  cn_par_1->SaveAs(out_res_1+".jpg");
  cn_par_1->SaveAs(out_res_1+".eps");

  cn_par_2->cd();
  double ncat_v[r] = {ncat.getVal()}; double ncat_e[r] = {mt.getError()*fit_ncat->GetParameter(1)};
  TGraphErrors *gr_ncat_res = new TGraphErrors(r,mt_v,ncat_v,mt_e,ncat_e);
  gr_myStyle(gr_ncat_res,"gr_ncat_res",1,46,1,46,1001,-1111.,-1111.,510,510,20,46,1.1,"","");
  gr_ncat_res->Draw("Psame");
  TString out_res_2 = outdir;
  if (blind)
    out_res_2 += "BlindedParameter_gaussian_relcont";
  else 
    out_res_2 += "UnblindedParameter_gaussian_relcont";
  cn_par_2->SaveAs(out_res_2+".pdf");
  cn_par_2->SaveAs(out_res_2+".C");
  cn_par_2->SaveAs(out_res_2+".jpg");
  cn_par_2->SaveAs(out_res_2+".eps");

  cn_par_3->cd();
  double gamma_gamma_v[r] = {gamma_gamma.getVal()}; double gamma_gamma_e[r] = {mt.getError()*fit_gamma_gamma->GetParameter(1)};
  TGraphErrors *gr_gamma_gamma_res = new TGraphErrors(r,mt_v,gamma_gamma_v,mt_e,gamma_gamma_e);
  gr_myStyle(gr_gamma_gamma_res,"gr_gamma_gamma_res",1,46,1,46,1001,-1111.,-1111.,510,510,20,46,1.1,"","");
  gr_gamma_gamma_res->Draw("Psame");
  TString out_res_3 = outdir;
  if (blind)
    out_res_3 += "BlindedParameter_gamma_shape";
  else 
    out_res_3 += "UnblindedParameter_gamma_shape";
  cn_par_3->SaveAs(out_res_3+".pdf");
  cn_par_3->SaveAs(out_res_3+".C");
  cn_par_3->SaveAs(out_res_3+".jpg");
  cn_par_3->SaveAs(out_res_3+".eps");

  cn_par_4->cd();
  double beta_gamma_v[r] = {beta_gamma.getVal()}; double beta_gamma_e[r] = {mt.getError()*fit_beta_gamma->GetParameter(1)};
  TGraphErrors *gr_beta_gamma_res = new TGraphErrors(r,mt_v,beta_gamma_v,mt_e,beta_gamma_e);
  gr_myStyle(gr_beta_gamma_res,"gr_beta_gamma_res",1,46,1,46,1001,-1111.,-1111.,510,510,20,46,1.1,"","");
  gr_beta_gamma_res->Draw("Psame");
  TString out_res_4 = outdir;
  if (blind)
    out_res_4 += "BlindedParameter_gamma_scale";
  else 
    out_res_4 += "UnblindedParameter_gamma_scale";
  cn_par_4->SaveAs(out_res_4+".pdf");
  cn_par_4->SaveAs(out_res_4+".C");
  cn_par_4->SaveAs(out_res_4+".jpg");
  cn_par_4->SaveAs(out_res_4+".eps");

  cn_par_5->cd();
  double mu_gamma_v[r] = {mu_gamma.getVal()}; double mu_gamma_e[r] = {mt.getError()*fit_mu_gamma->GetParameter(1)};
  TGraphErrors *gr_mu_gamma_res = new TGraphErrors(r,mt_v,mu_gamma_v,mt_e,mu_gamma_e);
  gr_myStyle(gr_mu_gamma_res,"gr_mu_gamma_res",1,46,1,46,1001,-1111.,-1111.,510,510,20,46,1.1,"","");
  gr_mu_gamma_res->Draw("Psame");
  TString out_res_5 = outdir;
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
      model.fitTo(*gen_dataset, Save(), PrintLevel(-1), PrintEvalErrors(-1));  

      //---- fill des histos
      hist_residual->Fill(mt.getVal()-mti_v[0]);
      hist_pull->Fill((mt.getVal()-mti_v[0])/mt.getError());
      hist_mean->Fill(mt.getVal());
      hist_err->Fill(mt.getError());
    }

    TCanvas *cn_mean = new TCanvas("cn_mean","cn_mean",800,800);
    cn_mean->cd();
    h_myStyle(hist_mean, 0, 38, 1, 38, 3002, 0, 1.1*hist_mean->GetMaximum(), 510, 510, 20, 38, 1.2, 1, "#tilde{M}_{t}^{toy} (GeV/c^{2})");
    hist_mean->Draw("hist");
    TLegend *leg_mean = new TLegend(0.7,0.62,0.9,0.7,NULL,"brNDC");
    leg_mean->SetTextSize(0.025);
    //leg_mean->SetHeader(TString::Format("Generated at M_{t} = %4.2f GeV/c^{2}", mti_v[0]));
    leg_mean->AddEntry((TObject*)0,"Generated at","");
    leg_mean->AddEntry((TObject*)0,TString::Format("M_{t} = %4.2f GeV/c^{2}", mti_v[0]),"");
    leg_myStyle(leg_mean);
    leg_mean->Draw("same");
    channel_tex->Draw("same");
    TString out_mean = outdir;
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
    h_myStyle(hist_err, 0, 38, 1, 38, 3002, 0, 1.1*hist_err->GetMaximum(), 510, 510, 20, 38, 1.2, 1, "#Delta#tilde{M}_{t}^{toy} (GeV/c^{2})");
    hist_err->Draw("hist");
    TLegend *leg_err = new TLegend(0.7,0.62,0.9,0.7,NULL,"brNDC");
    leg_err->SetTextSize(0.025);
    leg_err->SetHeader(TString::Format("Toys of #approx%d events", nevt));
    leg_myStyle(leg_err);
    leg_err->Draw("same");
    channel_tex->Draw("same");
    TString out_err = outdir;
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
    h_myStyle(hist_pull, 0, 38, 1, 38, 3002, 0, 1.1*hist_pull->GetMaximum(), 510, 510, 20, 38, 1.2, 1, "(#tilde{M}_{t}^{toy}-#tilde{M}_{t}^{gen})/#Delta #tilde{M}_{t}^{toy}");
    hist_pull->Draw("hist");
    hist_pull->Fit("gaus","Q","");
    TF1 *fit_pull_gaus = hist_pull->GetFunction("gaus");
    fit_pull_gaus->SetLineColor(38); fit_pull_gaus->SetLineWidth(2);
    fit_pull_gaus->Draw("same");
    TLegend *leg_pull = new TLegend(0.67,0.62,0.9,0.7,NULL,"brNDC");
    leg_pull->SetTextSize(0.025);
    leg_pull->SetHeader("Gaussian fit parameters:");
    leg_pull->AddEntry((TObject*)0, TString::Format("#mu = (%4.3f #pm %4.3f) GeV/c^{2}",fit_pull_gaus->GetParameter(1),fit_pull_gaus->GetParError(1)), "");
    leg_pull->AddEntry((TObject*)0, TString::Format("#sigma = (%4.3f #pm %4.3f) GeV/c^{2}",fit_pull_gaus->GetParameter(2),fit_pull_gaus->GetParError(2)), "");
    leg_myStyle(leg_pull);
    leg_pull->Draw("same");
    channel_tex->Draw("same");
    TString out_pull = outdir;
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
    h_myStyle(hist_residual, 0, 38, 1, 38, 3002, 0, 1.1*hist_residual->GetMaximum(), 510, 510, 20, 38, 1.2, 1, "#tilde{M}_{t}^{toy}-#tilde{M}_{t}^{gen} (GeV/c^{2})");
    hist_residual->Draw("hist");
    hist_residual->Fit("gaus","Q","");
    TF1 *fit_residual_gaus = hist_residual->GetFunction("gaus");
    fit_residual_gaus->SetLineColor(38); fit_residual_gaus->SetLineWidth(2);
    fit_residual_gaus->Draw("same");
    TLegend *leg_residual = new TLegend(0.67,0.62,0.9,0.7,NULL,"brNDC");
    leg_residual->SetTextSize(0.025);
    leg_residual->SetHeader("Gaussian fit parameters:");
    leg_residual->AddEntry((TObject*)0, TString::Format("#mu = (%4.3f #pm %4.3f) GeV/c^{2}",fit_residual_gaus->GetParameter(1),fit_residual_gaus->GetParError(1)), "");
    leg_residual->AddEntry((TObject*)0, TString::Format("#sigma = (%4.3f #pm %4.3f) GeV/c^{2}",fit_residual_gaus->GetParameter(2),fit_residual_gaus->GetParError(2)), "");
    leg_myStyle(leg_residual);
    leg_residual->Draw("same");
    channel_tex->Draw("same");
    TString out_residual = outdir;
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
  gr_myStyle(gr_mean_res,"gr_mean_res",1,9,1,9,1001,-3.,3.,510,510,20,9,1.1,"M_{t}^{gen} (GeV/c^{2})","residual mean (GeV/c^{2})");
  TFitResultPtr fitptr_mean_res = gr_mean_res->Fit("pol1","FS","");
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
  TLegend *leg_mean_res = new TLegend(0.58,0.82,0.9,0.9,NULL,"brNDC");
  leg_mean_res->SetHeader(TString::Format("c = (%0.3f #pm %0.3f) GeV/c^{2}",fit_mean_res->Eval(173.),mean_residual_e[n172p5]));
  leg_myStyle(leg_mean_res);
  leg_mean_res->Draw("same");
  channel_tex->Draw("same");
  cms_myStyle(lumi, false);
  TString out_gr_mean_res =outdir+"Mean_Residual";
  cn_gr_mean_res->SaveAs(out_gr_mean_res+".pdf");
  cn_gr_mean_res->SaveAs(out_gr_mean_res+".C");
  cn_gr_mean_res->SaveAs(out_gr_mean_res+".jpg");
  cn_gr_mean_res->SaveAs(out_gr_mean_res+".eps");

  TCanvas *cn_gr_width_pull = new TCanvas("cn_gr_width_pull","cn_gr_width_pull",800,800);
  cn_gr_width_pull->cd();
  TGraphErrors *gr_width_pull = new TGraphErrors(nttbar,mttbar,width_pull,0,width_pull_e);
  gr_myStyle(gr_width_pull,"gr_width_pull",1,9,1,9,1001,0.7,1.3,510,510,20,9,1.1,"M_{t}^{gen} (GeV/c^{2})","pull width");
  TFitResultPtr fitptr_width_pull = gr_width_pull->Fit("pol1","FS","");
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
  TLegend *leg_width_pull = new TLegend(0.58,0.82,0.9,0.9,NULL,"brNDC");
  leg_width_pull->SetHeader(TString::Format("c = %0.3f #pm %0.3f",fit_width_pull->Eval(173.),width_pull_e[n172p5]));
  leg_myStyle(leg_width_pull);
  leg_width_pull->Draw("same");
  channel_tex->Draw("same");
  cms_myStyle(lumi, false);
  TString out_gr_width_pull =outdir+"Width_Pull";
  cn_gr_width_pull->SaveAs(out_gr_width_pull+".pdf");
  cn_gr_width_pull->SaveAs(out_gr_width_pull+".C");
  cn_gr_width_pull->SaveAs(out_gr_width_pull+".jpg");
  cn_gr_width_pull->SaveAs(out_gr_width_pull+".eps");

  TCanvas *cn_gr_mean_pull = new TCanvas("cn_gr_mean_pull","cn_gr_mean_pull",800,800);
  cn_gr_mean_pull->cd();
  TGraphErrors *gr_mean_pull = new TGraphErrors(nttbar,mttbar,mean_pull,0,mean_pull_e);
  gr_myStyle(gr_mean_pull,"gr_mean_pull",1,9,1,9,1001,-1.,1.,510,510,20,9,1.1,"M_{t}^{gen} (GeV/c^{2})","pull mean");
  TFitResultPtr fitptr_mean_pull = gr_mean_pull->Fit("pol1","FS","");
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
  TLegend *leg_mean_pull = new TLegend(0.58,0.82,0.9,0.9,NULL,"brNDC");
  leg_mean_pull->SetHeader(TString::Format("c = %0.3f #pm %0.3f",fit_mean_pull->Eval(173.),mean_pull_e[n172p5]));
  leg_myStyle(leg_mean_pull);
  leg_mean_pull->Draw("same");
  channel_tex->Draw("same");
  cms_myStyle(lumi, false);
  TString out_gr_mean_pull =outdir+"Mean_Pull";
  cn_gr_mean_pull->SaveAs(out_gr_mean_pull+".pdf");
  cn_gr_mean_pull->SaveAs(out_gr_mean_pull+".C");
  cn_gr_mean_pull->SaveAs(out_gr_mean_pull+".jpg");
  cn_gr_mean_pull->SaveAs(out_gr_mean_pull+".eps");

  TCanvas *cn_gr_width_res = new TCanvas("cn_gr_width_res","cn_gr_width_res",800,800);
  cn_gr_width_res->cd();
  TGraphErrors *gr_width_res = new TGraphErrors(nttbar,mttbar,width_residual,0,width_residual_e);
  gr_myStyle(gr_width_res,"gr_width_res",1,9,1,9,1001,1.,8.,510,510,20,9,1.1,"M_{t}^{gen} (GeV/c^{2})","residual width (GeV/c^{2})");
  TFitResultPtr fitptr_width_res = gr_width_res->Fit("pol1","FS","");
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
  TLegend *leg_width_res = new TLegend(0.58,0.82,0.9,0.9,NULL,"brNDC");
  leg_width_res->SetHeader(TString::Format("c = (%0.3f #pm %0.3f) GeV/c^{2}",fit_width_res->Eval(173.),width_residual_e[n172p5]));
  leg_myStyle(leg_width_res);
  leg_width_res->Draw("same");
  channel_tex->Draw("same");
  cms_myStyle(lumi, false);
  TString out_gr_width_res =outdir+"Width_Residual";
  cn_gr_width_res->SaveAs(out_gr_width_res+".pdf");
  cn_gr_width_res->SaveAs(out_gr_width_res+".C");
  cn_gr_width_res->SaveAs(out_gr_width_res+".jpg");
  cn_gr_width_res->SaveAs(out_gr_width_res+".eps");

  data_fi->Close(); 
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
int simpleFit(TString date = "", TString version = "", bool blind = true)
//---------------------------------------------------------------
{  
  if (date.Length() > 0 && version.Length() > 0)  {

    cout << "/!\\ you should have run mergeMC.C and mergeChannels.py before \n" << endl; 

    vector<double> mtop; mtop.push_back(166.5); mtop.push_back(169.5); mtop.push_back(171.5); mtop.push_back(173.5); mtop.push_back(175.5); mtop.push_back(178.5);
    vector<double> mtoys; mtoys.push_back(167.); mtoys.push_back(169.); mtoys.push_back(171.); mtoys.push_back(172.5); mtoys.push_back(174.); mtoys.push_back(176.); mtoys.push_back(178);
    double mtlim[2] = {130, 216};
    const unsigned int nsample = 3000.;
    int nevt[2] = {274, 311};

    if (blind)
      cout << "Running the blinded analysis: \"data\" is the full-stat MC sample generated at 173.5 GeV/c^{2} " << endl; 
    else  
      cout << "Running the unblinded analysis: \"data\" is Run2012ABCD" << endl; 
    cout << "Performing a simple unbinned likelihood fit (gaussian+gamma function) for M_{t} = "<< mtop[0] << ", " << mtop[1] << ", " << mtop[2] << ", " << mtop[3] << ", " << mtop[4] << ", " << mtop [5] << " GeV/c^{2}" << endl;
    cout << "Toys in the e + Jets channel: " << nsample << " toys of Poisson(" << nevt[0] << ") events" << endl;
    cout << "Toys in the #mu + Jets channel: " << nsample << " toys of Poisson(" << nevt[1] << ") events" << endl;
    cout << "Toys in the l + Jets channel: " << nsample << " toys of Poisson(" << nevt[0]+nevt[1] << ") events" << endl;
    cout << "for M_{t} = " << mtoys[0] << ", " << mtoys[1] << ", " << mtoys[2] << ", " << mtoys[3] << ", " << mtoys[4] << ", " << mtoys[5] << ", " << mtoys[6] << " GeV/c^{2}" << endl;

    cout << "\n===================================================\n" <<endl;

    getchar();

    TStyle* my_style = createMyStyle();
    my_style->cd();
    gROOT->SetBatch(true);

    double *mtop_el = treat("ElectronHadASingleElectronBCD.root", 19.7, nevt[0], mtop, mtlim, mtoys, nsample, date, version, blind); 
    double *mtop_mu = treat("MuHadASingleMuBCD.root", 19.7, nevt[1], mtop, mtlim, mtoys, nsample, date, version, blind); 
    double *mtop_all = treat("Run2012ABCD.root", 19.7, nevt[0]+nevt[1], mtop, mtlim, mtoys, nsample, date, version, blind); 

    cout << "\n===================================================\n" <<endl;

    double *mtop_combi = combi(mtop_el[0], mtop_el[1], mtop_mu[0], mtop_mu[1]); 
    TString result1 = TString::Format("Combining e + Jets and #mu + Jets channels AFTER fits: \n \t \t \t M_{t} = (%3.1f #pm %3.1f) GeV/c^{2}", mtop_combi[0], mtop_combi[1]);
    cout << result1 << endl;
    TString result2 = TString::Format("Combining e + Jets and #mu + Jets channels BEFORE fits: \n \t \t \t M_{t} = (%3.1f #pm %3.1f) GeV/c^{2}", mtop_all[0], mtop_all[1]);
    cout << result2 << endl;

    return 0;
  }
  else 
    return 1;
}



