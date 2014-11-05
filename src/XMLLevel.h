/* 
 * File:   XMLLevel.h
 * Author: giannell
 *
 * Created on 31 October 2014, 10:52
 */

#ifndef XMLLEVEL_H
#define	XMLLEVEL_H

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "Commons.h"
#include "HelperFunctions.h"

class XMLLevel {
public:
    XMLLevel();
    XMLLevel(xmlNodePtr nodeType);
    XMLLevel(const XMLLevel& orig);
    virtual ~XMLLevel();
    
    string name;
    vector<string> inFolder;
    
private:

};

#endif	/* XMLLEVEL_H */

