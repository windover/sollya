#include <sollya.h>

#include <mpfr.h>
#include <mpfi.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  sollya_obj_t f1, f2, f3, f4;

  sollya_lib_init();

  f1 = sollya_lib_parse_string("(proc() {myownlog = library(\"./libraryexample\"); return myownlog;})()");
  f2 = SOLLYA_COS(SOLLYA_ADD(SOLLYA_X_, SOLLYA_CONST(1)));
  f3 = sollya_lib_apply(f1, f2, NULL);
  f4 = sollya_lib_diff(f3);
  sollya_lib_printf("%b\n", f4);

  sollya_lib_clear_obj(f1);
  sollya_lib_clear_obj(f2);
  sollya_lib_clear_obj(f3);
  sollya_lib_clear_obj(f4);
  sollya_lib_close();
  return 0;
}
