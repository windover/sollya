#include <sollya.h>
#include <mpfr.h>

void stupid1(mpfr_t res, mp_prec_t prec) {
  mpfr_set_ui(res, 0, GMP_RNDN);
  return;
}

void stupid2(mpfr_t res, mp_prec_t prec) {
  mpfr_set_ui(res, 1, GMP_RNDN);
  return;
}

int main(void) {
  sollya_obj_t f[11];
  void (*libfun)(mpfr_t, mp_prec_t) = NULL;
  int res = -1;
  int i;

  sollya_lib_init();

  f[0] = sollya_lib_parse_string("(proc() {euler_gamma = libraryconstant(\"./libraryexample\"); return euler_gamma;})()");

  /* Trying to decompose an object that is *not* a library constant */
  f[1] = SOLLYA_COS(SOLLYA_CONST(4));
  f[2] = sollya_lib_add(f[0], f[1]);
  res = sollya_lib_decompose_library_constant(&libfun, f[2]);
  if (res) sollya_lib_printf("sollya_lib_decompose_library_constant should not succeed on %b but it did.\n", f[2]);

  /* Trying to decompose a library constant created by parse_string */
  /* Trying also to recompose an object with the function pointer that we get and to test if both objects compare equal. */
  res = -1;  libfun = NULL;
  res = sollya_lib_decompose_library_constant(&libfun, f[0]);
  f[3] = sollya_lib_libraryconstant("should_not_be_used", libfun);
  f[4] = sollya_lib_cmp_equal(f[2], f[3]);
  if (!res) sollya_lib_printf("sollya_lib_decompose_library_constant should succeed on %b. It did not.\n", f[0]);
  else {
    sollya_lib_printf("%b == %b gives %b (expecting true)\n", f[2], f[3], f[4]);
  }


  /* Trying to decompose a library constant created with sollya_lib_libraryconstant */
  /* Trying also to recompose an object with the function pointer that we get and to test if both objects compare equal. */
  res = -1; libfun = NULL;
  f[5] = sollya_lib_libraryconstant("foo", stupid1);
  res = sollya_lib_decompose_library_constant(&libfun, f[5]);
  f[6] = sollya_lib_libraryconstant("should_not_be_used", libfun);
  f[7] = sollya_lib_cmp_equal(f[5], f[6]);
  if (!res) sollya_lib_printf("sollya_lib_decompose_library_constant should succeed on %b. It did not.\n", f[5]);
  else {
    sollya_lib_printf("%b == %b gives %b (expecting true)\n", f[5], f[6], f[7]);
  }


  /* Trying to decompose a library constant created with sollya_lib_build_function_libraryconstant */
  /* Trying also to recompose an object with the function pointer that we get and to test if both objects compare equal. */
  res = -1; libfun = NULL;
  f[8] = sollya_lib_build_function_libraryconstant("bar", stupid2);
  res = sollya_lib_decompose_library_constant(&libfun, f[8]);
  f[9] = sollya_lib_libraryconstant("should_not_be_used", libfun);
  f[10] = sollya_lib_cmp_equal(f[8], f[9]);
  if (!res) sollya_lib_printf("sollya_lib_decompose_library_constant should succeed on %b. It did not.\n", f[8]);
  else {
    sollya_lib_printf("%b == %b gives %b (expecting true)\n", f[8], f[9], f[10]);
  }

  for(i=0;i<=10;i++)  sollya_lib_clear_obj(f[i]);

  sollya_lib_close();
  return 0;
}
