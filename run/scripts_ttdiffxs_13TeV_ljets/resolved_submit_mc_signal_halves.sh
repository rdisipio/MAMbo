#!/bin/bash

analysis=tt_diffxs_13TeV
#outtag=TTbarResolved_resolved

systs="nominal"
#systs=`cat systematics.dat`
decays="nofullhad ljets"
decays="nofullhad"
for i in 0 1
do
	for syst in $systs
	do
		for decay in $decays
		do
			#syst=nominal

			#paramsdir=${MAMBODIR}/share/control/analysis_params/${outtag}	

			dsid=410000
			[ ! -z $1 ] && dsid=$1

			#decay=nofullhad
			[ ! -z $2 ] && decay=$2

			if [ $syst == "nocut" ]
			then
				template=$PWD/Resolved13TeV.nocut.xml.template
			else
				template=$PWD/Resolved13TeV.nominal.nofullhad.half${i}.xml.template
			fi

			filelistdir=$PWD/filelists_TTDIFFXS_3/
			filelist=$filelistdir/410000.PowhegPythiaEvtGen.e3698_s2608_s2183_r6765_r6282_p2442.list

			nomalizationdir=${MAMBODIR}/share/data/NEvents13TeV/
			nomalizationfile=${MAMBODIR}/share/data/NEvents13TeV/410000.PowhegPythiaEvtGen.e3698_s2608_s2183_r6765_r6282_p2442.evt.n
	
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
						continue
					fi

				
				fi
				if [ $ch == "mu" ]
				then
					#check if it's a muon systematic
					if [[ $syst == EG* ]]
					then 
						echo "Electron systematic for mu channel: $syst"
						continue
					fi

				
				fi			
				echo "INFO: submitting DiTop dsid=$dsid channel ${ch} decay ${decay}"

				[ $ch == "el" ] && ch_tag="electron"	
				[ $ch == "mu" ] && ch_tag="muon"

				filelist_mc=$filelist

				for flist in $(ls ${filelist}.??)
				do
					batchid=$(echo ${flist} | grep -oE "[^.]+$")

					flist_mc=$( echo ${flist} | sed "s/.${ch}.txt/.mc.txt/" )

					tag=${analysis}.mc.DiTop.${dsid}.${ch}.${syst}.${decay}.half${i}

					params=$PWD/Resolved13TeV.${ch}.${syst}.${decay}.half${i}.${batchid}.xml
					cp $template ${params}

					# 	 params=Resolved13TeV_${ch}.${syst}.${decay}.${batchid}.xml
					#          cp Resolved13TeV.xml.template ${params}
					if [ $syst != "nocut" ]
					then
						sed -i "s|@SYST@|${syst}|"     ${params}
					fi
					sed -i "s|@CHANNEL@|${ch_tag}|"     ${params}
					sed -i "s|@MCFILELIST@|${flist_mc}|"  ${params}
					sed -i "s|@NORMFILE@|${nomalizationfile}|"  ${params}
					sed -i "s|@DECAY@|${decay}|"  ${params}
					mkdir -p output/${syst}
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
