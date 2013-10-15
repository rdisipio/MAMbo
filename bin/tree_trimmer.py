#!/usr/bin/env python
"""
NAME
    tree_trimmer.py - general ROOT tree skimmer and slimmmer

SYNOPSIS
    tree_trimmer.py [OPTIONS] file1.root [file2.root ... skim.py] [OPTIONS]

DESCRIPTION
    This is a very general and configurable script for skimming (skipping
    events) and slimming (dropping branches) ROOT TTrees.

    An example call is:
    tree_trimmer.py -t mytree -b vars.txt -s skim -k 'CollectionTree,tauPerfMeta/TrigConfTree' *.root skim.py

    This call would chain together TTrees named 'mytree' in all '*.root' files.
    Then it would turn-off the branch status of all branches in mytree, except
    for those listed in vars.txt, which can look something like this:

    EventNumber
    RunNumber
    lbn
    el_*

    Then, it would skim mytree according to the skim(tree) function specified
    with the option -s, and implemented in skim.py.  The additional trees
    specified by the option -k, would also be kept in their entirety.

    The counts of all events and the events passing the skim are recorded in
    the first and second bins of a histogram, 'h_n_events', that is saved in
    each output file.

OPTIONS
    -h, --help
        Prints this docstring and exits.
        
    -b FILE, --branches_on_file=FILE
        When specified, FILE should be the name of a file containing branch
        names, or fnmatch patterns for branch names, one per line.
        (# comments are allowed.)  This specifies the branches that
        should be turned-on, all others are turned-off.

    -B FILE, --branches_off_file=FILE
        When specified, FILE should be the name of a file containing branch
        names, or fnmatch patterns for branch names, one per line.
        (# comments are allowed.)  This specifies the branches that
        should be turned-off, even if they were turned-on in the
        branches_off_file above; good for specifying exceptions.

    -k 'TREE1,DIR/TREE2,...', --keep_trees='TREE1,DIR/TREE2,...'
        Comma-separated names of additional trees (metadata, config, ...) that
        should be coppied in their entirety, in addtion to the main tree being
        skimmed.

    -m NUM, --max_events=NUM
        Max number of events to run over the input trees.

    -M MB, --max_tree_size=MB
        Specifies the ROOT.TTree.SetMaxTreeSize in MB.  By default, ROOT should
        make it 1900 MB.

    -o FILE, --out=FILE
        Specifies the name of the output file, 'skim.root' by default.

    -s FUNC, --skim=FUNC
        Specifies the name of a user-supplied skimming function, FUNC(tree),
        that should return True/False if the current entry in tree passes
        the skim.  The user should implement FUNC in a python file and provide
        it as a command-line argument.  For example, to skim for events that
        have a 20 GeV electron candidate, one could write:

            def skim(ch):
                for i_el in xrange(ch.el_n):
                    if ch.el_pt[i_el] > 20000.0:
                        return True
                return False

    -t NAME, --tree=NAME
        Specifies the name of the main tree to be skimmed (skipping events) and
        slimmed (dropping branches), 'tauPerf' by default.

AUTHOR
    Ryan Reece  <ryan.reece@cern.ch>

COPYRIGHT
    Copyright 2011 Ryan Reece
    License: GPL <http://www.gnu.org/licenses/gpl.html>

SEE ALSO
    ROOT <http://root.cern.ch>

TO DO
    - Optionally copy all additional objections in input files.  One has to
      pragram support for all ROOT object types that may copy differently,
      and treat the main tree as a special case.
    - Does not work if output exceeds one file.  The trees appear to be
      duplicated in the output files.
    - Progress bar?

2011-06-15
"""
#------------------------------------------------------------------------------

## std
import optparse
import fnmatch
import os
import time

## ROOT
import ROOT
ROOT.gROOT.SetBatch(True)

## my modules

## local modules

#ROOT.gROOT.LoadMacro("stl_loader.h+")
_path_of_this_file = os.path.realpath(os.path.dirname(__file__))
_stl_loader_path = os.path.join(_path_of_this_file, 'stl_loader.h')
ROOT.gROOT.ProcessLine('.L %s+' % _stl_loader_path)
#ROOT.gROOT.ProcessLine('.L stl_loader.h+')


#_____________________________________________________________________________
def options():
    parser = optparse.OptionParser(description="hello_world")
    parser.add_option('-b', '--branches_on_file', dest='branches_on_file', type=str, default='')
    parser.add_option('-B', '--branches_off_file', dest='branches_off_file', type=str, default='')
    parser.add_option('-R', '--branches_read_file', dest='branches_read_file', type=str, default='')
    parser.add_option('-k', '--keep_trees', dest='keep_trees', type=str, default='')
    parser.add_option('-m', '--max_events', dest='max_events', type=int, default=-1)
    parser.add_option('-M', '--max_tree_size', dest='max_tree_size', type=int, default=0)
    parser.add_option('-o', '--out', dest='out', type=str, default='skim.root')
    parser.add_option('-s', '--skim', dest='skim', type=str, default='')
    parser.add_option('-t', '--tree', dest='tree', type=str, default='tauPerf')
    return parser.parse_args()


#______________________________________________________________________________
def main():
    ops, args = options()

    args = split_comma_args(args)

    input_files = filter(lambda arg: fnmatch.fnmatch(arg, '*.root*') , args)
    py_configs = filter(lambda arg: fnmatch.fnmatch(arg, '*.py') , args)

    ## exec config files to declare any skimming functions
    for py in py_configs:
        execfile(py)
    
    ## build the chain
    ch_in = ROOT.TChain(ops.tree)
    for f in input_files:
        ch_in.Add(f)

    ## max_events
    max_events = ch_in.GetEntries()
    if ops.max_events > 0 and max_events > ops.max_events:
        max_events = ops.max_events

    ## branch status
    main_tree_branches_on = get_branches_status_on(ch_in)
    n_branches_in = len(main_tree_branches_on)
    n_branches_out = set_status_of_branches(
            ch_in,
            branches_on_file = ops.branches_on_file,
            branches_off_file = ops.branches_off_file)

    ## start new file and clone tree
    new_file = ROOT.TFile.Open(ops.out, 'RECREATE')
    ch_out = ch_in.CloneTree(0)

    ## reset the status of branches in the main tree
    the_braches_on_files = ops.branches_on_file
    if ops.branches_read_file:
        the_braches_on_files = [ops.branches_on_file, ops.branches_read_file]
    n_branches_read = set_status_of_branches(
            ch_in,
            branches_on_file = the_braches_on_files,
            branches_off_file = ops.branches_off_file)

    ## max_tree_size
    if ops.max_tree_size:
        ch_out.SetMaxTreeSize(ops.max_tree_size*1000000) # ops.max_tree_size in MB

    tree_names_to_keep = filter(None, ops.keep_trees.split(','))

    skim_func = None
    if ops.skim:
        skim_func = eval(ops.skim)

    ## event loop
    n_events = 0
    n_events_passed = 0
    i_prev_infile = -1
    i_prev_outfile = -1
    outfile_names = []
    infile_names = []
    infile_names_list = []

    counter = None
    counter_weighted = None
    counters = []
    counters_weighted = []

    for i_event in xrange(max_events):
        i_entry = ch_in.LoadTree(i_event)
        ch_in.GetEntry(i_event)

        if i_event % 1000 == 0:
            print 'Processing event %i of %i' % (i_event, max_events)

        i_infile = ch_in.GetTreeNumber()
        i_outfile = ch_out.GetFileNumber()

        ## check if the output file changed ##
        if i_outfile != i_prev_outfile:
            outfile_name = ch_out.GetCurrentFile().GetName()
            outfile_names.append(outfile_name)
            infile_names = []
            infile_names_list.append(infile_names)
            print 'Writing to output file: %s' % outfile_name
            counter = MyCounter(name='h_n_events', label='tree_trimmer.py $date', init_file=input_files[0])
            counter_weighted = MyCounter(name='h_n_events_weighted', label='tree_trimmer.py $date', init_file=input_files[0])
            counters.append(counter)
            counters_weighted.append(counter_weighted)

        ## check if the input file changed ##
        if i_infile != i_prev_infile:
            counter.add_tfile(ch_in.GetCurrentFile())
            counter_weighted.add_tfile(ch_in.GetCurrentFile())
            infile_name = ch_in.GetCurrentFile().GetName()
            print 'Reading from input file: %s' % infile_name

        ## check if the input or output file changed ##
        if i_infile != i_prev_infile or i_outfile != i_prev_outfile:
            infile_name = ch_in.GetCurrentFile().GetName()
            infile_names.append(infile_name)

        # count sum of mc event weights
        mcevt_weight = 0.0
        if hasattr(ch_in, 'mc_event_weight'):
            mcevt_weight = ch_in.mc_event_weight
        elif hasattr(ch_in, 'mcevt_weight'):
            vec_vec_double = ch_in.mcevt_weight
            if len(vec_vec_double):
                vec_double = vec_vec_double[0]
                if len(vec_double):
                    mcevt_weight = vec_double[0]
                else:
                    print 'WARNING: len(vec_double) = ', len(vec_double)
            else:
                print 'WARNING: len(vec_vec_double) = ', len(vec_vec_double)

        if not mcevt_weight in (-1.0, 0.0, 1.0):
            print 'WARNING: mcevt_weight = ', mcevt_weight

        # count all events
        n_events += 1
        counter.count_all()
        counter_weighted.count_all(mcevt_weight)

        passed_skim = True
        if not skim_func is None:
            passed_skim = skim_func(ch_in)

        if passed_skim:
            # count events passing skim
            ch_out.Fill() # fill the skimmed tree
            n_events_passed += 1
            counter.count_pass()
            counter_weighted.count_pass(mcevt_weight)

        i_prev_infile = i_infile
        i_prev_outfile = i_outfile
        prev_outfile_name = ch_out.GetCurrentFile().GetName()
        ## end of event-loop
    
#    ch_out.Print()
    
    ch_out.AutoSave()
#    ch_out.AutoSave('FlushBaskets')

#    ch_out.GetCurrentFile().Write()
    ch_out.GetCurrentFile().Close()
    
    print 'The skim has finished.'
    print 'n_events        = %16i' % n_events
    print 'n_events_passed = %16i' % n_events_passed
    print 'skim efficiency = %16.3g%%' % (100.0*float(n_events_passed)/n_events)
    print 'n_branches_in   = %16i' % n_branches_in
    print 'n_branches_read = %16i' % n_branches_read
    print 'n_branches_out  = %16i' % n_branches_out
    
    print 'Saving h_n_events histograms and additional trees...'

    # temporarily SetMaxTreeSize big so as not to change files when writing the addtional trees
    ROOT.TTree.SetMaxTreeSize(3000*1000000)

    for outfile_name, infile_names, counter, counter_weighted in zip(outfile_names, infile_names_list, counters, counters_weighted):
        print outfile_name, infile_names
        f_out = ROOT.TFile.Open(outfile_name, 'UPDATE')
        f_out.cd()
        counter.hist.Write()
        counter_weighted.hist.Write()
        for tree_name in tree_names_to_keep:
            print 'Saving tree: %s' % tree_name
            cwd = f_out
            tree_dirname = os.path.dirname(tree_name)
            if tree_dirname:
                print 'Creating directory: %s' % tree_dirname
                cwd = make_root_dir(f_out, tree_dirname)
            tree_out = None
            for i_infile, infile_name in enumerate(infile_names):
                f_in = ROOT.TFile.Open(infile_name, 'READ')
                tree_in = f_in.Get(tree_name)
                cwd.cd()
                if i_infile == 0:
                    tree_out = tree_in.CloneTree(0)
                tree_in.CopyAddresses(tree_out)
                tree_out.CopyEntries(tree_in)
                f_in.Close()
            tree_out.AutoSave()
#            tree_out.Write()
        f_out.Close()
    print 'Done.'

#__________________________________________________________________________
class MyCounter(object):
    def __init__(self,
            name = 'h_n_events',
            label = '',
            init_file = ''):
        self.name = name
        label = label.replace('$date', time.strftime('%Y-%m-%d'))
        self.label = label
        self.initialize(init_file)
        self._sumw = 0.0
        self._sumw2 = 0.0
    #______________________________________________________________________
    def initialize(self, init_file=''):
        if init_file:
            f = ROOT.TFile.Open(init_file)
            h = f.Get(self.name)
            self.bin = 2
            x_axis = None
            if h:
                print 'Counter histogram: %s found.' % self.name
                self.hist = h.Clone(self.name)
                self.hist.SetDirectory(0) # memory, not TFile, resident
                x_axis = self.hist.GetXaxis()
                for i in xrange(1, x_axis.GetNbins()+1):
                    if x_axis.GetBinLabel(i) == '':
                        self.bin = i
                        break
            else:
                self.hist = ROOT.TH1D(self.name, '', 20, 0.5, 20.5)
                self.hist.SetDirectory(0) # memory, not TFile, resident
                x_axis = self.hist.GetXaxis()
                x_axis.SetBinLabel(1, 'all')
            x_axis.SetBinLabel(self.bin, self.label)
            del x_axis, h
            f.Close()
            print 'Filling counts in %s bin = %i' % (self.name, self.bin)
    #______________________________________________________________________
    def count_pass(self, weight=1.0):
        self.hist.Fill(self.bin, weight)
    #______________________________________________________________________
    def count_all(self, weight=1.0):
        ## only count all on first skim
        if self.bin == 2:
            self.hist.Fill(1, weight)
        self._sumw += weight
        self._sumw2 += weight*weight
    #______________________________________________________________________
    def add_tfile(self, tfile):
        h = tfile.Get(self.name)
        if h:
            self.hist.Add(h)           
        else:
            print 'No %s bookkeeping histogram found in input file.' % self.name
        del h

#__________________________________________________________________________
def get_branches_status_on(tree):
    branches_all = [ b.GetName() for b in tree.GetListOfBranches() ]
    return filter(lambda bn: tree.GetBranchStatus(bn), branches_all)

#__________________________________________________________________________
def set_status_of_branches(
        tree,
        branches_on = None,
        branches_off = None,
        branches_on_file = '',
        branches_off_file = ''):

    branches_on = make_default_list(branches_on)
    branches_off = make_default_list(branches_off)
    branches_on_file = make_default_list(branches_on_file)
    branches_off_file = make_default_list(branches_off_file)

    ## get the set of all branches in the tree
    branches_all = [ b.GetName() for b in tree.GetListOfBranches() ]
    branches_to_use = branches_all

    if branches_on_file or branches_on or branches_off or branches_off_file:
        if branches_on_file or branches_on:
            patterns_on = branches_on
            for bf in branches_on_file:
                ## parse branches_on_file
                patterns_on.extend( parse_lines(bf) )

            ## filter for branches matching branches_on_file
            branches_to_use = filter(lambda b: any(fnmatch.fnmatch(b, p) for p in patterns_on), branches_all)
        
        if branches_off_file or branches_off:
            patterns_off = branches_off
            for bf in branches_off_file:
                ## parse branches_off_file
                patterns_off.extend( parse_lines(bf) )

            ## filter for branches not matching branches_off_file
            branches_to_use = filter(lambda b: not any(fnmatch.fnmatch(b, p) for p in patterns_off), branches_to_use)

    ## set all branches off first
    tree.SetBranchStatus('*', 0)

    ## turn on just what we need
    n_branches_out = 0
    for bn in branches_to_use:
        tree.SetBranchStatus(bn, 1)
        n_branches_out += 1

    return n_branches_out

#______________________________________________________________________________
def parse_lines(fn):
    lines = []
    f = open(fn)
    for line in f:
        line = line.split('#')[0].strip() # remove comments
        if line:
            lines.append(line)
    f.close()
    return lines


#______________________________________________________________________________
def split_comma_args(args):
    new_args = []
    for arg in args:
        new_args.extend( arg.split(',') )
    return new_args


#______________________________________________________________________________
def make_default_list(x):
    if x:
        if isinstance(x, list):
            return x
        else:
             return [x]
    else:
        return []


#______________________________________________________________________________
def walk(top, topdown=True):
    """ 
    os.path.walk like function for TDirectories.
    Return 4-tuple: (dirpath, dirnames, filenames, top)
        dirpath = 'file_name.root:/some/path' # may end in a '/'?
        dirnames = ['list', 'of' 'TDirectory', 'keys']
        filenames = ['list', 'of' 'object', 'keys']
        top = this level's TDirectory
    """
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    assert isinstance(top, ROOT.TDirectory)
    names = [k.GetName() for k in top.GetListOfKeys()]
    dirpath = top.GetPath()
    dirnames = []
    filenames = []
    ## filter names for directories
    for k in names:
        d = top.Get(k)
        if isinstance(d, ROOT.TDirectory):
            dirnames.append(k)
        else:
            filenames.append(k)
    ## sort
    dirnames.sort()
    filenames.sort()
    ## yield
    if topdown:
        yield dirpath, dirnames, filenames, top 
    for dn in dirnames:
        d = top.Get(dn)
        for x in walk(d, topdown):
            yield x
    if not topdown:
        yield dirpath, dirnames, filenames, top 

#______________________________________________________________________________
def make_root_dir(f, dir):
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    dir.rstrip('/')
    dir_split = dir.split('/')
    lead_dir = dir_split[0]
    sub_dirs = dir_split[1:]

    d = f.GetDirectory(lead_dir)
    if not d:
        d = f.mkdir(lead_dir)
    
    if sub_dirs:
        return make_root_dir(d, '/'.join(sub_dirs))
    else:
        return d


#______________________________________________________________________________
if __name__ == '__main__': main()
