#ifndef SCALERTREE_H
#define SCALERTREE_H

#include "Commons.h"

#include <TTree.h>
#include <TDirectory.h>


/**
  * Mostly abstract class defines an interface for classes which will write
  * event scales to or read from `TTree` branches for SL mini n-tuple events.
  * 
  * Some standard memory is allocated, but most of the class defines the
  * interface which any systematic tree implementation must have to be used
  * in a consistent way from an executing program.
  *
  * @author Garrin McGoldrick (garrin.mcgoldrick@cern.ch)
  * adapted to MAMbo framework by Riccardo Di Sipio (disipio@cern.ch)
  */

class ScalerTree {

 protected:
  TTree        * m_ttree;
  StringVector_t m_branchNames;
  array_d        m_scales;

 public:
  ScalerTree() : m_ttree(NULL) {};
  virtual ~ScalerTree() {};

  /** Initialize and make a tree for writing */
  virtual void initRead(const TDirectory& dir) = 0;
  /** Initialize a tree for reading */
  virtual void initWrite(TDirectory& dir) = 0;

  /** Compute the scale values for an event */
  virtual void calculate() = 0;

  /** Get the branch name for the `i`th branch */
  virtual std::string indexToName(size_t i) = 0;

  /** Get the tree */
  virtual TTree* tree() { return m_ttree; }
  /** Get the scales for the current event */
  virtual const array_d& scales() { return m_scales; }
  /** Clear branch values */
  virtual void clear();
};

#endif  // SCALERTREE_H


