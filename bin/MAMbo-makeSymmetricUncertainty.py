#!/usr/bin/env python

import os, sys, time
import optparse
sys.path.append( os.environ['MAMBODIR'] + "/python" )

from ProgressBar import *

from xml.etree import ElementTree

from ROOT import *

########################################


class SampleWrapper:
   name        = ""
   file        = ""
   systematics = {}

class OutputType:
   unknown     = 0
   histogram   = 1
   graph       = 2
   both        = 3


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
      samples_configuration[name].name        = name
  
      fpath = node.attrib.get('file')
      if not fpath.startswith('/'): fpath = os.environ['MAMBOOUTPUTDIR'] + "/" + fpath
      samples_configuration[name].file        = TFile.Open( fpath )

      samples_configuration[name].systematics = {}
      for syst in node.iter("syst"):
         sname = syst.attrib['name']
         samples_configuration[name].systematics[sname] = {}
         for shift in syst.iter("shift"):
            side   = shift.attrib["side"]
            sfname = shift.attrib["file"]
            if not sfname.startswith('/'): sfname = os.environ['MAMBOOUTPUTDIR'] + "/" + sfname 
            samples_configuration[name].systematics[sname][side] = TFile.Open( sfname ) 

   return histograms_configuration, samples_configuration


####################################################


def GatherHistograms( hname, hpath ):
    hlist = {}

    for sample in samples_configuration:

        f = samples_configuration[sample].file
        if f == None:
            print "ERROR: invalid input file for sample", sample
        hsource = f.Get( hpath )

        if hsource == None:
            print "ERORR: invalid histogram", hpath, "for sample", sample, "in file", f.GetTitle()

        newname = "%s_%s" % ( sample, hname )
        hlist[sample] = hsource.Clone( newname )

        for syst,flist in samples_configuration[sample].systematics.iteritems():
           for side, fname in flist.iteritems():
              hsource = fname.Get( hpath )
              newname = "%s_%s_%s_%s" % ( sample, hname, syst, side )
              if hsource == None: print "ERROR: invalid histogram", sample, hname, syst, side
              hlist[newname] = hsource.Clone( newname )

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


#######################################

def CreateSymmetricHistograms( outfilenames ):

    outfile_u = TFile.Open( outfilenames['u'], "RECREATE" )
    outfile_d = TFile.Open( outfilenames['d'], "RECREATE" )

    for hpath in histograms_configuration:
       hname = hpath.split('/')[-1]
       
       hlist = GatherHistograms( hname, hpath )

       nbins = -1
       edges = []
       title = ""

       for sample in samples_configuration.keys():
          h_n   = hlist[sample]
          nbins = h_n.GetNbinsX()
          title = h_n.GetTitle()

          h_out_u = h_n.Clone()
          h_out_d = h_n.Clone()

          h_out_u.Reset("ICES")
          h_out_d.Reset("ICES")

          for i in range(nbins):
             y_n = h_n.GetBinContent(i+1)

             for systname in samples_configuration[sample].systematics.keys():
                 hpattern = "%s_%s_%s_" % ( sample, hname, systname )

                 h_sys = hlist[hpattern+"single"]

                 dy = h_sys.GetBinContent(i+1) - y_n

                 h_out_u.SetBinContent( i+1, y_n + dy )
                 h_out_d.SetBinContent( i+1, y_n - dy )

       outfile_u.cd()
       CreateROOTPath( hpath )
       h_out_u.Write( hname )

       outfile_d.cd()
       CreateROOTPath( hpath )
       h_out_d.Write( hname )
    

########################################################################


def DumpUpDownHistograms( hpath, edges, points ):

    hname = hpath.split('/')[-1]


########################################################################


if __name__ == "__main__":
   
   parser = optparse.OptionParser( usage = "%prog [options] configfile.xml" )
   parser.add_option( "-c", "--config", help="Configuration files",         dest="config", default="" )
   parser.add_option( "-o", "--output", help="Output file name [%default]", dest="output", default="uncertainty_up.histograms.root,uncertainty_down.histograms.root" )
   (opts, args) = parser.parse_args()

   configFileName = opts.config
   if configFileName == "":
        print "ERROR: please specify a config file in xml format."
        exit(1)

   outfilenames = opts.output.split(",")

   for outFileName in outfilenames:
      print "INFO: Output file name:", outFileName
 
   histograms_configuration, samples_configuration  = ReadConfiguration( configFileName )

   CreateSymmetricHistograms( { 'u' : outfilenames[0], 'd' : outfilenames[1] } )

