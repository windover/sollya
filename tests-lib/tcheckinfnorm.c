#include <sollya.h>

#define A_DIM 4

int callback(int message) {
  switch(message) {
  case SOLLYA_MSG_FAITHFUL_ROUNDING_FOR_EXPR_THAT_SHOULD_BE_CONST:
    sollya_lib_printf("Caught the message: a certain expression should have been constant and has been faithfully rounded.\n");
    break;
  default:
    sollya_lib_printf("Unexpected warning %d.\n", message);
  }
  return 0;
}

int main(void) {
  sollya_obj_t a[A_DIM];
  sollya_obj_t res;
  int i;

  sollya_lib_init();
  sollya_lib_install_msg_callback(callback);

  /* checkinfnorm(sin(x),[0;1.75], 1); */
  for (i=0;i<A_DIM;i++) {
    a[i] = NULL;
  }
  
  a[0] = SOLLYA_SIN(SOLLYA_X_);
  a[1] = sollya_lib_parse_string("[0;1.75]");
  a[2] = SOLLYA_CONST(1.0);

  res = sollya_lib_checkinfnorm(a[0],a[1],a[2]);
  
  sollya_lib_printf("checkinfnorm(%b, %b, %b) = %b - expecting true\n",a[0],a[1],a[2],res);
  
  for (i=0;i<A_DIM;i++) {
    if (a[i] != NULL) sollya_lib_clear_obj(a[i]);
  }

  /* checkinfnorm(sin(x),[0;1.75], 1/2); */
  for (i=0;i<A_DIM;i++) {
    a[i] = NULL;
  }
  
  a[0] = SOLLYA_SIN(SOLLYA_X_);
  a[1] = sollya_lib_parse_string("[0;1.75]");
  a[2] = SOLLYA_CONST(0.5);

  res = sollya_lib_checkinfnorm(a[0],a[1],a[2]);
  
  sollya_lib_printf("checkinfnorm(%b, %b, %b) = %b - expecting false\n",a[0],a[1],a[2],res);
  
  for (i=0;i<A_DIM;i++) {
    if (a[i] != NULL) sollya_lib_clear_obj(a[i]);
  }

  /* checkinfnorm(sin(x),[0;20/39], 1/2);*/
  for (i=0;i<A_DIM;i++) {
    a[i] = NULL;
  }
  
  a[0] = SOLLYA_SIN(SOLLYA_X_);
  a[1] = sollya_lib_parse_string("[0;20/39]");
  a[2] = SOLLYA_CONST(0.5);

  res = sollya_lib_checkinfnorm(a[0],a[1],a[2]);
  
  sollya_lib_printf("checkinfnorm(%b, %b, %b) = %b - expecting true\n",a[0],a[1],a[2],res);
  
  for (i=0;i<A_DIM;i++) {
    if (a[i] != NULL) sollya_lib_clear_obj(a[i]);
  }


  sollya_lib_close();
  return 0;
}

