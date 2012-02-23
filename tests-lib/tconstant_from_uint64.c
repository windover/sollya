#include <sollya.h>

int main(void) {
  sollya_obj_t a, a2, prec;
  uint64_t b;

  sollya_lib_init();

  b = -5;
  a = sollya_lib_constant_from_uint64(b);
  sollya_lib_printf("%b (should be %llu)\n", a, (unsigned long long int)b);
  sollya_lib_clear_obj(a);

  b = 7;
  a = sollya_lib_constant_from_uint64(b);
  sollya_lib_printf("%b (should be %llu)\n", a, (unsigned long long int)b);
  sollya_lib_clear_obj(a);

  /* overflow */
  b = 1234567890;
  b *= 1234567890;
  b *= 123456;
  a = sollya_lib_constant_from_uint64(b);
  sollya_lib_printf("%b (should be %llu)\n", a, (unsigned long long int)b);
  sollya_lib_clear_obj(a);

  prec = sollya_lib_constant_from_uint64(20);
  sollya_lib_set_prec(prec);
  sollya_lib_clear_obj(prec);
  b = 4194304; /* Does not fit on 20 bits */
  a = sollya_lib_constant_from_uint64(b);
  sollya_lib_printf("%b (should be %llu)\n", a, (unsigned long long int)b);

  sollya_lib_close();
  return 0;
}
