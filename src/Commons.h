#ifndef __COMMONS_H__
#define __COMMONS_H__


/////////////////////////////////////////////


//#define GeV 1000.
static const double GeV = 1.e+3;

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
#include <assert.h>

using namespace std;

#include <TROOT.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TDirectory.h>
#include <TChain.h>
#include <TLorentzVector.h>

/////////////////////////////////////////////

typedef TH1D ROOT_TH1_t;
typedef TH2D ROOT_TH2_t;

enum LeptonFlavor { kElectron, kMuon, kTau, kNeutrino, kUnknown };
enum JetTag       { kLight = 0, kCTagged = 4, kBTagged = 5, kTauTagged = 15, kGTagged = 21 };

typedef vector< string >       StringVector_t;
typedef vector< unsigned int > array_ui;
typedef vector< double >       array_d;
typedef vector< LeptonFlavor > array_fl;
typedef vector< JetTag >       array_tag;

typedef map< string,  vector< TH1* > > HistogramCollection_t;

typedef map< string, vector< double > > PropertyCollection_t;

/////////////////////////////////////////////

#define SAFE_DELETE(X) if(X) delete (X);

#define GET_VALUE(X) this->m_ntuple-> X
#define GET_VALUE_VECTOR(X,N) this->m_ntuple-> X ->at( N )
#define GET_VALUE_ARRAY(X,N) this->m_ntuple-> X[N]
#define CHECK_TRIGGER(T) if( GET_VALUE( T ) ) ed->trigger[ #T ] = 1
#define MAKE_OBJECT(OBJ, ED) if( !MakeEvent##OBJ( ED ) ) throw runtime_error( "Cannot create " # OBJ )
#define SET_PROPERTY(P) ed->property[ #P ] = GET_VALUE( P )


#endif /** __COMMONS_H__ */
