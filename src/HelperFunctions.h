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

  string Replace( const string& base, const string& from, const string& to );
  
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
    assert( p.Pt() > 0 );

    const size_t new_index = p_coll->n;

    p_coll->pT.push_back( p.Pt() );
    p_coll->eta.push_back( p.Eta() );
    p_coll->phi.push_back( p.Phi() );
    p_coll->E.push_back( p.E() );
    p_coll->m.push_back( p.M() ); 

    p_coll->n += 1;
    
    return new_index;
  }


  template< class S, class T >
  size_t CopyParticleToEventData( const S * p_source, const int s_index, T * p_target ) {
      const size_t new_index = p_target->n;

      p_target->pT.push_back( p_source->pT.at( s_index ) );
      p_target->eta.push_back( p_source->eta.at( s_index ) );
      p_target->phi.push_back( p_source->phi.at( s_index ) );
      p_target->E.push_back( p_source->E.at( s_index ) );
      //p_target->m.push_back( p_source->m.at( s_index ) );

      return new_index;
  };

  
  template< class T >
    size_t DumpTruthParticleToEventData( const TLorentzVector& p, const int pid, const int status, const int barcode, const float q, T * p_coll ) 
    {
      assert( p.Pt() > 0 );

      const size_t new_index = p_coll->n;

      p_coll->pdgId.push_back( pid );
      p_coll->status.push_back( status );
      p_coll->barcode.push_back( barcode );

      p_coll->pT.push_back( p.Pt() );
      p_coll->eta.push_back( p.Eta() );
      p_coll->phi.push_back( p.Phi() );
      p_coll->E.push_back( p.E() );
      p_coll->m.push_back( p.M() ); 
      p_coll->q.push_back( q ); 

      p_coll->n += 1;
      
      return new_index;
  }
};

#endif /**  __HELPERFUNCTIONS_H__ */
