/* 
 * File:   Particle.h
 * Author: Michele
 *
 * Created on 31 October 2014, 18:22
 */

#ifndef PARTICLE_H
#define	PARTICLE_H

#include "EventData.h"
#include "PhysicsHelperFunctions.h"
#include "Commons.h"

class Particle {
public:
    Particle();
    Particle(EventData::Reco_t& particle, int index);
    Particle(EventData::Truth_t& particle, int index);
    Particle(const Particle& orig);
    virtual ~Particle();
    
    double pt;
    double eta;
    double phi;
    double E;  
    double m;
    double y;
    
private:

};

#endif	/* PARTICLE_H */

