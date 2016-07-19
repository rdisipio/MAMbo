#!/bin/bash
# set -x
patterns="DiTop Wjets Zjets Diboson ttV Stop"

rm -v lumiList.txt


list=`find output/ -name "tt_diffxs_13TeV.mc.DiTop*.root" -o -name "tt_diffxs_13TeV.mc.Wjets*.root" -o -name "tt_diffxs_13TeV.mc.Zjets*.root" -o -name "tt_diffxs_13TeV.mc.Diboson*.root" -o -name "tt_diffxs_13TeV.mc.ttV*.root" -o -name "tt_diffxs_13TeV.mc.Stop*.root" -type f`
for f in $list
do
        echo "$f"
        if [ -h $f ] #is a symbolic link
        then
                echo "it's a link!"
        else
                echo $f >> lumiList.txt
                filename=`echo $f | cut -d/ -f3 | sed s#/#_#g` 
                batchid="lumiRescaler.$filename"
                script="../jobs/$batchid.sh"
                log="../logs/$batchid.log"
                cat > $script << A
        root -b -q 'resolved_LumiRescaler.C("$f" )'

A
        fi

        # chmod +x $script
        #./$script
        #             bsub -oe -oo $log -J $batchid -q T3_BO_LOCAL $script

done
