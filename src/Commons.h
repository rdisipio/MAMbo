#ifndef __COMMONS_H__
#define __COMMONS_H__


/////////////////////////////////////////////


#define GeV 1000.


/////////////////////////////////////////////

#include <math.h>

#include <iostream>
#include <fstream>

#include <string>
#include <sstream>

#include <vector>
#include <set>
#include <list>
#include <map>

#include <stdexcept>

using namespace std;

#include <TROOT.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TDirectory.h>
#include <TChain.h>
#include <TLorentzVector.h>

/////////////////////////////////////////////


enum LeptonFlavor { kElectron, kMuon, kTau, kNeutrino };
enum JetTag       { kLight = 0, kCTagged = 4, kBTagged = 5, kTauTagged = 15, kGTagged = 21 };

typedef vector< string >       StringVector_t;
typedef vector< unsigned int > array_ui;
typedef vector< double >       array_d;
typedef vector< LeptonFlavor > array_fl;
typedef vector< JetTag >       array_tag;

typedef map< string, TH1* > HistogramCollection_t;

typedef map< string, vector< double > > PropertyCollection_t;

/////////////////////////////////////////////


#endif /** __COMMONS_H__ */
