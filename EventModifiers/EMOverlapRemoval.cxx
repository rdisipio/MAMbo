#include "EMOverlapRemoval.h"

EMOverlapRemoval::EMOverlapRemoval() : IEventModifier( "OverlapRemoval" ),
   m_min_dR_ej(0.4), m_min_dR_je(0.2)
{
}


EMOverlapRemoval::~EMOverlapRemoval()
{
}


/////////////////////////////////////


void EMOverlapRemoval::Configure( const EventModifierParams_t& params )
{
}


/////////////////////////////////////


bool EMOverlapRemoval::Apply( EventData * ed )
{
  bool passed = true;

  int el_n  = ed->electrons.n;
  int mu_n  = ed->muons.n;
  int jet_n = ed->jets.n;

  for( int ie = 0 ; ie < el_n ; ++ie ) {
    TLorentzVector el = HelperFunctions::MakeFourMomentum( ed->electrons, ie );

    for( int ij = 0 ; ij < jet_n ; ++ij ) {
       const double dR_ej = PhysicsHelperFunctions::DeltaR( ed->electrons, ie, ed->jets, ij );

       if( dR_ej > m_min_dR_ej ) continue;

       TLorentzVector jet = HelperFunctions::MakeFourMomentum( ed->jets, ij );

       TLorentzVector diff = jet - el;	
       if( diff.M() < 0. ) cout << "WARNING: jet-el has negative mass" << endl;

       if( (diff.Pt() > 25 * GeV) && ( fabs(diff.Eta()) < 2.5 ) ) {  
          HelperFunctions::ReplaceParticle( &ed->jets, ij, diff );
       }
       else {
          HelperFunctions::RemoveJet( &ed->jets, ij );
       }
    }
  }
  jet_n = ed->jets.n;

  for( int ij = 0 ; ij < jet_n ; ++ij ) {
     for( int ie = 0 ; ie < el_n ; ++ie ) {
        const double dR_je = PhysicsHelperFunctions::DeltaR( ed->jets, ij, ed->electrons, ie );
        
        if( dR_je > m_min_dR_je ) continue;

        HelperFunctions::RemoveJet( &ed->electrons, ie );
     }
  }
  el_n = ed->electrons.n;
  
  for( int im = 0 ; im < mu_n ; ++im ) {
     for( int ij = 0 ; ij < jet_n ; ++ij ) {
         const double dR_mj = PhysicsHelperFunctions::DeltaR( ed->jets, ij, ed->muons, im );

         if( dR_mj > 0.04 + 10. / ed->jets.pT.at(ij) ) continue;

         HelperFunctions::RemoveJet( &ed->muons, im );
     }
  }
  mu_n = ed->muons.n;

  return passed;
}


/////////////////////////////////////////
// Plugin

extern "C" {
    EventModifiersPluginFactory_OverlapRemoval * MakeEventModifierPlugin() {
        return new EventModifiersPluginFactory_OverlapRemoval("OverlapRemoval");
    };
}

