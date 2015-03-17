#include <iostream>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <cassert>
#include <string>
#include <sstream>

#include <TObject.h>
#include <TDirectory.h>
#include <TTree.h>

// LHAPDF doesn't compile with CINT due to a header file problem in
// AnalysisTop 1.8.0.
#ifndef __CINT__
// NOTE: must include full header file since Factories.h will try to access
// functionality from elsewhere in LHAPDF without including that header file
#include "LHAPDF/LHAPDF.h"
#endif

#include "ScalerPDF.h"


///////////////////////////////////////////////

// set static variables

std::vector<LHAPDF::PDF*> ScalerPDF::s_PDFs;
int ScalerPDF::s_numInstances = 0;

const std::string ScalerPDF::s_setNamesFull[]  = { "CT10nlo", "MSTW2008nlo68cl", "NNPDF23_nlo_as_0119" };
const std::string ScalerPDF::s_setNames[]      = { "CT10", "MSTW", "NNPDF" };
const size_t      ScalerPDF::s_numSetMembers[] = { 53, 41, 101 };
const size_t      ScalerPDF::s_numScales       = 53 + 41 + 101;


///////////////////////////////////////////////


ScalerPDF::ScalerPDF() :
    ScalerTree() 
{
  m_scales.assign(s_numScales, 0);
  s_numInstances += 1;
}


///////////////////////////////////////////////


ScalerPDF::~ScalerPDF() 
{
  s_numInstances -= 1;
  // No LHADF objects to destruct from CINT
  #ifndef __CINT__
  if (s_numInstances <= 0)
    // This is the last instance in memory, so clean the dynamic static memory
    for (std::vector<LHAPDF::PDF*>::iterator it = s_PDFs.begin();
        it != s_PDFs.end(); ++it)
      if (*it) delete *it;
  #endif 
}


///////////////////////////////////////////////


void ScalerPDF::initRead(const TDirectory& dir) 
{
  // Get the standard named tree from the read directory
  TObject* ptr = dir.FindObject("ScalerPDF");
  if (!ptr) throw std::runtime_error(
      "ScalerPDF::initRead: tree not found in dir");
  m_ttree = dynamic_cast<TTree*>(ptr);

  // Point all its scale branches to the scale vector
  for (size_t iscale = 0; iscale < m_scales.size(); iscale++)
    m_ttree->SetBranchAddress(indexToName(iscale).c_str(), &(m_scales[iscale]) );
}


///////////////////////////////////////////////


void ScalerPDF::initWrite(TDirectory& dir) 
{
  // Only initialize PFD objects once for all instances
  if (s_PDFs.empty()) {
    // Each PDF scale is computed by its own LHAPDF object
    s_PDFs.assign(s_numScales, 0);
    // Buld the actual PDF objects used to compute scales
    for (size_t i = 0; i < s_numScales; i++) {
      size_t iset = 0;
      size_t imember = 0;
      // Map the scale number to a PDF set and its variant
      indexToSetMember(i, iset, imember);
      // Build a string which identifies this PDF set / variant in LHAPDF
      std::stringstream ss;
      ss << s_setNamesFull[iset] << "/" << imember;
      #ifndef __CINT__  // Don't compile LHAPDF functionality with CINT
      s_PDFs[i] = LHAPDF::mkPDF(ss.str());
      #else
      s_PDFs[i] = 0;
      #endif
    }
  }

  dir.cd();
  m_ttree = new TTree("ScalerPDF", "ScalerPDF");
  
  // Point the tree branches to the scale vector
  for (size_t iscale = 0; iscale < m_scales.size(); iscale++) {
    const std::string name = indexToName(iscale);
    m_ttree->Branch(name.c_str(), &(m_scales[iscale]), (name+"/F").c_str());
  }
} 


///////////////////////////////////////////////


void ScalerPDF::calculate() 
{
  if (s_PDFs.empty()) throw std::runtime_error(
        "ScalerPDF::calculate: can't calculate in read mode");

  const double PDF1 = m_params.pdf1;
  const double PDF2 = m_params.pdf2;

  const int pid1 = m_params.id1;
  const int pid2 = m_params.id2;
  const double x1 = m_params.x1;
  const double x2 = m_params.x2;
  const double q = m_params.scale;

  // For each LHAPDF object, get a scale which weights this event to mimic
  // the PDF set / variant of that scale
  for (size_t i = 0; i < s_numScales; i++) {
    #ifndef __CINT__  // Don't compile LHAPDF functionality with CINT
    const double new_PDF1 = s_PDFs[i]->xfxQ(pid1, x1, q);
    const double new_PDF2 = s_PDFs[i]->xfxQ(pid2, x2, q);
    #else
    const double new_PDF1 = 0;
    const double new_PDF2 = 0;
    #endif
    m_scales[i] = (new_PDF1*new_PDF2) / (PDF1*PDF2);
  }
}


///////////////////////////////////////////////


std::string ScalerPDF::indexToName(size_t i) 
{
  std::stringstream ss;
  size_t iset = 0;
  size_t imember = 0;
  indexToSetMember(i, iset, imember);
  ss << s_setNames[iset] << "_" << imember;
  return ss.str();
}


///////////////////////////////////////////////


void ScalerPDF::indexToSetMember(size_t index, size_t& iset, size_t& imember) 
{
  for (int nset = 0; nset < NSETS; nset++) {
    if (index < s_numSetMembers[nset]) {
      iset = nset;
      imember = index;
      return;
    }
    index -= s_numSetMembers[nset];
  }

  throw std::runtime_error("ScalerPDF::indexToSet: invalid index");
}


///////////////////////////////////////////////


size_t ScalerPDF::setMemberToIndex(size_t iset, size_t imember) 
{
  size_t accumulated = 0;
  for (size_t nset = 0; nset < iset; nset++)
    accumulated += s_numSetMembers[nset];
  return accumulated + imember;
};


