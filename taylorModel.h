
#ifndef AUTODIFF_H
#define AUTODIFF_H
//void taylor_model(mpfi_t* rem_bound, mpfi_t* res_array, node *f, mpfi_t x, int n);
tModel* createEmptytModel(int n,  mpfi_t x);
void taylor_model(tModel *t, node *f, mpfi_t x, int n);
#endif
