#include "HistogramManager.h"

HistogramManager::HistogramManager() :
  m_sumw2( false )
{

}


HistogramManager::~HistogramManager()
{
  /*
  for( StringVector_t::const_iterator itr = m_h1_names.begin() ; itr != m_h1_names.end() ; ++itr ) {
    TH1F * h = (TH1F*)m_histograms[*itr];
    delete h;
  }
  */
  m_histograms.clear();
}


/////////////////////////////////////////


HistogramManager * HistogramManager::GetHandle()
{
  static HistogramManager instance;
  
  return &instance;
}


/////////////////////////////////////////



TFile * HistogramManager::SetOutFileName( const char * name )
{
  m_outFile = TFile::Open( name, "recreate" );

  if( m_outFile ) {
    cout << "INFO: HistogramManager: output file created: " << name << endl;
  }
  else throw runtime_error( "HistogramManager: Cannot open output file" );

  return m_outFile;
}


/////////////////////////////////////////


TH1F * HistogramManager::Book1DHistogram( TH1F * h, const string& path )
{
  TDirectory * hdir = CreatePath( path, true );

  hdir->cd();
  //cout << "DEBUG: create h: current dir " << gDirectory->GetPath() << endl;

  m_histograms[path] = (TH1F*)h->Clone();
  m_histograms[path]->SetDirectory( hdir );

  if( m_sumw2 ) m_histograms[path]->Sumw2();

  m_h1_names.push_back( path );
  cout << "DEBUG: Created histogram " << path << endl;

  return (TH1F*)m_histograms[path];
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


TH1F * HistogramManager::Book1DHistogram( const string& path, const string& title, int nbins, Double_t xmin, Double_t xmax )
{
  size_t found      = path.find_last_of("/");
  const string name = path.substr( found+1 );

  TH1F h( name.c_str(), title.c_str(), nbins, xmin, xmax );

  return Book1DHistogram( &h, path );
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


TH1F * HistogramManager::Book1DHistogram( const string& path, const string& title, int nbins, const Double_t* xedges )
{
  size_t found      = path.find_last_of("/");
  const string name = path.substr( found+1 );

  TH1F h( name.c_str(), title.c_str(), nbins, xedges );

  return Book1DHistogram( &h, path );
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


TH1F * HistogramManager::Book1DHistogram( const xmlNodePtr xml )
{
  const char * path  = (const char*) xmlGetProp( xml, BAD_CAST "name" );
  const char * title = (const char*) xmlGetProp( xml, BAD_CAST "title" );
  const int    nbins = atoi( (const char*) xmlGetProp( xml, BAD_CAST "nbins" ) );

  if( xmlHasProp( xml, BAD_CAST "edges" ) ) {
    
    string s( (const char*)xmlGetProp( xml, BAD_CAST "edges" ) );
    StringVector_t tokens;
    size_t Nedges = HelperFunctions::Tokenize( s, tokens, "," );

    Double_t edges[Nedges+1];
    for( int n = 0 ; n < Nedges ; ++n ) {
      edges[n] = atof( tokens.at(n).c_str() );
    }

    return Book1DHistogram( path, title, nbins, edges );
  }
  else {
    Double_t xmin = atof( (const char*) xmlGetProp( xml, BAD_CAST "xmin" ) );
    Double_t xmax = atof( (const char*) xmlGetProp( xml, BAD_CAST "xmax" ) );

    return Book1DHistogram( path, title, nbins, xmin, xmax );
  }

}


/////////////////////////////////////////


TH2F * HistogramManager::Book2DHistogram( const xmlNodePtr xml )
{
  return NULL;
}


/////////////////////////////////////////


TDirectory * HistogramManager::CreatePath( const string& path, bool lastIsHistogramName )
{
  StringVector_t dirs;
  HelperFunctions::Tokenize( path, dirs, "/" );
  
  if( lastIsHistogramName ) {
    dirs.erase( dirs.end() ); 
  }

  m_outFile->cd();

  for( StringVector_t::const_iterator itr = dirs.begin() ; itr != dirs.end() ; ++itr ) {
    if( itr->empty() ) continue;

    const char * nextDirName = (*itr).c_str();

    TDirectory * nextDir = (TDirectory*)gDirectory->Get( nextDirName );
    if( !nextDir ) {
      gDirectory->mkdir( nextDirName );

      //cout << "INFO: Created ROOT dir: " << nextDirName << " | path = " << gDirectory->GetPath() << endl;      
    }
    
    gDirectory->cd( nextDirName );
  }

  return gDirectory;
}


/////////////////////////////////////////


void HistogramManager::WriteToFile()
{
  m_outFile->Write();
  m_outFile->Close();
}


/////////////////////////////////////////


bool HistogramManager::ConfigureFromXML( const string& fileName )
{
  bool success = true;

  xmlDocPtr doc;
  xmlNodePtr nodeRoot;
  xmlNodePtr nodeHisto;

  //unsigned int N1DHistograms = 0;
  //unsigned int N2DHistograms = 0;

  doc = xmlParseFile( fileName.c_str() );

  for( nodeRoot = doc->children; nodeRoot != NULL; nodeRoot = nodeRoot->next) {
    for( nodeHisto = nodeRoot->children; nodeHisto != NULL; nodeHisto = nodeHisto->next ) {
      if( xmlStrEqual( nodeHisto->name, BAD_CAST "TH1F" ) ) {
	Book1DHistogram( nodeHisto );
      }
      else if( xmlStrEqual( nodeHisto->name, BAD_CAST "TH2F" ) ) {
	Book2DHistogram( nodeHisto );
      }
      else continue;
    }
  }

  xmlFreeDoc( doc );
  return success;
}
