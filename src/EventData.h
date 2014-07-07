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
    map< string, double > property;
  } info;

  struct Lepton_t { 
    int    n;
    double pT;
    double eta;
    double phi;
    double E;
    double m;
    double q;
    PropertyCollection_t property; // see src/Commons.h
  } lepton;

  struct Electrons_t { 
    int     n;
    array_d pT;
    array_d eta;
    array_d phi;
    array_d E;
    array_d m;
    array_d q;
    PropertyCollection_t property;
  } electrons;

  struct Muons_t { 
    int n;
    array_d pT;
    array_d eta;
    array_d phi;
    array_d E;
    array_d m;
    array_d q;
    PropertyCollection_t property;
  } muons;

  struct Jets_t { 
    int     n;
    array_ui index;
    array_d pT;
    array_d eta;
    array_d phi;
    array_d E;
    array_d m;
    array_tag tag;
    PropertyCollection_t property;
  } jets;

  struct bJets_t { 
    int     n;
    array_ui index;
    array_d pT;
    array_d eta;
    array_d phi;
    array_d E;
    array_d m;
    PropertyCollection_t property;
  } bjets;

  struct lJets_t {
    int     n;
    array_ui index;
    array_d pT;
    array_d eta;
    array_d phi;
    array_d E;
    array_d m;
    array_tag tag;
    PropertyCollection_t property;
  } ljets;

  struct fJet_t { 
    int    n;
    array_ui index;
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
    PropertyCollection_t property;
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
    array_d q;
    PropertyCollection_t property;
  } mctruth;
 
  struct MET_t {
    double et;
    double etx;
    double ety;
    double phi;
    double sumet;
  } MET;


  struct Reco_t {
    int     n;
    array_d pT;
    array_d eta;
    array_d phi;
    array_d E;
    array_d m;
    array_ui pdgId;
    PropertyCollection_t property;
  } reco;

  map< string, int > trigger;
  map< string, double > property;
};

#endif /** __EVENTDATA_H__ */
