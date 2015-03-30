./submit_data.sh 
./submit_fakes.sh
./submit_mc_signal_as_bkg.sh 110404
./submit_mc_signal 110340

for sample in SingleTop Diboson Zjets Wjets
do
  ./submit_mc_resolved.sh ${sample}
done
