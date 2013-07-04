#include "TreeProcessor.h"

comhaireamh::TreeProcessor::TreeProcessor()
{
  //  this->outfile = outfile;
}

comhaireamh::TreeProcessor::~TreeProcessor()
{
}

// main function, process all events for tree
void comhaireamh::TreeProcessor::read()
{
  // loop over all events ...
  int nevents = tree->GetEntries();
  int unmatched_counter = 0;
  int Mcutevents = 0;
  int Xcut = 0;
  int Mcut = 0;
  int XMcut = 0;
  //  tree->Print();

  for(int i = 0; i < nevents; i++){
    tree->GetEntry(i);

    TObjArray *leaves  = (TObjArray*)tree->GetListOfLeaves();
    TLeaf *evnr = (TLeaf*)leaves->UncheckedAt(56);
    TLeaf *chi2 = (TLeaf*)leaves->UncheckedAt(30);
    TLeaf *mt = (TLeaf*)leaves->UncheckedAt(32);
    TLeaf *prob = (TLeaf*)leaves->UncheckedAt(31);
    evnr = tree->GetLeaf("event_number");
    chi2 = tree->GetLeaf("Chi2");
    mt = tree->GetLeaf("MT");  
    prob = tree->GetLeaf("Prob");

    double chimin = 9999;
    int index = -1;
    //pick combination with lowest chi2
    for(int j = 0; j < 4; j++){
      //      std::cout<<"event= "<<i<<" combination= "<<j<<" chi2= "<<chi2->GetValue(j)<<" mt= "<<mt->GetValue(j)<<" prob= "<<prob->GetValue(j)<<std::endl;      
      if(chi2->GetValue(j) < chimin && chi2->GetValue(j) != -1){chimin = chi2->GetValue(j); index = j;}
      //   if(chi2->GetValue(j) <= chimin){std::cout<<"event= "<<i<<" combination= "<<j<<" chi2= "<<chi2->GetValue(j)<<" mt= "<<mt->GetValue(j)<<" prob= "<<prob->GetValue(j)<<std::endl;}

    }
    if(index == -1){unmatched_counter++; continue;}

    TLeaf *hadP_pt = (TLeaf*)leaves->UncheckedAt(2);
    hadP_pt = tree->GetLeaf("HadP_pt");
    TLeaf *hadP_eta = (TLeaf*)leaves->UncheckedAt(3);
    hadP_eta = tree->GetLeaf("HadP_eta");
    TLeaf *hadP_phi = (TLeaf*)leaves->UncheckedAt(4);
    hadP_phi = tree->GetLeaf("HadP_phi");
    TLeaf *hadP_m = (TLeaf*)leaves->UncheckedAt(5);
    hadP_m = tree->GetLeaf("HadP_m");
    TLeaf *hadB_pt = (TLeaf*)leaves->UncheckedAt(6);
    hadB_pt = tree->GetLeaf("HadB_pt");
    TLeaf *hadB_eta = (TLeaf*)leaves->UncheckedAt(7);
    hadB_eta = tree->GetLeaf("HadB_eta");
    TLeaf *hadB_phi = (TLeaf*)leaves->UncheckedAt(8);
    hadB_phi = tree->GetLeaf("HadB_phi");
    TLeaf *hadB_m = (TLeaf*)leaves->UncheckedAt(9);
    hadB_m = tree->GetLeaf("HadB_m");
    TLeaf *hadQ_pt =(TLeaf*)leaves->UncheckedAt(10);
    hadQ_pt = tree->GetLeaf("HadQ_pt");
    TLeaf *hadQ_eta =(TLeaf*)leaves->UncheckedAt(11);
    hadQ_eta = tree->GetLeaf("HadQ_eta");
    TLeaf *hadQ_phi =(TLeaf*)leaves->UncheckedAt(12);
    hadQ_phi = tree->GetLeaf("HadQ_phi");
    TLeaf *hadQ_m =(TLeaf*)leaves->UncheckedAt(13);
    hadQ_m = tree->GetLeaf("HadQ_m");
    TLeaf *lepB_pt =(TLeaf*)leaves->UncheckedAt(14);
    lepB_pt = tree->GetLeaf("LepB_pt");
    TLeaf *lepB_eta =(TLeaf*)leaves->UncheckedAt(15);
    lepB_eta = tree->GetLeaf("LepB_eta");
    TLeaf *lepB_phi =(TLeaf*)leaves->UncheckedAt(16);
    lepB_phi = tree->GetLeaf("LepB_phi");
    TLeaf *lepB_m =(TLeaf*)leaves->UncheckedAt(17);
    lepB_m = tree->GetLeaf("LepB_m");
    TLeaf *lepL_pt =(TLeaf*)leaves->UncheckedAt(18);
    lepL_pt = tree->GetLeaf("LepL_pt");
    TLeaf *lepL_eta =(TLeaf*)leaves->UncheckedAt(19);
    lepL_eta = tree->GetLeaf("LepL_eta");
    TLeaf *lepL_phi =(TLeaf*)leaves->UncheckedAt(20);
    lepL_phi = tree->GetLeaf("LepL_phi");
    TLeaf *lepL_m =(TLeaf*)leaves->UncheckedAt(21);
    lepL_m = tree->GetLeaf("LepL_m");
    TLeaf *lepN_pt =(TLeaf*)leaves->UncheckedAt(22);
    lepN_pt = tree->GetLeaf("LepN_pt");
    TLeaf *lepN_eta =(TLeaf*)leaves->UncheckedAt(23);
    lepN_eta = tree->GetLeaf("LepN_eta");
    TLeaf *lepN_phi =(TLeaf*)leaves->UncheckedAt(24);
    lepN_phi = tree->GetLeaf("LepN_phi");
    TLeaf *lepN_m =(TLeaf*)leaves->UncheckedAt(25);
    lepN_m = tree->GetLeaf("LepN_m");
    TLeaf *MC_hadB_pt = (TLeaf*)leaves->UncheckedAt(37);
    MC_hadB_pt = tree->GetLeaf("mc_HadB_pt");
    TLeaf *MC_hadB_eta = (TLeaf*)leaves->UncheckedAt(38);
    MC_hadB_eta = tree->GetLeaf("mc_HadB_eta");
    TLeaf *MC_hadB_phi = (TLeaf*)leaves->UncheckedAt(39);
    MC_hadB_phi = tree->GetLeaf("mc_HadB_phi");
    TLeaf *MC_hadQ_pt =(TLeaf*)leaves->UncheckedAt(43);
    MC_hadQ_pt = tree->GetLeaf("mc_Q_pt");
    TLeaf *MC_hadQ_eta =(TLeaf*)leaves->UncheckedAt(44);
    MC_hadQ_eta = tree->GetLeaf("mc_Q_eta");
    TLeaf *MC_hadQ_phi =(TLeaf*)leaves->UncheckedAt(45);
    MC_hadQ_phi = tree->GetLeaf("mc_Q_phi");
    TLeaf *MC_hadP_pt =(TLeaf*)leaves->UncheckedAt(46);
    MC_hadP_pt = tree->GetLeaf("mc_QBar_pt");
    TLeaf *MC_hadP_eta =(TLeaf*)leaves->UncheckedAt(47);
    MC_hadP_eta = tree->GetLeaf("mc_QBar_eta");
    TLeaf *MC_hadP_phi =(TLeaf*)leaves->UncheckedAt(48);
    MC_hadP_phi = tree->GetLeaf("mc_QBar_phi");
    TLeaf *MC_lepL_charge =(TLeaf*)leaves->UncheckedAt(49);
    MC_lepL_charge = tree->GetLeaf("mc_LepL_charge");
    TLeaf *MC_lepL_pt =(TLeaf*)leaves->UncheckedAt(50);
    MC_lepL_pt = tree->GetLeaf("mc_LepL_pt");
    TLeaf *MC_lepL_eta =(TLeaf*)leaves->UncheckedAt(51);
    MC_lepL_eta = tree->GetLeaf("mc_LepL_eta");
    TLeaf *MC_lepL_phi =(TLeaf*)leaves->UncheckedAt(52);
    MC_lepL_phi = tree->GetLeaf("mc_LepL_phi");
    TLeaf *MC_lepB_pt =(TLeaf*)leaves->UncheckedAt(40);
    MC_lepB_pt = tree->GetLeaf("mc_LepB_pt");
    TLeaf *MC_lepB_eta =(TLeaf*)leaves->UncheckedAt(41);
    MC_lepB_eta = tree->GetLeaf("mc_LepB_eta");
    TLeaf *MC_lepB_phi =(TLeaf*)leaves->UncheckedAt(42);
    MC_lepB_phi = tree->GetLeaf("mc_LepB_phi");
    TLeaf *MC_lepN_pt =(TLeaf*)leaves->UncheckedAt(53);
    MC_lepN_pt = tree->GetLeaf("mc_LepN_pt");
    TLeaf *MC_lepN_eta =(TLeaf*)leaves->UncheckedAt(54);
    MC_lepN_eta = tree->GetLeaf("mc_LepN_eta");
    TLeaf *MC_lepN_phi =(TLeaf*)leaves->UncheckedAt(55);
    MC_lepN_phi = tree->GetLeaf("mc_LepN_phi");
    
    
    bool matching[4][4];
    //0 = hadP, 1 = hadB, 2 = lepB, 3 = hadQ
    //correct combination leads to diagonal
    matching[0][0] = Match(hadP_phi->GetValue(index),    hadP_eta->GetValue(index),MC_hadP_phi->GetValue(0),    MC_hadP_eta->GetValue(0), dR_cor );
    matching[0][1] = Match(hadP_phi->GetValue(index),    hadP_eta->GetValue(index),MC_hadB_phi->GetValue(0),    MC_hadB_eta->GetValue(0), dR_wrong);
    matching[0][2] = Match(hadP_phi->GetValue(index),    hadP_eta->GetValue(index),MC_lepB_phi->GetValue(0),    MC_lepB_eta->GetValue(0), dR_wrong);
    matching[0][3] = Match(hadP_phi->GetValue(index),    hadP_eta->GetValue(index),MC_hadQ_phi->GetValue(0),    MC_hadQ_eta->GetValue(0), dR_wrong);
    matching[1][0] = Match(hadB_phi->GetValue(index),    hadB_eta->GetValue(index),MC_hadP_phi->GetValue(0),    MC_hadP_eta->GetValue(0), dR_wrong);
    matching[1][1] = Match(hadB_phi->GetValue(index),    hadB_eta->GetValue(index),MC_hadB_phi->GetValue(0),    MC_hadB_eta->GetValue(0), dR_cor);
    matching[1][2] = Match(hadB_phi->GetValue(index),    hadB_eta->GetValue(index),MC_lepB_phi->GetValue(0),    MC_lepB_eta->GetValue(0), dR_wrong);
    matching[1][3] = Match(hadB_phi->GetValue(index),    hadB_eta->GetValue(index),MC_hadQ_phi->GetValue(0),    MC_hadQ_eta->GetValue(0), dR_wrong);
    matching[2][0] = Match(lepB_phi->GetValue(index),    lepB_eta->GetValue(index),MC_hadP_phi->GetValue(0),    MC_hadP_eta->GetValue(0), dR_wrong);
    matching[2][1] = Match(lepB_phi->GetValue(index),    lepB_eta->GetValue(index),MC_hadB_phi->GetValue(0),    MC_hadB_eta->GetValue(0), dR_wrong);
    matching[2][2] = Match(lepB_phi->GetValue(index),    lepB_eta->GetValue(index),MC_lepB_phi->GetValue(0),    MC_lepB_eta->GetValue(0), dR_cor);
    matching[2][3] = Match(lepB_phi->GetValue(index),    lepB_eta->GetValue(index),MC_hadQ_phi->GetValue(0),    MC_hadQ_eta->GetValue(0), dR_wrong);
    matching[3][0] = Match(hadQ_phi->GetValue(index),    hadQ_eta->GetValue(index),MC_hadP_phi->GetValue(0),    MC_hadP_eta->GetValue(0), dR_wrong);
    matching[3][1] = Match(hadQ_phi->GetValue(index),    hadQ_eta->GetValue(index),MC_hadB_phi->GetValue(0),    MC_hadB_eta->GetValue(0), dR_wrong);
    matching[3][2] = Match(hadQ_phi->GetValue(index),    hadQ_eta->GetValue(index),MC_lepB_phi->GetValue(0),    MC_lepB_eta->GetValue(0), dR_wrong);
    matching[3][3] = Match(hadQ_phi->GetValue(index),    hadQ_eta->GetValue(index),MC_hadQ_phi->GetValue(0),    MC_hadQ_eta->GetValue(0), dR_cor);

    int combination_index = -1;
    //check correct combination
    if(matching[0][0] && matching[1][1] && matching[2][2] && matching[3][3]){
      //correct combination
      combination_index = 0;
    }
    else if(matching[0][3] && matching[1][1] && matching[2][2] && matching[3][0])
      {
        //light quarks are swapped, which still is correct
        combination_index = 0;
      }
    else if(matching[0][0] && matching[1][2] && matching[2][1] && matching[3][3])
      {
        //b quarks are swapped
        combination_index = 1;
      }
    else if(matching[1][1] && ((matching[2][0] && matching[3][3]) || (matching[2][3] && matching[0][0])))
      {
        //bl_q_swapped
        combination_index = 2;
      }
    else if(matching[2][2] && ((matching[1][0] && matching[3][3]) || (matching[1][3] && matching[0][0])))
      {
        //bh_q_swapped
        combination_index = 3;
      }
    else if(!matching[0][0] && !matching[1][1] && !matching[2][2] && !matching[3][3]){
      //all four are matched wrong
      //want wrong to be the last
      combination_index = 5;
    }
    else{
      //by default only events with three swapped quarks are left
      combination_index = 4;
    }
    
    FILE *RightPerm;
    RightPerm = fopen("Permutation.txt","w");
    if(combination_index == 0){
      fprintf(RightPerm,"%d\t%i\n",evnr->GetValue(index),1); //right permutation
      std::cout<<"fill"<<std::endl;
    }
    else{
      fprintf(RightPerm,"%d\t%i\n",evnr->GetValue(index),0); //wrong permutation
      std::cout<<"fill wrong"<<std::endl;
    }
    fclose(RightPerm);

    TLorentzVector *h_B = new TLorentzVector();
    h_B->SetPtEtaPhiM(hadB_pt->GetValue(index),hadB_eta->GetValue(index), hadB_phi->GetValue(index), hadB_m->GetValue(index));
    TLorentzVector *l_B = new TLorentzVector();
    l_B->SetPtEtaPhiM(lepB_pt->GetValue(index),lepB_eta->GetValue(index), lepB_phi->GetValue(index), lepB_m->GetValue(index));
  TLorentzVector *Q = new TLorentzVector();
  Q->SetPtEtaPhiM(hadQ_pt->GetValue(index),hadQ_eta->GetValue(index), hadQ_phi->GetValue(index), hadQ_m->GetValue(index));
  TLorentzVector *QB = new TLorentzVector();
  QB->SetPtEtaPhiM(hadP_pt->GetValue(index),hadP_eta->GetValue(index), hadP_phi->GetValue(index), hadP_m->GetValue(index));
  TLorentzVector *lep = new TLorentzVector();
  lep->SetPtEtaPhiM(lepL_pt->GetValue(index),lepL_eta->GetValue(index), lepL_phi->GetValue(index), lepL_m->GetValue(index));
  TLorentzVector *n = new TLorentzVector();
  n->SetPtEtaPhiM(lepN_pt->GetValue(index),lepN_eta->GetValue(index), lepN_phi->GetValue(index), lepN_m->GetValue(index));

  TLorentzVector Whad = *Q + *QB;
  TLorentzVector Wlep = *lep + *n;
  TLorentzVector top;
  TLorentzVector antitop;

  if(MC_lepL_charge->GetValue(0) > 0){
    top = Wlep + *l_B;
    antitop = Whad + *h_B;
  }
  else{
    top = Whad + *h_B;
    antitop = Wlep + *l_B;
  }


  //fill the topmass in the corresponding combination histogram
  TopMass[combination_index]->Fill(mt->GetValue(index));
  //    if(mt->GetValue(index) <= 225 && mt->GetValue(index) >= 150){
  Chi[combination_index]->Fill(chi2->GetValue(index));
  Prob[combination_index]->Fill(prob->GetValue(index));
  TopMassKelly[combination_index]->Fill(top.M());
  WMass[combination_index]->Fill(Whad.M());
  Mcutevents++;
  //    }
  if(chi2->GetValue(index) > 20){Xcut++;}
  if(mt->GetValue(index) > 250 || mt->GetValue(index) < 150){Mcut++;}
  if(mt->GetValue(index) > 250 || mt->GetValue(index) < 150 || chi2->GetValue(index) > 20){XMcut++;}
  }
  std::cout<<"fit efficiency= "<<(double) (nevents - unmatched_counter)/nevents<<std::endl;
  std::cout<<"purity= "<<Chi[0]->Integral()/(Mcutevents)<<std::endl;
  std::cout<<"cut out by Chi2 cut= "<<(double) Xcut/(Mcutevents)<<std::endl;
  std::cout<<"cut out by Mass cut= "<<(double) Mcut/(Mcutevents)<<std::endl;
  std::cout<<"cut out by Chi2 + Mass cut= "<<(double) XMcut/(Mcutevents)<<std::endl;
}

bool comhaireamh::TreeProcessor::Match(double J_phi, double J_eta, double MC_phi, double MC_eta, TH1F *dr){
  double dR = sqrt((J_phi - MC_phi)*(J_phi - MC_phi)+(J_eta - MC_eta)*(J_eta - MC_eta));
  dr->Fill(dR);
  bool matched = false;
  if(dR < 0.15){matched = true;}
  return matched;
}

void comhaireamh::TreeProcessor::process(){
  std::cout<<"Getting trees....\n";
  get_trees_from_files();
  std::cout<<"Configuring Trees...\n";
  // configure_trees();
  std::cout<<"Processing Trees.... \n";
  // process_trees();
  bookHistos();
  read();
  std::cout<<"Making plots....\n";
  create_plots();
}

void comhaireamh::TreeProcessor::bookHistos(){
  TopMass[0] = new TH1F("correct","Top mass",100,100,450);
  TopMass[1] = new TH1F("b_swapped","Top mass",100,100,450);
  TopMass[2] = new TH1F("bl_q_swapped","Top mass",100,100,450);
  TopMass[3] = new TH1F("bh_q_swapped","Top mass",100,100,450);
  TopMass[4] = new TH1F("three_swapped","Top mass",100,100,450);
  TopMass[5] = new TH1F("four_swapped","Top mass",100,100,450);
  WMass[0] = new TH1F("Wcorrect","W mass",100,0,200);
  WMass[1] = new TH1F("Wb_swapped","W mass",100,0,200);
  WMass[2] = new TH1F("Wbl_q_swapped","W mass",100,0,200);
  WMass[3] = new TH1F("Wbh_q_swapped","W mass",100,0,200);
  WMass[4] = new TH1F("Wthree_swapped","W mass",100,0,200);
  WMass[5] = new TH1F("Wfour_swapped","W mass",100,0,200);
  TopMassKelly[0] = new TH1F("Kcorrect","Top mass",100,100,450);
  TopMassKelly[1] = new TH1F("Kb_swapped","Top mass",100,100,450);
  TopMassKelly[2] = new TH1F("Kbl_q_swapped","Top mass",100,100,450);
  TopMassKelly[3] = new TH1F("Kbh_q_swapped","Top mass",100,100,450);
  TopMassKelly[4] = new TH1F("Kthree_swapped","Top mass",100,100,450);
  TopMassKelly[5] = new TH1F("Kfour_swapped","Top mass",100,100,450);
  Chi[0] = new TH1F("Chi_correct","Chi2",100,0,200);
  Chi[1] = new TH1F("Chi_b_swapped","Chi2",100,0,200);
  Chi[2] = new TH1F("Chi_bl_q_swapped","Chi2",100,0,200);
  Chi[3] = new TH1F("Chi_bh_q_swapped","Chi2",100,0,200);
  Chi[4] = new TH1F("Chi_three_swapped","Chi2",100,0,200);
  Chi[5] = new TH1F("Chi_four_swapped","Chi2",100,0,200);
  Prob[0] = new TH1F("Prob_correct","Prob",100,0,1);
  Prob[1] = new TH1F("Prob_b_swapped","Prob",100,0,1);
  Prob[2] = new TH1F("Prob_bl_q_swapped","Prob",100,0,1);
  Prob[3] = new TH1F("Prob_bh_q_swapped","Prob",100,0,1);
  Prob[4] = new TH1F("Prob_three_swapped","Prob",100,0,1);
  Prob[5] = new TH1F("Prob_four_swapped","Prob",100,0,1);
  dR_cor = new TH1F("dR_cor","dR for correct match", 50, 0, 1);
  dR_wrong = new TH1F("dR_wrong","dR for wrong match", 50, 0, 1);
}

void comhaireamh::TreeProcessor::create_plots(){

  TLegend *leg = new TLegend(0.6, 0.7, 0.89,0.89);
  leg->SetFillColor(0);
  leg->AddEntry(TopMass[0],"correct");
  leg->AddEntry(TopMass[1],"b swapped");
  leg->AddEntry(TopMass[2],"bl - q swapped");
  leg->AddEntry(TopMass[3],"bh - q swapped");
  leg->AddEntry(TopMass[4],"three swapped");
  leg->AddEntry(TopMass[5],"four swapped");

  THStack *Mass = new THStack("Mass","Top Mass of the selected HitFit combination");
  TopMass[0]->SetFillColor(kRed);
  TopMass[1]->SetFillColor(kOrange);
  TopMass[2]->SetFillColor(kYellow);
  TopMass[3]->SetFillColor(kGreen);
  TopMass[4]->SetFillColor(kBlue);
  TopMass[5]->SetFillColor(kBlue+10);
  for(int i = 5; i >= 0; i--)
    {
      Mass->Add(TopMass[i]);
    }

  TCanvas *c1 = new TCanvas();
  c1->cd();
  gStyle->SetOptStat(111);
  Mass->Draw();
  leg->Draw();
  c1->Modified();
  c1->Update();
  c1->SaveAs("TopMass.C");
  delete c1;
  THStack *KellyMass = new THStack("KellyMass","Top Mass of the selected HitFit combination");
  TopMassKelly[0]->SetFillColor(kRed);
  TopMassKelly[1]->SetFillColor(kOrange);
  TopMassKelly[2]->SetFillColor(kYellow);
  TopMassKelly[3]->SetFillColor(kGreen);
  TopMassKelly[4]->SetFillColor(kBlue);
  TopMassKelly[5]->SetFillColor(kBlue+10);
  for(int i = 5; i >= 0; i--)
    {
      KellyMass->Add(TopMassKelly[i]);
    }

  TCanvas *c23 = new TCanvas();
  c23->cd();
  gStyle->SetOptStat(111);
  KellyMass->Draw();
  leg->Draw();
  c23->Modified();
  c23->Update();
  c23->SaveAs("KellyTopMass.C");
  delete c23;
  THStack *wMass = new THStack("wMass","Top Mass of the selected HitFit combination");
  WMass[0]->SetFillColor(kRed);
  WMass[1]->SetFillColor(kOrange);
  WMass[2]->SetFillColor(kYellow);
  WMass[3]->SetFillColor(kGreen);
  WMass[4]->SetFillColor(kBlue);
  WMass[5]->SetFillColor(kBlue+10);
  for(int i = 5; i >= 0; i--)
    {
      wMass->Add(WMass[i]);
    }

  TCanvas *c24 = new TCanvas();
  c24->cd();
  gStyle->SetOptStat(111);
  wMass->Draw();
  leg->Draw();
  c24->Modified();
  c24->Update();
  c24->SaveAs("WMass.C");
  delete c24;
  THStack *ChiStack = new THStack("ChiStack","Chi2 of the selected HitFit combination; Chi2; entries");
  Chi[0]->SetFillColor(kRed);
  Chi[1]->SetFillColor(kOrange);
  Chi[2]->SetFillColor(kYellow);
  Chi[3]->SetFillColor(kGreen);
  Chi[4]->SetFillColor(kBlue);
  Chi[5]->SetFillColor(kBlue+10);
  for(int i = 5; i >= 0; i--)
    {
      ChiStack->Add(Chi[i]);
    }

  TCanvas *c2 = new TCanvas();
  c2->cd();
  ChiStack->Draw();
  leg->Draw();
  c2->Modified();
  c2->Update();
  c2->SaveAs("Chi2.C");
  delete c2;
  THStack *ProbStack = new THStack("ProbStack","Prob of the selected HitFit combination");
  Prob[0]->SetFillColor(kRed);
  Prob[1]->SetFillColor(kOrange);
  Prob[2]->SetFillColor(kYellow);
  Prob[3]->SetFillColor(kGreen);
  Prob[4]->SetFillColor(kBlue);
  Prob[5]->SetFillColor(kBlue+10);
  for(int i = 5; i >= 0; i--)
    {
      ProbStack->Add(Prob[i]);
    }

  TCanvas *c5 = new TCanvas();
  c5->cd();
  ProbStack->Draw();
  leg->Draw();
  c5->Modified();
  c5->Update();
  c5->SaveAs("Prob.C");
  delete c5;
  TCanvas *c3 = new TCanvas();
  c3->cd();
  dR_cor->SetLineColor(kGreen);
  dR_wrong->SetLineColor(kRed);
  dR_cor->Draw();
  dR_wrong->Draw("sames");
  leg->Draw();
  c3->Modified();
  c3->Update();
  c3->SaveAs("dR.C");
  delete c3;
}

void comhaireamh::TreeProcessor::get_trees_from_files()
{
  std::vector<std::string> *sections = config_reader->get_sections();

  std::string filename_var = "file_name";
  std::string tree_name = config_reader->get_var("tree_name", "global", true);
  std::string dir_name = config_reader->get_var("dir_name", "global", true);

  // loop over all sections and make sure all root files are opened                                                                                                              
  for(std::vector<std::string>::iterator section = sections->begin();
      section != sections->end();
      ++section){
    if(*section != "global" && (section->find("scale_factor") == std::string::npos)){
      std::string filename = config_reader->get_var(filename_var, *section, true);
      
      // if this is a new tree, book a TreeProcessor                                                                                                                             
      TFile *infile = new TFile(filename.c_str(), "OPEN");
      //       comhaireamh::TreeProcessor *tree_reader = new comhaireamh::TreeProcessor(outfile);
      // tree_reader->set_tree((TTree*) infile->GetDirectory(dir_name.c_str())->Get(tree_name.c_str()));
     set_tree((TTree*) infile->GetDirectory(dir_name.c_str())->Get(tree_name.c_str()));
      //        tree_reader->set_config_reader(config_reader);
      set_config_reader(config_reader);
      
    }
  }
}
