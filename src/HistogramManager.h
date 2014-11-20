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
#include "XMLVariable.h"
#include "XMLLevel.h"
#include <vector>

class HistogramManager 
{
 public:
  virtual ~HistogramManager();

  static HistogramManager * GetHandle();

 public:
  void BookHistograms( const xmlNodePtr xml );
  void Book1DHistogram( const string path, const xmlNodePtr xml );
  void Book2DHistogram( const string path, const xmlNodePtr xml );
  void BookMatrices( const string path, const xmlNodePtr xml );
  void MoveHistogramtToFolder( TH1* h, const string fullPath );

  void CreateAllMatricesForVariableAndBin(const string path, XMLVariable* variable, XMLBin* bin, string matrixNameSuffix);

  TH1F* Book1DHistogram( const string& name, const string& title, int nbins, Double_t xmin, Double_t xmax );
  TH1F* Book1DHistogram( const string& name, const string& title, int nbins, const vector<double>  xedges );
  
  TH2F* Book2DHistogram( const string& name, const string& title, int nbinsx, Double_t xmin, Double_t xmax, int nbinsy, Double_t ymin, Double_t ymax );
  TH2F* Book2DHistogram( const string& name, const string& title, int nbinsx, const vector<double>  xedges, int nbinsy, vector<double>  yedges );

  TFile * SetOutFileName( const char * name );

  bool   ConfigureFromXML( const string& fileName );

  TDirectory * CreatePath( const string& path);

  inline TH1 * GetHistogram( const string& name ) { return (TH1*)m_outFile->Get( name.c_str() ); };
  inline TH2F * Get2DHistogram( const string& name ) { return (TH2F*)m_outFile->Get( name.c_str() ); };
  inline void  ToggleSumW2() { m_sumw2 = !m_sumw2; };

  void WriteToFile();  
  void FillHistograms(string fullPath, double value, double weight);
  void FillMatrices(string fullPath, double valuex, double valuey, double weight);
  
  void Book1DHistogramInFolder(string path, const string& name, const string& title, int nbins, Double_t xmin, Double_t xmax );

public:
  inline TH1 * operator[]( const string& name ) { return GetHistogram( name ); };

   
 protected:
  HistogramManager();

 protected:
  TFile                  * m_outFile;
  StringVector_t           m_h1_names;
  StringVector_t           m_h2_names;
  HistogramCollection_t    m_histograms;
  vector<XMLVariable*>     variables;
  vector<vector<XMLLevel*> > *pathNames;
  TDirectory*              currentDir;
  bool                     m_sumw2;
  
private :
  vector<XMLLevel*> FillLevelNames(xmlNodePtr nodeType);
  bool VariableNameAndFolderCondition(XMLVariable* variable, string variableName, string path);
  bool FolderCondition(vector<string> folders, string path);
  bool IsParentInFolderList(string parentName, vector<string> list);
};


#endif /** __HISTOGRAMMANAGER_H__ */


// Local Variables:
// mode: c++
// End:
