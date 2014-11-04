/* 
 * File:   Particle.cpp
 * Author: Michele
 * 
 * Created on 31 October 2014, 18:22
 */

#include "Particle.h"

Particle::Particle() {
}

Particle::Particle(EventData::Reco_t& particle, int index) {
    pt = particle.pT.at(index);
    eta = particle.eta.at(index);
    phi = particle.phi.at(index);
    E = particle.E.at(index);
    m = particle.m.at(index);
    y = PhysicsHelperFunctions::Rapidity(particle, index);
}

Particle::Particle(EventData::Truth_t& particle, int index) {
    pt = particle.pT.at(index);
    eta = particle.eta.at(index);
    phi = particle.phi.at(index);
    E = particle.E.at(index);
    m = particle.m.at(index);
    y = PhysicsHelperFunctions::Rapidity(particle, index);
}

Particle::Particle(const Particle& orig) {
}

Particle::~Particle() {
}
