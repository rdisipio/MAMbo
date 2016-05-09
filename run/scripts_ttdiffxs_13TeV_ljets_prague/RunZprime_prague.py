#!/usr/bin/python

import os, sys

Ljets = ['el', 'mu']

basecfg='analysis_params_TTbarResolved_mcsignal_ll_eos.xml'
path=os.environ['PWD']
mambodir=os.environ['MAMBODIR']
user=os.environ['USER']
outdir='/raid7_atlas2/%s/mambo_out' % (user,)

for ljet in Ljets:
    cfg=basecfg.replace('_ll_', '_%s_' % (ljet,))


    for flist in os.popen('ls lists/list__3013??.Pythia8EvtGen.txt').readlines():
        #print '------------------------'
        #print flist
        flist = flist[0:-1]
        # print flist
        tokens=flist.split('.')
        tag=tokens[0]
        tag=tag.replace('lists/list__', '')
        # print 'Tag: %s' % (tag,)
        newcfg=cfg.replace('eos', '%s' % (tag,))
        print newcfg
        # make the file config!
        cmd='cat control/%s | sed "s|lists/list_eos_new_mc.txt|%s|g" > control/%s' % (cfg, flist, newcfg)
        #print cmd
        os.system(cmd)
        ## prepare command:
        out='%s/histograms_PowHeg_%s_%s.root' % (outdir,tag, ljet,)
        cmd='cd %s ; . setup_AnalysisRelease_prague.sh ; cd run ; runMAMbo -p %s/run/control/%s -f %s/%s -o %s' % (mambodir, mambodir, newcfg, path, flist, out,)
        print cmd

    
