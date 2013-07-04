#include "Linearity.h"

eire::Linearity::Linearity(string name)
{
  Name = name;
}

eire::Linearity::~Linearity()
{
}

void eire::Linearity::AddPoint(int index, double f_gen, double f_obs, double f_obs_err, double p_av, double p_averr, double p_rms, double p_rmserr)
{
  x[index] = f_gen;
  y[index] = f_obs;
  y_err[index] = f_obs_err;
  P_av[index] = p_av;
  P_averr[index] = p_averr;
  P_rms[index] = p_rms;
  P_rmserr[index] = p_rmserr;
}

void eire::Linearity::Plot()
{
  double f_d[5];
  f_d[0] = y[0] - x[0];
  f_d[1] = y[1] - x[1];
  f_d[2] = y[2] - x[2];
  f_d[3] = y[3] - x[3];
  f_d[4] = y[4] - x[4];

  TCanvas *c1 = new TCanvas("c1", "c1",0,0,600,500);
  c1->Range(0,0,1,1);
  TPad *c1_1 = new TPad("c1_1", "newpad",0.01,0.01,0.99,0.32);
  c1_1->Draw();
  c1_1->cd();
  c1_1->SetTopMargin(0.01);
  c1_1->SetBottomMargin(0.3);
  c1_1->SetRightMargin(0.1);
  c1_1->SetFillStyle(0);
  TH1F *h2 = c1->DrawFrame(-0.15,-0.1,1.15,0.1);
  h2->GetXaxis()->SetTitle("f_{input}");
  h2->GetXaxis()->SetTitleSize(0.08);
  h2->GetXaxis()->SetLabelSize(0.08);
  h2->GetYaxis()->SetTitle("f_{measured} - f_{input}");
  h2->GetYaxis()->SetTitleSize(0.08);
  h2->GetYaxis()->SetLabelSize(0.08);
  h2->GetYaxis()->SetTitleOffset(0.55);
  TLine *l = new TLine(-0.15,0,1.15,0);
  TGraphErrors *gr_d = new TGraphErrors(5,x,f_d,0,y_err);
  gr_d->SetMarkerStyle(8);
  gr_d->SetMarkerSize(0.7);
  gr_d->Draw("p");
  l->Draw();
  c1->cd();
  TPad *c1_2 = new TPad("c1_2", "newpad",0.01,0.33,0.99,0.99);
  c1_2->Draw();
  c1_2->cd();
  c1_2->SetTopMargin(0.1);
  c1_2->SetBottomMargin(0.01);
  c1_2->SetRightMargin(0.1);
  c1_2->SetFillStyle(0);

  TH1F *h1 = c1->DrawFrame(-0.15,-0.15,1.15,1.15);
  h1->GetXaxis()->SetTitle("f_{input}");
  h1->GetYaxis()->SetTitle("f_{measured}");
  h1->GetYaxis()->SetTitleOffset(0.8);
  h1->GetYaxis()->SetTitleSize(0.05);


  TF1 *ff1 = new TF1("ff1","[0]+[1]*x",0,1);
  TGraphErrors *gr = new TGraphErrors(5,x,y,0,y_err);
  gr->SetMarkerStyle(8);
  gr->SetMarkerSize(0.7);
  gr->SetTitle();
  gr->Draw("p");
  gr->Fit(ff1,"R");
  //  TFitResult *result = gr->Fit(ff1,"R").Get();
  //double cor_p0_p1 = (result->GetCorrelationMatrix())[0][1];
  //std::cout<<"correlation between p0 and p1 = "<<cor_p0_p1<<std::endl;
  c1->Modified();
  c1->Update();
  c1->SaveAs(("Linearity_"+Name+".C").c_str());
  c1->SaveAs(("Linearity_"+Name+".pdf").c_str());

  double a = ff1->GetParameter(1);
  double a_err = ff1->GetParError(1);
  double b = ff1->GetParameter(0);
  double b_err = ff1->GetParError(0);

  if((a+3*a_err) < 1 || (a-3*a_err) > 1){std::cout<<"%%%%%%%% WARNING!  slope of Linearity curve is biased!"<<std::endl;}
  if((b+3*b_err) < 0 || (b-3*b_err) > 0){std::cout<<"%%%%%%%% WARNING!  offset of Linearity curve is biased!"<<std::endl;}

  TCanvas *c2 = new TCanvas();
  c2->Divide(2,1);
  c2->cd(1);
  TH1F *h3 = c1->DrawFrame(-0.15,-0.15,1.15,0.15);
  h3->GetXaxis()->SetTitle("f_{input}");
  h3->GetXaxis()->SetTitleSize(0.05);
  h3->GetYaxis()->SetTitle("Pull mean");
  h3->GetYaxis()->SetTitleOffset(1.5);
  
  TGraphErrors *PAv = new TGraphErrors(5,x,P_av,0,P_averr);
  PAv->SetMarkerStyle(8);
  PAv->SetMarkerSize(0.7);
  PAv->SetTitle();
  PAv->Draw("p");
  TLine *l2 = new TLine(0,0,1,0);
  l2->Draw("same");
  c2->Modified();
  c2->Update();
  c2->cd();
  c2->cd(2);
  TH1F *h4 = c1->DrawFrame(-0.15,0.9,1.15,1.1);
  h4->GetXaxis()->SetTitle("f_{input}");
  h4->GetXaxis()->SetTitleSize(0.05);
  h4->GetYaxis()->SetTitle("Pull RMS");
  h4->GetYaxis()->SetTitleOffset(1.5);
  TGraphErrors *PRMS = new TGraphErrors(5,x,P_rms,0,P_rmserr);
  TF1 *P1 = new TF1("P1","[0]",0,1);
  PRMS->SetMarkerStyle(8);
  PRMS->SetMarkerSize(0.7);
  PRMS->SetTitle();
  PRMS->Draw("p");
  //  PRMS->Fit(P1,"R");
  //std::cout<<"error correction factor = "<<P1->GetParameter(0)<<" +- "<<P1->GetParError(0)<<std::endl;
  TLine *l3 = new TLine(0,1,1,1);
  l3->Draw("same");
  c2->Modified();
  c2->Update();
  c2->SaveAs(("PullLins_"+Name+".C").c_str());
  c2->SaveAs(("PullLins_"+Name+".pdf").c_str());
}

