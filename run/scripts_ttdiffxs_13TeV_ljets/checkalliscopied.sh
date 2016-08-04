#!/bin/bash

pattern=$1
datasets=$(rucio list-dids $pattern | grep "CONTAINER")

for d in ${datasets[@]}                                                                                                         
                                                                                                                                
do                                                                                                                              
       if [[ $d != "user."* ]]; then
          continue
        fi

        rucio list-file-replicas  $d --list-collections --all-states|grep BOLOGNA        
        
done