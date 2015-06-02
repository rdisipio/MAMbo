#!/bin/sh

tag=_incl
#tag=_ljets

./scripts/makeRunScriptsMC_sig_PowHeg_hdamp_eos_split_halves.sh > _run_halves${tag}.sh

for h in 0 1 ; do

  cat _run_halves${tag}.sh | grep half${h} > _run_half${h}${tag}.sh
  split -l 1 _run_half${h}${tag}.sh _run_half${h}${tag}_a
  chmod +x _run_half${h}${tag}_a*
  
  for i in `ls _run_half${h}${tag}_a*` ; do

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
done

