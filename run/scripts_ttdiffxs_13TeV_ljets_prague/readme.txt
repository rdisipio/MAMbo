
JK:
legend:
Prepare*.sh runs appropriate Run*.py which prepares configs and submission scripts.
The submission to batch system is done via Send*.sh
(which uses Qsub.sh)

Assumes the filelists were generated in lists/:
cd lists ; . MakeFileListRucio.sh ; cd ../
cd lists ; ./SplitSig_prague.sh ; cd ../

