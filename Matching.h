#ifndef EIRE_MATCHING_H
#define EIRE_MATCHING_H
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
#include <TH1F.h>
#include "TROOT.h"
 
using namespace std;

namespace eire{
  class Matching{
  public:
    Matching(TTree *tree);
    ~Matching();
    map<int, bool> CheckPermutations();
    bool Match(double J_phi, double J_eta, double MC_phi, double MC_eta);

  private:
    TTree *HitFitTree;
  };
}

#endif
