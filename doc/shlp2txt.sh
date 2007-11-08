#!/bin/sh

sollyaBin="../sollya"

keywords_defs="./keywords.def"
types_defs="./types.def"
sollya_name="Sollya"

tempfile="/tmp/hlp2tex_tempfile"
tempfile2="/tmp/hlp2tex_tempfile2"
exampleFile="/tmp/hlp2tex_exampleFile"


getCommand() {
  command=`cat $source |grep "#NAME" | head -n 1 | sed -n 's/\(#NAME \)//;p'`
}

preprocessKeywords() {
  nLines=`cat $keywords_defs | grep "=" | wc -l`
  sed -n -i 's/\($\)/a/;p' $tempfile

  i=1
  while [ $i -le $nLines ]
  do
    pattern=\$`cat $keywords_defs | grep "=" | head -n $i | tail -n 1 | sed -n 's/\(=.*\)//;p'`
    replacement=`cat $keywords_defs | grep "=" | head -n $i | tail -n 1 | sed -n 's/\(.*="\)\(.*\)\("\)/\2/;p'`
    sed -n -i 's/\('"$pattern"'\)\([^[:upper:][:digit:]_]\)/'"$replacement"'\2/g;p' $tempfile

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
    sed -n -i 's/\('"$pattern"'\)\([^[:upper:][:digit:]_]\)/'"$replacement"'\2/g;p' $tempfile

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
      then head -n $i $tempfile | tail -n 1 | sed -n 's/<\([^>]*\)>/{\1}/g;p' >> $tempfile2
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
    then test="false"
    fi
    if [ $test = "true" ]
      then head -n $i $tempfile | tail -n 1 | sed -n 's/§§\([^§]*\)§\([^§]*\)§§/\1/g;p' >> $tempfile2
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
   then echo -n "Name: " >> $target
   else echo -n "Names: " >> $target
 fi
 grep "#NAME" $tempfile | sed -n 's/#NAME //;p' | sed -n 's/$/, /;p' | tr -d "\n" | sed -n 's/, $//;p' >> $target
 echo "" >> $target
}

processQuickDescription() {
 nLines=`cat $tempfile | grep "#QUICK_DESCRIPTION" | wc -l`
 if [ $nLines -eq 0 ]
 then return
 fi

 if quickDescr=`grep "#QUICK_DESCRIPTION" $tempfile`
 then
   echo -n "==> " >> $target
   echo "$quickDescr" | sed -n 's/#QUICK_DESCRIPTION //;p' >> $target
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
 echo "Usage: " >> $target
 while [ $i -le $nLines ]
   do
   calling=`grep "#CALLING" $tempfile | head -n $i | tail -n 1 | sed -n 's/#CALLING //;p'`
   type=`grep "#TYPE" $tempfile | head -n $i | tail -n 1 | sed -n 's/#TYPE //;p'`

   echo "   ""$calling"" : "$type >> $target
   i=`expr $i + 1`
 done
 
 echo "" >> $target
}

processParameters() {
 nLines=`grep "#PARAMETERS" $tempfile | wc -l`
 if [ $nLines -eq 0 ]
 then return
 fi

 i=1;
 echo "Parameters: " >> $target
 while [ $i -le $nLines ]
   do
   parameter=`grep "#PARAMETERS" $tempfile | head -n $i | tail -n 1 | sed -n 's/#PARAMETERS //;p'`

   echo "   ""$parameter" >> $target
   i=`expr $i + 1`
 done
 
 echo "" >> $target
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
 echo -n "Description: " >> $target
 while [ $i -le $nLines ]
 do
   line=`cat $tempfile | head -n $i | tail -n 1`
   if echo "$line" | grep "#DESCRIPTION" > /dev/null
   then
     firstLine="on"
     mode="on"
     echo "" >> $target
     echo -n "   * " >> $target
   else
     if [ $mode = "on" -a -n "$line" ]
     then
       if echo "$line" | grep -e "^#" > /dev/null
       then  i=`expr $nLines + 1`
       else
         if [ $firstLine = "on" ]
           then firstLine="off"
           else echo -n "   " >> $target
         fi
         echo "$line" >> $target 
       fi
     fi
   fi
   i=`expr $i + 1`
 done
 
 echo "" >> $target
}

processExampleFile() {
 nLineslocal=`cat $exampleFile | wc -l`
 ilocal=1;
 countlocal=0;
 total=0;
 while [ $ilocal -le $nLineslocal ]
 do
   echo -n "   > " >> $target
   cat $exampleFile | head -n $ilocal | tail -n 1 >> $target
   echo "verbosity=0!;" "`head -n $ilocal $exampleFile`" | $sollyaBin > $tempfile2
   sed -i -n 's/^/   /;p' $tempfile2
   total=`cat $tempfile2 | wc -l`
   countlocal=`expr $total - $countlocal`
   tail -n $countlocal $tempfile2 >> $target
   countlocal=$total
   ilocal=`expr $ilocal + 1`
 done
 echo "" >> $target
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
     echo "Example "$count": " >> $target
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
  then
    for file in `/bin/ls *.shlp`
    do
      source=$file
      target=`echo $source | sed -n 's/\.shlp/\.txt/;p'`
      echo "Processing file "$source
      processFile
    done
  else
    for file in $*
    do
      source=$file
      target=`echo $source | sed -n 's/\.shlp/\.txt/;p'`
      echo "Processing file "$source
      processFile
    done
  fi
}

main $*