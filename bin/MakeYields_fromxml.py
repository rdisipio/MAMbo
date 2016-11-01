#!/usr/bin/env python

import os, sys, time
import optparse

from xml.etree import ElementTree

####################################################

class YieldWrapper:
   nominal = 0.
   stat = 0.
   sys_u = 0.
   sys_d = 0.
   
####################################################


def ReadInput( filename ):
   
   SampleYield = YieldWrapper()
   with open( filename, 'rt') as f:
      tree = ElementTree.parse(f)
      
      for histogram in tree.findall( './/histogram' ):
         hpath = histogram.attrib.get('hpath')
         if hpath == "LPLUSJETS_cutflow_reco_unweight" :
            continue

#         print "*", hpath

         nbins = -1
         for nominal in histogram.findall( '.nominal' ):
             values = nominal.text.split(',')
             nbins = len( values )
             SampleYield.nominal = float(values[nbins-1])
             

         for syst in histogram.findall('.uncertainty'):
             systname = syst.attrib.get('name')
             if systname == "statonly" : 
               
                for shift in syst.findall('.u'):                               
                  thisstat = shift.text.split(',')
                  nbins1 = len( thisstat )
                  SampleYield.stat = float(thisstat[nbins1-1])
                  
             if systname == "statsyst" : 
               
                for shift_u in syst.findall('.u'):                               
                  thissyst_u = shift_u.text.split(',')
                  nbins1_u = len( thissyst_u )
                  SampleYield.sys_u = float(thissyst_u[nbins1_u-1])
                for shift_d in syst.findall('.d'):
		  thissyst_d = shift_d.text.split(',')
                  nbins1_d = len( thissyst_d )
                  SampleYield.sys_d = float(thissyst_d[nbins1_d-1])

   SampleYield.sys_u = SampleYield.sys_u * SampleYield.nominal / 100. 
   SampleYield.sys_d = SampleYield.sys_d * SampleYield.nominal / 100.
   SampleYield.stat = SampleYield.stat * SampleYield.nominal / 100.   

   return SampleYield

if __name__ == "__main__":

   parser = optparse.OptionParser( usage = "%prog [options]" )
   parser.add_option( "-s", "--sample", help="Sample", dest="sample", default="Total Prediction" )
   parser.add_option( "-i", "--input-xml", help="Input XML file [%default]", dest="input", default="uncertainty.xml" )
   (opts, args) = parser.parse_args()

   thisyield = ReadInput( opts.input )

   print "%s & %s & +%s %s \\\\" % ( opts.sample, thisyield.nominal, thisyield.sys_u, thisyield.sys_d)
   
