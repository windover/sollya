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
    printf "Processing file "$exampleFile"\n"
    targetTeX=`basename $exampleFile .sollya`".tex"
    targetHTML=`basename $exampleFile .sollya`".php"

    touch $targetTeX
    rm $targetTeX
    touch $targetHTML
    rm $targetHTML

    printf "\\\\begin{center}\\\\begin{minipage}{15cm}\\\\begin{Verbatim}[frame=single]\n" > $targetTeX
    printf "<div class=\"divExample\">\n" > $targetHTML

    nLines=`cat $exampleFile | wc -l`
    i=1;
    count=0;
    total=0;
    printPrompt=1;
    while [ $i -le $nLines ]
    do
      if ! cat $exampleFile | head -n $i | tail -n 1 | grep "/\*" > /dev/null
      then
        if [ $printPrompt -eq 1 ]
          then printf "> " >> $targetTeX
               printf "&nbsp;&nbsp;&nbsp;&gt; " >> $targetHTML
          else printf "  " >> $targetTeX
               printf "&nbsp;&nbsp;&nbsp;&nbsp; " >> $targetHTML
        fi

	cat $exampleFile | head -n $i | tail -n 1 | sed -n 's/\t/    /g;p' | sed -n 's/\(..............................................................................\)/\1\n/g;p' >> $targetTeX
	cat $exampleFile | head -n $i | tail -n 1 | sed -n 's/$/<br>/;p' | sed -n 's/  /\&nbsp;\&nbsp;/g;p' | sed -n 's/\&nbsp; /\&nbsp;\&nbsp;/g;p'  >> $targetHTML

	printf "%b" "roundingwarnings=on!;""`head -n $i $exampleFile`\n" | $sollyaBin > $tempfile
        if [ $? -eq 4 ]
          then printPrompt=0
          else printPrompt=1
        fi
	sed -i -n 's/^//;p' $tempfile
	total=`cat $tempfile | wc -l`
	count=`expr $total - $count`

	tail -n $count $tempfile | sed -n 's/\t/    /g;p' | sed -n 's/\(................................................................................\)/\1\n/g;p' >> $targetTeX
	tail -n $count $tempfile |sed -n 's/^/   /;p' | sed -n 's/  /\&nbsp;\&nbsp;/g;p' | sed -n 's/\&nbsp; /\&nbsp;\&nbsp;/g;p' | sed -n 's/</\&lt;/g;p' | sed -n 's/>/\&gt;/g;p' | sed -n 's/$/<br>/;p' >> $targetHTML

	count=$total
      fi

    i=`expr $i + 1`
    done
    printf "\\\\end{Verbatim}\n" >> $targetTeX
    printf "\\\\end{minipage}\\\\end{center}\n" >> $targetTeX

    printf "</div>\n" >> $targetHTML
  done
}

main $*
