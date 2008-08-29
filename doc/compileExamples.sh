#!/bin/sh

sollyaBin="../sollya"
tempfile="/tmp/hlp2tex_tempfile"



main() {
  if [ $# -eq 0 ]
  then liste=`/bin/ls introExample*.sollya`
  else liste=$*
  fi

  for exampleFile in $liste
  do
    echo "Processing file "$exampleFile
    target=`basename $exampleFile .sollya`".tex"

    touch $target
    rm $target

    echo "\begin{center}\begin{minipage}{15cm}\begin{Verbatim}[frame=single]" > $target

    nLines=`cat $exampleFile | wc -l`
    i=1;
    count=0;
    total=0;
    
    while [ $i -le $nLines ]
    do
      if ! cat $exampleFile | head -n $i | tail -n 1 | grep "/\*" > /dev/null
      then
        echo -n "> " >> $target
	cat $exampleFile | head -n $i | tail -n 1 | sed -n 's/\t/    /g;p' | sed -n 's/\(..............................................................................\)/\1\n/g;p' >> $target
	echo "roundingwarnings=on!;" "`head -n $i $exampleFile`" | $sollyaBin > $tempfile
	sed -i -n 's/^//;p' $tempfile
	total=`cat $tempfile | wc -l`
	count=`expr $total - $count`
	tail -n $count $tempfile | sed -n 's/\t/    /g;p' | sed -n 's/\(................................................................................\)/\1\n/g;p' >> $target
	count=$total
      fi

    i=`expr $i + 1`
    done
    echo "\end{Verbatim}" >> $target
    echo "\end{minipage}\end{center}" >> $target
  done
}

main $*