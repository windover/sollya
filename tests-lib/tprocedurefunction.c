#include <sollya.h>
#include <mpfr.h>

int main(void) {
  sollya_obj_t f1;
  sollya_obj_t f2;
  sollya_obj_t f3;
  mpfr_t x,y;

  sollya_lib_init();
  f1 = sollya_lib_parse_string("proc(X,n,p) {var res, oldPrec; oldPrec = prec; prec = p!; res = exp(X); prec = oldPrec!; return res; };");
  f2 = sollya_lib_free_variable();
  f3 = sollya_lib_procedurefunction(f2, f1);
  sollya_lib_printf("%b\n", f3);
  mpfr_init2(x, 30);
  mpfr_init2(y, 50);
  mpfr_set_ui(x, 2, GMP_RNDN);
  sollya_lib_evaluate_function_at_point(y,f3, x, NULL);
  sollya_lib_printf("%v (expecting approximate value of exp(2))\n", y);
  sollya_lib_clear_obj(f1);
  sollya_lib_clear_obj(f2);
  sollya_lib_clear_obj(f3);
  mpfr_clear(x);
  mpfr_clear(y);
  sollya_lib_close();
  return 0;
}
