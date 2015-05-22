#!/bin/sh
for i in `qs.sh | cut -d " " -f 1` ; do echo $i ; bkill $i ; done

