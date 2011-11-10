/*

Copyright 2011 by

Laboratoire d'Informatique de Paris 6, equipe PEQUAN,
UPMC Universite Paris 06 - CNRS - UMR 7606 - LIP6, Paris, France,

Contributor Ch. Lauter

christoph.lauter@ens-lyon.org
sylvain.chevillard@ens-lyon.org

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
therefore means  that it is reserved for developers  and  experienced
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

#ifndef MESSAGE_NUMBERS_H
#define MESSAGE_NUMBERS_H

#define SOLLYA_MSG_NO_MSG                                            0       /* Void error message, no error at all */
#define SOLLYA_MSG_CONTINUATION                                      1       /* Continues the error message that has just started */
#define SOLLYA_MSG_UNDEFINED_ERROR                                   2       /* Some undefined error occurred. This is a place-holder */
#define SOLLYA_MSG_ABS_NOT_TWICE_DIFFERENTIABLE                      3       /* abs is not twice differentiable */
#define SOLLYA_MSG_HALF_NOT_DIFFERENTIABLE                           4       /* half-precision rounding operator not differentiable */
#define SOLLYA_MSG_SINGLE_NOT_DIFFERENTIABLE                         5       /* single rounding operator not differentiable */
#define SOLLYA_MSG_DOUBLE_NOT_DIFFERENTIABLE                         6       /* double rounding operator not differentiable */
#define SOLLYA_MSG_DOUBLEEXTENDED_NOT_DIFFERENTIABLE                 7       /* double-extended rounding operator not differentiable */
#define SOLLYA_MSG_DOUBLE_DOUBLE_NOT_DIFFERENTIABLE                  8       /* double-double rounding operator not differentiable */
#define SOLLYA_MSG_TRIPLE_DOUBLE_NOT_DIFFERENTIABLE                  9       /* triple-double rounding operator not differentiable */
#define SOLLYA_MSG_QUAD_NOT_DIFFERENTIABLE                          10       /* quad rounding operator not differentiable */
#define SOLLYA_MSG_CEIL_NOT_DIFFERENTIABLE                          11       /* ceil operator not differentiable */
#define SOLLYA_MSG_FLOOR_NOT_DIFFERENTIABLE                         12       /* floor operator not differentiable */
#define SOLLYA_MSG_NEARESTINT_NOT_DIFFERENTIABLE                    13       /* nearestint operator not differentiable */
#define SOLLYA_MSG_UNDESIRED_ROUNDING_IN_ROUND_TO_FORMAT            14       /* An undesired rounding occurred in round to format */
#define SOLLYA_MSG_DOUBLE_ROUNDING_IN_ROUND_TO_DOUBLE               15       /* A double rounding occurred in round to double */
#define SOLLYA_MSG_DOUBLE_ROUNDING_IN_ROUND_TO_PREC                 16       /* A double rounding occurred in round-to-prec */
#define SOLLYA_MSG_ROUNDING_OCCURRED_WHILE_CONVERTING_FROM_DOUBLE   17       /* Rounding occurred while converting from double */
#define SOLLYA_MSG_DOUBLE_ROUNDING_IN_ROUND_TO_SINGLE               18       /* A double rounding occurred in round to single */
#define SOLLYA_MSG_DOUBLE_ROUNDING_IN_ROUND_TO_DOUBLE_DOUBLE        19       /* A double rounding occurred in round to double-double */
#define SOLLYA_MSG_DOUBLE_ROUNDING_IN_ROUND_TO_TRIPLE_DOUBLE        20       /* A double rounding occurred in round to triple-double */
#define SOLLYA_MSG_ROUNDING_DOWN_BEFORE_PRINTING_DOUBLE             22       /* A round-down occurred before printing a double precision value */
#define SOLLYA_MSG_ROUNDING_UP_BEFORE_PRINTING_DOUBLE               23       /* A round-up occurred before printing a double precision value */
#define SOLLYA_MSG_COULD_NOT_FIGURE_OUT_ENDIANESS                   24       /* Could not figure out the endianess of the system */
#define SOLLYA_MSG_ROUNDING_DOWN_BEFORE_PRINTING_SINGLE             25       /* A round-down occurred before printing a single precision value */
#define SOLLYA_MSG_ROUNDING_UP_BEFORE_PRINTING_SINGLE               26       /* A round-up occurred before printing a single precision value */
#define SOLLYA_MSG_SNAN_MIGHT_HAVE_BECOME_QNAN                      27       /* An sNaN might have become a qNaN. */
#define SOLLYA_MSG_UNABLE_TO_CONVERT_FROM_HEXADECIMAL_CONSTANT      28       /* Unable to convert from a hexadecimal constant. */
#define SOLLYA_MSG_GIVEN_FUNCTION_IS_NO_POLYNOMIAL                  29       /* The given function is no polynomial. */
#define SOLLYA_MSG_NUM_OF_FORMATS_DOES_NOT_CORRESPOND_TO_DEGREE     30       /* The number of formats does not correspond to the degree of the polynomial. */
#define SOLLYA_MSG_ERROR_WHILE_EXTRACTING_COEFFICIENTS_OF_POLY      31       /* Error while extracting the coefficients of a polynomial. */
#define SOLLYA_MSG_ERROR_POLY_COEFF_GETS_ROUNDED                    32       /* A coefficient of a polynomial is not constant and gets rounded. */
#define SOLLYA_MSG_ERROR_EVALUATION_OF_POLY_COEFF_NOT_FAITHFUL      33       /* The evaluation of a coefficient of a polynomial does not give a faithful rounding. */
#define SOLLYA_MSG_ERROR_UNKNOWN_EXPANSION_FORMAT                   34       /* An unknown expansion format is given. */
#define SOLLYA_MSG_DOUBLE_ROUNDING_ON_HANDLING_POLY_COEFF           35       /* A double rounding occurred while handling the evaluation of a coefficient of a polynomial */
#define SOLLYA_MSG_AT_LEAST_ONE_POLY_COEFF_HAS_BEEN_ROUNDED         36       /* At least one of the coefficients of a polynomial has been rounded. */
#define SOLLYA_MSG_NONE_OF_THE_POLY_COEFFS_HAS_BEEN_ROUNDED         37       /* None of the coefficients of a polynomial has been rounded. */
#define SOLLYA_MSG_NON_REAL_NUMBER_CANNOT_BE_DOUBLE_EXPANSION       38       /* A number that is not real cannot be displayed as a double expansion. */
#define SOLLYA_MSG_DOUBLE_ROUNDING_ON_CONVERSION                    39       /* A double rounding occurred unexpectly on a conversion. */
#define SOLLYA_MSG_DOUBLE_EXPANSION_INCOMPLETE                      40       /* A double expansion is incomplete because of the limited exponent range of double precision. */
#define SOLLYA_MSG_ROUNDING_WHILE_SIMPLIFYING_TO_POLYNOMIAL         41       /* A rounding occurred while simplifying an expression to a polynomial. */
#define SOLLYA_MSG_POLY_COEFF_IS_NOT_CONSTANT                       42       /* A coefficient of a polynomial is not a constant expression. */
#define SOLLYA_MSG_SOME_EVALUATION_IS_NOT_FAITHFUL                  43       /* Some evaluation of a constant expression fails to give a faithful rounding. */
#define SOLLYA_MSG_DOUBLE_ROUNDING_IN_ROUND_IEEE_754_2008_OPERATOR  44       /* A double rounding occurred during invocation of an IEEE 754-2008 rounding operator. */
#define SOLLYA_MSG_STRING_CANNOT_BE_PARSED_BY_MINIPARSER            45       /* A given string cannot be parsed by the mini-parser. */
#define SOLLYA_MSG_ERROR_ON_RUNNING_GUESSDEGREE                     46       /* Some error occurred while executing guessdegree. */
#define SOLLYA_MSG_FILE_EXECUTION_ASKED_FOR_QUIT_NOT_QUITTING       47       /* The execution of a file read by execute demanded stopping the interpretation but it is not stopped. */
#define SOLLYA_MSG_EXPR_SHOULD_BE_CONSTANT_AND_SEEMS_CONSTANT       48       /* An expression should be constant in a context. It seems constant but this could not be proven. */
#define SOLLYA_MSG_EXPR_SHOULD_BE_CONSTANT_AND_IS_CONSTANT_ON_FP    49       /* An expression should be constant in a context. It seems constant when floating-point evaluation is used. */
#define SOLLYA_MSG_EXPR_SHOULD_BE_CONSTANT_AND_IS_NOT_FAITHFUL      50       /* An expression should be constant in a context and faithful evaluation is not possible. Taking zero. */
#define SOLLYA_MSG_EXPR_SHOULD_BE_CONSTANT_NO_FAITHFUL_PLAIN_FP     51       /* An expression should be constant in a context and faithful evaluation is not possible. Performing plain FP evaluation. */
#define SOLLYA_MSG_FAITHFUL_ROUNDING_FOR_EXPR_THAT_SHOULD_BE_CONST  52       /* Taking a faithful rounding for an expression that should be a constant. */
#define SOLLYA_MSG_CONSTANT_IS_NOT_MACHINE_INTEGER_WILL_ROUND       53       /* A constant that should be an integer is not a machine integer. The nearest machine integer will be used instead. */
#define SOLLYA_MSG_PRECISION_OF_NUMBERS_MUST_BE_AT_LEAST_TWO_BITS   54       /* The precision of numbers must be at least 2 bits. Will use 2 bits of precision. */
#define SOLLYA_MSG_IDENTIFIER_ALREADY_BOUND                         55       /* An identifier is already bound to the free variable, to a library function, library constant or to an external procedure. */
#define SOLLYA_MSG_IDENTIFIER_REASSIGNMENT                          56       /* An identifier has already been assigned. This assignment is a reassignment. */
#define SOLLYA_MSG_DISPLAYED_VALUE_IS_FAITHFULLY_ROUNDED            57       /* A rounding has happened but the displayed value is a faithful rounding of the true result. */
#define SOLLYA_MSG_EXPRESSION_UNDEFINED_OR_UNSTABLE                 58       /* The given expression is undefined or numerically unstable. */
#define SOLLYA_MSG_ROUNDING_MAY_HAVE_HAPPENED_AND_NOT_FAITHFUL      59       /* Rounding may have happened and if there is rounding, the displayed value is not guaranteed to be a faithful rounding of the true result. */
#define SOLLYA_MSG_EVALUATION_WITH_PLAIN_FP_ARITHMETIC              60       /* The displayed value has been computed using plain floating-point arithmetic and might be completely wrong. */
#define SOLLYA_MSG_ROUNDING_MAY_HAVE_HAPPENED_SOMEWHERE             61       /* Rounding may have happened. */
#define SOLLYA_MSG_EXPRESSION_TOO_BIG_FOR_HORNER_FORM               62       /* The expression is too big for being written in Horner form. */
#define SOLLYA_MSG_EXPRESSION_TOO_BIG_FOR_CANONICAL_FORM            63       /* The expression is too big for being written in canonical form. */
#define SOLLYA_MSG_DOUBLE_SIMPLIFICATION_NECESSARY                  64       /* A double simplification is necessary. */
#define SOLLYA_MSG_COMMAND_NOT_EXECUTABLE                           65       /* The last command could not be executed. May leak memory. */
#define SOLLYA_MSG_TIMER_UNUSABLE                                   66       /* Unable to use the timer. Measures may be untrustable. */
#define SOLLYA_MSG_CAN_MODIFY_ONLY_ELEMENTS_OF_STRUCTURES           67       /* Cannot modify an element of something that is not a structure. */
#define SOLLYA_MSG_CONTROL_STRUCTURE_NOT_EXECUTABLE_EXPR_NO_BOOLEAN 68       /* The given expression does not evaluate to a boolean. */
#define SOLLYA_MSG_AT_END_OF_FOR_CNTRL_VAR_NO_LONGER_ASSIGNABLE     69       /* At the end of a for loop, the loop variable cannot longer be assigned to. */
#define SOLLYA_MSG_AT_END_OF_FOR_CNTRL_VAR_NO_LONGER_CONSTANT       70       /* At the end of a for loop, the loop variable decreased by the loop step does no longer evaluate to a constant. */
#define SOLLYA_MSG_TOOL_HAS_BEEN_RESTARTED_INSIDE_LOOP              71       /* The tool has been restarted inside a loop. */
#define SOLLYA_MSG_CNTRL_VAR_OF_LOOP_CANNOT_BE_ASSIGNED             72       /* The control variable of a loop cannot be assigned to. */
#define SOLLYA_MSG_ARGS_OF_FOR_LOOP_NOT_CONSTANT                    73       /* At least one of the arguments of a loop does not evaluate to a constant. */
#define SOLLYA_MSG_FOR_IN_LOOP_OVER_EMPTY_LIST                      74       /* Executing a for in statement on an empty list. */
#define SOLLYA_MSG_FOR_IN_LOOP_OVER_END_ELLIPTIC_LIST_NOT_ALLOWED   75       /* The given expression does not evaluate to a non-elliptic list. */
#define SOLLYA_MSG_AT_LEAST_ONE_OPERATION_MUST_BE_EXECUTED          76       /* At least one operation must be executed. */
#define SOLLYA_MSG_EXPR_DOES_NOT_EVALUATE_TO_MACHINE_INTEGER        77       /* A given expression does not evaluate to a machine integer. */
#define SOLLYA_MSG_RESTART_IN_FILE_READ_INTO_ANOTHER                78       /* A quit command has been used in a file read into another. */
#define SOLLYA_MSG_QUIT_IN_FILE_READ_INTO_ANOTHER                   79       /* A restart command has been used in a file read into another. */
#define SOLLYA_MSG_IDENTIFIER_IS_FREE_VAR_CANNOT_BE_LOCAL_VAR       80       /* An identifier is already bound to the current free variable. It cannot be declared as a local variable. */
#define SOLLYA_MSG_IDENTIFIER_IS_LIBRARY_FUNC_CANNOT_BE_LOCAL_VAR   81       /* An identifier is already bound to a library function. It cannot be declared as a local variable. */
#define SOLLYA_MSG_IDENTIFIER_IS_LIBRARY_CONST_CANNOT_BE_LOCAL_VAR  82       /* An identifier is already bound to a library constant. It cannot be declared as a local variable. */
#define SOLLYA_MSG_IDENTIFIER_IS_EXTERNAL_PROC_CANNOT_BE_LOCAL_VAR  83       /* An identifier is already bound to an external procedure. It cannot be declared as a local variable. */
#define SOLLYA_MSG_FRAME_SYSTEM_CORRUPTED_LOCAL_VAR_NOT_DECLARED    84       /* Previous command interruptions have corrupted the frame system. Some local variable cannot be declared. */
#define SOLLYA_MSG_FILE_COULD_NOT_BE_OPENED_FOR_WRITING             85       /* A file could not be opened for writing. */
#define SOLLYA_MSG_EXPR_DOES_NOT_EVALUATE_TO_STRING                 86       /* A given expression does not evaluate to a string. */
#define SOLLYA_MSG_EXPR_DOES_NOT_EVALUATE_TO_LIST_OF_FUNCTIONS      87       /* A given expression does not evaluate to a list of pure functions. */
#define SOLLYA_MSG_EXPR_DOES_NOT_EVALUATE_TO_RANGE                  88       /* A given expression does not evaluate to a range. */
#define SOLLYA_MSG_EXPR_DOES_NOT_EVALUATE_TO_STRING_NOR_DEFAULT     89       /* A given expression does not evaluate to a string nor to a default value. */
#define SOLLYA_MSG_IMPLEMENTATION_HAS_NOT_SUCCEEDED                 90       /* The implementation has not succeeded. */
#define SOLLYA_MSG_EXPR_DOES_NOT_EVALUATE_TO_CONSTANT               91       /* A given expression does not evaluate to a constant. */
#define SOLLYA_MSG_EXPR_DOES_NOT_EVALUATE_TO_AN_EXPRESSION          92       /* A given expression does not evaluate to an expression. */
#define SOLLYA_MSG_EXPR_DOES_NOT_EVALUATE_TO_A_FUNCTION             93       /* A given expression does not evaluate to a function. */
#define SOLLYA_MSG_ROUNDING_WHILE_PRINTING                          94       /* A rounding occurred while printing. */
#define SOLLYA_MSG_BASH_RETURNS_A_CERTAIN_RETURN_VALUE              95       /* After executing a command, bash returns a certain return value. */
#define SOLLYA_MSG_EXPR_DOES_NOT_EVALUATE_TO_ABS_NOR_REL            96       /* A given expression does not evaluate to neither absolute nor relative. */
#define SOLLYA_MSG_FILE_COULD_NOT_BE_OPENED_FOR_APPENDING           97       /* A file could not be opened for appending. */
#define SOLLYA_MSG_FILE_COULD_NOT_BE_OPENED_FOR_READING             98       /* A file could not be opened for reading. */
#define SOLLYA_MSG_FREE_VARIABLE_HAS_BEEN_NAMED_SOMEHOW             99       /* A certain name has been given to the free variable. */
#define SOLLYA_MSG_FREE_VARIABLE_HAS_BEEN_RENAMED                  100       /* The free variable has been renamed. */
#define SOLLYA_MSG_CAN_RENAME_ONLY_FREE_VARIABLE                   101       /* Only the free variable can be renamed. A variable with a different name cannot be renamed. */
#define SOLLYA_MSG_IDENTIFIER_IS_FREE_VAR_CANNOT_BE_EXTERNAL       102       /* An identifier is already bound to the current free variable. It cannot be bound to an external procedure. */
#define SOLLYA_MSG_IDENTIFIER_IS_BOUND_TO_VAR_CANNOT_BE_EXTERNAL   103       /* An identifier is already bound to some identifier. It cannot be bound to an external procedure. */
#define SOLLYA_MSG_IDENTIFIER_IS_LIBRARY_CONST_CANNOT_BE_EXTERNAL  104       /* An identifier is already bound to a library constant. It cannot be bound to an external procedure. */
#define SOLLYA_MSG_IDENTIFIER_IS_EXTERNAL_PROC_CANNOT_BE_EXTERNAL  105       /* An identifier is already bound to an external procedure. It cannot be bound to an external procedure. */
#define SOLLYA_MSG_ERROR_OCCURRED_COMMAND_NOT_EXECUTED             106       /* An error occurred. The command could not be executed. */
#define SOLLYA_MSG_ASSIGNMENT_WILL_HAVE_NO_EFFECT                  107       /* An assignment will have no effect. */
#define SOLLYA_MSG_ASSIGNMENT_OF_INDEXED_ELEMENTS_NOT_IN_RANGE     108       /* Assignments to indexed elements of lists are only allowed on indices in the existing range. */
#define SOLLYA_MSG_ASSIGNMENT_OF_INDEXED_EMPTY_LIST_ONLY_ON_ZERO   109       /* Assignments to indexed elements of empty lists are only allowed on index 0. */
#define SOLLYA_MSG_STRING_NOT_OF_LENGTH_ONE                        110       /* The given string is not of length one. */
#define SOLLYA_MSG_IDENTIFIER_NOT_BOUND_TO_LIST_OR_STRING          111       /* A certain identifier is not bound to a list or to a string. */
#define SOLLYA_MSG_IDENTIFIER_NOT_ASSIGNED_TO                      112       /* A certain identifier is not assigned to anything. */
#define SOLLYA_MSG_FIRST_ELMENT_OF_LEFT_SIDE_NOT_IDENTIFIER        113       /* The first element of a left-hand side is not an identifier. */
#define SOLLYA_MSG_LEFT_HAND_SIDE_NOT_ELEMENT_OF_STRUCTURED_TYPE   114       /* The left-hand side is not an access to an element of a structured type. */
#define SOLLYA_MSG_IDENTIFIER_IS_FREE_VAR_CANNOT_BE_LIBRARY        115       /* An identifier is already bound to the current free variable. It cannot be bound to a library function or constant. */
#define SOLLYA_MSG_IDENTIFIER_IS_BOUND_TO_VAR_CANNOT_BE_LIBRARY    116       /* An identifier is already bound to some identifier. It cannot be bound to a library function or constant. */
#define SOLLYA_MSG_IDENTIFIER_IS_LIBRARY_CONST_CANNOT_BE_LIBRARY   117       /* An identifier is already bound to a library constant. It cannot be bound to a library function or constant. */
#define SOLLYA_MSG_IDENTIFIER_IS_LIBRARY_FUNC_CANNOT_BE_LIBRARY    118       /* An identifier is already bound to a library constant. It cannot be bound to a library function or constant. */
#define SOLLYA_MSG_IDENTIFIER_IS_EXTERNAL_PROC_CANNOT_BE_LIBRARY   119       /* An identifier is already bound to an external procedure. It cannot be bound to a library function or constant. */
#define SOLLYA_MSG_PREC_MUST_BE_AT_LEAST_TWELVE_BITS               120       /* The precision of the tool must be at least 12 bits. */
#define SOLLYA_MSG_POINTS_MUST_BE_AT_LEAST_THREE_POINTS            121       /* The number of points must be at least 3 points. */
#define SOLLYA_MSG_EXPR_DOES_NOT_EVALUATE_TO_DISPLAY_TYPE          122       /* A given expression does not evaluate to either default, dyadic, powers, hexadecimal or binary. */
#define SOLLYA_MSG_VERBOSITY_MUST_NOT_BE_NEGATIVE                  123       /* The verbosity of the tool must not be negative. */
#define SOLLYA_MSG_EXPR_DOES_NOT_EVALUATE_TO_ON_OR_OFF             124       /* A given expression does not evaluate to either on or off. */
#define SOLLYA_MSG_TAYLOR_RECURSIONS_MUST_NOT_BE_NEGATIVE          125       /* The number of Taylor recursions must not be negative. */
#define SOLLYA_MSG_HOPITAL_RECURSIONS_MUST_NOT_BE_NEGATIVE         126       /* The number of Hopital recursions must not be negative. */
#define SOLLYA_MSG_EXPR_OR_COMMAND_COULD_NOT_BE_HANDLED            127       /* A given expression or command could not be handled. */
#define SOLLYA_MSG_EXPR_NOT_CORRECTLY_TYPED                        128       /* At least one of the given expressions or a subexpression is not correctly typed or its evaluation has failed because of some error on a side-effect. */
#define SOLLYA_MSG_EVALUATION_CREATES_ERROR_SPECIAL_SYMBOL         129       /* Evaluation creates an error special symbol. */
#define SOLLYA_MSG_EXPR_TOO_BIG_FOR_AUTOMATIC_SIMPLIFICATION       130       /* A given expression is too big to be treated by the automatic simplification. */
#define SOLLYA_MSG_FPMINIMAX_LESS_FORMATS_THAN_MONOMIALS           131       /* fpminimax: there are less formats indications than monomials. */
#define SOLLYA_MSG_FPMINIMAX_LESS_MONOMIALS_THAN_FORMATS           132       /* fpminimax: there are less monomials indications than formats. The list of formats will be truncated. */
#define SOLLYA_MSG_FPMINIMAX_FORMAT_LIST_MALFORMED                 133       /* fpminimax: the formats list must contain only integers or formats. */
#define SOLLYA_MSG_FPMINIMAX_FORMAT_NEGATIVE_FOR_FP_COEFFS         134       /* fpminimax: a format indication is non-positive while floating-point coefficients are desired. */
#define SOLLYA_MSG_QUIT_OR_RESTART_MUST_NOT_BE_IN_MATCH            135       /* A quit or restart command may not be part of the body of a match-with construct. */
#define SOLLYA_MSG_FRAME_SYSTEM_CORRUPTED_MATCH_NOT_EXECUTED       136       /* Previous command interruptions have corrupted the frame system. A match-with construct cannot be executed. */
#define SOLLYA_MSG_IDENTIFIER_IS_FREE_VAR_CANNOT_BE_MATCHED        137       /* An identifier is already bound to the current free variable. It cannot be used as a match variable. */
#define SOLLYA_MSG_IDENTIFIER_IS_EXTERNAL_PROC_CANNOT_BE_MATCHED   138       /* An identifier is already bound to an external procedure. It cannot be used as a match variable. */
#define SOLLYA_MSG_IDENTIFIER_IS_LIBRARY_CONST_CANNOT_BE_MATCHED   139       /* An identifier is already bound to a library constant. It cannot be used as a match variable. */
#define SOLLYA_MSG_IDENTIFIER_IS_LIBRARY_FUNC_CANNOT_BE_MATCHED    140       /* An identifier is already bound to a library constant. It cannot be used as a match variable. */
#define SOLLYA_MSG_NO_MATCHING_CASE_FOUND                          141       /* No matching expression found in a match-with construct and no default case given. */
#define SOLLYA_MSG_QUIT_OR_RESTART_MUST_NOT_BE_IN_PROC             142       /* A quit or restart command may not be part of a procedure body. */
#define SOLLYA_MSG_IDENTIFIER_IS_FREE_VAR_CANNOT_BE_PARAMETER      143       /* An identifier is already bound to the current free variable. It cannot be used as a formal parameter of a procedure. */
#define SOLLYA_MSG_IDENTIFIER_IS_EXTERNAL_PROC_CANNOT_BE_PARAMETER 144       /* An identifier is already bound to an external procedure. It cannot be used as a formal parameter of a procedure. */
#define SOLLYA_MSG_IDENTIFIER_IS_LIBRARY_CONST_CANNOT_BE_PARAMETER 145       /* An identifier is already bound to a library constant. It cannot be used as a formal parameter of a procedure. */
#define SOLLYA_MSG_IDENTIFIER_IS_LIBRARY_FUNC_CANNOT_BE_PARAMETER  146       /* An identifier is already bound to a library constant. It cannot be used as a formal parameter of a procedure. */
#define SOLLYA_MSG_FRAME_SYSTEM_CORRUPTED_PROC_NOT_EXECUTED        147       /* Previous command interruptions have corrupted the frame system. A procedure cannot be executed. */
#define SOLLYA_MSG_REMEZ_MONOMIAL_DEGREES_MUST_NOT_BE_NEGATIVE     148       /* Monomial degrees must be non-negative. */
#define SOLLYA_MSG_REMEZ_MONOMIAL_DEGREE_GIVEN_TWICE               149       /* A monomial degree is given twice in argument to Remez algorithm. */
#define SOLLYA_MSG_REMEZ_TOO_MANY_ARGUMENTS                        151       /* Too many arguments given to remez command. The remaining arguments will be ignored. */
#define SOLLYA_MSG_REMEZ_SECND_ARG_MUST_BE_NONNEGATIVE_INT_OR_LIST 152       /* The second argument of remez must be a non-negative integer or a list. */
#define SOLLYA_MSG_FPMINIMAX_TOO_MANY_ARGUMENTS                    153       /* Too many arguments given to fpminimax command. The remaining arguments will be ignored. */
#define SOLLYA_MSG_INVALID_FIFTH_ARGUMENT                          154       /* fpminimax: invalid fifth argument */
#define SOLLYA_MSG_FPMINIMAX_SECND_ARG_MUST_BE_NONNEG_INT_OR_LIST  155       /* The second argument of fpminimax must be a non-negative integer or a list. */
#define SOLLYA_MSG_FPMINIMAX_THIRD_ARG_MUST_BE_FORMAT_INDICATIONS  156       /* fpminimax: the third argument of fpminimax must be a list of formats indications. */
#define SOLLYA_MSG_FPMINIMAX_FOURTH_ARG_INTERVAL_OR_LIST_OF_POINTS 157       /* fpminimax: the fourth argument of fpminimax must be either an interval or a list of points. */
#define SOLLYA_MSG_TEST_COMPARES_ERROR_TO_SOMETHING                158       /* The evaluation of one of the sides of a test yields error due to a syntax error or an error on a side-effect. The other side either also yields error due to an syntax or side-effect error or does not evaluate to error. The boolean returned may be meaningless. */
#define SOLLYA_MSG_TEST_RELIES_ON_FP_RESULT_THAT_IS_NOT_FAITHFUL   159       /* A test relies on floating-point result that is not faithfully evaluated. */
#define SOLLYA_MSG_TEST_RELIES_ON_FP_RESULT                        160       /* A test relies on floating-point result that is faithfully rounded or not. */
#define SOLLYA_MSG_TEST_RELIES_ON_FP_RESULT_FAITHFUL_BUT_TOGGLING  161       /* A test relies on floating-point result that is faithfully evaluated and different faithful roundings toggle the result. */
#define SOLLYA_MSG_TEST_RELIES_ON_FP_RESULT_FAITHFUL_BUT_NOT_REAL  162       /* A test relies on floating-point result that is faithfully evaluated and at least one of the sides is not a real number. */
#define SOLLYA_MSG_MIN_RELIES_ON_FP_RESULT_THAT_IS_NOT_FAITHFUL    163       /* A minimum computation relies on floating-point result that is not faithfully evaluated. */
#define SOLLYA_MSG_MIN_RELIES_ON_FP_RESULT                         164       /* A minimum computation relies on floating-point result that is faithfully rounded or not. */
#define SOLLYA_MSG_MIN_RELIES_ON_FP_RESULT_FAITHFUL_BUT_TOGGLING   165       /* A minimum computation relies on floating-point result that is faithfully evaluated and different faithful roundings toggle the result. */
#define SOLLYA_MSG_MAX_RELIES_ON_FP_RESULT_THAT_IS_NOT_FAITHFUL    166       /* A maximum computation relies on floating-point result that is not faithfully evaluated. */
#define SOLLYA_MSG_MAX_RELIES_ON_FP_RESULT                         167       /* A maximum computation relies on floating-point result that is faithfully rounded or not. */
#define SOLLYA_MSG_MAX_RELIES_ON_FP_RESULT_FAITHFUL_BUT_TOGGLING   168       /* A maximum computation relies on floating-point result that is faithfully evaluated and different faithful roundings toggle the result. */
#define SOLLYA_MSG_ERROR_WHILE_EXECUTING_A_PROCEDURE               169       /* Some error occurred while executing a procedure. */
#define SOLLYA_MSG_DIFFERENTIATING_FOR_EVAL_AS_START_PREC_LOW      170       /* Formal differentiation is performed during evaluation because the start precision is low. */
#define SOLLYA_MSG_FREE_VAR_INTERPRETED_AS_IDENTITY_FUNCTION       171       /* The identifier for the free variable is used in a functional context. It will be interpreted as the identity function. */
#define SOLLYA_MSG_EXTERNAL_PROCEDURE_SIGNALED_FAILURE             172       /* An external procedure has signaled failure. */
#define SOLLYA_MSG_PRECISION_OF_NUMS_MUST_BE_AT_LEAST_TWELVE_BITS  173       /* The precision of numbers in the tool must be at least 12 bits. */
#define SOLLYA_MSG_ROUNDING_OCCURRED_WHILE_READING_A_CONSTANT      174       /* A rounding occurred while reading a constant. */
#define SOLLYA_MSG_RANGE_BOUNDS_IN_INVERSE_ORDER                   175       /* Range bounds are given in inverse order. They will get reverted. */
#define SOLLYA_MSG_LITERAL_STRUCTURE_CONTAINS_ENTRY_TWICE          176       /* A literal structure contains at least one entry twice. This is not allowed. */
#define SOLLYA_MSG_NOT_LEAST_POSSIBLE_INCLUSION_INTERVAL           177       /* Upon some evaluation, inclusion property is satisfied but the diameter may be greater than the least possible. */
#define SOLLYA_MSG_ONLY_ONE_ENDPOINT_OF_RANGE_IS_NAN               178       /* One bound of a range is NaN while the other is not. Will normalize the range to have two NaN endpoints. */
#define SOLLYA_MSG_TREE_IS_CONSTANT_BUT_CANNOT_DO_FAITHFUL_EVAL    179       /* A given tree is constant but cannot be faithfully evaluated. */
#define SOLLYA_MSG_TIMED_COMMAND_HAS_QUIT_THE_TOOL                 180       /* A command executed in a timed environment required quitting the tool. This is not possible. The quit command has been discarded. */
#define SOLLYA_MSG_PARAM_OF_PROCEDURE_DOES_NOT_EXIST               181       /* A given procedure has no argument named as indicated. The procedure is returned unchanged. */
#define SOLLYA_MSG_AUTODIFF_DEGREE_MUST_NOT_BE_NEGATIVE            182       /* The degree of differentiation for automatic differentiation must not be negative. */
#define SOLLYA_MSG_EXPR_IS_NO_FRACTION                             183       /* A given expression is not a fraction. Will consider it as a fraction with denominator 1. */
#define SOLLYA_MSG_NO_ROUNDING_HAS_HAPPENED                        184       /* No rounding has happened. */
#define SOLLYA_MSG_ROUND_UP_HAS_HAPPENED                           185       /* Round-up has happened. */
#define SOLLYA_MSG_ROUND_DOWN_HAS_HAPPENED                         186       /* Round-down has happened. */
#define SOLLYA_MSG_XML_FILE_CANNOT_BE_READ                         187       /* A file could not be read in XML format. */
#define SOLLYA_MSG_FILE_COULD_NOT_BE_OPENED_FOR_WRITING_IGNORING   188       /* A file could not be opened for writing. Ignoring a proof argument. */
#define SOLLYA_MSG_SUPNORM_DID_NOT_WORK_OUT_WELL                   189       /* The supremum norm on the error function between the given polynomial and the given function could not be computed. */
#define SOLLYA_MSG_GUESSDEGREE_FIFTH_ARGUMENT_MUST_BE_NUMBER       190       /* guessdegree: the optional fifth argument must be a positive number. */
#define SOLLYA_MSG_ROUND_TO_NEAREST_IMPOSSIBLE_WITH_BOUNDING       191       /* A correct rounding to nearest is impossible with the given enclosure. */
#define SOLLYA_MSG_OUT_OF_CURRENT_EXPONENT_RANGE                   192       /* A certain value is out of the current exponent range. Displayed values may be wrong. */
#define SOLLYA_MSG_INADVERTED_ROUNDING_WHILE_DISPLAYING            193       /* An inadverted rounding happened while displaying a value. The displayed value may be wrong. */
#define SOLLYA_MSG_EXPRESSION_HAS_BEEN_SIMPLIFIED                  194       /* An expression has been simplified. */
#define SOLLYA_MSG_EXPRESSION_HAS_BEEN_SIMPLIFIED_TO_ANOTHER_ONE   195       /* An expression has been simplified to another expression. */
#define SOLLYA_MSG_FORMALLY_DIFFERENTIATING_AN_EXPRESSION          196       /* An expression gets formally differentiated. */
#define SOLLYA_MSG_FORMALLY_DIFFERENTIATING_A_PARTICULAR_EXPR      197       /* A particular expression gets formally differentiated. */
#define SOLLYA_MSG_EXPR_TOO_BIG_FOR_SIMPLIFICATION_BEFORE_DIFF     198       /* An expression is too big to be simplified before it gets formally differentiated. */
#define SOLLYA_MSG_DEGREE_OF_POLYNOMIAL_DOESNT_HOLD_ON_MACHINE_INT 199       /* The degree of a certain polynomial does not hold on a machine integer. */
#define SOLLYA_MSG_DEG_OF_MAX_POLY_DIV_DOESNT_HOLD_ON_MACHINE_INT  200       /* The degree of a the maximal polynomial divider a certain expression does not hold on a machine integer. */
#define SOLLYA_MSG_ROUNDING_UPON_BINOMIAL_COEFFICIENT_COMPUTATION  201       /* A rounding occurred while computing a binomial coefficient. */
#define SOLLYA_MSG_ROUNDING_UPON_POW_EXPONENT_COMPUTATION          202       /* A rounding occurred while computing the exponent of an expanded power operator. */
#define SOLLYA_MSG_RECURSION_ON_POLY_COEFFICIENTS_EXTRACTION       203       /* Recursion has been necessary while extracting the coefficients of a polynomial. */
#define SOLLYA_MSG_POLY_COEFF_EXTRACTION_SPECIAL_ALGO_FOR_HORNER   204       /* A special algorithm for Horner forms is used when extracting the coefficients of a polynomial. */
#define SOLLYA_MSG_POLY_COEFF_EXTRACT_SPECIAL_ALGO_FOR_CANONICAL   205       /* A special algorithm for canonical forms is used when extracting the coefficients of a polynomial. */
#define SOLLYA_MSG_TRIED_TO_EXTRACT_COEFFS_OF_STH_NOT_POLYNOMIAL   206       /* A try was made to extract the coefficients of an expression that is not a polynomial. */
#define SOLLYA_MSG_EXPR_NOT_HORNERIZED_AS_ALREADY_HORNERIZED       207       /* A certain expression is not hornerized as it is already in Horner form. */
#define SOLLYA_MSG_ROUNDING_UPON_DIFFERENTIATION_OF_HORNER_POLY    208       /* Rounding has inadvertedly happened upon differentiation of an expression that was written in Horner form. */
#define SOLLYA_MSG_DIFFERENTIATION_USES_SPECIAL_ALGO_FOR_HORNER    209       /* A special algorithm for Horner forms is used when differentiating a Horner polynomial. */
#define SOLLYA_MSG_DIFFERENTIATION_USES_SPECIAL_ALGO_FOR_CANONICAL 210       /* A special algorithm for canonical forms is used when differentiating a canonically written polynomial. */
#define SOLLYA_MSG_ROUNDING_UPON_DIFFERENTIATION_OF_POLYNOMIAL     211       /* Rounding has inadvertedly happened upon differentiation of a polynomial. */
#define SOLLYA_MSG_EXPR_NOT_CANONICALIZED_AS_ALREADY_CANONICAL     212       /* A certain expression is not canonicalized as it is already in canonical form. */
#define SOLLYA_MSG_NO_COMMAND_PROVIDED                             213       /* No command has been provided. */
#define SOLLYA_MSG_ERROR_WHILE_CREATING_A_PIPE                     214       /* Error while creating a pipe. */
#define SOLLYA_MSG_ERROR_WHILE_FORKING                             215       /* Error while forking. */
#define SOLLYA_MSG_UNABLE_TO_WRITE_TO_BASH                         216       /* Unable to write to a bash command that has been forked. */
#define SOLLYA_MSG_THE_EXIT_CODE_OF_CHILD_PROCESS_IS               216       /* A child process has exited with a certain exit code. */
#define SOLLYA_MSG_SAMPLING_PREC_MUST_BE_LOWER_THAN_CURR_PREC      217       /* The sampling precision must be lower than the current precision of the tool. */
#define SOLLYA_MSG_EXTERNALPLOT_COULD_NOT_OPEN_A_LIBRARY           218       /* Externalplot could not open a library for some reason. */
#define SOLLYA_MSG_EXTERNALPLOT_DID_NOT_FIND_FUNCTION_F            219       /* Externalplot did not find function f in the library. */
#define SOLLYA_MSG_COULD_NOT_OPEN_PLOT_FILE                        220       /* A certain plot file could not be opened. */
#define SOLLYA_MSG_A_FUNCTION_COULD_NOT_BE_PLOTTED_AT_A_POINT      221       /* A function could not be plotted at a certain point. */
#define SOLLYA_MSG_TOOL_DIES_ON_ERROR_AS_PER_DIE_ON_ERROR_MODE     222       /* The tool is going to die on an error as die-on-error mode is activated. */
#define SOLLYA_MSG_ERROR_ON_INITIAL_SETUP                          223       /* An error occurred on initial setup of the tool. */
#define SOLLYA_MSG_FRAME_STACK_HAS_BEEN_CORRUPTED                  224       /* The frame stack has been corrupted. */
#define SOLLYA_MSG_TIMING_STACK_HAS_BEEN_CORRUPTED                 225       /* The timing stack has been corrupted. */
#define SOLLYA_MSG_LAST_COMMAND_INTERRUPTED                        226       /* The last command has been interrupted. May leak memory. */
#define SOLLYA_MSG_RELEASING_FRAME_STACK                           227       /* The variable frame stack has been released. */
#define SOLLYA_MSG_COEFF_NOT_TWICE_GREATER_THAN_SUBPOLY            228       /* A coefficient is not at least 2 times greater than a already evaluated sub-polynomial. */
#define SOLLYA_MSG_PREC_OF_HORNER_STEP_GREATER_THAN_FOR_PREV_ONE   229       /* The precision of a previous Horner step is greater than the one of the next. */
#define SOLLYA_MSG_NO_AUTO_ROUND_FOR_COEFF_W_PREC_HIGHER_THAN_TD   230       /* A coefficient's precision is higher than triple-double but no automatic rounding will be performed. */
#define SOLLYA_MSG_INFERED_COEFF_PREC_HIGHER_THAN_REQUIRED         231       /* The infered precision of a certain coefficient of the polynomial is greater than the necessary precision computed for this step. */
#define SOLLYA_MSG_COEFF_HAS_BEEN_ROUNDED_TO_TRIPLE_DOUBLE         232       /* A coefficient of the polynomial has automatically been rounded to a triple-double. */
#define SOLLYA_MSG_COEFF_HAS_BEEN_ROUNDED_TO_DOUBLE_DOUBLE         233       /* A coefficient of the polynomial has automatically been rounded to a double-double. */
#define SOLLYA_MSG_COEFF_HAS_BEEN_ROUNDED_TO_DOUBLE                234       /* A coefficient of the polynomial has automatically been rounded to a double. */
#define SOLLYA_MSG_ERROR_ON_HANDLING_A_COEFFICIENT                 235       /* There was an error during the internal handling of a coefficient. */
#define SOLLYA_MSG_IMPLEMENTED_POLY_DIFFERS_FROM_ORIGINAL_ONE      236       /* During implementation, at least one coefficient of a given polynomial has been rounded so that the implemented polynomial differs from the original one. */
#define SOLLYA_MSG_COEFF_DOES_NOT_EVEN_HOLD_ON_TRIPLE_DOUBLE       237       /* Tried to implement a coefficient that cannot even be written on a triple-double. */
#define SOLLYA_MSG_ROUNDING_ON_INTERNAL_HANDLING_OF_A_COEFFICIENT  238       /* A rounding occurred on the internal handling of a coefficient. */
#define SOLLYA_MSG_A_COEFF_COULD_NOT_BE_STORED_IN_ANY_KNOWN_FORMAT 239       /* At least one of the coefficients of the given polynomial could not be stored in any known format. */
#define SOLLYA_MSG_IMPLEMENTPOLY_FREE_VAR_HAS_UNKNOWN_FORMAT       240       /* The free variable is not associated to any known format in implementpoly. */
#define SOLLYA_MSG_ERROR_IN_PRECISION_MANAGEMENT                   241       /* An error occurred in the internal management of precisions. */
#define SOLLYA_MSG_CURRENT_PREC_INSUFFICIENT_FOR_TD_CODE           242       /* The current tool's precision is not sufficient for implementing triple-double code. */
#define SOLLYA_MSG_TARGET_ACCURACY_GREATER_OR_EQUAL_THAN_ONE       243       /* The target accuracy is greater than or equal to 1. This make no sense. */
#define SOLLYA_MSG_TARGET_ACCURACY_LESS_THAN_140_BITS              244       /* The target accuracy is less than 2^(-140). Implementation is restricted to maximally triple-double. */
#define SOLLYA_MSG_INFERED_OUTPUT_PREC_LESS_THAN_VARIABLE_PREC     245       /* The infered output expansion type is less from the given variable type. */
#define SOLLYA_MSG_COEFF_DOES_NOT_HOLD_ON_TD_USING_FAITHFUL_EVAL   246       /* A coefficient of the given polynomial cannot exactly be represented on a triple-double. It will be evaluated first, using faithful rounding. */
#define SOLLYA_MSG_ERROR_ON_DETERMINING_THE_REQUIRED_PRECISIONS    247       /* An error occurred upon determination of the required precisions. */
#define SOLLYA_MSG_ERROR_ON_DETERMINING_THE_REQUIRED_POWERS        248       /* An error occurred upon determination of the required powers. */
#define SOLLYA_MSG_THE_POLY_THAT_GETS_IMPLEMENTED_IS               249       /* A certain polynomial is obtained after rounding. This is the one that will get implemented. */
#define SOLLYA_MSG_ERROR_ON_CODE_GENERATION_FOR_COEFFICIENTS       250       /* An error occurred upon code generation for the polynomial's coefficients. */
#define SOLLYA_MSG_COULD_NOT_WRITE_TO_THE_IMPLEMENTATION_FILE      251       /* The implementation file could not be written to. */
#define SOLLYA_MSG_ERROR_ON_CODE_GENERATION_FOR_POWERS_OF_FREE_VAR 252       /* An error occurred upon code generation for the powers of the free variable. */
#define SOLLYA_MSG_ERROR_ON_CODE_GENERATION_FOR_HORNER_SCHEME      253       /* An error occurred upon code generation for the Horner scheme. */
#define SOLLYA_MSG_EXPR_SEEMS_TO_BE_ZERO_INCREASE_PREC             254       /* An expression seems to be exactly zero. If it is not, try to increase the tool precision. */
#define SOLLYA_MSG_A_BASE_FUNC_IS_NOT_SUPPORTED_BY_IMPLEMENTCONST  255       /* A certain base function is not supported by implementconst. */
#define SOLLYA_MSG_XML_PARSER_CHANGE                               256       /* There is a change of the current XML parser. */
#define SOLLYA_MSG_XML_PARSER_INDEX_CHANGE                         257       /* There is a change in the index of the current XML parser. */
#define SOLLYA_MSG_XML_PARSER_STATE_INFORMATION                    258       /* The XML parser prints some information of its current state. */
#define SOLLYA_MSG_ROUNDING_ON_READING_CONSTANT_IN_XML_FILE        259       /* Rounding has happened on reading a constant in an XML file. */
#define SOLLYA_MSG_XML_PARSER_FAILURE                              260       /* Failed to parse a certain XML file. */
#define SOLLYA_MSG_XML_SYNCHRONIZATION_LOST_TRYING_TO_RESYNCH      261       /* The XML parser has lost synchronization and is trying to resynchronize. */
#define SOLLYA_MSG_XML_PARSER_UNABLE_TO_OPEN_A_CERTAIN_FILE        262       /* The XML parser cannot open a certain file. */
#define SOLLYA_MSG_XML_PARSE_FUNCTIONALITY_NOT_COMPILED_IN         263       /* A certain XML file cannot be read because XInclude functionnality has not been compiled in. */
#define SOLLYA_MSG_EXPR_DOES_NOT_EVALUATE_TO_INTEGER               264       /* A given expression does not evaluate to an integer. */
#define SOLLYA_MSG_ROUNDING_ON_CONVERTING_A_MACHINE_INTEGER        265       /* A rounding has occurred during the conversion of a machine integer. */
#define SOLLYA_MSG_HARMLESS_ERROR_OCCURRED_COMMAND_NOT_EXECUTED    266       /* An error occurred. The last command will not succeed. This is harmless. */
#define SOLLYA_MSG_INPUT_AND_OUTPUT_PRECISION_MUST_BE_GREATER_TEN  267       /* The input and output precisions must be greater than 10. */
#define SOLLYA_MSG_INTERNAL_PREC_LESS_THAN_IN_AND_OUT_PREC         268       /* The internal precision must not be less than the input and output precisions. */
#define SOLLYA_MSG_EPS_SPECIFIED_GREATER_THAN_HALFULP_OF_OUT_PREC  269       /* The specified epsilon is greater than half an ulp of the specified output format. */
#define SOLLYA_MSG_GIVEN_EPS_MUST_BE_POSITIVE_TAKING_ABS           270       /* The specified epsilon value must be positive. Taking its absolute value. */
#define SOLLYA_MSG_CERTAIN_AMOUNT_OF_CASES_HANDLED                 271       /* A certain amount of cases has been handled. */
#define SOLLYA_MSG_FUNC_EVALUATED_TO_ZERO_TAKING_ABSOLUTE_ERROR    272       /* The given function evaluates to zero at a certain point. Considering an absolute error instead of a relative error at this point. */
#define SOLLYA_MSG_CANNOT_PERFORM_MORE_THAN_63_STEPS               273       /* A certain command cannot perform more than 63 steps. Will decrease the number of steps to 63. */
#define SOLLYA_MSG_SEARCH_PREC_HIGHER_THAN_TOOL_PREC               274       /* The required search precision is higher that the current tool precision. No search is possible. */
#define SOLLYA_MSG_NUMBERS_OF_FUNCS_AND_FORMATS_DIFFER             275       /* The numbers of the given functions, formats and accuracies differ. No search is possible. */
#define SOLLYA_MSG_START_POINT_TOO_PRECISE_FOR_GIVEN_INPUT_PREC    276       /* The given start point is too precise for the given search precision. It gets rounded beforehand. */
#define SOLLYA_MSG_DEGREE_OF_TAYLORFORM_MUST_BE_AT_LEAST_ZERO      271       /* The degree of a Taylor form must be at least zero. */
#define SOLLYA_MSG_ERROR_IN_TAYLORFORM_MULTIPLYING_INCOMPAT_MODELS 272       /* Error in Taylor form computation: multiplication of incompatible models. */
#define SOLLYA_MSG_ERROR_IN_TAYLORFORM_UNKNOWN_FUNC_FOR_ZUMKELLER  273       /* Error in Taylor form computation: unkown type of function used with Zumkeller's technique. */
#define SOLLYA_MSG_ERROR_IN_TAYLORFORM_TRYING_TO_INCREASE_DEGREE   274       /* Error in Taylor form computation: trying to increase the degree of a model. */
#define SOLLYA_MSG_DEVELOPMENT_POINT_NOT_CONSTANT                  275       /* The expression given as a development point is not constant. */
#define SOLLYA_MSG_ROUNDING_ON_COMPUTATION_OF_TAYLOR_COEFFICIENT   276       /* A rounding occurred while computing the constant factor of a Taylor coefficient. */
#define SOLLYA_MSG_ROUNDING_ON_COMPUTATION_OF_TAYLOR_POWER         277       /* A rounding occurred while computing the exponent of a power in a Taylor development. */
#define SOLLYA_MSG_A_CHARACTER_COULD_NOT_BE_RECOGNIZED             278       /* A certain character could not be recognized while lexing. */
#define SOLLYA_MSG_A_FILE_COULD_NOT_BE_OPENED_FOR_READING          279       /* A certain file could not be opened for reading. */
#define SOLLYA_MSG_SPACES_REMOVED_FROM_CONSTANT_IN_SCIENTIF_NOTAT  280       /* Spaces have been removed from a constant written in scientific notation. */
#define SOLLYA_MSG_SYNTAX_ERROR_ENCOUNTERED_WHILE_PARSING          281       /* Syntax error encountered while parsing. */
#define SOLLYA_MSG_SUPNORM_NO_TAYLOR                               282       /* During supnorm computation, no suitable Taylor form could be found. */
#define SOLLYA_MSG_SUPNORM_NOT_ENOUGH_WORKING_PRECISION            283       /* During supnorm computation, no result could be found as the working precision seems to be too low. */
#define SOLLYA_MSG_SUPNORM_SINGULARITY_NOT_REMOVED                 284       /* During supnorm computation, a singularity in the expression tree could not be removed. */
#define SOLLYA_MSG_SUPNORM_COULD_NOT_SHOW_POSITIVITY               285       /* During supnorm computation, the positivity of a polynomial could not be established. */
#define SOLLYA_MSG_SUPNORM_SINGULARITY_NOT_DETECTED                286       /* During supnorm computation, a false singularity could not be detected. */
#define SOLLYA_MSG_SUPNORM_ANOTHER_SINGULARITY_IN_DOM              287       /* During supnorm computation, there appeared to be at least two singularities in the domain. More bisection is needed. */
#define SOLLYA_MSG_SUPNORM_CANNOT_COMPUTE_LOWER_BOUND              288       /* During supnorm computation, it was not possible to determine a valid lower bound for the error function. */
#define SOLLYA_MSG_SUPNORM_CANNOT_COMPUTE_ABSOLUTE_INF             289       /* During supnorm computation, it was not possible to determine a valid lower bound for the absolute value of the function. */
#define SOLLYA_MSG_SUPNORM_CANNOT_DETERMINE_SIGN_OF_T              290       /* During supnorm computation, it was not possible to safely determine the sign of the Taylor polynomial. */
#define SOLLYA_MSG_SUPNORM_CANNOT_DETERMINE_ORDER_OF_SINGU         291       /* During supnorm computation, it was not possible to safely determine the order of a presume zero of the given function. */
#define SOLLYA_MSG_SUPNORM_GENERIC_ERROR                           292       /* During supnorm computation, some generic error occured. No further description is available. */
#define SOLLYA_MSG_SUPNORM_ACCURACY_TOO_HIGH                       292       /* For supnorm, the given accuracy depasses the current maximum precision. Try to increase the precision of the tool. */
#define SOLLYA_MSG_SUPNORM_COULD_NOT_FAITHFULLY_EVAL_ERROR_FUNC    293       /* During supnorm computation, the error function between the function and the polynomial could not faithfully be evaluated at some point. */
#define SOLLYA_MSG_DOMAIN_IS_NO_CLOSED_INTERVAL_ON_THE_REALS       294       /* The given domain is not a closed interval on the reals. */
#define SOLLYA_MSG_DOMAIN_IS_EMPTY                                 295       /* The given domain is empty. */
#define SOLLYA_MSG_DOMAIN_IS_REDUCED_TO_A_POINT_WILL_SIMPLY_EVAL   296       /* The given domain is reduced to a point. Will simply evaluate at this point. */
#define SOLLYA_MSG_SUPNORM_COULD_NOT_EVALUATE_ERROR_FUNC           297       /* During supnorm computation, the error function between the function and the polynomial could not be evaluated at some point. */
#define SOLLYA_MSG_ACCUARCY_INDICATION_IS_NOT_A_REAL_NUMBER        298       /* The given accuracy indication is not a real number. */
#define SOLLYA_MSG_ACCUARCY_INDICATION_IS_ZERO                     299       /* The given accuracy indication is zero. */
#define SOLLYA_MSG_POLYNOMIAL_HAS_NON_DYADIC_COEFFICIENTS          300       /* The given polynomials contains coefficients that are no dyadic numbers. */
#define SOLLYA_MSG_SUPNORM_SAFE_ENCLOSURE_COULD_NOT_BE_COMPUTED    301       /* An error occured during supremum norm computation. A safe enclosure of the supremum norm could not be computed. */
#define SOLLYA_MSG_STURM_INTERVAL_A_CERTAIN_PREC_HAS_BEEN_CHOSEN   302       /* During execution of Sturm's algorithm in interval arithmetic, a certain precision has been chosen. */
#define SOLLYA_MSG_STURM_COEFF_EVALUATED_TO_RATIONAL_NUMBER        303       /* A coefficient of the given polynomial has been evaluated to a certain rational number. */
#define SOLLYA_MSG_STURM_COEFF_NOT_CONSTANT_NOR_RATIONAL_ROUNDING  304       /* A coefficient of the given polynomial is neither a floating point or rational constant nor can be evaluated without rounding to a floating point constant. */
#define SOLLYA_MSG_STURM_COEFF_ROUNDED_TO_ZERO                     305       /* A coefficient of the given polynomial has been rounded to zero. */
#define SOLLYA_MSG_STURM_USING_SLOWER_ALGORITHM_ON_RATIONALS       306       /* Sturm's algorithm gets executed on rational numbers instead of being executed on intervals. */
#define SOLLYA_MSG_STURM_POLY_IS_ZERO_POLY                         307       /* The given polynomial is the zero polynomial. It has an infinite number of zeros in the interval. */
#define SOLLYA_MSG_CONSTANT_EXPR_CANNOT_BE_EVALUATED_AT_ALL        308       /* A certain constant expression cannot be evaluated at all. */
#define SOLLYA_MSG_PLOT_OVERFLOW_OCCURRED_ON_CONVERSION_TO_DOUBLE  309       /* An overflow occurred in a conversion mpfr to double while plotting. */
#define SOLLYA_MSG_PLOT_FUNC_PROVEN_LESS_THAN_2_TO_MINUS_PREC      310       /* While plotting a function, it was proven to be less than 2^(-prec) at some point, where prec is the current tool precision. It gets plotted with an ordinate inside the proof interval. */
#define SOLLYA_MSG_PLOT_FUNC_UNDEFINED_OR_UNSTABLE_AT_POINT        311       /* A function to be plotted is undefined or numerically unstable at some point. */
#define SOLLYA_MSG_PLOT_NOT_FAITHFULLY_EVALUATED_AT_SOME_POINT     312       /* A function to be plotted has not been faithfully evaluated at at least one point. */
#define SOLLYA_MSG_DOMAIN_IS_REDUCED_TO_A_POINT_TRIVIAL_RESULT     313       /* The given domain is reduced to a point. The result is trivial. */
#define SOLLYA_MSG_EXTERNAL_FUNC_OR_PROC_ALREADY_BOUND             314       /* An external function or external procedure with the same name has already been bound to the tool. */
#define SOLLYA_MSG_COULD_NOT_OPEN_LIBRARY_WITH_EXTERN_FUNC_OR_PROC 315       /* A library with an external function or procedure could not be opened. */
#define SOLLYA_MSG_EXTERNAL_FUNC_OR_PROC_NOT_FOUND_IN_LIBRARY      316       /* No external function or external procedure with the given name could be found in the given library. */
#define SOLLYA_MSG_COULD_NOT_CLOSE_LIBRARY                         317       /* A library could not be closed. */
#define SOLLYA_MSG_ENTERING_NEWTONS_ALGORITHM                      318       /* Entering Newton's algorithm. Certain parameters are given. */
#define SOLLYA_MSG_NEWTON_ZERO_IS_EXACT_ZERO                       319       /* Newton's algorithm: zero is an exact zero. */
#define SOLLYA_MSG_NEWTON_AN_EXACT_ZERO_HAS_BEEN_FOUND             320       /* Newton's algorithm: an exact zero has been found. */
#define SOLLYA_MSG_ERROR_IN_TAYLORFORM_COPYING_INCOMPAT_MODELS     321       /* Error in Taylor form computation: copy of incompatible models. */
#define SOLLYA_MSG_PLOT_COULD_NOT_OPEN_FILE                        322       /* A certain file could not be opened for writing while attempting to plot. */
#define SOLLYA_MSG_NEWTON_FUNC_APPEARS_TO_HAVE_MORE_THAN_ONE_ZERO  323       /* Newton's algorithm: the function has more than one zero in the interval. */
#define SOLLYA_MSG_NEWTON_ZERO_TOO_CLOSE_TO_ZERO_TO_BE_ACCURATE    324       /* Newton's algorithm: the zero of the function is too close to zero for being accurately determined. */
#define SOLLYA_MSG_NEWTON_ZERO_SEEMS_TO_BE_ZERO_NO_PROOF           325       /* Newton's algorithm: zero seems to be a zero of function, which cannot be proved. */
#define SOLLYA_MSG_NEWTON_ALGORITHM_FAILS_DUE_TO_NUMERICAL_ISSUES  326       /* Newton's algorithm fails due to numerical issues. */
#define SOLLYA_MSG_NEWTON_ALGORITHM_FAILS_TO_LOCATE_ZERO           327       /* Newton's algorithm fails to locate the zero. */
#define SOLLYA_MSG_NEWTON_PERFORMING_BISECTION_STEP                328       /* Newton's algorithm: performing a bisection step. */
#define SOLLYA_MSG_NEWTON_PERFORMING_TRISECTION_STEP               329       /* Newton's algorithm: performing a trisection step. */
#define SOLLYA_MSG_NEWTON_FINISHED_AFTER_NUMBER_OF_STEPS           330       /* Newton's algorithm has finished after a certain number of steps. */
#define SOLLYA_MSG_REMEZ_EXCHANGE_TAKE_A_CERTAIN_MINIMUM           331       /* Remez: an exchange step takes a certain minimum to perform the exchange. */
#define SOLLYA_MSG_REMEZ_EXCHANGE_TAKE_A_CERTAIN_MAXIMUM           332       /* Remez: an exchange step takes a certain maximum to perform the exchange. */
#define SOLLYA_MSG_REMEZ_FUNCTION_OSCILLATES_TOO_MUCH              333       /* Remez: the error function oscillates too much. */
#define SOLLYA_MSG_REMEZ_PERFORMING_AN_EXCHANGE_STEP               334       /* Remez: performing an exchange step. */
#define SOLLYA_MSG_REMEZ_COMPUTED_INFNORM_IS_A_CERTAIN_VALUE       335       /* Remez: the computed infinity norm of the current error function takes a certain value. */
#define SOLLYA_MSG_REMEZ_FAILED_TO_FIND_PSEUDOALTERNATING_POINTS   336       /* Remez: failed to find pseudo-alternating points. */
#define SOLLYA_MSG_REMEZ_CONSTRUCTING_THE_ERROR_TREE               337       /* Remez: constructing the error tree. */
#define SOLLYA_MSG_REMEZ_CONSTRUCTING_THE_ERROR_PRIME_TREE         338       /* Remez: constructing the error' tree. */
#define SOLLYA_MSG_REMEZ_CONSTRUCTING_THE_ERROR_SECOND_TREE        339       /* Remez: constructing the error'' tree. */
#define SOLLYA_MSG_REMEZ_COMPUTING_THE_YI                          340       /* Remez: computing the yi. */
#define SOLLYA_MSG_REMEZ_THE_COMPUTED_YI_ARE_CERTAIN_VALUES        341       /* Remez: the computed yi are certain values. */
#define SOLLYA_MSG_REMEZ_ALGORITHM_IS_IN_A_CERTAIN_CASE            342       /* Remez: the algorithm is in a certain case. */
#define SOLLYA_MSG_REMEZ_THE_COMPUTED_SIGNS_ARE_CERTAIN_VALUES     343       /* Remez: the computed signs take certain values. */
#define SOLLYA_MSG_REMEZ_SIGNS_COULD_NOT_BE_EVALUATED              344       /* Remez: the signs could not be evaluated. */
#define SOLLYA_MSG_REMEZ_MAIN_HEURISTIC_FAILED_USING_SLOWER_ALGO   345       /* Remez: the main heuristic failed; using a slower algorithm. */
#define SOLLYA_MSG_REMEZ_SLOWER_ALGORITHM_USED_FOR_A_STEP          346       /* Remez: a slower algorithm is used for a certain step. */
#define SOLLYA_MSG_REMEZ_THE_NEW_POINTS_ARE_CERTAIN_VALUES         347       /* Remez: the new points take certain values. */
#define SOLLYA_MSG_REMEZ_THE_CURRENT_NORM_TAKES_A_CERTAIN_VALUE    348       /* Remez: the current norm takes a certain value. */
#define SOLLYA_MSG_ENTERING_REMEZ_FUNCTION                         349       /* Entering the Remez function. Certain parameters are given. */
#define SOLLYA_MSG_REMEZ_COMPUTING_MONOMIALS                       350       /* Remez: computing the monomials. */
#define SOLLYA_MSG_REMEZ_COMPUTING_INITIAL_POINT_SET               351       /* Remez: computing an initial point set. */
#define SOLLYA_MSG_REMEZ_THE_COMPUTED_POINT_SET_IS_CERTAIN_VALUES  352       /* Remez: the computed point set contains certain values. */
#define SOLLYA_MSG_REMEZ_COMPUTING_THE_MATRIX                      353       /* Remez: computing the matrix. */
#define SOLLYA_MSG_REMEZ_COMPUTAT_OF_MATRIX_ENTRY_USES_SLOWER_ALGO 354       /* Remez: the computation of a certain matrix entry uses a slower algorithm. */
#define SOLLYA_MSG_REMEZ_DEGENERATED_SYSTEM_IN_NON_HAAR_CONTEXT    355       /* Remez: the system is degenerated in a non-Haar context. */
#define SOLLYA_MSG_REMEZ_SIGNS_FOR_PSEUDO_ALTERN_ARE_CERTAIN_VALS  356       /* Remez: the signs for the pseudo-alternation condition are certain values. */
#define SOLLYA_MSG_REMEZ_THE_COMPUTED_MATRIX_HAS_A_CERTAIN_VALUE   357       /* Remez: the computed matrix has a certain value. */
#define SOLLYA_MSG_REMEZ_SOLVING_THE_SYSTEM                        358       /* Remez: solving the system. */
#define SOLLYA_MSG_REMEZ_THE_COMPUTED_POLY_HAS_A_CERTAIN_VALUE     359       /* Remez: the computed polynomial has a certain value. */
#define SOLLYA_MSG_REMEZ_CURRENT_EPSILON_HAS_A_CERTAIN_VALUE       360       /* Remez: the current epsilon has a certain value. */
#define SOLLYA_MSG_REMEZ_DIFFERENTIATING_THE_COMPUTED_POLYNOMIAL   361       /* Remez: differentiating the computed polynomial. */
#define SOLLYA_MSG_REMEZ_SEARCHING_FOR_EXTREMA_OF_ERROR_FUNCTION   362       /* Remez: searching for the extrema of the error function. */
#define SOLLYA_MSG_REMEZ_THE_BEST_POLY_GIVES_A_CERTAIN_ERROR       363       /* Remez: the best polynomial that has been computed yields to a certain error. */
#define SOLLYA_MSG_REMEZ_CURRENT_QUALITY_HAS_A_CERTAIN_VALUE       364       /* Remez: the current quality has a certain value. */
#define SOLLYA_MSG_REMEZ_FINISHES_AS_TARGET_ERROR_IS_NOT_REACHABLE 365       /* The Remez algorithm finishes as the given target error is provably not reachable. */
#define SOLLYA_MSG_REMEZ_FINISHES_AS_TARGET_ERROR_HAS_BEEN_REACHED 366       /* The Remez algorithm finishes as the given target error has been reached. */
#define SOLLYA_MSG_REMEZ_FINISHES_AS_QUALITY_HAS_BEEN_REACHED      367       /* The Remez algorithm finishes as the specified quality has been reached. */
#define SOLLYA_MSG_REMEZ_FAILS_AND_LOOPS_AGAIN                     368       /* The Remez algorithm has failed (possible because of too many oscillations) and it loops again. */
#define SOLLYA_MSG_REMEZ_DOES_NOT_CONVERGE                         369       /* The Remez algorithm does not converge. */
#define SOLLYA_MSG_REMEZ_MAY_HAPPEN_NOT_TO_CONVRG_AS_DOM_IS_POINT  370       /* The Remez algorithm may happen not to converge because the given domain is reduced to a point. */
#define SOLLYA_MSG_GUESSDEGREE_TRYING_A_CERTAIN_DEGREE             371       /* Guessdegree is about to try a certain degree. */
#define SOLLYA_MSG_GUESSDEGREE_NONE_OF_LESSER_DEGS_SATISFIES_ERROR 372       /* Guessdegree: none of the degrees less than a certain degree satisfies the target error. */
#define SOLLYA_MSG_GUESSDEGREE_TRYING_A_CERTAIN_DEG_WITHIN_BOUNDS  373       /* Guessdegree is about to try a certain degree within certain bounds. */
#define SOLLYA_MSG_GUESSDEG_NONE_OF_LESS_DEGS_SEEMS_TO_SATISFY_ERR 374       /* Guessdegree: none of the degrees less than a certain degree provably satisfy the target error. */
#define SOLLYA_MSG_FPMINIMAX_SINGULAR_MATRIX                       375       /* Fpminimax: the matrix is singular. */
#define SOLLYA_MSG_FPMINIMAX_A_CERTAIN_COEFF_IS_EXACT_ZERO         376       /* Fpminimax: a certain coefficient is an exact zero. */
#define SOLLYA_MSG_FPMINIMAX_MINIMAX_DOES_NOT_GIVE_ENOUGH_POINTS   377       /* Fpminimax: the minimax does not give enough points, switching to Chebyshev points. */
#define SOLLYA_MSG_FPMINIMAX_THE_POINTS_ARE_CERTAIN_VALUES         378       /* Fpminimax: the points are certain values. */
#define SOLLYA_MSG_FPMINIMAX_FAILED_TO_RECOVER_COEFFS_FROM_POLY    379       /* Fpminimax failed to recover the coefficients from the given pseudo-polynomial. */
#define SOLLYA_MSG_FPMINIMAX_THE_EXPONENTS_ARE_CERTAIN_VALUES      380       /* Fpminimax: the exponents are certain values. */
#define SOLLYA_MSG_FPMINIMAX_DID_NOT_CONVERGE                      381       /* Fpminimax did not converge. */
#define SOLLYA_MSG_FPMINIMAX_NOT_ENOUGH_POINTS                     382       /* Fpminimax has been called with no sufficient number of points. */
#define SOLLYA_MSG_FPMINIMAX_NOT_ENOUGH_FORMATS                    383       /* Fpminimax has been called with no sufficient number of formats. */
#define SOLLYA_MSG_FPMINIMAX_COMP_OF_MATRIX_ENTRY_USES_SLOWER_ALGO 384       /* Fpminimax: the computation of a certain matrix entry uses a slower algorithm. */
#define SOLLYA_MSG_DIFFERENTIATING_FOR_DECORRELATION               385       /* Interval evaluation performs a formal differentiation in order to try to decorrelate expressions. */
#define SOLLYA_MSG_DECORRELATION_INTERVAL_ADDITION_OR_SUBTRACTION  386       /* Decorrelation is performed on an interval addition or subtraction. */
#define SOLLYA_MSG_DIFFERENTIATING_FOR_HOPITALS_RULE               387       /* Interval evaluation performs a formal differentiation in order to use Hopital's rule. */
#define SOLLYA_MSG_USING_HOPITALS_RULE_ON_POINT_DIVISION           388       /* Using Hopital's rule on point division. */
#define SOLLYA_MSG_SIMPLIFYING_INTERVAL_DIV_WITH_ZERO_POINT_NUMERA 389       /* Simplifying an interval division with a zero point interval as a numerator. */
#define SOLLYA_MSG_USING_HOPITALS_RULE_IN_GENERAL_CASE             390       /* Using Hopital's rule in the general case. */
#define SOLLYA_MSG_RECURSION_ON_USE_OF_HOPITALS_RULE               391       /* Recursion is needed on the use of Hopital's rule. */
#define SOLLYA_MSG_AVOIDING_TAYLOR_EVALUATION_ON_POINT_INTERVAL    392       /* Avoiding Taylor evaluation on a point interval. */
#define SOLLYA_MSG_NO_TAYLOR_EVALUATION_AS_NO_DERIVATIVE_GIVEN     393       /* No Taylor evaluation is possible because no derivative has been given. */
#define SOLLYA_MSG_USING_TAYLOR_EVALUATION                         394       /* Taylor evaluation gets used. */
#define SOLLYA_MSG_NO_TAYLOR_EVALUATION_AS_NO_DERIVATIVE_GETS_HUGE 395       /* No Taylor evaluation is possible because with all recursions, the tree of the derivative has become huge. */
#define SOLLYA_MSG_DERIVATIVE_DOES_NOT_CHANGE_SIGN_ON_TAYLOR_EVAL  396       /* The derivative of a function does not change sign on an interval during Taylor evaluation. The convex hull algorithm gets used. */
#define SOLLYA_MSG_NAN_OR_INF_ON_DERIVATIVE                        397       /* The tree for the derivative of a function evaluates to NaN or Inf on an interval. The function might not be differentiable. */
#define SOLLYA_MSG_INVOKING_RECURSIVE_INTERVAL_ZERO_SEARCH         398       /* Invoking recursive interval zero search. */
#define SOLLYA_MSG_RECURSIVE_INTERVAL_ZERO_SEARCH_HAS_FINISHED     399       /* Recursive interval zero search has finished. */
#define SOLLYA_MSG_CERTAIN_NUM_OF_INTVALS_ENCLOSING_ZEROS_OF_DERIV 400       /* A certain number of interval enclosing the zeros of the derivative of a function has been found. */
#define SOLLYA_MSG_EXPRESSION_IS_CONSTANT                          401       /* The given expression is constant. */
#define SOLLYA_MSG_EVALUATION_AT_POINT_GIVES_NAN_EXCLUDING_POINT   402       /* The evaluation of a certain function at a certain point becomes NaN. The point gets excluded from the list of points yielding to the result. */
#define SOLLYA_MSG_THE_CURRENT_MAXIMUM_IS_A_CERTAIN_VALUE          403       /* The current maximum is a certain value. */
#define SOLLYA_MSG_EVALUATION_OF_DERIVATIVE_GIVES_NAN_NO_NEWTON    404       /* The evaluation of the derivative of the function gives NaN. Newton's algorithm will not be used on this sub-interval. */
#define SOLLYA_MSG_NO_PROOF_WILL_BE_GENERATED                      405       /* No proof will be generated. */
#define SOLLYA_MSG_INFNORM_RESULT_IS_TRIVIAL                       406       /* The infnorm result of the given function on the given domain is trivially computable. */
#define SOLLYA_MSG_DERIVATIVE_IS_QUOTIENT                          407       /* The derivative of the given function is a quotient. */
#define SOLLYA_MSG_DERIVATIVE_SEEMS_TO_HAVE_SINGULARITY            408       /* The derivative of the given function seems to have a singularity in the domain. */
#define SOLLYA_MSG_DERIVATIVE_SEEMS_TO_HAVE_EXTENSIBLE_SINGULARITY 409       /* The derivative of the given function seems to have an extensible singularity in the domain. */
#define SOLLYA_MSG_DERIVATIVE_SEEMS_NOT_TO_HAVE_ANY_POLE           410       /* The derivative of the given function seems not to have any pole in the domain. */
#define SOLLYA_MSG_INVOKING_INFNORM_SUBFUNCTION                    411       /* Invoking the infnorm subfunction. */
#define SOLLYA_MSG_INFNORM_SUBFUNCTION_HAS_FINISHED                412       /* The infnorm subfunction has finished. */
#define SOLLYA_MSG_STARTING_TO_WRITE_THE_PROOF                     413       /* Starting to write the proof. */
#define SOLLYA_MSG_THE_PROOF_HAS_BEEN_WRITTEN                      414       /* The proof has been written. */
#define SOLLYA_MSG_THE_EXPRESSION_IS_NOT_CONSTANT                  415       /* The given expression is not constant. It will be evaluated at 1. */
#define SOLLYA_MSG_COULD_NOT_CHECK_INFNORM_ON_A_CERTAIN_INTERVAL   416       /* The given infinity norm result could not be check on a certain (sub-)interval. */
#define SOLLYA_MSG_REMOVING_A_POSSIBLE_ZERO_AT_SOME_POINT          417       /* A possible zero at some point is removed. */
#define SOLLYA_MSG_ZERO_FILTER_HAS_REMOVED_AT_LEAST_ONE_ZERO       418       /* The actual zero filter has removed at least one possible zero. */
#define SOLLYA_MSG_FAITHFUL_EVALUATION_RETURNS_NAN                 419       /* Faithful evaluation returns NaN. */
#define SOLLYA_MSG_INTERMEDIATE_PRECISION_HAS_BEEN_INCREASED       420       /* The intermediate precision has been increased to a certain value. */
#define SOLLYA_MSG_TAYLOR_RECURSION_TEMPORARILY_SET_TO_A_VALUE     421       /* The number of Taylor recursions has been temporarily set to a certain value. */
#define SOLLYA_MSG_ABS_DIAM_AND_PREC_SET_TO_CERTAIN_VALUES         422       /* The absolute diameter and the intermediate precision have been temporarily set to certain values. */
#define SOLLYA_MSG_IDENTIFIER_IS_LIBRARY_FUNC_CANNOT_BE_EXTERNAL   423       /* An identifier is already bound to a library function. It cannot be bound to an external procedure. */


#endif /* ifdef MESSAGE_NUMBERS_H*/
