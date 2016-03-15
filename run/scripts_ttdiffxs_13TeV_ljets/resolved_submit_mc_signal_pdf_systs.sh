#!/bin/bash
#set -x

function MakePDFSysts
{

	systs=""
	#ct14nlo
	for i in {0..56}
	do
		if [ $# == 1 ]
		then
			if [ $1 != "ct14nlo" ]
			then
				break
			fi
		fi
		systs="PDF:CT14nlo:$i ${systs}"		
	done
	#NNPDF30_nlo_as_0118
	for i in {0..100}
	do
		if [ $# == 1 ]
		then
			if [ $1 != "NNPDF30_nlo_as_0118" ]
			then
				break
			fi
		fi	
		systs="PDF:NNPDF30_nlo_as_0118:$i ${systs}"
	done
	#MMHT2014nlo68cl
	for i in {0..50}
	do
		if [ $# == 1 ]
		then
			if [ $1 != "MMHT2014nlo68cl" ]
			then
				break
			fi
		fi	
		systs="PDF:MMHT2014nlo68cl:$i ${systs}"
	done
	#PDF4LHC15_nlo_30
	for i in {0..30}
	do
		if [ $# == 1 ]
		then
			if [ $1 != "PDF4LHC15_nlo_30" ]
			then
				break
			fi
		fi
		systs="PDF:PDF4LHC15_nlo_30:$i ${systs}"
	done
	#PDF4LHC15_nlo_asvar
	for i in {0..1}
	do
		if [ $# == 1 ]
		then
			if [ $1 != "PDF4LHC15_nlo_asvar" ]
			then
				break
			fi
		fi
		systs="PDF:PDF4LHC15_nlo_asvar:$i ${systs}"
	done
	echo $systs
}


pdfsysts=`MakePDFSysts $1`



analysis=tt_diffxs_13TeV
#outtag=TTbarResolved_resolved

systs="nominal nocut"
#systs=$(cat systematics.dat) # | grep JET`
#systs=$(cat resolved_kinematic_systematics.dat | grep 19)
decays="nofullhad ljets"
decays="nofullhad"
production=TTDIFFXS_62




for pdfsyst in `echo $pdfsysts`
do
	pdfname=`echo $pdfsyst | cut -d: -f2`
	variation=`echo $pdfsyst | cut -d: -f3`
	for syst in $systs
	do
		mkdir -p output/${pdfname}_${variation}_$syst
		for decay in $decays
		do
			#syst=nominal

			#paramsdir=${MAMBODIR}/share/control/analysis_params/${outtag}	

			
			samples=mc.410003.aMcAtNloHerwigppEvtGen.e4441_a766_a810_r6282_p2516.TTDIFFXS_62_v5.txt

			echo "Running on $samples"
			for sample in $samples
			do
				filelistdir=$PWD/filelists_${production}/
				filelist=$filelistdir/$sample

				dsid=$(echo $sample | cut -d. -f2)
				normalizationfile=$(echo $sample | sed s/mc.// | sed s/.txt/_${pdfname}_${variation}.evt.n/)
				normalizationdir=${MAMBODIR}/share/data/NEvents_${production}/
				normalizationfile=${normalizationdir}/${normalizationfile}
				
				if [ $syst == "nocut" ]
				then
					template=$PWD/Resolved13TeV.nocut.xml.template
				else
					template=$PWD/Resolved13TeV.sf_syst.xml.template
				fi

			
				sendOnce=0
			#set -x


				for ch in el mu
				do	
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
							tag=${analysis}.mc.DiTop.${dsid}.${ch}.${pdfname}.${variation}.${syst}.${decay}
						else
							tag=${analysis}.mc.AFII.DiTop.${dsid}.${ch}.${pdfname}.${variation}.${syst}.${decay}
						fi
						params=$PWD/control/analysis_params/13TeV_ljets_resolved/config/${tag}.${batchid}.xml
						cp $template ${params}

						# 	 params=Resolved13TeV_${ch}.${syst}.${decay}.${batchid}.xml
						#          cp Resolved13TeV.xml.template ${params}
						if [ $syst != "nocut" ]
						then
							sed -i "s|@SYST@|${pdfsyst}|"     ${params}
						else
							sed -i "s|@SYST@|${pdfsyst}|"     ${params}
						fi
						sed -i "s|@CHANNEL@|${ch_tag}|"     ${params}
						sed -i "s|@MCFILELIST@|${flist_mc}|"  ${params}
						sed -i "s|@NORMFILE@|${normalizationfile}|"  ${params}
						sed -i "s|@DECAY@|${decay}|"  ${params}
						mkdir -p output_${production}/${syst}
						outfile=${pdfname}_${variation}_${syst}/${tag}.histograms.root.${batchid}
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
