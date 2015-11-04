./submit_data.sh 
./submit_fakes.sh
#./submit_mc_signal_as_bkg.sh 110404
#./submit_mc_signal_as_bkg.sh 110340
#./submit_mc_signal_as_bkg.sh 110406
#./submit_mc_signal_as_bkg.sh 110407
#./submit_mc_signal 110340

./submit_mc_signal.sh 110404 nofullhad
./submit_mc_signal.sh 110404 ljets

for sample in SingleTop Diboson Zjets Wjets
do
  ./submit_mc_resolved.sh ${sample}
done
