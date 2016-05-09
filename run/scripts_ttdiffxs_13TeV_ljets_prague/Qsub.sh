#!/bin/bash

# jk according to jarka

cd $MAMBODIR
. setup_AnalysisRelease_prague.sh
cd -

# usage:
#  run on a subset by excluding some filelists:
#    ./scripts/Qsub.sh -v "aao|aam.mujets|aan|WW"
# run on a subset by grepping some filelists:
#    ./scripts/Qsub.sh "aao|aam.mujets|aan|WW"

version=v00

scriptbase=_submit

### !!!
SkipAlreadyOutput=1
# if you really know what you're doing...
#SkipAlreadyOutput=0



cp $X509_USER_PROXY $HOME/myproxy
path=$MAMBODIR/run/

# default:
logdir=/raid7_atlas2/${USER}/mambo_logs/
mkdir -p $logdir


if [ ! -z ${TOP_SITE} ]
then
   logdir=$(readValue "base_log_dir")
fi

mkdir -p $logdir

# Choose here:
# for short jobs:
queue=iatlas
# for long jobs:
# DEFAULT:
# queue=gridatlas

if [ ! -z ${TOP_SITE} ]
then
    queue=$(readValue "queue")
fi

echo "Submission to queue $queue"

if [ $# -gt 0 ] ; then
  if [ $1 == "-v" ] ; then
    shift
    echo "Excluding requested $* ..."
    Scripts=`cd $path ; ls _submit*_a?? | egrep -v "$*"`
  else
   echo "Grepping requested $* ... "
   Scripts=`cd $path ; ls _submit*_a?? | egrep "$*"`
  fi
else
  echo "Standard running..."
  Scripts=`cd $path ; ls _submit*_a??`
fi

outfilelistForChecks=_outfilelistForChecks.txt
rm $outfilelistForChecks

for script in $Scripts ; do 

  cis=$(echo ${script} |sed -e "s#${scriptbase}.##g;s#.sh##g" )
  echo "CIS=$cis"

  # skip job if output already present:
  outfile=`cat ${path}${script} | cut -d \- -f 4 | cut -d " " -f 2`
  echo $outfile >> $outfilelistForChecks

  echo  $outfile
  if [ $SkipAlreadyOutput == 1 ] && [ -f $outfile ] ; then
    echo "===> Skipping, as output already exists!"
    continue
  fi
  #echo "OK, will run depending on queue status..."
  ## delay Loop by Olda, to wait until queue is able to accept more jobs
  #GO=0
  #sleep1=60
  #sleep2=0.3
  #while [ $GO -eq 0 ]
  #do
  #    NJOBS=`qstat -u $USER | grep $queue | wc | awk  '{print $1 }'` 
  #    echo $NJOBS
  #    if [ $((NJOBS)) -gt 300 ]; then 
  #        echo "Running jobs $NJOBS -> Will sleep $sleep1 and wait with jobs submission..."
  #        sleep $sleep1
  #    else
  #        GO=1
  #        sleep $sleep2
  #    fi
  #done


  echo "OK, submitting!"
  echo "  qsub -q ${queue} -o $logdir/log.${scriptbase}.$cis.${version}.stdout -e $logdir/log.${scriptbase}.$cis.${version}.stderr ${path}${script} "
  ### !!! 
  qsub      -q ${queue} -o $logdir/log.${scriptbase}.$cis.${version}.stdout -e $logdir/log.${scriptbase}.$cis.${version}.stderr ${path}${script}
done



