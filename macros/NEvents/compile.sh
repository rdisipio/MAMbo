#!/bin/bash

 g++ $( root-config --cflags --libs) sumWeights.cxx GetNEvents.cxx ../../src/HelperFunctions.o -g -o GetNEvents

 g++ $( root-config --cflags --libs) PDFsumWeights.cxx GetNEventsPDF.cxx ../../src/HelperFunctions.o -g -o GetNEventsPDF

 g++ $( root-config --cflags --libs) sumWeights.cxx GetNEventsHisto.cxx ../../src/HelperFunctions.o -g -o GetNEventsHisto

