#include <gmp.h>
#include <mpfr.h>
#include <fpu_control.h>


#define p_coeff_0h 9.99999999999999777955395074968691915273666381835937500000000000000000000000000000e-01
#define p_coeff_1h 1.00000000000000288657986402540700510144233703613281250000000000000000000000000000e+00
#define p_coeff_2h 5.00000000000066835426082434423733502626419067382812500000000000000000000000000000e-01
#define p_coeff_3h 1.66666666666438284538642733423330355435609817504882812500000000000000000000000000e-01
#define p_coeff_4h 4.16666666634575161287656897002307232469320297241210937500000000000000000000000000e-02
#define p_coeff_5h 8.33333333832309529343174148152684210799634456634521484375000000000000000000000000e-03
#define p_coeff_6h 1.38888894469550586499573263665752165252342820167541503906250000000000000000000000e-03
#define p_coeff_7h 1.98412654896551427863640726378946510521927848458290100097656250000000000000000000e-04
#define p_coeff_8h 2.48011514581319301639677349369250691779598128050565719604492187500000000000000000e-05
#define p_coeff_9h 2.75588903929834437773246230696244651880988385528326034545898437500000000000000000e-06
#define p_coeff_10h 2.77134645062331469506691208545823279507658298825845122337341308593750000000000000e-07
#define p_coeff_11h 2.48960985304026694022116555872134457949584884772775694727897644042968750000000000e-08

void p(double *p_resh, double x);

void mpfr_to_double(double *dh, mpfr_t op) {
  *dh = mpfr_get_d(op, GMP_RNDN);
}


void double_to_mpfr(mpfr_t rop, double dh) {
  mpfr_set_d(rop,dh,GMP_RNDN);
}


void f(mpfr_t y, mpfr_t xMpfr) {
  unsigned short oldcw, cw;

  double x;
  double resh;

  _FPU_GETCW(oldcw);
  cw = (_FPU_DEFAULT & ~_FPU_EXTENDED)|_FPU_DOUBLE;
  _FPU_SETCW(cw);

  mpfr_to_double(&x, xMpfr);     
  p(&resh, x);
  double_to_mpfr(y, resh);

  _FPU_SETCW(oldcw);

}

void p(double *p_resh, double x) {




double p_t_1_0h;
double p_t_2_0h;
double p_t_3_0h;
double p_t_4_0h;
double p_t_5_0h;
double p_t_6_0h;
double p_t_7_0h;
double p_t_8_0h;
double p_t_9_0h;
double p_t_10_0h;
double p_t_11_0h;
double p_t_12_0h;
double p_t_13_0h;
double p_t_14_0h;
double p_t_15_0h;
double p_t_16_0h;
double p_t_17_0h;
double p_t_18_0h;
double p_t_19_0h;
double p_t_20_0h;
double p_t_21_0h;
double p_t_22_0h;
double p_t_23_0h;
 


p_t_1_0h = p_coeff_11h;
p_t_2_0h = p_t_1_0h * x;
p_t_3_0h = p_coeff_10h + p_t_2_0h;
p_t_4_0h = p_t_3_0h * x;
p_t_5_0h = p_coeff_9h + p_t_4_0h;
p_t_6_0h = p_t_5_0h * x;
p_t_7_0h = p_coeff_8h + p_t_6_0h;
p_t_8_0h = p_t_7_0h * x;
p_t_9_0h = p_coeff_7h + p_t_8_0h;
p_t_10_0h = p_t_9_0h * x;
p_t_11_0h = p_coeff_6h + p_t_10_0h;
p_t_12_0h = p_t_11_0h * x;
p_t_13_0h = p_coeff_5h + p_t_12_0h;
p_t_14_0h = p_t_13_0h * x;
p_t_15_0h = p_coeff_4h + p_t_14_0h;
p_t_16_0h = p_t_15_0h * x;
p_t_17_0h = p_coeff_3h + p_t_16_0h;
p_t_18_0h = p_t_17_0h * x;
p_t_19_0h = p_coeff_2h + p_t_18_0h;
p_t_20_0h = p_t_19_0h * x;
p_t_21_0h = p_coeff_1h + p_t_20_0h;
p_t_22_0h = p_t_21_0h * x;
p_t_23_0h = p_coeff_0h + p_t_22_0h;
*p_resh = p_t_23_0h;


}
