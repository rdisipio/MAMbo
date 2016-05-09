#!/usr/bin/python

import os, sys

### IMPORTANT TO BE MOVED TO SOME GLOBALS!!!
production = 'TTDIFFXS_62'

mambodir=os.environ['MAMBODIR']
user=os.environ['USER']
baseoutdir='/raid7_atlas2/%s/mambo_out/' % (user,)
os.system('mkdir -p %s' % (baseoutdir,))
