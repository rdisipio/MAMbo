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

  TLorentzVector MakeMomentum( const EventData::Electrons_t& coll, int i );
};

#endif /**  __HELPERFUNCTIONS_H__ */
