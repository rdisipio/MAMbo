/* 
 * File:   ControlPlotValues.h
 * Author: Michele
 *
 * Created on 30 October 2014, 16:18
 */

#ifndef CONTROLPLOTVALUES_H
#define	CONTROLPLOTVALUES_H

#include <vector>
#include "JetValues.h"

using namespace std;

class ControlPlotValues {
public:
    ControlPlotValues();
    ControlPlotValues(const ControlPlotValues& orig);
    virtual ~ControlPlotValues();

    double weight;
    double lep_pt; 
    double lep_eta; 
    double lep_phi; 
    double lep_E;  
    int    jet_n; 
    int    bjet_n;  
    int    fjet_n;
    double ETmiss;  
    double mwt;     
    vector<JetValues> jets;
    vector<JetValues> fatJets;
    
private:

};

#endif	/* CONTROLPLOTVALUES_H */

