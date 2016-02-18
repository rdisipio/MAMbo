#!/bin/bash

analysis=tt_diffxs_13TeV
#outtag=TTbarResolved_resolved

systs="nominal nocut"
shapes="tt_rapidity tt_m tt_pt t_pt"
#systs=$(cat systematics.dat) # | grep JET`
decays="nofullhad ljets"
decays="nofullhad"
production=TTDIFFXS_55
for syst in $systs
do
	for shape in $shapes 
	do
		mkdir -p output/$shape/$syst
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
				template=$PWD/Resolved13TeV.stress.nocut.xml.template
			else
				template=$PWD/Resolved13TeV.stress.xml.template
			fi
			samples=mc.410000.PowhegPythiaEvtGen.e3698_s2608_s2183_r7267_r6282_p2516.${production}_v2.txt
			for sample in $samples
			do

				filelistdir=$PWD/filelists_${production}/
				filelist=$filelistdir/$sample
				dsid=$(echo $sample | cut -d. -f2)
				normalizationfile=$(echo $sample | sed s/mc.// | sed s/txt/evt.n/)
				normalizationdir=${MAMBODIR}/share/data/NEvents_${production}/
				normalizationfile=${normalizationdir}/${normalizationfile}
		
				sendOnce=0
			#set -x


				for ch in el mu
				do
				
					echo "INFO: submitting DiTop dsid=$dsid channel ${ch} decay ${decay}"

					[ $ch == "el" ] && ch_tag="electron"	
					[ $ch == "mu" ] && ch_tag="muon"

					filelist_mc=$filelist

					for flist in $(ls ${filelist}.??)
					do
						batchid=$(echo ${flist} | grep -oE "[^.]+$")

						flist_mc=$( echo ${flist} | sed "s/.${ch}.txt/.mc.txt/" )

						tag=${analysis}.mc.DiTop.${dsid}.${ch}.${shape}.${syst}.${decay}

						params=$PWD/control/analysis_params/13TeV_ljets_resolved/config/Resolved13TeV.${ch}.${shape}.${syst}.${decay}.${batchid}.xml
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
						sed -i "s|@STRESS@|${shape}|" ${params}
						outfile=${shape}/${syst}/${tag}.histograms.root.${batchid}
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
done
