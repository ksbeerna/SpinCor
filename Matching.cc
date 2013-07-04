#include "Matching.h"

//Pseudo-Experiment Builder
eire::Matching::Matching(TTree *tree)
{
  HitFitTree = tree;
}

eire::Matching::~Matching()
{
}

map<int,bool> eire::Matching::CheckPermutations()
{
  map<int,bool> Permutations;

  int nevents = HitFitTree->GetEntries();

  for(int i = 0; i < nevents; i++){
    HitFitTree->GetEntry(i);
    
    TObjArray *leaves  = (TObjArray*)HitFitTree->GetListOfLeaves();
    TLeaf *evnr = (TLeaf*)leaves->UncheckedAt(56);
    TLeaf *chi2 = (TLeaf*)leaves->UncheckedAt(30);
    TLeaf *mt = (TLeaf*)leaves->UncheckedAt(32);
    TLeaf *prob = (TLeaf*)leaves->UncheckedAt(31);
    evnr = HitFitTree->GetLeaf("event_number");
    chi2 = HitFitTree->GetLeaf("Chi2");
    mt = HitFitTree->GetLeaf("MT");
    prob = HitFitTree->GetLeaf("Prob");
    
    double chimin = 9999;
    int index = -1;
    //pick combination with lowest chi2                                                                                                                      
    for(int j = 0; j < 4; j++){
      if(chi2->GetValue(j) < chimin && chi2->GetValue(j) != -1){chimin = chi2->GetValue(j); index = j;}
    }
    //    if(index == -1){unmatched_counter++; continue;}
    
    TLeaf *hadP_pt = (TLeaf*)leaves->UncheckedAt(2);
    hadP_pt = HitFitTree->GetLeaf("HadP_pt");
    TLeaf *hadP_eta = (TLeaf*)leaves->UncheckedAt(3);
    hadP_eta = HitFitTree->GetLeaf("HadP_eta");
    TLeaf *hadP_phi = (TLeaf*)leaves->UncheckedAt(4);
    hadP_phi = HitFitTree->GetLeaf("HadP_phi");
    TLeaf *hadP_m = (TLeaf*)leaves->UncheckedAt(5);
    hadP_m = HitFitTree->GetLeaf("HadP_m");
    TLeaf *hadB_pt = (TLeaf*)leaves->UncheckedAt(6);
    hadB_pt = HitFitTree->GetLeaf("HadB_pt");
    TLeaf *hadB_eta = (TLeaf*)leaves->UncheckedAt(7);
    hadB_eta = HitFitTree->GetLeaf("HadB_eta");
    TLeaf *hadB_phi = (TLeaf*)leaves->UncheckedAt(8);
    hadB_phi = HitFitTree->GetLeaf("HadB_phi");
    TLeaf *hadB_m = (TLeaf*)leaves->UncheckedAt(9);
    hadB_m = HitFitTree->GetLeaf("HadB_m");
    TLeaf *hadQ_pt =(TLeaf*)leaves->UncheckedAt(10);
    hadQ_pt = HitFitTree->GetLeaf("HadQ_pt");
    TLeaf *hadQ_eta =(TLeaf*)leaves->UncheckedAt(11);
    hadQ_eta = HitFitTree->GetLeaf("HadQ_eta");
    TLeaf *hadQ_phi =(TLeaf*)leaves->UncheckedAt(12);
    hadQ_phi = HitFitTree->GetLeaf("HadQ_phi");
    TLeaf *hadQ_m =(TLeaf*)leaves->UncheckedAt(13);
    hadQ_m = HitFitTree->GetLeaf("HadQ_m");
    TLeaf *lepB_pt =(TLeaf*)leaves->UncheckedAt(14);
    lepB_pt = HitFitTree->GetLeaf("LepB_pt");
    TLeaf *lepB_eta =(TLeaf*)leaves->UncheckedAt(15);
    lepB_eta = HitFitTree->GetLeaf("LepB_eta");
    TLeaf *lepB_phi =(TLeaf*)leaves->UncheckedAt(16);
    lepB_phi = HitFitTree->GetLeaf("LepB_phi");
    TLeaf *lepB_m =(TLeaf*)leaves->UncheckedAt(17);
    lepB_m = HitFitTree->GetLeaf("LepB_m");
    TLeaf *lepL_pt =(TLeaf*)leaves->UncheckedAt(18);
    lepL_pt = HitFitTree->GetLeaf("LepL_pt");
    TLeaf *lepL_eta =(TLeaf*)leaves->UncheckedAt(19);
    lepL_eta = HitFitTree->GetLeaf("LepL_eta");
    TLeaf *lepL_phi =(TLeaf*)leaves->UncheckedAt(20);
    lepL_phi = HitFitTree->GetLeaf("LepL_phi");
    TLeaf *lepL_m =(TLeaf*)leaves->UncheckedAt(21);
    lepL_m = HitFitTree->GetLeaf("LepL_m");
    TLeaf *lepN_pt =(TLeaf*)leaves->UncheckedAt(22);
    lepN_pt = HitFitTree->GetLeaf("LepN_pt");
    TLeaf *lepN_eta =(TLeaf*)leaves->UncheckedAt(23);
    lepN_eta = HitFitTree->GetLeaf("LepN_eta");
    TLeaf *lepN_phi =(TLeaf*)leaves->UncheckedAt(24);
    lepN_phi = HitFitTree->GetLeaf("LepN_phi");
    TLeaf *lepN_m =(TLeaf*)leaves->UncheckedAt(25);
    lepN_m = HitFitTree->GetLeaf("LepN_m");
    TLeaf *MC_hadB_pt = (TLeaf*)leaves->UncheckedAt(37);
    MC_hadB_pt = HitFitTree->GetLeaf("mc_HadB_pt");
    TLeaf *MC_hadB_eta = (TLeaf*)leaves->UncheckedAt(38);
    MC_hadB_eta = HitFitTree->GetLeaf("mc_HadB_eta");
    TLeaf *MC_hadB_phi = (TLeaf*)leaves->UncheckedAt(39);
    MC_hadB_phi = HitFitTree->GetLeaf("mc_HadB_phi");
    TLeaf *MC_hadQ_pt =(TLeaf*)leaves->UncheckedAt(43);
    MC_hadQ_pt = HitFitTree->GetLeaf("mc_Q_pt");
    TLeaf *MC_hadQ_eta =(TLeaf*)leaves->UncheckedAt(44);
    MC_hadQ_eta = HitFitTree->GetLeaf("mc_Q_eta");
    TLeaf *MC_hadQ_phi =(TLeaf*)leaves->UncheckedAt(45);
    MC_hadQ_phi = HitFitTree->GetLeaf("mc_Q_phi");
    TLeaf *MC_hadP_pt =(TLeaf*)leaves->UncheckedAt(46);
    MC_hadP_pt = HitFitTree->GetLeaf("mc_QBar_pt");
    TLeaf *MC_hadP_eta =(TLeaf*)leaves->UncheckedAt(47);
    MC_hadP_eta = HitFitTree->GetLeaf("mc_QBar_eta");
    TLeaf *MC_hadP_phi =(TLeaf*)leaves->UncheckedAt(48);
    MC_hadP_phi = HitFitTree->GetLeaf("mc_QBar_phi");
    TLeaf *MC_lepL_charge =(TLeaf*)leaves->UncheckedAt(49);
    MC_lepL_charge = HitFitTree->GetLeaf("mc_LepL_charge");
    TLeaf *MC_lepL_pt =(TLeaf*)leaves->UncheckedAt(50);
    MC_lepL_pt = HitFitTree->GetLeaf("mc_LepL_pt");
    TLeaf *MC_lepL_eta =(TLeaf*)leaves->UncheckedAt(51);
    MC_lepL_eta = HitFitTree->GetLeaf("mc_LepL_eta");
    TLeaf *MC_lepL_phi =(TLeaf*)leaves->UncheckedAt(52);
    MC_lepL_phi = HitFitTree->GetLeaf("mc_LepL_phi");
    TLeaf *MC_lepB_pt =(TLeaf*)leaves->UncheckedAt(40);
    MC_lepB_pt = HitFitTree->GetLeaf("mc_LepB_pt");
    TLeaf *MC_lepB_eta =(TLeaf*)leaves->UncheckedAt(41);
    MC_lepB_eta = HitFitTree->GetLeaf("mc_LepB_eta");
    TLeaf *MC_lepB_phi =(TLeaf*)leaves->UncheckedAt(42);
    MC_lepB_phi = HitFitTree->GetLeaf("mc_LepB_phi");
    TLeaf *MC_lepN_pt =(TLeaf*)leaves->UncheckedAt(53);
    MC_lepN_pt = HitFitTree->GetLeaf("mc_LepN_pt");
    TLeaf *MC_lepN_eta =(TLeaf*)leaves->UncheckedAt(54);
    MC_lepN_eta = HitFitTree->GetLeaf("mc_LepN_eta");
    TLeaf *MC_lepN_phi =(TLeaf*)leaves->UncheckedAt(55);
    MC_lepN_phi = HitFitTree->GetLeaf("mc_LepN_phi");
    
    bool matching[4][4];
    //0 = hadP, 1 = hadB, 2 = lepB, 3 = hadQ                                                                                                               
    //correct combination leads to diagonal                                                                                                                
    matching[0][0] = Match(hadP_phi->GetValue(index),    hadP_eta->GetValue(index),MC_hadP_phi->GetValue(0),    MC_hadP_eta->GetValue(0));
    matching[0][1] = Match(hadP_phi->GetValue(index),    hadP_eta->GetValue(index),MC_hadB_phi->GetValue(0),    MC_hadB_eta->GetValue(0));
    matching[0][2] = Match(hadP_phi->GetValue(index),    hadP_eta->GetValue(index),MC_lepB_phi->GetValue(0),    MC_lepB_eta->GetValue(0));
    matching[0][3] = Match(hadP_phi->GetValue(index),    hadP_eta->GetValue(index),MC_hadQ_phi->GetValue(0),    MC_hadQ_eta->GetValue(0));
    matching[1][0] = Match(hadB_phi->GetValue(index),    hadB_eta->GetValue(index),MC_hadP_phi->GetValue(0),    MC_hadP_eta->GetValue(0));
    matching[1][1] = Match(hadB_phi->GetValue(index),    hadB_eta->GetValue(index),MC_hadB_phi->GetValue(0),    MC_hadB_eta->GetValue(0));
    matching[1][2] = Match(hadB_phi->GetValue(index),    hadB_eta->GetValue(index),MC_lepB_phi->GetValue(0),    MC_lepB_eta->GetValue(0));
    matching[1][3] = Match(hadB_phi->GetValue(index),    hadB_eta->GetValue(index),MC_hadQ_phi->GetValue(0),    MC_hadQ_eta->GetValue(0));
    matching[2][0] = Match(lepB_phi->GetValue(index),    lepB_eta->GetValue(index),MC_hadP_phi->GetValue(0),    MC_hadP_eta->GetValue(0));
    matching[2][1] = Match(lepB_phi->GetValue(index),    lepB_eta->GetValue(index),MC_hadB_phi->GetValue(0),    MC_hadB_eta->GetValue(0));
    matching[2][2] = Match(lepB_phi->GetValue(index),    lepB_eta->GetValue(index),MC_lepB_phi->GetValue(0),    MC_lepB_eta->GetValue(0));
    matching[2][3] = Match(lepB_phi->GetValue(index),    lepB_eta->GetValue(index),MC_hadQ_phi->GetValue(0),    MC_hadQ_eta->GetValue(0));
    matching[3][0] = Match(hadQ_phi->GetValue(index),    hadQ_eta->GetValue(index),MC_hadP_phi->GetValue(0),    MC_hadP_eta->GetValue(0));
    matching[3][1] = Match(hadQ_phi->GetValue(index),    hadQ_eta->GetValue(index),MC_hadB_phi->GetValue(0),    MC_hadB_eta->GetValue(0));
    matching[3][2] = Match(hadQ_phi->GetValue(index),    hadQ_eta->GetValue(index),MC_lepB_phi->GetValue(0),    MC_lepB_eta->GetValue(0));
    matching[3][3] = Match(hadQ_phi->GetValue(index),    hadQ_eta->GetValue(index),MC_hadQ_phi->GetValue(0),    MC_hadQ_eta->GetValue(0));
    
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
 
    if(combination_index == 0){
      Permutations[evnr->GetValue(0)] = true;
    }
    else{Permutations[evnr->GetValue(0)] = false;}
  }

  return Permutations;
  
}

bool eire::Matching::Match(double J_phi, double J_eta, double MC_phi, double MC_eta){
  double dR = sqrt((J_phi - MC_phi)*(J_phi - MC_phi)+(J_eta - MC_eta)*(J_eta - MC_eta));
  bool matched = false;
  if(dR < 0.15){matched = true;}
  return matched;
}

