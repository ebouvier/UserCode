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
#include "TFitResultPtr.h"
#include "TFile.h"
#include "TTree.h"

#pragma once

#define TITLE_FONTSIZE 30
#define LABEL_FONTSIZE 24

#define LEFT_MARGIN 0.17
#define RIGHT_MARGIN 0.03
#define TOP_MARGIN 0.05
#define BOTTOM_MARGIN 0.13

/* 
 * Plotting the measured top-quark mass on MC
 * as function of the mean of xb/xjpsi/xbxjpsi
 * /!\ l.288 to 308 are hardcoded /!\
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
  myStyle->SetTitleYOffset(2.); 
  myStyle->SetTitleXOffset(1.25);

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
    float y_min=-1111.,
    float y_max=-1111.,
    int ndivx=510,
    int ndivy=510,
    int marker_style=20,
    int marker_color=1,
    float marker_size=1.2,
    int optstat=0) {

  h->SetLineColor(line_color);
  h->SetFillColor(fill_color);
  h->SetFillStyle(fill_style);
  h->SetMaximum(y_max);
  h->SetMinimum(y_min);
  h->GetXaxis()->SetNdivisions(ndivx);
  h->GetYaxis()->SetNdivisions(ndivy);
  h->GetYaxis()->SetTitleOffset(2.);

  h->SetMarkerStyle(marker_style);
  h->SetMarkerColor(marker_color);
  h->SetMarkerSize(marker_size);
  h->SetStats(optstat);

  float binSize = h->GetXaxis()->GetBinWidth(1);
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
    float y_min=-1111.,
    float y_max=-1111.,
    int ndivx=510,
    int ndivy=510,
    int marker_style=20,
    int marker_color=1,
    float marker_size=1.2,
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

void cms_myStyle(float lumi = 19.7,bool isData = false){
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

  TString lumi_s = TString::Format("(8 TeV)");
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
int plotMtVsBfragGood(TString myanaDate)
//---------------------------------------------------------------
{
  TString date = "16Feb25";
  TString var = "xb";
  TString channel = "B decays with J/#psi";

  double ref = -173.503;

  std::vector<TString> tune;            std::vector<double> mt;     std::vector<double> errmt;  std::vector<double> ratio;  std::vector<double> errratio;  std::vector<int>color;
  /*
  tune.push_back("Z2star");             mt.push_back(ref+172.789);  errmt.push_back(0.158);     ratio.push_back(0.720087);  errratio.push_back(0.00060);  color.push_back(1);
  tune.push_back("P12FT");              mt.push_back(ref+172.430);  errmt.push_back(0.156);     ratio.push_back(0.729798);  errratio.push_back(0.00146);  color.push_back(801);
  tune.push_back("P12");                mt.push_back(ref+172.745);  errmt.push_back(0.157);     ratio.push_back(0.739445);  errratio.push_back(0.00154);  color.push_back(632);
  tune.push_back("P12FL");              mt.push_back(ref+173.018);  errmt.push_back(0.159);     ratio.push_back(0.741695);  errratio.push_back(0.00144);  color.push_back(802);
  tune.push_back("Z2star_rbLEP_soft");  mt.push_back(ref+173.002);  errmt.push_back(0.160);     ratio.push_back(0.745214);  errratio.push_back(0.00117);  color.push_back(882);
  tune.push_back("Z2star_rbLEP");       mt.push_back(ref+172.987);  errmt.push_back(0.160);     ratio.push_back(0.745196);  errratio.push_back(0.00120);  color.push_back(881);
  tune.push_back("Z2star_rbLEP_hard");  mt.push_back(ref+173.070);  errmt.push_back(0.159);     ratio.push_back(0.745362);  errratio.push_back(0.00120);  color.push_back(876);
  */
  tune.push_back("Z2star");             mt.push_back(ref+172.789);  errmt.push_back(0.158);     ratio.push_back(0.730763);  errratio.push_back(0.00090);  color.push_back(802); //424);
  tune.push_back("Z2star_rbLEP");       mt.push_back(ref+173.503);  errmt.push_back(0.163);     ratio.push_back(0.756775);  errratio.push_back(0.00072);  color.push_back(632);
  tune.push_back("Z2star_rbLEP_soft");  mt.push_back(ref+173.283);  errmt.push_back(0.161);     ratio.push_back(0.744987);  errratio.push_back(0.00085);  color.push_back(632); //801);
  tune.push_back("Z2star_rbLEP_hard");  mt.push_back(ref+173.817);  errmt.push_back(0.166);     ratio.push_back(0.766803);  errratio.push_back(0.00084);  color.push_back(632); //802);
  tune.push_back("P12FT");              mt.push_back(ref+172.928);  errmt.push_back(0.160);     ratio.push_back(0.739443);  errratio.push_back(0.00094);  color.push_back(801); //607);
  tune.push_back("P12FL");              mt.push_back(ref+173.521);  errmt.push_back(0.162);     ratio.push_back(0.751203);  errratio.push_back(0.00086);  color.push_back(801); //882);
  tune.push_back("P12");                mt.push_back(ref+173.228);  errmt.push_back(0.161);     ratio.push_back(0.749337);  errratio.push_back(0.00075);  color.push_back(801); //617);

  TStyle* my_style = createMyStyle();
  my_style->cd();

  TCanvas *canvas = new TCanvas("canvas","canvas",800,800);
  TLegend *legend = new TLegend(0.2,0.72,0.68,0.88,NULL,"brNDC");
  legend->SetTextSize(0.03);
  legend->SetNColumns(2);
  leg_myStyle(legend);
  TString xaxis = "#LTp_{T}^{gen}(B)/p_{T}^{gen}(jet)#GT";
  if (var.EqualTo("xjpsi", TString::kIgnoreCase)) 
    xaxis = "#LTp_{T}^{gen}(J/#psi)/p_{T}^{gen}(jet)#GT";
  if (var.EqualTo("xjpsixb", TString::kIgnoreCase)) 
    xaxis = "#LTp_{T}^{gen}(J/#psi)/p_{T}^{gen}(B)#GT";
  TString yaxis = "#DeltaM_{t} = M_{t}(Z2* rbLEP) - M_{t}(other tune) (GeV)";
  double *x_ratio = &ratio[0];
  double *y_mt = &mt[0];
  double *ex_ratio = &errratio[0];
  double *ey_mt = &errmt[0];
  TGraphErrors *first = new TGraphErrors((const int)tune.size(), x_ratio, y_mt, ex_ratio, ey_mt);
  grapherrors_myStyle(first, "first", 1, 0, 1, 0, 1001, -1111., -1111., 510, 510, 1, 0, 1., xaxis, yaxis);
  first->Draw("AP");
//  first->GetYaxis()->SetRangeUser(-0.4,1.4);
  first->GetYaxis()->SetRangeUser(-1.,0.8);

  TFitResultPtr fitptr = first->Fit("pol1", "FSQ", "");
  TF1 *fit = first->GetFunction("pol1");
  double yinte = fitptr->Parameter(0);
  double errYinte = fitptr->ParError(0);
  cout << "p0 = " << yinte << " +/- " << errYinte << endl;
  double slope = fitptr->Parameter(1);
  double errSlope = fitptr->ParError(1);
  cout << "p1 = " << slope << " +/- " << errSlope << endl;
  double chi2 = fitptr->Chi2();
  double ndf = fitptr->Ndf();
  cout << "chi2/ndf = " << chi2 << "/" << ndf << " = " << chi2/ndf << endl;
  double err_up[tune.size()];
  double err_down[tune.size()];
  double err_val[tune.size()];
  fitptr->GetConfidenceIntervals((const int)tune.size(), 1, 1, x_ratio, err_val, 0.68);
  for(unsigned int itune = 0; itune < tune.size(); itune++) {
    double error = err_val[itune];
    err_up[itune] = fit->Eval(x_ratio[itune]) + error;
    err_down[itune] = fit->Eval(x_ratio[itune]) - error;
  }
  TGraph *gr_up = new TGraph((const int)tune.size(),x_ratio,err_up);
  gr_up->Fit("pol2","FQ","");
  TF1 *fit_up = gr_up->GetFunction("pol2");
  TGraph *gr_down = new TGraph((const int)tune.size(),x_ratio,err_down);
  gr_down->Fit("pol2","FQ","");
  TF1 *fit_down = gr_down->GetFunction("pol2");  
  fit->SetLineColor(923);
  fit_up->SetLineColor(921); fit_up->SetLineStyle(2); fit_up->SetLineWidth(2);
  fit_up->Draw("same");
  fit_down->SetLineColor(921); fit_down->SetLineStyle(2); fit_down->SetLineWidth(2);
  fit_down->Draw("same");
  TLatex* fit_tex = new TLatex(0.32, 0.22, TString::Format("#DeltaM_{t} = (%.2f GeV/1%) #times #Delta"+xaxis, slope/100));
  fit_tex->SetNDC(true);
  fit_tex->SetTextFont(63);
  fit_tex->SetTextSize(TITLE_FONTSIZE - 4);
  fit_tex->Draw("same");

  for (unsigned int itune = 0; itune < tune.size(); itune++) {
    TString title = tune[itune];
    title.ReplaceAll("star","*");
    title.ReplaceAll("_"," ");

    double x[1] = {ratio[itune]};
    double y[1] = {mt[itune]};
    double ex[1] = {errratio[itune]};
    double ey[1] = {errmt[itune]};
    TGraphErrors *graph = new TGraphErrors(1, x, y, ex, ey);
    grapherrors_myStyle(graph, tune[itune], 2, color[itune], 1, color[itune], 1001, -1111., -1111., 510, 510, 20+itune, color[itune], 1.5, xaxis, yaxis);
    graph->Draw("P");
    legend->AddEntry(graph, title, "p");
  }
  legend->Draw("same");
  TLatex* channel_tex = new TLatex(0.22, 0.9, channel);
  channel_tex->SetNDC(true);
  channel_tex->SetTextFont(43);
  channel_tex->SetTextSize(TITLE_FONTSIZE - 6);
  channel_tex->Draw("same");
  cms_myStyle();
  
  TString outdir = myanaDate+"/BfragSummary";
  gROOT->ProcessLine(".! mkdir "+outdir);
  canvas->SaveAs(myanaDate+"/MtVsBfrag_"+date+"_"+var+".pdf");
  canvas->SaveAs(myanaDate+"/MtVsBfrag_"+date+"_"+var+".C");
  canvas->SaveAs(myanaDate+"/MtVsBfrag_"+date+"_"+var+".jpg");
  canvas->SaveAs(myanaDate+"/MtVsBfrag_"+date+"_"+var+".eps");

  return 0;
}
