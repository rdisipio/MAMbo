#include "MoMA.h"

MoMATool::MoMATool() :
  m_debug(false)/*, m_fakes_weighter_el( NULL ), m_fakes_weighter_mu( NULL ), 
  m_btag_weighter( NULL ), m_CDIindex_SF(NULL), m_CDIindex_Eff(NULL)*/
{
  InitializeLumiWeights();
}


//////////////////////////////////////////

/*
void MoMATool::InitializeBTagWeights()
{
   const string mamboDir = getenv( "MAMBODIR" );

   BTagType btag_type = MV1_70;
//   m_btag_weighter = new Analysis::CalibrationDataInterfaceROOT( "MV1", dataDir + "/data/TopD3PDCorrections/BTagCalibration.env" );
   m_btag_weighter = new Analysis::CalibrationDataInterfaceROOT( "MV1", mamboDir + "/share/BTagCalibration.env" );

   m_CDIindex_SF  = new unsigned int[4];
   m_CDIindex_Eff = new unsigned int[4];

   for (int i=0; i<4; i++) {
     m_CDIindex_SF[i]=999;
     m_CDIindex_Eff[i]=999;
   }
   unsigned int mapIndex = 0;
   string workingPoint = "0_7892"; // 70%
   string jetAuthor    = "AntiKt4TopoLCJVF0_5";
   m_btag_weighter->retrieveCalibrationIndex( "B"    , workingPoint.c_str(), jetAuthor, true, m_CDIindex_SF[0], mapIndex);
   m_btag_weighter->retrieveCalibrationIndex( "C"    , workingPoint.c_str(), jetAuthor, true, m_CDIindex_SF[1], mapIndex);
   m_btag_weighter->retrieveCalibrationIndex( "Light", workingPoint.c_str(), jetAuthor, true, m_CDIindex_SF[2], mapIndex);
   m_btag_weighter->retrieveCalibrationIndex( "T"    , workingPoint.c_str(), jetAuthor, true, m_CDIindex_SF[3], mapIndex);
   m_btag_weighter->retrieveCalibrationIndex( "B"    , workingPoint.c_str(), jetAuthor, false, m_CDIindex_Eff[0], mapIndex);
   m_btag_weighter->retrieveCalibrationIndex( "C"    , workingPoint.c_str(), jetAuthor, false, m_CDIindex_Eff[1], mapIndex);
   m_btag_weighter->retrieveCalibrationIndex( "Light", workingPoint.c_str(), jetAuthor, false, m_CDIindex_Eff[2], mapIndex);
   m_btag_weighter->retrieveCalibrationIndex( "T"    , workingPoint.c_str(), jetAuthor, false, m_CDIindex_Eff[3], mapIndex);

   // as-is from https://lost-contact.mit.edu/afs/cern.ch/atlas/software/ASG/builds/AnalysisTop/1.5.0/TopD3PDCorrections/Root/BTagScale.cxx
   int tauExtrapFromCharm = -1;

   std::vector<std::string> names = m_btag_weighter->listScaleFactorUncertainties( jetAuthor, "T", workingPoint.c_str(), true );
   for (unsigned int i = 0; i < names.size(); i++) {
      if (names[i] == "extrapolation from charm") {
         tauExtrapFromCharm = (int)i;
         break;
      }
   }
   if (tauExtrapFromCharm == -1) {
      std::cerr << "ERROR! Could not find number for extrapolation from charm uncertainty" << std::endl;
   }
   else {
      std::cerr << "Found extrapolation from charm parameter = " << tauExtrapFromCharm << endl;
   }
  
}
*/
/////


void MoMATool::InitializeLumiWeights()
{
	string rootcoreDir = string( getenv("ROOTCOREBIN") ) + "/data/TopDataPreparation/XSection-MC15-13TeV-fromSusyGrp.data";
	m_lumiSvc = SampleXsectionSvc::svc( rootcoreDir.c_str());
	m_lumiWeight = -1;
	m_lumiRunNumber = -1;
}

double MoMATool::GetLumiWeight( int runNumber, float nEvents, float lumi )
{
	if( m_lumiWeight < 0 || m_lumiRunNumber != runNumber )
	{
		m_lumiRunNumber = runNumber;
		double xs;
		if( m_xs_syst_type == XS_NOMINAL ) xs = m_lumiSvc->sampleXsection()->getXsection(runNumber);
		else if( m_xs_syst_type == XS_UP ) xs = m_lumiSvc->sampleXsection()->getXsectionUp( runNumber );
		else xs = m_lumiSvc->sampleXsection()->getXsectionDown( runNumber );
                double kFactor =  m_lumiSvc->sampleXsection()->getKfactor( runNumber );
		double lumiGen = nEvents / ( xs );
		cout << "Debug: double MoMATool::GetLumiWeight for run " << runNumber << ": xs = " << xs << ", kfactor = " << kFactor << " lumi " << lumi << ", nEvents " << nEvents << " lumigen " << lumiGen << endl;
		m_lumiWeight = lumi / lumiGen;
	}
	return m_lumiWeight;
}



MoMATool::~MoMATool()
{
  //delete m_fakes_weighter_el;
//  delete m_fakes_weighter_mu;

  //delete m_btag_weighter;
  //delete m_CDIindex_SF;
 // delete m_CDIindex_Eff;
  
  //delete m_lumiSvc;
  
}


///////////////////////////////////////////


MoMATool * MoMATool::GetHandle()
{
   static MoMATool instance;

   return &instance;
}


///////////////////////////////////////////



///////////////////////////////////////////

/*
double MoMATool::GetFakesWeight( int channel, const MMEvent& event, const MMLepton& lepton, bool tight )
{
  double w = 1.;
  double R = -666;
  double F = -666;

  if( !m_fakes_weighter_el) InitializeFakesWeights();

  if( channel == FakesWeights::EJETS ) {
    m_fakes_weighter_el->SetLepton( event, lepton );
    w = m_fakes_weighter_el->GetFakesWeightLJets( tight );
   
    if( m_debug ) {
       R = m_fakes_weighter_el->GetRealEff();
       F = m_fakes_weighter_el->GetFakeEff();
    }
  }
  else if( channel == FakesWeights::MUJETS ) {
    m_fakes_weighter_mu->SetLepton( event, lepton );
    w = m_fakes_weighter_mu->GetFakesWeightLJets( tight );
 
    if( m_debug ) {
       R = m_fakes_weighter_mu->GetRealEff();
       F = m_fakes_weighter_mu->GetFakeEff();
    }
  }
  else {
    throw runtime_error( "MoMA::FakesWeights: Invalid channel\n" );
  }

  if( m_debug )  cout << "DEBUG: r = " << R << " f = " << F << " w = " << w << endl;
  
  return w;
}

*/
///////////////////////////////////////////



/*
double MoMATool::GetBTagWeight( EventData * ed, const double mv1_cut, SYSTEMATIC_TYPE syst_type ) const
{
   if( !ed ) throw runtime_error( "MoMA::GetBTagWeight(): Invalid pointer to event data.\n" );

   double weight = 1.;

   Analysis::CalibrationDataVariables btag_vars;
   btag_vars.jetAuthor = "AntiKt4TopoLCJVF0_5";

   Analysis::Uncertainty u = Analysis::None;
   if( syst_type==BTAGSFUP || syst_type==BTAGSFDOWN || syst_type==CTAUTAGSFUP || syst_type==CTAUTAGSFDOWN || syst_type==MISTAGSFUP || syst_type==MISTAGSFDOWN ) u = Analysis::Total;
   Analysis::CalibResult res;

   for( int j = 0 ; j < ed->jets.n ; ++j ) {
     btag_vars.jetPt  = ed->jets.pT.at( j ); // MeV
     btag_vars.jetEta = ed->jets.eta.at( j );
  
     if( fabs( btag_vars.jetEta ) > 2.5 ) continue;
     if( btag_vars.jetPt <= 20*GeV ) continue;

     int typeIndex = -1;
     const int jLabel = ed->jets.property["trueflav"].at(j); 
     switch( jLabel ) {
        case 5:
           typeIndex = 0; break; // ugly ordering! see above from when CDIindex are set up
        case 4:
           typeIndex = 1; break;
        case 15:
           typeIndex = 3; break;
        default:
           typeIndex = 2; break;
     } 

     double mv1 = ed->jets.property["MV1"].at( j );
     bool tagged = ( mv1 > mv1_cut ) ? true : false;

//     int varIndex = 0; // for systematics. todo

     if( tagged ) {
       res = m_btag_weighter->getScaleFactor( btag_vars, m_CDIindex_SF[typeIndex], m_CDIindex_Eff[typeIndex], u ); //, varIndex );
     } 
     else {
       res = m_btag_weighter->getInefficiencyScaleFactor( btag_vars, m_CDIindex_SF[typeIndex], m_CDIindex_Eff[typeIndex], u ); //, varIndex );
     }
     double jetWeight = res.first;

     if( u==Analysis::Total ) {
           if ( (syst_type==BTAGSFUP   && jLabel==5) ||
                (syst_type==CTAUTAGSFUP   && jLabel==4) ||
                (syst_type==CTAUTAGSFUP && jLabel==15) ||
                (syst_type==MISTAGSFUP && jLabel==0 )) {
              if (tagged) jetWeight=res.first+res.second;
              else        jetWeight=res.first-res.second;
           } // up type
           if ( (syst_type==BTAGSFDOWN   && jLabel==5) ||
                (syst_type==CTAUTAGSFDOWN   && jLabel==4) ||
                (syst_type==CTAUTAGSFDOWN && jLabel==15) ||
                (syst_type==MISTAGSFDOWN && jLabel==0) ) {
              if (tagged) jetWeight=res.first-res.second;
              else        jetWeight=res.first+res.second;
           } // down type

           //protecting SF for sys variations
           Analysis::CalibResult eff;
           if (tagged) eff = m_btag_weighter->getMCEfficiency( btag_vars, m_CDIindex_Eff[typeIndex], u);
           else        eff = m_btag_weighter->getMCInefficiency( btag_vars, m_CDIindex_Eff[typeIndex], u);
           double EffMC = eff.first;
           if      (jetWeight*EffMC>1.) jetWeight = 1./EffMC;
           else if (jetWeight*EffMC<0.) jetWeight = 0.;
 
           if( jLabel == 15 && !tagged ) { // ugly tau inefficiency again
             Analysis::CalibResult tempRes;
             tempRes = m_btag_weighter->getScaleFactor( btag_vars, m_CDIindex_SF[typeIndex], m_CDIindex_Eff[typeIndex], u );
            float tausf = tempRes.first;
            tempRes = m_btag_weighter->getMCEfficiency( btag_vars, m_CDIindex_Eff[typeIndex], u );
            float mceff = tempRes.first;
            jetWeight = ( 1 - tausf*mceff ) / ( 1 - mceff );
         } 


     }


     weight *= jetWeight;
   }

   return weight;
}*/
