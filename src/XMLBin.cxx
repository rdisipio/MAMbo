/* 
 * File:   XMLBin.cpp
 * Author: Michele
 * 
 * Created on 29 October 2014, 14:46
 */

#include "XMLBin.h"

XMLBin::XMLBin() {
    min = -1;
    max = -1;
    edges = vector<double>();
    nBins = 0;
    id = -1;
    particle = "";
}

XMLBin::XMLBin(xmlNodePtr nodeBin){
    SetIdFromNode(nodeBin);
    SetParticleFromNode(nodeBin);      
    nBins = atoi( (const char*) xmlGetProp( nodeBin, BAD_CAST "nbins" ) );
    
    if( xmlHasProp( nodeBin, BAD_CAST "edges" ) ) {

      string s( (const char*)xmlGetProp( nodeBin, BAD_CAST "edges" ) );
      StringVector_t tokens;
      size_t Nedges = HelperFunctions::Tokenize( s, tokens, "," );

      for( int n = 0 ; n < Nedges ; ++n ) {
        edges.push_back(atof( tokens.at(n).c_str() ));
      }

    }
    else {
      min = atof( (const char*) xmlGetProp( nodeBin, BAD_CAST "xmin" ) );
      max = atof( (const char*) xmlGetProp( nodeBin, BAD_CAST "xmax" ) );
    }
}

XMLBin::XMLBin(int id, int nBins, vector<double> edges){
    this->id = id;
    this->nBins = nBins;
    this->edges = edges;
}

XMLBin::XMLBin(int id, int nBins, double min, double max){
    this->id = id;
    this->nBins = nBins;
    this->min = min;
    this->max = max;
}

XMLBin::XMLBin(const XMLBin& orig) {
}

XMLBin::~XMLBin() {
}

void XMLBin::SetIdFromNode(xmlNodePtr nodeBin){
    const char* idChar = (const char*) xmlGetProp( nodeBin, BAD_CAST "id" );
    
    if (idChar != NULL){
        id = atoi(idChar);
    }
    else{
        id = 0;
    }
}

void XMLBin::SetParticleFromNode(xmlNodePtr nodeBin){
    const char* particleType = (const char*) xmlGetProp( nodeBin, BAD_CAST "particle" );
    
    if (particleType != NULL) {
        particle  = string(particleType);
    }
}
