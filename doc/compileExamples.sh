#!/bin/sh

sollyaBin="../sollya"
tempfile="/tmp/hlp2tex_tempfile"



exampleFile=$1
target=`basename $exampleFile .txt`".tex"

touch $target
rm $target

echo "\begin{center}\begin{minipage}{15cm}\begin{Verbatim}[frame=single]" > $target

nLines=`cat $exampleFile | wc -l`
i=1;
count=0;
total=0;

while [ $i -le $nLines ]
  do
  echo -n "> " >> $target
  cat $exampleFile | head -n $i | tail -n 1 | sed -n 's/\t/    /g;p' | sed -n 's/\(..............................................................................\)/\1\n/g;p' >> $target
   echo "roundingwarnings=on!;" "`head -n $i $exampleFile`" | $sollyaBin > $tempfile
   sed -i -n 's/^//;p' $tempfile
   total=`cat $tempfile | wc -l`
   count=`expr $total - $count`
   tail -n $count $tempfile | sed -n 's/\t/    /g;p' | sed -n 's/\(................................................................................\)/\1\n/g;p' >> $target
   count=$total
   i=`expr $i + 1`
done
echo "\end{Verbatim}" >> $target
echo "\end{minipage}\end{center}" >> $target
