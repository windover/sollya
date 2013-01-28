#include <sollya.h>
#include <mpfr.h>
#include <mpfi.h>
#include <stdlib.h>
#include <string.h>

int myownlog(mpfi_t result, mpfi_t x, int n) {
  if(n==0) {
    /* Implementation of the neperian logarithm */

    if(mpfi_nan_p(x)) {
      mpfr_t a;
      mpfr_init2(a,mpfi_get_prec(result));
      mpfi_interv_fr(result,a,a);
      mpfr_clear(a);
      return 0;
    }
    if(mpfi_has_zero(x)) {
      mpfr_t a,b;
      mpfr_init2(a,mpfi_get_prec(result));
      mpfr_init2(b,mpfi_get_prec(result));

      mpfr_set_inf(a,-1);
      mpfi_get_right(b,x);
      mpfr_log(b,b,GMP_RNDU);
      mpfi_interv_fr(result, a, b);

      mpfr_clear(a);
      mpfr_clear(b);
      return 0;
    }
    else {
      mpfr_t a,b;
      mpfr_init2(a,mpfi_get_prec(result));
      mpfr_init2(b,mpfi_get_prec(result));

      mpfi_get_left(a,x);
      mpfr_log(a,a, GMP_RNDD);
      mpfi_get_right(b,x);
      mpfr_log(b,b,GMP_RNDU);
      mpfi_interv_fr(result, a, b);

      mpfr_clear(a);
      mpfr_clear(b);
      return 0;
    }
  }


  if(n==1) {
    /* Implementation of 1/x */
    mpfi_inv(result,x);
    return 0;
  }

  if(n==2) {
    /* Implementation of -1/x^2 */
    mpfi_t temp;
    mpfi_init2(temp, mpfi_get_prec(result));

    mpfi_sqr(temp, x);
    mpfi_inv(temp, temp);
    mpfi_neg(result, temp);

    mpfi_clear(temp);
    return 0;
  }

  // else
  mpfr_t a,b;
  mpfr_init2(a, mpfi_get_prec(result));
  mpfr_init2(b, mpfi_get_prec(result));

  mpfr_set_inf(a,-1);
  mpfr_set_inf(b, 1);
  mpfi_interv_fr(result,a,b);

  mpfr_clear(a);
  mpfr_clear(b);
  return 0;
}

int stupid1(mpfi_t result, mpfi_t x, int n) {
  mpfi_set_ui(result, 0);
  return 0;
}

int stupid2(mpfi_t result, mpfi_t x, int n) {
  mpfi_set_ui(result, 0);
  return 0;
}

int stupid3(mpfi_t result, mpfi_t x, int n) {
  mpfi_set_ui(result, 0);
  return 0;
}

int stupid4(mpfi_t result, mpfi_t x, int n) {
  mpfi_set_ui(result, 0);
  return 0;
}

int stupid5(mpfi_t result, mpfi_t x, int n) {
  mpfi_set_ui(result, 0);
  return 0;
}

int stupid6(mpfi_t result, mpfi_t x, int n) {
  mpfi_set_ui(result, 0);
  return 0;
}

int stupid7(mpfi_t result, mpfi_t x, int n) {
  mpfi_set_ui(result, 0);
  return 0;
}


int main(void) {
  sollya_obj_t f[15];
  mpfr_t x,y;
  int i;
  void *ptr;
  char str[256];

  sollya_lib_init();
  f[0] = sollya_lib_free_variable();

  /* Testing normal use */
  f[1] = sollya_lib_libraryfunction(f[0], "superfunc", myownlog);
  sollya_lib_printf("%b (expecting: superfunc(_x_))\n", f[1]);
  mpfr_init2(x, 30);
  mpfr_init2(y, 50);
  mpfr_set_ui(x, 2, GMP_RNDN);
  sollya_lib_evaluate_function_at_point(y, f[1], x, NULL);
  sollya_lib_printf("%v (expecting: approximate value of log(2))\n", y);

  /* Trying to rebind a function already bounded */
  f[2] = sollya_lib_libraryfunction(f[0], "superfunc", myownlog);
  sollya_lib_printf("%b (expecting superfunc(_x_))\n", f[2]);
  f[3] = sollya_lib_libraryfunction(f[0], "foo", myownlog);
  sollya_lib_printf("%b (expecting superfunc(_x_))\n", f[3]);
  f[4] = sollya_lib_libraryfunction(f[0], NULL, myownlog);
  sollya_lib_printf("%b (expecting superfunc(_x_))\n", f[4]);
  f[5] = sollya_lib_libraryfunction(f[0], "exp", myownlog);
  sollya_lib_printf("%b (expecting superfunc(_x_))\n", f[5]);

  for(i=2;i<=5;i++) {
    f[6] = sollya_lib_cmp_equal(f[1], f[i]);
    sollya_lib_printf("%b (expecting true)\n", f[6]);
    sollya_lib_clear_obj(f[6]);
  }

  /* Trying to bind a function to an already assigned name */
  f[6] = sollya_lib_libraryfunction(f[0], "superfunc", stupid1);
  sollya_lib_printf("%b (expecting superfunc_0(_x_))\n", f[6]);

  /* Leaving NULL as second argument */
  f[7] = sollya_lib_libraryfunction(f[0], NULL, stupid2);
  sollya_lib_printf("%b (expecting stupid2(_x_))\n", f[7]);

  /* Unauthorized names */
  f[8] = sollya_lib_libraryfunction(f[0], "e]xp", stupid3);
  sollya_lib_printf("%b (expecting exp_0(_x_))\n", f[8]);

  f[9] = sollya_lib_libraryfunction(f[0], "]0", stupid4);
  sollya_lib_printf("%b (expecting stupid4(_x_))\n", f[9]);

  f[10] = sollya_lib_libraryfunction(f[0], "0]a", stupid5);
  sollya_lib_printf("%b (expecting a(_x_))\n", f[10]);

  /* Pointer to non-valid functions, together with NULL/illicit as second argument */
  f[11] = sollya_lib_libraryfunction(f[0], NULL, stupid6+17);
  sollya_lib_sprintf(str, "%b", f[11]);
  if (strlen(str)>= 8) {
    str[7] = '\0';
    if (strcmp(str, "func_0x")==0) sollya_lib_printf("Testing NULL/invalid ptr combination: OK\n");
    else sollya_lib_printf("Testing NULL/invalid ptr combination: *NOT* OK: %b\n", f[11]);
  }

  f[12] = sollya_lib_libraryfunction(f[0], NULL, stupid7-17);
  sollya_lib_sprintf(str, "%b", f[12]);
  if (strlen(str)>= 8) {
    str[7] = '\0';
    if (strcmp(str, "func_0x")==0) sollya_lib_printf("Testing NULL/invalid ptr combination: OK\n");
    else sollya_lib_printf("Testing NULL/invalid ptr combination: *NOT* OK: %b\n", f[12]);
  }

  f[13] = sollya_lib_libraryfunction(f[0], "", (int (*)(mpfi_t, mpfi_t, int))(&x));
  sollya_lib_sprintf(str, "%b", f[13]);
  if (strlen(str)>= 8) {
    str[7] = '\0';
    if (strcmp(str, "func_0x")==0) sollya_lib_printf("Testing NULL/invalid ptr combination: OK\n");
    else sollya_lib_printf("Testing NULL/invalid ptr combination: *NOT* OK: %b\n", f[13]);
  }

  ptr = malloc(1);
  f[14] = sollya_lib_libraryfunction(f[0], "*]%", (int (*)(mpfi_t, mpfi_t, int))(ptr));
  sollya_lib_sprintf(str, "%b", f[14]);
  if (strlen(str)>= 8) {
    str[7] = '\0';
    if (strcmp(str, "func_0x")==0) sollya_lib_printf("Testing NULL/invalid ptr combination: OK\n");
    else sollya_lib_printf("Testing NULL/invalid ptr combination: *NOT* OK: %b\n", f[14]);
  }

  for(i=0;i<=14;i++) sollya_lib_clear_obj(f[i]);
  mpfr_clear(x);
  mpfr_clear(y);
  free(ptr);
  sollya_lib_close();
  return 0;
}