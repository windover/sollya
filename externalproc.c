#include <mpfi.h>
#include <mpfr.h>
#include "sollya.h"

/* Example of an external procedure linked to an identifier in sollya

   Compile with 

     gcc -fPIC -Wall -c externalproc.c 
     gcc -fPIC -shared -o externalproc externalproc.o 

   Procedure foo will be linked by

   externalproc(foo, "./externalproc", signature);

   where signature is the signature of the function as type -> type or (type, type, ...) -> type
   where type is one of

   void, constant, function, range, integer, string, boolean, list of constant, 
   list of function, list of range, list of integer, list of string, list of boolean.
   
   The C function foo is supposed to return an integer indicating success. 
   It returns its result depending on its sollya result type as follows:

   * void :        the C function has no pointer argument for the result
   * constant:     the first argument of the C function is of C type mpfr_t *, 
                   the result is returned by affecting the MPFR variable
   * function:     the first argument of the C function is of C type node **,
                   the result is returned by the node * pointed with a new node *
   * range:        the first argument of the C function is of C type mpfi_t *,
                   the result is returned by affecting the MPFI variable
   * integer:      the first argument of the C function is of C type int *,
                   the result is returned by affecting the int variable
   * string:       the first argument of the C function is of C type char **,
                   the result is returned by the char * pointed with a new char *
   * boolean:      the first argument of the C function is of C type int *,
                   the result is returned by affecting the int variable with a boolean value
   * list of type: the first argument of the C function is of C type chain **,
                   the result is returned by the chain * pointed with a new chain *
		   containing for sollya type 
		   - constant: pointers mpfr_t * to new MPFR variables
                   - function: pointers node * to new nodes
                   - range:    pointers mpfi_t * to new MPFI variables
                   - integer:  pointers int * to new int variables
		   - string:   pointers char * to new char * variables
		   - boolean:  pointers int * to new int variables representing boolean values.
	       
   The C function affects its possible pointer argument if and only if it succeeds.
   This means, if the function returns an integer indicating failure, it does not 
   leak any memory to the encompassing environment.
 
   The C function foo receives its arguments as follows: 
   If the sollya argument type is void, no argument array is given. 
   Otherwise the C function receives a C void ** argument representing an array 
   of size equal to the arity of the function where each entry (of C type void *) represents
   a value with a C type depending on the corresponding sollya type:

   * constant:     the C type the void * is to be casted to is mpfr_t *
   * function:     the C type the void * is to be casted to is node *
   * range:        the C type the void * is to be casted to is mpfi_t *
   * integer:      the C type the void * is to be casted to is int *
   * string:       the C type the void * is to be casted to is char *
   * boolean:      the C type the void * is to be casted to is int *
   * list of type: the C type the void * is to be casted to is chain *
                   where depending on sollya type, the values in the chain are
		   to be casted to 
		   - constant: mpfr_t *
                   - function: node *
                   - range:    mpfi_t *
                   - integer:  int *
		   - string:   char *
		   - boolean:  int *.

   The C function is not supposed to alter the memory pointed by its array argument void **.

   In both directions (argument and result values), empty lists are represented by chain * NULL pointers.

*/


/* Signature (integer, integer) -> integer */

int foo(int *res, void **args) {

  *res = *((int *) args[0]) + *((int *) args[1]);

  return 1;
}
