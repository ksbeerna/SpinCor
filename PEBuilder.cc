#include "PEBuilder.h"

//Pseudo-Experiment Builder
eire::PEBuilder::PEBuilder(std::vector< std::vector<float> > Cor, std::vector< std::vector<float> > Uncor, float mixing, std::vector< std::vector<float> > WJets, float Back_frac, bool use_back)
{
  L_Cor = Cor;
  L_Uncor = Uncor;
  mix_frac = mixing;
  L_WJets = WJets;
  Wfrac = Back_frac;
  Use_back = use_back;
  verbose = false;
}

eire::PEBuilder::~PEBuilder()
{
}

std::vector<TH1F> eire::PEBuilder::DrawTemplates()
{
  TH1F* Template_SigCor = new TH1F("Correlated","-2ln#lambda = 2lnL_{H=C} - 2lnL_{H=U};;normalised entries", nBins, low_range, high_range);
  TH1F* Template_SigUnCor = new TH1F("UnCorrelated","-2ln#lambda = 2lnL_{H=C} - 2lnL_{H=U};;normalised entries", nBins, low_range, high_range);
  TH1F* LikelihoodCutCor = new TH1F("LikelihoodCutCor","-lnL_{H=C};-lnL_{H=C};entries", 50, 0, 100);
  TH1F* LikelihoodCutUnCor = new TH1F("LikelihoodCutUnCor","-lnL_{H=C};-lnL_{H=C};entries", 50, 0, 100);
  TH1F* LikelihoodCutUnCorCor = new TH1F("LikelihoodCutUnCorCor","-lnL_{H=U};-lnL_{H=U};entries", 50, 0, 100);
  TH1F* LikelihoodCutUnCorUnCor = new TH1F("LikelihoodCutUnCorUnCor","-lnL_{H=U};-lnL_{H=U};entries", 50, 0, 100);

  std::vector<float> TTcorcor = (L_Cor)[0];
  std::vector<float> TTcoruncor = (L_Cor)[1];
  std::vector<float> TTuncorcor = (L_Uncor)[0];
  std::vector<float> TTuncoruncor = (L_Uncor)[1];

  for(unsigned int i = 0; i < TTcorcor.size(); i++){
    Template_SigCor->Fill(2*(TTcorcor)[i] - 2*(TTcoruncor)[i]);
    LikelihoodCutCor->Fill(-1*(TTcorcor)[i]);
    LikelihoodCutUnCorCor->Fill(-1*(TTcoruncor)[i]);
  }
  for(unsigned int i = 0; i < TTuncorcor.size(); i++){
    Template_SigUnCor->Fill(2*(TTuncorcor)[i] - 2*(TTuncoruncor)[i]);
    LikelihoodCutUnCor->Fill(-1*(TTuncorcor)[i]);
    LikelihoodCutUnCorUnCor->Fill(-1*(TTuncoruncor)[i]);
  }
  
  Template_SigCor->Sumw2();
  Template_SigUnCor->Sumw2();
  Template_SigCor->Scale(1./Template_SigCor->Integral("width"));
  Template_SigUnCor->Scale(1./Template_SigUnCor->Integral("width"));
  Template_SigCor->SetLineColor(kRed);
  Template_SigUnCor->SetLineColor(kBlack);

  LikelihoodCutCor->SetLineColor(kRed);
  LikelihoodCutUnCor->SetLineColor(kBlack);
  LikelihoodCutUnCorCor->SetLineColor(kRed);
  LikelihoodCutUnCorUnCor->SetLineColor(kBlack);

  TH1F* SF = new TH1F("SF","", nBins, low_range, high_range);
  SF = (TH1F*) Template_SigCor->Clone();
  SF->Divide(Template_SigUnCor);
  SF->SetTitle("");
  TCanvas *c1 = new TCanvas("c1", "c1",0,0,600,500);
  c1->Range(0,0,1,1);
  TPad *c1_1 = new TPad("c1_1", "newpad",0.01,0.01,0.99,0.32);
  c1_1->Draw();
  c1_1->cd();
  c1_1->SetTopMargin(0.01);
  c1_1->SetBottomMargin(0.3);
  c1_1->SetRightMargin(0.1);
  c1_1->SetFillStyle(0);
  SF->SetMinimum(0.800);
  SF->SetMaximum(1.200);
  SF->GetYaxis()->SetNdivisions(5);
  SF->GetXaxis()->SetTitle("-2ln#lambda");
  SF->GetYaxis()->SetTitle("Scale Factor");
  SF->GetXaxis()->SetTitleSize(0.14);
  SF->GetXaxis()->SetLabelSize(0.14);
  SF->GetYaxis()->SetLabelSize(0.11);
  SF->GetYaxis()->SetTitleSize(0.14);
  SF->GetYaxis()->SetTitleOffset(0.28);
  SF->Draw();
  TLine* l = new TLine(low_range,1,high_range,1);
  l->Draw("same");
  c1->cd();
  TPad *c1_2 = new TPad("c1_2", "newpad",0.01,0.33,0.99,0.99);
  c1_2->Draw();
  c1_2->cd();
  c1_2->SetTopMargin(0.1);
  c1_2->SetBottomMargin(0.01);
  c1_2->SetRightMargin(0.1);
  c1_2->SetFillStyle(0);
  TLegend *leg = new TLegend(0.6,0.7,0.89,0.89);
  leg->AddEntry(Template_SigCor,"correlated");
  leg->AddEntry(Template_SigUnCor,"uncorrelated");
  leg->SetFillColor(kWhite);
  Template_SigCor->Draw("EHIST");
  Template_SigUnCor->Draw("EHISTsames");

  TH1F* Template_WJets = new TH1F("WJets","-2ln#lambda = 2lnL_{H=C} - 2lnL_{H=U}", nBins, low_range, high_range);
  TH1F* LikelihoodCutWJets = new TH1F("LikelihoodCutWJets","-lnL_{H=C};;entries", 50, 0, 100);
  TH1F* LikelihoodCutUnCorWJets = new TH1F("LikelihoodCutUnCorWJets","-lnL_{H=U};;entries", 50, 0, 100);
  if(Use_back){
    std::vector<float> WJetscor = (L_WJets)[0];
    std::vector<float> WJetsuncor = (L_WJets)[1];
    for(unsigned int i = 0; i < WJetscor.size(); i++){
      Template_WJets->Fill(2*(WJetscor)[i] - 2*(WJetsuncor)[i]);
      LikelihoodCutWJets->Fill(-1*(WJetscor)[i]);
      LikelihoodCutUnCorWJets->Fill(-1*(WJetsuncor)[i]);
    }
    Template_WJets->Sumw2();
    Template_WJets->Scale(1./Template_WJets->Integral("width"));
    Template_WJets->SetLineColor(kBlue);
    LikelihoodCutWJets->SetLineColor(kBlue);
    LikelihoodCutUnCorWJets->SetLineColor(kBlue);
    leg->AddEntry(Template_WJets,"WJets");
    Template_WJets->Draw("EHISTsames");
  }

  leg->Draw();
  c1->Modified();
  c1->Update();
  c1->SaveAs("InputTemplates.C");
  delete c1;

  TCanvas *c2 = new TCanvas();
  c2->cd();
  TLegend *leg2 = new TLegend(0.6,0.7,0.89,0.89);
  leg2->AddEntry(LikelihoodCutCor,"correlated");
  leg2->AddEntry(LikelihoodCutUnCor,"uncorrelated");
  leg2->SetFillColor(kWhite);
  LikelihoodCutCor->Draw();
  LikelihoodCutUnCor->Draw("sames");
  if(Use_back){
    LikelihoodCutWJets->Draw("sames");
    leg2->AddEntry(LikelihoodCutWJets,"WJets");
  }
  leg2->Draw();
  c2->Modified();
  c2->Update();
  c2->SaveAs("LikelihoodCut.C");
  delete c2;

  TCanvas *c3 = new TCanvas();
  c3->cd();
  TLegend *leg3 = new TLegend(0.6,0.7,0.89,0.89);
  leg3->AddEntry(LikelihoodCutUnCorCor,"correlated");
  leg3->AddEntry(LikelihoodCutUnCorUnCor,"uncorrelated");
  leg3->SetFillColor(kWhite);
  LikelihoodCutUnCorCor->Draw();
  LikelihoodCutUnCorUnCor->Draw("sames");
  if(Use_back){
    LikelihoodCutUnCorWJets->Draw("sames");
    leg3->AddEntry(LikelihoodCutUnCorWJets,"WJets");
  }
  leg3->Draw();
  c3->Modified();
  c3->Update();
  c3->SaveAs("LikelihoodCutUnCor.C");
  delete c3;

  std::vector<TH1F> *templates = new std::vector<TH1F>();
  templates->push_back(*Template_SigCor);
  templates->push_back(*Template_SigUnCor);
  if(Use_back){templates->push_back(*Template_WJets);}
  return *templates;
}

void eire::PEBuilder::SetProperties(int Bins, int EvPerPE, float lowRange, float highRange, bool v)
{
  nBins = Bins;
  EvPE = EvPerPE;
  low_range = lowRange;
  high_range = highRange;
  verbose = v;
}

void eire::PEBuilder::Mix()
{
  std::vector<float> TTcorcor = (L_Cor)[0];
  std::vector<float> TTcoruncor = (L_Cor)[1];
  std::vector<float> TTuncorcor = (L_Uncor)[0];
  std::vector<float> TTuncoruncor = (L_Uncor)[1];
  std::vector<float> WJetscor;
  std::vector<float> WJetsuncor;
  if(Wfrac > 0.){
    WJetscor = (L_WJets)[0];
    WJetsuncor = (L_WJets)[1];
  }

  TH1F* Pull = new TH1F("Pull","(f_obs - f_exp)/sigma_obs; pull; number of PE", 40, -6, 6);
  TH1F* h_fobs = new TH1F("h_fobs","Fitted fraction of correlation f; f_{obs}; number of PE", 30, -3, 4);
  TH1F* h_ferr = new TH1F("h_ferr","Fit error; #delta f; number of PE", 20, 0.0, 1.2);
  TH1F* h_Wobs = new TH1F("h_Wobs","Fitted background fraction W; W_{obs}; number of PE", 30, 0., 1.);
  TH1F* h_Werr = new TH1F("h_Werr","Fitted error; #delta W; number of PE", 20, 0, 0.1);
  TH1F* h_WPull = new TH1F("h_WPull","(W_obs - W_exp)/sigma_obs); pull; number of PE", 40, -3., 3.);

  std::vector<TH1F> *hists = new std::vector<TH1F>();
  TH1F* Data = new TH1F("Data","-2ln#lambda = 2lnL_{H=C} - 2lnL_{H=U}", nBins, low_range, high_range);
  hists->push_back(*Data);
  int i = 0;
  int ev_cor = (int) (mix_frac*EvPE*(1. - Wfrac));
  int ev_uncor = (int) ((1. - mix_frac)*EvPE*(1. - Wfrac));
  int ev_w = (int) (EvPE*Wfrac);
  TH1F* Data2[2000];
  char histname[2000];

  if(ev_cor > 0){
    for(unsigned int j =0; j < TTcorcor.size(); j++){
      (*hists)[i].Fill(2*(TTcorcor)[j] - 2*(TTcoruncor)[j]);
      if( j % ev_cor == 0 && j != 0){
	i++;
	sprintf(histname,"Data2_%i",i);
	Data2[i] = new TH1F(histname,"-2ln#lambda = 2lnL_{H=C} - 2lnL_{H=U}", nBins, low_range, high_range);
	hists->push_back(*Data2[i]);
      }
    }
  }

  int w = 0;
  if(ev_cor > 0 && ev_uncor > 0){
    for(unsigned int j = 0; j < TTuncorcor.size();j++){
      (*hists)[w].Fill(2*(TTuncorcor)[j] - 2*(TTuncoruncor)[j]);
      if( j % ev_uncor == 0 && j != 0){
	w++;
	if(w >= (int) hists->size()){break;}
      }
    }
  }if(ev_uncor > 0 && ev_cor == 0){
    for(unsigned int j =0; j < TTuncorcor.size(); j++){
      (*hists)[w].Fill(2*(TTuncorcor)[j] - 2*(TTuncoruncor)[j]);
      if( j % ev_uncor == 0 && j != 0){
	w++;
	sprintf(histname,"Data2_%i",w);
	Data2[w] = new TH1F(histname,"-2ln#lambda = 2lnL_{H=C} - 2lnL_{H=U}", nBins, low_range, high_range);
	hists->push_back(*Data2[w]);
      }
    }
  }

  if(w == 0){w = i;}

  if(ev_w > 0){
    int l = 0;
    for(unsigned int j = 0; j < WJetscor.size(); j++){
      (*hists)[l].Fill(2*(WJetscor)[j] - 2*(WJetsuncor)[j]);
      if( j % ev_w == 0 && j != 0 ){
	l++;
	if(l >= w ){break;}
      }
    }
    w = l;
  }

  std::vector<TH1F> templates = DrawTemplates();
  TH1F TemplateCor = templates[0];
  TH1F TemplateUncor = templates[1];
  TH1F TemplateWJets;
  if(Use_back){TemplateWJets = templates[2];}
  

  int nexp = w;
  for(int z = 0; z < nexp; z++){
    TH1F H = (*hists)[z];
    H.Sumw2();
    std::vector<double> res;
    if(Use_back){res = FitB(&H, z, TemplateCor, TemplateUncor, TemplateWJets);}
    else{res = Fit(&H, z, TemplateCor, TemplateUncor);}
    double f= (res)[0];
    double Err_f=(res)[1];
    double Converged = (res)[2];
    if(Converged > 2){
      Pull->Fill((f - mix_frac)/Err_f);
      h_fobs->Fill(f);
      h_ferr->Fill(Err_f);
      if(Use_back){
	double W = (res)[4];
	double W_err = (res)[5];
	h_Wobs->Fill(W);
	h_Werr->Fill(W_err);
	h_WPull->Fill((W - Wfrac)/W_err);
      }
    }
    gStyle->SetOptStat(1111111);
  }

  TF1 *g_f = new TF1("g_f","gaus",-2,3);
  g_f->SetLineWidth(0.08);
  TF1 *g_ferr = new TF1("g_ferr","gaus",0.0,0.7);
  g_ferr->SetLineWidth(0.08);
  TF1 *g_pull = new TF1("g_pull","gaus",-6,6);
  g_pull->SetLineWidth(0.08);
  TF1 *g_W = new TF1("g_W","gaus",0.0,1.0);
  g_W->SetLineWidth(0.08);
  TF1 *g_Werr = new TF1("g_Werr","gaus",0.0,0.1);
  g_Werr->SetLineWidth(0.08);
  TF1 *g_Wpull = new TF1("g_Wpull","gaus",-3.0,3.0);
  g_Wpull->SetLineWidth(0.08);

  TCanvas *c3 = new TCanvas();
  gStyle->SetOptStat(2200);
  c3->Divide(2,1);
  c3->cd(1);
  h_fobs->Draw();
  h_fobs->Fit("g_f");
  c3->cd(2);
  h_ferr->Draw();
  h_ferr->Fit("g_ferr");
  c3->SaveAs("fhists.C");
  TCanvas *c5 = new TCanvas();
  c5->cd();
  Pull->Draw();
  Pull->Fit("g_pull");
  c5->SaveAs("Pull.C");
  if(Use_back){
  TCanvas *c4 = new TCanvas();
  c4->Divide(3,1);
  c4->cd(1);
  h_Wobs->Draw();
  h_Wobs->Fit("g_W");
  c4->cd(2);
  h_Werr->Draw();
  h_Werr->Fit("g_Werr");
  c4->cd(3);
  h_WPull->Draw();
  h_WPull->Fit("g_Wpull");
  c4->SaveAs("Whists.C");
  }
}

std::vector<double> eire::PEBuilder::Fit(TH1F *hist_data, int k, TH1F TemplateCor, TH1F TemplateUncor)
{

  using namespace RooFit;
  RooMsgService::instance().setSilentMode(1);
  RooMsgService::instance().setGlobalKillBelow(RooFit::WARNING);
  RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR);  

  RooRealVar* IndL_ = new RooRealVar("IndL","-2ln#lambda",low_range, high_range, "x");

  RooRealVar IndL = *IndL_;

  gROOT->cd();
  
  RooArgList X(IndL);
  ///////// convert Histograms into RooDataHists                                                                                                           
  RooDataHist* data = new RooDataHist("data","data",X, hist_data);
  RooDataHist* MC_cor = new RooDataHist("MC_cor","MC_cor", X, &TemplateCor,2);
  RooDataHist* MC_uncor = new RooDataHist("MC_uncor","MC_uncor", X, &TemplateUncor,2);
  RooHistPdf* Cor = new RooHistPdf("Cor","Cor", X, *MC_cor);
  RooHistPdf* UnCor = new RooHistPdf("UnCor","UnCor", X, *MC_uncor);
  
  RooArgList *Sum = new RooArgList();
  Sum->add(*Cor);
  Sum->add(*UnCor);

  RooRealVar* f = new RooRealVar("f","f",0.5,-200,200);
  
  RooAddPdf pdfPass("pdfPass","sum pdf", *Sum, *f);//f*cor+(1-f)*uncor                                                                                     
  RooFitResult *fitResult = pdfPass.fitTo(*data,Minos(kTRUE),Save(),SumW2Error(kFALSE));
  if(verbose){
  //  fitResult->Print();
  TString cname = TString("fit");
  TCanvas* c = new TCanvas(cname,cname,500,500);
  RooPlot* frame1 = IndL.frame();
  frame1->SetMinimum(0);
  RooAbsData::ErrorType errorType = RooAbsData::SumW2;
  data->plotOn(frame1,RooFit::DataError(errorType));
  pdfPass.plotOn(frame1,RooFit::ProjWData(*data),RooFit::Components(*Cor),RooFit::LineColor(kRed));
  pdfPass.plotOn(frame1,RooFit::ProjWData(*data),RooFit::Components(*UnCor),RooFit::LineColor(kGreen));
  pdfPass.plotOn(frame1,RooFit::ProjWData(*data));
  pdfPass.plotOn(frame1);
  pdfPass.paramOn(frame1,data);
  frame1->Draw("e0");
  char fname[1024];
  sprintf(fname,"fit_%i.pdf",k);
  c->SaveAs(fname);
  delete c;
  }

  std::vector<double> results;
  double x = f->getVal();
  results.push_back(x);
  double Err = f->getError();
  results.push_back(Err);
  results.push_back(fitResult->covQual());
  results.push_back(fitResult->status());
  
  return results;
}

std::vector<double> eire::PEBuilder::FitB(TH1F *hist_data, int k, TH1F TemplateCor, TH1F TemplateUncor, TH1F TemplateWJets)
{

  using namespace RooFit;
  RooMsgService::instance().setSilentMode(1);
  RooMsgService::instance().setGlobalKillBelow(RooFit::WARNING);
  RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR);  

  RooRealVar* IndL_ = new RooRealVar("IndL","IndL",low_range, high_range, "x");
  RooRealVar IndL = *IndL_;
  
  gROOT->cd();
  
  RooArgList X(IndL);
  ///////// convert Histograms into RooDataHists                                                                                                           
  RooDataHist* data = new RooDataHist("data","data",X, hist_data);
  RooDataHist* MC_cor = new RooDataHist("MC_cor","MC_cor", X, &TemplateCor,2);
  RooDataHist* MC_uncor = new RooDataHist("MC_uncor","MC_uncor", X, &TemplateUncor,2);
  RooDataHist* MC_WJets = new RooDataHist("MC_WJets","WJets", X, &TemplateWJets,2);

  RooHistPdf* Cor = new RooHistPdf("Cor","Cor", X, *MC_cor);
  RooHistPdf* UnCor = new RooHistPdf("UnCor","UnCor", X, *MC_uncor);
  RooHistPdf* WJets = new RooHistPdf("WJets","WJets", X, *MC_WJets);
  
  RooArgList *Sum = new RooArgList();
  Sum->add(*WJets);
  Sum->add(*Cor);
  Sum->add(*UnCor);
  
  RooRealVar* f = new RooRealVar("f","f",0.5,-200,200);
  RooRealVar* W = new RooRealVar("W","W",0.0,0.0,1.0);

  RooArgList F(*W, *f);
  RooAddPdf pdfPass("pdfPass","sum pdf", *Sum, F, kTRUE);
  
  RooFitResult *fitResult = pdfPass.fitTo(*data,Minos(kTRUE),Save(),SumW2Error(kFALSE));
  if(verbose){
    //fitResult->Print();
  TString cname = TString("fit");
  TCanvas* c = new TCanvas(cname,cname,500,500);                                                                                                       
  RooPlot* frame1 = IndL.frame();                                                                                                                      
  frame1->SetMinimum(0);                                                                                                                               
  RooAbsData::ErrorType errorType = RooAbsData::SumW2;                                                                                                 
  data->plotOn(frame1,RooFit::DataError(errorType));                                                                                                   
  pdfPass.plotOn(frame1,RooFit::ProjWData(*data),RooFit::Components(*Cor),RooFit::LineColor(kRed));                                                    
  pdfPass.plotOn(frame1,RooFit::ProjWData(*data),RooFit::Components(*UnCor),RooFit::LineColor(kGreen));                                                
  pdfPass.plotOn(frame1,RooFit::ProjWData(*data),RooFit::Components(*WJets),RooFit::LineColor(kOrange));                                               
  pdfPass.plotOn(frame1,RooFit::ProjWData(*data));                                                                                                     
  pdfPass.plotOn(frame1);                                                                                                                        
  pdfPass.paramOn(frame1,data);                                                                                                                        
  frame1->Draw("e0");                                                                                                                                  
  char fname[1024];                                                                                                                                    
  sprintf(fname,"fit_%i.pdf",k);                                                                                                                 
  c->SaveAs(fname);                                                                                                                                    
  delete c;                                                                                                                                            
  }
  std::vector<double> results;
  double x = f->getVal();
  results.push_back(x);
  double Err = f->getError();
  results.push_back(Err);
  results.push_back(fitResult->covQual());
  results.push_back(fitResult->status());
  results.push_back(W->getVal());
  results.push_back(W->getError());
  results.push_back(fitResult->correlation("f","W"));
  return results;
}
