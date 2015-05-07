#!/bin/sh
# a more involved complex PBS spy script;)

tmp=qst.tmp

bjobs > $tmp

server=lxplus

if [ $# -gt 0 ] ; then
 par1=$1
 if [ $par1 = "sh" ] || [ $par1 = "show" ]; then   
   cat $tmp | grep ${server} | awk '{printf($3);printf("  ");printf($2);printf("\n");}' | sort | uniq -c | sort -n
fi
else
cat $tmp  | grep ${server} | awk '{print $3}' | sort | uniq -c | sort -n
fi

echo "Running jobs :    `cat $tmp | grep " RUN " | wc -l`"
echo "Hanging jobs :    `cat $tmp | grep ${server} | egrep -v \"RUN|DONE\" | wc -l`"
echo "DONE jobs    :   `cat $tmp | grep "DONE" | wc -l`"
#echo "Queueing jobs:   `cat $tmp | grep " Q " | wc -l`"
#echo "Terminated jobs: `cat $tmp | grep " T " | wc -l`"
#echo "Exiting jobs:    `cat $tmp | grep " E " | wc -l`"
#echo "C'ing jobs:      `cat $tmp | grep " C " | wc -l`"

echo "Total jobs:      `cat $tmp  | grep ${server} | awk '{print $3}' | sort | uniq -c | sort -n | awk 'BEGIN{sum=0};{sum=sum+$1};END{printf(sum);printf("\n")};'`"

# clean:
rm $tmp
