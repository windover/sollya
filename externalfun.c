#include <mpfi.h>
#include "arenaireplot.h"

/* Example of an external functionnality linked to a function symbol in arenaireplot

   Compile with 

     gcc -fPIC -Wall -c externalfun.c 
     gcc -fPIC -shared -o externalfun externalfun.o 

   Function foo will be linked by

   foo = library("./externalfun");

   The C function foo is supposed to affect rop with an enclosure of 
   the image of the n-th derivative of the function on interval op.
   It is supposed to be sensitive to the precision of rop.
   
   Remark that most arenaireplot functionalities rely on the fact that
   at least the second derivative can be finitely enclosed. The C function
   may return [-inf; +inf] as an enclosure for the higher derivatives.

   The C function foo can use all functionalities inside arenaireplot that
   have been exported in arenaireplot.h. Some care must be taken with regard
   to the memory management inside the C function if arenaireplot functionalities
   are used: be sure that all memory is freed before returning.

   The C function foo is supposed to return an integer. Its meaning is to be defined.

*/


int foo(mpfi_t rop, mpfi_t op, int n) {


  return 0;
}
