#include "PEBuilder.h"

//Pseudo-Experiment Builder
eire::PEBuilder::PEBuilder(std::vector< std::vector<float> > Cor, std::vector< std::vector<float> > Uncor, std::vector< std::vector<float> > WJets, float Back_frac, bool use_back, string name)
{
  L_Cor = Cor;
  L_Uncor = Uncor;
  L_WJets = WJets;
  Wfrac = Back_frac;
  Use_back = use_back;
  verbose = false;
  Name = name;
  match = false;
}

eire::PEBuilder::~PEBuilder()
{
}

void eire::PEBuilder::TurnMatchingOn(std::vector< bool > cor, std::vector< bool > uncor)
{
  match = true;
  match_cor = cor;
  match_uncor = uncor;
}

std::vector<TH1F> eire::PEBuilder::DrawTemplates()
{
  TH1F* Template_SigCor = new TH1F("Correlated","-2ln#lambda = 2lnL_{H=C} - 2lnL_{H=U};;normalised entries", nBins, low_range, high_range);
  TH1F* Template_SigUnCor = new TH1F("UnCorrelated","-2ln#lambda = 2lnL_{H=C} - 2lnL_{H=U};;normalised entries", nBins, low_range, high_range);
  TH1F* LikelihoodCutCor = new TH1F("LikelihoodCutCor","-lnL_{H=C};-lnL_{H=C};entries", 50, 0, 100);
  TH1F* LikelihoodCutUnCor = new TH1F("LikelihoodCutUnCor","-lnL_{H=C};-lnL_{H=C};entries", 50, 0, 100);
  TH1F* LikelihoodCutUnCorCor = new TH1F("LikelihoodCutUnCorCor","-lnL_{H=U};-lnL_{H=U};entries", 50, 0, 100);
  TH1F* LikelihoodCutUnCorUnCor = new TH1F("LikelihoodCutUnCorUnCor","-lnL_{H=U};-lnL_{H=U};entries", 50, 0, 100);
  TH1F* LikelihoodCutCor_wrong = new TH1F("LikelihoodCutCor_wrong","-lnL_{H=C};-lnL_{H=C};entries", 50, 0, 100);
  TH1F* LikelihoodCutUnCor_wrong = new TH1F("LikelihoodCutUnCor_wrong","-lnL_{H=C};-lnL_{H=C};entries", 50, 0, 100);
  TH1F* LikelihoodCutUnCorCor_wrong = new TH1F("LikelihoodCutUnCorCor_wrong","-lnL_{H=U};-lnL_{H=U};entries", 50, 0, 100);
  TH1F* LikelihoodCutUnCorUnCor_wrong = new TH1F("LikelihoodCutUnCorUnCor_wrong","-lnL_{H=U};-lnL_{H=U};entries", 50, 0, 100);

  TH2F* LikelihoodCorVsUnCor_corsample = new TH2F("LikelihoodCorVsUnCor_corsample","-lnL_{H=C} vs -lnL_{H=U};-lnL_{H=C};-lnL_{H=U}", 50, 40, 90,50,40,90);
  TH2F* LikelihoodCorVsUnCor_uncorsample = new TH2F("LikelihoodCorVsUnCor_uncorsample","-lnL_{H=C} vs -lnL_{H=U};-lnL_{H=C};-lnL_{H=U}", 50, 40, 90,50,40,90);
  TH2F* LikelihoodCorVsUnCor_Wsample = new TH2F("LikelihoodCorVsUnCor_Wsample","-lnL_{H=C} vs -lnL_{H=U};-lnL_{H=C};-lnL_{H=U}", 50, 40, 90,50,40,90);

  std::vector<float> TTcorcor = (L_Cor)[0];
  std::vector<float> TTcoruncor = (L_Cor)[1];
  std::vector<float> TTuncorcor = (L_Uncor)[0];
  std::vector<float> TTuncoruncor = (L_Uncor)[1];

  std::cout<<"TTcorcor size = "<<TTcorcor.size()<<std::endl;
  for(unsigned int i = 0; i < TTcorcor.size(); i++){
    Template_SigCor->Fill(2*(TTcorcor)[i] - 2*(TTcoruncor)[i]);
    if(!match || match_cor[i]){
      LikelihoodCutCor->Fill(-1*(TTcorcor)[i]);
      LikelihoodCutUnCorCor->Fill(-1*(TTcoruncor)[i]);
      LikelihoodCorVsUnCor_corsample->Fill(-1*(TTcorcor)[i],-1*(TTcoruncor)[i]);
    }
    else{
      std::cout<<"fill cor"<<std::endl;
      LikelihoodCutCor_wrong->Fill(-1*(TTcorcor)[i]);
      LikelihoodCutUnCorCor_wrong->Fill(-1*(TTcoruncor)[i]);
    }
  }
  for(unsigned int i = 0; i < TTuncorcor.size(); i++){
    Template_SigUnCor->Fill(2*(TTuncorcor)[i] - 2*(TTuncoruncor)[i]);
    if(!match || match_uncor[i]){
      LikelihoodCutUnCor->Fill(-1*(TTuncorcor)[i]);
      LikelihoodCutUnCorUnCor->Fill(-1*(TTuncoruncor)[i]);
      LikelihoodCorVsUnCor_uncorsample->Fill(-1*(TTuncorcor)[i],-1*(TTuncoruncor)[i]);
    }
    else{
      std::cout<<"fill uncor"<<std::endl;
      LikelihoodCutUnCor_wrong->Fill(-1*(TTuncorcor)[i]);
      LikelihoodCutUnCorUnCor_wrong->Fill(-1*(TTuncoruncor)[i]);
    }
  }
  
  Template_SigCor->Sumw2();
  Template_SigUnCor->Sumw2();
  Template_SigCor->Scale(1./Template_SigCor->Integral("width"));
  Template_SigUnCor->Scale(1./Template_SigUnCor->Integral("width"));
  Template_SigCor->SetLineColor(kRed);
  Template_SigUnCor->SetLineColor(kBlack);

  LikelihoodCutCor->Scale(1./LikelihoodCutCor->Integral("width"));
  LikelihoodCutUnCor->Scale(1./LikelihoodCutUnCor->Integral("width"));

  LikelihoodCutCor->SetLineColor(kRed);
  LikelihoodCutUnCor->SetLineColor(kBlack);
  LikelihoodCutUnCorCor->SetLineColor(kRed);
  LikelihoodCutUnCorUnCor->SetLineColor(kBlack);
  LikelihoodCutCor_wrong->SetLineColor(kBlue);
  LikelihoodCutUnCor_wrong->SetLineColor(kBlue);
  LikelihoodCutUnCorCor_wrong->SetLineColor(kBlue);
  LikelihoodCutUnCorUnCor_wrong->SetLineColor(kBlue);
  //  LikelihoodCutCor_wrong->SetLineStyle(2);
  LikelihoodCutUnCor_wrong->SetLineStyle(2);
  //LikelihoodCutUnCorCor_wrong->SetLineStyle(2);
  LikelihoodCutUnCorUnCor_wrong->SetLineStyle(2);

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
  SF->SetMinimum(0.500);
  SF->SetMaximum(1.500);
  SF->GetYaxis()->SetNdivisions(5);
  SF->GetXaxis()->SetTitle("-2ln#lambda");
  SF->GetYaxis()->SetTitle("cor/uncor");
  SF->GetXaxis()->SetTitleSize(0.08);
  SF->GetXaxis()->SetLabelSize(0.08);
  SF->GetYaxis()->SetLabelSize(0.08);
  SF->GetYaxis()->SetTitleSize(0.08);
  SF->GetYaxis()->SetTitleOffset(0.34);
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
  Template_SigCor->GetYaxis()->SetLabelSize(0.05);
  Template_SigCor->GetYaxis()->SetTitleSize(0.05);
  Template_SigCor->GetYaxis()->SetTitleOffset(1.);
  Template_SigCor->SetLineWidth(2);
  LikelihoodCutCor->SetLineWidth(2);
  Template_SigCor->Draw("EHIST");
  Template_SigUnCor->GetYaxis()->SetLabelSize(0.05);
  Template_SigUnCor->GetYaxis()->SetTitleSize(0.05);
  Template_SigUnCor->GetYaxis()->SetTitleOffset(1.);
  LikelihoodCutUnCor->SetLineWidth(2);
  LikelihoodCutUnCor->SetLineStyle(2);
  Template_SigUnCor->SetLineWidth(2);
  Template_SigUnCor->SetLineStyle(2);
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
      LikelihoodCorVsUnCor_Wsample->Fill(-1*(WJetscor)[i],-1*(WJetsuncor)[i]);
    }
    Template_WJets->Sumw2();
    Template_WJets->Scale(1./Template_WJets->Integral("width"));
    Template_WJets->SetLineColor(kBlue);
    LikelihoodCutWJets->Scale(1./LikelihoodCutWJets->Integral("width"));
    LikelihoodCutWJets->SetLineColor(kBlue);
    LikelihoodCutWJets->SetLineWidth(2);
    LikelihoodCutWJets->SetLineStyle(3);
    LikelihoodCutUnCorWJets->SetLineColor(kBlue);
    Template_WJets->SetLineWidth(2);
    Template_WJets->SetLineStyle(3);
    leg->AddEntry(Template_WJets,"WJets");
    Template_WJets->Draw("EHISTsames");
  }

  leg->Draw();
  stringstream nameT;
  nameT<<"InputTemplates"<<Name;
  nameT<<".C";
  c1->Modified();
  c1->Update();
  c1->SaveAs(nameT.str().c_str());
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
  if(match){
    LikelihoodCutCor_wrong->Draw("sames");
    leg2->AddEntry(LikelihoodCutCor_wrong,"correlated wrong");
    LikelihoodCutUnCor_wrong->Draw("sames");
    leg2->AddEntry(LikelihoodCutUnCor_wrong,"uncorrelated wrong");
  }
  leg2->Draw();
  c2->Modified();
  c2->Update();
  stringstream Lcut;
  Lcut<<"LikelihoodCut"<<Name;
  Lcut<<".C";
  c2->SaveAs(Lcut.str().c_str());
  delete c2;

  TCanvas *c25 = new TCanvas();
  c25->cd();
  TLegend *leg25 = new TLegend(0.6,0.7,0.89,0.89);
  leg25->AddEntry(LikelihoodCorVsUnCor_corsample,"correlated");
  leg25->SetFillColor(kWhite);
  LikelihoodCorVsUnCor_corsample->Draw("colz");
  leg25->Draw();
  c25->Modified();
  c25->Update();
  stringstream LVscor;
  LVscor<<"LikelihoodCorVsUnCor_corsample"<<Name;
  LVscor<<".C";
  c25->SaveAs(LVscor.str().c_str());
  delete c25;

  TCanvas *c26 = new TCanvas();
  c26->cd();
  TLegend *leg26 = new TLegend(0.6,0.7,0.89,0.89);
  leg26->AddEntry(LikelihoodCorVsUnCor_uncorsample,"uncorrelated");
  leg26->SetFillColor(kWhite);
  LikelihoodCorVsUnCor_uncorsample->Draw("colz");
  leg26->Draw();
  c26->Modified();
  c26->Update();
  stringstream LVsuncor;
  LVsuncor<<"LikelihoodCorVsUnCor_uncorsample"<<Name;
  LVsuncor<<".C";
  c26->SaveAs(LVsuncor.str().c_str());
  delete c26;

  if(Use_back){
    TCanvas *c27 = new TCanvas();
    c27->cd();
    TLegend *leg27 = new TLegend(0.6,0.7,0.89,0.89);
    leg27->AddEntry(LikelihoodCorVsUnCor_Wsample,"WJets");
    leg27->SetFillColor(kWhite);
    LikelihoodCorVsUnCor_Wsample->Draw("colz");
    leg27->Draw();
    c27->Modified();
    c27->Update();
    stringstream LVs_w;
    LVs_w<<"LikelihoodCorVsUnCor_wsample"<<Name;
    LVs_w<<".C";
    c27->SaveAs(LVs_w.str().c_str());
    delete c27;
  }

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
  if(match){
    LikelihoodCutUnCorCor_wrong->Draw("sames");
    leg3->AddEntry(LikelihoodCutUnCorCor_wrong,"correlated wrong");
    LikelihoodCutUnCorUnCor_wrong->Draw("sames");
    leg3->AddEntry(LikelihoodCutUnCorUnCor_wrong,"uncorrelated wrong");
  }
  leg3->Draw();
  c3->Modified();
  c3->Update();
  stringstream Luncorcut;
  Luncorcut<<"LikelihoodCutUnCor"<<Name;
  Luncorcut<<".C";
  c3->SaveAs(Luncorcut.str().c_str());
  delete c3;

  std::vector<TH1F> *templates = new std::vector<TH1F>();
  templates->push_back(*Template_SigCor);
  templates->push_back(*Template_SigUnCor);
  if(Use_back){templates->push_back(*Template_WJets);}
  return *templates;
}

void eire::PEBuilder::SetProperties(int Bins, int EvPerPE, float lowRange, float highRange, bool v, float mixing)
{
  nBins = Bins;
  EvPE = EvPerPE;
  low_range = lowRange;
  high_range = highRange;
  verbose = v;
  mix_frac = mixing;
}

std::vector<double> eire::PEBuilder::Mix(std::vector<TH1F> templates)
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
  
  char Pn[2000], fn[2000], fen[2000], Wn[2000], Wen[2000], Wp[2000], Nn[2000], Nne[2000], Cov_f_Nobs[2000], Cov_f_W[2000];
  char PNe[2000], Cov_W_N[2000];
  sprintf(Pn,"Pull_mix_%i",(int) (mix_frac*10));
  sprintf(fn,"h_fobs_mix_%i", (int) (mix_frac*10));
  sprintf(fen,"h_ferr_mix_%i", (int) (mix_frac*10));
  sprintf(Wn,"h_Wobs_mix_%i",(int) (mix_frac*10));
  sprintf(Wen,"h_Werr_mix_%i",(int) (mix_frac*10));
  sprintf(Wp,"h_WPull_mix_%i",(int) (mix_frac*10));
  sprintf(Nn,"h_Nobs_mix_%i",(int) (mix_frac*10));
  sprintf(Nne,"h_Nobs_err_mix_%i",(int) (mix_frac*10));
  sprintf(PNe,"h_Pull_Ne_mix_%i",(int) (mix_frac*10));
  sprintf(Cov_f_Nobs,"h_Cov_f_Nobs_mix_%i",(int) (mix_frac*10));
  sprintf(Cov_f_W,"h_Cov_f_W_mix_%i",(int) (mix_frac*10));
  sprintf(Cov_W_N,"h_Cov_W_N_mix_%i",(int) (mix_frac*10));
  TH1F* Pull = new TH1F(Pn,"(f_obs - f_input)/sigma_obs; pull; number of PE", 15, -6, 6);
  TH1F* h_fobs = new TH1F(fn,"Fitted fraction of correlated events f; f_{obs}; number of PE", 60, -3., 4.);
  TH1F* h_ferr = new TH1F(fen,"Fit error; #delta f; number of PE", 150, 0.0, 1.0);
  //  TH1F* h_Wobs = new TH1F(Wn,"Fitted background fraction W; W_{obs}; number of PE", 70, 0.0, 1.0);//0.2
  //TH1F* h_Werr = new TH1F(Wen,"Fitted error; #delta W; number of PE", 100, 0, 0.1);
  TH1F* h_Wobs = new TH1F(Wn,"Fitted number of background events N_{bkg}; N_{bkg}; number of PE", 70, 50.0, 200.0);//0.2
  TH1F* h_Werr = new TH1F(Wen,"Fitted error; #delta N_{bkg}; number of PE", 100, 0, 100);
  TH1F* h_WPull = new TH1F(Wp,"(N_{bkg} - N^{input}_{bkg})/sigma_obs); pull; number of PE", 10, -4., 4.);
  TH1F* h_NPull = new TH1F(PNe,"(N_{ttbar} - N^{input}_{ttbar})/sigma_obs); pull; number of PE", 10, -4., 4.);
  TH1F* h_Nobs = new TH1F(Nn,"Fitted number of ttbar events N_{ttbar}; N_{ttbar}; number of PE",100,200,800);
  TH1F* h_Nobs_err = new TH1F(Nne,"Error on N_{ttbar}; #delta N_{ttbar}; number of PE",50,15,30);
  TH1F* h_Cov_f_Nobs = new TH1F(Cov_f_Nobs,"Correlation between f_obs and N_{ttbar}; correlation; number of PE",120,-1.,0.);
  TH1F* h_Cov_f_W = new TH1F(Cov_f_W,"Correlation between f_obs and N_{bkg}; correlation; number of PE",120,0.,1.);
  TH1F* h_Cov_W_N = new TH1F(Cov_W_N,"Correlation between N_{ttbar} and N_{bkg}; correlation; number of PE",120,-1.,0.);

  TF1 *g_f = new TF1("g_f","gaus",-3,4);
  g_f->SetLineWidth(0.08);
  TF1 *g_ferr = new TF1("g_ferr","gaus",0.0,0.5);
  g_ferr->SetLineWidth(0.08);
  TF1 *g_N = new TF1("g_N","gaus",200.0,800.);
  g_N->SetLineWidth(0.08);
  TF1 *g_Nerr = new TF1("g_Nerr","gaus",15.,30.);
  g_Nerr->SetLineWidth(0.08);
  TF1 *g_pull = new TF1("g_pull","gaus",-6,6);
  g_pull->SetLineWidth(0.08);
  TF1 *g_pullN = new TF1("g_pullN","gaus",-4,4);
  g_pullN->SetLineWidth(0.08);
  TF1 *g_W = new TF1("g_W","gaus",50.0,200.);
  g_W->SetLineWidth(0.08);
  TF1 *g_Werr = new TF1("g_Werr","gaus",0.0,100);
  g_Werr->SetLineWidth(0.08);
  TF1 *g_Wpull = new TF1("g_Wpull","gaus",-4.0,4.0);
  g_Wpull->SetLineWidth(0.08);
  TF1 *g_Cov_f_N = new TF1("g_Cov_f_N","gaus",-1.0,0.0);
  g_Cov_f_N->SetLineWidth(0.08);
  TF1 *g_Cov_f_W = new TF1("g_Cov_f_W","gaus",0.0,1.0);
  g_Cov_f_W->SetLineWidth(0.08);
  TF1 *g_Cov_W_N = new TF1("g_Cov_W_N","gaus",-1.0,0.0);
  g_Cov_W_N->SetLineWidth(0.08);


  Pull->Sumw2();
  h_fobs->Sumw2();
  h_ferr->Sumw2();
  h_Wobs->Sumw2();
  h_Werr->Sumw2();
  h_WPull->Sumw2();
  h_NPull->Sumw2();
  h_Nobs->Sumw2();
  h_Nobs_err->Sumw2();
  h_Cov_f_Nobs->Sumw2();
  h_Cov_f_W->Sumw2();
  h_Cov_W_N->Sumw2();

  std::vector<TH1F> *hists = new std::vector<TH1F>();
  char histname[2000];
  sprintf(histname,"Data_mix_%f",mix_frac);
  TH1F* Data = new TH1F(histname,"-2ln#lambda = 2lnL_{H=C} - 2lnL_{H=U}", nBins, low_range, high_range);
  hists->push_back(*Data);
  int PoissonMean = EvPE;
  int i = 0;
  int ev_cor = (int) (mix_frac*EvPE*(1. - Wfrac));
  int ev_uncor = (int) ((1. - mix_frac)*EvPE*(1. - Wfrac));
  int ev_w = (int) (EvPE*Wfrac);
  TH1F* Data2[2000];
  int cor_stop_prev = 0;
  int uncor_stop_prev = 0;
  int w_stop_prev = 0;
  std::vector<int> *EvInPE = new std::vector<int>();

  TRandom2 *EvGen = new TRandom2();
  EvGen->SetSeed();
  
  if(ev_cor > 0){
    EvPE = EvGen->Poisson(PoissonMean);
    
    for(unsigned int j =0; j < TTcorcor.size(); j++){
      ev_cor = (int) (mix_frac*EvPE*(1. - Wfrac));
      (*hists)[i].Fill(2*(TTcorcor)[j] - 2*(TTcoruncor)[j]);
      if( (int) j == (cor_stop_prev + ev_cor) && j != 0){
	i++;
	EvInPE->push_back(EvPE);
	EvPE = EvGen->Poisson(PoissonMean);
	cor_stop_prev = j;
	sprintf(histname,"Data2_%i_mix_%f",i,mix_frac);
	Data2[i] = new TH1F(histname,"-2ln#lambda = 2lnL_{H=C} - 2lnL_{H=U}", nBins, low_range, high_range);
	hists->push_back(*Data2[i]);
      }
    }
  }

  int w = 0;
  if(ev_cor > 0 && ev_uncor > 0){
    for(unsigned int j = 0; j < TTuncorcor.size();j++){
      EvPE = (*EvInPE)[w];
      ev_uncor = (int) ((1. - mix_frac)*EvPE*(1. - Wfrac));
      (*hists)[w].Fill(2*(TTuncorcor)[j] - 2*(TTuncoruncor)[j]);
      if((int) j == uncor_stop_prev + ev_uncor && j != 0){
	w++;
	uncor_stop_prev = j;
	if(w >= (int) hists->size()){break;}
      }
    }
  }if(ev_uncor > 0 && ev_cor == 0){
    EvPE = EvGen->Poisson(PoissonMean);
    for(unsigned int j =0; j < TTuncorcor.size(); j++){
      ev_uncor = (int) ((1. - mix_frac)*EvPE*(1. - Wfrac));
      (*hists)[w].Fill(2*(TTuncorcor)[j] - 2*(TTuncoruncor)[j]);
      if((int) j == uncor_stop_prev + ev_uncor && j != 0){
	w++;
	EvInPE->push_back(EvPE);
	EvPE = EvGen->Poisson(PoissonMean);
	uncor_stop_prev = j;
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
      EvPE = (*EvInPE)[l];
      ev_w = (int) (EvPE*Wfrac);
      (*hists)[l].Fill(2*(WJetscor)[j] - 2*(WJetsuncor)[j]);
      if((int) j == w_stop_prev + ev_w && j != 0 ){
	l++;
	w_stop_prev = j;
	if(l >= w ){break;}
      }
    }
    w = l;
  }


  TH1F TemplateCor = templates[0];
  TH1F TemplateUncor = templates[1];
  TH1F TemplateWJets;
  if(Use_back){TemplateWJets = templates[2];}

  FILE *event_f;
  char name[2000];
  sprintf(name,"event_f_%f",mix_frac);
  event_f = fopen(name,"w");  

  int nexp = w;
  for(int z = 0; z < nexp; z++){
    //for(int z = 0; z < 500; z++){
    TH1F H = (*hists)[z];
    H.Sumw2();
    std::vector<double> res;
    if(Use_back){res = FitB(&H, z, TemplateCor, TemplateUncor, TemplateWJets);}
    else{res = Fit(&H, z, TemplateCor, TemplateUncor);}
    double f= (res)[0];
    double Err_f=(res)[1];
    double Nobs = (res)[2];
    double Nerr = (res)[3];
    double Converged = (res)[4];
    double status = (res)[5];
    double edm = (res)[6];
    double Cor_f_N = (res)[7];
    if(status == 0){
      Pull->Fill((f - mix_frac)/Err_f);
      h_fobs->Fill(f);
      h_ferr->Fill(Err_f);
      h_Nobs->Fill(Nobs);
      h_Nobs_err->Fill(Nerr);
      h_NPull->Fill((Nobs - (1-Wfrac)*PoissonMean)/Nerr);
      h_Cov_f_Nobs->Fill(Cor_f_N);
      int NPE = (*EvInPE)[z];
      if(Use_back){
	double W = (res)[8];
	double W_err = (res)[9];
	double cor_f_w = (res)[10];
	double cor_w_N = (res)[11];
	h_Wobs->Fill(W);
	h_Werr->Fill(W_err);
	//	h_WPull->Fill((W - Wfrac)/W_err);
	h_WPull->Fill((W - Wfrac*PoissonMean)/W_err);
	h_Cov_f_W->Fill(cor_f_w);
	h_Cov_W_N->Fill(cor_w_N);
      }
      int ev_cor = (int) ( NPE*mix_frac);
      int ev_uncor = (int) ( NPE*(1-mix_frac));
      for(int i = 0; i < ev_cor; i++){
        fprintf(event_f,"%i\t%.3f\n",i+z*ev_cor,f); //correlated events                                                                                      
      }
      for(int i = 0; i < ev_uncor; i++){
        fprintf(event_f,"%i\t%.3f\n",-1*(i+z*ev_uncor),f); //uncorrelated events                                                                            
      }
    }
    gStyle->SetOptStat(1111111);
  }

  fclose(event_f);

  TCanvas *c3 = new TCanvas();
  gStyle->SetOptStat(2200);
  c3->Divide(3,1);
  c3->cd(1);
  h_fobs->Draw();
  h_fobs->Fit("g_f");
  c3->cd(2);
  h_ferr->Draw();
  h_ferr->Fit("g_ferr");
  c3->cd(3);
  Pull->Draw();
  Pull->Fit("g_pull");
  stringstream namef;
  stringstream n;
  n<<"_mix_"<<mix_frac;
  namef<<"fhists_"<<Name<<n.str()<<".C";
  c3->SaveAs(namef.str().c_str());
  TCanvas *c5 = new TCanvas();
  c5->Divide(3,1);
  c5->cd(1);
  h_Nobs->Draw();
  h_Nobs->Fit("g_N");
  c5->cd(2);
  h_Nobs_err->Draw();
  h_Nobs_err->Fit("g_Nerr");
  c5->cd(3);
  h_NPull->Draw();
  h_NPull->Fit("g_pullN");
  stringstream nameP;
  nameP<<"Nobs_"<<Name<<n.str()<<".C";
  c5->SaveAs(nameP.str().c_str());

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
  stringstream nameW;
  nameW<<"Whists_"<<Name<<n.str()<<".C";
  c4->SaveAs(nameW.str().c_str());
  TCanvas *c11 = new TCanvas();
  c11->Divide(3,1);
  c11->cd(1);
  h_Cov_f_W->Draw();
  h_Cov_f_W->Fit("g_Cov_f_W");
  c11->cd(2);
  h_Cov_f_Nobs->Draw();
  h_Cov_f_Nobs->Fit("g_Cov_f_N");
  c11->cd(3);
  h_Cov_W_N->Draw();
  h_Cov_W_N->Fit("g_Cov_W_N");
  stringstream nameCovW;
  nameCovW<<"Correlation_"<<Name<<n.str()<<".C";
  c11->SaveAs(nameCovW.str().c_str());
  }
  //  else{
  // TCanvas *c10 = new TCanvas();
  //c10->cd();
  //h_Cov_f_Nobs->Draw();
  //h_Cov_f_Nobs->Fit("g_Cov_f_N");
  //stringstream nameCov;
  //nameCov<<"Correlation_"<<Name<<n.str()<<".C";
  //c10->SaveAs(nameCov.str().c_str());
  //}

  double f_av = g_f->GetParameter(1);
  double f_averr = g_f->GetParError(1);
  double p_av = g_pull->GetParameter(1);
  double p_averr = g_pull->GetParError(1);
  double p_RMS = g_pull->GetParameter(2);
  double p_RMSerr = g_pull->GetParError(2);

  if((f_av + 3*f_averr) < mix_frac || (f_av - 3*f_averr) > mix_frac){std::cout<<"%%%%%% WARNING! The mean f is biased for mixing fraction "<<mix_frac<<std::endl;}
  if((p_av + 3*p_averr) < 0 || (p_av - 3*p_averr) > 0){std::cout<<"%%%%%% WARNING! The pull mean is biased for mixing fraction "<<mix_frac<<std::endl;}
  if((p_RMS + 3*p_RMSerr) < 1 || (p_RMS - 3*p_RMSerr) > 1){std::cout<<"%%%%%% WARNING! The errors are not properly estimated for mixing fraction "<<mix_frac<<std::endl;}

  std::vector<double> Results;
  Results.push_back(f_av);
  Results.push_back(f_averr);
  Results.push_back(p_av);
  Results.push_back(p_averr);
  Results.push_back(p_RMS);
  Results.push_back(p_RMSerr);
  return Results;
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
  //  RooHistPdf* Cor_orig = new RooHistPdf("Cor_orig","Cor", X, *MC_cor);
  //RooHistPdf* UnCor_orig = new RooHistPdf("UnCor_orig","UnCor", X, *MC_uncor);
  
  // RooDataHist* H_Cor = Cor_orig->generateBinned(X, 350000, Extended(kTRUE)); 
  //RooDataHist* H_Uncor = UnCor_orig->generateBinned(X, 350000, Extended(kTRUE)); 

  RooHistPdf* Cor = new RooHistPdf("Cor","Cor", X, *MC_cor);
  RooHistPdf* UnCor = new RooHistPdf("UnCor","UnCor", X, *MC_uncor);

  RooArgList *Sum = new RooArgList();
  Sum->add(*Cor);
  Sum->add(*UnCor);

  RooRealVar* f = new RooRealVar("f","f",0.5);
  f->setConstant(kFALSE);

  RooRealVar* nEv = new RooRealVar("nEv","nEv",hist_data->GetEntries());
  nEv->setConstant(false);
  
  RooFormulaVar* nCor = new RooFormulaVar("nCor","f*nEv",RooArgList(*f,*nEv));
  RooFormulaVar* nUnCor = new RooFormulaVar("nUnCor","(1-f)*nEv",RooArgList(*f,*nEv));

  RooArgList yields(*nCor,*nUnCor);
    //RooArgList yields(*f);
  RooAddPdf pdfPass("pdfPass","sum pdf", *Sum, yields);//f*cor+(1-f)*uncor                                                              
                   
  RooFitResult *fitResult = pdfPass.fitTo(*data,Minos(kTRUE),Save(),SumW2Error(kFALSE),Hesse(kTRUE),InitialHesse(kTRUE),Extended(kTRUE),Minimizer("Minuit2","migrad"));
  //  RooFitResult *fitResult = pdfPass.fitTo(*data,Minos(kTRUE),Save(),SumW2Error(kFALSE),Hesse(kTRUE),InitialHesse(kTRUE),Extended(kFALSE),Minimizer("Minuit2","migrad"));
  if(verbose){
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
  double N = nEv->getVal();
  results.push_back(N);
  double N_err = nEv->getError();
  results.push_back(N_err);
  results.push_back(fitResult->covQual());
  results.push_back(fitResult->status());
  results.push_back(fitResult->edm());
  double cov = (fitResult->correlationMatrix())[0][1];
  results.push_back(fabs(cov));
  return results;
}

std::vector<double> eire::PEBuilder::FitB(TH1F *hist_data, int k, TH1F TemplateCor, TH1F TemplateUncor, TH1F TemplateWJets)
{

  using namespace RooFit;
  RooMsgService::instance().setSilentMode(1);
  RooMsgService::instance().setGlobalKillBelow(RooFit::WARNING);
  RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR);  
  
  //  RooRealVar* IndL_ = new RooRealVar("IndL","IndL",low_range, high_range, "x");
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
  
  RooRealVar* f = new RooRealVar("f","f",0.5);
  f->setConstant(false);

  //  RooRealVar* nEv = new RooRealVar("nEv","nEv",hist_data->GetEntries(),0.90*hist_data->GetEntries(),1.10*hist_data->GetEntries());
  //  std::cout<<"get entries = "<<hist_data->GetEntries()<<std::endl;
  //RooRealVar* nEv = new RooRealVar("nEv","nEv",hist_data->GetEntries(),0.5*hist_data->GetEntries(),1.5*hist_data->GetEntries());
  RooRealVar* nEv = new RooRealVar("nEv","nEv",hist_data->GetEntries());
  nEv->setConstant(false);

  RooRealVar* nTt = new RooRealVar("nTt","nTt",0.9*hist_data->GetEntries());
  nTt->setConstant(false);
  
  RooRealVar* nBkg = new RooRealVar("nBkg","nBkg",0.1*hist_data->GetEntries());
  nBkg->setConstant(false);

  RooRealVar* W = new RooRealVar("W","W",0.10);//,0.09,0.11);
  W->setConstant(false);

  //RooFormulaVar* W = new RooFormulaVar("W","nBkg/nEv*nTot",RooArgList(*nBkg,*nEv,*nTot));//,0.09,0.11);
  //  W->setConstant(false);

  /*  
  RooFormulaVar* nCor = new RooFormulaVar("nCor","nEv*f*(1-W)",RooArgList(*nEv,*f,*W));
  RooFormulaVar* nUnCor = new RooFormulaVar("nUnCor","nEv*(1-f)*(1-W)",RooArgList(*nEv,*f,*W));
  */

  RooFormulaVar* nCor = new RooFormulaVar("nCor","(nTt+nBkg)*nTt*f/(nTt+nBkg)",RooArgList(*nTt,*f,*nBkg));
  RooFormulaVar* nUnCor = new RooFormulaVar("nUnCor","(nTt+nBkg)*nTt*(1-f)/(nTt+nBkg)",RooArgList(*nTt,*f,*nBkg));


  //RooRealVar* nCor = new RooRealVar("nCor",0.5*hist_data->GetEntries());
  //nCor->setConstant(false);
  //RooRealVar* nUnCor = new RooRealVar("nUnCor",0.5*hist_data->GetEntries());
  //nUnCor->setConstant(false);

  //  RooFormulaVar* nW = new RooFormulaVar("nW","W*nEv",RooArgList(*W,*nEv));

  RooFormulaVar* nW = new RooFormulaVar("nW","(nTt+nBkg)*nBkg/(nTt+nBkg)",RooArgList(*nTt,*nBkg));

  //  RooRealVar* nCor = new RooRealVar("nCor","nCor",0.5*hist_data->GetEntries());
  //nCor->setConstant(kFALSE);
  //RooRealVar* nUnCor = new RooRealVar("nUnCor","nUnCor",0.5*hist_data->GetEntries());
  //nUnCor->setConstant(kFALSE);
  //std::cout<<"nW = "<<0.10*hist_data->GetEntries()<<std::endl;
  //RooRealVar* nW  = new RooRealVar("nW","nW", 0.10*hist_data->GetEntries(),0.,hist_data->GetEntries());
  //RooRealVar* nW  = new RooRealVar("nW","nW", 0.10*hist_data->GetEntries());
  //nW->setConstant(false);

  //RooArgList yields(*d, *f);
  //RooArgList nSig(*nCor, *nUnCor);
  //RooAddPdf Sig("Sig","sum pdf", *Signal, nSig, kTRUE);
  //  RooArgList yields(*nW, *nCor, *nUnCor);
  RooArgList yields(*nW, *nCor, *nUnCor);//nW
  RooAddPdf pdfPass("pdfPass","sum pdf", *Sum, yields, kFALSE);//kFALSE = not recursive
  
  RooFitResult *fitResult = pdfPass.fitTo(*data,Minos(kTRUE),Save(),SumW2Error(kFALSE),Extended(kTRUE));
  if(verbose){
  TString cname = TString("fit");
  TCanvas* c = new TCanvas(cname,cname,500,500);                                                                                                       
  RooPlot* frame1 = IndL.frame();                                                                                                                      
  frame1->SetMinimum(0);                                                                                                                               
  RooAbsData::ErrorType errorType = RooAbsData::SumW2;                                                                                                 
  data->plotOn(frame1,RooFit::DataError(errorType));                                                                                                   
  pdfPass.plotOn(frame1,RooFit::ProjWData(*data),RooFit::Components(*Cor),RooFit::LineColor(kRed));                                                    
  pdfPass.plotOn(frame1,RooFit::ProjWData(*data),RooFit::Components(*UnCor),RooFit::LineColor(kGreen));                                                
  pdfPass.plotOn(frame1,RooFit::ProjWData(*data),RooFit::Components(*WJets),RooFit::LineColor(kOrange));                                               
  //  pdfPass.plotOn(frame1,RooFit::ProjWData(*data));                                                                                                     
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
  double N = nTt->getVal();
  results.push_back(N);
  double N_err = nTt->getError();
  //double N_err = 1;
  results.push_back(N_err);
  results.push_back(fitResult->covQual());
  results.push_back(fitResult->status());
  results.push_back(fitResult->edm());
  //  std::cout<<"f= "<<f->getVal()<<" + "<<f->getError()<<" nEv= "<<nEv->getVal()<<" + "<<nEv->getError()<<" nW = "<<W->getVal()<<" + "<<W->getError()<<std::endl;
  //  std::cout<<"cor f,N= "<<(fitResult->correlationMatrix())[1][2]<<" cor f, W= "<<(fitResult->correlationMatrix())[0][1]<<" cor W,N = "<<(fitResult->correlationMatrix())[0][2]<<std::endl;
  double cov = (fitResult->correlationMatrix())[0][2];
  results.push_back(cov);
  results.push_back(nBkg->getVal());
  results.push_back(nBkg->getError());
  results.push_back((fitResult->correlationMatrix())[0][1]);
  results.push_back((fitResult->correlationMatrix())[1][2]);
  return results;
}
