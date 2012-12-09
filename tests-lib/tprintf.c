#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <stdint.h>
#include <malloc.h>
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

int verif(int r[2], char result[2][BUFSIZE], char test1[2][SIZE], char test2[2][SIZE]) {
  int test = 1;
  int i;
  int counter[2];
  char test3[2][SIZE];
  char *ptr;
  int n;

  for(i=0;i<2;i++) {
    counter[i] = strnlen(result[i], BUFSIZE);
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
    *((hh_t *)((test3[0])+9)) = (hh_t)n;
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
    *((hh_t *)((test3[1])+9)) = (hh_t)n;
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

int main(void) {
  int flag; char flags[6];
  int w, width;
  int p, prec;
  int c; char conv;
  int v, val;
  char *str = "Hello, world!";
  char format[BUFSIZE];
  char test1[2][SIZE];
  char test2[2][SIZE];
  int r[2];
  char result[2][BUFSIZE];
  int (*prntf[2])(char *str, const char *format, ...);
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
      width = (w==0)?(-17):( (w==1)?0: ( (w==2)?1:17 ) );
      for(p=0;p<4;p++) {
        prec = (p==0)?(0):( (p==1)?(-5): ( (p==2)?1:17 ) );
        for(v=0; v<3; v++) {
          val = (v==0)?(-42):( (v==1)?0:42 );
          for(c=0; c<5; c++) {
            conv = (c==0)?'d':( (c==1)?'i':( (c==2)?'o':( (c==3)?'x':'X' ) ) );
            
            if (p!=1) {
              clean(test1, test2, result);
              sprintf(format, "|%%%s%d.%.0dhh%c| %%hhn %%s |%%%s%d.%.0dhh%c| %%hhn %%s", flags, width, prec, conv, flags, width, prec, conv);
              for(i=0;i<2;i++) r[i] = prntf[i](result[i], format, (hh_t)(val), (hh_t *)(test1[i]+9), str, (hh_t)(val), (hh_t *)(test2[i]+9), str);
              if(!verif(r, result, test1, test2))  printf("Tested format string was: \"%s\", %d\n\n", format, val);

              clean(test1, test2, result);
              sprintf(format, "|%%%s*.%.0dhh%c| %%hhn %%s |%%%s*.%.0dhh%c| %%hhn %%s", flags, prec, conv, flags, prec, conv);
              for(i=0;i<2;i++) r[i] = prntf[i](result[i], format, width, (hh_t)(val), (hh_t *)(test1[i] + 9), str, width, (hh_t)(val), (hh_t *)(test2[i]+9), str);
              if(!verif(r, result, test1, test2))  printf("Tested format string was: \"%s\", %d, %d\n\n", format, width, val);
            }

            clean(test1, test2, result);
            sprintf(format, "|%%%s%d.*hh%c| %%hhn %%s |%%%s%d.*hh%c| %%hhn %%s", flags, width, conv, flags, width, conv);
            for(i=0;i<2;i++) r[i] = prntf[i](result[i], format, prec, (hh_t)(val), (hh_t *)(test1[i]+9), str, prec, (hh_t)(val), (hh_t *)(test2[i]+9), str);
              if(!verif(r, result, test1, test2))  printf("Tested format string was: \"%s\", %d, %d\n\n", format, prec, val);

            clean(test1, test2, result);
            sprintf(format, "|%%%s*.*hh%c| %%hhn %%s |%%%s*.*hh%c| %%hhn %%s", flags, conv, flags, conv);
            for(i=0;i<2;i++) r[i] = prntf[i](result[i], format, width, prec, (hh_t)(val), (hh_t *)(test1[i]+9), str, width, prec, (hh_t)(val), (hh_t *)(test2[i]+9), str);
            if(!verif(r, result, test1, test2))  printf("Tested format string was: \"%s\", %d, %d\n\n", format, width, prec, val);
          }
        }
      }
    }
  }

  printf("Performed %d tests.\n", counter);
  sollya_lib_close();
  return 0;
}
