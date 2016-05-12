#!/bin/bash
./scripts_ttdiffxs_13TeV_ljets_prague/RunZprime_prague.py  | grep runM > _submit_zprime.sh
split -l 1 _submit_zprime.sh _submit_zprime_a 
