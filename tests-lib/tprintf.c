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

void clean_simple_tab(char tab[2][SIZE]) {
  int i,j;
  for(i=0; i<2; i++) 
    for(j=0;j<SIZE;j++) tab[i][j] = 5;
}
void clean(char tab1[2][SIZE], char tab2[2][SIZE], char res[2][BUFSIZE]) {
  int i,j;

  clean_simple_tab(tab1);
  clean_simple_tab(tab2);

  for(i=0; i<2; i++) 
    for(j=0;j<BUFSIZE;j++) res[i][j]='\0';

}

int verif(int r[2], char result[2][BUFSIZE], char test1[2][SIZE], char test2[2][SIZE], int length) {
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

  if (counter[0] != r[0]) { test = 0; printf("sprintf returned %d but %d characters have been written. ", r[0], counter[0]); }
  if (counter[1] != r[1]) { test = 0; printf("sollya_lib_sprintf returned %d but %d characters have been written. ", r[1], counter[1]); }
  if (r[0] != r[1]) { test = 0; printf("sprintf returned %d and sollya_lib_printf returned %d. ", r[0], r[1]); }

  for(i=0;i<SIZE;i++) {
    if(test1[0][i] != test1[1][i]) { 
      test = 0;
      printf("The first %%n does not lead to the same value with both implementation. ");
      break;
    }
  }

  clean_simple_tab(test3);
  ptr = strstr(result[0], " Hello");
  if (ptr==NULL) {
    test = 0;
    printf("The string returned by sprintf does not contain ' Hello'. ");
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
      printf("The first %%n of sprintf did not return the expected value (%d). ", n);
      break;
    }
  }

  for(i=0;i<SIZE;i++) {
    if(test2[0][i] != test2[1][i]) { 
      test = 0;
      printf("The second %%n does not lead to the same value with both implementation. ");
      break;
    }
  }

  ptr = strstr(result[0]+n+1, " Hello");
  if (ptr==NULL) {
    test = 0;
    printf("The string returned by sprintf does not contain two instances of ' Hello'. ");
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
      printf("The second %%n of sprintf did not return the expected value (%d). ", n);
      break;
    }
  }

  if(strcmp(result[0], result[1])) {
    test = 0;
    printf("Both implementations did not return the same string. ");
  }

  if(strchr(result[0], '%')) {
    test = 0;
    printf("The format string has not been understood by sprintf. ");
  }

  if (!test) {
    printf("Below: first the string returned by sprintf, then the string returned by sollya_lib_sprintf.\n");
    printf("%s [returned value: %d]\n", result[0], r[0]);
    printf("%s [returned value: %d]\n", result[1], r[1]);

    for(i=0;i<SIZE-1;i++) printf("%hhu-", test1[0][i]);
    printf("%hhu. [First %%n returned by sprintf]\n", test1[0][SIZE-1]);

    for(i=0;i<SIZE-1;i++) printf("%hhu-", test1[1][i]);
    printf("%hhu. [First %%n returned by sollya_lib_sprintf]\n", test1[1][SIZE-1]);

    for(i=0;i<SIZE-1;i++) printf("%hhu-", test3[0][i]);
    printf("%hhu. [Expected first %%n returned by sprintf]\n", test3[0][SIZE-1]);

    for(i=0;i<SIZE-1;i++) printf("%hhu-", test2[0][i]);
    printf("%hhu. [Second %%n returned by sprintf]\n", test2[0][SIZE-1]);

    for(i=0;i<SIZE-1;i++) printf("%hhu-", test2[1][i]);
    printf("%hhu. [Second %%n returned by sollya_lib_sprintf]\n", test2[1][SIZE-1]);

    for(i=0;i<SIZE-1;i++) printf("%hhu-", test3[1][i]);
    printf("%hhu. [Expected second %%n returned by sprintf]\n", test3[1][SIZE-1]);
  }
  
  return test;
}

#define DO_TESTS(cast)                                                  \
  if (p!=1) {                                                           \
    clean(test1, test2, result);                                        \
    sprintf(format, "|%%%s%d.%.0d%s%c| %%%sn %%s |%%%s%d.%.0d%s%c| %%%sn %%s", \
            flags, width[w], prec[p], length[L], conv[c], length[L],    \
            flags, width[w], prec[p], length[L], conv[c], length[L]);   \
    for(i=0;i<2;i++) r[i] = prntf[i](result[i], format,  (cast)(val[v]), (cast *)(test1[i]+9), str, (cast)(val[v]), (cast *)(test2[i]+9), str); \
    if(!verif(r, result, test1, test2, 2*L+(!c)))  printf("Tested format string was: \"%s\", %d\n\n", format, val[v]); \
                                                                        \
    clean(test1, test2, result);                                        \
    sprintf(format, "|%%%s*.%.0d%s%c| %%%sn %%s |%%%s*.%.0d%s%c| %%%sn %%s", flags, prec[p], length[L], conv[c], length[L], flags, prec[p], length[L], conv[c], length[L]); \
    for(i=0;i<2;i++) r[i] = prntf[i](result[i], format, width[w], (cast)(val[v]), (cast *)(test1[i] + 9), str, width[w], (cast)(val[v]), (cast *)(test2[i]+9), str); \
    if(!verif(r, result, test1, test2, 2*L+(!c)))  printf("Tested format string was: \"%s\", %d, %d\n\n", format, width[w], val[v]); \
  }                                                                     \
                                                                        \
  clean(test1, test2, result);                                          \
  sprintf(format, "|%%%s%d.*%s%c| %%%sn %%s |%%%s%d.*%s%c| %%%sn %%s", flags, width[w], length[L], conv[c], length[L], flags, width[w], length[L], conv[c], length[L]); \
  for(i=0;i<2;i++) r[i] = prntf[i](result[i], format, prec[p], (cast)(val[v]), (cast *)(test1[i]+9), str, prec[p], (cast)(val[v]), (cast *)(test2[i]+9), str); \
  if(!verif(r, result, test1, test2, 2*L+(!c)))  printf("Tested format string was: \"%s\", %d, %d\n\n", format, prec[p], val[v]); \
                                                                        \
  clean(test1, test2, result);                                          \
  sprintf(format, "|%%%s*.*%s%c| %%%sn %%s |%%%s*.*%s%c| %%%sn %%s", flags, length[L], conv[c], length[L], flags, length[L], conv[c], length[L]); \
  for(i=0;i<2;i++) r[i] = prntf[i](result[i], format, width[w], prec[p], (cast)(val[v]), (cast *)(test1[i]+9), str, width[w], prec[p], (cast)(val[v]), (cast *)(test2[i]+9), str); \
  if(!verif(r, result, test1, test2, 2*L+(!c)))  printf("Tested format string was: \"%s\", %d, %d, %d\n\n", format, width[w], prec[p], val[v]);



int main(void) {
  int flag; char flags[6];
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
  int i;

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
  sollya_lib_close();
  return 0;
}
