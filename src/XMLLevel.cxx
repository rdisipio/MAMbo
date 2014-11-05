/* 
 * File:   XMLLevel.cpp
 * Author: giannell
 * 
 * Created on 31 October 2014, 10:52
 */

#include "XMLLevel.h"

XMLLevel::XMLLevel() {
}

XMLLevel::XMLLevel(xmlNodePtr nodeType) {
    name = (string)((const char*)xmlGetProp( nodeType, BAD_CAST "name" ));

    const char* parentFolder = (const char*)xmlGetProp( nodeType, BAD_CAST "inFolder" );
    if(parentFolder != NULL){
        string allfolders = string(parentFolder); 
        HelperFunctions::Tokenize( allfolders, inFolder, "," );
    } 
}

XMLLevel::XMLLevel(const XMLLevel& orig) {
}

XMLLevel::~XMLLevel() {
}

