#!/bin/bash
#set -x
analysis=tt_diffxs_13TeV
#outtag=TTbarResolved_resolved

systs="nominal nocut"
#systs=$(cat systematics.dat) # | grep JET`
systs="nominal nocut $(cat resolved_kinematic_systematics.dat )"
decays="nofullhad ljets"
decays="nofullhad"
systs="nominal `cat resolved_*dat`"
systs="nominal nocut"
production=TTDIFFXS_62
for syst in $systs
do
	mkdir -p output/$syst
	for decay in $decays
	do
		#syst=nominal

		#paramsdir=${MAMBODIR}/share/control/analysis_params/${outtag}	

		
		samples=mc.410000.PowhegPythiaEvtGen.e3698_s2608_s2183_r7267_r6282_p2516.${production}_v5.txt

		[ ! -z $1 ] && samples=$(cat $1)
		echo "Running on $samples"
		for sample in $samples
		do
			filelistdir=$PWD/filelists_${production}/
			filelist=$filelistdir/$sample

			dsid=$(echo $sample | cut -d. -f2)
			normalizationfile=$(echo $sample | sed s/mc.// | sed s/txt/evt.n/)
			normalizationdir=${MAMBODIR}/share/data/NEvents_${production}/
			normalizationfile=${normalizationdir}/${normalizationfile}
			
			if [ $syst == "nocut" ]
			then
				template=$PWD/Resolved13TeV.nocut.xml.template
			else
				template=$PWD/Resolved13TeV.xml.template
			fi

		
			sendOnce=0
		#set -x


			for ch in el mu
			do
				if [ $ch == "el" ]
				then
					#check if it's a muon systematic
					if [[ $syst == MUON* ]]
					then 
						echo "Muon systematic for el channel: $syst"
			#			continue
					fi

					
				fi
				if [ $ch == "mu" ]
				then
					#check if it's a muon systematic
					if [[ $syst == EG* ]]
					then 
						echo "Electron systematic for mu channel: $syst"
			#			continue
					fi

					
				fi			
				echo "INFO: submitting DiTop dsid=$dsid channel ${ch} decay ${decay}"

				[ $ch == "el" ] && ch_tag="electron"	
				[ $ch == "mu" ] && ch_tag="muon"

				filelist_mc=$filelist
				gridtag=$(echo $sample | cut -d. -f4 )
				simulationtype=$(echo $gridtag | cut -d_ -f2)

				for flist in $(ls ${filelist}.??)
				do
					batchid=$(echo ${flist} | grep -oE "[^.]+$")

					flist_mc=$( echo ${flist} | sed "s/.${ch}.txt/.mc.txt/" )
					
					if [[ $simulationtype == "s"* ]]
					then
						echo full sim!
						tag=${analysis}.mc.DiTop.${dsid}.${ch}.${syst}.${decay}
					else
						tag=${analysis}.mc.AFII.DiTop.${dsid}.${ch}.${syst}.${decay}
					fi
					params=$PWD/control/analysis_params/13TeV_ljets_resolved/config/${tag}.${batchid}.xml
					cp $template ${params}

					# 	 params=Resolved13TeV_${ch}.${syst}.${decay}.${batchid}.xml
					#          cp Resolved13TeV.xml.template ${params}
					if [ $syst != "nocut" ]
					then
						sed -i "s|@SYST@|${syst}|"     ${params}
					else
						sed -i "s|@SYST@|NOMINAL|"     ${params}
					fi
					sed -i "s|@CHANNEL@|${ch_tag}|"     ${params}
					sed -i "s|@MCFILELIST@|${flist_mc}|"  ${params}
					sed -i "s|@NORMFILE@|${normalizationfile}|"  ${params}
					sed -i "s|@DECAY@|${decay}|"  ${params}
					mkdir -p output_${production}/${syst}
					outfile=${syst}/${tag}.histograms.root.${batchid}
					jobname=${tag}.${batchid}

					echo ${params}  
					echo ${flist_mc}

					echo "Submitting ${jobname}"
					MAMbo-submit.sh -p ${params} -f ${flist} -o ${outfile} -j ${jobname}
					if [ $sendOnce -eq 1 ]
					then
						break
					fi
				done
			done


			echo
		done
	done
done
