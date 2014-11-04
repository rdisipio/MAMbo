/* 
 * File:   JetValues.h
 * Author: Michele
 *
 * Created on 30 October 2014, 16:23
 */

#ifndef JETVALUES_H
#define	JETVALUES_H

class JetValues {
public:
    JetValues();
    JetValues(const JetValues& orig);
    virtual ~JetValues();
    
    double pt;
    double eta;
    double phi;
    double E;  
    double m;

private:

};

#endif	/* JETVALUES_H */

