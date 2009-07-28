#/bin/bash

beforedir=`pwd`
cd $1
echo "#include \"expansion.h\"" > impl.c
echo " " >> impl.c
cat $beforedir/$2  >> impl.c
gcc -D$3 -fPIC -I/home/clauter/sollyaDependencies/include -c impl.c 
gcc -D$3 -fPIC -I/home/clauter/sollyaDependencies/include -c expansion.c 
gcc -shared -o implementation impl.o expansion.o -lgmp -lmpfr -L/home/clauter/sollyaDependencies/lib
#rm impl.c
rm impl.o
rm expansion.o
cd $beforedir


