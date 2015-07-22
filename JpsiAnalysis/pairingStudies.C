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
int treatHisto(TTree* tree, TString outdir, TLatex* channel_tex, 
    double lumi, double nGP, double nWP, TString histName, 
    TString xTitle, int nbins, double xmin, double xmax)
//---------------------------------------------------------------
{  

  TH1F *histo_ap = new TH1F(histName+"AllPairing", histName+"AllPairing", nbins, xmin, xmax);
  TH1F *histo_gp = new TH1F(histName+"GoodPairing", histName+"GoodPairing", nbins, xmin, xmax);
  TH1F *histo_wp = new TH1F(histName+"WrongPairing", histName+"WrongPairing", nbins, xmin, xmax);

  /*
  tree->Draw(histName+">>histo_ap", "","goff");
  tree->Draw(histName+">>histo_gp", "Pairing>0","goff");
  tree->Draw(histName+">>histo_gp", "Pairing<0","goff");
  */

  float m_var, m_weight, m_pair;
  tree->SetBranchAddress(histName, &m_var);
  tree->SetBranchAddress("Weight", &m_weight);
  tree->SetBranchAddress("Pairing", &m_pair);

  unsigned int nEvt = (unsigned int)tree->GetEntries();
  for (unsigned int iEvt = 0; iEvt < nEvt; iEvt++) {
    tree->GetEntry(iEvt);
    histo_ap->Fill(m_var, m_weight);
    if (m_pair > 0)
      histo_gp->Fill(m_var, m_weight);
    else
      histo_wp->Fill(m_var, m_weight);
  }

  double histo_max = 1.3*histo_ap->GetMaximum();
  double histo_min = 0.8*min(histo_wp->GetMinimum(),histo_gp->GetMinimum());
  h_myStyle(histo_ap,38,38,0,histo_min,histo_max,510,510,20,38,1.2,0.,xTitle);
  h_myStyle(histo_gp,30,30,0,histo_min,histo_max,510,510,20,30,1.2,0.,xTitle);
  h_myStyle(histo_wp,50,50,0,histo_min,histo_max,510,510,20,50,1.2,0.,xTitle);

  TCanvas *cn = new TCanvas("cn", "cn", 800, 800);
  cn->cd();
  TLegend *leg = new TLegend(0.58,0.75,0.93,0.92,NULL,"brNDC");
  leg->SetTextSize(0.025);
  leg->AddEntry(histo_gp, TString::Format("Good pairing (%4.2f %%)", 100.*nGP), "lp");
  leg->AddEntry(histo_wp, TString::Format("Wrong pairing (%4.2f %%)", 100.*nWP), "lp");
  leg->AddEntry(histo_ap, "Both pairings", "lp");
  leg_myStyle(leg);
  histo_ap->Draw("e");
  histo_gp->Draw("esame");
  histo_wp->Draw("esame");
  leg->Draw("same");
  histo_ap->Draw("esame");
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
int pairingStudies(TString date = "", TString version = "", TString decay = "")
//---------------------------------------------------------------
{  
  TH1::SetDefaultSumw2(kTRUE);

  if (date.Length() > 0 && version.Length() > 0 && decay.Length() > 0)  {

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

    // TString fileData = date+"/v"+version+"/MyAnaAll/TTJets_MSDecays_JpsiFilter_172_5.root";
    // TString outdir   = date+"/v"+version+"/PairingStudies/";
    TString fileData = date+"/"+version+"/MyAnaAll/TTJets_MSDecays_JpsiFilter_172_5.root";
    TString outdir   = date+"/"+version+"/PairingStudies/";

    gROOT->ProcessLine(".! mkdir "+outdir);

    TFile *res = TFile::Open(fileData);
    TTree *tree = (TTree*)res->Get("PairingStudies");

    TH1F *histo_ap = new TH1F("NJets20AllPairing", "NJets20AllPairing", 15, 0., 15.);
    TH1F *histo_gp = new TH1F("NJets20GoodPairing", "NJets20GoodPairing", 15, 0., 15.);
    TH1F *histo_wp = new TH1F("NJets20WrongPairing", "NJets20WrongPairing", 15, 0., 15.);
    /*
    tree->Draw("NJets20>>histo_ap", "","goff");
    tree->Draw("NJets20>>histo_gp", "Pairing>0","goff");
    tree->Draw("NJets20>>histo_gp", "Pairing<0","goff");
    */
    float m_var, m_weight, m_pair;
    tree->SetBranchAddress("NJets20", &m_var);
    tree->SetBranchAddress("Weight", &m_weight);
    tree->SetBranchAddress("Pairing", &m_pair);
    unsigned int nEvt = (unsigned int)tree->GetEntries();
    for (unsigned int iEvt = 0; iEvt < nEvt; iEvt++) {
      tree->GetEntry(iEvt);
      histo_ap->Fill(m_var, m_weight);
      if (m_pair > 0)
        histo_gp->Fill(m_var, m_weight);
      else
        histo_wp->Fill(m_var, m_weight);
    }
    double nGP = histo_gp->Integral()/histo_ap->Integral();
    double nWP = histo_wp->Integral()/histo_ap->Integral();
    delete histo_wp; 
    delete histo_gp; 
    delete histo_ap;

    treatHisto(tree, outdir, channel_tex, lumi, nGP, nWP, "MJpsi", "J/#psi mass (GeV/c^{2})", 20, 3., 3.2);
    treatHisto(tree, outdir, channel_tex, lumi, nGP, nWP, "PtJpsi", "p_{T} (J/#psi) (GeV/c)", 28, 0., 140.);
    treatHisto(tree, outdir, channel_tex, lumi, nGP, nWP, "EtaJpsi", "#eta (J/#psi)", 30, -3., 3.);
    treatHisto(tree, outdir, channel_tex, lumi, nGP, nWP, "PhiJpsi", "#phi (J/#psi)", 32, -3.2, 3.2);
    treatHisto(tree, outdir, channel_tex, lumi, nGP, nWP, "Chi2Jpsi", "#chi^{2}(J/#psi vertex)", 16, 0., 8.);
    treatHisto(tree, outdir, channel_tex, lumi, nGP, nWP, "LJpsi", "c#tau(J/#psi) (cm)", 25, 0., 0.5);
    treatHisto(tree, outdir, channel_tex, lumi, nGP, nWP, "SigmaLJpsi", "#Delta(c#tau)(J/#psi) (cm)", 30, 0., 0.0015);
    treatHisto(tree, outdir, channel_tex, lumi, nGP, nWP, "LOverSigmaJpsi", "(c#tau)/#Delta(c#tau)(J/#psi)", 42, 0., 7000.);
    treatHisto(tree, outdir, channel_tex, lumi, nGP, nWP, "PtFracJpsiJet", "p_{T}(J/#psi)/p_{T}(jet)", 20, 0., 1.);
    treatHisto(tree, outdir, channel_tex, lumi, nGP, nWP, "PtJetJpsi", "p_{T}(jets with a J/#psi) (GeV/c)", 25, 0., 500.);
    treatHisto(tree, outdir, channel_tex, lumi, nGP, nWP, "CsvJetJpsi", "CSV discriminant (jets with a J/#psi)", 50, 0., 1.);
    treatHisto(tree, outdir, channel_tex, lumi, nGP, nWP, "ChMuEFracJetJpsi", "#mu^{#pm} energy fraction (jets with a J/#psi)", 50, 0., 1.);
    treatHisto(tree, outdir, channel_tex, lumi, nGP, nWP, "ChEMEFracJetJpsi", "e^{#pm} energy fraction (jets with a J/#psi)", 50, 0., 1.);
    treatHisto(tree, outdir, channel_tex, lumi, nGP, nWP, "ChHadEFracJetJpsi", "Charged hadron energy fraction (jets with a J/#psi)", 50, 0., 1.);
    treatHisto(tree, outdir, channel_tex, lumi, nGP, nWP, "ChEFracJetJpsi", "Charged energy fraction (jets with a J/#psi)", 50, 0., 1.);
    treatHisto(tree, outdir, channel_tex, lumi, nGP, nWP, "NEMEFracJetJpsi", "#gamma energy fraction (jets with a J/#psi)", 50, 0., 1.);
    treatHisto(tree, outdir, channel_tex, lumi, nGP, nWP, "NHadEFracJetJpsi", "Neutral hadron energy fraction (jets with a J/#psi)", 50, 0., 1.);
    treatHisto(tree, outdir, channel_tex, lumi, nGP, nWP, "NEFracJetJpsi", "Neutral energy fraction (jets with a J/#psi)", 50, 0., 1.);
    treatHisto(tree, outdir, channel_tex, lumi, nGP, nWP, "PtIsoLept", "p_{T}(isolated lepton) (GeV/c)", 30, 0., 300.);
    treatHisto(tree, outdir, channel_tex, lumi, nGP, nWP, "EtaIsoLept", "#eta(isolated lepton)", 30, -3., 3.);
    treatHisto(tree, outdir, channel_tex, lumi, nGP, nWP, "PhiIsoLept", "#phi(isolated lepton)", 32, -3.2, 3.2);
    treatHisto(tree, outdir, channel_tex, lumi, nGP, nWP, "DPhiJpsiIsoLept", "#Delta#phi (J/#psi-isolated lepton)", 16, 0., 4.);
    treatHisto(tree, outdir, channel_tex, lumi, nGP, nWP, "DRJpsiIsoLept", "#DeltaR (J/#psi-isolated lepton)", 20, 0., 5.);
    treatHisto(tree, outdir, channel_tex, lumi, nGP, nWP, "MTriLept", "M(J/#psi+l) (GeV/c^{2})", 25, 0., 250.);
    treatHisto(tree, outdir, channel_tex, lumi, nGP, nWP, "PtTriLept", "p_{T}(J/#psi+l) (GeV/c)", 25, 0., 250.);

    delete tree;
    res->Close(); 
    delete res;

    return 0;
  }
  else 
    return 1;
}



