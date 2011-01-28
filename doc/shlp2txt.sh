#!/bin/sh

export LC_ALL=C

sollyaBin="../sollya"

keywords_defs="./keywords.def"
types_defs="./types.def"
sollya_name="Sollya"
helpFile="../help.h"

tempfile="/tmp/hlp2txt_tempfile"
tempfile2="/tmp/hlp2txt_tempfile2"
exampleFile="/tmp/hlp2txt_exampleFile"


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
      then head -n $i $tempfile | tail -n 1 | sed -n 's/<\([^<>]*\)>/{\1}/g;p' >> $tempfile2
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
 then printf "Error: you must specify at least one name. Exiting\n"; exit 1
 fi

 if [ $nLines -eq 1 ]
   then printf "Name: " >> $target
   else printf "Names: " >> $target
 fi
 grep "#NAME" $tempfile | sed -n 's/#NAME //;p' | sed -n 's/$/, /;p' | tr -d "\n" | sed -n 's/, $//;p' >> $target
 printf "\n" >> $target
}

processQuickDescription() {
 nLines=`cat $tempfile | grep "#QUICK_DESCRIPTION" | wc -l`
 if [ $nLines -eq 0 ]
 then return
 fi

 ( printf "==> "; \
   grep "#QUICK_DESCRIPTION" $tempfile | \
   sed -n 's/#QUICK_DESCRIPTION //;p';
   printf "\n" ) >> $target
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
 printf "Usage: \n" >> $target
 while [ $i -le $nLines ]
   do
   ( printf "   "; \
     grep "#CALLING" $tempfile | head -n $i | tail -n 1 | sed -n 's/#CALLING //;p' | tr -d '\n'; \
     printf " : "; \
     grep "#TYPE" $tempfile | head -n $i | tail -n 1 | sed -n 's/#TYPE //;p' | tr -d '\n' ;\
     printf "\n" ) >> $target
   i=`expr $i + 1`
 done
 
 printf "\n" >> $target
}

processParameters() {
 nLines=`grep "#PARAMETERS" $tempfile | wc -l`
 if [ $nLines -eq 0 ]
 then return
 fi

 i=1;
 printf "Parameters: \n" >> $target
 while [ $i -le $nLines ]
   do
   ( printf "   "; grep "#PARAMETERS" $tempfile | head -n $i | tail -n 1 | sed -n 's/#PARAMETERS //;p' | tr -d '\n'; printf "\n") >> $target
   i=`expr $i + 1`
 done
 
 printf "\n" >> $target
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
 printf "Description: " >> $target
 while [ $i -le $nLines ]
 do
   line=`cat $tempfile | head -n $i | tail -n 1`
   if printf "%b" "$line" | grep "#DESCRIPTION" > /dev/null
   then
     firstLine="on"
     mode="on"
     printf "\n" >> $target
     printf "   * " >> $target
   else
     if [ $mode = "on" -a -n "$line" ]
     then
       if printf "%b" "$line"| grep -e "^#" > /dev/null
       then  i=`expr $nLines + 1`
       else
         if [ $firstLine = "on" ]
           then firstLine="off"
           else printf "   " >> $target
         fi
         printf "%b" "$line\n" >> $target 
       fi
     fi
   fi
   i=`expr $i + 1`
 done
 
 printf "\n" >> $target
}

processExampleFile() {
 nLineslocal=`cat $exampleFile | wc -l`
 ilocal=1;
 countlocal=0;
 total=0;
 while [ $ilocal -le $nLineslocal ]
 do
   printf "   > " >> $target
   cat $exampleFile | head -n $ilocal | tail -n 1 >> $target
   printf "verbosity=0!; roundingwarnings=on!;""`head -n $ilocal $exampleFile`\n" | $sollyaBin > $tempfile2
   sed -i -n 's/^/   /;p' $tempfile2
   total=`cat $tempfile2 | wc -l`
   countlocal=`expr $total - $countlocal`
   tail -n $countlocal $tempfile2 >> $target
   countlocal=$total
   ilocal=`expr $ilocal + 1`
 done
 printf "\n" >> $target
}

processExamples() {
 nLines=`cat $tempfile | wc -l`
 i=1;
 count=1;
 mode="off"

 while [ $i -le $nLines ]
 do
   line=`cat $tempfile | head -n $i | tail -n 1`
   if printf "%b" "$line"| grep "#EXAMPLE" > /dev/null
   then
     if [ $mode = "on" ]
       then processExampleFile
       else mode="on"
     fi
     if [ -e $exampleFile ]
       then rm $exampleFile; touch $exampleFile
     fi
     printf "Example "$count": \n" >> $target
     count=`expr $count + 1`
   else
     if [ $mode = "on" -a -n "$line" ]
     then
       if printf "%b" "$line"| grep -e "^#" > /dev/null
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

 printf "See also: " >> $target
 grep "#SEEALSO" $tempfile | sed -n 's/#SEEALSO //;p' | sed -n 's/$/, /;p' | tr -d "\n" | sed -n 's/, $//;p' >> $target
 printf "\n" >> $target
}

processFile() {
  if [ -e $target ]
  then rm $target; touch $target
  fi

  getCommand
  sed -n 's/\(\$COMMAND\)/'$command'/g;p' $source > $tempfile
  printf "\n" >> $tempfile
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
  then liste=`/bin/ls *.shlp`
  else liste=$*
  fi

  for file in $liste
  do
    if [ -e $file ]
    then
        source=$file
	target=`printf $source | sed -n 's/\.shlp/\.txt/;p'`
	printf "Processing file "$source"\n"
	processFile
	
	if [ $verbosity -eq 1 ]
	    then cat $target
	fi
	
	sed -i -n 's/\\/\\\\/g;p' $target
	sed -i -n 's/"/\\"/g;p' $target
	sed -i -n 's/\t/\\t/g;p' $target
	sed -i -n 's/$/\\n/g;p' $target
	index=`printf $source | sed -n 's/\.shlp//;p' | tr 'a-z' 'A-Z'`
	cat $target | tr -d '\n' > $tempfile
	
	sed -i -n 's/\(^#define HELP_'"$index"'_TEXT\)\(.*\)//;p' $helpFile
	sed -i -n 's/\(#endif\)\(.*\)//;p' $helpFile
	printf "#define HELP_"$index"_TEXT \"" >> $helpFile
	cat $tempfile  >> $helpFile
	printf "\"\n" >> $helpFile
	printf "#endif /* ifdef HELP_H*/\n" >> $helpFile
	
	rm $target
    else printf "File "$file" does not exist!\n"
    fi
  done

  tr -s '\n' < $helpFile > $tempfile
  mv $tempfile $helpFile
}



if [ "$1" = "-v" ]
then verbosity=1; shift
else verbosity=0
fi
main $*
