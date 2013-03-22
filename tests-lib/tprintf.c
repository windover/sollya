#define _BSD_SOURCE
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <stdint.h>
#include <unistd.h>
#include <stddef.h>
#include <sollya.h>

#define SIZE 32
#define BUFSIZE 256

typedef signed char hh_t;
typedef unsigned char hhu_t;
typedef short int h_t;
typedef unsigned short int hu_t;
typedef long int l_t;
typedef unsigned long int lu_t;
typedef long long int ll_t;
typedef unsigned long long int llu_t;
typedef intmax_t j_t;
typedef intmax_t ju_t;
typedef size_t z_t;
typedef ssize_t zu_t;
typedef ptrdiff_t t_t;

int counter = 0;

size_t my_strnlen(const char *s, size_t lngmax) {
  int i;
  for(i=0;(size_t)(i)<lngmax;i++) {
    if (s[i]=='\0') return strlen(s);
  }
  return lngmax;
}

int wrapper_sollya_sprintf(char *str, const char *format, ...) {
  va_list va;
  int r;
  counter++;
  va_start(va, format);
  r = sollya_lib_v_sprintf(str, format, va);
  va_end(va);
  return r;
}

int wrapper_sollya_snprintf(char *str, size_t size, const char *format, ...) {
  va_list va;
  int r;
  counter++;
  va_start(va, format);
  r = sollya_lib_v_snprintf(str, size, format, va);
  va_end(va);
  return r;
}

void clean_simple_tab(char tab[SIZE]) {
  int j;
  for(j=0;j<SIZE;j++) tab[j] = 5;
}

void clean_buffer(char tab[BUFSIZE]) {
  int j;
  for(j=0;j<BUFSIZE;j++) tab[j] = 'a';
}

void clean(char tab1[2][SIZE], char tab2[2][SIZE], char res[2][BUFSIZE]) {
  clean_simple_tab(tab1[0]); clean_simple_tab(tab1[1]);
  clean_simple_tab(tab2[0]); clean_simple_tab(tab2[1]);
  clean_buffer(res[0]); clean_buffer(res[1]);
}

/* Variable all_tests is a boolean indicating if all tests should be performed.
   Typically, if snprintf has been used and the output is truncated, some tests
   should be avoided: the returned value is not equal to the length of the
   written string for instance, which is one of the tests performed.

   In the case when not all tests are performed, size_snprintf indicates what
   size argument were passed to snprintf, allowing for specific tests.
*/
int verif(int r[2], char result[2][BUFSIZE], char test1[2][SIZE], char test2[2][SIZE], int length, int all_tests, size_t size_snprintf) {
  int test = 1;
  int i;
  int counter[2];
  char test3[2][SIZE];
  char *ptr;
  int n;

  for(i=0;i<2;i++) {
    counter[i] = my_strnlen(result[i], BUFSIZE);
    if (counter[i]==BUFSIZE) counter[i] = -1;
  }

  if (all_tests) {
    if (counter[0] != r[0]) {
      test = 0;
      printf("First function returned %d but %d characters have been written. ", r[0], counter[0]);
    }
    if (counter[1] != r[1]) {
      test = 0;
      printf("Second function returned %d but %d characters have been written. ", r[1], counter[1]);
    }
  }
  else {
    if (size_snprintf == 0) {
      for(i=0;i<BUFSIZE-1;i++) { if (result[0][i] != 'a') test=0;}
      if (result[0][BUFSIZE-1] != '\0') test = 0;
      if (!test)
        printf("The pointer should have been left intact by the first function, but is now indeed %s\n", result[0]);
      for(i=0;i<BUFSIZE-1;i++) { if (result[1][i] != 'a') test=0;}
      if (result[1][BUFSIZE-1] != '\0') test = 0;
      if (!test)
        printf("The pointer should have been left intact by the second function, but is now indeed %s\n", result[1]);
    }
    else {
      if (counter[0] != (int)(size_snprintf)-1) {
        test = 0;
        printf("First function wrote %d characters but at most %d characters should have been written. ", counter[0], (int)(size_snprintf)-1);
      }
      if (counter[1] != (int)(size_snprintf)-1) {
        test = 0;
        printf("Second function wrote %d characters but (at most) %d characters should have been written. ", counter[0], (int)(size_snprintf)-1);
      }
    }
  }
  if (r[0] != r[1]) {
    test = 0;
    printf("First function returned %d and second function returned %d. ", r[0], r[1]);
  }

  for(i=0;i<SIZE;i++) {
    if(test1[0][i] != test1[1][i]) {
      test = 0;
      printf("The first %%n does not lead to the same value with both implementation. ");
      break;
    }
  }

  if (all_tests) {
    clean_simple_tab(test3[0]); clean_simple_tab(test3[1]);
    ptr = strstr(result[0], " Hello");
    if (ptr==NULL) {
      test = 0;
      printf("The string returned by the first function does not contain ' Hello'. ");
    }
    else {
      n = ptr-result[0];
      switch(length) {
      case 0: *((hh_t *)(test3[0]+9)) = (hh_t)n; break;
      case 1: *((hhu_t *)(test3[0]+9)) = (hhu_t)n; break;
      case 2: *((h_t *)(test3[0]+9)) = (h_t)n; break;
      case 3: *((hu_t *)(test3[0]+9)) = (hu_t)n; break;
      case 4: *((l_t *)(test3[0]+9)) = (l_t)n; break;
      case 5: *((lu_t *)(test3[0]+9)) = (lu_t)n; break;
      case 6: *((ll_t *)(test3[0]+9)) = (ll_t)n; break;
      case 7: *((llu_t *)(test3[0]+9)) = (llu_t)n; break;
      case 8: *((j_t *)(test3[0]+9)) = (j_t)n; break;
      case 9: *((ju_t *)(test3[0]+9)) = (ju_t)n; break;
      case 10: *((z_t *)(test3[0]+9)) = (z_t)n; break;
      case 11: *((zu_t *)(test3[0]+9)) = (zu_t)n; break;
      default: *((t_t *)(test3[0]+9)) = (t_t)n; break;
      }
    }

    for(i=0;i<SIZE;i++) {
      if(test1[0][i] != test3[0][i]) {
        test = 0;
        printf("The first %%n of the first function did not return the expected value (%d). ", n);
        break;
      }
    }
  }

  for(i=0;i<SIZE;i++) {
    if(test2[0][i] != test2[1][i]) {
      test = 0;
      printf("The second %%n does not lead to the same value with both implementation. ");
      break;
    }
  }

  if (all_tests) {
    ptr = strstr(result[0]+n+1, " Hello");
    if (ptr==NULL) {
      test = 0;
      printf("The string returned by the first function does not contain two instances of ' Hello'. ");
    }
    else {
      n = ptr-result[0];
      switch(length) {
      case 0: *((hh_t *)(test3[1]+9)) = (hh_t)n; break;
      case 1: *((hhu_t *)(test3[1]+9)) = (hhu_t)n; break;
      case 2: *((h_t *)(test3[1]+9)) = (h_t)n; break;
      case 3: *((hu_t *)(test3[1]+9)) = (hu_t)n; break;
      case 4: *((l_t *)(test3[1]+9)) = (l_t)n; break;
      case 5: *((lu_t *)(test3[1]+9)) = (lu_t)n; break;
      case 6: *((ll_t *)(test3[1]+9)) = (ll_t)n; break;
      case 7: *((llu_t *)(test3[1]+9)) = (llu_t)n; break;
      case 8: *((j_t *)(test3[1]+9)) = (j_t)n; break;
      case 9: *((ju_t *)(test3[1]+9)) = (ju_t)n; break;
      case 10: *((z_t *)(test3[1]+9)) = (z_t)n; break;
      case 11: *((zu_t *)(test3[1]+9)) = (zu_t)n; break;
      default: *((t_t *)(test3[1]+9)) = (t_t)n; break;
      }
    }

    for(i=0;i<SIZE;i++) {
      if(test2[0][i] != test3[1][i]) {
        test = 0;
        printf("The second %%n of the first function did not return the expected value (%d). ", n);
        break;
      }
    }
  }

  if(strcmp(result[0], result[1])) {
    test = 0;
    printf("Both implementations did not return the same string. ");
  }

  if(strchr(result[0], '%')) {
    test = 0;
    printf("The format string has not been understood by the first function. ");
  }

  if (!test) {
    printf("Below: first the string returned by the first function, then the string returned by the second function.\n");
    printf("%s [returned value: %d]\n", result[0], r[0]);
    printf("%s [returned value: %d]\n", result[1], r[1]);

    for(i=0;i<SIZE-1;i++) printf("%hhu-", test1[0][i]);
    printf("%hhu. [First %%n returned by the first function]\n", test1[0][SIZE-1]);

    for(i=0;i<SIZE-1;i++) printf("%hhu-", test1[1][i]);
    printf("%hhu. [First %%n returned by the second function]\n", test1[1][SIZE-1]);

    for(i=0;i<SIZE-1;i++) printf("%hhu-", test3[0][i]);
    printf("%hhu. [Expected first %%n returned by the first function]\n", test3[0][SIZE-1]);

    for(i=0;i<SIZE-1;i++) printf("%hhu-", test2[0][i]);
    printf("%hhu. [Second %%n returned by the first function]\n", test2[0][SIZE-1]);

    for(i=0;i<SIZE-1;i++) printf("%hhu-", test2[1][i]);
    printf("%hhu. [Second %%n returned by the second function]\n", test2[1][SIZE-1]);

    for(i=0;i<SIZE-1;i++) printf("%hhu-", test3[1][i]);
    printf("%hhu. [Expected second %%n returned by the first function]\n", test3[1][SIZE-1]);
  }

  return test;
}

#define DO_TESTS(cast)                                                  \
  if (p!=1) {                                                           \
    clean(test1, test2, result);                                        \
    sprintf(format, "|%%%s%d.%.0d%s%c| %%%sn %%s |%%%s%d.%.0d%s%c| %%%sn %%s", \
            flags, width[w], prec[p], length[L], conv[c], length[L],    \
            flags, width[w], prec[p], length[L], conv[c], length[L]);   \
    for(i=0;i<2;i++)                                                    \
      r[i] = prntf[i](result[i], format,                                \
                      (cast)(val[v]), (cast *)(test1[i]+9), str,        \
                      (cast)(val[v]), (cast *)(test2[i]+9), str);       \
    if(!verif(r, result, test1, test2, 2*L+(!c), 1, 17))                \
      printf("Tested format string was: \"%s\", %d\n\n", format, val[v]); \
    snlength[3] = (size_t)(r[0]); snlength[4] = (size_t)(r[0])+1;       \
    for(j=0;j<5;j++) {                                                  \
      clean(test1, test2, result);                                      \
      for(i=0;i<2;i++) {                                                \
        r[i] = snprntf[i]( (j==0)?NULL:result[i], snlength[j], format,  \
                          (cast)(val[v]), (cast *)(test1[i]+9), str,    \
                          (cast)(val[v]), (cast *)(test2[i]+9), str);   \
        result[i][BUFSIZE-1] = '\0';                                    \
      }                                                                 \
      if(!verif(r, result, test1, test2, 2*L+(!c), (j==4), snlength[j])) \
        printf("Tested format string was: \"%s\", %d\n\n", format, val[v]); \
    }                                                                   \
                                                                        \
                                                                        \
                                                                        \
    clean(test1, test2, result);                                        \
    sprintf(format, "|%%%s*.%.0d%s%c| %%%sn %%s |%%%s*.%.0d%s%c| %%%sn %%s", \
            flags, prec[p], length[L], conv[c], length[L],              \
            flags, prec[p], length[L], conv[c], length[L]);             \
    for(i=0;i<2;i++)                                                    \
      r[i] = prntf[i](result[i], format,                                \
                      width[w], (cast)(val[v]), (cast *)(test1[i]+9), str, \
                      width[w], (cast)(val[v]), (cast *)(test2[i]+9), str); \
    if(!verif(r, result, test1, test2, 2*L+(!c), 1, 17))                \
      printf("Tested format string was: \"%s\", %d, %d\n\n", format, width[w], val[v]); \
    snlength[3] = (size_t)(r[0]); snlength[4] = (size_t)(r[0])+1;       \
    for(j=0;j<5;j++) {                                                  \
      clean(test1, test2, result);                                      \
      for(i=0;i<2;i++) {                                                \
        r[i] = snprntf[i]( (j==0)?NULL:result[i], snlength[j], format,  \
                           width[w], (cast)(val[v]), (cast *)(test1[i]+9), str, \
                           width[w], (cast)(val[v]), (cast *)(test2[i]+9), str); \
        result[i][BUFSIZE-1] = '\0';                                    \
      }                                                                 \
      if(!verif(r, result, test1, test2, 2*L+(!c), (j==4), snlength[j])) \
        printf("Tested format string was: \"%s\", %d, %d\n\n", format, width[w], val[v]); \
    }                                                                   \
  }                                                                     \
                                                                        \
  clean(test1, test2, result);                                          \
  sprintf(format, "|%%%s%d.*%s%c| %%%sn %%s |%%%s%d.*%s%c| %%%sn %%s",  \
          flags, width[w], length[L], conv[c], length[L],               \
          flags, width[w], length[L], conv[c], length[L]);              \
  for(i=0;i<2;i++)                                                      \
    r[i] = prntf[i](result[i], format,                                  \
                    prec[p], (cast)(val[v]), (cast *)(test1[i]+9), str, \
                    prec[p], (cast)(val[v]), (cast *)(test2[i]+9), str); \
  if(!verif(r, result, test1, test2, 2*L+(!c), 1, 17))                  \
    printf("Tested format string was: \"%s\", %d, %d\n\n", format, prec[p], val[v]); \
  snlength[3] = (size_t)(r[0]); snlength[4] = (size_t)(r[0])+1;         \
  for(j=0;j<5;j++) {                                                    \
    clean(test1, test2, result);                                        \
    for(i=0;i<2;i++) {                                                  \
      r[i] = snprntf[i]( (j==0)?NULL:result[i], snlength[j], format,    \
                         prec[p], (cast)(val[v]), (cast *)(test1[i]+9), str, \
                         prec[p], (cast)(val[v]), (cast *)(test2[i]+9), str); \
      result[i][BUFSIZE-1] = '\0';                                      \
    }                                                                   \
    if(!verif(r, result, test1, test2, 2*L+(!c), (j==4), snlength[j]))  \
      printf("Tested format string was: \"%s\", %d, %d\n\n", format, prec[p], val[v]); \
  }                                                                     \
                                                                        \
                                                                        \
  clean(test1, test2, result);                                          \
  sprintf(format, "|%%%s*.*%s%c| %%%sn %%s |%%%s*.*%s%c| %%%sn %%s",    \
          flags, length[L], conv[c], length[L],                         \
          flags, length[L], conv[c], length[L]);                        \
  for(i=0;i<2;i++)                                                      \
    r[i] = prntf[i](result[i], format,                                  \
                    width[w], prec[p], (cast)(val[v]), (cast *)(test1[i]+9), str, \
                    width[w], prec[p], (cast)(val[v]), (cast *)(test2[i]+9), str); \
  if(!verif(r, result, test1, test2, 2*L+(!c), 1, 17))                  \
    printf("Tested format string was: \"%s\", %d, %d, %d\n\n", format, width[w], prec[p], val[v]); \
  snlength[3] = (size_t)(r[0]); snlength[4] = (size_t)(r[0])+1;         \
  for(j=0;j<5;j++) {                                                    \
    clean(test1, test2, result);                                        \
    for(i=0;i<2;i++) {                                                  \
      r[i] = snprntf[i]( (j==0)?NULL:result[i], snlength[j], format,    \
                         width[w], prec[p], (cast)(val[v]), (cast *)(test1[i]+9), str, \
                         width[w], prec[p], (cast)(val[v]), (cast *)(test2[i]+9), str); \
      result[i][BUFSIZE-1] = '\0';                                      \
    }                                                                   \
    if(!verif(r, result, test1, test2, 2*L+(!c), (j==4), snlength[j]))  \
      printf("Tested format string was: \"%s\", %d, %d, %d\n\n", format, width[w], prec[p], val[v]); \
  }                                                                     \


int main(void) {
  int flag, flag2;
  char flags[6];
  int w;
  int width[4] = {-17, 0, 1, 17};
  int p;
  int prec[4] = {0, -5, 1, 17};
  int c;
  char conv[6] = {'u', 'd','i', 'o', 'x', 'X'};
  int v;
  int val[3] = {-42, 0, 42};
  int L;
  char *length[7] = {"hh", "h", "l", "ll", "j", "z", "t" };
  char *str = "Hello, world!";
  char format[BUFSIZE];
  char test1[2][SIZE];
  char test2[2][SIZE];
  int r[2];
  char result[2][BUFSIZE];
  int (*prntf[2])(char *str, const char *formats, ...);
  prntf[0] = sprintf; prntf[1] = wrapper_sollya_sprintf;
  int (*snprntf[2])(char *str, size_t size, const char *formats, ...);
  snprntf[0] = snprintf; snprntf[1] = wrapper_sollya_snprintf;
  size_t snlength[5] = {0, 0, 1, 42, 42};
  int i, j;
  sollya_obj_t a[2];
  mpfi_t x[2];

  sollya_lib_init();

  /* Format : % [[attr1] ... [attrn]] [width] [.prec] [length] conv
     with
       attr in #|0|+|-|' '
       width an integer (or * and an integer argument)
       prec an integer (or * and an integer argument)
        length in hh|h|l|ll|L|q|j|z|t
       conv in d|i|o|u|x|X|e|E|f|F|g|G|a|A|c|s|p|n
  */
  for(flag=0;flag<32;flag++) {
    sprintf(flags, "%s%s%s%s%s", (flag & 1)?"-":"", (flag & 2)?"#":"", (flag & 4)?"+":"", (flag & 8)?" ":"", (flag & 16)?"0":"");
    for(w=0;w<4;w++) {
      for(p=0;p<4;p++) {
        for(v=0; v<3; v++) {
          for(c=0; c<6; c++) {
            for(L=0;L< (7-(!c)); L++) {  /* The trick 7-(!c) ensures that L ranges from 0 to 6 when c!=0
                                            i.e., length can be any of 'h', 'hh', 'l', 'll', 'j', 'z,' or 't' when the conversion is unsigned,
                                            but ranges from 0 to 5 when c==0,
                                            i.e. length 't' is excluded when the conversion is 'u'
                                         */
              /* The trick 2*L+(!c) permits us to consider 0 for hh, 1 for hhu,    2 for h, 3 for hu, etc. */
              switch(2*L+(!c)) {
              case 0: DO_TESTS(hh_t) break;
              case 1: DO_TESTS(hhu_t) break;
              case 2: DO_TESTS(h_t) break;
              case 3: DO_TESTS(hu_t) break;
              case 4: DO_TESTS(l_t) break;
              case 5: DO_TESTS(lu_t) break;
              case 6: DO_TESTS(ll_t) break;
              case 7: DO_TESTS(llu_t) break;
              case 8: DO_TESTS(j_t) break;
              case 9: DO_TESTS(ju_t) break;
              case 10: DO_TESTS(z_t) break;
              case 11: DO_TESTS(zu_t) break;
              default: DO_TESTS(t_t) break;
              }
            }
          }
        }
      }
    }
  }
  printf("Performed %d tests.\n", counter);

  a[0] = SOLLYA_CONST(33);
  for(w=0;w<4;w++) {
    for(p=0;p<4;p++) {
      for(i=0;i<2;i++) {
        /* format where the only possible flag character is '-'.
           Since it is the only flag character accepted by Sollya, this serves as a reference.
           Other formats, made with other possible flag characters must behave exactly the same.
        */
        if (p!=1) {
          sprintf(flags, (i==0)?"":"-");
          sprintf(format, "|%%%s%d.%.0db| %%ln %%s |%%%s%d.%.0db| %%ln %%s", flags, width[w], prec[p], flags, width[w], prec[p]);
          clean_simple_tab(test1[0]); clean_simple_tab(test2[0]); clean_buffer(result[0]);
          r[0] = sollya_lib_sprintf(result[0], format, a[0], (long int *)(test1[0]+9), str, a[0], (long int *)(test2[0]+9), str);
          sollya_lib_printf("%s  [Given by format \"%s\", %b]\n", result[0], format, a[0]);
          for(flag=0;flag<16;flag++) {
            flag2 = (2*flag+i);
            sprintf(flags, "%s%s%s%s%s", (flag2 & 1)?"-":"", (flag2 & 2)?"#":"", (flag2 & 4)?"+":"", (flag2 & 8)?" ":"", (flag2 & 16)?"0":"");
            sprintf(format, "|%%%s%d.%.0db| %%ln %%s |%%%s%d.%.0db| %%ln %%s", flags, width[w], prec[p], flags, width[w], prec[p]);
            clean_simple_tab(test1[1]); clean_simple_tab(test2[1]); clean_buffer(result[1]);
            r[1] = sollya_lib_sprintf(result[1], format, a[0], (long int *)(test1[1]+9), str, a[0], (long int *)(test2[1]+9), str);
            /* 4 is for long int conversion in %n */
            if(!verif(r, result, test1, test2, 4, 1, 17))
              sollya_lib_printf("Flag characters are not ignored as they should be. Format string was: \"%s\", %b\n\n", format, a[0]);
          }


          sprintf(flags, (i==0)?"":"-");
          sprintf(format, "|%%%s*.%.0db| %%ln %%s |%%%s*.%.0db| %%ln %%s", flags, prec[p], flags, prec[p]);
          clean_simple_tab(test1[0]); clean_simple_tab(test2[0]); clean_buffer(result[0]);
          r[0] = sollya_lib_sprintf(result[0], format, width[w], a[0], (long int *)(test1[0]+9), str, width[w], a[0], (long int *)(test2[0]+9), str);
          sollya_lib_printf("%s  [Given by format \"%s\", %d, %b]\n", result[0], format, width[w], a[0]);
          for(flag=0;flag<16;flag++) {
            flag2 = (2*flag+i);
            sprintf(flags, "%s%s%s%s%s", (flag2 & 1)?"-":"", (flag2 & 2)?"#":"", (flag2 & 4)?"+":"", (flag2 & 8)?" ":"", (flag2 & 16)?"0":"");
            sprintf(format, "|%%%s*.%.0db| %%ln %%s |%%%s*.%.0db| %%ln %%s", flags, prec[p], flags, prec[p]);
            clean_simple_tab(test1[1]); clean_simple_tab(test2[1]); clean_buffer(result[1]);
            r[1] = sollya_lib_sprintf(result[1], format, width[w], a[0], (long int *)(test1[1]+9), str, width[w], a[0], (long int *)(test2[1]+9), str);
            /* 4 is for long int conversion in %n */
            if(!verif(r, result, test1, test2, 4, 1, 17))
              sollya_lib_printf("Flag characters are not ignored as they should be. Format string was: \"%s\", %b\n\n", format, a[0]);
          }
        }


        sprintf(flags, (i==0)?"":"-");
        sprintf(format, "|%%%s%d.*b| %%ln %%s |%%%s%d.*b| %%ln %%s", flags, width[w], flags, width[w]);
        clean_simple_tab(test1[0]); clean_simple_tab(test2[0]); clean_buffer(result[0]);
        r[0] = sollya_lib_sprintf(result[0], format, prec[p], a[0], (long int *)(test1[0]+9), str, prec[p], a[0], (long int *)(test2[0]+9), str);
        sollya_lib_printf("%s  [Given by format \"%s\", %d, %b]\n", result[0], format, prec[p], a[0]);
        for(flag=0;flag<16;flag++) {
          flag2 = (2*flag+i);
          sprintf(flags, "%s%s%s%s%s", (flag2 & 1)?"-":"", (flag2 & 2)?"#":"", (flag2 & 4)?"+":"", (flag2 & 8)?" ":"", (flag2 & 16)?"0":"");
          sprintf(format, "|%%%s%d.*b| %%ln %%s |%%%s%d.*b| %%ln %%s", flags, width[w], flags, width[w]);
          clean_simple_tab(test1[1]); clean_simple_tab(test2[1]); clean_buffer(result[1]);
          r[1] = sollya_lib_sprintf(result[1], format, prec[p], a[0], (long int *)(test1[1]+9), str, prec[p], a[0], (long int *)(test2[1]+9), str);
          /* 4 is for long int conversion in %n */
          if(!verif(r, result, test1, test2, 4, 1, 17))
            sollya_lib_printf("Flag characters are not ignored as they should be. Format string was: \"%s\", %b\n\n", format, a[0]);
        }


        sprintf(flags, (i==0)?"":"-");
        sprintf(format, "|%%%s*.*b| %%ln %%s |%%%s*.*b| %%ln %%s", flags, flags);
        clean_simple_tab(test1[0]); clean_simple_tab(test2[0]); clean_buffer(result[0]);
        r[0] = sollya_lib_sprintf(result[0], format, width[w], prec[p], a[0], (long int *)(test1[0]+9), str, width[w], prec[p], a[0], (long int *)(test2[0]+9), str);
        sollya_lib_printf("%s  [Given by format \"%s\", %d, %d, %b]\n", result[0], format, width[w], prec[p], a[0]);
        for(flag=0;flag<16;flag++) {
          flag2 = (2*flag+i);
          sprintf(flags, "%s%s%s%s%s", (flag2 & 1)?"-":"", (flag2 & 2)?"#":"", (flag2 & 4)?"+":"", (flag2 & 8)?" ":"", (flag2 & 16)?"0":"");
          sprintf(format, "|%%%s*.*b| %%ln %%s |%%%s*.*b| %%ln %%s", flags, flags);
          clean_simple_tab(test1[1]); clean_simple_tab(test2[1]); clean_buffer(result[1]);
          r[1] = sollya_lib_sprintf(result[1], format, width[w], prec[p], a[0], (long int *)(test1[1]+9), str, width[w], prec[p], a[0], (long int *)(test2[1]+9), str);
          /* 4 is for long int conversion in %n */
          if(!verif(r, result, test1, test2, 4, 1, 17))
            sollya_lib_printf("Flag characters are not ignored as they should be. Format string was: \"%s\", %b\n\n", format, a[0]);
        }
      }
    }
  }


  clean(test1, test2, result);
  r[0] = sollya_lib_snprintf(result[0], 8, "Hello |%-12d| %n %d", 17, (int *)(test1[0]+9), 42);
  printf("%s\n", result[0]);

  clean(test1, test2, result);
  r[0] = sollya_lib_snprintf(result[0], 9, "Hello |%-12d| %n %d", 17, (int *)(test1[0]+9), 42);
  printf("%s\n", result[0]);

  clean(test1, test2, result);
  r[0] = sollya_lib_snprintf(result[0], 10, "Hello |%-12d| %n %d", 17, (int *)(test1[0]+9), 42);
  printf("%s\n", result[0]);

  clean(test1, test2, result);
  r[0] = sollya_lib_snprintf(result[0], 23, "Hello |%-12d| %n %d", 17, (int *)(test1[0]+9), 42);
  printf("%s\n", result[0]);

  clean(test1, test2, result);
  r[0] = sollya_lib_snprintf(result[0], 24, "Hello |%-12d| %n %d", 17, (int *)(test1[0]+9), 42);
  printf("%s\n", result[0]);

  clean(test1, test2, result);
  r[0] = sollya_lib_snprintf(result[0], 25, "Hello |%-12d| %n %d", 17, (int *)(test1[0]+9), 42);
  printf("%s\n", result[0]);

  a[0] = SOLLYA_CONST(17);
  a[1] = SOLLYA_CONST(42);
  clean(test1, test2, result);
  r[0] = sollya_lib_snprintf(result[0], 8, "Hello |%-12b| %n %b", a[0], (int *)(test1[0]+9), a[1]);
  printf("%s\n", result[0]);

  clean(test1, test2, result);
  r[0] = sollya_lib_snprintf(result[0], 9, "Hello |%-12b| %n %b", a[0], (int *)(test1[0]+9), a[1]);
  printf("%s\n", result[0]);

  clean(test1, test2, result);
  r[0] = sollya_lib_snprintf(result[0], 10, "Hello |%-12b| %n %b", a[0], (int *)(test1[0]+9), a[1]);
  printf("%s\n", result[0]);

  clean(test1, test2, result);
  r[0] = sollya_lib_snprintf(result[0], 23, "Hello |%-12b| %n %b", a[0], (int *)(test1[0]+9), a[1]);
  printf("%s\n", result[0]);

  clean(test1, test2, result);
  r[0] = sollya_lib_snprintf(result[0], 24, "Hello |%-12b| %n %b", a[0], (int *)(test1[0]+9), a[1]);
  printf("%s\n", result[0]);

  clean(test1, test2, result);
  r[0] = sollya_lib_snprintf(result[0], 25, "Hello |%-12b| %n %b", a[0], (int *)(test1[0]+9), a[1]);
  printf("%s\n", result[0]);


  mpfi_init2(x[0], 53);
  mpfi_init2(x[1], 53);
  mpfi_set_ui(x[0], 17);
  mpfi_set_ui(x[1], 42);
  clean(test1, test2, result);
  r[0] = sollya_lib_snprintf(result[0], 8, "Hello |%-12w| %n %w", x[0], (int *)(test1[0]+9), x[1]);
  printf("%s\n", result[0]);

  clean(test1, test2, result);
  r[0] = sollya_lib_snprintf(result[0], 9, "Hello |%-12w| %n %w", x[0], (int *)(test1[0]+9), x[1]);
  printf("%s\n", result[0]);

  clean(test1, test2, result);
  r[0] = sollya_lib_snprintf(result[0], 10, "Hello |%-12w| %n %w", x[0], (int *)(test1[0]+9), x[1]);
  printf("%s\n", result[0]);

  clean(test1, test2, result);
  r[0] = sollya_lib_snprintf(result[0], 23, "Hello |%-12w| %n %w", x[0], (int *)(test1[0]+9), x[1]);
  printf("%s\n", result[0]);

  clean(test1, test2, result);
  r[0] = sollya_lib_snprintf(result[0], 24, "Hello |%-12w| %n %w", x[0], (int *)(test1[0]+9), x[1]);
  printf("%s\n", result[0]);

  clean(test1, test2, result);
  r[0] = sollya_lib_snprintf(result[0], 25, "Hello |%-12w| %n %w", x[0], (int *)(test1[0]+9), x[1]);
  printf("%s\n", result[0]);

  sollya_lib_printf("%b (should be NULL)\n", NULL);
  sollya_lib_printf("%% (should display the character percent)\n", NULL);

  sollya_lib_close();
  return 0;
}
