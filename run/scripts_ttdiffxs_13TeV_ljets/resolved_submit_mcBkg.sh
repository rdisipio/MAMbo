#!/bin/bash
#set -x
analysis=tt_diffxs_13TeV
#outtag=TTbarResolved_resolved
systs="wjets_stat wjets_syst"
systs="nominal wjets_stat wjets_syst $(cat resolved_*_systematics.dat )"
wjetsSysts="CA_up CA_down Fcc_up Fcc_down Flight_up Flight_down ttV_up Diboson_up Stop_up Zjets_up Fakes_up fakes_realEff_stat_D fakes_realEff_stat_U fakes_fakeEff_stat_D fakes_fakeEff_stat_U fakes_fakeEff_MCscale_D fakes_fakeEff_MCscale_U fakes_fakeEff_CR_S CA_2ex_up CA_2ex_down CA_3ex_up CA_3ex_down CA_4incl_up CA_4incl_down Fcc_up Fcc_down Fc_up Fc_down Flight_up Flight_down"
isWjets=0
wjetsRuns=$(cat Wjets.run )
wjetsSyst=nominal
production=TTDIFFXS_62
nomalizationfilepath=${MAMBODIR}/share/data/NEvents_${production}/
filelistdir=$PWD/filelists_${production}/
#paramsdir=${MAMBODIR}/share/control/analysis_params/${outtag}
sendOnce=0
systs="nominal"
systs=$wjetsSysts
systs="nominal $wjetsSysts $(cat resolved_*_systematics.dat )"
#systs="$wjetsSysts nominal"
systs="ttV_up Diboson_up Stop_up Zjets_up Fakes_up fakes_realEff_stat_D fakes_realEff_stat_U fakes_fakeEff_stat_D fakes_fakeEff_stat_U fakes_fakeEff_MCscale_D fakes_fakeEff_MCscale_U fakes_fakeEff_CR_S"
systs="Stop_up"
systs="nominal ttV_up Diboson_up Stop_up Zjets_up Fakes_up $wjetsSysts $(cat resolved_*_systematics.dat )"
systs="`cat resolved_bkg_systematics.txt`"
systs="CA_2ex_up CA_2ex_down CA_3ex_up CA_3ex_down CA_4incl_up CA_4incl_down Fcc_up Fcc_down Fc_up Fc_down Flight_up Flight_down"
systs="nominal `cat resolved_scale_systematics.dat resolved_kinematic_systematics.dat`"
systs="Fakes_up"
for syst in $systs
do
        mkdir -p output/$syst
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
          # filelist=missingZ.txt
          # filelist=ttVList.txt
          # filelist=ZjetsList.txt
           filelist=WjetsList.txt
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
                 cp $template  ${params}
				 
				wjetsSyst=nominal
				isWjets=0
				 if [[ ${wjetsRuns} == *"${dsid}"* ]]
				 then
					echo "It's a wjets sample!"
					isWjets=1
					wjetsSyst=$syst
				  fi
				  
				  systname=$syst
				  if [[ $wjetsSysts == *"${syst}"* ]]
				  then
						if [ $isWjets == "0" ]
						then
							echo $syst asked for non-wjet run $dsid, skipping
							continue
						fi
						systname="nominal"
						
				   fi
				 params=$PWD/control/analysis_params/13TeV_ljets_resolved/config/Resolved13TeV.${dsid}.${ch}.${syst}.xml
                 sed -i "s|@CHANNEL@|${ch_tag}|"     ${params}
                 sed -i "s|@NORMFILE@|${nomalizationfile}|"  ${params}
                 sed -i "s|@SYST@|${systname}|"  ${params}
                 sed -i "s|@ISWJETS@|${isWjets}|"  ${params}
                 sed -i "s|@WJETSSYST@|${wjetsSyst}|"  ${params}
                 jobname=${tag}

                 echo ${params}  
                 
               
                 echo "Submitting ${jobname}"
                 flist=${filelistdir}/${flist}
                 echo ${flist} $params
                 
                MAMbo-submit.sh -p ${params} -f ${flist} -o ${outfile} -j ${jobname}
                if [ $sendOnce -eq 1 ]
                then
                        break
                fi		 
             done < ${filelist}


             echo
        done
done
