#ifndef __EVENTDUMPER_JETS_H__
#define __EVENTDUMPER_JETS_H__

#include "IEventDumper.h"

//#include "TopMini.h"

class EventDumperJets : public IEventDumper< TopMini >
{
 public:
    EventDumperJets() {};
    virtual ~EventDumperJets() {};

 public: 
    virtual bool DumpEventJets( EventData * ed )
    {
       bool success = true;

  size_t alljet_n = GET_VALUE( jet_n );
    //size_t goodjet_n = 0;
    //size_t bjet_n = 0;
    //size_t ljet_n = 0;
    ed->jets.n  = 0;
    ed->bjets.n = 0;
    ed->ljets.n = 0;
    ed->fjets.n = 0;

    for( int j = 0; j < alljet_n; ++j ) {
        const double jet_pT   = GET_VALUE_ARRAY( jet_pt, j );
        const double jet_eta  = GET_VALUE_ARRAY( jet_eta, j );
        const double jet_phi  = GET_VALUE_ARRAY( jet_phi, j );
        const double jet_E    = GET_VALUE_ARRAY( jet_E, j );

        if( jet_pT > 25 * GeV && ( fabs(jet_eta) < 2.5) ) {

            ed->jets.n++;

            ed->jets.index.push_back( j );

            ed->jets.pT.push_back(  jet_pT );
            ed->jets.eta.push_back( jet_eta );
            ed->jets.phi.push_back( jet_phi );
            ed->jets.E.push_back(   jet_E );

            const double jet_m = PhysicsHelperFunctions::Mass( ed->jets, j );
            ed->jets.m.push_back( jet_m );

            ed->jets.property["jvf"].push_back(          GET_VALUE_ARRAY(jet_jvf, j)          );
            ed->jets.property["trueflav"].push_back(     GET_VALUE_ARRAY(jet_trueflav, j)     );
            ed->jets.property["truthMatched"].push_back( GET_VALUE_ARRAY(jet_truthMatched, j) );
            ed->jets.property["SV0"].push_back(          GET_VALUE_ARRAY(jet_SV0, j)          );
            ed->jets.property["COMBNN"].push_back(	 GET_VALUE_ARRAY(jet_COMBNN, j)       );
            ed->jets.property["MV1"].push_back(          GET_VALUE_ARRAY(jet_MV1, j)          );
            ed->jets.property["MV1c"].push_back(         GET_VALUE_ARRAY(jet_MV1c, j)         );
            ed->jets.property["isSemilep"].push_back(    GET_VALUE_ARRAY(jet_isSemilep, j)    );

            const double mv1 = GET_VALUE_ARRAY(jet_MV1, j);

            if( mv1 > 0.7892 ) {
                ed->bjets.n++;

                ed->bjets.pT.push_back( jet_pT );
                ed->bjets.eta.push_back( jet_eta );
                ed->bjets.phi.push_back( jet_phi );
                ed->bjets.E.push_back( jet_E );
                ed->bjets.m.push_back( jet_m );
                ed->bjets.index.push_back( j );
                ed->bjets.property["MV1"].push_back(mv1);
            } else {
                ed->ljets.n++;

                ed->ljets.pT.push_back( jet_pT );
                ed->ljets.eta.push_back( jet_eta );
                ed->ljets.phi.push_back( jet_phi );
                ed->ljets.E.push_back( jet_E );
                ed->ljets.m.push_back( jet_m );
                ed->ljets.index.push_back( j );
                ed->ljets.property["MV1"].push_back(mv1);
            }
	}

    }

  // fat jet collection
  size_t allfjet_n = GET_VALUE( fjet_n );

  for( int i = 0 ; i < allfjet_n ; ++i ) {
     const double fjet_pT      = GET_VALUE_ARRAY( fjet_pt, i );
     const double fjet_eta     = GET_VALUE_ARRAY( fjet_eta, i );
     const double fjet_phi     = GET_VALUE_ARRAY( fjet_phi, i );
     const double fjet_E       = GET_VALUE_ARRAY( fjet_E, i );
     const double fjet_m       = GET_VALUE_ARRAY( fjet_m, i );
     const double fjet_d12     = GET_VALUE_ARRAY( fjet_d12, i );
     const double fjet_dPhi_lj = GET_VALUE_ARRAY( fjet_DeltaPhi_Lap_FatJet, i );
     const double dR_lj        = GET_VALUE_ARRAY( fjet_DeltaR_LapJet_Fatjet, i );

     if( fjet_E <=  0. )        continue; // correctedE ?
     if( fjet_pT <= 300.*GeV )  continue;
     if( fjet_m  <= 100.*GeV )  continue;
     if( fjet_d12 <= 40.*GeV )  continue;
     if( fabs(fjet_eta) >= 2. ) continue;

     ed->fjets.n++;
     ed->fjets.index.push_back( i );

     ed->fjets.pT.push_back(  fjet_pT  );
     ed->fjets.eta.push_back( fjet_eta );
     ed->fjets.phi.push_back( fjet_phi );
     ed->fjets.E.push_back(   fjet_E   );
     ed->fjets.m.push_back(   fjet_m   );

     ed->fjets.d12.push_back(     fjet_d12     );
     ed->fjets.dPhi_lj.push_back( fjet_dPhi_lj );
     ed->fjets.dR_lj.push_back(   dR_lj        );

  }

  return success;

    };

 protected:

};


#endif /** __EVENTDUMPER_JETS_H__ */
