#include <sollya.h>

int callback(int message) {
  if (message == SOLLYA_MSG_EXPR_NOT_CORRECTLY_TYPED)
    sollya_lib_printf("The following test produces a typing error\n");
  else
    sollya_lib_printf("Unexpected message\n");
  return 0;
}

int main(void) {
  sollya_obj_t a, res;
  double nan = 0.0/0.0;

  sollya_lib_init();
  sollya_lib_install_msg_callback(callback);

  a = SOLLYA_CONST(2);
  res = sollya_lib_inf(a);
  sollya_lib_printf("inf of %b is %b\n", a, res);
  sollya_lib_clear_obj(a);
  sollya_lib_clear_obj(res);

  a = SOLLYA_DIV(SOLLYA_CONST(1), SOLLYA_CONST(3));
  res = sollya_lib_inf(a);
  sollya_lib_printf("inf of %b is %b\n", a, res);
  sollya_lib_clear_obj(a);
  sollya_lib_clear_obj(res);

  a = SOLLYA_LOG(SOLLYA_NEG(SOLLYA_CONST(3)));
  res = sollya_lib_inf(a);
  sollya_lib_printf("inf of %b is %b\n", a, res);
  sollya_lib_clear_obj(a);
  sollya_lib_clear_obj(res);

  a = SOLLYA_CONST(nan);
  res = sollya_lib_inf(a);
  sollya_lib_printf("inf of %b is %b\n", a, res);
  sollya_lib_clear_obj(a);
  sollya_lib_clear_obj(res);

  a = sollya_lib_parse_string("[1,2]");
  res = sollya_lib_inf(a);
  sollya_lib_printf("inf of %b is %b\n", a, res);
  sollya_lib_clear_obj(a);
  sollya_lib_clear_obj(res);

  a = SOLLYA_X_;
  res = sollya_lib_inf(a);
  sollya_lib_printf("inf of %b is %b\n", a, res);
  sollya_lib_clear_obj(a);
  sollya_lib_clear_obj(res);

  a = sollya_lib_string("Hello");
  res = sollya_lib_inf(a);
  sollya_lib_printf("inf of %b is %b\n", a, res);
  sollya_lib_clear_obj(a);
  sollya_lib_clear_obj(res);

  sollya_lib_uninstall_msg_callback();
  sollya_lib_close();
  return 0;
}