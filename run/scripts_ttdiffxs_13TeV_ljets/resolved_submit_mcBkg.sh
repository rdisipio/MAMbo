#!/bin/bash
#set -x
analysis=tt_diffxs_13TeV
#outtag=TTbarResolved_resolved
systs=nominal
production=TTDIFFXS_62
nomalizationfilepath=${MAMBODIR}/share/data/NEvents_${production}/
filelistdir=$PWD/filelists_${production}/
#paramsdir=${MAMBODIR}/share/control/analysis_params/${outtag}
sendOnce=0
for syst in $systs
        if [[ $syst == "scale"* ]]
        then
                template=Resolved13TeVBkg.sf_syst.xml.template
        else
                template=Resolved13TeVBkg.xml.template
        fi
        for ch in el mu
        do

           [ $ch == "el" ] && ch_tag="electron"
           [ $ch == "mu" ] && ch_tag="muon"
              
           filelist=AllBkgTTDIFFXS_62.txt

           while read flist           
             do 
               
               if [[ "x$flist" == "x#"* ]]; then
                 continue
               fi
         
                 dsid=`echo $flist | cut -d. -f2`

                 nomalizationfile=${nomalizationfilepath}/$( echo ${flist} | sed s/mc.// | sed "s/.txt/.evt.n/" )
                 tag=${analysis}.mc.bkg.${dsid}.${ch}.${syst}
                mkdir -p output_${production}/${syst}
                 outfile=${syst}/${tag}.histograms.root
                 jobname=${tag}
                 params=$PWD/control/analysis_params/13TeV_ljets_resolved/config/Resolved13TeV.${dsid}.${ch}.${syst}.xml
                 cp  ${params}

                 sed -i "s|@CHANNEL@|${ch_tag}|"     ${params}
                 sed -i "s|@NORMFILE@|${nomalizationfile}|"  ${params}
                 sed -i "s|@SYST@|${syst}|"  ${params}
                 jobname=${tag}

                 echo ${params}  
                 
               
                 echo "Submitting ${jobname}"
                 flist=${filelistdir}/${flist}
                 echo ${flist}
                 
                 MAMbo-submit.sh -p ${params} -f ${flist} -o ${outfile} -j ${jobname}
                if [ $sendOnce -eq 1 ]
                then
                        break
                fi		 
             done < ${filelist}


             echo
        done
done
