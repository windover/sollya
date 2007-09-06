#ifndef EXECUTE_H
#define EXECUTE_H


#include <mpfr.h>
#include <stdio.h>
#include "main.h"
#include "expression.h"

#define COMMANDLIST 50			
#define WHILE 51				
#define IFELSE 52				
#define IF 53				
#define FOR 54						
#define FORIN 56 				
#define QUIT 57 				
#define FALSEQUIT 58 			
#define RESTART 59 			
#define PRINT 60				
#define NEWFILEPRINT 61 			
#define APPENDFILEPRINT 62 			
#define PLOT 63				
#define PRINTHEXA 64 			
#define PRINTBINARY 65 			
#define PRINTEXPANSION 66 			
#define BASHEXECUTE 67			
#define EXTERNALPLOT 68			
#define WRITE 69				
#define NEWFILEWRITE 70			
#define APPENDFILEWRITE 71		
#define ASCIIPLOT 72			
#define WORSTCASE 73			
#define RENAME 74				
#define AUTOPRINT 75 			
#define ASSIGNMENT 76			
#define LIBRARYBINDING 77 			
#define PRECASSIGN 78			
#define POINTSASSIGN 79			
#define DIAMASSIGN 80			
#define DISPLAYASSIGN 81			
#define VERBOSITYASSIGN 82 		
#define CANONICALASSIGN 83		
#define AUTOSIMPLIFYASSIGN 84 		
#define TAYLORRECURSASSIGN 85		
#define TIMINGASSIGN 86			
#define FULLPARENASSIGN 87 		
#define MIDPOINTASSIGN 88			
#define HOPITALRECURSASSIGN 89 		
#define PRECSTILLASSIGN 90		
#define POINTSSTILLASSIGN 91		
#define DIAMSTILLASSIGN 92		
#define DISPLAYSTILLASSIGN 93 		
#define VERBOSITYSTILLASSIGN 94		
#define CANONICALSTILLASSIGN 95		
#define AUTOSIMPLIFYSTILLASSIGN 96 	
#define TAYLORRECURSSTILLASSIGN 97	
#define TIMINGSTILLASSIGN 98		
#define FULLPARENSTILLASSIGN 99 		
#define MIDPOINTSTILLASSIGN 100		
#define HOPITALRECURSSTILLASSIGN 101 	
#define AND 102				
#define OR 103				
#define NEGATION 104			
#define INDEX 105				
#define COMPAREEQUAL 106			
#define COMPARELESS 107			
#define COMPAREGREATER 108			
#define COMPARELESSEQUAL 109		
#define COMPAREGREATEREQUAL 110		
#define COMPARENOTEQUAL 111		
#define CONCAT 112			
#define ADDTOLIST 113			
#define ON 114				
#define OFF 115				
#define DYADIC 116 				
#define POWERS 117				
#define BINARY 118			 	
#define FILESYM 119			 	
#define POSTSCRIPT 120 			
#define POSTSCRIPTFILE 121 			
#define PERTURB 122			
#define ROUNDDOWN 123			
#define ROUNDUP 124			
#define ROUNDTOZERO 125 			
#define ROUNDTONEAREST 126			
#define HONORCOEFF 127			
#define TRUE 128			 	
#define FALSE 129			 	
#define DEFAULT 130			
#define DOUBLESYMBOL 131 			
#define DOUBLEDOUBLESYMBOL 132 		
#define TRIPLEDOUBLESYMBOL 133		
#define STRING 134			 	
#define TABLEACCESS 135 			
#define TABLEACCESSWITHSUBSTITUTE 136 	
#define DECIMALCONSTANT 137		
#define DYADICCONSTANT 138			
#define HEXCONSTANT 139			
#define BINARYCONSTANT 140			
#define EMPTYLIST 141			
#define LIST 142			 	
#define FINALELLIPTICLIST 143		
#define ELLIPTIC 144 			
#define RANGE 145			 	
#define DEBOUNDMAX 146 			
#define DEBOUNDMIN 147			
#define DEBOUNDMID 148			
#define DIFF 149			 	
#define SIMPLIFY 150 			
#define SIMPLIFYSAFE 151 			
#define REMEZ 152			 	
#define HORNER 153			 	
#define CANONICAL 154			
#define EXPAND 155			 	
#define TAYLOR 156			 	
#define DEGREE 157			 	
#define NUMERATOR 158			
#define DENOMINATOR 159			
#define SUBSTITUTE 160			
#define COEFF 161			 	
#define SUBPOLY 162			
#define ROUNDCOEFFICIENTS 163		
#define RATIONALAPPROX 164			
#define ACCURATEINFNORM 165		
#define ROUNDTOFORMAT 166			
#define EVALUATE 167			
#define PARSE 168			 	
#define INFNORM 169			
#define FINDZEROS 170			
#define FPFINDZEROS 171			
#define DIRTYINFNORM 172			
#define INTEGRAL 173			
#define DIRTYINTEGRAL 174 			
#define IMPLEMENTPOLY 175			
#define CHECKINFNORM 176			
#define ZERODENOMINATORS 177 		
#define ISEVALUABLE 178			
#define SEARCHGAL 179			
#define GUESSDEGREE 180			
#define DIRTYFINDZEROS 181			
#define HEAD 182			 	
#define TAIL 183			 	
#define LENGTH 184			 	
#define PRECDEREF 185			
#define POINTSDEREF 186			
#define DIAMDEREF 187			
#define DISPLAYDEREF 188			
#define VERBOSITYDEREF 189			
#define CANONICALDEREF 190			
#define AUTOSIMPLIFYDEREF 191		
#define TAYLORRECURSDEREF 192		
#define TIMINGDEREF 193			
#define FULLPARENDEREF 194			
#define MIDPOINTDEREF 195			
#define HOPITALRECURSDEREF 196 		
#define ABSOLUTESYM 197
#define RELATIVESYM 198
#define DECIMAL 199
#define ASSIGNMENTININDEXING 200
#define DOUBLEEXTENDEDSYMBOL 201
#define ERRORSPECIAL 202
#define PRINTXML 203
#define PRINTXMLNEWFILE 204
#define PRINTXMLAPPENDFILE 205
#define READXML 206

int executeCommand(node *);

void freeThing(node *);
void rawPrintThing(node *);
void freeThingOnVoid(void *);

node *makeCommandList(chain *thinglist);
node *makeWhile(node *thing1, node *thing2);
node *makeIfElse(node *thing1, node *thing2, node *thing3);
node *makeIf(node *thing1, node *thing2);
node *makeFor(char *string, node *thing1, node *thing2, node *thing3, node *thing4);
node *makeConstantDouble(double d);
node *makeForIn(char *string, node *thing1, node *thing2);
node *makeQuit();
node *makeFalseQuit();
node *makeRestart();
node *makePrint(chain *thinglist);
node *makeNewFilePrint(node *thing, chain *thinglist);
node *makeAppendFilePrint(node *thing, chain *thinglist);
node *makePlot(chain *thinglist);
node *makePrintHexa(node *thing);
node *makePrintBinary(node *thing);
node *makePrintExpansion(node *thing);
node *makeBashExecute(node *thing);
node *makeExternalPlot(chain *thinglist);
node *makeWrite(chain *thinglist);
node *makeNewFileWrite(node *thing, chain *thinglist);
node *makeAppendFileWrite(node *thing, chain *thinglist);
node *makeAsciiPlot(node *thing1, node *thing2);
node *makeWorstCase(chain *thinglist);
node *makeRename(char *string1, char *string2);
node *makeAutoprint(chain *thinglist);
node *makeAssignment(char *string, node *thing);
node *makeLibraryBinding(char *string, node *thing);
node *makePrecAssign(node *thing);
node *makePointsAssign(node *thing);
node *makeDiamAssign(node *thing);
node *makeDisplayAssign(node *thing);
node *makeVerbosityAssign(node *thing);
node *makeCanonicalAssign(node *thing);
node *makeAutoSimplifyAssign(node *thing);
node *makeTaylorRecursAssign(node *thing);
node *makeTimingAssign(node *thing);
node *makeFullParenAssign(node *thing);
node *makeMidpointAssign(node *thing);
node *makeHopitalRecursAssign(node *thing);
node *makePrecStillAssign(node *thing);
node *makePointsStillAssign(node *thing);
node *makeDiamStillAssign(node *thing);
node *makeDisplayStillAssign(node *thing);
node *makeVerbosityStillAssign(node *thing);
node *makeCanonicalStillAssign(node *thing);
node *makeAutoSimplifyStillAssign(node *thing);
node *makeTaylorRecursStillAssign(node *thing);
node *makeTimingStillAssign(node *thing);
node *makeFullParenStillAssign(node *thing);
node *makeMidpointStillAssign(node *thing);
node *makeHopitalRecursStillAssign(node *thing);
node *makeAnd(node *thing1, node *thing2);
node *makeOr(node *thing1, node *thing2);
node *makeNegation(node *thing);
node *makeIndex(node *thing1, node *thing2);
node *makeCompareEqual(node *thing1, node *thing2);
node *makeCompareLess(node *thing1, node *thing2);
node *makeCompareGreater(node *thing1, node *thing2);
node *makeCompareLessEqual(node *thing1, node *thing2);
node *makeCompareGreaterEqual(node *thing1, node *thing2);
node *makeCompareNotEqual(node *thing1, node *thing2);
node *makeConcat(node *thing1, node *thing2);
node *makeAddToList(node *thing1, node *thing2);
node *makeOn();
node *makeOff();
node *makeDyadic();
node *makePowers();
node *makeBinaryThing();
node *makeFile();
node *makePostscript();
node *makePostscriptFile();
node *makePerturb();
node *makeRoundDown();
node *makeRoundUp();
node *makeRoundToZero();
node *makeRoundToNearest();
node *makeHonorCoeff();
node *makeTrue();
node *makeFalse();
node *makeDefault();
node *makeDecimal();
node *makeAbsolute();
node *makeRelative();
node *makeError();
node *makeDoubleSymbol();
node *makeDoubleDoubleSymbol();
node *makeTripleDoubleSymbol();
node *makeString(char *string);
node *makeTableAccess(char *string);
node *makeTableAccessWithSubstitute(char *string, node *thing);
node *makeDecimalConstant(char *string);
node *makeDyadicConstant(char *string);
node *makeHexConstant(char *string);
node *makeBinaryConstant(char *string);
node *makeEmptyList();
node *makeList(chain *thinglist);
node *makeFinalEllipticList(chain *thinglist);
node *makeElliptic();
node *makeRange(node *thing1, node *thing2);
node *makeDeboundMax(node *thing);
node *makeDeboundMin(node *thing);
node *makeDeboundMid(node *thing);
node *makeDiff(node *thing);
node *makeSimplify(node *thing);
node *makeSimplifySafe(node *thing);
node *makeRemez(chain *thinglist);
node *makeHorner(node *thing);
node *makeCanonicalThing(node *thing);
node *makeExpand(node *thing);
node *makeTaylor(node *thing1, node *thing2, node *thing3);
node *makeDegree(node *thing);
node *makeNumerator(node *thing);
node *makeDenominator(node *thing);
node *makeSubstitute(node *thing1, node *thing2);
node *makeCoeff(node *thing1, node *thing2);
node *makeSubpoly(node *thing1, node *thing2);
node *makeRoundcoefficients(node *thing1, node *thing2);
node *makeRationalapprox(node *thing1, node *thing2);
node *makeAccurateInfnorm(chain *thinglist);
node *makeRoundToFormat(node *thing1, node *thing2, node *thing3);
node *makeEvaluate(node *thing1, node *thing2);
node *makeParse(node *thing);
node *makeInfnorm(chain *thinglist);
node *makeFindZeros(node *thing1, node *thing2);
node *makeFPFindZeros(node *thing1, node *thing2);
node *makeDirtyInfnorm(node *thing1, node *thing2);
node *makeIntegral(node *thing1, node *thing2);
node *makeDirtyIntegral(node *thing1, node *thing2);
node *makeImplementPoly(chain *thinglist);
node *makeCheckInfnorm(node *thing1, node *thing2, node *thing3);
node *makeZeroDenominators(node *thing1, node *thing2);
node *makeIsEvaluable(node *thing1, node *thing2);
node *makeSearchGal(chain *thinglist);
node *makeGuessDegree(chain *thinglist);
node *makeDirtyFindZeros(node *thing1, node *thing2);
node *makeHead(node *thing);
node *makeTail(node *thing);
node *makeLength(node *thing);
node *makePrecDeref();
node *makePointsDeref();
node *makeDiamDeref();
node *makeDisplayDeref();
node *makeVerbosityDeref();
node *makeCanonicalDeref();
node *makeAutoSimplifyDeref();
node *makeTaylorRecursDeref();
node *makeTimingDeref();
node *makeFullParenDeref();
node *makeMidpointDeref();
node *makeHopitalRecursDeref();
node *makeAssignmentInIndexing(node *, node *, node *);
node *makeDoubleextendedSymbol();
node *makePrintXml(node *);
node *makePrintXmlNewFile(node *, node *);
node *makePrintXmlAppendFile(node *, node *);
node *makeReadXml(node *);


#endif /* ifdef EXECUTE_H*/
