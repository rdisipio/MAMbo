#!/bin/bash

SUBMISSION_TIMESTAMP=$(date +"%Y%m%d%H%M%S")

######################

function print_help {
    echo "To submit a MAMbo job to your batch system:"
    echo "$0 -p paramfile.xml -f file_list.txt [-n n_events_max] [-o output_file_name.root] [-j job_name] [-q queue]"
    exit
}

######################


if [ -z ${MAMBODIR} ]
then
  echo "MAMBODIR not set. Did you set up the environment first?"
  exit
fi

WORKDIR=${MAMBODIR}/run
jobdir=${WORKDIR}/jobs
logdir=${WORKDIR}/logs

if [[ -z ${MAMBOOUTPUTDIR} ]]
then
   outdir=${PWD}/output
else
   outdir=${MAMBOOUTPUTDIR}
fi

queue=T3_BO
backend=lsf #options are: lsf pbs
dryrun=0

jobname=MAMboJob_${SUBMISSION_TIMESTAMP}
paramsfile=UNSET
filelist=UNSET
nevtmax=-1
outfilename=mambo.histograms.root

while [ $# -gt 0 ] ; do
case $1 in
    -b) backend=$2             ; shift 2;;
    -p) paramsfile=$2          ; shift 2;;
    -f) filelist=$2            ; shift 2;;
    -n) nevtmax=$2             ; shift 2;;
    -o) outfilename=$2         ; shift 2;;
    -q) queue=$2               ; shift 2;;
    -j) jobname=$2             ; shift 2;;
    -d) dryrun=$2              ; shift 2;;
    -h) print_help             ; shift 2;;
    *)                           shift 1;;
esac
done

if [ -z $paramsfile ] 
then
    echo Params file not set. 
    exit
fi

if [ -z filelist ]
then
    echo File list not set
    exit
fi

# determine which backend to use
if [ "$backend" == "lsf" ]
then
   exe="bsub"
   logopts="-oe -oo"
   jobnameopts="-J"
else
   exe="qsub -V"
   logopts="-j oe -o"
   jobnameopts="-N"
fi


test -d $jobdir || mkdir -p $jobdir
test -d $logdir || mkdir -p $logdir
test -d $outdir || mkdir -p $outdir

jobfile=$jobdir/${jobname}.job.sh
logfile=$logdir/${jobname}.log

rm -fr $logfile


## NOW CREATE ON-THE-FLY THE SCRIPT TO BE SUBMITTED
echo job file: ${jobfile}

cat > ${jobfile} <<EOF
#!/bin/bash
#PBS -l nodes=1:ppn=8,walltime=2:00:00
#PBS -N $jobname
echo Running on \$HOSTNAME
date

cd ${WORKDIR}

source MAMbo-setenv.sh

time runMAMbo -p $paramsfile -f $filelist -n $nevtmax -o $outdir/$outfilename

echo "End of run"
date

EOF


# OK NOW SUBMIT THE JOB

chmod +x $jobfile

if [[ "${dryrun}" == "0" ]] 
then
  ${exe} -q $queue ${logopts} $logfile ${jobnameopts} $jobname $jobfile
else
  echo "Dry run. See ${jobfile}"
fi
