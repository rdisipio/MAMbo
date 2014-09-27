#include "HelperFunctions.h"

namespace HelperFunctions {
  size_t Tokenize( const string& str, StringVector_t& tokens, const string& delimiters ) 
  {
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while( string::npos != pos || string::npos != lastPos )
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }

    return tokens.size();
  }
  
  
  //////////////////////////////////////////////////////

  
  std::string Replace( const std::string& base, const std::string& from, const std::string& to) 
  {
    std::string SecureCopy = base;

    for (size_t start_pos = SecureCopy.find(from); start_pos != std::string::npos; start_pos = SecureCopy.find(from,start_pos))
    {
        SecureCopy.replace(start_pos, from.length(), to);
    }

    return SecureCopy;
}
  
  //////////////////////////////////////////////////////

  
  int ListDirectory( string dir, vector<string> &files )
  {
     DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
      cout << "Error(" << errno << ") opening " << dir << endl;
      return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
      files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return files.size();
  }


   //////////////////////////////////////////////////////


  int FindFatJets( EventData * ed, const double fjet_ptmin, fastjet::JetAlgorithm alg, double R )
  {
    vector< fastjet::PseudoJet > pseudoJets;
    for( int i = 0 ; i < ed->jets.n ; ++i ) {
      double px = ed->jets.pT.at(i) * cos( ed->jets.phi.at(i) );
      double py = ed->jets.pT.at(i) * sin( ed->jets.phi.at(i) );
      double pz = ed->jets.pT.at(i) * sinh( ed->jets.eta.at(i) );
      double E  = ed->jets.E.at(i);

      fastjet::PseudoJet pj( px, py, pz, E );
      pseudoJets.push_back( pj );
    }

    const fastjet::JetDefinition fat_jet_def( alg, R );
    fastjet::ClusterSequence clust_seq( pseudoJets, fat_jet_def );
    vector<fastjet::PseudoJet> fjets = clust_seq.inclusive_jets( fjet_ptmin );

    ed->fjets.n = fjets.size();
    for( vector<fastjet::PseudoJet>::const_iterator fj = fjets.begin() ; fj != fjets.end() ; ++fj ) {
      ed->fjets.pT.push_back(  fj->pt() );
      ed->fjets.eta.push_back( fj->pseudorapidity() );
      ed->fjets.phi.push_back( fj->phi() );
      ed->fjets.E.push_back(   fj->E() );
      ed->fjets.m.push_back(   fj->m() );

      HEPTopTagger toptag( clust_seq, *fj, 172.5*GeV, 80.4*GeV );
      toptag.set_top_range( 130*GeV, 230*GeV );
      toptag.run_tagger();

      double tag    = 0;
      double hadt_m = -1.0;
      if( toptag.is_masscut_passed() == true ) {
	tag    = 1;
	hadt_m = toptag.top_candidate().m();
      }
      ed->fjets.tag.push_back( tag );  
      ed->fjets.hadt_m.push_back( hadt_m );  
    }

    return ed->fjets.n;
  }


  //////////////////////////////////////////////////////

  
  bool ComputeJetsDR(const TLorentzVector& r_jet1, const TLorentzVector& r_jet2, const TLorentzVector& r_had_bjet, const TLorentzVector& r_lep_bjet,
		     const TLorentzVector& p_jet1, const TLorentzVector& p_jet2, const TLorentzVector& p_had_bjet, const TLorentzVector& p_lep_bjet,
		     int debug)
  {

    vector< double > DRs;

    // don't care about swap within jets forming Whad:
    double dr1 = r_jet1.DeltaR( p_jet1 );
    double dr2 = r_jet2.DeltaR( p_jet2 );
    double dr1swap = r_jet2.DeltaR( p_jet1 );
    double dr2swap = r_jet1.DeltaR( p_jet2 );
    if (dr1 + dr2 < dr1swap + dr2swap) {
      DRs.push_back( dr1 );
      DRs.push_back( dr2 );
    } else {
      DRs.push_back( dr1swap );
      DRs.push_back( dr2swap );	  
    }
    DRs.push_back(r_had_bjet.DeltaR( p_had_bjet ) );
    DRs.push_back(r_lep_bjet.DeltaR( p_lep_bjet ) );
    
    bool allObjectsMatched = true;
    if (debug) cout << "  DRs: ";
    if (debug) cout << "  Whad: " << dr1 << "," << dr2 << " " << dr1swap << "," << dr2swap;
    if (debug) cout << "  Choice: ";
    for (auto vector< double >::iterator it = DRs.begin(); it != DRs.end(); ++it) {
      if (debug) cout << "   " << (*it) << " ";
      if ( (*it) >= 0.35) {
	allObjectsMatched = false;
	if (!debug) 
	  break;
      }
    }
    if (debug) cout << endl;

    return allObjectsMatched;

  }

  //////////////////////////////////////////////////////

};
