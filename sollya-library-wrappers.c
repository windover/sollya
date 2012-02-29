/*

  Copyright 2011-2012 by

  Laboratoire d'Informatique de Paris 6, equipe PEQUAN,
  UPMC Universite Paris 06 - CNRS - UMR 7606 - LIP6, Paris, France,

  Contributors Ch. Lauter

  christoph.lauter@ens-lyon.org

  This software is a computer program whose purpose is to provide an
  environment for safe floating-point code development. It is
  particularily targeted to the automatized implementation of
  mathematical floating-point libraries (libm). Amongst other features,
  it offers a certified infinity norm, an automatic polynomial
  implementer and a fast Remez algorithm.

  This software is governed by the CeCILL-C license under French law and
  abiding by the rules of distribution of free software.  You can  use,
  modify and/ or redistribute the software under the terms of the CeCILL-C
  license as circulated by CEA, CNRS and INRIA at the following URL
  "http://www.cecill.info".

  As a counterpart to the access to the source code and  rights to copy,
  modify and redistribute granted by the license, users are provided only
  with a limited warranty  and the software's author,  the holder of the
  economic rights,  and the successive licensors  have only  limited
  liability.

  In this respect, the user's attention is drawn to the risks associated
  with loading,  using,  modifying and/or developing or reproducing the
  software by the user in light of its specific status of free software,
  that may mean  that it is complicated to manipulate,  and  that  also
  herefore means  that it is reserved for developers  and  experienced
  professionals having in-depth computer knowledge. Users are therefore
  encouraged to load and test the software's suitability as regards their
  requirements in conditions enabling the security of their systems and/or
  data to be ensured and,  more generally, to use and operate it in the
  same conditions as regards security.

  The fact that you are presently reading this means that you have had
  knowledge of the CeCILL-C license and that you accept its terms.

  This program is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

*/

#include <stdarg.h>
#include <gmp.h>
#include <mpfr.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mpfi.h>
#include "expression.h"
#include "execute.h"
#include "chain.h"
#include "assignment.h"
#include "mpfi-compat.h"
#include "sollya-library-wrappers.h"

/* Some helper macros */

#define MAKE_THINGLIST_DECLS(__thinglist)       \
  va_list varlist;                              \
  chain *__thinglist, *curr;                    \
  node *elem

#define MAKE_THINGLIST_DECLS_FROM_VA_LIST(__thinglist)  \
  chain *__thinglist, *curr;                            \
  node *elem

#define MAKE_THINGLIST_FROM_VARIADIC(__last)            \
  va_start(varlist,(__last));                           \
  thinglist = (chain *) safeMalloc(sizeof(chain));      \
  thinglist->value = copyThing((__last));               \
  thinglist->next = NULL;                               \
  curr = thinglist;                                     \
  while ((elem = va_arg(varlist,node *)) != NULL) {     \
    curr->next = (chain *) safeMalloc(sizeof(chain));   \
    curr = curr->next;                                  \
    curr->value = copyThing(elem);                      \
    curr->next = NULL;                                  \
  }                                                     \
  va_end(varlist)

#define MAKE_THINGLIST_FROM_VA_LIST(__last, __varlist)  \
  thinglist = (chain *) safeMalloc(sizeof(chain));      \
  thinglist->value = copyThing((__last));               \
  thinglist->next = NULL;                               \
  curr = thinglist;                                     \
  while ((elem = va_arg((__varlist),node *)) != NULL) { \
    curr->next = (chain *) safeMalloc(sizeof(chain));   \
    curr = curr->next;                                  \
    curr->value = copyThing(elem);                      \
    curr->next = NULL;                                  \
  }                                                     \
  (void) 1

/* Actual wrapper functions */

int sollya_lib_init_with_custom_memory_functions(void *(*myMalloc)(size_t),
						 void *(*myCalloc)(size_t, size_t),
						 void *(*myRealloc)(void *, size_t),
						 void (*myFree)(void*),
						 void *(*myReallocWithSize)(void *, size_t, size_t),
						 void (*myFreeWithSize)(void *, size_t)) {
  return initializeLibraryMode(myMalloc, myCalloc, myRealloc, myFree, myReallocWithSize, myFreeWithSize);
}

int sollya_lib_init() {
  return sollya_lib_init_with_custom_memory_functions(NULL, NULL, NULL, NULL, NULL, NULL);
}

int sollya_lib_close() {
  return finalizeLibraryMode();
}

int sollya_lib_install_msg_callback(int (*callback_func) (int)) {
  return installMessageCallback(callback_func);
}

int sollya_lib_uninstall_msg_callback() {
  return uninstallMessageCallback();
}

int (*sollya_lib_get_msg_callback())(int) {
  return getMessageCallback();
}

char *sollya_lib_msg_number_to_text(int msgNum) {
  return messageNumberToText(msgNum);
}

int sollya_lib_printf(const char *format, ...) {
  va_list varlist;
  int res;

  va_start(varlist,format);

  res = sollyaVfprintf(stdout,format,varlist);

  va_end(varlist);

  return res;
}

int sollya_lib_v_printf(const char *format, va_list varlist) {
  int res;

  res = sollyaVfprintf(stdout,format,varlist);

  return res;
}

int sollya_lib_fprintf(FILE *fd, const char *format, ...) {
  va_list varlist;
  int res;

  va_start(varlist,format);

  res = sollyaVfprintf(fd,format,varlist);

  va_end(varlist);

  return res;
}

int sollya_lib_v_fprintf(FILE *fd, const char *format, va_list varlist) {
  int res;

  res = sollyaVfprintf(fd,format,varlist);

  return res;
}

void sollya_lib_clear_obj(sollya_obj_t obj1) {
  freeThing(obj1);
}

void sollya_lib_free(void *ptr) {
  safeFree(ptr);
}

sollya_obj_t sollya_lib_copy_obj(sollya_obj_t obj1) {
  return copyThing(obj1);
}

int sollya_lib_cmp_objs_structurally(sollya_obj_t obj1, sollya_obj_t obj2) {
  return isEqualThing(obj1, obj2);
}

void sollya_lib_name_free_variable(const char *str) {
  if (variablename != NULL) {
    safeFree(variablename);
    variablename = NULL;
  }
  variablename = (char *) safeCalloc(strlen(str) + 1, sizeof(char));
  strcpy(variablename, str);
}

char *sollya_lib_get_free_variable_name() {
  char unnamed[] = "_x_";
  char *staticName, *res;

  staticName = unnamed;
  if (variablename != NULL) staticName = variablename;
  res = (char *) safeCalloc(strlen(staticName) + 1, sizeof(char));
  strcpy(res,staticName);

  return res;
}

void sollya_lib_plot(sollya_obj_t obj1, sollya_obj_t obj2, ...) {
  node *thingToExecute;
  MAKE_THINGLIST_DECLS(thinglist);
  MAKE_THINGLIST_FROM_VARIADIC(obj2);
  thingToExecute = makePlot(addElement(thinglist, copyThing(obj1)));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_v_plot(sollya_obj_t obj1, sollya_obj_t obj2, va_list varlist) {
  node *thingToExecute;
  MAKE_THINGLIST_DECLS_FROM_VA_LIST(thinglist);
  MAKE_THINGLIST_FROM_VA_LIST(obj2,varlist);
  thingToExecute = makePlot(addElement(thinglist, copyThing(obj1)));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_printdouble(sollya_obj_t obj1) {
  node *thingToExecute;
  thingToExecute = makePrintHexa(copyThing(obj1));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_printsingle(sollya_obj_t obj1) {
  node *thingToExecute;
  thingToExecute = makePrintFloat(copyThing(obj1));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_printexpansion(sollya_obj_t obj1) {
  node *thingToExecute;
  thingToExecute = makePrintExpansion(copyThing(obj1));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_implementconst(sollya_obj_t obj1, ...) {
  node *thingToExecute;
  MAKE_THINGLIST_DECLS(thinglist);
  MAKE_THINGLIST_FROM_VARIADIC(obj1);
  thingToExecute = makeImplementConst(thinglist);
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_v_implementconst(sollya_obj_t obj1, va_list varlist) {
  node *thingToExecute;
  MAKE_THINGLIST_DECLS_FROM_VA_LIST(thinglist);
  MAKE_THINGLIST_FROM_VA_LIST(obj1,varlist);
  thingToExecute = makeImplementConst(thinglist);
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_bashexecute(sollya_obj_t obj1) {
  node *thingToExecute;
  thingToExecute = makeBashExecute(copyThing(obj1));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_externalplot(sollya_obj_t obj1, sollya_obj_t obj2, sollya_obj_t obj3, sollya_obj_t obj4, sollya_obj_t obj5, ...) {
  node *thingToExecute;
  MAKE_THINGLIST_DECLS(thinglist);
  MAKE_THINGLIST_FROM_VARIADIC(obj5);
  thingToExecute = makeExternalPlot(addElement(addElement(addElement(addElement(thinglist, copyThing(obj4)),copyThing(obj3)),copyThing(obj2)),copyThing(obj1)));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_v_externalplot(sollya_obj_t obj1, sollya_obj_t obj2, sollya_obj_t obj3, sollya_obj_t obj4, sollya_obj_t obj5, va_list varlist) {
  node *thingToExecute;
  MAKE_THINGLIST_DECLS_FROM_VA_LIST(thinglist);
  MAKE_THINGLIST_FROM_VA_LIST(obj5,varlist);
  thingToExecute = makeExternalPlot(addElement(addElement(addElement(addElement(thinglist, copyThing(obj4)),copyThing(obj3)),copyThing(obj2)),copyThing(obj1)));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_asciiplot(sollya_obj_t obj1, sollya_obj_t obj2) {
  node *thingToExecute;
  thingToExecute = makeAsciiPlot(copyThing(obj1),copyThing(obj2));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_printxml(sollya_obj_t obj1) {
  node *thingToExecute;
  thingToExecute = makePrintXml(copyThing(obj1));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_printxml_newfile(sollya_obj_t obj1, sollya_obj_t obj2) {
  node *thingToExecute;
  thingToExecute = makePrintXmlNewFile(copyThing(obj1),copyThing(obj2));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_printxml_appendfile(sollya_obj_t obj1, sollya_obj_t obj2) {
  node *thingToExecute;
  thingToExecute = makePrintXmlAppendFile(copyThing(obj1),copyThing(obj2));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_worstcase(sollya_obj_t obj1, sollya_obj_t obj2, sollya_obj_t obj3, sollya_obj_t obj4, sollya_obj_t obj5, ...) {
  node *thingToExecute;
  MAKE_THINGLIST_DECLS(thinglist);
  MAKE_THINGLIST_FROM_VARIADIC(obj5);
  thingToExecute = makeWorstCase(addElement(addElement(addElement(addElement(thinglist, copyThing(obj4)),copyThing(obj3)),copyThing(obj2)),copyThing(obj1)));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_v_worstcase(sollya_obj_t obj1, sollya_obj_t obj2, sollya_obj_t obj3, sollya_obj_t obj4, sollya_obj_t obj5, va_list varlist) {
  node *thingToExecute;
  MAKE_THINGLIST_DECLS_FROM_VA_LIST(thinglist);
  MAKE_THINGLIST_FROM_VA_LIST(obj5,varlist);
  thingToExecute = makeWorstCase(addElement(addElement(addElement(addElement(thinglist, copyThing(obj4)),copyThing(obj3)),copyThing(obj2)),copyThing(obj1)));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_autoprint(sollya_obj_t obj1, ...) {
  node *thingToExecute;
  MAKE_THINGLIST_DECLS(thinglist);
  MAKE_THINGLIST_FROM_VARIADIC(obj1);
  thingToExecute = makeAutoprint(thinglist);
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_suppressmessage(sollya_obj_t obj1, ...) {
  node *thingToExecute;
  MAKE_THINGLIST_DECLS(thinglist);
  MAKE_THINGLIST_FROM_VARIADIC(obj1);
  thingToExecute = makeSuppressMessage(thinglist);
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_unsuppressmessage(sollya_obj_t obj1, ...) {
  node *thingToExecute;
  MAKE_THINGLIST_DECLS(thinglist);
  MAKE_THINGLIST_FROM_VARIADIC(obj1);
  thingToExecute = makeUnsuppressMessage(thinglist);
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_v_autoprint(sollya_obj_t obj1, va_list varlist) {
  node *thingToExecute;
  MAKE_THINGLIST_DECLS_FROM_VA_LIST(thinglist);
  MAKE_THINGLIST_FROM_VA_LIST(obj1,varlist);
  thingToExecute = makeAutoprint(thinglist);
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_v_suppressmessage(sollya_obj_t obj1, va_list varlist) {
  node *thingToExecute;
  MAKE_THINGLIST_DECLS_FROM_VA_LIST(thinglist);
  MAKE_THINGLIST_FROM_VA_LIST(obj1,varlist);
  thingToExecute = makeSuppressMessage(thinglist);
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_v_unsuppressmessage(sollya_obj_t obj1, va_list varlist) {
  node *thingToExecute;
  MAKE_THINGLIST_DECLS_FROM_VA_LIST(thinglist);
  MAKE_THINGLIST_FROM_VA_LIST(obj1,varlist);
  thingToExecute = makeUnsuppressMessage(thinglist);
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_set_prec_and_print(sollya_obj_t obj1) {
  node *thingToExecute;
  thingToExecute = makePrecAssign(copyThing(obj1));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_set_points_and_print(sollya_obj_t obj1) {
  node *thingToExecute;
  thingToExecute = makePointsAssign(copyThing(obj1));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_set_diam_and_print(sollya_obj_t obj1) {
  node *thingToExecute;
  thingToExecute = makeDiamAssign(copyThing(obj1));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_set_display_and_print(sollya_obj_t obj1) {
  node *thingToExecute;
  thingToExecute = makeDisplayAssign(copyThing(obj1));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_set_verbosity_and_print(sollya_obj_t obj1) {
  node *thingToExecute;
  thingToExecute = makeVerbosityAssign(copyThing(obj1));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_set_canonical_and_print(sollya_obj_t obj1) {
  node *thingToExecute;
  thingToExecute = makeCanonicalAssign(copyThing(obj1));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_set_autosimplify_and_print(sollya_obj_t obj1) {
  node *thingToExecute;
  thingToExecute = makeAutoSimplifyAssign(copyThing(obj1));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_set_showmessagenumbers_and_print(sollya_obj_t obj1) {
  node *thingToExecute;
  thingToExecute = makeShowMessageNumbersAssign(copyThing(obj1));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_set_taylorrecursions_and_print(sollya_obj_t obj1) {
  node *thingToExecute;
  thingToExecute = makeTaylorRecursAssign(copyThing(obj1));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_set_timing_and_print(sollya_obj_t obj1) {
  node *thingToExecute;
  thingToExecute = makeTimingAssign(copyThing(obj1));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_set_midpointmode_and_print(sollya_obj_t obj1) {
  node *thingToExecute;
  thingToExecute = makeMidpointAssign(copyThing(obj1));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_set_dieonerrormode_and_print(sollya_obj_t obj1) {
  node *thingToExecute;
  thingToExecute = makeDieOnErrorAssign(copyThing(obj1));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_set_rationalmode_and_print(sollya_obj_t obj1) {
  node *thingToExecute;
  thingToExecute = makeRationalModeAssign(copyThing(obj1));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_set_roundingwarnings_and_print(sollya_obj_t obj1) {
  node *thingToExecute;
  thingToExecute = makeSuppressWarningsAssign(copyThing(obj1));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_set_hopitalrecursions_and_print(sollya_obj_t obj1) {
  node *thingToExecute;
  thingToExecute = makeHopitalRecursAssign(copyThing(obj1));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_set_prec(sollya_obj_t obj1) {
  node *thingToExecute;
  thingToExecute = makePrecStillAssign(copyThing(obj1));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_set_points(sollya_obj_t obj1) {
  node *thingToExecute;
  thingToExecute = makePointsStillAssign(copyThing(obj1));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_set_diam(sollya_obj_t obj1) {
  node *thingToExecute;
  thingToExecute = makeDiamStillAssign(copyThing(obj1));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_set_display(sollya_obj_t obj1) {
  node *thingToExecute;
  thingToExecute = makeDisplayStillAssign(copyThing(obj1));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_set_verbosity(sollya_obj_t obj1) {
  node *thingToExecute;
  thingToExecute = makeVerbosityStillAssign(copyThing(obj1));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_set_canonical(sollya_obj_t obj1) {
  node *thingToExecute;
  thingToExecute = makeCanonicalStillAssign(copyThing(obj1));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_set_autosimplify(sollya_obj_t obj1) {
  node *thingToExecute;
  thingToExecute = makeAutoSimplifyStillAssign(copyThing(obj1));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_set_showmessagenumbers(sollya_obj_t obj1) {
  node *thingToExecute;
  thingToExecute = makeShowMessageNumbersStillAssign(copyThing(obj1));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_set_taylorrecursions(sollya_obj_t obj1) {
  node *thingToExecute;
  thingToExecute = makeTaylorRecursStillAssign(copyThing(obj1));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_set_timing(sollya_obj_t obj1) {
  node *thingToExecute;
  thingToExecute = makeTimingStillAssign(copyThing(obj1));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_set_midpointmode(sollya_obj_t obj1) {
  node *thingToExecute;
  thingToExecute = makeMidpointStillAssign(copyThing(obj1));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_set_dieonerrormode(sollya_obj_t obj1) {
  node *thingToExecute;
  thingToExecute = makeDieOnErrorStillAssign(copyThing(obj1));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_set_rationalmode(sollya_obj_t obj1) {
  node *thingToExecute;
  thingToExecute = makeRationalModeStillAssign(copyThing(obj1));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

void sollya_lib_set_roundingwarnings(sollya_obj_t obj1) {
  node *thingToExecute;
  thingToExecute = makeSuppressWarningsStillAssign(copyThing(obj1));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
} 

void sollya_lib_set_hopitalrecursions(sollya_obj_t obj1) {
  node *thingToExecute;
  thingToExecute = makeHopitalRecursStillAssign(copyThing(obj1));
  executeCommand(thingToExecute);
  freeThing(thingToExecute);
}

sollya_obj_t sollya_lib_free_variable() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeVariable();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_and(sollya_obj_t obj1, sollya_obj_t obj2) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeAnd(copyThing(obj1),copyThing(obj2));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_or(sollya_obj_t obj1, sollya_obj_t obj2) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeOr(copyThing(obj1),copyThing(obj2));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_negate(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeNegation(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_cmp_equal(sollya_obj_t obj1, sollya_obj_t obj2) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeCompareEqual(copyThing(obj1),copyThing(obj2));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_cmp_in(sollya_obj_t obj1, sollya_obj_t obj2) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeCompareIn(copyThing(obj1),copyThing(obj2));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_cmp_less(sollya_obj_t obj1, sollya_obj_t obj2) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeCompareLess(copyThing(obj1),copyThing(obj2));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_cmp_greater(sollya_obj_t obj1, sollya_obj_t obj2) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeCompareGreater(copyThing(obj1),copyThing(obj2));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_cmp_less_equal(sollya_obj_t obj1, sollya_obj_t obj2) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeCompareLessEqual(copyThing(obj1),copyThing(obj2));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_cmp_greater_equal(sollya_obj_t obj1, sollya_obj_t obj2) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeCompareGreaterEqual(copyThing(obj1),copyThing(obj2));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_cmp_not_equal(sollya_obj_t obj1, sollya_obj_t obj2) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeCompareNotEqual(copyThing(obj1),copyThing(obj2));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_add(sollya_obj_t obj1, sollya_obj_t obj2) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeAdd(copyThing(obj1),copyThing(obj2));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_sub(sollya_obj_t obj1, sollya_obj_t obj2) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeSub(copyThing(obj1),copyThing(obj2));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_concat(sollya_obj_t obj1, sollya_obj_t obj2) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeConcat(copyThing(obj1),copyThing(obj2));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_append(sollya_obj_t obj1, sollya_obj_t obj2) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeAppend(copyThing(obj1),copyThing(obj2));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_prepend(sollya_obj_t obj1, sollya_obj_t obj2) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makePrepend(copyThing(obj1),copyThing(obj2));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_apply(sollya_obj_t obj1, sollya_obj_t obj2, ...) {
  node *thingToEvaluate, *evaluatedThing;
  MAKE_THINGLIST_DECLS(thinglist);
  MAKE_THINGLIST_FROM_VARIADIC(obj2);
  thingToEvaluate = makeApply(copyThing(obj1),thinglist);
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_v_apply(sollya_obj_t obj1, sollya_obj_t obj2, va_list varlist) {
  node *thingToEvaluate, *evaluatedThing;
  MAKE_THINGLIST_DECLS_FROM_VA_LIST(thinglist);
  MAKE_THINGLIST_FROM_VA_LIST(obj2,varlist);
  thingToEvaluate = makeApply(copyThing(obj1),thinglist);
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_approx(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeEvalConst(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_mul(sollya_obj_t obj1, sollya_obj_t obj2) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeMul(copyThing(obj1),copyThing(obj2));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_div(sollya_obj_t obj1, sollya_obj_t obj2) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeDiv(copyThing(obj1),copyThing(obj2));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_pow(sollya_obj_t obj1, sollya_obj_t obj2) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makePow(copyThing(obj1),copyThing(obj2));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_neg(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeNeg(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_sup(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeDeboundMax(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_mid(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeDeboundMid(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_inf(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeDeboundMin(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_diff(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeDiff(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_simplify(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeSimplify(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_bashevaluate(sollya_obj_t obj1, ...) {
  node *thingToEvaluate, *evaluatedThing;
  MAKE_THINGLIST_DECLS(thinglist);
  MAKE_THINGLIST_FROM_VARIADIC(obj1);
  thingToEvaluate = makeBashevaluate(thinglist);
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_v_bashevaluate(sollya_obj_t obj1, va_list varlist) {
  node *thingToEvaluate, *evaluatedThing;
  MAKE_THINGLIST_DECLS_FROM_VA_LIST(thinglist);
  MAKE_THINGLIST_FROM_VA_LIST(obj1,varlist);
  thingToEvaluate = makeBashevaluate(thinglist);
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_getsuppressedmessages() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeGetSuppressedMessages();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_remez(sollya_obj_t obj1, sollya_obj_t obj2, sollya_obj_t obj3, ...) {
  node *thingToEvaluate, *evaluatedThing;
  MAKE_THINGLIST_DECLS(thinglist);
  MAKE_THINGLIST_FROM_VARIADIC(obj3);
  thingToEvaluate = makeRemez(addElement(addElement(thinglist, copyThing(obj2)),copyThing(obj1)));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_v_remez(sollya_obj_t obj1, sollya_obj_t obj2, sollya_obj_t obj3, va_list varlist) {
  node *thingToEvaluate, *evaluatedThing;
  MAKE_THINGLIST_DECLS_FROM_VA_LIST(thinglist);
  MAKE_THINGLIST_FROM_VA_LIST(obj3,varlist);
  thingToEvaluate = makeRemez(addElement(addElement(thinglist, copyThing(obj2)),copyThing(obj1)));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_min(sollya_obj_t obj1, ...) {
  node *thingToEvaluate, *evaluatedThing;
  MAKE_THINGLIST_DECLS(thinglist);
  MAKE_THINGLIST_FROM_VARIADIC(obj1);
  thingToEvaluate = makeMin(thinglist);
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_v_min(sollya_obj_t obj1, va_list varlist) {
  node *thingToEvaluate, *evaluatedThing;
  MAKE_THINGLIST_DECLS_FROM_VA_LIST(thinglist);
  MAKE_THINGLIST_FROM_VA_LIST(obj1,varlist);
  thingToEvaluate = makeMin(thinglist);
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_max(sollya_obj_t obj1, ...) {
  node *thingToEvaluate, *evaluatedThing;
  MAKE_THINGLIST_DECLS(thinglist);
  MAKE_THINGLIST_FROM_VARIADIC(obj1);
  thingToEvaluate = makeMax(thinglist);
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_v_max(sollya_obj_t obj1, va_list varlist) {
  node *thingToEvaluate, *evaluatedThing;
  MAKE_THINGLIST_DECLS_FROM_VA_LIST(thinglist);
  MAKE_THINGLIST_FROM_VA_LIST(obj1,varlist);
  thingToEvaluate = makeMax(thinglist);
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_fpminimax(sollya_obj_t obj1, sollya_obj_t obj2, sollya_obj_t obj3, sollya_obj_t obj4, ...) {
  node *thingToEvaluate, *evaluatedThing;
  MAKE_THINGLIST_DECLS(thinglist);
  MAKE_THINGLIST_FROM_VARIADIC(obj4);
  thingToEvaluate = makeFPminimax(addElement(addElement(addElement(thinglist, copyThing(obj3)), copyThing(obj2)),copyThing(obj1)));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_v_fpminimax(sollya_obj_t obj1, sollya_obj_t obj2, sollya_obj_t obj3, sollya_obj_t obj4, va_list varlist) {
  node *thingToEvaluate, *evaluatedThing;
  MAKE_THINGLIST_DECLS_FROM_VA_LIST(thinglist);
  MAKE_THINGLIST_FROM_VA_LIST(obj4,varlist);
  thingToEvaluate = makeFPminimax(addElement(addElement(addElement(thinglist, copyThing(obj3)), copyThing(obj2)),copyThing(obj1)));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_horner(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeHorner(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_canonical(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeCanonicalThing(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_expand(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeExpand(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_simplifysafe(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeSimplifySafe(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_taylor(sollya_obj_t obj1, sollya_obj_t obj2, sollya_obj_t obj3) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeTaylor(copyThing(obj1),copyThing(obj2),copyThing(obj3));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_taylorform(sollya_obj_t obj1, sollya_obj_t obj2, sollya_obj_t obj3, ...) {
  node *thingToEvaluate, *evaluatedThing;
  MAKE_THINGLIST_DECLS(thinglist);
  MAKE_THINGLIST_FROM_VARIADIC(obj3);
  thingToEvaluate = makeTaylorform(addElement(addElement(thinglist, copyThing(obj2)),copyThing(obj1)));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_v_taylorform(sollya_obj_t obj1, sollya_obj_t obj2, sollya_obj_t obj3, va_list varlist) {
  node *thingToEvaluate, *evaluatedThing;
  MAKE_THINGLIST_DECLS_FROM_VA_LIST(thinglist);
  MAKE_THINGLIST_FROM_VA_LIST(obj3,varlist);
  thingToEvaluate = makeTaylorform(addElement(addElement(thinglist, copyThing(obj2)),copyThing(obj1)));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_autodiff(sollya_obj_t obj1, sollya_obj_t obj2, sollya_obj_t obj3) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeAutodiff(addElement(addElement(addElement(NULL,copyThing(obj3)),copyThing(obj2)),copyThing(obj1)));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_degree(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeDegree(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_numerator(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeNumerator(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_denominator(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeDenominator(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_substitute(sollya_obj_t obj1, sollya_obj_t obj2) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeSubstitute(copyThing(obj1),copyThing(obj2));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_composepolynomials(sollya_obj_t obj1, sollya_obj_t obj2) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeComposePolynomials(copyThing(obj1),copyThing(obj2));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_coeff(sollya_obj_t obj1, sollya_obj_t obj2) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeCoeff(copyThing(obj1),copyThing(obj2));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_subpoly(sollya_obj_t obj1, sollya_obj_t obj2) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeSubpoly(copyThing(obj1),copyThing(obj2));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_roundcoefficients(sollya_obj_t obj1, sollya_obj_t obj2) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeRoundcoefficients(copyThing(obj1),copyThing(obj2));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_rationalapprox(sollya_obj_t obj1, sollya_obj_t obj2) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeRationalapprox(copyThing(obj1),copyThing(obj2));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_round(sollya_obj_t obj1, sollya_obj_t obj2, sollya_obj_t obj3) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeRoundToFormat(copyThing(obj1),copyThing(obj2),copyThing(obj3));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_evaluate(sollya_obj_t obj1, sollya_obj_t obj2) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeEvaluate(copyThing(obj1),copyThing(obj2));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_parse(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeParse(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_readxml(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeReadXml(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_infnorm(sollya_obj_t obj1, sollya_obj_t obj2, ...) {
  node *thingToEvaluate, *evaluatedThing;
  MAKE_THINGLIST_DECLS(thinglist);
  MAKE_THINGLIST_FROM_VARIADIC(obj2);
  thingToEvaluate = makeInfnorm(addElement(thinglist, copyThing(obj1)));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_v_infnorm(sollya_obj_t obj1, sollya_obj_t obj2, va_list varlist) {
  node *thingToEvaluate, *evaluatedThing;
  MAKE_THINGLIST_DECLS_FROM_VA_LIST(thinglist);
  MAKE_THINGLIST_FROM_VA_LIST(obj2,varlist);
  thingToEvaluate = makeInfnorm(addElement(thinglist, copyThing(obj1)));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_supnorm(sollya_obj_t obj1, sollya_obj_t obj2, sollya_obj_t obj3, sollya_obj_t obj4, sollya_obj_t obj5) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeAutodiff(addElement(addElement(addElement(addElement(addElement(NULL,copyThing(obj5)),copyThing(obj4)),
                                                                  copyThing(obj3)),copyThing(obj2)),copyThing(obj1)));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_findzeros(sollya_obj_t obj1, sollya_obj_t obj2) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeFindZeros(copyThing(obj1),copyThing(obj2));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_dirtyinfnorm(sollya_obj_t obj1, sollya_obj_t obj2) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeDirtyInfnorm(copyThing(obj1),copyThing(obj2));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_numberroots(sollya_obj_t obj1, sollya_obj_t obj2) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeNumberRoots(copyThing(obj1),copyThing(obj2));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_integral(sollya_obj_t obj1, sollya_obj_t obj2) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeIntegral(copyThing(obj1),copyThing(obj2));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_dirtyintegral(sollya_obj_t obj1, sollya_obj_t obj2) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeDirtyIntegral(copyThing(obj1),copyThing(obj2));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_implementpoly(sollya_obj_t obj1, sollya_obj_t obj2, sollya_obj_t obj3, sollya_obj_t obj4, sollya_obj_t obj5, sollya_obj_t obj6, ...) {
  node *thingToEvaluate, *evaluatedThing;
  MAKE_THINGLIST_DECLS(thinglist);
  MAKE_THINGLIST_FROM_VARIADIC(obj6);
  thingToEvaluate = makeImplementPoly(addElement(addElement(addElement(addElement(addElement(thinglist, copyThing(obj5)), copyThing(obj4)),copyThing(obj3)),copyThing(obj2)),copyThing(obj1)));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_v_implementpoly(sollya_obj_t obj1, sollya_obj_t obj2, sollya_obj_t obj3, sollya_obj_t obj4, sollya_obj_t obj5, sollya_obj_t obj6, va_list varlist) {
  node *thingToEvaluate, *evaluatedThing;
  MAKE_THINGLIST_DECLS_FROM_VA_LIST(thinglist);
  MAKE_THINGLIST_FROM_VA_LIST(obj6,varlist);
  thingToEvaluate = makeImplementPoly(addElement(addElement(addElement(addElement(addElement(thinglist, copyThing(obj5)), copyThing(obj4)),copyThing(obj3)),copyThing(obj2)),copyThing(obj1)));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_checkinfnorm(sollya_obj_t obj1, sollya_obj_t obj2, sollya_obj_t obj3) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeCheckInfnorm(copyThing(obj1),copyThing(obj2),copyThing(obj3));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_zerodenominators(sollya_obj_t obj1, sollya_obj_t obj2) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeZeroDenominators(copyThing(obj1),copyThing(obj2));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_searchgal(sollya_obj_t obj1, sollya_obj_t obj2, sollya_obj_t obj3, sollya_obj_t obj4, sollya_obj_t obj5, sollya_obj_t obj6) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeSearchGal(addElement(addElement(addElement(addElement(addElement(addElement(NULL,copyThing(obj6)),copyThing(obj5)),copyThing(obj4)),
								   copyThing(obj3)),copyThing(obj2)),copyThing(obj1)));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_guessdegree(sollya_obj_t obj1, sollya_obj_t obj2, sollya_obj_t obj3, ...) {
  node *thingToEvaluate, *evaluatedThing;
  MAKE_THINGLIST_DECLS(thinglist);
  MAKE_THINGLIST_FROM_VARIADIC(obj3);
  thingToEvaluate = makeGuessDegree(addElement(addElement(thinglist, copyThing(obj2)),copyThing(obj1)));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_v_guessdegree(sollya_obj_t obj1, sollya_obj_t obj2, sollya_obj_t obj3, va_list varlist) {
  node *thingToEvaluate, *evaluatedThing;
  MAKE_THINGLIST_DECLS_FROM_VA_LIST(thinglist);
  MAKE_THINGLIST_FROM_VA_LIST(obj3,varlist);
  thingToEvaluate = makeGuessDegree(addElement(addElement(thinglist, copyThing(obj2)),copyThing(obj1)));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_dirtyfindzeros(sollya_obj_t obj1, sollya_obj_t obj2) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeDirtyFindZeros(copyThing(obj1),copyThing(obj2));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_head(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeHead(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_roundcorrectly(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeRoundCorrectly(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_revert(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeRevert(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_sort(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeSort(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_mantissa(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeMantissa(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_precision(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makePrecision(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_exponent(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeExponent(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_tail(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeTail(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_range(sollya_obj_t obj1, sollya_obj_t obj2) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeRange(copyThing(obj1),copyThing(obj2));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_sqrt(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeSqrt(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_exp(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeExp(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_log(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeLog(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_log2(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeLog2(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_log10(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeLog10(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_sin(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeSin(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_cos(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeCos(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_tan(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeTan(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_asin(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeAsin(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_acos(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeAcos(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_atan(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeAtan(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_sinh(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeSinh(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_cosh(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeCosh(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_tanh(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeTanh(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_asinh(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeAsinh(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_acosh(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeAcosh(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_atanh(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeAtanh(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_abs(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeAbs(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_erf(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeErf(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_erfc(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeErfc(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_log1p(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeLog1p(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_expm1(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeExpm1(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_double(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeDouble(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_single(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeSingle(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_quad(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeQuad(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_halfprecision(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeHalfPrecision(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_double_double(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeDoubledouble(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_triple_double(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeTripledouble(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_doubleextended(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeDoubleextended(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_ceil(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeCeil(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_floor(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeFloor(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_nearestint(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeNearestInt(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_length(sollya_obj_t obj1) {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeLength(copyThing(obj1));
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_get_prec() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makePrecDeref();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_get_points() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makePointsDeref();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_get_diam() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeDiamDeref();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_get_display() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeDisplayDeref();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_get_verbosity() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeVerbosityDeref();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_get_canonical() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeCanonicalDeref();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_get_autosimplify() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeAutoSimplifyDeref();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_get_showmessagenumbers() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeShowMessageNumbersDeref();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_get_taylorrecursions() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeTaylorRecursDeref();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_get_timing() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeTimingDeref();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_get_midpointmode() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeMidpointDeref();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_get_dieonerrormode() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeDieOnErrorDeref();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_get_rationalmode() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeRationalModeDeref();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_get_roundingwarnings() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeSuppressWarningsDeref();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_get_hopitalrecursions() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeHopitalRecursDeref();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_on() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeOn();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_off() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeOff();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_dyadic() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeDyadic();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_powers() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makePowers();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_binary() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeBinaryThing();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_hexadecimal() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeHexadecimalThing();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_file() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeFile();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_postscript() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makePostscript();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_postscriptfile() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makePostscriptFile();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_perturb() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makePerturb();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_round_down() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeRoundDown();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_round_up() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeRoundUp();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_round_towards_zero() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeRoundToZero();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_round_to_nearest() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeRoundToNearest();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_honorcoeffprec() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeHonorCoeff();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_true() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeTrue();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_false() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeFalse();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_void() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeUnit();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_default() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeDefault();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_decimal() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeDecimal();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_absolute() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeAbsolute();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_relative() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeRelative();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_fixed() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeFixed();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_floating() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeFloating();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_error() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeError();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_double_obj() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeDoubleSymbol();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_single_obj() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeSingleSymbol();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_quad_obj() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeQuadSymbol();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_halfprecision_obj() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeHalfPrecisionSymbol();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_doubleextended_obj() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeDoubleextendedSymbol();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_double_double_obj() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeDoubleDoubleSymbol();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_triple_double_obj() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makeTripleDoubleSymbol();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_pi() {
  node *thingToEvaluate, *evaluatedThing;
  thingToEvaluate = makePi();
  evaluatedThing = evaluateThing(thingToEvaluate);
  freeThing(thingToEvaluate);
  return evaluatedThing;
}

sollya_obj_t sollya_lib_parse_string(const char *str) {
  return parseString((char *) str);
}

sollya_obj_t sollya_lib_string(char *str) {
  return makeString(str);
}

sollya_obj_t sollya_lib_range_from_interval(mpfi_t interval) {
  sollya_obj_t temp;
  mp_prec_t prec;
  mpfr_t left, right;
  sollya_mpfi_t myInterval;

  sollya_init_and_convert_interval(myInterval, interval);
  prec = sollya_mpfi_get_prec(myInterval);
  mpfr_init2(left,prec);
  mpfr_init2(right,prec);
  sollya_mpfi_get_left(left,myInterval);
  sollya_mpfi_get_right(right,myInterval);
  temp = makeRange(makeConstant(left),makeConstant(right));
  mpfr_clear(left);
  mpfr_clear(right);
  sollya_mpfi_clear(myInterval);

  return temp;
}

sollya_obj_t sollya_lib_range_from_bounds(mpfr_t left, mpfr_t right) {
  sollya_obj_t temp, res;
  temp = makeRange(makeConstant(left),makeConstant(right));
  res = evaluateThing(temp);
  freeThing(temp);
  return res;
}

sollya_obj_t sollya_lib_constant(mpfr_t value) {
  return makeConstant(value);
}

sollya_obj_t sollya_lib_constant_from_double(double value) {
  sollya_obj_t temp;
  mpfr_t valueAsMpfr;

  mpfr_init2(valueAsMpfr,64); /* On some systems, doubles actually are double-extended */
  mpfr_set_d(valueAsMpfr, value, GMP_RNDN);
  temp = makeConstant(valueAsMpfr);
  mpfr_clear(valueAsMpfr);

  return temp;
}

sollya_obj_t sollya_lib_constant_from_int(int value) {
  sollya_obj_t temp;
  mpfr_t valueAsMpfr;

  mpfr_init2(valueAsMpfr,8 * sizeof(int) + 5);
  mpfr_set_si(valueAsMpfr, value, GMP_RNDN);
  temp = makeConstant(valueAsMpfr);
  mpfr_clear(valueAsMpfr);

  return temp;
}

sollya_obj_t sollya_lib_constant_from_int64(int64_t value) {
  sollya_obj_t temp;
  double valueDoubleHi, valueDoubleLo;
  int64_t valueHi, valueLo, tempInt64;
  mpfr_t valueMpfr, tempMpfr;

  /* Cut the 64 bit signed value into two pieces
     such that

     value = valueHi * 2^32 + valueLo.

     Then convert both values to double, which will always
     hold. Adjust the high value. Finally convert to MPFR.
  */
  valueHi = value;
  valueHi >>= 32;       /* Performs floor, even signed */
  tempInt64 = valueHi;
  tempInt64 <<= 32;     /* Exact */
  valueLo = value - tempInt64;

  valueDoubleHi = (double) valueHi;
  valueDoubleLo = (double) valueLo;
  valueDoubleHi *= 4294967296.0;   /* Multiply by 2^32 */

  mpfr_init2(valueMpfr, 64);
  mpfr_init2(tempMpfr, 64);
  mpfr_set_d(valueMpfr, valueDoubleHi, GMP_RNDN);
  mpfr_set_d(tempMpfr, valueDoubleLo, GMP_RNDN);
  mpfr_add(valueMpfr, valueMpfr, tempMpfr, GMP_RNDN); /* exact */
  temp = makeConstant(valueMpfr);
  mpfr_clear(valueMpfr);
  mpfr_clear(tempMpfr);

  return temp;
}

sollya_obj_t sollya_lib_constant_from_uint64(uint64_t value) {
  sollya_obj_t temp;
  double valueDoubleHi, valueDoubleLo;
  uint64_t valueHi, valueLo, tempInt64;
  mpfr_t valueMpfr, tempMpfr;

  /* Cut the 64 bit unsigned value into two pieces
     such that

     value = valueHi * 2^32 + valueLo.

     Then convert both values to double, which will always
     hold. Adjust the high value. Finally convert to MPFR.
  */
  valueHi = value;
  valueHi >>= 32;       /* Performs floor */
  tempInt64 = valueHi;
  tempInt64 <<= 32;     /* Exact */
  valueLo = value - tempInt64;

  valueDoubleHi = (double) valueHi;
  valueDoubleLo = (double) valueLo;
  valueDoubleHi *= 4294967296.0;   /* Multiply by 2^32 */

  mpfr_init2(valueMpfr, 64);
  mpfr_init2(tempMpfr, 64);
  mpfr_set_d(valueMpfr, valueDoubleHi, GMP_RNDN);
  mpfr_set_d(tempMpfr, valueDoubleLo, GMP_RNDN);
  mpfr_add(valueMpfr, valueMpfr, tempMpfr, GMP_RNDN); /* exact */
  temp = makeConstant(valueMpfr);
  mpfr_clear(valueMpfr);
  mpfr_clear(tempMpfr);

  return temp;
}

int sollya_lib_get_interval_from_range(mpfi_t interval, sollya_obj_t obj1) {
  mpfr_t a, b;

  mpfr_init2(a,tools_precision); /* evaluateThingToRange will change the precision afterwards */
  mpfr_init2(b,tools_precision); /* evaluateThingToRange will change the precision afterwards */
  if (evaluateThingToRange(a, b, obj1)) {
    sollya_mpfi_interv_fr(interval, a, b);
    mpfr_clear(a);
    mpfr_clear(b);
    return 1;
  }

  mpfr_clear(a);
  mpfr_clear(b);
  return 0;
}

int sollya_lib_get_bounds_from_range(mpfr_t left, mpfr_t right, sollya_obj_t obj1) {
  mpfr_t a, b;
  mp_prec_t p, pp;
  sollya_mpfi_t temp;

  mpfr_init2(a,tools_precision); /* evaluateThingToRange will change the precision afterwards */
  mpfr_init2(b,tools_precision); /* evaluateThingToRange will change the precision afterwards */
  if (evaluateThingToRange(a, b, obj1)) {
    p = mpfr_get_prec(a);
    pp = mpfr_get_prec(b);
    if (pp > p) p = pp;
    sollya_mpfi_init2(temp,p);
    sollya_mpfi_interv_fr(temp, a, b);
    sollya_mpfi_get_left(left, temp);
    sollya_mpfi_get_right(right, temp);
    sollya_mpfi_clear(temp);
    mpfr_clear(a);
    mpfr_clear(b);
    return 1;
  }

  mpfr_clear(a);
  mpfr_clear(b);
  return 0;
}

int sollya_lib_get_string(char **str, sollya_obj_t obj1) {
  return evaluateThingToString(str, obj1);
}

int sollya_lib_get_constant(mpfr_t value, sollya_obj_t obj1) {
  sollya_obj_t evaluatedObj, simplifiedObj;
  mpfr_t myValue;

  evaluatedObj = evaluateThing(obj1);
  if (!isPureTree(evaluatedObj)) {
    freeThing(evaluatedObj);
    return 0;
  }

  simplifiedObj = simplifyTreeErrorfree(evaluatedObj);
  if (!isConstant(simplifiedObj)) {
    freeThing(evaluatedObj);
    freeThing(simplifiedObj);
    return 0;
  }

  mpfr_init2(myValue, mpfr_get_prec(value));
  if (evaluateThingToConstant(myValue, simplifiedObj, NULL, 1, 0)) {
    if (mpfr_set(value, myValue, GMP_RNDN) != 0) {
      if (!noRoundingWarnings) {
	printMessage(1,SOLLYA_MSG_ROUNDING_ON_CONSTANT_RETRIEVAL,"Warning: rounding occurred on retrieval of a constant.\n");
      }
    }
    mpfr_clear(myValue);
    freeThing(evaluatedObj);
    freeThing(simplifiedObj);
    return 1;
  }

  mpfr_clear(myValue);
  freeThing(evaluatedObj);
  freeThing(simplifiedObj);
  return 0;
}

int sollya_lib_get_prec_of_constant(mp_prec_t *pr, sollya_obj_t obj1) {
  sollya_obj_t evaluatedObj, simplifiedObj;

  evaluatedObj = evaluateThing(obj1);
  if (!isPureTree(evaluatedObj)) {
    freeThing(evaluatedObj);
    return 0;
  }

  simplifiedObj = simplifyTreeErrorfree(evaluatedObj);
  if (!isConstant(simplifiedObj)) {
    freeThing(evaluatedObj);
    freeThing(simplifiedObj);
    return 0;
  }

  if (simplifiedObj->nodeType == CONSTANT) {
    *pr = mpfr_get_prec(*(simplifiedObj->value));
    freeThing(evaluatedObj);
    freeThing(simplifiedObj);
    return 1;
  }

  freeThing(evaluatedObj);
  freeThing(simplifiedObj);
  return 0;
}

int sollya_lib_get_constant_as_double(double *value, sollya_obj_t obj1) {
  mpfr_t temp;

  mpfr_init2(temp,64); /* sollya_lib_get_constant may change the precision afterwards */
  if (sollya_lib_get_constant(temp, obj1)) {
    *value = mpfr_get_d(temp, GMP_RNDN);
    mpfr_clear(temp);
    return 1;
  }

  mpfr_clear(temp);
  return 0;
}

int sollya_lib_get_constant_as_int(int *value, sollya_obj_t obj1) {
  mpfr_t temp;

  mpfr_init2(temp,64); /* sollya_lib_get_constant may change the precision afterwards */
  if (sollya_lib_get_constant(temp, obj1)) {
    *value = mpfr_get_si(temp, GMP_RNDN);
    mpfr_clear(temp);
    return 1;
  }

  mpfr_clear(temp);
  return 0;
}

int64_t sollya_lib_helper_mpfr_to_int64(mpfr_t op) {
  int64_t res;
  mp_prec_t p;
  mpfr_t op_int, temp, temp2;
  int bytes[8];
  int i;


  p = mpfr_get_prec(op);
  if (p < 64) p = 64;
  mpfr_init2(op_int,p);
  mpfr_init2(temp,p);
  mpfr_init2(temp2,p);
  mpfr_nearestint(op_int,op);
  for (i=0;i<8;i++) {
    mpfr_div_2ui(temp, op_int, 3, GMP_RNDN); /* exact */
    mpfr_floor(temp, temp);
    mpfr_mul_2ui(temp, temp, 3, GMP_RNDN); /* exact */
    mpfr_sub(temp2, op_int, temp, GMP_RNDN); /* Sterbenz */
    bytes[i] = mpfr_get_si(temp2, GMP_RNDN); /* exact */
    mpfr_set(op_int, temp, GMP_RNDN); /* exact */
  }
  if (mpfr_zero_p(op_int)) {
    res = 0;
    for (i=7;i>=0;i--) {
      res = res * ((int64_t) 256) + (int64_t) (bytes[i]);
    }
  } else {
    /* The mpfr value overflows on int64 */
    res = (int64_t) 1e65;
  }

  mpfr_clear(op_int);
  mpfr_clear(temp);
  mpfr_clear(temp2);

  return res;
}

uint64_t sollya_lib_helper_mpfr_to_uint64(mpfr_t op) {
  uint64_t res;
  mp_prec_t p;
  mpfr_t op_int, temp, temp2;
  unsigned int bytes[8];
  int i;


  p = mpfr_get_prec(op);
  if (p < 64) p = 64;
  mpfr_init2(op_int,p);
  mpfr_init2(temp,p);
  mpfr_init2(temp2,p);
  mpfr_nearestint(op_int,op);
  if (mpfr_sgn(op_int) >= 0) {
    for (i=0;i<8;i++) {
      mpfr_div_2ui(temp, op_int, 3, GMP_RNDN); /* exact */
      mpfr_floor(temp, temp);
      mpfr_mul_2ui(temp, temp, 3, GMP_RNDN); /* exact */
      mpfr_sub(temp2, op_int, temp, GMP_RNDN); /* Sterbenz */
      bytes[i] = mpfr_get_ui(temp2, GMP_RNDN); /* exact */
      mpfr_set(op_int, temp, GMP_RNDN); /* exact */
    }
    if (mpfr_zero_p(op_int)) {
      res = 0;
      for (i=7;i>=0;i--) {
        res = res * ((uint64_t) 256) + (uint64_t) (bytes[i]);
      }
    } else {
      /* The mpfr value overflows on uint64 */
      res = (uint64_t) 1e65;
    }
  } else {
    /* The mpfr value is negative */
    res = (uint64_t) -1.0;
  }

  mpfr_clear(op_int);
  mpfr_clear(temp);
  mpfr_clear(temp2);

  return res;
}

int sollya_lib_get_constant_as_int64(int64_t *value, sollya_obj_t obj1) {
  mpfr_t temp;

  mpfr_init2(temp,64); /* sollya_lib_get_constant may change the precision afterwards */
  if (sollya_lib_get_constant(temp, obj1)) {
    *value = sollya_lib_helper_mpfr_to_int64(temp);
    mpfr_clear(temp);
    return 1;
  }

  mpfr_clear(temp);
  return 0;
}

int sollya_lib_get_constant_as_uint64(uint64_t *value, sollya_obj_t obj1) {
  mpfr_t temp;

  mpfr_init2(temp,64); /* sollya_lib_get_constant may change the precision afterwards */
  if (sollya_lib_get_constant(temp, obj1)) {
    *value = sollya_lib_helper_mpfr_to_uint64(temp);
    mpfr_clear(temp);
    return 1;
  }

  mpfr_clear(temp);
  return 0;
}

sollya_obj_t sollya_lib_list(sollya_obj_t objects[], int num) {
  int i;
  chain *tempChain;

  if (num < 1) return makeEmptyList();
  tempChain = NULL;
  for (i=num-1;i>=0;i--) {
    tempChain = addElement(tempChain, copyThing(objects[i]));
  }
  return makeList(tempChain);
}

sollya_obj_t sollya_lib_end_elliptic_list(sollya_obj_t objects[], int num) {
  int i;
  chain *tempChain;

  if (num < 1) return makeError();
  tempChain = NULL;
  for (i=num-1;i>=0;i--) {
    tempChain = addElement(tempChain, copyThing(objects[i]));
  }
  return makeFinalEllipticList(tempChain);
}

int sollya_lib_get_list_elements(sollya_obj_t **objects, int *num, int *end_elliptic, sollya_obj_t obj1) {
  sollya_obj_t evaluatedObj;
  int tempVal, i;
  chain *curr;

  evaluatedObj = evaluateThing(obj1);
  if (isEmptyList(evaluatedObj)) {
    *num = 0;
    *end_elliptic = 0;
    freeThing(evaluatedObj);
    return 1;
  }
  if (isPureList(evaluatedObj) || (tempVal = isPureFinalEllipticList(evaluatedObj))) {
    *num = lengthChain(evaluatedObj->arguments);
    *objects = (sollya_obj_t *) safeCalloc(*num,sizeof(sollya_obj_t));
    for (curr=evaluatedObj->arguments,i=0;curr!=NULL;curr=curr->next,i++) {
      (*objects)[i] = copyThing((node *) (curr->value));
    }
    *end_elliptic = tempVal;
    freeThing(evaluatedObj);
    return 1;
  }

  freeThing(evaluatedObj);
  return 0;
}

int sollya_lib_obj_is_function(sollya_obj_t obj1) {
  return isPureTree(obj1);
}

int sollya_lib_obj_is_list(sollya_obj_t obj1) {
  return (isEmptyList(obj1) || isPureList(obj1));
}

int sollya_lib_obj_is_end_elliptic_list(sollya_obj_t obj1) {
  return (isEmptyList(obj1) || isPureFinalEllipticList(obj1));
}

int sollya_lib_obj_is_range(sollya_obj_t obj1) {
  return isRange(obj1);
}

int sollya_lib_obj_is_string(sollya_obj_t obj1) {
  return isString(obj1);
}

int sollya_lib_obj_is_error(sollya_obj_t obj1) {
  return isError(obj1);
}

int sollya_lib_get_function_arity(int *ari, sollya_obj_t obj1) {
  if (!isPureTree(obj1)) return 0;
  if (ari != NULL) {
    *ari = arity(obj1);
  }
  return 1;
}

int sollya_lib_get_head_function(sollya_base_function_t *base_func, sollya_obj_t obj1) {
  if (!isPureTree(obj1)) return 0;
  if (base_func != NULL) {
    switch (obj1->nodeType) {
    case VARIABLE:
      *base_func = SOLLYA_BASE_FUNC_FREE_VARIABLE;
      break;
    case CONSTANT:
      *base_func = SOLLYA_BASE_FUNC_CONSTANT;
      break;
    case ADD:
      *base_func = SOLLYA_BASE_FUNC_ADD;
      break;
    case SUB:
      *base_func = SOLLYA_BASE_FUNC_SUB;
      break;
    case MUL:
      *base_func = SOLLYA_BASE_FUNC_MUL;
      break;
    case DIV:
      *base_func = SOLLYA_BASE_FUNC_DIV;
      break;
    case SQRT:
      *base_func = SOLLYA_BASE_FUNC_SQRT;
      break;
    case EXP:
      *base_func = SOLLYA_BASE_FUNC_EXP;
      break;
    case LOG:
      *base_func = SOLLYA_BASE_FUNC_LOG;
      break;
    case LOG_2:
      *base_func = SOLLYA_BASE_FUNC_LOG_2;
      break;
    case LOG_10:
      *base_func = SOLLYA_BASE_FUNC_LOG_10;
      break;
    case SIN:
      *base_func = SOLLYA_BASE_FUNC_SIN;
      break;
    case COS:
      *base_func = SOLLYA_BASE_FUNC_COS;
      break;
    case TAN:
      *base_func = SOLLYA_BASE_FUNC_TAN;
      break;
    case ASIN:
      *base_func = SOLLYA_BASE_FUNC_ASIN;
      break;
    case ACOS:
      *base_func = SOLLYA_BASE_FUNC_ACOS;
      break;
    case ATAN:
      *base_func = SOLLYA_BASE_FUNC_ATAN;
      break;
    case SINH:
      *base_func = SOLLYA_BASE_FUNC_SINH;
      break;
    case COSH:
      *base_func = SOLLYA_BASE_FUNC_COSH;
      break;
    case TANH:
      *base_func = SOLLYA_BASE_FUNC_TANH;
      break;
    case ASINH:
      *base_func = SOLLYA_BASE_FUNC_ASINH;
      break;
    case ACOSH:
      *base_func = SOLLYA_BASE_FUNC_ACOSH;
      break;
    case ATANH:
      *base_func = SOLLYA_BASE_FUNC_ATANH;
      break;
    case POW:
      *base_func = SOLLYA_BASE_FUNC_POW;
      break;
    case NEG:
      *base_func = SOLLYA_BASE_FUNC_NEG;
      break;
    case ABS:
      *base_func = SOLLYA_BASE_FUNC_ABS;
      break;
    case DOUBLE:
      *base_func = SOLLYA_BASE_FUNC_DOUBLE;
      break;
    case SINGLE:
      *base_func = SOLLYA_BASE_FUNC_SINGLE;
      break;
    case QUAD:
      *base_func = SOLLYA_BASE_FUNC_QUAD;
      break;
    case HALFPRECISION:
      *base_func = SOLLYA_BASE_FUNC_HALFPRECISION;
      break;
    case DOUBLEDOUBLE:
      *base_func = SOLLYA_BASE_FUNC_DOUBLEDOUBLE;
      break;
    case TRIPLEDOUBLE:
      *base_func = SOLLYA_BASE_FUNC_TRIPLEDOUBLE;
      break;
    case ERF:
      *base_func = SOLLYA_BASE_FUNC_ERF;
      break;
    case ERFC:
      *base_func = SOLLYA_BASE_FUNC_ERFC;
      break;
    case LOG_1P:
      *base_func = SOLLYA_BASE_FUNC_LOG_1P;
      break;
    case EXP_M1:
      *base_func = SOLLYA_BASE_FUNC_EXP_M1;
      break;
    case DOUBLEEXTENDED:
      *base_func = SOLLYA_BASE_FUNC_DOUBLEEXTENDED;
      break;
    case LIBRARYFUNCTION:
      *base_func = SOLLYA_BASE_FUNC_LIBRARYFUNCTION;
      break;
    case PROCEDUREFUNCTION:
      *base_func = SOLLYA_BASE_FUNC_PROCEDUREFUNCTION;
      break;
    case CEIL:
      *base_func = SOLLYA_BASE_FUNC_CEIL;
      break;
    case FLOOR:
      *base_func = SOLLYA_BASE_FUNC_FLOOR;
      break;
    case NEARESTINT:
      *base_func = SOLLYA_BASE_FUNC_NEARESTINT;
      break;
    case PI_CONST:
      *base_func = SOLLYA_BASE_FUNC_PI;
      break;
    case LIBRARYCONSTANT:
      *base_func = SOLLYA_BASE_FUNC_LIBRARYCONSTANT;
      break;
    default:
      return 0;
    }
  }
  return 1;
}

int sollya_lib_v_get_subfunctions(sollya_obj_t obj1, int *ari, va_list varlist) {
  sollya_obj_t *elem;
  int i, funcArity, gottaBreak;

  if (!isPureTree(obj1)) return 0;
  funcArity = arity(obj1);
  if (ari != NULL) {
    *ari = funcArity;
  }
  i = 1;
  while ((elem = va_arg(varlist,sollya_obj_t *)) != NULL) {
    if (i <= funcArity) {
      gottaBreak = 0;
      switch (i) {
      case 1:
        *elem = copyThing(obj1->child1);
        break;
      case 2:
        *elem = copyThing(obj1->child2);
        break;
      default:
        gottaBreak = 1;
        break;
      }
      if (gottaBreak) break;
    } else {
      break;
    }
    i++;
  }
  return 1;
}

int sollya_lib_get_subfunctions(sollya_obj_t obj1, int *ari, ...) {
  va_list varlist;
  int res;

  va_start(varlist,ari);
  res = sollya_lib_v_get_subfunctions(obj1, ari, varlist);
  va_end(varlist);

  return res;
}

int sollya_lib_v_decompose_function(sollya_obj_t obj1, sollya_base_function_t *base_func, int *ari, va_list varlist) {
  sollya_obj_t *elem;
  int i, funcArity, gottaBreak;

  if (!isPureTree(obj1)) return 0;
  if (base_func != NULL) {
    switch (obj1->nodeType) {
    case VARIABLE:
      *base_func = SOLLYA_BASE_FUNC_FREE_VARIABLE;
      break;
    case CONSTANT:
      *base_func = SOLLYA_BASE_FUNC_CONSTANT;
      break;
    case ADD:
      *base_func = SOLLYA_BASE_FUNC_ADD;
      break;
    case SUB:
      *base_func = SOLLYA_BASE_FUNC_SUB;
      break;
    case MUL:
      *base_func = SOLLYA_BASE_FUNC_MUL;
      break;
    case DIV:
      *base_func = SOLLYA_BASE_FUNC_DIV;
      break;
    case SQRT:
      *base_func = SOLLYA_BASE_FUNC_SQRT;
      break;
    case EXP:
      *base_func = SOLLYA_BASE_FUNC_EXP;
      break;
    case LOG:
      *base_func = SOLLYA_BASE_FUNC_LOG;
      break;
    case LOG_2:
      *base_func = SOLLYA_BASE_FUNC_LOG_2;
      break;
    case LOG_10:
      *base_func = SOLLYA_BASE_FUNC_LOG_10;
      break;
    case SIN:
      *base_func = SOLLYA_BASE_FUNC_SIN;
      break;
    case COS:
      *base_func = SOLLYA_BASE_FUNC_COS;
      break;
    case TAN:
      *base_func = SOLLYA_BASE_FUNC_TAN;
      break;
    case ASIN:
      *base_func = SOLLYA_BASE_FUNC_ASIN;
      break;
    case ACOS:
      *base_func = SOLLYA_BASE_FUNC_ACOS;
      break;
    case ATAN:
      *base_func = SOLLYA_BASE_FUNC_ATAN;
      break;
    case SINH:
      *base_func = SOLLYA_BASE_FUNC_SINH;
      break;
    case COSH:
      *base_func = SOLLYA_BASE_FUNC_COSH;
      break;
    case TANH:
      *base_func = SOLLYA_BASE_FUNC_TANH;
      break;
    case ASINH:
      *base_func = SOLLYA_BASE_FUNC_ASINH;
      break;
    case ACOSH:
      *base_func = SOLLYA_BASE_FUNC_ACOSH;
      break;
    case ATANH:
      *base_func = SOLLYA_BASE_FUNC_ATANH;
      break;
    case POW:
      *base_func = SOLLYA_BASE_FUNC_POW;
      break;
    case NEG:
      *base_func = SOLLYA_BASE_FUNC_NEG;
      break;
    case ABS:
      *base_func = SOLLYA_BASE_FUNC_ABS;
      break;
    case DOUBLE:
      *base_func = SOLLYA_BASE_FUNC_DOUBLE;
      break;
    case SINGLE:
      *base_func = SOLLYA_BASE_FUNC_SINGLE;
      break;
    case QUAD:
      *base_func = SOLLYA_BASE_FUNC_QUAD;
      break;
    case HALFPRECISION:
      *base_func = SOLLYA_BASE_FUNC_HALFPRECISION;
      break;
    case DOUBLEDOUBLE:
      *base_func = SOLLYA_BASE_FUNC_DOUBLEDOUBLE;
      break;
    case TRIPLEDOUBLE:
      *base_func = SOLLYA_BASE_FUNC_TRIPLEDOUBLE;
      break;
    case ERF:
      *base_func = SOLLYA_BASE_FUNC_ERF;
      break;
    case ERFC:
      *base_func = SOLLYA_BASE_FUNC_ERFC;
      break;
    case LOG_1P:
      *base_func = SOLLYA_BASE_FUNC_LOG_1P;
      break;
    case EXP_M1:
      *base_func = SOLLYA_BASE_FUNC_EXP_M1;
      break;
    case DOUBLEEXTENDED:
      *base_func = SOLLYA_BASE_FUNC_DOUBLEEXTENDED;
      break;
    case LIBRARYFUNCTION:
      *base_func = SOLLYA_BASE_FUNC_LIBRARYFUNCTION;
      break;
    case PROCEDUREFUNCTION:
      *base_func = SOLLYA_BASE_FUNC_PROCEDUREFUNCTION;
      break;
    case CEIL:
      *base_func = SOLLYA_BASE_FUNC_CEIL;
      break;
    case FLOOR:
      *base_func = SOLLYA_BASE_FUNC_FLOOR;
      break;
    case NEARESTINT:
      *base_func = SOLLYA_BASE_FUNC_NEARESTINT;
      break;
    case PI_CONST:
      *base_func = SOLLYA_BASE_FUNC_PI;
      break;
    case LIBRARYCONSTANT:
      *base_func = SOLLYA_BASE_FUNC_LIBRARYCONSTANT;
      break;
    default:
      return 0;
    }
  }
  funcArity = arity(obj1);
  if (ari != NULL) {
    *ari = funcArity;
  }
  i = 1;
  while ((elem = va_arg(varlist,sollya_obj_t *)) != NULL) {
    if (i <= funcArity) {
      gottaBreak = 0;
      switch (i) {
      case 1:
        *elem = copyThing(obj1->child1);
        break;
      case 2:
        *elem = copyThing(obj1->child2);
        break;
      default:
        gottaBreak = 1;
        break;
      }
      if (gottaBreak) break;
    } else {
      break;
    }
    i++;
  }
  return 1;
}

int sollya_lib_decompose_function(sollya_obj_t obj1, sollya_base_function_t *base_func, int *ari, ...) {
  va_list varlist;
  int res;

  va_start(varlist,ari);
  res = sollya_lib_v_decompose_function(obj1, base_func, ari, varlist);
  va_end(varlist);

  return res;
}

int sollya_lib_is_on(sollya_obj_t obj1){
  return (obj1->nodeType == ON);
}

int sollya_lib_is_off(sollya_obj_t obj1) {
  return (obj1->nodeType == OFF);
}

int sollya_lib_is_dyadic(sollya_obj_t obj1) {
  return (obj1->nodeType == DYADIC);
}

int sollya_lib_is_powers(sollya_obj_t obj1) {
  return (obj1->nodeType == POWERS);
}

int sollya_lib_is_binary(sollya_obj_t obj1) {
  return (obj1->nodeType == BINARY);
}

int sollya_lib_is_hexadecimal(sollya_obj_t obj1) {
  return (obj1->nodeType == HEXADECIMAL);
}

int sollya_lib_is_file(sollya_obj_t obj1) {
  return (obj1->nodeType == FILESYM);
}

int sollya_lib_is_postscript(sollya_obj_t obj1) {
  return (obj1->nodeType == POSTSCRIPT);
}

int sollya_lib_is_postscriptfile(sollya_obj_t obj1) {
  return (obj1->nodeType == POSTSCRIPTFILE);
}

int sollya_lib_is_perturb(sollya_obj_t obj1) {
  return (obj1->nodeType == PERTURB);
}

int sollya_lib_is_round_down(sollya_obj_t obj1) {
  return (obj1->nodeType == ROUNDDOWN);
}

int sollya_lib_is_round_up(sollya_obj_t obj1) {
  return (obj1->nodeType == ROUNDUP);
}

int sollya_lib_is_round_towards_zero(sollya_obj_t obj1) {
  return (obj1->nodeType == ROUNDTOZERO);
}

int sollya_lib_is_round_to_nearest(sollya_obj_t obj1) {
  return (obj1->nodeType == ROUNDTONEAREST);
}

int sollya_lib_is_honorcoeffprec(sollya_obj_t obj1) {
  return (obj1->nodeType == HONORCOEFF);
}

int sollya_lib_is_true(sollya_obj_t obj1) {
  return (obj1->nodeType == TRUE);
}

int sollya_lib_is_false(sollya_obj_t obj1) {
  return (obj1->nodeType == FALSE);
}

int sollya_lib_is_void(sollya_obj_t obj1) {
  return (obj1->nodeType == UNIT);
}

int sollya_lib_is_default(sollya_obj_t obj1) {
  return (obj1->nodeType == DEFAULT);
}

int sollya_lib_is_decimal(sollya_obj_t obj1) {
  return (obj1->nodeType == DECIMAL);
}

int sollya_lib_is_absolute(sollya_obj_t obj1) {
  return (obj1->nodeType == ABSOLUTESYM);
}

int sollya_lib_is_relative(sollya_obj_t obj1) {
  return (obj1->nodeType == RELATIVESYM);
}

int sollya_lib_is_fixed(sollya_obj_t obj1) {
  return (obj1->nodeType == FIXED);
}

int sollya_lib_is_floating(sollya_obj_t obj1) {
  return (obj1->nodeType == FLOATING);
}

int sollya_lib_is_double_obj(sollya_obj_t obj1) {
  return (obj1->nodeType == DOUBLESYMBOL);
}

int sollya_lib_is_single_obj(sollya_obj_t obj1) {
  return (obj1->nodeType == SINGLESYMBOL);
}

int sollya_lib_is_quad_obj(sollya_obj_t obj1) {
  return (obj1->nodeType == QUADSYMBOL);
}

int sollya_lib_is_halfprecision_obj(sollya_obj_t obj1) {
  return (obj1->nodeType == HALFPRECISIONSYMBOL);
}

int sollya_lib_is_doubleextended_obj(sollya_obj_t obj1) {
  return (obj1->nodeType == DOUBLEEXTENDEDSYMBOL);
}

int sollya_lib_is_double_double_obj(sollya_obj_t obj1) {
  return (obj1->nodeType == DOUBLEDOUBLESYMBOL);
}

int sollya_lib_is_triple_double_obj(sollya_obj_t obj1) {
  return (obj1->nodeType == TRIPLEDOUBLESYMBOL);
}

int sollya_lib_is_pi(sollya_obj_t obj1) {
  return (obj1->nodeType == PI_CONST);
}

int sollya_lib_obj_is_structure(sollya_obj_t obj1) {
  return isStructure(obj1);
}

int sollya_lib_get_structure_elements(char ***identifiers, sollya_obj_t **objects, int *num, sollya_obj_t obj1) {
  chain *curr;
  int i;

  if (!isStructure(obj1)) return 0;

  *num = lengthChain(obj1->arguments);
  *identifiers = (char **) safeCalloc(*num, sizeof(char *));
  *objects = (sollya_obj_t *) safeCalloc(*num, sizeof(sollya_obj_t));
  for (curr=obj1->arguments, i=0; curr != NULL; curr=curr->next, i++) {
    (*objects)[i] = copyThing((node *) (((entry *) (curr->value))->value));
    (*identifiers)[i] = (char *) safeCalloc(strlen((char *) (((entry *) (curr->value))->name)) + 1, sizeof(char));
    strcpy((*identifiers)[i],(char *) (((entry *) (curr->value))->name));
  }
  return 1;
}

int sollya_lib_get_element_in_structure(sollya_obj_t *object, char *identifier, sollya_obj_t obj1) {
  chain *curr;
  if (!isStructure(obj1)) return 0;

  for (curr=obj1->arguments; curr != NULL; curr=curr->next) {
    if (!strcmp(identifier, (char *) (((entry *) (curr->value))->name))) {
      *object = copyThing((node *) (((entry *) (curr->value))->value));
      return 1;
    }
  }

  return 0;
}

int sollya_lib_assign_in_structure(sollya_obj_t *object, sollya_obj_t obj1, char *identifier, sollya_obj_t obj2) {
  entry *tempEntry;
  int added;
  chain *curr;
  node *tempObj;

  if (obj1 == NULL) {
    tempEntry = (entry *) safeMalloc(sizeof(entry));
    tempEntry->name = (char *) safeCalloc(strlen(identifier) + 1, sizeof(char));
    strcpy(tempEntry->name, identifier);
    tempEntry->value = copyThing(obj2);
    *object = makeStructure(addElement(NULL, tempEntry));
    return 1;
  }
  if (!isStructure(obj1)) return 0;

  tempObj = (node *) safeMalloc(sizeof(node));
  tempObj->nodeType = STRUCTURE;
  tempObj->arguments = NULL;
  added = 0;
  for (curr = obj1->arguments; curr != NULL; curr=curr->next) {
    tempEntry = (entry *) safeMalloc(sizeof(entry));
    tempEntry->name = (char *) safeCalloc(strlen((char *) (((entry *) (curr->value))->name)) + 1, sizeof(char));
    strcpy(tempEntry->name, (char *) (((entry *) (curr->value))->name));
    if (!strcmp(identifier, (char *) (((entry *) (curr->value))->name))) {
      tempEntry->value = copyThing(obj2);
      added = 1;
    } else {
      tempEntry->value = copyThing((node *) (((entry *) (curr->value))->value));
    }
    tempObj->arguments = addElement(tempObj->arguments, tempEntry);
  }
  if (!added) {
    tempEntry = (entry *) safeMalloc(sizeof(entry));
    tempEntry->name = (char *) safeCalloc(strlen(identifier) + 1, sizeof(char));
    strcpy(tempEntry->name, identifier);
    tempEntry->value = copyThing(obj2);
    tempObj->arguments = addElement(tempObj->arguments, tempEntry);
  }
  *object = tempObj;

  return 1;
}

fp_eval_result_t sollya_lib_evaluate_function_at_point(mpfr_t y, sollya_obj_t obj1, mpfr_t x, mpfr_t *cutoff) {
  int res;
  mpfr_t myCutOff;
  sollya_mpfi_t xInt, yInt;
  mpfr_t yLeft, yRight;
  mp_prec_t prec, p;
  mpfr_t threshold;

  /* Check if object is a function */
  if (!isPureTree(obj1)) {
    mpfr_set_nan(y);
    return FP_EVAL_OBJ_NO_FUNCTION;
  }

  /* Determine start precision */
  prec = mpfr_get_prec(y) + 10;

  /* Initialize our own cutoff variable */
  if (cutoff == NULL) {
    mpfr_init2(myCutOff, 12);
    mpfr_set_ui(myCutOff, 0, GMP_RNDN);
  } else {
    if (mpfr_nan_p(*cutoff)) {
      mpfr_set_nan(y);
      return FP_EVAL_CUTOFF_IS_NAN;
    }
    mpfr_init2(myCutOff, mpfr_get_prec(*cutoff));
    mpfr_abs(myCutOff, *cutoff, GMP_RNDN);
  }

  /* Try to perform faithful evaluation */
  res = evaluateFaithfulWithCutOffFast(y, obj1, NULL, x, myCutOff, prec);

  /* Free cutoff */
  mpfr_clear(myCutOff);

  /* Translate the evaluation result code */
  switch (res) {
  case 1:
    /* Faithful rounding was possible */
    return FP_EVAL_FAITHFUL;
    break;
  case 2:
    /* Result was shown to be smaller than cutoff */
    mpfr_set_ui(y,0,GMP_RNDN); /* Set to zero because we are below the cutoff */
    return FP_EVAL_BELOW_CUTOFF;
    break;
  default:
    break;
  }

  /* If we are here, we could not acheive faithful rounding nor get
     below the cutoff.

     We have to perform an additional interval evaluation and see
     if we get real numbers as bounds and if zero is in that interval
     or not.

  */
  if (prec < tools_precision) prec = tools_precision;
  sollya_mpfi_init2(xInt, mpfr_get_prec(x));
  sollya_mpfi_set_fr(xInt, x);
  p = 256 * prec + 10;
  sollya_mpfi_init2(yInt, p);

  /* Perform interval evaluation */
  evaluateInterval(yInt, obj1, NULL, xInt);

  /* Extract bounds */
  mpfr_init2(yLeft, sollya_mpfi_get_prec(yInt));
  mpfr_init2(yRight, sollya_mpfi_get_prec(yInt));
  sollya_mpfi_get_left(yLeft, yInt);
  sollya_mpfi_get_right(yRight, yInt);

  /* Clear intervals */
  sollya_mpfi_clear(xInt);
  sollya_mpfi_clear(yInt);

  /* Check if we got a "point" infinity proof interval */
  if (mpfr_inf_p(yLeft) && mpfr_inf_p(yRight) &&
      (mpfr_sgn(yLeft) == mpfr_sgn(yRight))) {
    mpfr_set(y, yLeft, GMP_RNDN); /* Copying an infinity */
    mpfr_clear(yLeft);
    mpfr_clear(yRight);
    return FP_EVAL_INFINITY;
  }

  /* Check if one of the bounds is a NaN */
  if (mpfr_nan_p(yLeft) || mpfr_nan_p(yRight)) {
    mpfr_set_nan(y);
    return FP_EVAL_FAILURE;
  }

  /* Check if we have an infinity left over */
  if ((!mpfr_number_p(yLeft)) || (!mpfr_number_p(yRight))) {
    /* Here we have [-Inf;Inf] or [4;Inf] or [-Inf;4] 

       We return the floating-point evaluation of (inf(I) + sup(I))/2.
       This means we will produce NaN for [-Inf;Inf].
    */
    mpfr_add(yLeft, yLeft, yRight, GMP_RNDN); 
    mpfr_div_2ui(y, yLeft, 1, GMP_RNDN);
    mpfr_clear(yLeft);
    mpfr_clear(yRight);
    return FP_EVAL_NOT_FAITHFUL_INFINITY_CONTAINED;
  }

  /* Here, both bounds of the proof interval are numbers.

     Check if zero is in the proof interval or not.

  */
  if (mpfr_sgn(yLeft) * mpfr_sgn(yRight) < 0) {
    /* Zero is in the proof interval. 

       Separate the case if max(abs(yLeft),abs(yRight)) is less than
       2^(-p/2) or not. Here, p is the computing precision we used for
       the last interval evaluation.

     */
    mpfr_init2(threshold, 12); /* Will store a power of 2 */
    mpfr_set_ui(threshold,1,GMP_RNDN);
    mpfr_div_2ui(threshold,threshold,(p >> 1),GMP_RNDN); /* exact: power of 2 */
    if ((mpfr_cmp_abs(yLeft, threshold) < 0) && (mpfr_cmp_abs(yRight, threshold) < 0)) {
      mpfr_clear(threshold);
      /* Here both bounds are in magnitude less than the threshold = 2^(-p/2) 

	 We return 0.
	 
      */
      mpfr_set_ui(y,0,GMP_RNDN);
      mpfr_clear(yLeft);
      mpfr_clear(yRight);
      return FP_EVAL_NOT_FAITHFUL_ZERO_CONTAINED_BELOW_THRESHOLD;
    } 
    mpfr_clear(threshold);

    /* Here, at least one of the bounds is not below the threshold.

       We return the floating-point midpoint of the proof interval.

    */
    mpfr_add(yLeft, yLeft, yRight, GMP_RNDN);
    mpfr_div_2ui(y, yLeft, 1, GMP_RNDN);
    mpfr_clear(yLeft);
    mpfr_clear(yRight);
    return FP_EVAL_NOT_FAITHFUL_ZERO_CONTAINED_NOT_BELOW_THRESHOLD; 
  }

  /* Here, zero is not in the proof interval. Take the approximate
     midpoint of the proof interval as an approximation of the
     mathematical result value.
  */

  mpfr_add(yLeft, yLeft, yRight, GMP_RNDN);
  mpfr_div_2ui(y, yLeft, 1, GMP_RNDN);
  mpfr_clear(yLeft);
  mpfr_clear(yRight);
  return FP_EVAL_NOT_FAITHFUL_ZERO_NOT_CONTAINED;
}

fp_eval_result_t sollya_lib_evaluate_function_at_constant_expression(mpfr_t y, sollya_obj_t obj1, sollya_obj_t x, mpfr_t *cutoff) {
  int res;
  mpfr_t myCutOff;
  sollya_mpfi_t xInt, yInt;
  mpfr_t yLeft, yRight;
  mp_prec_t prec, p;
  mpfr_t threshold;
  sollya_mpfi_t dummyInterval;

  /* Check if object is a function */
  if ((!isPureTree(obj1)) || (!isPureTree(x))) {
    mpfr_set_nan(y);
    return FP_EVAL_OBJ_NO_FUNCTION;
  }
  
  /* Check if abscissa expression is constant */
  if (!isConstant(x)) {
    mpfr_set_nan(y);
    return FP_EVAL_EXPRESSION_NOT_CONSTANT;
  }

  /* Determine start precision */
  prec = mpfr_get_prec(y) + 10;

  /* Initialize our own cutoff variable */
  if (cutoff == NULL) {
    mpfr_init2(myCutOff, 12);
    mpfr_set_ui(myCutOff, 0, GMP_RNDN);
  } else {
    if (mpfr_nan_p(*cutoff)) {
      mpfr_set_nan(y);
      return FP_EVAL_CUTOFF_IS_NAN;
    }
    mpfr_init2(myCutOff, mpfr_get_prec(*cutoff));
    mpfr_abs(myCutOff, *cutoff, GMP_RNDN);
  }

  /* Try to perform faithful evaluation */
  res = evaluateFaithfulAtConstantExpression(y, obj1, NULL, x, myCutOff, prec);

  /* Free cutoff */
  mpfr_clear(myCutOff);

  /* Translate the evaluation result code */
  switch (res) {
  case 1:
    /* Faithful rounding was possible */
    return FP_EVAL_FAITHFUL;
    break;
  case 2:
    /* Result was shown to be smaller than cutoff */
    mpfr_set_ui(y,0,GMP_RNDN); /* Set to zero because we are below the cutoff */
    return FP_EVAL_BELOW_CUTOFF;
    break;
  default:
    break;
  }

  /* If we are here, we could not acheive faithful rounding nor get
     below the cutoff.

     We have to perform an additional interval evaluation and see
     if we get real numbers as bounds and if zero is in that interval
     or not.

  */
  if (prec < tools_precision) prec = tools_precision;
  p = 256 * prec + 10;

  /* Evaluate x to an interval xInt */
  sollya_mpfi_init2(xInt, p);
  evaluateConstantExpressionToInterval(xInt, x);

  /* Initialize the ordinate interval */
  sollya_mpfi_init2(yInt, p);

  /* Perform interval evaluation */
  evaluateInterval(yInt, obj1, NULL, xInt);

  /* Extract bounds */
  mpfr_init2(yLeft, sollya_mpfi_get_prec(yInt));
  mpfr_init2(yRight, sollya_mpfi_get_prec(yInt));
  sollya_mpfi_get_left(yLeft, yInt);
  sollya_mpfi_get_right(yRight, yInt);

  /* Clear intervals */
  sollya_mpfi_clear(xInt);
  sollya_mpfi_clear(yInt);

  /* Check if we got a "point" infinity proof interval */
  if (mpfr_inf_p(yLeft) && mpfr_inf_p(yRight) &&
      (mpfr_sgn(yLeft) == mpfr_sgn(yRight))) {
    mpfr_set(y, yLeft, GMP_RNDN); /* Copying an infinity */
    mpfr_clear(yLeft);
    mpfr_clear(yRight);
    return FP_EVAL_INFINITY;
  }

  /* Check if one of the bounds is a NaN */
  if (mpfr_nan_p(yLeft) || mpfr_nan_p(yRight)) {
    mpfr_set_nan(y);
    return FP_EVAL_FAILURE;
  }

  /* Check if we have an infinity left over */
  if ((!mpfr_number_p(yLeft)) || (!mpfr_number_p(yRight))) {
    /* Here we have [-Inf;Inf] or [4;Inf] or [-Inf;4] 

       We return the floating-point evaluation of (inf(I) + sup(I))/2.
       This means we will produce NaN for [-Inf;Inf].
    */
    mpfr_add(yLeft, yLeft, yRight, GMP_RNDN); 
    mpfr_div_2ui(y, yLeft, 1, GMP_RNDN);
    mpfr_clear(yLeft);
    mpfr_clear(yRight);
    return FP_EVAL_NOT_FAITHFUL_INFINITY_CONTAINED;
  }

  /* Here, both bounds of the proof interval are numbers.

     Check if zero is in the proof interval or not.

  */
  if (mpfr_sgn(yLeft) * mpfr_sgn(yRight) < 0) {
    /* Zero is in the proof interval. 

       Separate the case if max(abs(yLeft),abs(yRight)) is less than
       2^(-p/2) or not. Here, p is the computing precision we used for
       the last interval evaluation.

     */
    mpfr_init2(threshold, 12); /* Will store a power of 2 */
    mpfr_set_ui(threshold,1,GMP_RNDN);
    mpfr_div_2ui(threshold,threshold,(p >> 1),GMP_RNDN); /* exact: power of 2 */
    if ((mpfr_cmp_abs(yLeft, threshold) < 0) && (mpfr_cmp_abs(yRight, threshold) < 0)) {
      mpfr_clear(threshold);
      /* Here both bounds are in magnitude less than the threshold = 2^(-p/2) 

	 We return 0.
	 
      */
      mpfr_set_ui(y,0,GMP_RNDN);
      mpfr_clear(yLeft);
      mpfr_clear(yRight);
      return FP_EVAL_NOT_FAITHFUL_ZERO_CONTAINED_BELOW_THRESHOLD;
    } 
    mpfr_clear(threshold);

    /* Here, at least one of the bounds is not below the threshold.

       We return the floating-point midpoint of the proof interval.

    */
    mpfr_add(yLeft, yLeft, yRight, GMP_RNDN);
    mpfr_div_2ui(y, yLeft, 1, GMP_RNDN);
    mpfr_clear(yLeft);
    mpfr_clear(yRight);
    return FP_EVAL_NOT_FAITHFUL_ZERO_CONTAINED_NOT_BELOW_THRESHOLD; 
  }

  /* Here, zero is not in the proof interval. Take the approximate
     midpoint of the proof interval as an approximation of the
     mathematical result value.
  */

  mpfr_add(yLeft, yLeft, yRight, GMP_RNDN);
  mpfr_div_2ui(y, yLeft, 1, GMP_RNDN);
  mpfr_clear(yLeft);
  mpfr_clear(yRight);
  return FP_EVAL_NOT_FAITHFUL_ZERO_NOT_CONTAINED;
}

ia_eval_result_t sollya_lib_evaluate_function_over_interval(mpfi_t y, sollya_obj_t obj1, mpfi_t op_x) {
  sollya_mpfi_t myY, myPointY, x;
  mpfr_t xLeft, xRight, yLeft, yRight, myCutOff;
  mp_prec_t prec, p;

  /* Check if object is a function */
  if (!isPureTree(obj1)) {
    sollya_mpfi_set_nan(y);
    return INT_EVAL_OBJ_NO_FUNCTION;
  }

  /* Convert entering mpfi_t interval to sollya_mpfi_t */
  sollya_init_and_convert_interval(x, op_x);

  /* Initialize our own versions of the final result */
  prec = sollya_mpfi_get_prec(y);
  sollya_mpfi_init2(myY, prec + 5);
  sollya_mpfi_init2(myPointY, prec + 5);
  sollya_mpfi_set_full_range(myPointY);

  /* If x is a point interval, try to use faithful evaluation with
     precision adaptation to get a tighter result.
  */
  p = sollya_mpfi_get_prec(x);
  mpfr_init2(xLeft, p);
  mpfr_init2(xRight, p);
  sollya_mpfi_get_left(xLeft, x);
  sollya_mpfi_get_right(xRight, x);
  if (mpfr_equal_p(xLeft,xRight)) {
    mpfr_init2(yLeft, prec + 10);
    mpfr_init2(yRight, prec + 10);
    mpfr_init2(myCutOff, 12);
    mpfr_set_ui(myCutOff, 0, GMP_RNDN);
    if (evaluateFaithfulWithCutOffFast(yLeft, obj1, NULL, xLeft, myCutOff, prec + 15) == 1) {
      mpfr_set(yRight, yLeft, GMP_RNDN); /* exact */
      mpfr_nextbelow(yLeft);
      mpfr_nextbelow(yLeft);
      mpfr_nextabove(yRight);
      mpfr_nextabove(yRight);
      if (mpfr_number_p(yLeft) && mpfr_number_p(yRight)) {
        sollya_mpfi_interv_fr(myPointY, yLeft, yRight);
      }
    }
    mpfr_clear(myCutOff);
    mpfr_clear(yLeft);
    mpfr_clear(yRight);
  }
  mpfr_clear(xLeft);
  mpfr_clear(xRight);

  /* Perform an interval evaluation on the whole interval */
  evaluateInterval(myY, obj1, NULL, x);

  /* Set final result as intersection of myY and myPointY */
  sollya_mpfi_intersect(y, myY, myPointY);

  /* Clear the local variables */
  sollya_mpfi_clear(myY);
  sollya_mpfi_clear(myPointY);

  /* Clear our sollya_mpfi_t copy of the entering interval */
  sollya_mpfi_clear(x);

  /* Return evaluation status result as a function of the result */
  if (sollya_mpfi_bounded_p(y)) return INT_EVAL_BOUNDED;
  if (sollya_mpfi_has_nan(y)) return INT_EVAL_FAILURE;
  if (sollya_mpfi_has_infinity(y)) return INT_EVAL_UNBOUNDED;

  /* Just in case we missed something */
  return INT_EVAL_FAILURE;
}

sollya_obj_t sollya_lib_get_object_list_head(sollya_obj_list_t list) {
  if (list == NULL) return NULL;
  return (sollya_obj_t) (list->value);
}

sollya_obj_list_t sollya_lib_get_object_list_tail(sollya_obj_list_t list) {
  if (list == NULL) return NULL;
  return (sollya_obj_list_t) (list->next);
}

sollya_obj_list_t sollya_lib_construct_object_list(sollya_obj_t obj1, sollya_obj_list_t list) {
  return (sollya_obj_list_t) addElement(list, obj1);
}

sollya_obj_list_t sollya_lib_copy_object_list(sollya_obj_list_t list) {
  if (list == NULL) return NULL;
  return (sollya_obj_list_t) (copyChainWithoutReversal(list, copyThingOnVoid));
}

void sollya_lib_clear_object_list(sollya_obj_list_t list) {
  freeChain(list, freeThingOnVoid);
}

int sollya_lib_is_empty_object_list(sollya_obj_list_t list) {
  return (list == NULL);
}

mpfr_t *sollya_lib_get_constant_list_head(sollya_constant_list_t list) {
  if (list == NULL) return NULL;
  return (mpfr_t *) (list->value);
}

sollya_constant_list_t sollya_lib_get_constant_list_tail(sollya_constant_list_t list) {
  if (list == NULL) return NULL;
  return (sollya_constant_list_t) (list->next);
}

sollya_constant_list_t sollya_lib_construct_constant_list(mpfr_t *constant, sollya_constant_list_t list) {
  return (sollya_constant_list_t) addElement(list, constant);
}

sollya_constant_list_t sollya_lib_copy_constant_list(sollya_constant_list_t list) {
  if (list == NULL) return NULL;
  return (sollya_constant_list_t) (copyChainWithoutReversal(list, copyMpfrPtr));
}

void sollya_lib_clear_constant_list(sollya_constant_list_t list) {
  freeChain(list, freeMpfrPtr);
}

int sollya_lib_is_empty_constant_list(sollya_constant_list_t list) {
  return (list == NULL);
}

mpfi_t *sollya_lib_get_interval_list_head(sollya_interval_list_t list) {
  if (list == NULL) return NULL;
  return (mpfi_t *) (list->value);
}

sollya_interval_list_t sollya_lib_get_interval_list_tail(sollya_interval_list_t list) {
  if (list == NULL) return NULL;
  return (sollya_interval_list_t) (list->next);
}

sollya_interval_list_t sollya_lib_construct_interval_list(mpfi_t *interval, sollya_interval_list_t list) {
  return (sollya_interval_list_t) addElement(list, interval);
}

sollya_interval_list_t sollya_lib_copy_interval_list(sollya_interval_list_t list) {
  if (list == NULL) return NULL;
  return (sollya_interval_list_t) (copyChainWithoutReversal(list, copyMpfiPtr));
}

void sollya_lib_clear_interval_list(sollya_interval_list_t list) {
  freeChain(list, freeMpfiPtr);
}

int sollya_lib_is_empty_interval_list(sollya_interval_list_t list) {
  return (list == NULL);
}

int sollya_lib_get_int_list_head(sollya_int_list_t list) {
  if (list == NULL) return 0;
  return *((int *) (list->value));
}

sollya_int_list_t sollya_lib_get_int_list_tail(sollya_int_list_t list) {
  if (list == NULL) return NULL;
  return (sollya_int_list_t) (list->next);
}

sollya_int_list_t sollya_lib_construct_int_list(int integer, sollya_int_list_t list) {
  int *intPtr;

  intPtr = (int *) safeMalloc(sizeof(int));
  *intPtr = integer;
  return (sollya_int_list_t) addElement(list, intPtr);
}

sollya_int_list_t sollya_lib_copy_int_list(sollya_int_list_t list) {
  if (list == NULL) return NULL;
  return (sollya_int_list_t) (copyChainWithoutReversal(list, copyIntPtrOnVoid));
}

void sollya_lib_clear_int_list(sollya_int_list_t list) {
  freeChain(list, freeIntPtr);
}

int sollya_lib_is_empty_int_list(sollya_int_list_t list) {
  return (list == NULL);
}

int sollya_lib_get_boolean_list_head(sollya_boolean_list_t list) {
  if (list == NULL) return 0;
  return *((int *) (list->value));
}

sollya_boolean_list_t sollya_lib_get_boolean_list_tail(sollya_boolean_list_t list) {
  if (list == NULL) return NULL;
  return (sollya_boolean_list_t) (list->next);
}

sollya_boolean_list_t sollya_lib_construct_boolean_list(int boolVal, sollya_boolean_list_t list) {
  int *intPtr;

  intPtr = (int *) safeMalloc(sizeof(int));
  *intPtr = boolVal;
  return (sollya_boolean_list_t) addElement(list, intPtr);
}

sollya_boolean_list_t sollya_lib_copy_boolean_list(sollya_boolean_list_t list) {
  if (list == NULL) return NULL;
  return (sollya_boolean_list_t) (copyChainWithoutReversal(list, copyIntPtrOnVoid));
}

void sollya_lib_clear_boolean_list(sollya_boolean_list_t list) {
  freeChain(list, freeIntPtr);
}

int sollya_lib_is_empty_boolean_list(sollya_boolean_list_t list) {
  return (list == NULL);
}

char *sollya_lib_get_string_list_head(sollya_string_list_t list) {
  if (list == NULL) return NULL;
  return (char *) (list->value);
}

sollya_string_list_t sollya_lib_get_string_list_tail(sollya_string_list_t list) {
  if (list == NULL) return NULL;
  return (sollya_string_list_t) (list->next);
}

sollya_string_list_t sollya_lib_construct_string_list(char *str, sollya_string_list_t list) {
  return (sollya_string_list_t) addElement(list, str);
}

sollya_string_list_t sollya_lib_copy_string_list(sollya_string_list_t list) {
  if (list == NULL) return NULL;
  return (sollya_string_list_t) (copyChainWithoutReversal(list, copyString));
}

void sollya_lib_clear_string_list(sollya_string_list_t list) {
  freeChain(list, freeStringPtr);
}

int sollya_lib_is_empty_string_list(sollya_string_list_t list) {
  return (list == NULL);
}

sollya_obj_t sollya_lib_build_list(sollya_obj_t obj1, ...) {
  node *elem;
  chain *thinglist, *curr;
  va_list varlist;
  
  if (obj1 == NULL) {
    return makeEmptyList();
  } 

  va_start(varlist,obj1);
  thinglist = (chain *) safeMalloc(sizeof(chain));
  thinglist->value = obj1;
  thinglist->next = NULL;
  curr = thinglist;
  while ((elem = va_arg(varlist,node *)) != NULL) {
      curr->next = (chain *) safeMalloc(sizeof(chain));
      curr = curr->next;
      curr->value = elem;
      curr->next = NULL;
  }
  va_end(varlist);
  
  return makeList(thinglist);
}

sollya_obj_t sollya_lib_build_end_elliptic_list(sollya_obj_t obj1, ...) {
  node *elem;
  chain *thinglist, *curr;
  va_list varlist;
  
  if (obj1 == NULL) {
    return makeError();
  } 

  va_start(varlist,obj1);
  thinglist = (chain *) safeMalloc(sizeof(chain));
  thinglist->value = obj1;
  thinglist->next = NULL;
  curr = thinglist;
  while ((elem = va_arg(varlist,node *)) != NULL) {
      curr->next = (chain *) safeMalloc(sizeof(chain));
      curr = curr->next;
      curr->value = elem;
      curr->next = NULL;
  }
  va_end(varlist);
  
  return makeFinalEllipticList(thinglist);
} 

sollya_obj_t sollya_lib_v_build_list(va_list varlist) {
  node *elem;
  chain *thinglist, *curr;
  
  elem = va_arg(varlist,node *);
  if (elem == NULL) {
    return makeEmptyList();
  } 

  thinglist = (chain *) safeMalloc(sizeof(chain));
  thinglist->value = elem;
  thinglist->next = NULL;
  curr = thinglist;
  while ((elem = va_arg(varlist,node *)) != NULL) {
      curr->next = (chain *) safeMalloc(sizeof(chain));
      curr = curr->next;
      curr->value = elem;
      curr->next = NULL;
  }
  
  return makeList(thinglist);
}

sollya_obj_t sollya_lib_v_build_end_elliptic_list(va_list varlist) {
  node *elem;
  chain *thinglist, *curr;
  
  elem = va_arg(varlist,node *);
  if (elem == NULL) {
    return makeError();
  } 

  thinglist = (chain *) safeMalloc(sizeof(chain));
  thinglist->value = elem;
  thinglist->next = NULL;
  curr = thinglist;
  while ((elem = va_arg(varlist,node *)) != NULL) {
      curr->next = (chain *) safeMalloc(sizeof(chain));
      curr = curr->next;
      curr->value = elem;
      curr->next = NULL;
  }
  
  return makeFinalEllipticList(thinglist);
}

sollya_obj_t sollya_lib_build_function_free_variable() {
  return makeVariable();
}

sollya_obj_t sollya_lib_build_function_add(sollya_obj_t obj1, sollya_obj_t obj2) {
  return makeAdd(obj1,obj2);
}

sollya_obj_t sollya_lib_build_function_sub(sollya_obj_t obj1, sollya_obj_t obj2) {
  return makeSub(obj1,obj2);
}

sollya_obj_t sollya_lib_build_function_mul(sollya_obj_t obj1, sollya_obj_t obj2) {
  return makeMul(obj1,obj2);
}

sollya_obj_t sollya_lib_build_function_div(sollya_obj_t obj1, sollya_obj_t obj2) {
  return makeDiv(obj1,obj2);
}

sollya_obj_t sollya_lib_build_function_sqrt(sollya_obj_t obj1) {
  return makeSqrt(obj1);
}

sollya_obj_t sollya_lib_build_function_exp(sollya_obj_t obj1) {
  return makeExp(obj1);
}

sollya_obj_t sollya_lib_build_function_log(sollya_obj_t obj1) {
  return makeLog(obj1);
}

sollya_obj_t sollya_lib_build_function_log2(sollya_obj_t obj1) {
  return makeLog2(obj1);
}

sollya_obj_t sollya_lib_build_function_log10(sollya_obj_t obj1) {
  return makeLog10(obj1);
}

sollya_obj_t sollya_lib_build_function_sin(sollya_obj_t obj1) {
  return makeSin(obj1);
}

sollya_obj_t sollya_lib_build_function_cos(sollya_obj_t obj1) {
  return makeCos(obj1);
}

sollya_obj_t sollya_lib_build_function_tan(sollya_obj_t obj1) {
  return makeTan(obj1);
}

sollya_obj_t sollya_lib_build_function_asin(sollya_obj_t obj1) {
  return makeAsin(obj1);
}

sollya_obj_t sollya_lib_build_function_acos(sollya_obj_t obj1) {
  return makeAcos(obj1);
}

sollya_obj_t sollya_lib_build_function_atan(sollya_obj_t obj1) {
  return makeAtan(obj1);
}

sollya_obj_t sollya_lib_build_function_pow(sollya_obj_t obj1, sollya_obj_t obj2) {
  return makePow(obj1, obj2);
}

sollya_obj_t sollya_lib_build_function_neg(sollya_obj_t obj1) {
  return makeNeg(obj1);
}

sollya_obj_t sollya_lib_build_function_abs(sollya_obj_t obj1) {
  return makeAbs(obj1);
}

sollya_obj_t sollya_lib_build_function_double(sollya_obj_t obj1) {
  return makeDouble(obj1);
}

sollya_obj_t sollya_lib_build_function_single(sollya_obj_t obj1) {
  return makeSingle(obj1);
}

sollya_obj_t sollya_lib_build_function_quad(sollya_obj_t obj1) {
  return makeQuad(obj1);
}

sollya_obj_t sollya_lib_build_function_halfprecision(sollya_obj_t obj1) {
  return makeHalfPrecision(obj1);
}

sollya_obj_t sollya_lib_build_function_double_double(sollya_obj_t obj1) {
  return makeDoubledouble(obj1);
}

sollya_obj_t sollya_lib_build_function_triple_double(sollya_obj_t obj1) {
  return makeTripledouble(obj1);
}

sollya_obj_t sollya_lib_build_function_erf(sollya_obj_t obj1) {
  return makeErf(obj1);
}

sollya_obj_t sollya_lib_build_function_erfc(sollya_obj_t obj1) {
  return makeErfc(obj1);
}

sollya_obj_t sollya_lib_build_function_log1p(sollya_obj_t obj1) {
  return makeLog1p(obj1);
}

sollya_obj_t sollya_lib_build_function_expm1(sollya_obj_t obj1) {
  return makeExpm1(obj1);
}

sollya_obj_t sollya_lib_build_function_doubleextended(sollya_obj_t obj1) {
  return makeDoubleextended(obj1);
}

sollya_obj_t sollya_lib_build_function_ceil(sollya_obj_t obj1) {
  return makeCeil(obj1);
}

sollya_obj_t sollya_lib_build_function_floor(sollya_obj_t obj1) {
  return makeFloor(obj1);
}

sollya_obj_t sollya_lib_build_function_nearestint(sollya_obj_t obj1) {
  return makeNearestInt(obj1);
}

sollya_obj_t sollya_lib_build_function_sinh(sollya_obj_t obj1) {
  return makeSinh(obj1);
}

sollya_obj_t sollya_lib_build_function_cosh(sollya_obj_t obj1) {
  return makeCosh(obj1);
}

sollya_obj_t sollya_lib_build_function_tanh(sollya_obj_t obj1) {
  return makeTanh(obj1);
}

sollya_obj_t sollya_lib_build_function_asinh(sollya_obj_t obj1) {
  return makeAsinh(obj1);
}

sollya_obj_t sollya_lib_build_function_acosh(sollya_obj_t obj1) {
  return makeAcosh(obj1);
}

sollya_obj_t sollya_lib_build_function_atanh(sollya_obj_t obj1) {
  return makeAtanh(obj1);
}

sollya_obj_t sollya_lib_build_function_pi() {
  return makePi();
}
