

int foo(int *res, void **args) {

  *res = *((int *) args[0]) + *((int *) args[1]);

  return 1;
}
