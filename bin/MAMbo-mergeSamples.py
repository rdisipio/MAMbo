#!/usr/bin/env python

import os, sys
import optparse

sys.path.append( os.environ['MAMBODIR'] + "/python" )

from xml.etree import ElementTree

from ROOT import *


########################################


class Simulations:
   unknown = 0
   full    = 1
   fast    = 2


class SampleWrapper:
   dsid        = -1
   name        = ""
   generator   = ""
   simulation  = Simulations.unknown
   xsec        = 0.
   kfact       = 0.
   sf          = 1.
   genevt      = 0


########################################


def ReadFromExternalFile( hfilename ):
   hlist = []

   with open( hfilename, 'rt') as f:
      tree = ElementTree.parse( f )

   for node in tree.iter( "histogram" ):
      hlist += [ node.attrib.get('hpath') ]
   
   return hlist


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


def ReadConfiguration( configFileName ): 
   with open( configFileName, 'rt') as f:
      tree = ElementTree.parse(f)
 
   if tree == None:
      print "ERROR: cannot parse input file", configFileName
      exit(1)

   histograms_configuration = []
   for node in tree.iter( "histograms" ):
       if "file" in node.attrib:
          hfilename = node.attrib.get('file')
          print "INFO: histograms defined in external file", hfilename
          histograms_configuration = ReadFromExternalFile( hfilename )
       else:
          for node in tree.iter( "histogram" ):
             histograms_configuration += [ node.attrib.get('hpath') ]

   samples_configuration = {}
   for node in tree.iter( "sample" ):
      name = node.attrib.get('name')
      samples_configuration[name] = SampleWrapper()
      samples_configuration[name].dsid        = node.attrib.get('dsid')
      samples_configuration[name].name        = name
      samples_configuration[name].generator   = node.attrib.get('generator')
      samples_configuration[name].simulation  = node.attrib.get('simulation')
      samples_configuration[name].xsec        = float( node.attrib.get('xsec') )
      samples_configuration[name].kfact       = float( node.attrib.get('kfact' ) )
      if 'sf' in node.attrib: samples_configuration[name].sf = float( node.attrib.get('sf') )
      samples_configuration[name].genevt      = float( node.attrib.get('genevt' ) )


   input_files = {} 
   for node in tree.iter( "file" ):
      sample = node.attrib.get('sample')

      path = node.attrib.get('path')
      if path.startswith("/"): path = path
      else: 
          path = os.environ['MAMBOOUTPUTDIR'] + "/" + path
      input_files[sample] = TFile.Open( path )

   return histograms_configuration, samples_configuration, input_files


####################################################


def RemoveNegativeBins( h ):
    nbins = h.GetNbinsX()
    for i in range(nbins):
       y = h.GetBinContent( i+1 )
       if y >= 0.: continue

       h.SetBinContent( i+1, 0. )


####################################################


def GatherHistograms( hname, hpath ):
    hlist = {}

    for sample in samples_configuration:

        hsource = input_files[sample].Get( hpath )

        if hsource == None:
            print "ERORR: invalid histogram", hpath, "for sample", sample

        newname = "%s_%s" % ( sample, hname )
        hlist[sample] = hsource.Clone( newname )
        if hlist[sample] == None:
           print "ERROR: invalid histogram", newname
        RemoveNegativeBins( hlist[sample] )

    return hlist


####################################################


def CreateROOTPath( path ):
    tokens = path.split( '/' )

    if len( tokens ) == 1:
        return gDirectory.GetDirectory(".")
    else:
        nextdir = tokens[0]

        if gDirectory.FindObject( nextdir ) == None:
            gDirectory.mkdir( nextdir )
        gDirectory.cd( nextdir )

        newpath = path.replace( tokens[0] + "/", "" )

        return CreateROOTPath( newpath )


####################################################


def CheckConsistency( h1, h2, sample ):
    nbins1 = h1.GetNbinsX()
    nbins2 = h2.GetNbinsX()

    if not nbins1 == nbins2: raise Exception( "Inconsistent number of bins for %s: %s has %i, %s has %i", h1.GetName(), "sum", nbins1, sample, nbins2 )
 
    for i in range( nbins1+1 ):
       xlow1 = h1.GetBinLowEdge( i+1 )
       xlow2 = h2.GetBinLowEdge( i+1 )
     
       if not xlow1 == xlow2: raise Exception( "Inconsistent bin %i low edges for %s: %s has %i, %s has %i", i, h1.GetName(), "sum", xlow1, sample, xlow2 ) 


####################################################


def CreateMergedHistograms():

    for hpath in histograms_configuration:
        outfile.cd()
	
        hname = hpath.split('/')[-1]
#        print "INFO: merging histogram", hpath

        do_reweight = False if hname.endswith( "_unweight" ) else True
#        do_copy     = True if hname.find("cutflow") > -1 and hname.endswith("weighted") else False
        do_copy     = True if hname.find("cutflow") > -1 else False

        hlist = GatherHistograms( hname, hpath )

        hsum = None
        for sample, h in hlist.iteritems():

           norm = 1.0
           if do_reweight:
               genevt = samples_configuration[sample].genevt
               xsec   = samples_configuration[sample].xsec
               kfact  = samples_configuration[sample].kfact
               sf     = samples_configuration[sample].sf
               norm   = iLumi * xsec * kfact * sf / genevt
           
           if hsum == None:

               newdir = CreateROOTPath( hpath )
               hsum = h.Clone( hname )

               hsum.Reset( "ICES" )
               hsum.SetDirectory( newdir )

#            CheckConsistency( hsum, h, sample )
           h.Scale( norm )

           if do_copy:
             h.Write( hname+"_"+sample )

           hsum.Add( h )

        hsum.Write()


########################################################################

    
if __name__ == "__main__":
   
   parser = optparse.OptionParser( usage = "%prog [options] configfile.xml" )
   parser.add_option( "-c", "--config", help="Configuration files",         dest="config", default="" )
   parser.add_option( "-o", "--output", help="Output file name [%default]", dest="output", default="merged.histograms.root" )
   parser.add_option( "-l", "--iLumi",  help="Target integrated luminosity [%default]", dest="iLumi", default=20300 )
   (opts, args) = parser.parse_args()

   configFileName = opts.config
   if configFileName == "":
        print "ERROR: please specify a config file in xml format."
        exit(1)

   print "INFO: Config file name:", configFileName

   outFileName = opts.output
   print "INFO: Output file name:", outFileName
 
   iLumi = float( opts.iLumi )

   histograms_configuration, samples_configuration, input_files = ReadConfiguration( configFileName )
  
   outfile = TFile.Open( outFileName, "RECREATE" )

   CreateMergedHistograms()

   outfile.Close()
