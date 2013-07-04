#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include "ConfigReader/ConfigReader.h"
#include "Collector.h"
#include "PEBuilder.h"
#include "Linearity.h"
#include "TFile.h"
#include "Matching.h"

int main(int argc, char **argv)
{
  if(argc < 2){
    std::cerr << "usage: ./SpinCor <config file>" << std::endl;
    exit(1);
  }
  
  // read config file name as parameter from command line
  std::string filename(argv[1]);
  
  eire::ConfigReader *config_reader = new eire::ConfigReader();
  config_reader->read_config_from_file(filename);

  //read config file and get all parameters necessary
  std::string Dataset_cor = config_reader->get_var("Dataset_cor","global",true);
  std::string Dataset_uncor = config_reader->get_var("Dataset_uncor","global",true);
  std::string Dataset_wjets = config_reader->get_var("Dataset_wjets","global",false);
  std::string Name = config_reader->get_var("output_name","global",true);
  bool verbose = false;
  verbose = config_reader->get_bool_var("verbose","global",false);
  float Wfrac = atof(config_reader->get_var("Wfrac","global",false).c_str());
  bool with_HitFit = false;
  with_HitFit = config_reader->get_bool_var("with_HitFit","global",false);
  float mixing = atof(config_reader->get_var("mixing","global",true).c_str());
  int nbins = atoi(config_reader->get_var("nbins","global",true).c_str());
  int nEvPE = atoi(config_reader->get_var("Ev_PE","global",true).c_str());
  float lowRange = atof(config_reader->get_var("lowRange","global",true).c_str());
  float highRange = atof(config_reader->get_var("highRange","global",true).c_str());
  float Chicut = atof(config_reader->get_var("Chicut","global",false).c_str());
  if(Chicut == 0){Chicut = 99999;}
  //  bool match = config_reader->get_bool_var("permutation_matching","global",false);
  float MassLow = atof(config_reader->get_var("MassLow","global",false).c_str());
  if(MassLow == 0){MassLow = -10;}
  float MassHigh = atof(config_reader->get_var("MassHigh","global",false).c_str());
  if(MassHigh == 0){MassHigh = 99999;}
  float Like_cut_up = atof(config_reader->get_var("Like_cor_cut_up","global",false).c_str());
  if(Like_cut_up == 0){Like_cut_up = 999999;}
  float Like_cut_down = atof(config_reader->get_var("Like_cor_cut_down","global",false).c_str());
  float Like_cutuncor_up = atof(config_reader->get_var("Like_uncor_cut_up","global",false).c_str());
  if(Like_cutuncor_up == 0){Like_cutuncor_up = 999999;}
  float Like_cutuncor_down = atof(config_reader->get_var("Like_uncor_cut_down","global",false).c_str());

  //if you want to run the complete pseudo-experiments at once!
  bool RunFullExp = config_reader->get_bool_var("RunFullExp","global",false);

  //do you want to print out the permutations
  bool matching = config_reader->get_bool_var("perm_matching","global",false);
  if(matching == 0){
    matching = false;
  }

  //naming
  stringstream name;
  name<<Name<<"_b"<<nbins<<lowRange<<"-"<<highRange<<"_"<<nEvPE<<"evPE";
  
  //get the likelihoods of the chosen dataset
  eire::Collector *Cor_collector = new eire::Collector(with_HitFit, Chicut, MassLow, MassHigh,Like_cut_up,Like_cut_down,Like_cutuncor_up,Like_cutuncor_down);
  eire::Collector *Uncor_collector = new eire::Collector(with_HitFit, Chicut, MassLow, MassHigh,Like_cut_up,Like_cut_down,Like_cutuncor_up,Like_cutuncor_down);

  if(matching)
    {
      Cor_collector->TurnMatchingOn();
      Uncor_collector->TurnMatchingOn();
    }
  
  std::vector<std::vector<float> > L_cor = Cor_collector->CollectLikelihoods(Dataset_cor);
  std::vector<std::vector<float> > L_uncor = Uncor_collector->CollectLikelihoods(Dataset_uncor);

  bool UseBack = false;
  UseBack = config_reader->get_bool_var("use_back","global",true);
  std::vector<std::vector<float> > Wjets;
  eire::Collector *W_collector;
  if(!Dataset_wjets.empty()){
    W_collector = new eire::Collector(with_HitFit, Chicut, MassLow, MassHigh,Like_cut_up,Like_cut_down,Like_cutuncor_up,Like_cutuncor_down);
    Wjets = W_collector->CollectLikelihoods(Dataset_wjets);
  }

  //split into the Pseudo-Experiments with proper mixing
  eire::PEBuilder *builder;
  builder = new eire::PEBuilder(L_cor, L_uncor, Wjets, Wfrac, UseBack, name.str());
  
  eire::Linearity *LinPlotter;
  LinPlotter = new eire::Linearity(name.str());

  std::vector<TH1F> templates;
  std::vector<double> Results; 

  if(!RunFullExp){
    builder->SetProperties(nbins,nEvPE,lowRange,highRange,verbose, mixing);
    templates = builder->DrawTemplates();
    Results = builder->Mix(templates);
  }
  else{
    builder->SetProperties(nbins,nEvPE,lowRange,highRange,verbose, 0.);
    templates = builder->DrawTemplates();
    Results = builder->Mix(templates);
    LinPlotter->AddPoint(0, 0.,(Results)[0],(Results)[1],(Results)[2],(Results)[3],(Results)[4],(Results)[5]);
    builder->SetProperties(nbins,nEvPE,lowRange,highRange,verbose, 0.25);
    Results = builder->Mix(templates);
    LinPlotter->AddPoint(1, 0.25,(Results)[0],(Results)[1],(Results)[2],(Results)[3],(Results)[4],(Results)[5]);
    builder->SetProperties(nbins,nEvPE,lowRange,highRange,verbose, 0.50);
    Results = builder->Mix(templates);
    LinPlotter->AddPoint(2, 0.50,(Results)[0],(Results)[1],(Results)[2],(Results)[3],(Results)[4],(Results)[5]);
    builder->SetProperties(nbins,nEvPE,lowRange,highRange,verbose, 0.75);
    Results = builder->Mix(templates);
    LinPlotter->AddPoint(3, 0.75,(Results)[0],(Results)[1],(Results)[2],(Results)[3],(Results)[4],(Results)[5]);
    builder->SetProperties(nbins,nEvPE,lowRange,highRange,verbose, 1.);
    Results = builder->Mix(templates);
    LinPlotter->AddPoint(4, 1.,(Results)[0],(Results)[1],(Results)[2],(Results)[3],(Results)[4],(Results)[5]);
    LinPlotter->Plot();
  }

  if(config_reader){
    delete config_reader;
    config_reader = NULL;
  }
  if(Cor_collector){
    delete Cor_collector;
    Cor_collector = NULL;
  }
  if(Uncor_collector){
    delete Uncor_collector;
    Uncor_collector = NULL;
  }
  //  if(W_collector){
  //delete W_collector;
  //W_collector = NULL;
  //}
  if(builder){
    delete builder;
    builder = NULL;
  }
  if(LinPlotter){
    delete LinPlotter;
    LinPlotter = NULL;
  }

  return 0;
}
