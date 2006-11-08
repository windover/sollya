#/bin/bash

echo "#include \"expansion.h\"" > impl.c
echo " " >> impl.c
cat implementation.c >> impl.c

gcc -D$1 -fPIC -c impl.c 
gcc -D$1 -fPIC -c expansion.c 
gcc -shared -o implementation impl.o expansion.o -lgmp -lmpfr 
rm impl.c
rm impl.o
rm expansion.o
