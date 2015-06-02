#!/bin/sh

tag=_dilepton

./scripts/makeRunScriptsMC_sig_PowHeg_hdamp_eos_dilepton_split.sh > _run_dilepton${tag}.sh

  split -l 1 _run_dilepton${tag}.sh _run_dilepton${tag}_a
  chmod +x _run_dilepton${tag}_a*
  
  for i in `ls _run_dilepton${tag}_a*` ; do

    j=${i}_tmp
    echo "#!/bin/bash" > $j
    echo "" >> $j
    echo "cd $MAMBODIR" >> $j
    echo "source setup.sh" >> $j
    echo "cd run/" >> $j
    echo "" >> $j
    cat $i >> $j
    echo "" >> $j

    mv $j $i
    chmod +x $i

    outfile=`cat ${i} | grep root | cut -d \- -f 4 | cut -d " " -f 2`

    echo  "OK, calling bsub -q 8nh ${i}"
    ###!!!!
    if [ -f $outfile  ] ; then
      echo "    Skipping submission, out file exists!!!"
    else 
      echo "    Will submit..."
      #bsub -q 8nh ${i}
    fi
  done


