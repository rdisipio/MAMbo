/* 
 * File:   XMLVariable.h
 * Author: Michele
 *
 * Created on 29 October 2014, 15:03
 */

#ifndef XMLVARIABLE_H
#define	XMLVARIABLE_H

#include "XMLBin.h"
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <stdio.h>
#include "Commons.h"

using namespace std;

class XMLVariable {
public:
    XMLVariable();
    XMLVariable(xmlNodePtr nodeVariable);    
    XMLVariable(const XMLVariable& orig);
    virtual ~XMLVariable();

    vector<XMLBin*> GetBinsInPath(string path);
    XMLBin* GetBinByIdInPath(int binId, string path);
    
    string name;
    string title;     
    vector<string> folders;
    vector<XMLBin*> bins;

private:
    void SetParticleFromNode(xmlNodePtr nodeVariable);
};

#endif	/* XMLVARIABLE_H */

