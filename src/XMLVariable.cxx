/* 
 * File:   XMLVariable.cpp
 * Author: Michele
 * 
 * Created on 29 October 2014, 15:03
 */

#include "XMLVariable.h"
#include "Commons.h"

template<class XMLBin>
class HasElement {
    int _id;
    string _path;
public:
    HasElement(int id, string particleType) : _id(id), _path(particleType) {}
    bool operator()(XMLBin* o) const {
        return (_id < 0 || o->id == _id) && (o->particle == "" || (o->particle != "" && _path.find(o->particle)!=string::npos));
    }
};

XMLVariable::XMLVariable() {
    //bins = vector<XMLBin>();
}

XMLVariable::XMLVariable(xmlNodePtr nodeVariable) {
    name  = string((const char*) xmlGetProp( nodeVariable, BAD_CAST "name" ));
    title = string((const char*) xmlGetProp( nodeVariable, BAD_CAST "title" )); 
    SetParticleFromNode(nodeVariable);    

    for(xmlNodePtr nodeBin = nodeVariable->children; nodeBin != NULL; nodeBin = nodeBin->next ) {
        if( xmlStrEqual( nodeBin->name, BAD_CAST "Bin" ) ) { 
            bins.push_back(new XMLBin(nodeBin));
        }
     }
}

XMLVariable::XMLVariable(const XMLVariable& orig) {
}

XMLVariable::~XMLVariable() {
}

vector<XMLBin*> XMLVariable::GetBinsInPath(string path){
    vector<XMLBin*> result;
    std::copy_if(bins.begin(), bins.end(), back_inserter(result), HasElement<XMLBin>(-1, path));

    return result;
}

XMLBin* XMLVariable::GetBinByIdInPath(int id, string path){
    
    vector<XMLBin*>::iterator matched = std::find_if(bins.begin(), bins.end(), HasElement<XMLBin>(id, path));

    if (matched < bins.end())
        return *matched;
    else {
        return NULL;
    }

}

void XMLVariable::SetParticleFromNode(xmlNodePtr nodeVariable){
    const char* inFolder = (const char*) xmlGetProp( nodeVariable, BAD_CAST "folder" );
    
    if (inFolder != NULL) {
        string allfolders = string(inFolder);
        HelperFunctions::Tokenize( allfolders, folders, "," );
    }
}