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
#include "RooCBShape.h"
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
 * Performing a gaussian binned likelihood fit for data
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
    //int text_align = 22,
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
int fitMJpsi(TString date = "", TString version = "", TString fileData = "", TString decay = "")
//---------------------------------------------------------------
{  
  if (date.Length() > 0 && version.Length() > 0 && fileData.Length() > 0 && decay.Length() > 0)  {

    vector<double> xlim; xlim.push_back(3.02); xlim.push_back(3.2);
    double lumi = 19.7;

    TStyle* my_style = createMyStyle();
    my_style->cd();
    gROOT->SetBatch(true);

    // TString indir = date+"/v"+version+"/";
    TString indir = date+"/"+version+"/";
    TString outdir = indir+"MJpsi/";
    TString outFile = outdir;
    TString channel = " + Jets channel";
    if (fileData.Contains("el", TString::kIgnoreCase)) {
      indir += "MyAnaEl/";
      fileData = indir+"ElectronHadASingleElectronBCD.root";
      outFile += "GaussianBinnedFit_ElChannel";
      if (decay.Contains("semi", TString::kIgnoreCase))
          channel = "e"+channel;
      if (decay.Contains("di", TString::kIgnoreCase))
          channel = "ee/e#mu"+channel;
      if (decay.Contains("all", TString::kIgnoreCase))
          channel = "e/ee/e#mu"+channel;
    }
    if (fileData.Contains("mu", TString::kIgnoreCase)) {
      indir += "MyAnaMu/";
      fileData = indir+"MuHadASingleMuBCD.root";
      outFile += "GaussianBinnedFit_MuChannel";
      if (decay.Contains("semi", TString::kIgnoreCase))
        channel = "#mu"+channel;
      if (decay.Contains("di", TString::kIgnoreCase))
        channel = "#mu#mu/#mue"+channel;
      if (decay.Contains("all", TString::kIgnoreCase))
        channel = "#mu/#mu#mu/#mue"+channel;
    }
    if (fileData.Contains("all", TString::kIgnoreCase)) {
      indir += "MyAnaAll/";
      fileData = indir+"Run2012ABCD.root";
      outFile += "GaussianBinnedFit_AllChannel";
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

    using namespace RooFit;

    TFile *res = TFile::Open(fileData);

    RooRealVar mjpsi("mass", "M_{J/#psi}", 3., 3.2, "GeV/c^{2}");
    RooRealVar mean_gaus("mean_gaus", "mass_gaus", 3.09, 3.07, 3.11);
    RooRealVar width_gaus("width_gaus", "width_gaus", 0.04, 0.02, 0.06);
    RooRealVar mean_cball("mean_cball", "mass_cball", 3.09, 3.07, 3.11);
    RooRealVar width_cball("width_cball", "width_cball", 0.04, 0.02, 0.06);
    RooRealVar alpha_cball("alpha_cball", "alpha_cball", 1.8);
    RooRealVar n_cball("n_cball", "n_cball", 2.5);

    TH1F *histo = (TH1F*)res->Get("MJpsi");
    h_myStyle(histo,38,38,3002,histo->GetMinimum(),1.2*histo->GetMaximum(),510,510,20,38,1.,0.);
    RooDataHist *datahist = new RooDataHist("datahist", "datahist", RooArgList(mjpsi), histo, 1.);
    RooGaussian pdf("gaus", "gaus", mjpsi, mean_gaus, width_gaus);
    pdf.fitTo(*datahist, Range(xlim[0], xlim[1]));
    RooCBShape pdf2("CBall", "CBall", mjpsi, mean_cball, width_cball, alpha_cball, n_cball);
    pdf2.fitTo(*datahist, Range(3., xlim[1]));

    TCanvas *cn = new TCanvas("cn", "cn", 800, 800);
    cn->cd();
    RooPlot *massframe = mjpsi.frame();
    datahist->plotOn(massframe); //, MarkerColor(38), LineColor(38));
    pdf.plotOn(massframe, LineColor(38), Range(xlim[0], xlim[1]), Name("bleu"));
    pdf2.plotOn(massframe, LineColor(50), Range(3., xlim[1]), Name("rouge"));
    massframe->Draw();
    TLegend *leg = new TLegend(0.58,0.82,0.93,0.92,NULL,"brNDC");
    leg->SetTextSize(0.025);
    leg->SetHeader("Gaussian fit parameters:");
    leg->AddEntry(massframe->findObject("bleu"), TString::Format("#mu = (%4.3f #pm %4.3f) GeV/c^{2}",mean_gaus.getVal(),mean_gaus.getError()), "l");
    leg->AddEntry((TObject*)0, TString::Format("#sigma = (%4.3f #pm %4.3f) GeV/c^{2}",width_gaus.getVal(),width_gaus.getError()), "");
    TLegend *leg2 = new TLegend(0.58,0.72,0.93,0.82,NULL,"brNDC");
    leg2->SetTextSize(0.025);
    leg2->SetHeader("Crystal Ball fit parameters:");
    leg2->AddEntry((TObject*)0, TString::Format("#mu = (%4.3f #pm %4.3f) GeV/c^{2}",mean_cball.getVal(),mean_cball.getError()), "");
    leg2->AddEntry(massframe->findObject("rouge"), TString::Format("#sigma = (%4.3f #pm %4.3f) GeV/c^{2}",width_cball.getVal(),width_cball.getError()), "l");
    leg2->AddEntry((TObject*)0, TString::Format("#alpha = %2.1f, n = %2.1f",alpha_cball.getVal(),n_cball.getVal()), "");
    leg_myStyle(leg);
    leg_myStyle(leg2);
    leg->Draw("same");
    leg2->Draw("same");
    channel_tex->Draw("same");
    cms_myStyle(lumi, true);
    cn->SaveAs(outFile+".pdf");
    cn->SaveAs(outFile+".C");
    cn->SaveAs(outFile+".jpg");
    cn->SaveAs(outFile+".eps");

    res->Close();

    return 0;
  }
  else 
    return 1;
}



