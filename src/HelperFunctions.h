#ifndef __HELPERFUNCTIONS_H__
#define __HELPERFUNCTIONS_H__

#include "Commons.h"

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

#include "fastjet/JetDefinition.hh"
#include "fastjet/AreaDefinition.hh"
#include "fastjet/ClusterSequence.hh"
#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/PseudoJet.hh"

#include "TLorentzVector.h"

#include "HEPTopTagger.h"
#include "EventData.h"

namespace HelperFunctions {
  size_t Tokenize( const string& str, StringVector_t& tokens, const string& delimiters = "," );

  int    ListDirectory( string dir, vector<string> &files );

  int    FindFatJets( EventData * ed, const double fjet_ptmin = 300.*GeV, fastjet::JetAlgorithm alg = fastjet::antikt_algorithm, double R = 1.0 );

  template< class T > 
  TLorentzVector MakeFourMomentum( const T& coll, int i ) {
     TLorentzVector p;

     p.SetPtEtaPhiE( coll.pT.at(i), coll.eta.at(i), coll.phi.at(i), coll.E.at(i) );
     
     return p;
  }

 
  template< class T >
  size_t DumpParticleToEventData( const TLorentzVector& p, T * p_coll )
  {
     const size_t new_index = p_coll->n;

     p_coll->pT.push_back( p.Pt() );
     p_coll->eta.push_back( p.Eta() );
     p_coll->phi.push_back( p.Phi() );
     p_coll->E.push_back( p.E() );
     p_coll->m.push_back( p.M() ); 

     p_coll->n += 1;
 
     return new_index;
  }

};

#endif /**  __HELPERFUNCTIONS_H__ */
