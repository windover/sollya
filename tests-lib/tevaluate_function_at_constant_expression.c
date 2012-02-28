#include <stdio.h>
#include <stdlib.h>
#include <sollya.h>


const char *get_status(fp_eval_result_t s) {
  switch(s) {
  case FP_EVAL_OBJ_NO_FUNCTION:
    return "status: FP_EVAL_OBJ_NO_FUNCTION";
  case FP_EVAL_FAITHFUL:
    return "status: FP_EVAL_FAITHFUL";
  case FP_EVAL_BELOW_CUTOFF:
    return "status: FP_EVAL_BELOW_CUTOFF";
  case FP_EVAL_NOT_FAITHFUL_ZERO_CONTAINED_BELOW_THRESHOLD:
    return "status: FP_EVAL_NOT_FAITHFUL_ZERO_CONTAINED_BELOW_THRESHOLD";
  case FP_EVAL_NOT_FAITHFUL_ZERO_CONTAINED_NOT_BELOW_THRESHOLD:
    return "status: FP_EVAL_NOT_FAITHFUL_ZERO_CONTAINED_NOT_BELOW_THRESHOLD";
  case FP_EVAL_NOT_FAITHFUL_ZERO_NOT_CONTAINED:
    return "status: FP_EVAL_NOT_FAITHFUL_ZERO_NOT_CONTAINED";
  case FP_EVAL_NOT_FAITHFUL_INFINITY_CONTAINED:
    return "status: FP_EVAL_NOT_FAITHFUL_INFINITY_CONTAINED";
  case FP_EVAL_INFINITY:
    return "status: FP_EVAL_INFINITY";
  case FP_EVAL_FAILURE:
    return "status: FP_EVAL_FAILURE";
  case FP_EVAL_CUTOFF_IS_NAN:
    return "status: FP_EVAL_CUTOFF_IS_NAN";
  case FP_EVAL_EXPRESSION_NOT_CONSTANT:
    return "status: FP_EVAL_EXPRESSION_NOT_CONSTANT";
  default:
    fprintf(stderr, "Unexpected case. Exiting.\n");
    exit(1);
  }
 }

/* tester cutoff = NaN, +inf, négatif */
int main(void) {
  fp_eval_result_t res;
  sollya_obj_t f, x, powers;
  mpfr_t y, cutoff;

  mpfr_init2(y, 30);
  mpfr_init2(cutoff, 30);
  sollya_lib_init();

  powers = sollya_lib_powers();
  sollya_lib_set_display(powers);
  sollya_lib_clear_obj(powers);

  /* Evaluate a 0-ary function */

  f = SOLLYA_PI;
  x = SOLLYA_CONST(3);
  mpfr_set_d(y, -17, GMP_RNDN);;
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, NULL);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff NULL: returns %v (%s)", f, x, y, get_status(res));
  sollya_lib_printf(" -- expecting one of 105414357 * 2^(-25) or 843314857 * 2^(-28)\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);


  f = SOLLYA_PI;
  x = SOLLYA_CONST(3);
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 1., GMP_RNDN);
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff %.1g: returns %v (%s)", f, x, mpfr_get_d(cutoff, GMP_RNDN), y, get_status(res));
  sollya_lib_printf(" -- expecting one of 105414357 * 2^(-25) or 843314857 * 2^(-28)\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);


  f = SOLLYA_PI;
  x = SOLLYA_CONST(3);
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 4., GMP_RNDN);
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff %.1g: returns %v (%s)", f, x, mpfr_get_d(cutoff, GMP_RNDN), y, get_status(res));
  sollya_lib_printf(" -- expecting one of 105414357 * 2^(-25) or 843314857 * 2^(-28)\n");
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);


  /* Evaluate a constant expression */

  f = SOLLYA_DIV(SOLLYA_CONST(1), SOLLYA_CONST(10));
  x = SOLLYA_CONST(3);
  mpfr_set_d(y, -17, GMP_RNDN);;
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, NULL);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff NULL: returns %v (%s)", f, x, y, get_status(res));
  sollya_lib_printf(" -- expecting one of 858993459 * 2^(-33) or 214748365 * 2^(-31)\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);


  f = SOLLYA_DIV(SOLLYA_CONST(1), SOLLYA_CONST(10));
  x = SOLLYA_CONST(3);
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 0.01, GMP_RNDN);
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff %.1g: returns %v (%s)", f, x, mpfr_get_d(cutoff, GMP_RNDN), y, get_status(res));
  sollya_lib_printf(" -- expecting one of 858993459 * 2^(-33) or 214748365 * 2^(-31)\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);


  f = SOLLYA_DIV(SOLLYA_CONST(1), SOLLYA_CONST(10));
  x = SOLLYA_CONST(3);
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 4., GMP_RNDN);
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff %.1g: returns %v (%s)", f, x, mpfr_get_d(cutoff, GMP_RNDN), y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);


  /* Evaluate the identity at 1/10 */

  f = SOLLYA_X_;
  x = SOLLYA_DIV(SOLLYA_CONST(1), SOLLYA_CONST(10));
  mpfr_set_d(y, -17, GMP_RNDN);;
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, NULL);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff NULL: returns %v (%s)", f, x, y, get_status(res));
  sollya_lib_printf(" -- expecting one of 858993459 * 2^(-33) or 214748365 * 2^(-31)\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);


  f = SOLLYA_X_;
  x = SOLLYA_DIV(SOLLYA_CONST(1), SOLLYA_CONST(10));
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 0.01, GMP_RNDN);
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff %.1g: returns %v (%s)", f, x, mpfr_get_d(cutoff, GMP_RNDN), y, get_status(res));
  sollya_lib_printf(" -- expecting one of 858993459 * 2^(-33) or 214748365 * 2^(-31)\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);


  f = SOLLYA_X_;
  x = SOLLYA_DIV(SOLLYA_CONST(1), SOLLYA_CONST(10));
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 4., GMP_RNDN);
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff %.1g: returns %v (%s)", f, x, mpfr_get_d(cutoff, GMP_RNDN), y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);


  /* Evaluate a string */

  f = sollya_lib_string("Hello");
  x = SOLLYA_CONST(3);
  mpfr_set_d(y, -17, GMP_RNDN);;
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, NULL);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff NULL: returns %v (%s)", f, x, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);



  /* Evaluate an expression exactly equal to 0 */

  f = SOLLYA_SUB( SOLLYA_DIV(SOLLYA_LOG10(SOLLYA_X_), SOLLYA_LOG10(SOLLYA_CONST(2))),
                  SOLLYA_DIV(SOLLYA_LOG(SOLLYA_X_), SOLLYA_LOG(SOLLYA_CONST(2)))
                  );
  x = SOLLYA_DIV(SOLLYA_CONST(3), SOLLYA_PI);
  mpfr_set_d(y, -17, GMP_RNDN);;
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, NULL);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff NULL: returns %v (%s)", f, x, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);


  f = SOLLYA_SUB( SOLLYA_DIV(SOLLYA_LOG10(SOLLYA_X_), SOLLYA_LOG10(SOLLYA_CONST(2))),
                  SOLLYA_DIV(SOLLYA_LOG(SOLLYA_X_), SOLLYA_LOG(SOLLYA_CONST(2)))
                  );
  x = SOLLYA_DIV(SOLLYA_CONST(3), SOLLYA_PI);
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 0.01, GMP_RNDN);
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff %.1g: returns %v (%s)", f, x, mpfr_get_d(cutoff, GMP_RNDN), y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);



  /* Evaluate an expression */

  f = SOLLYA_EXP( SOLLYA_COS(SOLLYA_X_));
  x = SOLLYA_CONST(3);
  mpfr_set_d(y, -17, GMP_RNDN);
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, NULL);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff NULL: returns %v (%s)", f, x, y, get_status(res));
  sollya_lib_printf(" -- expecting one of 797960855 * 2^(-31) or 99745107 * 2^(-28)\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);


  f = SOLLYA_EXP( SOLLYA_COS(SOLLYA_X_));
  x = SOLLYA_CONST(3);
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 0.01, GMP_RNDN);
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff %.1g: returns %v (%s)", f, x, mpfr_get_d(cutoff, GMP_RNDN), y, get_status(res));
  sollya_lib_printf(" -- expecting one of 797960855 * 2^(-31) or 99745107 * 2^(-28)\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);


  f = SOLLYA_EXP( SOLLYA_COS(SOLLYA_X_));
  x = SOLLYA_CONST(3);
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 4., GMP_RNDN);
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff %.1g: returns %v (%s)", f, x, mpfr_get_d(cutoff, GMP_RNDN), y, get_status(res));
  sollya_lib_printf(" -- expecting one of 797960855 * 2^(-31) or 99745107 * 2^(-28)\n");
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);


  /* Evaluate a very small expression */

  f = SOLLYA_EXP(SOLLYA_X_);
  x = SOLLYA_CONST(-100);
  mpfr_set_d(y, -17, GMP_RNDN);;
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, NULL);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff NULL: returns %v (%s)", f, x, y, get_status(res));
  sollya_lib_printf(" -- expecting one of 890781225 * 2^(-174) or 445390613 * 2^(-173)\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);


  f = SOLLYA_EXP(SOLLYA_X_);
  x = SOLLYA_CONST(-100);
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 1e-50, GMP_RNDN);
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff %.1g: returns %v (%s)", f, x, mpfr_get_d(cutoff, GMP_RNDN), y, get_status(res));
  sollya_lib_printf(" -- expecting one of 890781225 * 2^(-174) or 445390613 * 2^(-173)\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);


  f = SOLLYA_EXP(SOLLYA_X_);
  x = SOLLYA_CONST(-100);
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 4., GMP_RNDN);
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff %.1g: returns %v (%s)", f, x, mpfr_get_d(cutoff, GMP_RNDN), y, get_status(res));
  sollya_lib_printf(" -- expecting one of 890781225 * 2^(-174) or 445390613 * 2^(-173)\n");
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);


  /* Evaluate an undefined expression */

  f = SOLLYA_TAN(SOLLYA_X_);
  x = SOLLYA_DIV(SOLLYA_PI, SOLLYA_CONST(2));
  mpfr_set_d(y, -17, GMP_RNDN);;
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, NULL);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff NULL: returns %v (%s)", f, x, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);


  f = SOLLYA_TAN(SOLLYA_X_);
  x = SOLLYA_DIV(SOLLYA_PI, SOLLYA_CONST(2));
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 1e-50, GMP_RNDN);
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff %.1g: returns %v (%s)", f, x, mpfr_get_d(cutoff, GMP_RNDN), y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);


  f = SOLLYA_TAN(SOLLYA_X_);
  x = SOLLYA_DIV(SOLLYA_PI, SOLLYA_CONST(2));
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 4., GMP_RNDN);
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff %.1g: returns %v (%s)", f, x, mpfr_get_d(cutoff, GMP_RNDN), y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);


  /* Evaluate an expression at a point where its value is +Inf */

  f = SOLLYA_DIV(SOLLYA_CONST(1), SOLLYA_POW(SOLLYA_X_, SOLLYA_CONST(2)));
  x = SOLLYA_CONST(0);
  mpfr_set_d(y, -17, GMP_RNDN);;
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, NULL);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff NULL: returns %v (%s)", f, x, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);


  f = SOLLYA_DIV(SOLLYA_CONST(1), SOLLYA_POW(SOLLYA_X_, SOLLYA_CONST(2)));
  x = SOLLYA_CONST(0);
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 1e-50, GMP_RNDN);
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff %.1g: returns %v (%s)", f, x, mpfr_get_d(cutoff, GMP_RNDN), y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);


  f = SOLLYA_DIV(SOLLYA_CONST(1), SOLLYA_POW(SOLLYA_X_, SOLLYA_CONST(2)));
  x = SOLLYA_CONST(0);
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 4., GMP_RNDN);
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff %.1g: returns %v (%s)", f, x, mpfr_get_d(cutoff, GMP_RNDN), y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);




  /* Evaluate an expression at a point where it is undefined */

  f = SOLLYA_DIV(SOLLYA_CONST(1), SOLLYA_X_);
  x = SOLLYA_CONST(0);
  mpfr_set_d(y, -17, GMP_RNDN);;
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, NULL);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff NULL: returns %v (%s)", f, x, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);


  f = SOLLYA_DIV(SOLLYA_CONST(1), SOLLYA_X_);
  x = SOLLYA_CONST(0);
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 1e-50, GMP_RNDN);
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff %.1g: returns %v (%s)", f, x, mpfr_get_d(cutoff, GMP_RNDN), y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);


  f = SOLLYA_DIV(SOLLYA_CONST(1), SOLLYA_X_);
  x = SOLLYA_CONST(0);
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 4., GMP_RNDN);
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff %.1g: returns %v (%s)", f, x, mpfr_get_d(cutoff, GMP_RNDN), y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);


  /* Evaluate an expression at a point on the boundary of its domain */

  f = SOLLYA_LOG(SOLLYA_X_);
  x = SOLLYA_CONST(0);
  mpfr_set_d(y, -17, GMP_RNDN);;
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, NULL);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff NULL: returns %v (%s)", f, x, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);


  f = SOLLYA_LOG(SOLLYA_X_);
  x = SOLLYA_CONST(0);
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 1e-50, GMP_RNDN);
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff %.1g: returns %v (%s)", f, x, mpfr_get_d(cutoff, GMP_RNDN), y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);


  f = SOLLYA_LOG(SOLLYA_X_);
  x = SOLLYA_CONST(0);
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 4., GMP_RNDN);
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff %.1g: returns %v (%s)", f, x, mpfr_get_d(cutoff, GMP_RNDN), y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);



  /* Evaluate an expression at a point outside of its domain */

  f = SOLLYA_LOG(SOLLYA_X_);
  x = SOLLYA_CONST(-1);
  mpfr_set_d(y, -17, GMP_RNDN);;
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, NULL);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff NULL: returns %v (%s)", f, x, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);


  f = SOLLYA_LOG(SOLLYA_X_);
  x = SOLLYA_CONST(-1);
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 1e-50, GMP_RNDN);
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff %.1g: returns %v (%s)", f, x, mpfr_get_d(cutoff, GMP_RNDN), y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);


  f = SOLLYA_LOG(SOLLYA_X_);
  x = SOLLYA_CONST(-1);
  mpfr_set_d(y, -17, GMP_RNDN);
  mpfr_set_d(cutoff, 4., GMP_RNDN);
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff %.1g: returns %v (%s)", f, x, mpfr_get_d(cutoff, GMP_RNDN), y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);



  /* Evaluate an expression at a point where it is very close to 0, but not zero */

  f = sollya_lib_parse_string("sin(pi/3)-x+1b-100000");
  x = SOLLYA_DIV(SOLLYA_SQRT(SOLLYA_CONST(3)), SOLLYA_CONST(2));
  mpfr_set_d(y, -17, GMP_RNDN);;
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, NULL);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff NULL: returns %v (%s)", f, x, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);


  f = sollya_lib_parse_string("sin(pi/3)-x+1b-100000");
  x = SOLLYA_DIV(SOLLYA_SQRT(SOLLYA_CONST(3)), SOLLYA_CONST(2));
  mpfr_set_d(y, -17, GMP_RNDN);;
  mpfr_set_d(cutoff, 1e-50, GMP_RNDN);
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff %.1g: returns %v (%s)", f, x, mpfr_get_d(cutoff, GMP_RNDN), y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);


  f = sollya_lib_parse_string("sin(pi/3)-x+1b-100000");
  x = SOLLYA_DIV(SOLLYA_SQRT(SOLLYA_CONST(3)), SOLLYA_CONST(2));
  mpfr_set_d(y, -17, GMP_RNDN);
  mpfr_set_d(cutoff, 4., GMP_RNDN);
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff %.1g: returns %v (%s)", f, x, mpfr_get_d(cutoff, GMP_RNDN), y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);



  /* Evaluate tricky expressions. */

  f = sollya_lib_parse_string("(sin(pi/3)-x)*1b100000+3");
  x = SOLLYA_DIV(SOLLYA_SQRT(SOLLYA_CONST(3)), SOLLYA_CONST(2));
  mpfr_set_d(y, -17, GMP_RNDN);;
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, NULL);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff NULL: returns %v (%s)", f, x, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);

  f = sollya_lib_parse_string("(sin(pi/3)-x)*1b100000+1b60000");
  x = SOLLYA_DIV(SOLLYA_SQRT(SOLLYA_CONST(3)), SOLLYA_CONST(2));
  mpfr_set_d(y, -17, GMP_RNDN);;
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, NULL);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff NULL: returns %v (%s)", f, x, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);

  f = sollya_lib_parse_string("(sin(pi/3)-x)*1b10000+3");
  x = SOLLYA_DIV(SOLLYA_SQRT(SOLLYA_CONST(3)), SOLLYA_CONST(2));
  mpfr_set_d(y, -17, GMP_RNDN);
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, NULL);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff NULL: returns %v (%s)", f, x, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);


  /* Trying negative cutoff, infinite cutoff and NaN cutoff */

  f = sollya_lib_parse_string("sin(pi/6)-x+1b-100000");
  x = SOLLYA_CONST(0.5);
  mpfr_set_d(y, -17, GMP_RNDN);
  mpfr_set_d(cutoff, -4., GMP_RNDN);
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff %.1g: returns %v (%s)", f, x, mpfr_get_d(cutoff, GMP_RNDN), y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);


  f = sollya_lib_parse_string("sin(pi/6)-x+1b-100000");
  x = SOLLYA_CONST(0.5);
  mpfr_set_d(y, -17, GMP_RNDN);
  mpfr_set_inf(cutoff, 1);
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff %.1g: returns %v (%s)", f, x, mpfr_get_d(cutoff, GMP_RNDN), y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);


  f = sollya_lib_parse_string("sin(pi/6)-x+1b-100000");
  x = SOLLYA_CONST(0.5);
  mpfr_set_d(y, -17, GMP_RNDN);
  mpfr_set_nan(cutoff);
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, &cutoff);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff %.1g: returns %v (%s)", f, x, mpfr_get_d(cutoff, GMP_RNDN), y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);



  /* Cases when the constant function argument is not a constant function */

  f = SOLLYA_X_;
  x = SOLLYA_X_;
  mpfr_set_d(y, -17, GMP_RNDN);
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, NULL);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff NULL: returns %v (%s)", f, x, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);

  f = SOLLYA_X_;
  x = sollya_lib_string("Hello");
  mpfr_set_d(y, -17, GMP_RNDN);
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, NULL);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff NULL: returns %v (%s)", f, x, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);


  f = sollya_lib_string("Hello");
  x = SOLLYA_X_;
  mpfr_set_d(y, -17, GMP_RNDN);
  res = sollya_lib_evaluate_function_at_constant_expression(y, f, x, NULL);
  sollya_lib_printf("Trying to faithfuly evaluate %b at %b with cutoff NULL: returns %v (%s)", f, x, y, get_status(res));
  sollya_lib_printf("\n");
  sollya_lib_clear_obj(f);
  sollya_lib_clear_obj(x);


  mpfr_clear(y);
  mpfr_clear(cutoff);
  sollya_lib_close();
  return 0;
}
