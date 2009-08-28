#!/bin/dash

sollyaBin="../sollya"

keywords_defs="./keywords.def"
types_defs="./types.def"
sollya_name="\\\\sollya"
listOfCommands="./CommandsAndFunctions.tex"

tempfile="/tmp/hlp2tex_tempfile"
tempfile2="/tmp/hlp2tex_tempfile2"
exampleFile="/tmp/hlp2tex_exampleFile"


getCommand() {
  command=`cat $source |grep "#NAME" | head -n 1 | sed -n 's/\(#NAME \)//;p'`
  command=$command
}

preprocessKeywords() {
  nLines=`cat $keywords_defs | grep "=" | wc -l`
  sed -n -i 's/\($\)/a/;p' $tempfile

  i=1
  while [ $i -le $nLines ]
  do
    pattern2=`cat $keywords_defs | grep "=" | head -n $i | tail -n 1 | sed -n 's/\(=.*\)//;p'`
    pattern=\$"$pattern2"
    pattern2=`echo $pattern2 | tr A-Z a-z`

    replacement=`cat $keywords_defs | grep "=" | head -n $i | tail -n 1 | sed -n 's/\(.*="\)\(.*\)\("\)/\2/;p'`

    sed -n -i 's/#SEEALSO \('"$pattern"'\)\([^[:upper:][:digit:]_]\)/#SEEALSO \\textbf{'"$replacement"'} (\\ref{lab'"$pattern2"'})a/g;p' $tempfile
    sed -n -i 's/\('"$pattern"'\)\([^[:upper:][:digit:]_]\)/\\textbf{'"$replacement"'}\2/g;p' $tempfile

    i=`expr $i + 1`
  done
  sed -n -i 's/\(a$\)//;p' $tempfile
}


preprocessTypes() {
  nLines=`cat $types_defs | grep "=" | wc -l`
  sed -n -i 's/\($\)/a/;p' $tempfile

  i=1
  while [ $i -le $nLines ]
  do
    pattern=\$`cat $types_defs | grep "=" | head -n $i | tail -n 1 | sed -n 's/\(=.*\)//;p'`
    replacement=`cat $types_defs | grep "=" | head -n $i | tail -n 1 | sed -n 's/\(.*="\)\(.*\)\("\)/\2/;p'`
    sed -n -i 's/\('"$pattern"'\)\([^[:upper:][:digit:]_]\)/\\textsf{'"$replacement"'}\2/g;p' $tempfile

    i=`expr $i + 1`
  done
  sed -n -i 's/\(a$\)//;p' $tempfile
}

preprocessMeta() {
  nLines=`cat $tempfile | wc -l`
  if [ -e $tempfile2 ]
    then rm $tempfile2; touch $tempfile2
  fi

  test="true"
  i=1
  while [ $i -le $nLines ]
  do
    if head -n $i $tempfile | tail -n 1 | grep "#EXAMPLE" > /dev/null
    then test="false"
    fi
    if head -n $i $tempfile | tail -n 1 | grep "#SEEALSO" > /dev/null
    then test="false"
    fi
    if [ $test = "true" ]
      then head -n $i $tempfile | tail -n 1 | sed -n 's/<\([^<>]*\)>/\\emph{\1}/g;p' >> $tempfile2
      else head -n $i $tempfile | tail -n 1 >> $tempfile2
    fi
    i=`expr $i + 1`
  done
  mv $tempfile2 $tempfile
}

preprocessTeX() {
  nLines=`cat $tempfile | wc -l`
  if [ -e $tempfile2 ]
    then rm $tempfile2; touch $tempfile2
  fi

  test="true"
  i=1
  while [ $i -le $nLines ]
  do
    if head -n $i $tempfile | tail -n 1 | grep "#EXAMPLE" > /dev/null
    then test="false"
    fi
    if head -n $i $tempfile | tail -n 1 | grep "#SEEALSO" > /dev/null
    then test="true"
    fi
    if [ $test = "true" ]
      then head -n $i $tempfile | tail -n 1 | sed -n 's/§§\([^§]*\)§\([^§]*\)§§/\2/g;p' >> $tempfile2
      else head -n $i $tempfile | tail -n 1 >> $tempfile2
    fi
    i=`expr $i + 1`
  done
  mv $tempfile2 $tempfile
}

processName() {
 nLines=`cat $tempfile | grep "#NAME" | wc -l`
 if [ $nLines -eq 0 ]
 then echo "Error: you must specify at least one name. Exiting"; exit 1
 fi

 if [ $nLines -eq 1 ]
   then printf "\\\\noindent Name: " >> $target
   else printf "\\\\noindent Names: " >> $target
 fi
 grep "#NAME" $tempfile | sed -n 's/#NAME //;p' | sed -n 's/$/, /;p' | tr -d "\n" | sed -n 's/, $//;p' >> $target
 printf "\\\\\\\\\n" >> $target
}

processQuickDescription() {
 nLines=`cat $tempfile | grep "#QUICK_DESCRIPTION" | wc -l`
 if [ $nLines -eq 0 ]
 then return
 fi

 if quickDescr=`grep "#QUICK_DESCRIPTION" $tempfile`
 then
   echo -n "$quickDescr" | sed -n 's/#QUICK_DESCRIPTION //;p' >> $target
   printf "\\\\\\\\" >> $target
   echo "" >> $target
 fi
}

processCallingAndTypes() {
 if [ `grep "#CALLING" $tempfile | wc -l` != `grep "#TYPE" $tempfile |wc -l` ]
 then
   echo "ASSERT failed : there shall be the same number of #CALLING and #TYPE instructions. Exits."
   exit 1
 fi

 nLines=`grep "#CALLING" $tempfile | wc -l`
 if [ $nLines -eq 0 ]
 then return
 fi

 i=1;
 printf "\\\\noindent Usage: \n" >> $target
 printf "\\\\begin{center}\n" >> $target
 while [ $i -le $nLines ]
   do
   ( grep "#CALLING" $tempfile | head -n $i | tail -n 1 | sed -n 's/#CALLING //;p' | tr -d '\n'; \
       printf " : " ; \
       grep "#TYPE" $tempfile | head -n $i | tail -n 1 | sed -n 's/#TYPE //;p' | sed -n 's/->/$\\rightarrow$/g;p' )>> $target
#   type=`echo $type | sed -n 's/|/$|$/g;p'`
   i=`expr $i + 1`
 done
 
 printf "\\\\end{center}\n" >> $target
}

processParameters() {
 nLines=`grep "#PARAMETERS" $tempfile | wc -l`
 if [ $nLines -eq 0 ]
 then return
 fi

 i=1;
 echo "Parameters: " >> $target
 printf "\\\\begin{itemize}\n" >> $target
 while [ $i -le $nLines ]
   do
   (printf "\\\\item "; grep "#PARAMETERS" $tempfile | head -n $i | tail -n 1 | sed -n 's/#PARAMETERS //;p' ) >> $target
   i=`expr $i + 1`
 done
 
 printf "\\\\end{itemize}\n" >> $target
}

processDescriptions() {
 nLines=`grep "#DESCRIPTION" $tempfile | wc -l`
 if [ $nLines -eq 0 ]
 then return
 fi

 nLines=`cat $tempfile | wc -l`
 i=1;
 mode="off"
 firstLine="off"
 printf "\\\\noindent Description: " >> $target
 printf "\\\\begin{itemize}\n" >> $target
 while [ $i -le $nLines ]
 do
   # little trick to escape the backslashes
   line=`cat $tempfile | head -n $i | tail -n 1 | sed -n 's/\\\\/\\\\\\\\/g;p'`
   if printf "$line" | grep "#DESCRIPTION" > /dev/null
   then
     firstLine="on"
     mode="on"
     echo "" >> $target
     printf "\\\\item " >> $target
   else
     if [ $mode = "on" -a -n "$line" ]
     then
       if printf "$line" | grep -e "^#" > /dev/null
       then  i=`expr $nLines + 1`
       else
         if [ $firstLine = "on" ]
           then firstLine="off"
           else echo -n "   " >> $target
         fi
         printf "$line""\n" >> $target 
       fi
     fi
   fi
   i=`expr $i + 1`
 done
 
 printf "\\\\end{itemize}\n" >> $target
}

processExampleFile() {
 nLineslocal=`cat $exampleFile | wc -l`
 ilocal=1;
 countlocal=0;
 total=0;
 while [ $ilocal -le $nLineslocal ]
 do
   echo -n "> " >> $target
   cat $exampleFile | head -n $ilocal | tail -n 1 | sed -n 's/\t/    /g;p' | sed -n 's/\(..............................................................................\)/\1\n/g;p' >> $target
   echo "verbosity=0!; roundingwarnings=on!;" "`head -n $ilocal $exampleFile`" | $sollyaBin > $tempfile2
   sed -i -n 's/^//;p' $tempfile2
   total=`cat $tempfile2 | wc -l`
   countlocal=`expr $total - $countlocal`
   tail -n $countlocal $tempfile2 | sed -n 's/\t/    /g;p' | sed -n 's/\(................................................................................\)/\1\n/g;p' >> $target
   countlocal=$total
   ilocal=`expr $ilocal + 1`
 done
 printf "\\\\end{Verbatim}\n" >> $target
 printf "\\\\end{minipage}\\\\end{center}\n" >> $target
}

processExamples() {
 nLines=`cat $tempfile | wc -l`
 i=1;
 count=1;
 mode="off"

 while [ $i -le $nLines ]
 do
   line=`cat $tempfile | head -n $i | tail -n 1`
   if echo "$line" | grep "#EXAMPLE" > /dev/null
   then
     if [ $mode = "on" ]
       then processExampleFile
       else mode="on"
     fi
     if [ -e $exampleFile ]
       then rm $exampleFile; touch $exampleFile
     fi
     printf "\\\\noindent Example "$count": \n" >> $target
     printf "\\\\begin{center}\\\\begin{minipage}{15cm}\\\\begin{Verbatim}[frame=single]\n" >> $target
     count=`expr $count + 1`
   else
     if [ $mode = "on" -a -n "$line" ]
     then
       if echo "$line" | grep -e "^#" > /dev/null
       then  i=`expr $nLines + 1`
       else
         echo "$line" >> $exampleFile 
       fi
     fi
   fi
   i=`expr $i + 1`
 done
 
 if [ $mode = "on" ]
 then processExampleFile
 fi
}

processSeeAlso() {
 nLines=`cat $tempfile | grep "#SEEALSO" | wc -l`
 if [ $nLines -eq 0 ]
 then return
 fi

 echo -n "See also: " >> $target
# grep "#SEEALSO" $tempfile | sed -n 's/#SEEALSO \\textbf{\(.*\)}/\\textbf{\1} (\\ref{lab\1})/;p' | sed -n 's/$/, /;p' | tr -d "\n" | sed -n 's/, $//;p' >> $target
 grep "#SEEALSO" $tempfile | sed -n 's/#SEEALSO //;p' | sed -n 's/$/, /;p' | tr -d "\n" | sed -n 's/, $//;p' >> $target
 echo "" >> $target
}

processFile() {
  if [ -e $target ]
  then rm $target; touch $target
  fi

  getCommand
  sed -n 's/\(\$COMMAND\)/'$command'/g;p' $source > $tempfile
  echo "" >> $tempfile
  preprocessKeywords
  preprocessTypes
  preprocessMeta
  preprocessTeX
  sed -n -i 's/$SOLLYA/'"$sollya_name"'/g;p' $tempfile


  printf "\\\\subsection{"$sectionName"}\n" >> $target
  printf "\\\\label{lab"$sectionName"}\n" | sed -n 's/ //g;p' >> $target
  processName
  processQuickDescription
  processCallingAndTypes
  processParameters
  processDescriptions
  processExamples
  processSeeAlso

  if [ -e $tempfile ]
    then rm $tempfile
  fi
  if [ -e $tempfile2 ]
    then rm $tempfile2
  fi
  if [ -e $exampleFile ]
    then rm $exampleFile
  fi
}

main() {
  if [ $# -eq 0 ]
  then liste=`/bin/ls *.shlp`
  else liste=$*
  fi

  for file in $liste
  do
    if [ -e $file ]
    then
      source=$file
      sectionName=`echo $source | sed -n 's/\.shlp//;p'`
      target=`echo $source | sed -n 's/\.shlp/\.tex/;p'`
      echo "Processing file "$source
      processFile
      if grep `printf "\\\\input{$source}\n" | sed -n 's/\.shlp//;p'` $listOfCommands > /dev/null
      then echo "Nothing to change in "$listOfCommands
      else
        printf "\\\\input{"`echo $source | sed -n 's/\.shlp//;p'`"}\n" >> $listOfCommands
      fi
    else
      echo "File "$file" does not exist!"
    fi
  done

  sort $listOfCommands > $tempfile
  mv $tempfile $listOfCommands
}

main $*
