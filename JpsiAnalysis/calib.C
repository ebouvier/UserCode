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
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "RooLandau.h"
#include "RooPlot.h"
#include "RooArgSet.h"

#pragma once

#define TITLE_FONTSIZE 26
#define LABEL_FONTSIZE 18

#define LEFT_MARGIN 0.17
#define RIGHT_MARGIN 0.03
#define TOP_MARGIN 0.05
#define BOTTOM_MARGIN 0.13

/*
 * Simple calibration with a gaussian (un)binned likelihood fit around the trilepton mass peak
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

void poly_myStyle(TPolyLine *pl,
    int line_width=2,
    int line_color=1,
    int line_style=1,
    int fill_color=1,
    int fill_style=3001) {
  pl->SetLineWidth(line_width);
  pl->SetLineColor(line_color);
  pl->SetLineStyle(line_style);
  pl->SetFillColor(fill_color);
  pl->SetFillStyle(fill_style);
}

void line_myStyle(TLine *li,
    int line_width=2,
    int line_color=1,
    int line_style=1) {
  li->SetLineWidth(line_width);
  li->SetLineColor(line_color);
  li->SetLineStyle(line_style);
}

void h_myStyle(TH1 *h,
    int line_color=1,
    int fill_color=50,
    int fill_style=1001,
    double y_min=-1111.,
    double y_max=-1111.,
    int ndivx=510,
    int ndivy=510,
    int marker_style=20,
    int marker_color=1,
    double marker_size=1.2,
    int optstat=0) {

  h->SetLineColor(line_color);
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
}

void grapherrors_myStyle(TGraphErrors *gr,
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
  std::string status = "Preliminary Simulation";
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
double *binnedFit(TString fiName, vector<double> xlim, double mtop, TLatex *channel_tex, TString outdir, double lumi)
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

  TFile *res = TFile::Open(fiName);

  RooRealVar mtl("mass", "M_{J/#psi+l}", 0., 250., "GeV");
  //RooRealVar mean("mean", "mass", (xlim[1]+xlim[0])/2., (xlim[1]+3.*xlim[0])/4., (3.*xlim[1]+xlim[0])/4.);
  RooRealVar mean("mean", "mass", 70., 60., 80.);
  RooRealVar width("width", "width", 25., 15., 40.);

  TH1F *histo = (TH1F*)res->Get("MTriLept-allPair");
  h_myStyle(histo,38,38,3002,histo->GetMinimum(),1.2*histo->GetMaximum(),510,510,20,38,1.,0.);
  RooDataHist *datahist = new RooDataHist("datahist", "datahist", RooArgList(mtl), histo, 1.);
  RooGaussian pdf("gaus", "gaus", mtl, mean, width);
  pdf.fitTo(*datahist, Range(xlim[0], xlim[1]), SumW2Error(kTRUE), PrintLevel(-1), PrintEvalErrors(-1));

  TCanvas *cn = new TCanvas("cn", "cn", 800, 800);
  cn->cd();
  RooPlot *massframe = mtl.frame();
  datahist->plotOn(massframe, MarkerColor(38), LineColor(38), DataError(RooAbsData::SumW2));
  pdf.plotOn(massframe, LineColor(38), Range(xlim[0], xlim[1]));
  massframe->Draw();
  histo->Draw("samehist");
  TLegend *leg = new TLegend(0.58,0.82,0.93,0.92,NULL,"brNDC");
  if (mtop < 1e-6)
    leg->SetHeader(TString::Format("#tilde{M}_{J/#psi+l} = (%3.1f #pm %3.1f) GeV", mean.getVal(), mean.getError()));
  else
    leg->SetHeader(TString::Format("#splitline{M_{t}^{gen} = %3.1f GeV}{#tilde{M}_{J/#psi+l} = (%3.1f #pm %3.1f) GeV}", mtop+0.5, mean.getVal(), mean.getError()));
  leg_myStyle(leg);
  leg->Draw("same");
  channel_tex->Draw("same");
  if (mtop < 1e-6)
    cms_myStyle(lumi, true);
  else
    cms_myStyle(lumi, false);
  TString outFile = outdir;
  if (mtop < 1e-6)
    outFile += "GausianBinnedFit_Data";
  else
    outFile += TString::Format("GaussianBinnedFit_%d_5", (int)mtop);
  cn->SaveAs(outFile+".pdf");
  cn->SaveAs(outFile+".C");
  cn->SaveAs(outFile+".jpg");
  cn->SaveAs(outFile+".eps");

  res->Close();

  double *mean_err = new double[2];
  mean_err[0] = mean.getVal();
  mean_err[1] = mean.getError();

  return mean_err;
}

//---------------------------------------------------------------
double *unbinnedFit(TString fiName, vector<double> xlim, double mtop, TLatex *channel_tex, TString outdir, double lumi)
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

  TFile *res = TFile::Open(fiName);

  RooRealVar mtl("mass", "M_{J/#psi+l}", 0., 250., "GeV");
  RooRealVar weight("weight", "weight", 0., 2.);
  //RooRealVar mean("mean", "mass", (xlim[1]+xlim[0])/2., (xlim[1]+3.*xlim[0])/4., (3.*xlim[1]+xlim[0])/4.);
  RooRealVar mean("mean", "mass", 70., 60., 80.);
  RooRealVar width("width", "width", 25., 15., 40.);

  TTree *tree = (TTree*)res->Get("MTriLept");
  RooDataSet *dataset = new RooDataSet("dataset", "dataset", RooArgSet(mtl, weight), Import(*tree), WeightVar(weight));
  RooGaussian pdf("gaus", "gaus", mtl, mean, width);
  pdf.fitTo(*dataset, Range(xlim[0], xlim[1]), SumW2Error(kTRUE), PrintLevel(-1), PrintEvalErrors(-1));

  TCanvas *cn = new TCanvas("cn", "cn", 800, 800);
  cn->cd();
  RooPlot *massframe = mtl.frame();
  if (mtop < 1e-6)
    dataset->plotOn(massframe, Binning(25), DataError(RooAbsData::SumW2));
  else
    dataset->plotOn(massframe, Binning(50), DataError(RooAbsData::SumW2));
  pdf.plotOn(massframe, Range(xlim[0], xlim[1]));
  massframe->Draw();
  TLegend *leg = new TLegend(0.58,0.82,0.93,0.92,NULL,"brNDC");
  if (mtop < 1e-6)
    leg->SetHeader(TString::Format("#tilde{M}_{J/#psi+l} = (%3.1f #pm %3.1f) GeV", mean.getVal(), mean.getError()));
  else
    leg->SetHeader(TString::Format("#splitline{M_{t}^{gen} = %3.1f GeV}{#tilde{M}_{J/#psi+l} = (%3.1f #pm %3.1f) GeV}", mtop+0.5, mean.getVal(), mean.getError()));
  leg_myStyle(leg);
  leg->Draw("same");
  channel_tex->Draw("same");
  if (mtop < 1e-6)
    cms_myStyle(lumi, true);
  else
    cms_myStyle(lumi, false);
  TString outFile = outdir;
  if (mtop < 1e-6)
    outFile += "GausianUnbinnedFit_Data";
  else
    outFile += TString::Format("GaussianUnbinnedFit_%d_5", (int)mtop);
  cn->SaveAs(outFile+".pdf");
  cn->SaveAs(outFile+".C");
  cn->SaveAs(outFile+".jpg");
  cn->SaveAs(outFile+".eps");

  res->Close();

  double *mean_err = new double[2];
  mean_err[0] = mean.getVal();
  mean_err[1] = mean.getError();

  return mean_err;
}

//---------------------------------------------------------------
double *treat(TString fileData, double lumi, TString decay, vector<double> mtop, vector<double> xlim, int binned, TString date, TString version) 
//---------------------------------------------------------------
{
  //TString indir = date+"/v"+version+"/";
  TString indir = date+"/"+version+"/";
  TString outdir = indir;
  TString channel = " + Jets channel";
  if (fileData.Contains("ElectronHad")) {
    outdir += "CalibEl/";
    indir += "MyAnaEl/";
    if (decay.Contains("semi", TString::kIgnoreCase))
      channel = "e"+channel;
    if (decay.Contains("di", TString::kIgnoreCase))
      channel = "ee/e#mu"+channel;
    if (decay.Contains("all", TString::kIgnoreCase))
      channel = "e/ee/e#mu"+channel;
  }
  if (fileData.Contains("MuHad")) {
    outdir += "CalibMu/";
    indir += "MyAnaMu/";
    if (decay.Contains("semi", TString::kIgnoreCase))
      channel = "#mu"+channel;
    if (decay.Contains("di", TString::kIgnoreCase))
      channel = "#mu#mu/#mue"+channel;
    if (decay.Contains("all", TString::kIgnoreCase))
      channel = "#mu/#mu#mu/#mue"+channel;
  }
  if (fileData.Contains("Run2012")) {
    outdir += "CalibAll/";
    indir += "MyAnaAll/";
    if (decay.Contains("semi", TString::kIgnoreCase))
      channel = "e/#mu"+channel;
    if (decay.Contains("di", TString::kIgnoreCase))
      channel = "ee/#mu#mu/e#mu"+channel;
    if (decay.Contains("all", TString::kIgnoreCase))
      channel = "e/#mu/ee/#mu#mu/e#mu"+channel;
  }
  gROOT->ProcessLine(".! mkdir "+outdir);
  TLatex* channel_tex = new TLatex(0.22, 0.9, channel);
  channel_tex->SetNDC(true);
  channel_tex->SetTextFont(43);
  channel_tex->SetTextSize(TITLE_FONTSIZE - 6);

  const unsigned int numberOfPoints = mtop.size(); 
  double x[numberOfPoints], ex[numberOfPoints];
  double y[numberOfPoints], ey[numberOfPoints];

  for (unsigned int itop = 0; itop < numberOfPoints; itop++) {
    TString fileMC = TString::Format("All_%d_5.root", (int)mtop[itop]);
    //TString fileMC = TString::Format("TTJets_MSDecays_JpsiFilter_%d_5.root", (int)mtop[itop]);
    double *mean_err = new double[2];
    if (binned < 2)
      mean_err = unbinnedFit(indir+fileMC, xlim, mtop[itop], channel_tex, outdir, lumi);
    if (binned == 2)
      mean_err = binnedFit(indir+fileMC, xlim, mtop[itop], channel_tex, outdir, lumi);
    y[itop] = mean_err[0];
    ey[itop] = mean_err[1];
    x[itop] = mtop[itop]+0.5;
    ex[itop] = 0.;
  }

  TGraphErrors *gr = new TGraphErrors(numberOfPoints, x, y, ex, ey);

  TFitResultPtr fitptr = gr->Fit("pol1", "FSQ", "");
  TF1 *fit = gr->GetFunction("pol1");
  double yinte = fitptr->Parameter(0);
  double errYinte = fitptr->ParError(0);
  double slope = fitptr->Parameter(1);
  double errSlope = fitptr->ParError(1);
  double chi2 = fitptr->Chi2();
  double ndf = fitptr->Ndf();

  double err_up[numberOfPoints];
  double err_down[numberOfPoints];
  double err_val[numberOfPoints];
  fitptr->GetConfidenceIntervals(numberOfPoints, 1, 1, x, err_val, 0.68);
  for(unsigned int itop = 0; itop < numberOfPoints; itop++) {
    double error = err_val[itop];
    err_up[itop] = fit->Eval(x[itop]) + error;
    err_down[itop] = fit->Eval(x[itop]) - error;
  }

  TGraph *gr_up = new TGraph(numberOfPoints,x,err_up);
  gr_up->Fit("pol2","FQ","");
  TF1 *fit_up = gr_up->GetFunction("pol2");
  TGraph *gr_down = new TGraph(numberOfPoints,x,err_down);
  gr_down->Fit("pol2","FQ","");
  TF1 *fit_down = gr_down->GetFunction("pol2");  

  TLegend *leg_calib = new TLegend(0.2,0.75,0.5,0.83,NULL,"brNDC");
  leg_calib->SetTextSize(0.025);
  leg_calib->AddEntry(gr,TString::Format("Slope of %.2f #pm %.2f", slope, errSlope),"lp");
  leg_calib->SetHeader("Calibration curve");

  // Blinded analysis 
  
  TCanvas *cn_calib = new TCanvas("cn_calib", "cn_calib", 800, 800);
  cn_calib->cd();
  grapherrors_myStyle(gr,"gr",2,30,1,30,1001,-1111,-1111,510,510,21,36,1.,"M_{t} (GeV)","M_{J/#psi+l} (GeV)");
  gr->Draw("AP");
  cn_calib->Update();
  fit->SetLineColor(30);
  fit_up->SetLineColor(29); fit_up->SetLineStyle(2); fit_up->SetLineWidth(2);
  fit_up->Draw("same");
  fit_down->SetLineColor(29); fit_down->SetLineStyle(2); fit_down->SetLineWidth(2);
  fit_down->Draw("same");
  leg_myStyle(leg_calib);
  leg_calib->SetTextAlign(22);
  leg_calib->Draw();  
  channel_tex->Draw("same");
  cms_myStyle(lumi, false);
  TString outBlind = outdir;
  if (binned < 2)
    outBlind += "BlindedUnbinnedCalibration";
  if (binned == 2)
    outBlind += "BlindedBinnedCalibration";
  cn_calib->SaveAs(outBlind+".pdf");
  cn_calib->SaveAs(outBlind+".C");
  cn_calib->SaveAs(outBlind+".jpg");
  cn_calib->SaveAs(outBlind+".eps");

  // Unblinded analysis
  double *data_fit = new double[2];
  if (binned == 0)
    data_fit = unbinnedFit(indir+fileData, xlim, 0., channel_tex, outdir, lumi);
  if (binned > 0)
    data_fit = binnedFit(indir+fileData, xlim, 0., channel_tex, outdir, lumi);
  double mean_gaus = data_fit[0];
  double err_gaus = data_fit[1];
  TString mjpsil_res = TString::Format("M_{J/#psi+l} = (%3.1f #pm %3.1f) GeV", mean_gaus, err_gaus);

  double x_horiz[4]={gr->GetXaxis()->GetXmin(),fit->GetX(mean_gaus+err_gaus,0,250),fit->GetX(mean_gaus-err_gaus,0,250),gr->GetXaxis()->GetXmin()};
  double y_horiz[4]={mean_gaus+err_gaus,mean_gaus+err_gaus,mean_gaus-err_gaus,mean_gaus-err_gaus};
  TPolyLine *horiz = new TPolyLine(4,x_horiz,y_horiz);
  TLine *horiz_sup = new TLine(x_horiz[0], y_horiz[0], x_horiz[1], y_horiz[1]);
  TLine *horiz_med = new TLine(gr->GetXaxis()->GetXmin(), mean_gaus, fit->GetX(mean_gaus,0,250), mean_gaus);
  TLine *horiz_inf = new TLine(x_horiz[2], y_horiz[2], x_horiz[3], y_horiz[3]);
  double x_vert_min[4]={fit_up->GetX(mean_gaus-err_gaus,0,250),fit_up->GetX(mean_gaus-err_gaus,0,250),x_horiz[2],x_horiz[2]};
  double y_vert_min[4]={gr->GetYaxis()->GetXmin(),mean_gaus-err_gaus,mean_gaus-err_gaus,gr->GetYaxis()->GetXmin()};
  TPolyLine *vert_min = new TPolyLine(4,x_vert_min,y_vert_min);
  double x_vert_mean[4]={x_horiz[2],x_horiz[2],x_horiz[1],x_horiz[1]};
  double y_vert_mean[4]={gr->GetYaxis()->GetXmin(),y_horiz[2],y_horiz[1],gr->GetYaxis()->GetXmin()};
  TPolyLine *vert_mean = new TPolyLine(4,x_vert_mean,y_vert_mean);
  double x_vert_max[4]={x_horiz[1],x_horiz[1],fit_down->GetX(mean_gaus+err_gaus,0,250),fit_down->GetX(mean_gaus+err_gaus,0,250)};
  double y_vert_max[4]={gr->GetYaxis()->GetXmin(),mean_gaus+err_gaus,mean_gaus+err_gaus,gr->GetYaxis()->GetXmin()};
  TPolyLine *vert_max = new TPolyLine(4,x_vert_max,y_vert_max);
  TLine *vert1 = new TLine(x_vert_min[0],y_vert_min[0],x_vert_min[1],y_vert_min[1]);
  TLine *vert2 = new TLine(x_vert_mean[0],y_vert_mean[0],x_vert_mean[1],y_vert_mean[1]);
  TLine *vert3 = new TLine(fit->GetX(mean_gaus,0,250),y_vert_mean[0],fit->GetX(mean_gaus,0,250),mean_gaus);
  TLine *vert4 = new TLine(x_vert_mean[3],y_vert_mean[3],x_vert_mean[2],y_vert_mean[2]);
  TLine *vert5 = new TLine(x_vert_max[3],y_vert_max[3],x_vert_max[2],y_vert_max[2]);
  TString mt_res; 
  double pm_fit = (x_vert_mean[3]-x_vert_mean[0])/2.;
  double p_fit = x_vert_max[3]-x_vert_mean[3];
  double m_fit = x_vert_mean[0]-x_vert_min[0];
  if (fabs(p_fit-m_fit)<0.1) 
    mt_res= TString::Format("M_{t} = (%0.1f #pm %0.1f #pm %0.1f) GeV", fit->GetX(mean_gaus,0,250), pm_fit, fabs(m_fit));
  else 
    mt_res= TString::Format("M_{t} = (%0.1f #pm %0.1f #splitline{_{+ %0.1f}}{_{- %0.1f}}) GeV", fit->GetX(mean_gaus,0,250),pm_fit, fabs(p_fit), fabs(m_fit));
  double *mtop_res = new double[2];
  mtop_res[0] = fit->GetX(mean_gaus,0,250);
  mtop_res[1] = pm_fit + max(fabs(p_fit), fabs(m_fit));

  TLegend *leg_res = new TLegend(0.2,0.75,0.65,0.87,NULL,"brNDC");
  leg_res->SetTextSize(0.025);
  leg_res->AddEntry(gr,TString::Format("Slope of %.2f #pm %.2f", slope, errSlope),"lp");
  leg_res->AddEntry((TObject*)0, mjpsil_res, "");
  leg_res->AddEntry((TObject*)0, mt_res, "");

  TCanvas *cn_res = new TCanvas("cn_res", "cn_res", 800, 800);
  cn_res->cd();
  grapherrors_myStyle(gr,"gr",2,30,1,30,1001,-1111,-1111,510,510,21,36,1.,"M_{t} (GeV)","M_{J/#psi+l} (GeV)");
  gr->Draw("AP");
  cn_res->Update();
  fit->SetLineColor(30);
  fit_up->SetLineColor(29); fit_up->SetLineStyle(2); fit_up->SetLineWidth(2);
  fit_up->Draw("same");
  fit_down->SetLineColor(29); fit_down->SetLineStyle(2); fit_down->SetLineWidth(2);
  fit_down->Draw("same");
  poly_myStyle(horiz,0,30,1,9,3002);
  horiz->Draw("f");
  horiz->Draw("same");
  line_myStyle(horiz_sup,2,9,2);
  horiz_sup->Draw("same");
  line_myStyle(horiz_med,2,4,1);
  horiz_med->Draw("same");
  line_myStyle(horiz_inf,2,9,2);
  horiz_inf->Draw("same");
  poly_myStyle(vert_min,0,9,2,38,3003);
  vert_min->Draw("f");
  vert_min->Draw("same");
  poly_myStyle(vert_mean,0,30,1,9,3002);
  vert_mean->Draw("f");
  vert_mean->Draw("same");
  poly_myStyle(vert_max,2,38,2,38,3003);
  vert_max->Draw("f");
  vert_max->Draw("same");
  line_myStyle(vert1,2,38,2);
  vert1->Draw("same");
  line_myStyle(vert2,2,9,2);
  vert2->Draw("same");
  line_myStyle(vert3,2,4,1);
  vert3->Draw("same");
  line_myStyle(vert4,2,9,2);
  vert4->Draw("same");
  line_myStyle(vert5,2,38,2);
  vert5->Draw("same");
  leg_myStyle(leg_res);
  leg_res->SetTextAlign(22);
  leg_res->Draw();  
  channel_tex->Draw("same");
  cms_myStyle(lumi, true);
  TString outUnblind = outdir;
  if (binned == 0)
    outUnblind += "UnblindedUnbinnedCalibration";
  if (binned == 1)
    outUnblind += "UnblindedMixedCalibration";
  if (binned == 2)
    outUnblind += "UnblindedBinnedCalibration";
  cn_res->SaveAs(outUnblind+".pdf");
  cn_res->SaveAs(outUnblind+".C");
  cn_res->SaveAs(outUnblind+".jpg");
  cn_res->SaveAs(outUnblind+".eps");

  cout << "\n=============== " << channel <<" =================\n" <<endl;
  for (unsigned int itop = 0; itop < numberOfPoints; itop++)
    cout << "M_{top} = "<< x[itop] << " GeV, #tilde{M}_{J/#psi+l} = (" << y[itop] << " +/- "<< ey[itop] << ") GeV" << endl;
  cout << "\nCalibration:" << endl;
  cout << "#chi^{2}/Ndof = " << chi2/ndf << endl;
  cout << "slope = " << slope << " +/- " << errSlope << endl;
  cout << "y-intercept = " << yinte << " +/- " << errYinte << endl;
  if (binned == 0)
    cout << "\nUnbinned fit:" << endl;
  if (binned == 1)
    cout << "\nMixed fit:" << endl;
  if (binned == 2)
    cout << "\nBinned fit:" << endl;
  cout << mjpsil_res << endl;
  cout << mt_res << endl;
  cout << "\nFigures saved in " << outdir << endl;

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
int calib(TString date = "", TString version = "", TString decay = "", int binned = 0)
//---------------------------------------------------------------
{  
  TH1::SetDefaultSumw2(kTRUE);

  if (date.Length() > 0 && version.Length() > 0 && decay.Length() > 0)  {

    cout << "/!\\ you should have run mergeMC.C before \n" << endl;

    vector<double> mtop;
    mtop.push_back(166.); mtop.push_back(169.); mtop.push_back(171.); mtop.push_back(172.); mtop.push_back(173.); mtop.push_back(175.); mtop.push_back(178.);

    vector<double> xlim;
    xlim.push_back(30.); xlim.push_back(110.);

    if (binned == 0)
      cout << "Performing a gaussian unbinned likelihood fit for data and MC between " << xlim[0] << " and " << xlim[1] << endl;
    if (binned == 1)
      cout << "Performing a gaussian (un)binned likelihood fit for data (and MC) between " << xlim[0] << " and " << xlim[1] << endl;
    if (binned == 2)
      cout << "Performing a gaussian binned likelihood fit for data and MC between " << xlim[0] << " and " << xlim[1] << endl;

    cout << "\n===================================================\n" <<endl;

    TStyle* my_style = createMyStyle();
    my_style->cd();
    gROOT->SetBatch(true);

    double *mtop_el = treat("ElectronHadASingleElectronBCD.root", 19.7, decay, mtop, xlim, binned, date, version); 
    getchar();
    double *mtop_mu = treat("MuHadASingleMuBCD.root", 19.7, decay, mtop, xlim, binned, date, version); 
    getchar();
    double *mtop_all = treat("Run2012ABCD.root", 19.7, decay, mtop, xlim, binned, date, version); 

    cout << "\n===================================================\n" <<endl;

    double *mtop_combi = combi(mtop_el[0], mtop_el[1], mtop_mu[0], mtop_mu[1]); 
    TString result1 = TString::Format("Combining decay channels AFTER fits: \n \t \t \t M_{t} = (%3.1f #pm %3.1f) GeV", mtop_combi[0], mtop_combi[1]);
    cout << result1 << endl;
    TString result2 = TString::Format("Combining decay channels BEFORE fits: \n \t \t \t M_{t} = (%3.1f #pm %3.1f) GeV", mtop_all[0], mtop_all[1]);
    cout << result2 << endl;
   
    return 0;
  }
  else 
    return 1;
}


