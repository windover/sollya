#!/bin/sh

sollyaBin="../sollya"

keywords_defs="./keywords.def"
types_defs="./types.def"
sollya_name="Sollya"
helpFile="../help.h"
listOfCommands="./ListOfCommands.php"

tempfile="/tmp/hlp2html_tempfile"
tempfile2="/tmp/hlp2html_tempfile2"
exampleFile="/tmp/hlp2html_exampleFile"


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
    nameOfCommand=`cat $keywords_defs | grep "=" | head -n $i | tail -n 1 | sed -n 's/\(=.*\)//;p' | tr 'A-Z' 'a-z'`
    sed -n -i 's/\('"$pattern"'\)\([^[:upper:][:digit:]_]\)/<a class="command" href="help.php?name='$nameOfCommand'#'$nameOfCommand'">'"$replacement"'<\/a>\2/g;p' $tempfile

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
    sed -n -i 's/\('"$pattern"'\)\([^[:upper:][:digit:]_]\)/<span class="type">'"$replacement"'<\/span>\2/g;p' $tempfile

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
      then head -n $i $tempfile | tail -n 1 | sed -n 's/<\([^<>]*\)>/<span class="arg">\1<\/span>/g;p' >> $tempfile2
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
    then 
	head -n $i $tempfile | tail -n 1 | sed -n 's/§§\([^§]*\)§\\\\§§/<br>/g;p' \
                                         | sed -n 's/§§\([^§]*\)§\\begin{itemize}§§/<ul><LI>/g;p' \
	                                 | sed -n 's/§§\([^§]*\)§\\end{itemize}§§/<\/li><\/ul>/g;p' \
	                                 | sed -n 's/§§\([^§]*\)§\\item§§/<\/li><li>/g;p' \
	                                 | sed -n 's/§§\([^§]*\)§\([^§]*\)§§/\1/g;p' >> $tempfile2
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
   then echo -n "<h2 class=\"name\">Name:</h2> " >> $target
   else echo -n "<h2 class=\"name\">Names:</h2> " >> $target
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
   echo -n "<span class=\"smallDescription\">" >> $target
   echo "$quickDescr" | sed -n 's/#QUICK_DESCRIPTION //;p' >> $target
   echo "</span>" >> $target
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
 echo "<h2 class=\"category\">Usage</h2>" >> $target
 while [ $i -le $nLines ]
   do
   calling=`grep "#CALLING" $tempfile | head -n $i | tail -n 1 | sed -n 's/#CALLING //;p'`
   type=`grep "#TYPE" $tempfile | head -n $i | tail -n 1 | sed -n 's/#TYPE //;p'`

   echo "<span class=\"commandline\">""$calling"" : "$type"</span>" >> $target
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
 echo "<h2 class=\"category\">Parameters: </h2>" >> $target
 echo "<ul>" >> $target
 while [ $i -le $nLines ]
   do
   parameter=`grep "#PARAMETERS" $tempfile | head -n $i | tail -n 1 | sed -n 's/#PARAMETERS //;p'`

   echo "<li>""$parameter""</li>" >> $target
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
 mustCloseLI="off"
 echo -n "<h2 class=\"category\">Description: </h2>" >> $target
 echo "<ul>" >> $target
 while [ $i -le $nLines ]
 do
   line=`cat $tempfile | head -n $i | tail -n 1`
   if echo "$line" | grep "#DESCRIPTION" > /dev/null
   then
     firstLine="on"
     mode="on"
     if [ $mustCloseLI = "on" ]
     then echo -n "</li><li>" >> $target
     else echo -n "<li>" >> $target
          mustCloseLI="on"
     fi
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
 
 echo "</ul>" >> $target
}

processExampleFile() {
 nLineslocal=`cat $exampleFile | wc -l`
 ilocal=1;
 countlocal=0;
 total=0;
 while [ $ilocal -le $nLineslocal ]
 do
   echo -n "   > " >> $target
   cat $exampleFile | head -n $ilocal | tail -n 1 | sed -n 's/$/<br>/;p' >> $target
   echo "verbosity=0!; roundingwarnings=on!;" "`head -n $ilocal $exampleFile`" | $sollyaBin > $tempfile2
   sed -i -n 's/^/   /;p' $tempfile2
   total=`cat $tempfile2 | wc -l`
   countlocal=`expr $total - $countlocal`
   tail -n $countlocal $tempfile2 | sed -n 's/$/<br>/;p' >> $target
   countlocal=$total
   ilocal=`expr $ilocal + 1`
 done
 echo "</div>" >> $target
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
     echo "<div class=\"divExample\">" >> $target
     echo "<h2 class=\"category\">Example "$count": </h2>" >> $target
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

 echo -n "<span class=\"category\">See also: </span>" >> $target
 grep "#SEEALSO" $tempfile | sed -n 's/#SEEALSO //;p' | sed -n 's/$/, /;p' | tr -d "\n" | sed -n 's/, $//;p' >> $target
 echo "" >> $target
}

processFile() {
  if [ -e $target ]
  then rm $target; touch $target
  fi
  
  echo "<div class=\"helpBlock\">" > $target

  cat $source > $tempfile
  getCommand
  sed -n -i 's/\(\$COMMAND\)/'$command'/g;p' $tempfile
  preprocessMeta
  preprocessKeywords
  preprocessTypes
  preprocessTeX
  sed -n -i 's/$SOLLYA/'"$sollya_name"'/g;p' $tempfile

  echo "<a name=\""$command"\"></a>" > $target
  echo "<div class=\"divName\">" >> $target
  processName
  processQuickDescription
  echo "</div>" >> $target
  echo "<div class=\"divUsage\">" >> $target
  processCallingAndTypes
  echo "</div>" >> $target
  echo "<div class=\"divParameters\">" >> $target
  processParameters
  echo "</div>" >> $target
  echo "<div class=\"divDescription\">" >> $target
  processDescriptions
  echo "</div>" >> $target
  echo "<div class=\"divExamples\">" >> $target
  processExamples
  echo "</div>" >> $target
  echo "<div class=\"divSeeAlso\">" >> $target
  processSeeAlso
  echo "</div>" >> $target

  echo "</div>" >> $target
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
      target=`echo $source | sed -n 's/\.shlp/\.php/;p'`
      echo "Processing file "$source
      processFile
#      if grep `echo "\input{$source}" | sed -n 's/\.shlp//;p'` $listOfCommands > /dev/null
#      then echo "Nothing to change in "$listOfCommands
#      else
#        echo "\input{"`echo $source | sed -n 's/\.shlp//;p'`"}" >> $listOfCommands
#      fi
    else
      echo "File "$file" does not exist!"
    fi
  done

#  sort $listOfCommands > $tempfile
#  mv $tempfile $listOfCommands
}

main $*