#!/bin/sh
for i in `qs.sh | cut -d . -f 1` ; do qdel $i ; done

