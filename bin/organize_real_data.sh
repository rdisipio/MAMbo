#!/bin/bash

BASEDIR=/gpfs_data/local/atlas/mromano/Resolved8TeV/minintuples-october

if [ -z ${MAMBODIR+x} ] 
then 
   echo "MAMbo environment not set"
   return
fi

FILELISTDIR=${MAMBODIR}/run/control/file_list/TTbarResolved/
echo "File lists will be stored in ${FILELISTDIR}"

periods=( "A" "B" "C" "D" "E" "G" "H" "I" "JK" "L" )
edges=(200804 202660 206248 207447 209074 211522 212619 213431 213900 215414 216399)

num_of_periods=${#periods[@]}
echo "Number of known periods: ${num_of_periods}"

declare -A dts_per_period_lo
declare -A dts_per_period_hi

dts_per_period_lo[A]=200804 
dts_per_period_hi[A]=202660 

dts_per_period_lo[B]=202660
dts_per_period_hi[B]=206248

dts_per_period_lo[C]=206248
dts_per_period_hi[C]=207447

dts_per_period_lo[D]=207447
dts_per_period_hi[D]=209074

dts_per_period_lo[E]=209074
dts_per_period_hi[E]=211522

dts_per_period_lo[G]=211522
dts_per_period_hi[G]=212619

dts_per_period_lo[H]=212619
dts_per_period_hi[H]=213431

dts_per_period_lo[I]=213431
dts_per_period_hi[I]=213900

dts_per_period_lo[JK]=213900
dts_per_period_hi[JK]=215414

dts_per_period_lo[L]=215414
dts_per_period_hi[L]=216399


function get_period()
{
  local id=$1

  for j in $(seq 0 ${num_of_periods})
  do
    if [ ${id} -ge ${edges[$j]} ] && [ ${id} -lt ${edges[(($j+1))]} ]
    then
        p=${periods[j]}
        echo "$p"
    fi
  done
}


function save_filelists()
{
  trigger_stream=$1
  channel=$2

  collection=$( ls ${BASEDIR} | grep ${trigger_stream} | grep ${channel}.root )

  for dts in ${collection}
  do
   did=$(echo $dts | cut -d'.' -f3)

   found_period=$(get_period ${did})
   echo "${ch}: ${did} --> Period ${found_period}"

   makeFileList.sh ${BASEDIR}/${dts} >> ${FILELISTDIR}/data.period${found_period}.${channel}.txt
  done
}

save_filelists Egamma el
save_filelists Muons mu
