#include <sollya.h>

int main(void) {
  sollya_obj_t a;
  int n;

  sollya_lib_init();

  n = sollya_lib_printf("Hello word!\n");
  sollya_lib_printf("Expecting 12 characters. Counted %d.\n", n);

  a = SOLLYA_CONST(17);
  sollya_lib_printf("%+10.*b\n%+*.*d\n0123456789 \n", 42, a, 10, 4, 17);
  sollya_lib_clear_obj(a);

  sollya_lib_close();
  return 0;
}
