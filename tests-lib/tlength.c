#include <sollya.h>

int callback(int message) {
  if (message == SOLLYA_MSG_EXPR_NOT_CORRECTLY_TYPED)
    sollya_lib_printf("The following test is not correctly typed\n");
  else
    sollya_lib_printf("Unexpected warning\n");
  return 0;
}

int main(void) {
  sollya_obj_t a, res;

  sollya_lib_init();
  sollya_lib_install_msg_callback(callback);

  a = sollya_lib_string("Hello world!");
  res = sollya_lib_length(a);
  sollya_lib_printf("length of %b is %b\n", a, res);
  sollya_lib_clear_obj(a);
  sollya_lib_clear_obj(res);

  a = sollya_lib_parse_string("[|1,2,3,4,5|]");
  res = sollya_lib_length(a);
  sollya_lib_printf("length of %b is %b\n", a, res);
  sollya_lib_clear_obj(a);
  sollya_lib_clear_obj(res);

  a = sollya_lib_parse_string("[||]");
  res = sollya_lib_length(a);
  sollya_lib_printf("length of %b is %b\n", a, res);
  sollya_lib_clear_obj(a);
  sollya_lib_clear_obj(res);

  a = sollya_lib_parse_string("[|1,2...|]");
  res = sollya_lib_length(a);
  sollya_lib_printf("length of %b is %b\n", a, res);
  sollya_lib_clear_obj(a);
  sollya_lib_clear_obj(res);

  a = sollya_lib_parse_string("[1,2]");
  res = sollya_lib_length(a);
  sollya_lib_printf("length of %b is %b\n", a, res);
  sollya_lib_clear_obj(a);
  sollya_lib_clear_obj(res);

  sollya_lib_uninstall_msg_callback();
  sollya_lib_close();
  return 0;
}
