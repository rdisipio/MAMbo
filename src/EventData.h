#ifndef __EVENTDATA_H__
#define __EVENTDATA_H__

#include "Commons.h"

///////////////////////////////////////////


struct EventData 
{
  struct EventInfo_t {
    Long64_t runNumber;
    Long64_t eventNumber;
    Long64_t mcChannelNumber;
    double   mcWeight;
    double   mu;
    int      hfor;
    float    MC_vxp_z;
    double   eventWeight;
  } info;

  struct Lepton_t { 
    int    n;
    double pT;
    double eta;
    double phi;
    double E;
    double m;
  } lepton;

  struct Electrons_t { 
    int     n;
    array_d pT;
    array_d eta;
    array_d phi;
    array_d E;
    array_d m;
  } electrons;

  struct Muons_t { 
    int n;
    array_d pT;
    array_d eta;
    array_d phi;
    array_d E;
    array_d m;
  } muons;

  struct Jets_t { 
    int     n;
    array_d pT;
    array_d eta;
    array_d phi;
    array_d E;
    array_d m;
    array_tag tag;
  } jets;

  struct bJets_t { 
    int     n;
    array_d pT;
    array_d eta;
    array_d phi;
    array_d E;
    array_d m;
  } bjets;

  struct fJet_t { 
    int    n;
    array_d pT;
    array_d eta;
    array_d phi;
    array_d E;
    array_d m;
    array_d d12;
    array_d dR_lj;
    array_d dPhi_lj;
    array_d tag;
    array_d hadt_m;
  } fjets;

  struct Truth_t {
    int     n;
    array_ui pdgId;
    array_ui status;
    array_ui barcode;

    array_d pT;
    array_d eta;
    array_d phi;
    array_d E;
    array_d m;
  };

  struct MET_t {
    double et;
    double etx;
    double ety;
    double phi;
    double sumet;
  } MET;

  map< string, double > property;
};

#endif /** __EVENTDATA_H__ */
