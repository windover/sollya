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
    targetTeX=`basename $exampleFile .sollya`".tex"
    targetHTML=`basename $exampleFile .sollya`".php"

    touch $targetTeX
    rm $targetTeX
    touch $targetHTML
    rm $targetHTML

    echo "\begin{center}\begin{minipage}{15cm}\begin{Verbatim}[frame=single]" > $targetTeX
    echo "<div class=\"divExample\">" > $targetHTML

    nLines=`cat $exampleFile | wc -l`
    i=1;
    count=0;
    total=0;
    
    while [ $i -le $nLines ]
    do
      if ! cat $exampleFile | head -n $i | tail -n 1 | grep "/\*" > /dev/null
      then
        printf "> " >> $targetTeX
	printf "&nbsp;&nbsp;&nbsp;&gt; " >> $targetHTML

	cat $exampleFile | head -n $i | tail -n 1 | sed -n 's/\t/    /g;p' | sed -n 's/\(..............................................................................\)/\1\n/g;p' >> $targetTeX
	cat $exampleFile | head -n $i | tail -n 1 | sed -n 's/$/<br>/;p' | sed -n 's/  /\&nbsp;\&nbsp;/g;p' | sed -n 's/\&nbsp; /\&nbsp;\&nbsp;/g;p'  >> $targetHTML

	echo "roundingwarnings=on!;" "`head -n $i $exampleFile`" | $sollyaBin > $tempfile
	sed -i -n 's/^//;p' $tempfile
	total=`cat $tempfile | wc -l`
	count=`expr $total - $count`

	tail -n $count $tempfile | sed -n 's/\t/    /g;p' | sed -n 's/\(................................................................................\)/\1\n/g;p' >> $targetTeX
	tail -n $count $tempfile |sed -n 's/^/   /;p' | sed -n 's/  /\&nbsp;\&nbsp;/g;p' | sed -n 's/\&nbsp; /\&nbsp;\&nbsp;/g;p' | sed -n 's/</\&lt;/g;p' | sed -n 's/>/\&gt;/g;p' | sed -n 's/$/<br>/;p' >> $targetHTML

	count=$total
      fi

    i=`expr $i + 1`
    done
    echo "\end{Verbatim}" >> $targetTeX
    echo "\end{minipage}\end{center}" >> $targetTeX

    echo "</div>" >> $targetHTML
  done
}

main $*