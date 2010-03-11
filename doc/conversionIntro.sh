#!/bin/sh

source="sollya.tex"
target="sollya.php"

########################## Headers of the HTML file ##########################
printf "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\" \"http://www.w3.org/TR/html4/strict.dtd\">\n" > $target
printf "<html>\n" >> $target
printf "<head>\n" >> $target
printf "<title>Sollya User's Manual</title>\n" >> $target
printf "<meta name=\"author\" content=\"Sylvain Chevillard, Christoph Lauter\">\n" >> $target
printf "<meta name=\"copyright\" content=\"2009 Laboratoire de l'Informatique du Parallélisme - UMR CNRS - ENS Lyon - UCB Lyon 1 - INRIA 5668\">\n" >> $target
printf "<meta name=\"keywords\" content=\"help, sollya, User's Manual\">\n" >> $target
printf "<meta name=\"description\" content=\"This is part of Sollya User's Manual\">\n" >> $target
printf "<meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\">\n" >> $target
printf "<link href=\"sollyacss.css\" type=\"text/css\" rel=\"stylesheet\">\n" >> $target
printf "<style type=\"text/css\"><!--\n" >> $target
printf ".todo { color:#ff0000;}\n" >> $target
printf " --></style>\n" >> $target
printf "</head>\n" >> $target
printf "<body>\n" >> $target


########################## Copy of sollya.tex ##########################
sed -n 's/\\sollya/<span class="sollya">Sollya<\/span>/g;p' $source >> $target

printf "</body>\n" >> $target

########################## Postprocessing ##########################
sed -n -i 's/\\texttt{\([^}]*\)}/<code>\1<\/code>/g;p' $target
sed -n -i 's/\\com{\([^}]*\)}/<code class="com">\1<\/code>/g;p' $target
sed -n -i 's/\\key{\([^}]*\)}/<code class="key">\1<\/code>/g;p' $target
sed -n -i 's/\\rlwrap/<code>rlwrap<\/code>/g;p' $target
sed -n -i 's/\\section{\([^}]*\)}/<h1>\1<\/h1>/g;p' $target
sed -n -i 's/\\section\*{\([^}]*\)}/<h1>\1<\/h1>/g;p' $target
sed -n -i 's/\\subsection{\([^}]*\)}/<h2>\1<\/h2>/g;p' $target
sed -n -i 's/\\subsection\*{\([^}]*\)}/<h2>\1<\/h2>/g;p' $target
sed -n -i 's/\\url{\([^}]*\)}/<a href="\1">\1<\/a>/g;p' $target
sed -n -i 's/\\begin{itemize}/<ul>/g;p' $target
sed -n -i 's/\\end{itemize}/<\/li><\/ul>/g;p' $target
sed -n -i 's/\\item/<\/li><li>/g;p' $target  # Warning: the first one should not be closed
sed -n -i 's/\\input{\([^}]*\)}/<?php include("\1.php"); ?>/g;p' $target
sed -n -i 's/^%\(.*\)/<!-- \1 -->/g;p' $target
sed -n -i 's/\\copyright/\&copy;/g;p' $target
sed -n -i 's/~/\&nbsp;/g;p' $target
sed -n -i 's/\\emph{\([^}]*\)}/<em>\1<\/em>/g;p' $target
sed -n -i 's/\\label{\([^}]*\)}//g;p' $target

sed -n -i "s/\\\'E/É/g;p" $target
sed -n -i "s/\\\'e/é/g;p" $target

sed -n -i 's/\\ref{\([^}]*\)}/<span class="todo">REF(\1)<\/span>/g;p' $target
sed -n -i 's/\\footnote{\([^}]*\)}/<span class="todo">FOOTNOTE(\1)<\/span>/g;p' $target
sed -n -i 's/^$/<p>/g;p' $target