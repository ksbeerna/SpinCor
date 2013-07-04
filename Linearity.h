#ifndef EIRE_LINEARITY_H
#define EIRE_LINEARITY_H

#include <iostream> 
#include <math.h>
#include <TFitResult.h>
#include <TFitResultPtr.h>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>
#include <TH1.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TLine.h>
#include <cstdlib>
#include <stdio.h>
#include <iomanip>
using namespace std;

namespace eire{
  class Linearity{
  public:
    Linearity(string name);
    ~Linearity();
    void AddPoint(int index, double f_gen, double f_obs, double f_obs_err, double p_av, double p_averr, double p_rms, double p_rmserr); 
    void Plot();
    
  private:
    double x[5];
    double y[5];
    double y_err[5];
    double P_av[5];
    double P_averr[5];
    double P_rms[5];
    double P_rmserr[5];
    string Name;
  };
}

#endif
