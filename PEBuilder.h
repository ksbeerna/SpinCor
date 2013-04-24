#ifndef EIRE_PEBUILDER_H
#define EIRE_PEBUILDER_H
#include <math.h>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <sstream>
#include <stdio.h>
#include <fstream>
#include "TROOT.h"
#include "TSystem.h"
#include "TVirtualFitter.h"
#include "TTree.h"
#include "TGraphErrors.h"
#include "RooMsgService.h"
#include "TH1.h"
#include "TF1.h"
#include "TH2.h"
#include "TStyle.h"
#include <RooFit.h>
#include <RooMinuit.h>
#include "RooMinimizer.h"
#include "RooFitResult.h"
#include <RooGlobalFunc.h>
#include <RooPlot.h>
#include "RooTFnBinding.h"
#include <TMultiGraph.h>
#include "TF2.h"
#include "RooCategory.h"
#include "RooPlot.h"
#include "TROOT.h"
#include "RooGlobalFunc.h"
#include <stdio.h>
#include "TStyle.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <cstdlib>
#include "TFile.h"
#include "TLegend.h"
#include "RooCategory.h"
#include "TTree.h"
#include "TPaveText.h"
#include "TF1.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TVector.h"
#include "TCanvas.h"
#include "TProfile.h"
#include <math.h>
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooConstVar.h"
#include "RooFormulaVar.h"
#include "RooGenericPdf.h"
#include "RooPolynomial.h"
#include "RooChi2Var.h"
#include "RooMinuit.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "RooPlot.h"
#include "RooFitResult.h"
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
#include "RooFitResult.h"
#include <RooPlot.h>
#include "RooHistPdf.h"
#include "RooAddPdf.h"
#include "RooAbsPdf.h"

using namespace std;

namespace eire{
  class PEBuilder{
  public:
    PEBuilder(std::vector< std::vector<float> > Cor, std::vector< std::vector<float> > Uncor, float mixing, std::vector< std::vector<float> > WJets, float Back_frac, bool use_back);
    ~PEBuilder();
    void SetProperties(int Bins, int EvPerPE, float lowRange, float highRange, bool v); 
    void Mix();

  private:
    std::vector<TH1F> DrawTemplates();
    std::vector<double> Fit(TH1F *hist_data, int k, TH1F TemplateCor, TH1F TemplateUncor);
    std::vector<double> FitB(TH1F *hist_data, int k, TH1F TemplateCor, TH1F TemplateUncor, TH1F TemplateWJets);
    std::vector< std::vector<float> > L_Cor;
    std::vector< std::vector<float> > L_Uncor;
    std::vector< std::vector<float> > L_WJets;
    bool Use_back;
    float Wfrac;
    int nBins;
    int EvPE;
    float low_range;
    float high_range;
    float mix_frac;
    bool verbose;
  };
}

#endif
