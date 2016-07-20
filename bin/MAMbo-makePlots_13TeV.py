#!/usr/bin/env python

import os, sys
import optparse
from distutils.dir_util import mkpath

sys.path.append( os.environ['MAMBODIR'] + "/python" )

from xml.etree import ElementTree

from ROOT import *
from MAMboPlottingToolkit_13TeV import *

#gROOT.Macro( os.environ['MAMBODIR'] + "/share/rootlogon.C" )
gROOT.LoadMacro( os.environ['MAMBODIR'] + "/share/AtlasStyle.C" )
gROOT.LoadMacro( os.environ['MAMBODIR'] + "/share/AtlasUtils.C" )
gROOT.LoadMacro( os.environ['MAMBODIR'] + "/share/graph_scale.C" )
SetAtlasStyle()

gROOT.LoadMacro( os.environ['MAMBODIR'] + "/share/DrawOverflow.C" )
from ROOT import ScaleGraph, DrawOverflow
norm = False

####################################################


class PlotScale:
   unknown = 0
   linear  = 1
   log     = 2
   logx    = 3
   bilog   = 4

   @classmethod
   def ToScale( self, txt ): 
      if   txt.lower() == "linear": return self.linear
      elif txt.lower() == "log":    return self.log
      elif txt.lower() == "logx":   return self.logx
      elif txt.lower() == "bilog":  return self.bilog
      else:                         return self.unknown

   @classmethod
   def ToString( self, scale ):
      if scale   == self.linear: return "linear"
      elif scale == self.log:    return "log"
      elif scale == self.logx:   return "logx"
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

      if samples_configuration[name].type == SampleType.data: samples_configuration[name].description# += " " + channel_tag
      i += 1

   input_files = {}
   for node in tree.iter( "file" ):
      sample = node.attrib.get('sample')

      path = node.attrib.get('path')
      if not path.startswith('/'): path = os.environ['MAMBOOUTPUTDIR'] + "/" + path
      input_files[sample] = TFile.Open( path )

   return plots_configuration, samples_configuration, input_files


####################################################


def AddOverflowToLastBin_TH1( h ):
   N   = h.GetNbinsX()
   yN  = h.GetBinContent( N )
   yOF = h.GetBinContent( N+1 )
   eN  = h.GetBinError( N )
   eOF = h.GetBinError( N+1 )

   yNew = yN + yOF
   eNew = sqrt( eN*eN + eOF*eOF )
  
   h.SetBinContent( N, yNew )
   h.SetBinError( N, eNew )

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

#       AddOverflowToLastBin( h ) ## DOESN'T WORK WIHT TGRAPH!
       histograms[sample] = h.Clone( newname )
   
#       if samples_configuration[sample].type == SampleType.data:
#         print "INFO: poissonize", newname
#         histograms[sample] = Poissonize( histograms[sample] )

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


def SetHistogramsStyle( hlist, Integer=0 ):
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

    SetAxesStyle( hlist.values(), Integer )


####################################################


def PrintLegend( lparams, histograms ):
    # todo: font must be helvetica (42?)
    leg = MakeLegend( lparams )
    nbins = histograms['data'].GetNbinsX()
   # leg.SetTextFont( 42 )

    if opts.style != "paper":
        leg.AddEntry( histograms['data'], samples_configuration['data'].description + "(" + "{:.0f}".format( histograms['data'].Integral( 1, nbins, "width") ) + ")", "lep" )
    else:
        leg.AddEntry( histograms['data'], samples_configuration['data'].description, "lep" )
    ordered_samples = [ "" for i in range( len(histograms) ) ]

    for sample, h in histograms.iteritems():    
       if samples_configuration[sample].type == SampleType.data:        continue
       id = samples_configuration[sample].id
       ordered_samples[id] = sample

    ordered_samples = [ s for s in ordered_samples if s != "" ]    

    for sample in ordered_samples:
       if sample != "uncertainty":
         if opts.style != "paper":
                 leg.AddEntry( histograms[sample], samples_configuration[sample].description + "(" + "{:.1f}".format(  histograms[sample].Integral( 1, nbins, "width" ) ) + ")", "f" )
         else:
                 leg.AddEntry( histograms[sample], samples_configuration[sample].description, "f" )  
         continue
       leg.AddEntry( histograms[sample], samples_configuration[sample].description, "f" )
         
  
    leg.Draw()
   # leg.SetY1( leg.GetY1() - lparams['height'] * leg.GetNRows() )

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


def MakeStackedHistogram( histograms , normaliztion_factor ):
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
       histograms[sample].Scale(normaliztion_factor)
       stack.Add( histograms[sample] )

#    stack.SetMaximum( hmax )

    return stack


  
######################################################
#def SubtractBackground( histograms ):
    
    #h = histograms['DiTop'].Clone()
    #for sample in histograms.keys():
        #if samples_configuration[sample].type in [ SampleType.data, SampleType.signal, SampleType.uncertainty, SampleType.unknown ]: continue
        #h.Add(histograms[sample])
    
    #IntegralSignal = h.Integral("width")
    #if IntegralSignal != 0 :
      #h.Scale(1/IntegralSignal)

    #return h

#####################################################



def SumPredictionHistograms( histograms ):
   # stack = THStack( "stack", "Prediction" )

    # order samples by id in reversed order
    ordered_samples = [ "" for i in range(len(histograms)) ]

    for sample in histograms.keys():
        if samples_configuration[sample].type in [ SampleType.data, SampleType.uncertainty, SampleType.unknown ]: continue
        id = samples_configuration[sample].id
        ordered_samples[id] = sample
    ordered_samples = [ s for s in ordered_samples if s != "" ]  
    ordered_samples = ordered_samples[::-1]
    
    counter = 0
    for sample in ordered_samples:
       if counter == 0: hsum = histograms[sample].Clone( "sum" )
       else: hsum.Add( histograms[sample] )
       counter+=1

#    stack.SetMaximum( hmax )

    return hsum
 

####################################################


def DoPlot( plot, iLumi = 1. ):
    global norm
    print "INFO: plotting %s with %s scale" % ( plot.hname, PlotScale.ToString(plot.scale) )

    histograms = FetchHistograms()

    #ScaleToIntegratedLuminosity( histograms, iLumi )
    Integer=0
    if "_n" in plot.hname:
      Integer=1
   
    DivideByBinWidth( histograms )
    SetHistogramsStyle( histograms, Integer )

    sfmax = 1.9 if plot.scale in [ PlotScale.linear, PlotScale.logx ] else 100.
    sfmin = 0.1 if plot.scale in [ PlotScale.linear, PlotScale.logx ] else 1e-2
    print histograms.keys()
    SetMaximum( histograms, 'data', sfmax, sfmin )
    

    histograms['data'].GetYaxis().SetTitle( plot.ytitle )
    min = 0.1 if plot.scale in [ PlotScale.linear, PlotScale.logx ] else 1e-2
    histograms['data'].GetYaxis().SetTitle( plot.ytitle )
    histograms['data'].SetMinimum( min )

    ## draw top pad

    pad0.cd()
    pad0.SetLogy(False)
    pad0.SetLogx(False)
    pad1.SetLogy(False)
    pad1.SetLogx(False)

    normalize=1.
    hsum = SumPredictionHistograms( histograms )
    nbins = hsum.GetNbinsX()
    if norm == True:
     StackIntegral = hsum.Integral(1, nbins, "width")
     DataIntegral = histograms['data'].Integral(1, nbins, "width")
     if  StackIntegral != 0 :
       normalize = DataIntegral/StackIntegral
     for bin in range(hsum.GetNbinsX()):
        histograms['uncertainty'].SetPoint(bin, hsum.GetBinCenter(bin+1), hsum.GetBinContent(bin+1) * normalize)      
        histograms['uncertainty'].SetPointError(bin, histograms['uncertainty'].GetErrorXhigh(bin),histograms['uncertainty'].GetErrorXlow(bin), histograms['uncertainty'].GetErrorYhigh(bin) * normalize, histograms['uncertainty'].GetErrorYlow(bin) * normalize)
    
    hstack = MakeStackedHistogram( histograms, normalize )
  
    
      
    if histograms['data'].Class() in [ TH1F.Class(), TH1D.Class() ]:
       histograms['data'].Draw()
       hstack.Draw( 'hist same' )
    else:
       hstack.Draw( 'hist' )

    histograms['uncertainty'].Draw( 'e2 same' )
    histograms['data'].Draw("e p same" )

    #Redrowing Axis to be visible
    pad0.RedrawAxis()

    tag_scale = ""
    if plot.scale == PlotScale.linear:
#       pad1.SetLogy(False)
       pad0.SetLogx(False)
    if plot.scale == PlotScale.log: 
       pad0.SetLogy(True)
       tag_scale = "_log"
    if plot.scale == PlotScale.logx:
       pad0.SetLogx(True)
#       pad1.SetLogx(True)
#       pad1.SetLogy(False)
       tag_scale = "_logx"
    if plot.scale == PlotScale.bilog: 
       pad0.SetLogy(True)
       pad0.SetLogx(True)
#       pad1.SetLogx(True)  
#       pad1.SetLogy(False)
       tag_scale = "_bilog"

       
       
    # lparams = {
        # 'xoffset' : 0.67,
        # 'yoffset' : 0.92,
        # 'width'   : 0.3,
        # 'height'  : 0.048
        # }
         # TLegend(0.65, 0.52, 0.85, 0.90)
    lparams = {
        'xoffset' : 0.65,
        'yoffset' : 0.52,
        'width'   : 0.2,
        'height'  : 0.38
        }
    legend = PrintLegend( lparams, histograms )
    #kolmogorov test
    channel_tag =  plot.tag
    prob = "KS: %2.1f" % (hsum.KolmogorovTest( histograms['data'], "D" ))
    t = TLatex()
    t.SetTextAlign(9);
    t.SetTextSize(0.06); 
    t.SetNDC();
    t.SetTextColor(kBlack);
   # l.DrawLatex( 0.8, 0.961, prob );
    

    MakeATLASLabel( 0.21, 0.87, "Internal", "3.2", "13" )
    t.DrawLatex( 0.21, 0.735, opts.region );
   # t.DrawLatex( 0.2, 0.63, opts.region )
   
    ## make data/prediction ratio

    pad1.cd()
    
    fs = samples_configuration["uncertainty"].fillstyle
    frame, tot_unc, ratio, norm1 = DrawRatio( histograms['data'], histograms['uncertainty'], plot.xtitle , fs, Integer)
       

    if plot.scale in [ PlotScale.bilog, PlotScale.logx ]: 
       pad1.SetLogx(True)
       pad1.SetLogy(False)
       frame.GetXaxis().SetMoreLogLabels(True)
       frame.GetXaxis().SetNoExponent(True)
       

    ## save image
    pad0.cd()
    
    gPad.RedrawAxis()
    c.cd()
    for ext in [ "pdf", "png" ]: #, "pdf", "C" ]:
       imgname = "img/%s/%s%s.%s" % ( ext, plot.hname, tag_scale, ext )
       c.SaveAs( imgname ) 


########################################################################

    
if __name__ == "__main__":
   
   parser = optparse.OptionParser( usage = "%prog [options] configfile.xml" )
   parser.add_option( "-b", "--batch", help="Batch mode [%default]", dest="batch", default=True )
   parser.add_option( "-l", "--lumi",  help="Integrated luminosity [%default]", dest="ilumi", default=20300 )
   parser.add_option( "-n", "--normalization",  help="Normalize Sample", dest="normalization", default=False )
   parser.add_option( "-s", "--style", help="Use paper/note style", dest="style", default="note")
   parser.add_option( "-r", "--region", help="Resolved/Boosted region", dest="region", default="Resolved")
   (opts, args) = parser.parse_args()
   
   print "Paper style ", opts.style
   if opts.batch:
        gROOT.SetBatch(True)
   
   norm=False
   if opts.normalization:
        norm=True
       
   configFileName = sys.argv[-1]

   plots_configuration, samples_configuration, input_files = ReadConfiguration( configFileName )
  
#   for ext in [ 'png', 'eps', 'C' ]:
   for ext in [ 'png']:
      mkpath( "./img/%s" % ext )   

   c, pad0, pad1 = MakeCanvas()

   iLumi = float( opts.ilumi )

   for key, plot in plots_configuration.iteritems():
      DoPlot( plot, iLumi )
