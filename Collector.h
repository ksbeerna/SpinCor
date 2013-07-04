#ifndef EIRE_COLLECTOR_H
#define EIRE_COLLECTOR_H

#include <iostream> 
#include <math.h>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>
#include <TTree.h>
#include <TLeaf.h>
#include <TFile.h>
#include <cstdlib>
#include <stdio.h>
#include <iomanip>
#include <Matching.h>
using namespace std;

namespace eire{
  class Collector{
  public:
    Collector(bool HF=false, float Chi=99999, float M_low=0, float M_high=99999, float Like_cor_cut_up = 999999, float Like_cor_cut_down = 0,float Like_uncor_cut_up = 999999, float Like_uncor_cut_down = 0);
    ~Collector();
    std::vector<std::vector<float> > CollectLikelihoods(std::string name); 
    void TurnMatchingOn();
    std::vector< bool > ReturnPermutations();
    
  private:
    bool use_HitFit;
    bool match;
    std::vector< bool > Permutations;
    float chicut;
    float m_low;
    float m_high;
    float Like_cut_up;
    float Like_cut_down;
    float Like_cutuncor_up;
    float Like_cutuncor_down;
  };
}

#endif
