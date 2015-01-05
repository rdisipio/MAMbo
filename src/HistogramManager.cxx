#include "HistogramManager.h"

HistogramManager::HistogramManager() :
  m_sumw2( true )
{
    pathNames = new vector< vector< XMLLevel* > >();
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

void HistogramManager::MoveHistogramtToFolder( TH1* h, const string fullPath )
{
    //cout << "DEBUG: create h: "<< h->GetName() << " in dir " << gDirectory->GetPath() << endl;
    if( m_sumw2 ) h->Sumw2();
    h->SetDirectory( currentDir );
    m_histograms[fullPath].push_back(h);  
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


ROOT_TH1_t* HistogramManager::Book1DHistogram( const string& name, const string& title, int nbins, Double_t xmin, Double_t xmax )
{
    return new ROOT_TH1_t( name.c_str(), title.c_str(), nbins, xmin, xmax );
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


ROOT_TH1_t* HistogramManager::Book1DHistogram( const string& name, const string& title, int nbins, const vector<double> xedges )
{
    return new ROOT_TH1_t( name.c_str(), title.c_str(), nbins, &xedges[0] );
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool HistogramManager::IsParentInFolderList(string parentName, vector<string> list){
    for (string s : list ){
        if( s.compare(parentName) == 0){
            return true;
        }
    }
    
    return false;
}

void HistogramManager::BookHistograms( const xmlNodePtr xml )
{  
    for (XMLLevel* path1 : pathNames->at(0)){        
        for (XMLLevel* path2 : pathNames->at(1)){
            if (path2->inFolder.empty() || IsParentInFolderList(path1->name, path2->inFolder)) {
                for (XMLLevel* path3 : pathNames->at(2)){
                    if (path3->inFolder.empty() || IsParentInFolderList(path2->name, path3->inFolder)) {                    
                        string path = path1->name + "/" + path2->name + "/" + path3->name;                        
                        currentDir = CreatePath( path );                        
                       
                        if( xmlStrEqual( xml->name, BAD_CAST "TH1F" ) ) {
                            Book1DHistogram(path, xml);
                        }
                        else if( xmlStrEqual( xml->name, BAD_CAST "TH2F" ) ) {
			  cout << "Booking 2D histos for path " << path.c_str() << endl;
			  Book2DHistogram(path, xml );
                        }
                        else if( xmlStrEqual( xml->name, BAD_CAST "Matrix" ) ) {
                            BookMatrices(path, xml );
                        }
                    }
                }
            }
        }
    }
}

void HistogramManager::Book1DHistogram( const string path, const xmlNodePtr xml )
{
    const string variableName = string((const char*) xmlGetProp( xml, BAD_CAST "variable" ));

    for (XMLVariable* variable : variables){
        if (VariableNameAndFolderCondition(variable, variableName, path)){
            vector<XMLBin*> bins = variable->GetBinsInPath(path); 
            for (XMLBin* bin : bins){
                //cout<<"Booking histo: " << path << "/" << variable->name << endl;
                
                string plotName = variable->name;
		if (bins.size() > 1 && bin->id > 0) {
                    plotName += "_" + std::to_string(bin->id);
                }
                
                ROOT_TH1_t* h;
                if (bin->edges.size() > 0){
                    h = Book1DHistogram( plotName, variable->title, bin->nBins, bin->edges);
                }
                else {
                    h = Book1DHistogram( plotName, variable->title, bin->nBins, bin->min, bin->max);
                }
                
                MoveHistogramtToFolder(h, path+"/"+variable->name);
            }            
        }
    }    
}

bool HistogramManager::VariableNameAndFolderCondition(XMLVariable* variable, string variableName, string path){
    bool nameCondition = variable->name.compare(variableName) == 0 ;
    bool folderCondition = variable->folders.size() == 0 || FolderCondition(variable->folders, path);
    return nameCondition && folderCondition;
}

bool HistogramManager::FolderCondition(vector<string> folders, string path){
    for (string folder : folders){
        if (path.find(folder)==string::npos){
            return false;
        }
    }
    return true;
}

void HistogramManager::Book2DHistogram(const string path, const xmlNodePtr xml )
{
    const int binIdX = atoi( (const char*) xmlGetProp( xml, BAD_CAST "binIdX" ) );
    const int binIdY = atoi( (const char*) xmlGetProp( xml, BAD_CAST "binIdY" ) );
    const string variableNameX = string((const char*) xmlGetProp( xml, BAD_CAST "variableX" ));
    const string variableNameY = string((const char*) xmlGetProp( xml, BAD_CAST "variableY" ));
        
    string plotName =  variableNameY + "_vs_" + variableNameX;
    string plotTitle =  variableNameY + " vs "+  variableNameX;

    XMLBin *binX, *binY;
    bool useEdges;
    
    for (XMLVariable* variable : variables){
        if (VariableNameAndFolderCondition(variable, variableNameX, path)){
            binX = variable->GetBinByIdInPath(binIdX, path);
	    cout << "  HistogramManager::Book2DHistogram got binX @ " << binX  << endl;
	    cout << "  HistogramManager::Book2DHistogram got binX n=" << binX->edges.size() << endl;
            if (binX->edges.size() > 0){
                useEdges = true;
            }
        }
        if (VariableNameAndFolderCondition(variable, variableNameY, path)){
            binY = variable->GetBinByIdInPath(binIdY, path);
	    cout << "  HistogramManager::Book2DHistogram got binY @ " << binY  << endl;
	    cout << "  HistogramManager::Book2DHistogram got binY n=" << binY->edges.size() << endl;
        }
    }    
    
    string plotNameWithBin = plotName;
    if ( (binX != NULL && binX->id > 0) || (binY != NULL && binY->id > 0) ) {
       plotNameWithBin += "_" + std::to_string(binX->id) + "_" + std::to_string(binY->id);
    }   

    ROOT_TH2_t*  h;
    cout << "  HistogramManager::Book2DHistogram: Booking " << plotNameWithBin.c_str() << endl;
    if (binX != NULL && binY != NULL) {
      if (useEdges)
        h = Book2DHistogram( plotNameWithBin, plotTitle, binX->nBins, binX->edges, binY->nBins, binY->edges);
      else 
        h = Book2DHistogram( plotNameWithBin, plotTitle, binX->nBins, binX->min, binX->max , binY->nBins, binY->min, binY->max );
      cout << "  HistogramManager::Book2DHistogram: Booked!" << endl;
      MoveHistogramtToFolder(h, path+"/"+plotName);
      cout << "  HistogramManager::Book2DHistogram: Moved!" << endl;
    }
}

void HistogramManager::BookMatrices(const string path, const xmlNodePtr xml )
{
    const string variableName = string((const char*) xmlGetProp( xml, BAD_CAST "variable" ));

    for (XMLVariable* variable : variables){
        if (VariableNameAndFolderCondition(variable, variableName, path)){
            vector<XMLBin*> bins = variable->GetBinsInPath(path);
            for (XMLBin* bin : bins){
                string matrixNameSuffix = "";
                if (bins.size() > 1 && bin->id > 0) {
                    matrixNameSuffix += "_" + std::to_string(bin->id);
                }  
                                
                CreateAllMatricesForVariableAndBin(path, variable, bin, matrixNameSuffix);
            }
        }
    }    
}

void HistogramManager::CreateAllMatricesForVariableAndBin(const string path, XMLVariable* variable, XMLBin* bin, string matrixNameSuffix){
    StringVector_t dirs;
    HelperFunctions::Tokenize( path, dirs, "/" );
  
    string currentLevel = dirs[0];
  
    for (XMLLevel* level : pathNames->at(0)) {
        if (level->name.compare(currentLevel) != 0){
            string matrixName = "Matrix_" + currentLevel + "_" + level->name + "_" + variable->name;
            string matrixTitle = "Matrix " + currentLevel + "/" + level->name + " " + variable->title + ";" + currentLevel + " " + variable->title + ";" + level->name + " " + variable->title; // JK

            string matrixNameWithBin = matrixName + matrixNameSuffix;

            ROOT_TH2_t* h;
            if (bin->edges.size() > 0){
                h = Book2DHistogram( matrixNameWithBin, matrixTitle, bin->nBins, bin->edges, bin->nBins, bin->edges);
            }
            else {
                h = Book2DHistogram( matrixNameWithBin, matrixTitle, bin->nBins, bin->min, bin->max, bin->nBins, bin->min, bin->max);
            }
            
            MoveHistogramtToFolder(h, path+"/"+matrixName);
        }
    }
}

/////////////////////////////////////////


ROOT_TH2_t* HistogramManager::Book2DHistogram( const string& name, const string& title, int nbinsx, Double_t xmin, Double_t xmax, int nbinsy, Double_t ymin, Double_t ymax )
{
    return new ROOT_TH2_t( name.c_str(), title.c_str(), nbinsx, xmin, xmax, nbinsy, ymin, ymax );
}


/////////////////////////////////////////


ROOT_TH2_t* HistogramManager::Book2DHistogram( const string& name, const string& title, int nbinsx, const vector<double>  xedges, int nbinsy, vector<double>  yedges )
{
    return new ROOT_TH2_t( name.c_str(), title.c_str(), nbinsx, &xedges[0], nbinsy, &yedges[0] );
}


/////////////////////////////////////////


TDirectory * HistogramManager::CreatePath( const string& path )
{
  StringVector_t dirs;
  HelperFunctions::Tokenize( path, dirs, "/" );
  
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
  cout<<"Open Histogram configuration file " << fileName << endl;
    
  bool success = true;

  xmlDocPtr doc = xmlParseFile( fileName.c_str() );

  for( xmlNodePtr nodeRoot = doc->children; nodeRoot != NULL; nodeRoot = nodeRoot->next) {
      for( xmlNodePtr nodeLevel = nodeRoot->children; nodeLevel != NULL; nodeLevel = nodeLevel->next ) {
        if (xmlStrEqual( nodeLevel->name, BAD_CAST "Level" )) {
            pathNames->push_back(FillLevelNames(nodeLevel));
        }      
        else if (xmlStrEqual( nodeLevel->name, BAD_CAST "Variables" )) {
            for( xmlNodePtr nodeVariable = nodeLevel->children; nodeVariable != NULL; nodeVariable = nodeVariable->next ) {
                if( xmlStrEqual( nodeVariable->name, BAD_CAST "Variable" ) ) {
                    XMLVariable* variable = new XMLVariable(nodeVariable);    
                    variables.push_back(variable);
                    //cout<<"Variables filled: "<< variables[variables.size() -1]->name << " " << variable->title << endl;
                }          
            }            
        }      
        else if (xmlStrEqual( nodeLevel->name, BAD_CAST "Histos" )) {
            for( xmlNodePtr nodeHisto = nodeLevel->children; nodeHisto != NULL; nodeHisto = nodeHisto->next ) {
                BookHistograms(nodeHisto);
            }          
        }      
        else continue;
      }
  }

  xmlFreeDoc( doc );
  return success;
}

vector<XMLLevel*> HistogramManager::FillLevelNames(xmlNodePtr nodeLevel){
    vector<XMLLevel*> v;
    for( xmlNodePtr nodeType = nodeLevel->children; nodeType != NULL; nodeType = nodeType->next ) {
        if( xmlStrEqual( nodeType->name, BAD_CAST "Type" ) ) {
            v.push_back(new XMLLevel(nodeType));
        }   
    }
    
    return v;
}

void HistogramManager::FillHistograms(string fullPath, double value, double weight){
    for (TH1* h : m_histograms[fullPath]){
        if (h != NULL){
            h->Fill( value, weight );
        }
        else{
            cout<< "WARNING: histogram in path: " << fullPath << " was NULL" << endl;
        }
    }
    if (m_histograms[fullPath].size() == 0){
        cout<< "WARNING: no histogram for path: " << fullPath << " was NULL" << endl;        
    }
}


void HistogramManager::FillMatrices(string fullPath, double valuex, double valuey, double weight){
    for (TH1* h : m_histograms[fullPath]){
        if (h != NULL){
            ((ROOT_TH2_t*) h)->Fill( valuex, valuey, weight );
        }
        else{
            cout<< "WARNING: histogram in path: " << fullPath << " was NULL" << endl;
        }
    }
    if (m_histograms[fullPath].size() == 0){
        cout<< "WARNING: no histogram for path: " << fullPath << " was NULL" << endl;        
    }
}

void HistogramManager::Book1DHistogramInFolder(string path, const string& name, const string& title, int nbins, Double_t xmin, Double_t xmax ){
    currentDir = CreatePath( path );
    currentDir->cd();
    Book1DHistogram(name, title, nbins, xmin, xmax);
}

void HistogramManager::WriteHistosToXML(string outputFileName){
    string xml;
    xml = "<histograms>\n";
    for (auto& pair : m_histograms){
        string histoLineBase = "<histogram hpath=\"" + pair.first + "/";
        for(auto& h : pair.second) {            
            string histoLine = histoLineBase;
            // The key contains an additional "path" that is used to loop over same type histos which do not exists and need to be removed.
            int pos = histoLine.find(((TH1*)h)->GetDirectory()->GetName()); 
            histoLine.erase(pos + strlen(((TH1*)h)->GetDirectory()->GetName()) + 1 , histoLine.size()); // +1 to keep the last / 
            histoLine += ((TH1*)h)->GetName();
            histoLine += "\" />\n";
            xml += histoLine;
        }
    }
    xml += "</histograms>";
    
    std::ofstream out(outputFileName);
    out << xml;
    out.close();
}
