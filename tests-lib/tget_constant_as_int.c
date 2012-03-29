#include <sollya.h>

int main(void) {
  sollya_obj_t a, prec;
  int res;
  int i;

  sollya_lib_init();

  prec = SOLLYA_CONST(20);
  sollya_lib_set_prec_and_print(prec);
  sollya_lib_clear_obj(prec);

  /* something that is obviously not a constant */
  res = -17;
  a = sollya_lib_parse_string("[1;2]");
  if (!sollya_lib_get_constant_as_int(&res, a))
    sollya_lib_printf("%b is not a constant.\n\n", a);
  else {
    sollya_lib_printf("%b has been converted to %d\n\n", a, res);
  }
  sollya_lib_clear_obj(a);


  /* something that could be interpreted as constant but that is not a */
  /* constant, strictly speaking */
  res = -17;
  a = sollya_lib_parse_string("[1;1]");
  if (!sollya_lib_get_constant_as_int(&res, a))
    sollya_lib_printf("%b is not a constant.\n\n", a);
  else {
    sollya_lib_printf("%b has been converted to %d\n\n", a, res);
  }
  sollya_lib_clear_obj(a);


  /* something that is constant, but it is not obvious */
  res = -17;
  a = sollya_lib_parse_string("3*cos(2*x)/(2*sin(x)*cos(x))");
  if (!sollya_lib_get_constant_as_int(&res, a))
    sollya_lib_printf("%b is not a constant.\n\n", a);
  else {
    sollya_lib_printf("%b has been converted to %d\n\n", a, res);
  }
  sollya_lib_clear_obj(a);


  /* An obvious constant */
  res = -17;
  a = SOLLYA_CONST(3);
  if (!sollya_lib_get_constant_as_int(&res, a))
    sollya_lib_printf("%b is not a constant.\n\n", a);
  else {
    sollya_lib_printf("%b has been converted to %d (expecting 3)\n\n", a, res);
  }
  sollya_lib_clear_obj(a);

  /* A constant, but that does not fit on 20 bits */
  res = -17;
  a = SOLLYA_CONST(1073741824);
  if (!sollya_lib_get_constant_as_int(&res, a))
    sollya_lib_printf("%b is not a constant.\n\n", a);
  else {
    sollya_lib_printf("%b has been converted to %d (expecting 1073741824)\n\n", a, res);
  }
  sollya_lib_clear_obj(a);

  /* A negative constant */
  res = -17;
  a = SOLLYA_CONST(-3);
  if (!sollya_lib_get_constant_as_int(&res, a))
    sollya_lib_printf("%b is not a constant.\n\n", a);
  else {
    sollya_lib_printf("%b has been converted to %d (expecting -3)\n\n", a, res);
  }
  sollya_lib_clear_obj(a);


  /* A constant close to an overflow */
  res = -17;
  a = SOLLYA_CONST(1);
  for (i=1;i<=sizeof(int)*8-1;i++) a = SOLLYA_MUL(a, SOLLYA_CONST(2));
  a = SOLLYA_SUB(a, SOLLYA_CONST(1));
  if (!sollya_lib_get_constant_as_int(&res, a))
    sollya_lib_printf("%b is not a constant.\n\n", a);
  else {
    sollya_lib_printf("%b has been converted to %d (expecting MAXINT, i.e. probably 2147483647 or 9223372036854775807)\n\n", a, res);
  }
  sollya_lib_clear_obj(a);

  /* A constant that overflows */
  res = -17;
  a = SOLLYA_CONST(1);
  for (i=1;i<=sizeof(int)*8-1;i++) a = SOLLYA_MUL(a, SOLLYA_CONST(2));
  if (!sollya_lib_get_constant_as_int(&res, a))
    sollya_lib_printf("%b is not a constant.\n\n", a);
  else {
    sollya_lib_printf("%b has been converted to %d (expecting -MAXINT-1, i.e. probably -2147483648 or -9223372036854775808)\n\n", a, res);
  }
  sollya_lib_clear_obj(a);



  /* A constant expression exactly representable as an int but it cannot be decided. */
  res = -17;
  a = sollya_lib_parse_string("(1b200+1)-1b200*(log2(3)/log2(7) - log(3)/log(7) + 1)");
  if (!sollya_lib_get_constant_as_int(&res, a))
    sollya_lib_printf("%b is not a constant.\n\n", a);
  else {
    sollya_lib_printf("%b has been converted to %d (expecting 1)\n\n", a, res);
  }
  sollya_lib_clear_obj(a);


  /* A constant expression very close to the middle between two integers
   and it cannote be decided. */
  res = -17;
  a = sollya_lib_parse_string("1 + 1b-400 + 0.5*(log2(3)/log2(7) - log(3)/log(7) + 1)");
  if (!sollya_lib_get_constant_as_int(&res, a))
    sollya_lib_printf("%b is not a constant.\n\n", a);
  else {
    sollya_lib_printf("%b has been converted to %d (expecting either 1 or 2 -- 2 would be better)\n\n", a, res);
  }
  sollya_lib_clear_obj(a);


  /* A constant expression very close to the middle between two doubles */
  res = -17;
  a = sollya_lib_parse_string("1 + 1b-400 + 0.5");
  if (!sollya_lib_get_constant_as_int(&res, a))
    sollya_lib_printf("%b is not a constant.\n\n", a);
  else {
    sollya_lib_printf("%b has been converted to %d (expecting either 1 or 2 -- 2 would be better)\n\n", a, res);
  }
  sollya_lib_clear_obj(a);


  /* A constant expression exactly at the middle between two doubles, but
     it cannot be decided. */
  res = -17;
  a = sollya_lib_parse_string("1 - 0.5*(log2(3)/log2(7) - log(3)/log(7) + 1)");
  if (!sollya_lib_get_constant_as_int(&res, a))
    sollya_lib_printf("%b is not a constant.\n\n", a);
  else {
    sollya_lib_printf("%b has been converted to %d (expecting either 0 or 1 -- 0 would be better)\n\n", a, res);
  }
  sollya_lib_clear_obj(a);


  /* The same constant but decidable */
  res = -17;
  a = sollya_lib_parse_string("1 - 0.5");
  if (!sollya_lib_get_constant_as_int(&res, a))
    sollya_lib_printf("%b is not a constant.\n\n", a);
  else {
    sollya_lib_printf("%b has been converted to %d (expecting either 0 or 1 -- 0 would be better)\n\n", a, res);
  }
  sollya_lib_clear_obj(a);


  /* Another constant expression exactly at the middle between two doubles, but
     it cannot be decided. */
  res = -17;
  a = sollya_lib_parse_string("1 + 1.5*(log2(3)/log2(7) - log(3)/log(7) + 1)");
  if (!sollya_lib_get_constant_as_int(&res, a))
    sollya_lib_printf("%b is not a constant.\n\n", a);
  else {
    sollya_lib_printf("%b has been converted to %d (expecting either 2 or 3 -- 2 would be better)\n\n", a, res);
  }
  sollya_lib_clear_obj(a);


  /* The same constant but decidable. */
  res = -17;
  a = sollya_lib_parse_string("1 + 1.5");
  if (!sollya_lib_get_constant_as_int(&res, a))
    sollya_lib_printf("%b is not a constant.\n\n", a);
  else {
    sollya_lib_printf("%b has been converted to %d (expecting either 2 or 3 -- 2 would be better)\n\n", a, res);
  }
  sollya_lib_clear_obj(a);


  /* A transcendantal constant. */
  res = -17;
  a = sollya_lib_parse_string("exp(pi) + log(2)");
  if (!sollya_lib_get_constant_as_int(&res, a))
    sollya_lib_printf("%b is not a constant.\n\n", a);
  else {
    sollya_lib_printf("%b has been converted to %d (expecting either 23 or 24 -- 24 would be better)\n\n", a, res);
  }
  sollya_lib_clear_obj(a);


  /* A constant hard to evaluate because exactly zero but undecidable. */
  res = -17;
  a = sollya_lib_parse_string("log10(2)/log10(3) - log(2)/log(3)");
  if (!sollya_lib_get_constant_as_int(&res, a))
    sollya_lib_printf("%b is not a constant.\n\n", a);
  else {
    sollya_lib_printf("%b has been converted to %d (ideally 0, but any value would do the trick, provided that a warning message be displayed.)\n\n", a, res);
  }
  sollya_lib_clear_obj(a);


  /* A constant very hard to evaluate (cf. tevaluate_function_at_constant_expression). */
  res = -17;
  a = sollya_lib_parse_string("(sin((pi) / 3) - sqrt(3) / 2) * (1 * 2^(100000)) + 3");
  if (!sollya_lib_get_constant_as_int(&res, a))
    sollya_lib_printf("%b is not a constant.\n\n", a);
  else {
    sollya_lib_printf("%b has been converted to %d (ideally 3, but any value would do the trick, provided that a warning message be displayed.)\n\n", a, res);
  }
  sollya_lib_clear_obj(a);


  /* Another tricky one. */
  res = -17;
  a = sollya_lib_parse_string("(sin((pi) / 3) - sqrt(3) / 2 ) * (1 * 2^(100000)) + (1 * 2^(60000))");
  if (!sollya_lib_get_constant_as_int(&res, a))
    sollya_lib_printf("%b is not a constant.\n\n", a);
  else {
    sollya_lib_printf("%b has been converted to %d (ideally inf, but any value would do the trick, provided that a warning message be displayed.)\n\n", a, res);
  }
  sollya_lib_clear_obj(a);


  /* Trying -inf */
  res = -17;
  a = sollya_lib_parse_string("-@Inf@");
  if (!sollya_lib_get_constant_as_int(&res, a))
    sollya_lib_printf("%b is not a constant.\n\n", a);
  else {
    sollya_lib_printf("%b has been converted to %d (expecting 0).\n\n", a, res);
  }
  sollya_lib_clear_obj(a);


/* Trying NaN */
  res = -17;
  a = sollya_lib_parse_string("@NaN@");
  if (!sollya_lib_get_constant_as_int(&res, a))
    sollya_lib_printf("%b is not a constant.\n\n", a);
  else {
    sollya_lib_printf("%b has been converted to %d (expecting 0).\n\n", a, res);
  }
  sollya_lib_clear_obj(a);


  sollya_lib_close();
  return 0;
}
