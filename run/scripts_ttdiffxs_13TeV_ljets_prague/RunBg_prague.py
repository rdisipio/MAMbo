#!/usr/bin/python

# jk 5.5.2016

from globals_prague import *

Ljets = ['el', 'mu']

basecfg='analysis_params_TTbarResolved_bg_ll_eos.xml'
path=os.environ['PWD']

# just nominal:
Systs = [ 'nominal' ]


# systematics:
# Systs = [ 'JET_JER_SINGLE_NP__1up' ]
# Systs = [ '' ]

fnames = ['scripts_ttdiffxs_13TeV_ljets/resolved_kinematic_systematics.dat' ]
# TO BE SUPPORTED!!! , 'scripts_ttdiffxs_13TeV_ljets/resolved_scale_systematics.dat' ]
for fname in fnames:
    infile = open(fname, 'r')
    for line in infile.readlines():
        ###!!!Systs.append(line[:-1].replace('\t', '').replace(' ','')) # OMG;)
        pass
    infile.close()

#print Systs

### STEERING!!!
requireTag = False
# requireTag = True
# Zjets ONLY, and some CT10 ballast, too;)
dsidTag = 'mc.361'

BgList = []
fname = 'scripts_ttdiffxs_13TeV_ljets/AllBkgTTDIFFXS_62.txt'
infile = open(fname)
for line in infile.readlines():
    mline = line[:-1]
    if mline != '':
        if requireTag and mline.find(dsidTag) < 0:
            continue
        tokens = mline.split('.')
        BgList.append(tokens[1])
#print BgList


for syst in Systs:
    print 'Processing syst %s' % (syst,)
    outdir = baseoutdir + '/' + syst
    os.system('mkdir -p %s' % (outdir,))
    
    for ljet in Ljets:
                   
        print '  Processing %s' % (ljet,)
        for bgid in BgList:
            print 'Processing %s' % (bgid,)
            for flist in os.popen('ls lists/list__*.txt | grep %s' % (bgid,)).readlines():



                #print '------------------------'
                #print flist
                flist = flist[0:-1]
                # print flist
                tokens=flist.split('.')
                tag=tokens[0]
                tag=tag.replace('lists/list__', '')
                #print 'Tag: %s' % (tag,)
                ## prepare command:

                normalizationdir = '%s/share/data/NEvents_%s/' % (mambodir, production,)
                normalizationfile = os.popen('cd %s ; ls *.n | grep %s' % (normalizationdir, tag)).readlines()
                if len(normalizationfile) == 1:
                    lumifile = normalizationfile[0][:-1]
                else:
                    # MORE CARE NEEDED FOR AFII AND FULLSIM SAMPLES!!
                    lumifile = normalizationfile[0][:-1] ## TO FINISH
                #print lumifile

                cfg=basecfg
                cfg=cfg.replace('_ll_', '_%s_' % (ljet,))

                
                newcfg=cfg
                newcfg = newcfg.replace('eos', '%s_%s' % (syst,tag))
                cfg = cfg.replace('_eos', '')
                # print cfg, newcfg
                # make the file config!
                cmd='cat control/%s | sed "s|lists/list_eos_new_mc.txt|%s|g" | sed "s|nominal|%s|g" | sed "s|MAMBODIR|%s|g" | sed "s|LUMIFILE|%s|g"> control/%s' % (cfg, '', syst, mambodir, lumifile, newcfg)
                #print cmd
                os.system(cmd)
 




                out='%s/histograms_PowHeg_%s_%s.root' % (outdir,tag, ljet,)
                cmd='cd %s ; . setup_AnalysisRelease_prague.sh ; cd run ; runMAMbo -p %s/run/control/%s -f %s/%s -o %s' % (mambodir, mambodir, newcfg, path, flist, out,)
                print cmd
            
            
