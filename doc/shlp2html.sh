#!/bin/sh

sollyaBin="../sollya"

keywords_defs="./keywords.def"
types_defs="./types.def"
sollya_name="Sollya"
helpFile="../help.h"
listOfCommandsTmp="./ListOfCommandsTmp"
listOfCommandsPHP="./ListOfCommands.php"

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
#    sed -n -i 's/\('"$pattern"'\)\([^[:upper:][:digit:]_]\)/<a class="command" href="help.php?name='$nameOfCommand'#'$nameOfCommand'">'"$replacement"'<\/a>\2/g;p' $tempfile
    sed -n -i 's/\('"$pattern"'\)\([^[:upper:][:digit:]_]\)/<?php linkTo("command","'$nameOfCommand'","'"$replacement"'");?>\2/g;p' $tempfile
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
  testOpenedLi="false"
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
	                                 | sed -n 's/§§ § §§/<br><br>/g;p' \
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
 then printf "Error: you must specify at least one name. Exiting\n"; exit 1
 fi

 if [ $nLines -eq 1 ]
   then printf "<h2 class=\"name\">Name:</h2> " >> $target
   else printf "<h2 class=\"name\">Names:</h2> " >> $target
 fi
 grep "#NAME" $tempfile | sed -n 's/#NAME //;p' | sed -n 's/$/, /;p' | tr -d "\n" | sed -n 's/, $//;p' >> $target
 printf "\n" >> $target
}

processQuickDescription() {
 nLines=`cat $tempfile | grep "#QUICK_DESCRIPTION" | wc -l`
 if [ $nLines -eq 0 ]
 then return
 fi

 ( printf "<span class=\"smallDescription\">"; \
   grep "#QUICK_DESCRIPTION" $tempfile | \
   sed -n 's/#QUICK_DESCRIPTION //;p'; \
   printf "</span>\n" ) >> $target
}

processCallingAndTypes() {
 if [ `grep "#CALLING" $tempfile | wc -l` != `grep "#TYPE" $tempfile |wc -l` ]
 then
   printf "ASSERT failed : there shall be the same number of #CALLING and #TYPE instructions. Exits.\n"
   exit 1
 fi

 nLines=`grep "#CALLING" $tempfile | wc -l`
 if [ $nLines -eq 0 ]
 then return
 fi

 i=1;
 printf "<div class=\"divUsage\">\n" >> $target
 printf "<h2 class=\"category\">Usage: </h2>\n" >> $target
 while [ $i -le $nLines ]
   do
   ( printf "<span class=\"commandline\">"; \
     grep "#CALLING" $tempfile | head -n $i | tail -n 1 | sed -n 's/#CALLING //;p' |tr -d '\n'; \
     printf " : "; \
     grep "#TYPE" $tempfile | head -n $i | tail -n 1 | sed -n 's/#TYPE //;p' | tr -d '\n';\
     printf "</span>\n" ) >> $target
   i=`expr $i + 1`
 done
 
 printf "\n</div>\n" >> $target
}

processParameters() {
 nLines=`grep "#PARAMETERS" $tempfile | wc -l`
 if [ $nLines -eq 0 ]
 then return
 fi

 i=1;
 printf "<div class=\"divParameters\">\n" >> $target
 printf "<h2 class=\"category\">Parameters: </h2>\n" >> $target
 printf "<ul>\n" >> $target

 while [ $i -le $nLines ]
   do
   ( printf "<li>"; 
     grep "#PARAMETERS" $tempfile | head -n $i | tail -n 1 | sed -n 's/#PARAMETERS //;p' | tr -d '\n';
     printf "</li>\n") >> $target
   i=`expr $i + 1`
 done
 
 printf "</ul>\n</div>\n" >> $target
}

processDescriptions() {
 nLines=`grep "#DESCRIPTION" $tempfile | wc -l`
 if [ $nLines -eq 0 ]
 then return
 fi

 nLines=`cat $tempfile | wc -l`
 i=1;
 mode="off"
 mustCloseLI="off"
 printf "<div class=\"divDescription\">\n" >> $target
 printf "<h2 class=\"category\">Description: </h2>" >> $target
 printf "<ul>\n" >> $target
 while [ $i -le $nLines ]
 do
   line=`cat $tempfile | head -n $i | tail -n 1`
   if printf "%s" "$line" | grep "#DESCRIPTION" > /dev/null
   then
     mode="on"
     if [ $mustCloseLI = "on" ]
     then printf "</li><li>" >> $target
     else printf "<li>" >> $target
          mustCloseLI="on"
     fi
   else
     if [ $mode = "on" -a -n "$line" ]
     then
       if printf "%s" "$line" | grep -e "^#" > /dev/null
       then  i=`expr $nLines + 1`
       else
         printf "%b" "$line\n"  >> $target 
       fi
     fi
   fi
   i=`expr $i + 1`
 done
 
 printf "</ul>\n" >> $target
 printf "</div>\n" >> $target

}

# This function supposes that $exampleFile is filled with the source code of an example
# It process $exampleFile line by line. For each line, it outputs:
#    > currentLine <br>
# Then, it produces a script containing all the lines of the example until
# the current one (included) and runs Sollya on it, producing $tempfile2.
# Finally, it keeps only the trailing lines of this output (that correspond to the output
# of the current line) and formats them.
# Once the example is completely processed, it closes the <div> (that has been opened by
# function processExamples.
processExampleFile() {
 nLineslocal=`cat $exampleFile | wc -l`
 ilocal=1;
 countlocal=0;
 total=0;
 while [ $ilocal -le $nLineslocal ]
 do
   printf "&nbsp;&nbsp;&nbsp;&gt; " >> $target
   cat $exampleFile | head -n $ilocal | tail -n 1 | sed -n 's/$/<br>/;p' | sed -n 's/  /\&nbsp;\&nbsp;/g;p' | sed -n 's/\&nbsp; /\&nbsp;\&nbsp;/g;p'  >> $target
   printf "verbosity=0!; roundingwarnings=on!;""`head -n $ilocal $exampleFile`\n" | $sollyaBin > $tempfile2
   sed -i -n 's/^/   /;p' $tempfile2
   total=`cat $tempfile2 | wc -l`
   countlocal=`expr $total - $countlocal`
   tail -n $countlocal $tempfile2 | sed -n 's/  /\&nbsp;\&nbsp;/g;p' | sed -n 's/\&nbsp; /\&nbsp;\&nbsp;/g;p' | sed -n 's/</\&lt;/g;p' | sed -n 's/>/\&gt;/g;p' | sed -n 's/$/<br>/;p' >> $target
   countlocal=$total
   ilocal=`expr $ilocal + 1`
 done
 printf "</div>\n" >> $target
}

# This function process the .shlp file looking for #EXAMPLE directives
# When it finds one, it outputs:
#   <div class="divExample">
#   <h2 class="category">Example n: </h2>
#
# and fills $exampleFile with the source code of the #EXAMPLE.
# Once an example is finished, function processExampleFile is launched.
# etc. until the last example.
processExamples() {
 nLines=`cat $tempfile | wc -l`
 i=1;
 count=1;
 mode="off"

 while [ $i -le $nLines ]
 do
   line=`cat $tempfile | head -n $i | tail -n 1`
   if printf "%s" "$line" | grep "#EXAMPLE" > /dev/null
   then
     if [ $mode = "on" ]
       then processExampleFile
       else mode="on"
     fi
     if [ -e $exampleFile ]
       then rm $exampleFile; touch $exampleFile
     fi
     printf "<div class=\"divExample\">\n" >> $target
     printf "<h2 class=\"category\">Example "$count": </h2>\n" >> $target
     count=`expr $count + 1`
   else
     if [ $mode = "on" -a -n "$line" ]
     then
       if printf "%s" "$line" | grep -e "^#" > /dev/null
       then  i=`expr $nLines + 1`
       else
         cat $tempfile | head -n $i | tail -n 1 >> $exampleFile 
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

 printf "<div class=\"divSeeAlso\">\n" >> $target
 printf "<span class=\"category\">See also: </span>" >> $target
 grep "#SEEALSO" $tempfile | sed -n 's/#SEEALSO //;p' | sed -n 's/$/, /;p' | tr -d "\n" | sed -n 's/, $//;p' >> $target
 printf "\n</div>\n" >> $target
}


removeLI() {  # removes the unwanted first <LI></li> of each itemize
  statut="closed"
  nLines=`cat $tempfile| wc -l` 
  i=1
  while [ $i -le $nLines ]
  do
    ligne=`head -n $i $tempfile |  tail -n 1 | sed -n 's/\\\\/\\\\\\\\/g;p'`;
    if [ $statut = "opened" ]
    then
	printf "%b" "$ligne" |grep "<\/li>" > /dev/null; if [ $? = "0" ]
	then
	    statut="closed"
	    ligne=`printf "%b" "$ligne" | sed -n 's/\([^<]*\)<\/li>\(.*\)/\1\2/;p' | sed -n 's/\\\\/\\\\\\\\/g;p'`
	fi
    fi
    printf "%b" "$ligne" | grep "<LI>" > /dev/null; if [ $? = "0" ]	
    then
	printf "%b" "$ligne" |grep -e "<LI>.*</li>" > /dev/null; if [ $? = "0" ]
	then 
	    printf "%b" "$ligne\n" | sed -n 's/\(.*\)<LI>[^<]*<\/li>\(.*\)/\1\2/g;p'
	else 
	    statut="opened"
	    printf "%b" "$ligne\n" | sed -n 's/\(.\)<LI>.*/\1/;p'
	fi
    else
	printf "%b" "$ligne\n" 
    fi
    i=`expr $i + 1`
  done > $tempfile2
  mv $tempfile2 $tempfile
}


processFile() {
  if [ -e $target ]
  then rm $target; touch $target
  fi
  
  printf "<div class=\"helpBlock\">\n" > $target

  cat $source > $tempfile
  getCommand   # defines the variable $command which is for instance "$GT"
  sed -n -i 's/\(\$COMMAND\)/'$command'/g;p' $tempfile
  preprocessMeta  
  preprocessKeywords   # transforms the name of keywords (e.g. $GT) by their value (e.g. >)
  preprocessTypes
  preprocessTeX
  removeLI
  command=`printf $command | sed -n 's/\$\(.*\)/\1/;p'`  # removes the initial "$" of $command (e.g. GT)
  nameOfCommand=`cat $keywords_defs | grep "^$command=" | sed -n 's/\(=.*\)//;p' | tr 'A-Z' 'a-z'` # name of the command (e.g. gt) used to name the files
  realNameOfCommand=`cat $keywords_defs | grep "^$command=" | sed -n 's/\(.*="\)\(.*\)\("\)/\2/;p' | sed -n 's/§§\([^§]*\)§\([^§]*\)§§/\1/g;p' |sed -n 's/\\\\//g;p'`  # name of the command really used in Sollya (e.g. >)

  sed -n -i 's/$SOLLYA/'"$sollya_name"'/g;p' $tempfile

  
  printf "<a name=\""$nameOfCommand"\"></a>\n" > $target
  printf "<div class=\"divName\">\n" >> $target
  processName
  processQuickDescription
  printf "</div>\n" >> $target

  processCallingAndTypes
  processParameters
  processDescriptions

  printf "<div class=\"divExamples\">\n" >> $target
  processExamples
  printf "</div>\n" >> $target

  processSeeAlso

  sed -n -i 's/$/ /;p' $target

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

  if [ -e $listOfCommandsPHP ]
  then cat $listOfCommandsPHP | head -n -2 | tail -n +3 | sed -n 's/,$//;p' > $listOfCommandsTmp
  else touch $listOfCommandsTmp
  fi

  for file in $liste
  do
    if [ -e $file ]
    then
      source=$file
      sectionName=`printf $source | sed -n 's/\.shlp//;p'`
      target=`printf $source | sed -n 's/\.shlp/\.php/;p'`
      printf "Processing file "$source"\n"
      processFile
      
      if grep  "\"$nameOfCommand\"" $listOfCommandsTmp > /dev/null
      then
	  printf "Nothing to change in "$listOfCommandsPHP"\n"
      else
 	  printf "\""$nameOfCommand"\",\"$realNameOfCommand\",\n" >> $listOfCommandsTmp
      fi
    else
	printf "File "$file" does not exist!\n"
    fi
  done

  printf "<?php\n" > $listOfCommandsPHP
  printf "\$listOfCommands=array(\n" >> $listOfCommandsPHP

  sort $listOfCommandsTmp >> $listOfCommandsPHP
  (head -n -1 $listOfCommandsPHP; tail -n 1 $listOfCommandsPHP | sed -n 's/,$//;p') > $listOfCommandsTmp
  mv $listOfCommandsTmp $listOfCommandsPHP
  printf ");\n" >> $listOfCommandsPHP
  printf "?>\n" >> $listOfCommandsPHP
}

main $*
