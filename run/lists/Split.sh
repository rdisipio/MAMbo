#!/bin/bash

for ll in el mu mc ; do
  split -l 8 list_eos_new_${ll}.txt split_list_eos_new_${ll}_
done
