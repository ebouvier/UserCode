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
 * Comparing several distributions whether the
 * isolated is well matched to the J/psi or not
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
int treatHisto(TString date, TString ref, TString down, TString up, TString outdir, 
    TLatex* channel_tex, double lumi, TString histName, TString xTitle)
//---------------------------------------------------------------
{  
  TString sRef = date + "/" + ref + "/MyAnaAll/";
  if (ref.Contains("P11mpiHi", TString::kIgnoreCase))
    sRef += "TTJets_SemiLeptMGDecays_TuneP11mpiHi.root";
  else if (ref.Contains("P11noCR", TString::kIgnoreCase))
    sRef += "TTJets_SemiLeptMGDecays_TuneP11noCR.root";
  else if (ref.Contains("P11TeV", TString::kIgnoreCase))
    sRef += "TTJets_SemiLeptMGDecays_TuneP11TeV.root";
  else if (ref.Contains("P11", TString::kIgnoreCase))
    sRef += "TTJets_SemiLeptMGDecays_TuneP11.root";
  else if (ref.Contains("MCatNLO", TString::kIgnoreCase))
    sRef += "TTJets_MCatNLO.root";
  else if (ref.Contains("Powheg", TString::kIgnoreCase))
    sRef += "TTJets_Powheg.root";
  else
    sRef += "TTJets_MSDecays_JpsiFilter_172_5.root";

  TString sDown = date + "/" + down + "/MyAnaAll/"; 
  if (down.Contains("P11mpiHi", TString::kIgnoreCase))
    sDown += "TTJets_SemiLeptMGDecays_TuneP11mpiHi.root";
  else if (down.Contains("P11noCR", TString::kIgnoreCase))
    sDown += "TTJets_SemiLeptMGDecays_TuneP11noCR.root";
  else if (down.Contains("P11TeV", TString::kIgnoreCase))
    sDown += "TTJets_SemiLeptMGDecays_TuneP11TeV.root";
  else if (down.Contains("P11", TString::kIgnoreCase))
    sDown += "TTJets_SemiLeptMGDecays_TuneP11.root";
  else if (down.Contains("MCatNLO", TString::kIgnoreCase))
    sDown += "TTJets_MCatNLO.root";
  else if (down.Contains("Powheg", TString::kIgnoreCase))
    sDown += "TTJets_Powheg.root";
  else
    sDown += "TTJets_MSDecays_JpsiFilter_172_5.root"; 

  TString sUp = date + "/" + up + "/MyAnaAll/"; 
  if (up.Contains("P11mpiHi", TString::kIgnoreCase))
    sUp += "TTJets_SemiLeptMGDecays_TuneP11mpiHi.root";
  else if (up.Contains("P11noCR", TString::kIgnoreCase))
    sUp += "TTJets_SemiLeptMGDecays_TuneP11noCR.root";
  else if (up.Contains("P11TeV", TString::kIgnoreCase))
    sUp += "TTJets_SemiLeptMGDecays_TuneP11TeV.root";
  else if (up.Contains("P11", TString::kIgnoreCase))
    sUp += "TTJets_SemiLeptMGDecays_TuneP11.root";
  else if (up.Contains("MCatNLO", TString::kIgnoreCase))
    sUp += "TTJets_MCatNLO.root";
  else if (up.Contains("Powheg", TString::kIgnoreCase))
    sUp += "TTJets_Powheg.root";
  else
    sUp += "TTJets_MSDecays_JpsiFilter_172_5.root"; 

  TFile* fiDown = TFile::Open(sDown);
  TFile* fiUp   = TFile::Open(sUp);
  TH1F* hDown = (TH1F*)fiDown->Get(histName);
  TH1F* hUp   = (TH1F*)fiUp->Get(histName);
  h_myStyle(hDown,38,38,0,-1111.,-1111.,510,510,20,38,1.2,0.,xTitle);
  h_myStyle(hUp,50,50,0,-1111.,-1111.,510,510,20,50,1.2,0.,xTitle);

  TCanvas *cn = new TCanvas("cn", "cn", 800, 800);
  cn->cd();
  hDown->DrawNormalized();
  TLegend *leg = new TLegend(0.58,0.8,0.93,0.92,NULL,"brNDC");
  leg->SetTextSize(0.025);
  leg->AddEntry(hDown, down, "lp");
  if (ref.Length() > 0) {
    TFile* fiRef = TFile::Open(sRef);
    TH1F* hRef = (TH1F*)fiRef->Get(histName);
    h_myStyle(hRef,30,30,0,-1111.,-1111.,510,510,20,30,1.2,0.,xTitle);
    leg->AddEntry(hRef, ref, "lp");
    hRef->DrawNormalized("ehistsame");
  }
  leg->AddEntry(hUp, up, "lp");
  leg_myStyle(leg);
  hDown->DrawNormalized("esame");
  hUp->DrawNormalized("esame");
  leg->Draw("same");
  channel_tex->Draw("same");
  cms_myStyle(lumi, true);
  TString outFile = outdir + histName;
  cn->SaveAs(outFile+".pdf");
  cn->SaveAs(outFile+".C");
  cn->SaveAs(outFile+".jpg");
  cn->SaveAs(outFile+".eps");

  return 0;
}

//---------------------------------------------------------------
int sysVariations(TString date = "", TString ref = "", TString down = "", TString up = "", TString out = "", TString decay = "")
//---------------------------------------------------------------
{  
  TH1::SetDefaultSumw2(kTRUE);

  if (date.Length() > 0 && down.Length() > 0 && up.Length() > 0 && out.Length() > 0 && decay.Length() > 0)  {

    double lumi = 19.7;
    TString channel = " + Jets channel";
    if (decay.Contains("semi", TString::kIgnoreCase))
      channel = "e/#mu" + channel;
    if (decay.Contains("di", TString::kIgnoreCase))
      channel = "ee/#mu#mu/e#mu" + channel;
    if (decay.Contains("all", TString::kIgnoreCase))
      channel = "e/#mu/ee/#mu#mu/e#mu" + channel;
    TLatex* channel_tex = new TLatex(0.22, 0.9, channel);
    channel_tex->SetNDC(true);
    channel_tex->SetTextFont(43);
    channel_tex->SetTextSize(TITLE_FONTSIZE - 6);

    TStyle* my_style = createMyStyle();
    my_style->cd();
    gROOT->SetBatch(true);

    TString outdir = date+"/SysVariations/";
    gROOT->ProcessLine(".! mkdir "+outdir);
    outdir += out+"/";
    gROOT->ProcessLine(".! mkdir "+outdir);

    treatHisto(date, ref, down, up, outdir, channel_tex, lumi, "PtIsoLept", "p_{T}(leading lepton) (GeV)");
    treatHisto(date, ref, down, up, outdir, channel_tex, lumi, "NJets20", "Number of jets with p_{T}>20 GeV");
    treatHisto(date, ref, down, up, outdir, channel_tex, lumi, "PtLeadJet1", "p_{T}(1st jet) (GeV)");
    treatHisto(date, ref, down, up, outdir, channel_tex, lumi, "MetMet", "MET (GeV)");
    treatHisto(date, ref, down, up, outdir, channel_tex, lumi, "MJpsi", "J/#psi mass (GeV)");
    treatHisto(date, ref, down, up, outdir, channel_tex, lumi, "PtJpsi", "p_{T} (J/#psi) (GeV)");
    treatHisto(date, ref, down, up, outdir, channel_tex, lumi, "MTriLept-allPair", "M(J/#psi+l) (GeV)");
    treatHisto(date, ref, down, up, outdir, channel_tex, lumi, "PtTriLept", "p_{T}(J/#psi+l) (GeV)");
    treatHisto(date, ref, down, up, outdir, channel_tex, lumi, "PtJetJpsi", "p_{T}(jets with a J/#psi) (GeV)");

    return 0;
  }
  else 
    return 1;
}



