/* 
 * File:   XMLBin.h
 * Author: Michele
 *
 * Created on 29 October 2014, 14:46
 */

#ifndef XMLBIN_H
#define	XMLBIN_H

#include <vector>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "Commons.h"
#include "HelperFunctions.h"

using namespace std;

class XMLBin {
public:
    XMLBin();
    XMLBin(xmlNodePtr nodeBin);
    XMLBin(int id, int nBins, vector<double> edges);
    XMLBin(int id, int nBins, double min, double max);
    XMLBin(const XMLBin& orig);
    virtual ~XMLBin();
  
    int id;
    int nBins;
    vector<double> edges;
    double min;
    double max;
    string particle;

private:
    void SetIdFromNode(xmlNodePtr nodeBin);
    void SetParticleFromNode(xmlNodePtr nodeBin);
};

#endif	/* XMLBIN_H */

