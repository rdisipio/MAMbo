#!/usr/bin/env python

import os, sys
import optparse
from distutils.dir_util import mkpath

sys.path.append( os.environ['MAMBODIR'] + "/python" )

from xml.etree import ElementTree

from ROOT import *
from MAMboPlottingToolkit import *

gROOT.Macro( os.environ['MAMBODIR'] + "/share/rootlogon.C" )
gROOT.LoadMacro( os.environ['MAMBODIR'] + "/share/AtlasUtils.C" )
gROOT.LoadMacro( os.environ['MAMBODIR'] + "/share/graph_scale.C" )
from ROOT import ScaleGraph

####################################################


class PlotScale:
   unknown = 0
   linear  = 1
   log     = 2
   bilog   = 3

   @classmethod
   def ToScale( self, txt ): 
      if   txt.lower() == "linear": return self.linear
      elif txt.lower() == "log":    return self.log
      elif txt.lower() == "bilog":  return self.bilog
      else:                         return self.unknown

   @classmethod
   def ToString( self, scale ):
      if scale   == self.linear: return "linear"
      elif scale == self.log:    return "log"
      elif scale == self.bilog:  return "bilog"
      else:                      return "unknown"


class PlotWrapper:
   hname  = ""
   hpath  = ""
   xtitle = ""
   ytitle = ""
   scale  = PlotScale.linear
   rebin  = 1
   tag    = ""

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class SampleType:
   unknown     = 0
   data        = 1
   signal      = 2
   background  = 3
   datadriven  = 4
   uncertainty = 5

   @classmethod
   def ToType( self, txt ):
       t = txt.lower()
       if   t == "data":        return self.data
       elif t == "signal":      return self.signal
       elif t == "background":  return self.background
       elif t == "datadriven":  return self.datadriven
       elif t == "uncertainty": return self.uncertainty
       else:                    return self.unknown

class SampleWrapper:
   id          = -1
   name        = ""
   type        = SampleType.unknown
   description = ""
   color       = 1
   fillstyle   = 0
   linewidth   = 2


####################################################


def ReadConfiguration( configFileName ):
   with open( configFileName, 'rt') as f:
      tree = ElementTree.parse(f)

   if tree == None:
      print "ERROR: cannot parse input file", configFileName
      exit(1)

   plots_configuration = {}

   for node in tree.iter( "plots" ):
     plot_tag    = node.attrib.get('tag')
     channel_tag = node.attrib.get('latex')

   for node in tree.iter( "plot" ):

      hpath = node.attrib.get('hpath')
      hname = plot_tag + "_" + hpath.replace('/', '_')   

      plots_configuration[hname] = PlotWrapper()
      plots_configuration[hname].hname  = hname
      plots_configuration[hname].hpath  = hpath
      plots_configuration[hname].xtitle = node.attrib.get('xtitle')
      plots_configuration[hname].ytitle = node.attrib.get('ytitle')
      plots_configuration[hname].tag    = channel_tag

      scale  = node.attrib.get('scale')
      plots_configuration[hname].scale  = PlotScale.ToScale( scale )

      if 'rebin' in node.attrib: plots_configuration[hname].rebin = int( node.attrib.get('rebin') )

   samples_configuration = {}
   i = 0
   for node in tree.iter( "sample" ):
      name = node.attrib.get('name')
      samples_configuration[name] = SampleWrapper()
      samples_configuration[name].id          = i
      samples_configuration[name].name        = name
      samples_configuration[name].type        = SampleType.ToType( node.attrib.get('type') ) 
      samples_configuration[name].description = node.attrib.get('description')
      samples_configuration[name].color       = int( node.attrib.get('color') )
      samples_configuration[name].fillstyle   = int( node.attrib.get('fillstyle') )
      samples_configuration[name].linewidth   = int( node.attrib.get('linewidth') )

      if samples_configuration[name].type == SampleType.data: samples_configuration[name].description += " " + channel_tag
      i += 1

   input_files = {}
   for node in tree.iter( "file" ):
      sample = node.attrib.get('sample')

      path = node.attrib.get('path')
      input_files[sample] = TFile.Open( path )

   return plots_configuration, samples_configuration, input_files


####################################################


def FetchHistograms():
    histograms = {}

    for sample, sample_config in samples_configuration.iteritems():
       infile = input_files[sample]
       if infile == None:
           print "WARNING: invalid input file for sample", sample
           continue

       newname = "%s_%s" % ( sample, plot.hname )
       h = input_files[sample].Get( plot.hpath )
       if h == None:
          print "ERROR: invalid histogram for sample", sample, "in file", input_files[sample]

       histograms[sample] = h.Clone( newname )
#       histograms[sample].Rebin( plots_configuration[plot.hname].rebin )

    return histograms
  

####################################################


def ScaleToIntegratedLuminosity( histograms, iLumi = 1. ):

   for sample in samples_configuration:
      if samples_configuration[sample].type == SampleType.data: continue
      if samples_configuration[sample].type == SampleType.datadriven: continue
      if samples_configuration[sample].type == SampleType.uncertainty:
         ScaleGraph( histograms[sample], iLumi ) 
      else:
         histograms[sample].Scale( iLumi )


####################################################


def SetHistogramsStyle( hlist ):
    for sample, h in hlist.iteritems():
       col  = samples_configuration[sample].color
       fs   = samples_configuration[sample].fillstyle
       type = samples_configuration[sample].type

       if type == SampleType.data:
          SetTH1FStyle( h, color=kBlack, markersize=1.2, markerstyle=20, linewidth=2 )    
       
       if type == SampleType.background or type == SampleType.datadriven:
          SetTH1FStyle( h, color=col, markersize=0, markerstyle=0, linewidth=0, fillcolor=col, fillstyle=fs ) 

       if type == SampleType.uncertainty:
          SetTH1FStyle(	h, color=col, markersize=0, markerstyle=0, linewidth=0, fillcolor=col, fillstyle=fs )

    SetAxesStyle( hlist.values() )


####################################################


def PrintLegend( lparams, histograms ):
    # todo: font must be helvetica (42?)
    leg = MakeLegend( lparams )

    leg.AddEntry( histograms['data'], samples_configuration['data'].description, "lep" )

    ordered_samples = [ "" for i in range( len(histograms) ) ]

    for sample, h in histograms.iteritems():    
       if samples_configuration[sample].type == SampleType.data:        continue
       id = samples_configuration[sample].id
       ordered_samples[id] = sample

    ordered_samples = [ s for s in ordered_samples if s != "" ]    

    for sample in ordered_samples:
       leg.AddEntry( histograms[sample], samples_configuration[sample].description, "f" )
  
    leg.Draw()
    leg.SetY1( leg.GetY1() - lparams['height'] * leg.GetNRows() )

    return leg


####################################################


def MakeStackedHistogram( histograms ):
    stack = THStack( "stack", "Prediction" )

    # order samples by id in reversed order
    ordered_samples = [ "" for i in range(len(histograms)) ]

    for sample in histograms.keys():
        if samples_configuration[sample].type in [ SampleType.data, SampleType.uncertainty, SampleType.unknown ]: continue
        id = samples_configuration[sample].id
        ordered_samples[id] = sample
    ordered_samples = [ s for s in ordered_samples if s != "" ]  
    ordered_samples = ordered_samples[::-1]

    for sample in ordered_samples:
       stack.Add( histograms[sample] )

#    stack.SetMaximum( hmax )

    return stack
 

####################################################


def DoPlot( plot, iLumi = 1. ):

    print "INFO: plotting %s with %s scale" % ( plot.hname, PlotScale.ToString(plot.scale) )

    histograms = FetchHistograms()

    ScaleToIntegratedLuminosity( histograms, iLumi )

    DivideByBinWidth( histograms )

    SetHistogramsStyle( histograms )

    hmax = 1.4 if plot.scale == PlotScale.linear else 15.
    SetMaximum( histograms, 'data', hmax )

    histograms['data'].GetYaxis().SetTitle( plot.ytitle )

    ## draw top pad

    pad0.cd()
    gPad.SetLogy(False)
    gPad.SetLogx(False)

    hstack = MakeStackedHistogram( histograms )

    histograms['data'].Draw()
    #histograms['ttbar_ljets'].Draw( 'hist same' )
    hstack.Draw( 'hist same' )
    histograms['uncertainty'].Draw( 'e2 same' )
    histograms['data'].Draw("e p same" )

    if plot.scale == PlotScale.log: gPad.SetLogy(True)
    if plot.scale == PlotScale.bilog: 
       gPad.SetLogy(True)
       gPad.SetLogx(True)  

    lparams = {
        'xoffset' : 0.63,
        'yoffset' : 0.92,
        'width'   : 0.3,
        'height'  : 0.048
        }
    legend = PrintLegend( lparams, histograms )

    MakeATLASLabel( 0.18, 0.87, "Internal", "20.3", "8" )

    ## make data/prediction ratio

    pad1.cd()

    frame, tot_unc, ratio = DrawRatio( histograms['data'], histograms['uncertainty'], plot.xtitle )    
    

    ## save image

    c.cd()
    for ext in [ "png", "eps", "C" ]:
       imgname = "img/%s/%s.%s" % ( ext, plot.hname, ext )
       c.SaveAs( imgname ) 


########################################################################

    
if __name__ == "__main__":
   
   parser = optparse.OptionParser( usage = "%prog [options] configfile.xml" )
   parser.add_option( "-b", "--batch", help="Batch mode [%default]", dest="batch", default=True )
   parser.add_option( "-l", "--lumi",  help="Integrated luminosity [%default]", dest="ilumi", default=20300 )
   (opts, args) = parser.parse_args()
 
   if opts.batch:
        gROOT.SetBatch(True)

   configFileName = sys.argv[-1]

   plots_configuration, samples_configuration, input_files = ReadConfiguration( configFileName )
  
   for ext in [ 'png', 'eps', 'C' ]:
      mkpath( "./img/%s" % ext )   

   c, pad0, pad1 = MakeCanvas()

   iLumi = float( opts.ilumi )

   for key, plot in plots_configuration.iteritems():
      DoPlot( plot, iLumi )
