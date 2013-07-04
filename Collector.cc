#include "Collector.h"

eire::Collector::Collector(bool HF, float Chi, float M_low, float M_high, float Like_cor_cut_up, float Like_cor_cut_down, float Like_uncor_cut_up, float Like_uncor_cut_down)
{
  use_HitFit = HF;
  if(use_HitFit){
    chicut = Chi;
    m_low = M_low;
    m_high = M_high;
  }
  Like_cut_up = Like_cor_cut_up;
  Like_cut_down = Like_cor_cut_down;
  Like_cutuncor_up = Like_uncor_cut_up;
  Like_cutuncor_down = Like_uncor_cut_down;
  match = false;
  std::vector< bool > Permutations;
}

eire::Collector::~Collector()
{
}

void eire::Collector::TurnMatchingOn()
{
  match = true;
}

std::vector< bool > eire::Collector::ReturnPermutations()
{
  return Permutations;
}

std::vector<std::vector<float> > eire::Collector::CollectLikelihoods(std::string name)
{
  std::cout<<"making Likelihoods for "<<name<<std::endl;

  int number_of_files = 0.;
  string Cor;
  string UnCor;
  string Map;

  TTree *HitFitTree;
  TFile *infile;
  TTree *HitFitTree1;
  TFile *infile1;
  TTree *HitFitTree2;
  TFile *infile2;
  TTree *HitFitTree3;
  TFile *infile3;

  std::vector<float> cor;
  std::vector<float> uncor;

  int threshold1 = 0;
  int threshold2 = 0;

  if(name == "WJets"){number_of_files = 2000;
    Cor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Wbjets_corrected_cor/weights-";
    UnCor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Wbjets_corrected_uncor/weights-";
    Map = "selected_events_map_Gen_Wbjets";
  }
  else if(name == "TTbar_cor"){number_of_files = 8000;
    Cor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Ev_cor_ME_cor/weights-";
    UnCor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Ev_cor_ME_uncor/weights-";
    Map = "selected_events_map_Gen_Cor";
  }
  else if(name == "TTbar_uncor"){number_of_files = 8000;
    Cor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Ev_uncor_ME_cor/weights-";
    UnCor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Ev_uncor_ME_uncor/weights-";
    Map = "selected_events_map_Gen_Uncor";
  }
  else if(name == "TTbar_uncor_5Jets"){number_of_files = 523;
    Cor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Ev_uncor_ME_cor_5Jets/weights-";
    UnCor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Ev_uncor_ME_uncor_5Jets/weights-";
    //    Map = "selected_events_map_Gen_Cor";
  }

  if(name == "WJets_cuts"){number_of_files = 677;//677;
    Cor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Wbjets_cuts_cor/weights-";
    UnCor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Wbjets_cuts_uncor/weights-";
  }
  else if(name == "TTbar_cor_cuts"){number_of_files = 8000;
    Cor = "/afs/cern.ch/work/k/ksbeerna/public/weights-cuts/Ev_cor_ME_cor/weights-";
    UnCor = "/afs/cern.ch/work/k/ksbeerna/public/weights-cuts/Ev_cor_ME_uncor/weights-";
  }
  else if(name == "TTbar_uncor_cuts"){number_of_files = 8000;
    Cor = "/afs/cern.ch/work/k/ksbeerna/public/weights-cuts/Ev_uncor_ME_cor/weights-";
    UnCor = "/afs/cern.ch/work/k/ksbeerna/public/weights-cuts/Ev_uncor_ME_uncor/weights-";
  }
  if(name == "WJets_smear"){number_of_files = 937;
    Cor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Wbjets_cor_smear/weights-";
    UnCor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Wbjets_uncor_smear/weights-";
  }
  else if(name == "TTbar_cor_smear"){number_of_files = 4388;
    Cor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Ev_cor_ME_cor_smear/weights-";
    UnCor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Ev_cor_ME_uncor_smear/weights-";
  }
  else if(name == "TTbar_uncor_smear"){number_of_files = 4430;
    Cor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Ev_uncor_ME_cor_smear/weights-";
    UnCor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Ev_uncor_ME_uncor_smear/weights-";
  }
  else if(name == "TTbar_MCatNLO_cor_5jets"){number_of_files = 626;
    Cor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Ev_cor_ME_cor_5Jets/weights-";
    UnCor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Ev_cor_ME_uncor_5Jets/weights-";
  }
  else if(name == "TTbar_MCatNLO_uncor_5jets"){number_of_files = 626;
    Cor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Ev_uncor_ME_cor_5Jets/weights-";
    UnCor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Ev_uncor_ME_uncor_5Jets/weights-";
  }
  else if(name == "TTbar_cor_HitFit"){number_of_files = 3695;
    Cor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Ev_cor_ME_cor_HitFit_updated_kinematics/weights-";
    UnCor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Ev_cor_ME_uncor_HitFit_updated_kinematics/weights-";
    if(use_HitFit){
      infile1 = new TFile("/data/input/HitFit/Updated_kinematics/HitFit_Cor_1.root","OPEN");
      HitFitTree1 = (TTree*) infile1->GetDirectory("HitFit")->Get("HitFitResults");
      infile2 = new TFile("/data/input/HitFit/Updated_kinematics/HitFit_Cor_2.root","OPEN");
      HitFitTree2 = (TTree*) infile2->GetDirectory("HitFit")->Get("HitFitResults");
      infile3 = new TFile("/data/input/HitFit/Updated_kinematics/HitFit_Cor_3.root","OPEN");
      HitFitTree3 = (TTree*) infile3->GetDirectory("HitFit")->Get("HitFitResults");
      threshold1 = 80300;
      threshold2 = 158350;
    }
  }
  else if(name == "TTbar_uncor_HitFit"){number_of_files = 3729;
    Cor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Ev_uncor_ME_cor_HitFit_updated_kinematics/weights-";
    UnCor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Ev_uncor_ME_uncor_HitFit_updated_kinematics/weights-";
    if(use_HitFit){
      infile1 = new TFile("/data/input/HitFit/Updated_kinematics/HitFit_Uncor_1.root","OPEN");
      HitFitTree1 = (TTree*) infile1->GetDirectory("HitFit")->Get("HitFitResults");
      infile2 = new TFile("/data/input/HitFit/Updated_kinematics/HitFit_Uncor_2.root","OPEN");
      HitFitTree2 = (TTree*) infile2->GetDirectory("HitFit")->Get("HitFitResults");
      infile3 = new TFile("/data/input/HitFit/Updated_kinematics/HitFit_Uncor_3.root","OPEN");
      HitFitTree3 = (TTree*) infile3->GetDirectory("HitFit")->Get("HitFitResults");
      threshold1 = 79050;
      threshold2 = 105900;
    }
  }
  else if(name == "WJets_HitFit"){number_of_files = 638;
    Cor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Wbjets_cor_HitFit_updated_kinematics/weights-";
    UnCor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Wbjets_uncor_HitFit_updated_kinematics/weights-";
    if(use_HitFit){
      infile = new TFile("/data/input/HitFit/Updated_kinematics/HitFit_WJets.root","OPEN");
      HitFitTree = (TTree*) infile->GetDirectory("HitFitResults")->Get("HitFitResults");
    }
  }
  else if(name == "TTbar_cor_HitFit_TF"){number_of_files = 3695;
    Cor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Ev_cor_ME_cor_HitFit_TF/weights-";
    UnCor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Ev_cor_ME_uncor_HitFit_TF/weights-";
    if(use_HitFit){
      infile = new TFile("/data/input/HitFit/Updated_kinematics/HitFit_Cor.root","OPEN");
      HitFitTree = (TTree*) infile->GetDirectory("HitFit")->Get("HitFitResults");
    }
  }
  else if(name == "TTbar_uncor_HitFit_TF"){number_of_files = 3729;
    Cor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Ev_uncor_ME_cor_HitFit_TF/weights-";
    UnCor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Ev_uncor_ME_uncor_HitFit_TF/weights-";
    if(use_HitFit){
      infile = new TFile("/data/input/HitFit/Updated_kinematics/HitFit_Uncor.root","OPEN");
      HitFitTree = (TTree*) infile->GetDirectory("HitFit")->Get("HitFitResults");
    }
  }
  else if(name == "WJets_HitFit_TF"){number_of_files = 638;
    Cor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Wbjets_cor_HitFit_TF/weights-";
    UnCor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Wbjets_uncor_HitFit_TF/weights-";
    if(use_HitFit){
      infile = new TFile("/data/input/HitFit/Updated_kinematics/HitFit_WJets.root","OPEN");
      HitFitTree = (TTree*) infile->GetDirectory("HitFit")->Get("HitFitResults");
    }
  }
  else if(name == "TTbar_cor_HitFit_NoTopMass"){number_of_files = 3665;
    Cor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Ev_cor_ME_cor_HitFit_updated_kinematics_NoTopMass/weights-";
    UnCor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Ev_cor_ME_uncor_HitFit_updated_kinematics_NoTopMass/weights-";
    if(use_HitFit){
      infile1 = new TFile("/data/input/HitFit/Updated_kinematics_NoTopMassConstraint/HitFit_Cor_1.root","OPEN");
      HitFitTree1 = (TTree*) infile1->GetDirectory("HitFit")->Get("HitFitResults");
      infile2 = new TFile("/data/input/HitFit/Updated_kinematics_NoTopMassConstraint/HitFit_Cor_2.root","OPEN");
      HitFitTree2 = (TTree*) infile2->GetDirectory("HitFit")->Get("HitFitResults");
      infile3 = new TFile("/data/input/HitFit/Updated_kinematics_NoTopMassConstraint/HitFit_Cor_3.root","OPEN");
      HitFitTree3 = (TTree*) infile3->GetDirectory("HitFit")->Get("HitFitResults");
      threshold1 = 26550;
      threshold2 = 104900;
    }
  }
  else if(name == "TTbar_uncor_HitFit_NoTopMass"){number_of_files = 3748;
    Cor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Ev_uncor_ME_cor_HitFit_updated_kinematics_NoTopMass/weights-";
    UnCor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Ev_uncor_ME_uncor_HitFit_updated_kinematics_NoTopMass/weights-";
    if(use_HitFit){
      infile1 = new TFile("/data/input/HitFit/Updated_kinematics_NoTopMassConstraint/HitFit_Uncor_1.root","OPEN");
      HitFitTree1 = (TTree*) infile1->GetDirectory("HitFit")->Get("HitFitResults");
      infile2 = new TFile("/data/input/HitFit/Updated_kinematics_NoTopMassConstraint/HitFit_Uncor_2.root","OPEN");
      HitFitTree2 = (TTree*) infile2->GetDirectory("HitFit")->Get("HitFitResults");
      infile3 = new TFile("/data/input/HitFit/Updated_kinematics_NoTopMassConstraint/HitFit_Uncor_3.root","OPEN");
      HitFitTree3 = (TTree*) infile3->GetDirectory("HitFit")->Get("HitFitResults");
      threshold1 = 79500;
      threshold2 = 160450;
    }
  }
  else if(name == "WJets_HitFit_NoTopMass"){number_of_files = 673;
    Cor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Wbjets_cor_HitFit_updated_kinematics_NoTopMass/weights-";
    UnCor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Wbjets_uncor_HitFit_updated_kinematics_NoTopMass/weights-";
    if(use_HitFit){
      infile1 = new TFile("/data/input/HitFit/Updated_kinematics_NoTopMassConstraint/HitFit_WJets_1.root","OPEN");
      HitFitTree1 = (TTree*) infile1->GetDirectory("HitFit")->Get("HitFitResults");
      infile2 = new TFile("/data/input/HitFit/Updated_kinematics_NoTopMassConstraint/HitFit_WJets_2.root","OPEN");
      HitFitTree2 = (TTree*) infile2->GetDirectory("HitFit")->Get("HitFitResults");
      infile3 = new TFile("test","WRITE");
      infile3->Close();
      threshold1 = 4000;
      threshold2 = 99999999;
    }
  }
  else if(name == "TTbar_cor_HitFit_TF_NoTopMass"){number_of_files = 3665;
    Cor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Ev_cor_ME_cor_HitFit_TF_NoTopMass/weights-";
    UnCor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Ev_cor_ME_uncor_HitFit_TF_NoTopMass/weights-";
    if(use_HitFit){
      infile = new TFile("/data/input/HitFit/Updated_kinematics_NoTopMassConstraint/HitFit_Cor.root","OPEN");
      HitFitTree = (TTree*) infile->GetDirectory("HitFit")->Get("HitFitResults");
    }
  }
  else if(name == "TTbar_uncor_HitFit_TF_NoTopMass"){number_of_files = 3748;
    Cor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Ev_uncor_ME_cor_HitFit_TF_NoTopMass/weights-";
    UnCor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Ev_uncor_ME_uncor_HitFit_TF_NoTopMass/weights-";
    if(use_HitFit){
      infile = new TFile("/data/input/HitFit/Updated_kinematics_NoTopMassConstraint/HitFit_Uncor.root","OPEN");
      HitFitTree = (TTree*) infile->GetDirectory("HitFit")->Get("HitFitResults");
    }
  }
  else if(name == "WJets_HitFit_TF_NoTopMass"){number_of_files = 673;
    Cor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Wbjets_cor_HitFit_TF_NoTopMass/weights-";
    UnCor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Wbjets_uncor_HitFit_TF_NoTopMass/weights-";
    if(use_HitFit){
      infile = new TFile("/data/input/HitFit/Updated_kinematics_NoTopMassConstraint/HitFit_WJets.root","OPEN");
      HitFitTree = (TTree*) infile->GetDirectory("HitFit")->Get("HitFitResults");
    }
  }
  else if(name == "WJets_smearPerm"){number_of_files = 937;
    Cor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Wbjets_cor_smearPerm/weights-";
    UnCor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Wbjets_uncor_smearPerm/weights-";
    if(use_HitFit){
      infile1 = new TFile("/data/input/HitFit/ComboOnly/HitFit_WJets_0.root","OPEN");
      HitFitTree1 = (TTree*) infile1->GetDirectory("HitFit")->Get("HitFitResults");
      infile2 = new TFile("/data/input/HitFit/ComboOnly/HitFit_WJets_1.root","OPEN");
      HitFitTree2 = (TTree*) infile2->GetDirectory("HitFit")->Get("HitFitResults");
      threshold1 = 5550;
      threshold2 = 99999999;
    }
  }
  else if(name == "TTbar_cor_smearPerm"){number_of_files = 4394;
    Cor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Ev_cor_ME_cor_smearPerm/weights-";
    UnCor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Ev_cor_ME_uncor_smearPerm/weights-";
    if(use_HitFit){
      infile1 = new TFile("/data/input/HitFit/ComboOnly/HitFit_Cor_0.root","OPEN");
      HitFitTree1 = (TTree*) infile1->GetDirectory("HitFit")->Get("HitFitResults");
      infile2 = new TFile("/data/input/HitFit/ComboOnly/HitFit_Cor_1.root","OPEN");
      HitFitTree2 = (TTree*) infile2->GetDirectory("HitFit")->Get("HitFitResults");
      infile3 = new TFile("/data/input/HitFit/ComboOnly/HitFit_Cor_2.root","OPEN");
      HitFitTree3 = (TTree*) infile3->GetDirectory("HitFit")->Get("HitFitResults");
      threshold1 = 31450;
      threshold2 = 126750;
    }
  }
  else if(name == "TTbar_uncor_smearPerm"){number_of_files = 4431;
    Cor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Ev_uncor_ME_cor_smearPerm/weights-";
    UnCor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Ev_uncor_ME_uncor_smearPerm/weights-";
    if(use_HitFit){
      infile = new TFile("/data/input/HitFit/ComboOnly/HitFit_Uncor.root","OPEN");
      HitFitTree = (TTree*) infile->GetDirectory("HitFit")->Get("HitFitResults");
      infile1 = new TFile("/data/input/HitFit/ComboOnly/HitFit_Uncor_0.root","OPEN");
      HitFitTree1 = (TTree*) infile1->GetDirectory("HitFit")->Get("HitFitResults");
      infile2 = new TFile("/data/input/HitFit/ComboOnly/HitFit_Uncor_1.root","OPEN");
      HitFitTree2 = (TTree*) infile2->GetDirectory("HitFit")->Get("HitFitResults");
      infile3 = new TFile("/data/input/HitFit/ComboOnly/HitFit_Uncor_2.root","OPEN");
      HitFitTree3 = (TTree*) infile3->GetDirectory("HitFit")->Get("HitFitResults");
      threshold1 = 31750;
      threshold2 = 127400;
    }
  }
  else if(name == "TTbar_cor_HitFitCombo"){number_of_files = 3714;
    Cor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Ev_cor_ME_cor_HitFitCombo/weights-";
    UnCor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Ev_cor_ME_uncor_HitFitCombo/weights-";
    if(use_HitFit){
      infile1 = new TFile("/data/input/HitFit/ComboOnly/HitFit_Cor_0.root","OPEN");
      HitFitTree1 = (TTree*) infile1->GetDirectory("HitFit")->Get("HitFitResults");
      infile2 = new TFile("/data/input/HitFit/ComboOnly/HitFit_Cor_1.root","OPEN");
      HitFitTree2 = (TTree*) infile2->GetDirectory("HitFit")->Get("HitFitResults");
      infile3 = new TFile("/data/input/HitFit/ComboOnly/HitFit_Cor_2.root","OPEN");
      HitFitTree3 = (TTree*) infile3->GetDirectory("HitFit")->Get("HitFitResults");
      threshold1 = 26550;
      threshold2 = 107350;
    }
  }
  else if(name == "TTbar_uncor_HitFitCombo"){number_of_files = 3748;
    Cor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Ev_uncor_ME_cor_HitFitCombo/weights-";
    UnCor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Ev_uncor_ME_uncor_HitFitCombo/weights-";
    if(use_HitFit){
      infile1 = new TFile("/data/input/HitFit/ComboOnly/HitFit_Uncor_0.root","OPEN");
      HitFitTree1 = (TTree*) infile1->GetDirectory("HitFit")->Get("HitFitResults");
      infile2 = new TFile("/data/input/HitFit/ComboOnly/HitFit_Uncor_1.root","OPEN");
      HitFitTree2 = (TTree*) infile2->GetDirectory("HitFit")->Get("HitFitResults");
      infile3 = new TFile("/data/input/HitFit/ComboOnly/HitFit_Uncor_2.root","OPEN");
      HitFitTree3 = (TTree*) infile3->GetDirectory("HitFit")->Get("HitFitResults");
      threshold1 = 26950;
      threshold2 = 107900;
    }
  }
  else if(name == "WJets_HitFitCombo"){number_of_files = 673;
    Cor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Wbjets_cor_HitFitCombo/weights-";
    UnCor = "/afs/cern.ch/work/k/ksbeerna/public/weights/Wbjets_uncor_HitFitCombo/weights-";
    if(use_HitFit){
      infile1 = new TFile("/data/input/HitFit/ComboOnly/HitFit_WJets_0.root","OPEN");
      HitFitTree1 = (TTree*) infile1->GetDirectory("HitFit")->Get("HitFitResults");
      infile2 = new TFile("/data/input/HitFit/ComboOnly/HitFit_WJets_1.root","OPEN");
      HitFitTree2 = (TTree*) infile2->GetDirectory("HitFit")->Get("HitFitResults");
      threshold1 = 4000;
      threshold2 = 99999999;
    }
  }
  
  map<int, bool> match_map;
  if(match){
    Matching *Matcher = new Matching(HitFitTree1);
    match_map = Matcher->CheckPermutations();
  }

  map<int, bool> Selection_map;
  bool select = false;
  int n_sel = 0.;
  if(name == "TTbar_cor" || name == "TTbar_uncor" || name == "WJets"){
    select=true;
    ifstream mapfile(Map.c_str());
    string ev_nr;
    string selected;
    if(mapfile.is_open()){
      while(mapfile>>ev_nr){
	mapfile>>selected;
	Selection_map[atoi(ev_nr.c_str())] = atoi(selected.c_str());
	if(atoi(selected.c_str()) > 0){n_sel++;}
      }
    }
  }

    std::cout<<"n_sel = "<<n_sel<<std::endl;

  map<int, bool> ChiCut_map1;
  map<int, bool> ChiCut_map2;
  map<int, bool> ChiCut_map3;

  if(use_HitFit){
    int nevents = HitFitTree1->GetEntries();
    for(int x=0; x < nevents; x++){
      HitFitTree1->GetEntry(x);
      TObjArray *leaves = (TObjArray*)HitFitTree1->GetListOfLeaves();
      TLeaf *sol = (TLeaf*)leaves->UncheckedAt(1);
      sol = HitFitTree1->GetLeaf("nSol");
      TLeaf *evnr = (TLeaf*)leaves->UncheckedAt(56);
      evnr = HitFitTree1->GetLeaf("event_number");
      TLeaf *chi2 = (TLeaf*)leaves->UncheckedAt(30);
      chi2 = HitFitTree1->GetLeaf("Chi2");
      TLeaf *mtop = (TLeaf*)leaves->UncheckedAt(32);
      mtop = HitFitTree1->GetLeaf("MT");
      if(sol->GetValue(0) == 0){continue;}
      if(chi2->GetValue(0) < chicut ){
        if(mtop->GetValue(0) >= m_low && mtop->GetValue(0) <= m_high){
          ChiCut_map1[evnr->GetValue(0)] = true;
        }
        else{ChiCut_map1[evnr->GetValue(0)] = false;}
      }
      else{ChiCut_map1[evnr->GetValue(0)] = false;}
    }
    infile1->Close();
    nevents = HitFitTree2->GetEntries();
    for(int x=0; x < nevents; x++){
      HitFitTree2->GetEntry(x);
      TObjArray *leaves = (TObjArray*)HitFitTree2->GetListOfLeaves();
      TLeaf *sol = (TLeaf*)leaves->UncheckedAt(1);
      sol = HitFitTree2->GetLeaf("nSol");
      TLeaf *evnr = (TLeaf*)leaves->UncheckedAt(56);
      evnr = HitFitTree2->GetLeaf("event_number");
      TLeaf *chi2 = (TLeaf*)leaves->UncheckedAt(30);
      chi2 = HitFitTree2->GetLeaf("Chi2");
      TLeaf *mtop = (TLeaf*)leaves->UncheckedAt(32);
      mtop = HitFitTree2->GetLeaf("MT");
      if(sol->GetValue(0) == 0){continue;}
      if(chi2->GetValue(0) < chicut ){
        if(mtop->GetValue(0) >= m_low && mtop->GetValue(0) <= m_high){
          ChiCut_map2[evnr->GetValue(0)] = true;
        }
        else{ChiCut_map2[evnr->GetValue(0)] = false;}
      }
      else{ChiCut_map2[evnr->GetValue(0)] = false;}
    }
    infile2->Close();
    if(infile3->IsOpen()){
      nevents = HitFitTree3->GetEntries();
      for(int x=0; x < nevents; x++){
	HitFitTree3->GetEntry(x);
	TObjArray *leaves = (TObjArray*)HitFitTree3->GetListOfLeaves();
	TLeaf *sol = (TLeaf*)leaves->UncheckedAt(1);
	sol = HitFitTree3->GetLeaf("nSol");
	TLeaf *evnr = (TLeaf*)leaves->UncheckedAt(56);
	evnr = HitFitTree3->GetLeaf("event_number");
	TLeaf *chi2 = (TLeaf*)leaves->UncheckedAt(30);
	chi2 = HitFitTree3->GetLeaf("Chi2");
	TLeaf *mtop = (TLeaf*)leaves->UncheckedAt(32);
	mtop = HitFitTree3->GetLeaf("MT");
	if(sol->GetValue(0) == 0){continue;}
	if(chi2->GetValue(0) < chicut ){
	  if(mtop->GetValue(0) >= m_low && mtop->GetValue(0) <= m_high){
	    ChiCut_map3[evnr->GetValue(0)] = true;
	  }
	  else{ChiCut_map3[evnr->GetValue(0)] = false;}
	}
	else{ChiCut_map3[evnr->GetValue(0)] = false;}
      }
      infile3->Close();
    }
  }

  map<int, bool> ChiCut_map = ChiCut_map1;

  for(int i= 0; i < number_of_files; i++){
    int Ev = i*50;
    if(Ev < threshold1){ChiCut_map = ChiCut_map1;}
    else if(Ev < threshold2){ChiCut_map = ChiCut_map2;}
    else{ChiCut_map = ChiCut_map3;}

    stringstream nameCor;
    nameCor<<Cor<<Ev<<".out";
    stringstream nameUnCor;
    nameUnCor<<UnCor<<Ev<<".out";

    //Open input file                                                                                                                                                                                                                                                                                                  
    ifstream myInfile(nameCor.str().c_str());
    ifstream myInfile2(nameUnCor.str().c_str());
    string event_number;
    string likelihood;
    string likelihood_unc;
    float L, L_unc;
    
    if(myInfile.is_open() && myInfile2.is_open()){
      if ( myInfile.is_open() ) {
	int x = 0;
	while ( myInfile>>event_number){
	  int evnr = Ev + x;
	  myInfile>>likelihood; myInfile>>likelihood_unc;
	  if(atof(likelihood.c_str()) != 0 && use_HitFit && ChiCut_map[atoi(event_number.c_str())]){L= log(atof(likelihood.c_str()));}
	  else if(atof(likelihood.c_str()) != 0 && !use_HitFit && select && Selection_map[evnr]){L = log(atof(likelihood.c_str()));}
	  else if(atof(likelihood.c_str()) != 0 && !use_HitFit && !select){L = log(atof(likelihood.c_str()));}
	  else{L = 999;}
	  L_unc = log(atof(likelihood_unc.c_str()));
	  cor.push_back(L);
	  x++;
	  if(match)
	    {
	      Permutations.push_back(match_map[atoi(event_number.c_str())]);
	    }
	}
      }
      myInfile.close();
      
      if ( myInfile2.is_open() ) {
	int x = 0;
	while ( myInfile2>>event_number){
	  int evnr = Ev + x;
	  myInfile2>>likelihood; myInfile2>>likelihood_unc;
	  if(atof(likelihood.c_str()) != 0 && use_HitFit && ChiCut_map[atoi(event_number.c_str())]){L= log(atof(likelihood.c_str()));}
	  else if(atof(likelihood.c_str()) != 0 && !use_HitFit && select && Selection_map[evnr]){L = log(atof(likelihood.c_str()));}
	  else if(atof(likelihood.c_str()) != 0 && !use_HitFit && !select){L = log(atof(likelihood.c_str()));}
	  else{L = 999;}
	  L_unc = log(atof(likelihood_unc.c_str()));
	  uncor.push_back(L);
	  x++;
	}
      }
      myInfile2.close();
    }
  }

  std::cout<<"cor size = "<<cor.size()<<std::endl;
  for(unsigned int j = 0; j < cor.size(); j++){
    if((cor)[j] == 999 || (uncor)[j] == 999 || (-1)*(cor)[j] > Like_cut_up || (-1)*(cor)[j] < Like_cut_down || (-1)*(uncor)[j] > Like_cutuncor_up || (-1)*(uncor)[j] < Like_cutuncor_down){
      cor.erase(cor.begin()+j);
      uncor.erase(uncor.begin()+j);
      if(match){Permutations.erase(Permutations.begin()+j);}
      j--;}
  }

  std::vector<std::vector<float> > result;
  result.push_back(cor);
  result.push_back(uncor);

  //  std::cout<<"finish"<<std::endl;
  return result;
}
