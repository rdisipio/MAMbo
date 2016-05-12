#!/usr/bin/python

from globals_prague import *

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

        dsid = tag

        normalizationdir = '%s/share/data/NEvents_%s/' % (mambodir, production,)
        normalizationfile = os.popen('cd %s ; ls *.n | grep %s | grep -v "_a" ' % (normalizationdir, dsid)).readlines()
        print normalizationdir
        print normalizationfile
        if len(normalizationfile) == 1:
            lumifile = normalizationfile[0][:-1]
        else:
            # MORE CARE NEEDED FOR AFII AND FULLSIM SAMPLES!!
            lumifile = normalizationfile[0][:-1] ## TO FINISH
        #print lumifile


        # make the file config!
        # old: cmd='cat control/%s | sed "s|lists/list_eos_new_mc.txt|%s|g" > control/%s' % (cfg, flist, newcfg)
        cmd='cat control/%s | sed "s|lists/list_eos_new_mc.txt|%s|g" | sed "s|MAMBODIR|%s|g" | sed "s|LUMIFILE|%s|g" > control/%s' % (cfg, flist, mambodir, lumifile, newcfg)
        #print cmd
        os.system(cmd)
        ## prepare command:
        out='%s/histograms_zprime_%s_%s.root' % (outdir,tag, ljet,)
        cmd='cd %s ; . setup_AnalysisRelease_prague.sh ; cd run ; runMAMbo -p %s/run/control/%s -f %s/%s -o %s' % (mambodir, mambodir, newcfg, path, flist, out,)
        print cmd

    
