#!/bin/bash
./scripts_ttdiffxs_13TeV_ljets_prague/RunSig_prague.py | grep runM > _submit_410000.sh
split -l 1 _submit_410000.sh _submit_410000_a 