#ifndef __HISTOGRAMMANAGER_H__
#define __HISTOGRAMMANAGER_H__

#include "Commons.h"

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TDirectory.h>

#include "HelperFunctions.h"

class HistogramManager 
{
 public:
  virtual ~HistogramManager();

  static HistogramManager * GetHandle();

 public:
  TH1F * Book1DHistogram( TH1F * h, const string& path = "" );
  TH1F * Book1DHistogram( const string& path, const string& title, int nbins, Double_t xmin, Double_t xmax );
  TH1F * Book1DHistogram( const string& path, const string& title, int nbins, const Double_t* xedges );
  TH1F * Book1DHistogram( const xmlNodePtr xml );

  TH2F * Book2DHistogram( const xmlNodePtr xml );

  TFile * SetOutFileName( const char * name );

  bool   ConfigureFromXML( const string& fileName );

  TDirectory * CreatePath( const string& path, bool lastIsHistogramName = false );

  inline TH1 * GetHistogram( const string& name ) { return (TH1*)m_outFile->Get( name.c_str() ); };

  inline void  ToggleSumW2() { m_sumw2 = !m_sumw2; };

  void WriteToFile();

 public:
  inline TH1 * operator[]( const string& name ) { return GetHistogram( name ); };

   
 protected:
  HistogramManager();

 protected:
  TFile                  * m_outFile;
  StringVector_t           m_h1_names;
  StringVector_t           m_h2_names;
  HistogramCollection_t    m_histograms;

  bool                     m_sumw2;
};


#endif /** __HISTOGRAMMANAGER_H__ */


// Local Variables:
// mode: c++
// End:
