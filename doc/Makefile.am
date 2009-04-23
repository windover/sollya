EXTRA_DIST = sollya.pdf

all: 
	echo Doing all in doc

sollya.pdf: *.tex
	-pdflatex sollya
	-pdflatex sollya
	-bibtex sollya
	-bibtex sollya
	-pdflatex sollya
	pdflatex sollya


