#include <sollya.h>
#include <mpfr.h>
#include <stdlib.h>
#include <string.h>

void euler_gamma(mpfr_t res, mp_prec_t prec) {
  mpfr_set_prec(res, prec);
  mpfr_const_euler(res, GMP_RNDN);
  return;
}

void stupid1(mpfr_t res, mp_prec_t prec) {
  mpfr_set_ui(res, 0, GMP_RNDN);
  return;
}

void stupid2(mpfr_t res, mp_prec_t prec) {
  mpfr_set_ui(res, 0, GMP_RNDN);
  return;
}

void stupid3(mpfr_t res, mp_prec_t prec) {
  mpfr_set_ui(res, 0, GMP_RNDN);
  return;
}

void stupid4(mpfr_t res, mp_prec_t prec) {
  mpfr_set_ui(res, 0, GMP_RNDN);
  return;
}

void stupid5(mpfr_t res, mp_prec_t prec) {
  mpfr_set_ui(res, 0, GMP_RNDN);
  return;
}

void stupid6(mpfr_t res, mp_prec_t prec) {
  mpfr_set_ui(res, 0, GMP_RNDN);
  return;
}

void stupid7(mpfr_t res, mp_prec_t prec) {
  mpfr_set_ui(res, 0, GMP_RNDN);
  return;
}

int main(void) {
  sollya_obj_t f[15];
  int i;
  void *ptr;
  char str[256];
  mpfr_t x,y;

  sollya_lib_init();

  /* Normal use */
  f[0] = sollya_lib_libraryconstant("superconst", euler_gamma);
  sollya_lib_printf("%b (expecting superconst)\n", f[0]);
  mpfr_init2(x, 30);
  mpfr_init2(y, 50);
  mpfr_set_ui(x, 0, GMP_RNDN);
  sollya_lib_evaluate_function_at_point(y, f[0], x, NULL);
  sollya_lib_printf("%v (expecting: 0.5772...)\n", y);

  /* Trying to rebind a constant already bounded */
  f[1] = sollya_lib_libraryconstant("*]%", euler_gamma);
  sollya_lib_printf("%b (expecting superconst)\n", f[1]);
  f[2] = sollya_lib_libraryconstant("superconst", euler_gamma);
  sollya_lib_printf("%b (expecting superconst)\n", f[2]);
  f[3] = sollya_lib_libraryconstant("foo", euler_gamma);
  sollya_lib_printf("%b (expecting superconst)\n", f[3]);
  f[4] = sollya_lib_libraryconstant(NULL, euler_gamma);
  sollya_lib_printf("%b (expecting superconst)\n", f[4]);
  f[5] = sollya_lib_libraryconstant("pi", euler_gamma);
  sollya_lib_printf("%b (expecting superconst)\n", f[5]);

  for(i=1;i<=5;i++) {
    f[6] = sollya_lib_cmp_equal(f[0], f[i]);
    sollya_lib_printf("%b (expecting true)\n", f[6]);
    sollya_lib_clear_obj(f[6]);
  }

   /* Trying to bind a function to an already assigned name */
  f[6] = sollya_lib_libraryconstant("superconst", stupid1);
  sollya_lib_printf("%b (expecting superconst_0)\n", f[6]);

  /* Leaving NULL as first argument */
  f[7] = sollya_lib_libraryconstant(NULL, stupid2);
  sollya_lib_printf("%b (expecting stupid2)\n", f[7]);

  /* Unauthorized names */
  f[8] = sollya_lib_libraryconstant("e]xp", stupid3);
  sollya_lib_printf("%b (expecting exp_0)\n", f[8]);

  f[9] = sollya_lib_libraryconstant("]0", stupid4);
  sollya_lib_printf("%b (expecting stupid4)\n", f[9]);

  f[10] = sollya_lib_libraryconstant("0]a", stupid5);
  sollya_lib_printf("%b (expecting a)\n", f[10]);

  /* Pointer to non-valid functions, together with NULL/illicit as second argument */
  f[11] = sollya_lib_libraryconstant(NULL, stupid6+17);
  sollya_lib_sprintf(str, "%b", f[11]);
  if (strlen(str)>= 8) {
    str[7] = '\0';
    if (strcmp(str, "const_0x")==0) sollya_lib_printf("Testing NULL/invalid ptr combination: OK\n");
    else sollya_lib_printf("Testing NULL/invalid ptr combination: *NOT* OK: %b\n", f[11]);
  }

  f[12] = sollya_lib_libraryconstant(NULL, stupid7-17);
  sollya_lib_sprintf(str, "%b", f[12]);
  if (strlen(str)>= 8) {
    str[7] = '\0';
    if (strcmp(str, "const_0x")==0) sollya_lib_printf("Testing NULL/invalid ptr combination: OK\n");
    else sollya_lib_printf("Testing NULL/invalid ptr combination: *NOT* OK: %b\n", f[12]);
  }

  f[13] = sollya_lib_libraryconstant("", (void (*)(mpfr_t, mp_prec_t))(&x));
  sollya_lib_sprintf(str, "%b", f[13]);
  if (strlen(str)>= 8) {
    str[7] = '\0';
    if (strcmp(str, "const_0x")==0) sollya_lib_printf("Testing NULL/invalid ptr combination: OK\n");
    else sollya_lib_printf("Testing NULL/invalid ptr combination: *NOT* OK: %b\n", f[13]);
  }

  ptr = malloc(1);
  f[14] = sollya_lib_libraryconstant("*]%", (void (*)(mpfr_t, mp_prec_t))(ptr));
  sollya_lib_sprintf(str, "%b", f[14]);
  if (strlen(str)>= 8) {
    str[7] = '\0';
    if (strcmp(str, "const_0x")==0) sollya_lib_printf("Testing NULL/invalid ptr combination: OK\n");
    else sollya_lib_printf("Testing NULL/invalid ptr combination: *NOT* OK: %b\n", f[14]);
  }

  for(i=0;i<=14;i++) sollya_lib_clear_obj(f[i]);
  free(ptr);
  mpfr_clear(x);
  mpfr_clear(y);
  sollya_lib_close();
  return 0;
}
