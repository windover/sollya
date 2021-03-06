#include <stdio.h>
#include <stdlib.h>
#include <sollya.h>


const char *get_status(sollya_fp_result_t s) {
  switch(s) {
  case SOLLYA_FP_OBJ_NO_FUNCTION:
    return "status: SOLLYA_FP_OBJ_NO_FUNCTION";
  case SOLLYA_FP_PROVEN_EXACT:
    return "status: SOLLYA_FP_PROVEN_EXACT";
  case SOLLYA_FP_CORRECTLY_ROUNDED:
    return "status: SOLLYA_FP_CORRECTLY_ROUNDED";
  case SOLLYA_FP_CORRECTLY_ROUNDED_PROVEN_INEXACT:
    return "status: SOLLYA_FP_CORRECTLY_ROUNDED_PROVEN_INEXACT";
  case SOLLYA_FP_FAITHFUL_PROVEN_INEXACT:
    return "status: SOLLYA_FP_FAITHFUL_PROVEN_INEXACT";
  case SOLLYA_FP_FAITHFUL:
    return "status: SOLLYA_FP_FAITHFUL";
  case SOLLYA_FP_BELOW_CUTOFF:
    return "status: SOLLYA_FP_BELOW_CUTOFF";
  case SOLLYA_FP_NOT_FAITHFUL_ZERO_CONTAINED_BELOW_THRESHOLD:
    return "status: SOLLYA_SOLLYA_FP_NOT_FAITHFUL_ZERO_CONTAINED_BELOW_THRESHOLD";
  case SOLLYA_FP_NOT_FAITHFUL_ZERO_CONTAINED_NOT_BELOW_THRESHOLD:
    return "status: SOLLYA_FP_NOT_FAITHFUL_ZERO_CONTAINED_NOT_BELOW_THRESHOLD";
  case SOLLYA_FP_NOT_FAITHFUL_ZERO_NOT_CONTAINED:
    return "status: SOLLYA_FP_NOT_FAITHFUL_ZERO_NOT_CONTAINED";
  case SOLLYA_FP_NOT_FAITHFUL_INFINITY_CONTAINED:
    return "status: SOLLYA_FP_NOT_FAITHFUL_INFINITY_CONTAINED";
  case SOLLYA_FP_INFINITY:
    return "status: SOLLYA_FP_INFINITY";
  case SOLLYA_FP_FAILURE:
    return "status: SOLLYA_FP_FAILURE";
  case SOLLYA_FP_CUTOFF_IS_NAN:
    return "status: SOLLYA_FP_CUTOFF_IS_NAN";
  default:
    fprintf(stderr, "Unexpected case. Exiting.\n");
    exit(1);
  }
 }

/* tester cutoff = NaN, +inf, négatif */
int main(void) {
  sollya_fp_result_t res;
  sollya_obj_t f, powers;
  mpfr_t x,y, cutoff;

  mpfr_init2(y, 30);
  mpfr_init2(x, 30);
  mpfr_init2(cutoff, 30);
  sollya_lib_init();

  powers = sollya_lib_powers();
  sollya_lib_set_display(powers);
  sollya_lib_clear_obj(powers);

  /* Evaluate a 0-ary function */
  f = SOLLYA_PI;
  mpfr_set_d(x, 3, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);;
  res = sollya_lib_evaluate_function_at_point(y, f, x, NULL);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff NULL: returns %v (%s)", f, x, y, get_status(res));
  sollya_lib_printf(" -- expecting one of 105414357 * 2^(-25) or 843314857 * 2^(-28)\n");
  sollya_lib_clear_obj(f);


  f = SOLLYA_PI;
  mpfr_set_d(x, 3, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 1., GMP_RNDN);
  res = sollya_lib_evaluate_function_at_point(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff %v: returns %v (%s)", f, x, cutoff, y, get_status(res));
  sollya_lib_printf(" -- expecting one of 105414357 * 2^(-25) or 843314857 * 2^(-28)\n");
  sollya_lib_clear_obj(f);


  f = SOLLYA_PI;
  mpfr_set_d(x, 3, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 4., GMP_RNDN);
  res = sollya_lib_evaluate_function_at_point(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff %v: returns %v (%s)", f, x, cutoff, y, get_status(res));
  sollya_lib_printf(" -- expecting one of 105414357 * 2^(-25) or 843314857 * 2^(-28)\n");
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);


 /* Evaluate a simple expression */

  f = SOLLYA_DIV(SOLLYA_EXP(SOLLYA_CONST(0)), SOLLYA_CONST(4));
  mpfr_set_d(x, 3, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);;
  res = sollya_lib_evaluate_function_at_point(y, f, x, NULL);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff NULL: returns %v (%s)", f, x, y, get_status(res));
  sollya_lib_printf(" -- expecting 1 * 2^(-2)\n\n");
  sollya_lib_clear_obj(f);

  /* Evaluate an exact expression, but it is hard to decide that it is exact */

  f = SOLLYA_ADD( SOLLYA_CONST(1),
                  SOLLYA_SUB( SOLLYA_DIV(SOLLYA_LOG10(SOLLYA_X_), SOLLYA_LOG10(SOLLYA_CONST(2))),
                              SOLLYA_DIV(SOLLYA_LOG(SOLLYA_X_), SOLLYA_LOG(SOLLYA_CONST(2)))
                              )
                  );
  mpfr_set_d(x, 3, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);;
  res = sollya_lib_evaluate_function_at_point(y, f, x, NULL);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff NULL: returns %v (%s)", f, x, y, get_status(res));
  sollya_lib_printf(" -- expecting 1\n\n");
  sollya_lib_clear_obj(f);


  /* Evaluate an expression exactly at the middle of two fp numbers
     but it is hard to decide that it is exact */

  f = SOLLYA_ADD( SOLLYA_ADD(SOLLYA_CONST(1), SOLLYA_POW(SOLLYA_CONST(2), SOLLYA_NEG(SOLLYA_CONST(mpfr_get_prec(y))))),
                  SOLLYA_SUB( SOLLYA_DIV(SOLLYA_LOG10(SOLLYA_X_), SOLLYA_LOG10(SOLLYA_CONST(2))),
                              SOLLYA_DIV(SOLLYA_LOG(SOLLYA_X_), SOLLYA_LOG(SOLLYA_CONST(2)))
                              )
                  );
  mpfr_set_d(x, 3, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);;
  res = sollya_lib_evaluate_function_at_point(y, f, x, NULL);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff NULL: returns %v (%s)", f, x, y, get_status(res));
  sollya_lib_printf(" -- expecting 1 or 536870913 * 2^(-29)\n\n");
  sollya_lib_clear_obj(f);



  /* Evaluate a constant expression */
  f = SOLLYA_DIV(SOLLYA_CONST(1), SOLLYA_CONST(10));
  mpfr_set_d(x, 3, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);;
  res = sollya_lib_evaluate_function_at_point(y, f, x, NULL);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff NULL: returns %v (%s)", f, x, y, get_status(res));
  sollya_lib_printf(" -- expecting one of 858993459 * 2^(-33) or 214748365 * 2^(-31)\n");
  sollya_lib_clear_obj(f);


  f = SOLLYA_DIV(SOLLYA_CONST(1), SOLLYA_CONST(10));
  mpfr_set_d(x, 3, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 0.01, GMP_RNDN);
  res = sollya_lib_evaluate_function_at_point(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff %v: returns %v (%s)", f, x, cutoff, y, get_status(res));
  sollya_lib_printf(" -- expecting one of 858993459 * 2^(-33) or 214748365 * 2^(-31)\n");
  sollya_lib_clear_obj(f);


  f = SOLLYA_DIV(SOLLYA_CONST(1), SOLLYA_CONST(10));
  mpfr_set_d(x, 3, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 4., GMP_RNDN);
  res = sollya_lib_evaluate_function_at_point(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff %v: returns %v (%s)", f, x, cutoff, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);


  /* Evaluate a string */
  f = sollya_lib_string("Hello");
  mpfr_set_d(x, 3, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);;
  res = sollya_lib_evaluate_function_at_point(y, f, x, NULL);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff NULL: returns %v (%s)", f, x, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);


  /* Evaluate an expression exactly equal to 0 */
  f = SOLLYA_SUB( SOLLYA_DIV(SOLLYA_LOG10(SOLLYA_X_), SOLLYA_LOG10(SOLLYA_CONST(2))),
                  SOLLYA_DIV(SOLLYA_LOG(SOLLYA_X_), SOLLYA_LOG(SOLLYA_CONST(2)))
                  );
  mpfr_set_d(x, 3, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);;
  res = sollya_lib_evaluate_function_at_point(y, f, x, NULL);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff NULL: returns %v (%s)", f, x, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);


  f = SOLLYA_SUB( SOLLYA_DIV(SOLLYA_LOG10(SOLLYA_X_), SOLLYA_LOG10(SOLLYA_CONST(2))),
                  SOLLYA_DIV(SOLLYA_LOG(SOLLYA_X_), SOLLYA_LOG(SOLLYA_CONST(2)))
                  );
  mpfr_set_d(x, 3, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 0.01, GMP_RNDN);
  res = sollya_lib_evaluate_function_at_point(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff %v: returns %v (%s)", f, x, cutoff, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);



  /* Evaluate an expression */
  f = SOLLYA_EXP( SOLLYA_COS(SOLLYA_X_));
  mpfr_set_d(x, 3, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);
  res = sollya_lib_evaluate_function_at_point(y, f, x, NULL);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff NULL: returns %v (%s)", f, x, y, get_status(res));
  sollya_lib_printf(" -- expecting one of 797960855 * 2^(-31) or 99745107 * 2^(-28)\n");
  sollya_lib_clear_obj(f);


  f = SOLLYA_EXP( SOLLYA_COS(SOLLYA_X_));
  mpfr_set_d(x, 3, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 0.01, GMP_RNDN);
  res = sollya_lib_evaluate_function_at_point(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff %v: returns %v (%s)", f, x, cutoff, y, get_status(res));
  sollya_lib_printf(" -- expecting one of 797960855 * 2^(-31) or 99745107 * 2^(-28)\n");
  sollya_lib_clear_obj(f);


  f = SOLLYA_EXP( SOLLYA_COS(SOLLYA_X_));
  mpfr_set_d(x, 3, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 4., GMP_RNDN);
  res = sollya_lib_evaluate_function_at_point(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff %v: returns %v (%s)", f, x, cutoff, y, get_status(res));
  sollya_lib_printf(" -- expecting one of 797960855 * 2^(-31) or 99745107 * 2^(-28)\n");
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);


  /* Evaluate a very small expression */
  f = SOLLYA_EXP(SOLLYA_X_);
  mpfr_set_d(x, -100, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);;
  res = sollya_lib_evaluate_function_at_point(y, f, x, NULL);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff NULL: returns %v (%s)", f, x, y, get_status(res));
  sollya_lib_printf(" -- expecting one of 890781225 * 2^(-174) or 445390613 * 2^(-173)\n");
  sollya_lib_clear_obj(f);


  f = SOLLYA_EXP(SOLLYA_X_);
  mpfr_set_d(x, -100, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 1e-50, GMP_RNDN);
  res = sollya_lib_evaluate_function_at_point(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff %v: returns %v (%s)", f, x, cutoff, y, get_status(res));
  sollya_lib_printf(" -- expecting one of 890781225 * 2^(-174) or 445390613 * 2^(-173)\n");
  sollya_lib_clear_obj(f);


  f = SOLLYA_EXP(SOLLYA_X_);
  mpfr_set_d(x, -100, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 4., GMP_RNDN);
  res = sollya_lib_evaluate_function_at_point(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff %v: returns %v (%s)", f, x, cutoff, y, get_status(res));
  sollya_lib_printf(" -- expecting one of 890781225 * 2^(-174) or 445390613 * 2^(-173)\n");
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);


  /* Evaluate an undefined expression */
  f = SOLLYA_TAN(SOLLYA_DIV(SOLLYA_PI, SOLLYA_CONST(2)));
  mpfr_set_d(x, -100, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);;
  res = sollya_lib_evaluate_function_at_point(y, f, x, NULL);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff NULL: returns %v (%s)", f, x, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);


  f = SOLLYA_TAN(SOLLYA_DIV(SOLLYA_PI, SOLLYA_CONST(2)));
  mpfr_set_d(x, -100, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 1e-50, GMP_RNDN);
  res = sollya_lib_evaluate_function_at_point(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff %v: returns %v (%s)", f, x, cutoff, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);


  f = SOLLYA_TAN(SOLLYA_DIV(SOLLYA_PI, SOLLYA_CONST(2)));
  mpfr_set_d(x, -100, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 4., GMP_RNDN);
  res = sollya_lib_evaluate_function_at_point(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff %v: returns %v (%s)", f, x, cutoff, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);


  /* Evaluate an expression at a point where its value is +Inf */
  f = SOLLYA_DIV(SOLLYA_CONST(1), SOLLYA_POW(SOLLYA_X_, SOLLYA_CONST(2)));
  mpfr_set_d(x, 0, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);;
  res = sollya_lib_evaluate_function_at_point(y, f, x, NULL);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff NULL: returns %v (%s)", f, x, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);


  f = SOLLYA_DIV(SOLLYA_CONST(1), SOLLYA_POW(SOLLYA_X_, SOLLYA_CONST(2)));
  mpfr_set_d(x, 0, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 1e-50, GMP_RNDN);
  res = sollya_lib_evaluate_function_at_point(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff %v: returns %v (%s)", f, x, cutoff, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);


  f = SOLLYA_DIV(SOLLYA_CONST(1), SOLLYA_POW(SOLLYA_X_, SOLLYA_CONST(2)));
  mpfr_set_d(x, 0, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 4., GMP_RNDN);
  res = sollya_lib_evaluate_function_at_point(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff %v: returns %v (%s)", f, x, cutoff, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);




  /* Evaluate an expression at a point where it is undefined */
  f = SOLLYA_DIV(SOLLYA_CONST(1), SOLLYA_X_);
  mpfr_set_d(x, 0, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);;
  res = sollya_lib_evaluate_function_at_point(y, f, x, NULL);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff NULL: returns %v (%s)", f, x, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);


  f = SOLLYA_DIV(SOLLYA_CONST(1), SOLLYA_X_);
  mpfr_set_d(x, 0, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 1e-50, GMP_RNDN);
  res = sollya_lib_evaluate_function_at_point(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff %v: returns %v (%s)", f, x, cutoff, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);


  f = SOLLYA_DIV(SOLLYA_CONST(1), SOLLYA_X_);
  mpfr_set_d(x, 0, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 4., GMP_RNDN);
  res = sollya_lib_evaluate_function_at_point(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff %v: returns %v (%s)", f, x, cutoff, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);


  /* Evaluate an expression at a point on the boundary of its domain */
  f = SOLLYA_LOG(SOLLYA_X_);
  mpfr_set_d(x, 0, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);;
  res = sollya_lib_evaluate_function_at_point(y, f, x, NULL);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff NULL: returns %v (%s)", f, x, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);


  f = SOLLYA_LOG(SOLLYA_X_);
  mpfr_set_d(x, 0, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 1e-50, GMP_RNDN);
  res = sollya_lib_evaluate_function_at_point(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff %v: returns %v (%s)", f, x, cutoff, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);


  f = SOLLYA_LOG(SOLLYA_X_);
  mpfr_set_d(x, 0, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 4., GMP_RNDN);
  res = sollya_lib_evaluate_function_at_point(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff %v: returns %v (%s)", f, x, cutoff, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);



  /* Evaluate an expression at a point outside of its domain */
  f = SOLLYA_LOG(SOLLYA_X_);
  mpfr_set_d(x, -1, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);;
  res = sollya_lib_evaluate_function_at_point(y, f, x, NULL);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff NULL: returns %v (%s)", f, x, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);


  f = SOLLYA_LOG(SOLLYA_X_);
  mpfr_set_d(x, -1, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 1e-50, GMP_RNDN);
  res = sollya_lib_evaluate_function_at_point(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff %v: returns %v (%s)", f, x, cutoff, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);


  f = SOLLYA_LOG(SOLLYA_X_);
  mpfr_set_d(x, -1, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);
  mpfr_set_d(cutoff, 4., GMP_RNDN);
  res = sollya_lib_evaluate_function_at_point(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff %v: returns %v (%s)", f, x, cutoff, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);



  /* Evaluate an expression at a point where it is very close to 0, but not zero */
  f = sollya_lib_parse_string("sin(pi/6)-x+1b-100000");
  mpfr_set_d(x, 0.5, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);;
  res = sollya_lib_evaluate_function_at_point(y, f, x, NULL);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff NULL: returns %v (%s)", f, x, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);


  f = sollya_lib_parse_string("sin(pi/6)-x+1b-100000");
  mpfr_set_d(x, 0.5, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 1e-50, GMP_RNDN);
  res = sollya_lib_evaluate_function_at_point(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff %v: returns %v (%s)", f, x, cutoff, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);


  f = sollya_lib_parse_string("sin(pi/6)-x+1b-100000");
  mpfr_set_d(x, 0.5, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);
  mpfr_set_d(cutoff, 4., GMP_RNDN);
  res = sollya_lib_evaluate_function_at_point(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff %v: returns %v (%s)", f, x, cutoff, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);



  /* Evaluate tricky expressions. */
  f = sollya_lib_parse_string("(sin(pi/6)-x)*1b100000+3");
  mpfr_set_d(x, 0.5, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);;
  res = sollya_lib_evaluate_function_at_point(y, f, x, NULL);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff NULL: returns %v (%s)", f, x, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);

  f = sollya_lib_parse_string("(sin(pi/6)-x)*1b100000+1b50000");
  mpfr_set_d(x, 0.5, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);;
  res = sollya_lib_evaluate_function_at_point(y, f, x, NULL);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff NULL: returns %v (%s)", f, x, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);

  f = sollya_lib_parse_string("3+7b-31*sin(1/(280b-18000 + (sin(pi/6)-x)))");
  mpfr_set_d(x, 0.5, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);
  res = sollya_lib_evaluate_function_at_point(y, f, x, NULL);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff NULL: returns %v (%s)", f, x, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);


  /* Trying negative cutoff, infinite cutoff and NaN cutoff */
  f = sollya_lib_parse_string("sin(pi/6)-x+1b-100000");
  mpfr_set_d(x, 0.5, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);
  mpfr_set_d(cutoff, -4., GMP_RNDN);
  res = sollya_lib_evaluate_function_at_point(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff %v: returns %v (%s)", f, x, cutoff, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);


  f = sollya_lib_parse_string("sin(pi/6)-x+1b-100000");
  mpfr_set_d(x, 0.5, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);
  mpfr_set_inf(cutoff, 1);
  res = sollya_lib_evaluate_function_at_point(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff %v: returns %v (%s)", f, x, cutoff, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);


  f = sollya_lib_parse_string("sin(pi/6)-x+1b-100000");
  mpfr_set_d(x, 0.5, GMP_RNDN);
  mpfr_set_d(y, -17, GMP_RNDN);
  mpfr_set_nan(cutoff);
  res = sollya_lib_evaluate_function_at_point(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %v with cutoff %v: returns %v (%s)", f, x, cutoff, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);



  mpfr_clear(x);
  mpfr_clear(y);
  mpfr_clear(cutoff);
  sollya_lib_close();
  return 0;
}
