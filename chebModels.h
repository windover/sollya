#include "sollya.h"
#include "stdio.h"

extern void pushTimeCounter(void);
extern void popTimeCounter(char *s);

 extern void mpfr_get_poly(mpfr_t *rc, sollya_mpfi_t *errors_array, sollya_mpfi_t rest, int n, sollya_mpfi_t *p, sollya_mpfi_t x0, sollya_mpfi_t x);
 extern chain *constructChain(sollya_mpfi_t *err, int n);
/*************Functions from chebModelsAux********/

extern int polynomialDivide_mpfi(sollya_mpfi_t *quotient, int *quotient_degree, sollya_mpfi_t *rest, int *rest_degree, sollya_mpfi_t *p, int p_degree, sollya_mpfi_t *q, int q_degree, mp_prec_t prec);
/* Evaluates a symbolic polynomial at point x by Horner scheme */
extern void symbolic_poly_evaluation_horner(sollya_mpfi_t res, sollya_mpfi_t *coeffs_array, sollya_mpfi_t x, int degree);
extern void symbolic_poly_diff(sollya_mpfi_t *res, sollya_mpfi_t *coeff_array, int degree);

extern int mpfi_set_node( sollya_mpfi_t *r, node * c);

/*returns n chebyshev points in x*/
extern void getChebyshevPoints(sollya_mpfi_t *chebPoints, int n, sollya_mpfi_t x);

/*Returns n-1 chebyshev extrema in x*/ 
extern void getChebyshevExtrema(sollya_mpfi_t *chebPoints, int n, sollya_mpfi_t x);

/*The so called chebMatrix, contains 
the specific values of T_i(x_j) i=0..n-1, j=0..n-1
x_j \in [-1,1]. 
Note: It has to be computed only once for each n*/
extern void getChebMatrix(sollya_mpfi_t**chebMatrix, int n);

/*Returns the coeffs of the cheb polynomials, n*n*/
extern void getChebPolyCoeffs(mpz_t* chebMatrix, int n);

/*returns in chebCoeffs the coeffs of the finite Chebyshev basis expansion of the polynomial given by the monomial coefficients p, of degree n-1*/
extern void getPolyCoeffsChebBasis(sollya_mpfi_t *chebCoeffs, sollya_mpfi_t *p, int n);

/*returns in c the coeffs in the monomial basis for the polynomial p(a*x+b), where a and b are mpfi_s
 the polynomial p  of degree n-1 given by the monomial coefficients stored as mpfi_s in p*/
extern void getTranslatedPolyCoeffs(sollya_mpfi_t *c, sollya_mpfi_t *p, int n, sollya_mpfi_t a, sollya_mpfi_t b);

/*evaluate a function in n chebPoints*/
extern void getFunctionValues(sollya_mpfi_t* fValues, sollya_mpfi_t * chebPoints,node* f,int n);


/*this function computes the cheb coeffs for the interpolation polynomial of degree n-1 at chebpoints (we have n chebpoints and a n*n chebMatrix)*/
extern void getChebCoeffs(sollya_mpfi_t* coeffs, sollya_mpfi_t *chebMatrix, sollya_mpfi_t *fValues,int n);


/*wrapper to get directly the coeffs from the function*/
extern void getChebCoeffsFromFunction(sollya_mpfi_t* coeffs, sollya_mpfi_t * chebPoints, sollya_mpfi_t * chebMatrix,node *f,int n);


/*wrapper to get directly the coeffs in the chebyshev basis from a polynomial in the monomial basis(given a pointer to node, over a given interval x*/
extern void getChebCoeffsFromPolynomial(sollya_mpfi_t**coeffs, int*n, node *f, sollya_mpfi_t x);

/*wrapper to get directly the coeffs in the chebyshev basis up to degree n-1 (first n coeffs) and a bound for the remaining polynomial, from a polynomial in the monomial basis(given a pointer to node, over a given interval x*/
extern void getNChebCoeffsFromPolynomial(sollya_mpfi_t *coeffs, sollya_mpfi_t bound, node *f, sollya_mpfi_t x, int n);


/*wrapper to get directly the coeffs in the monomial basis from a polynomial in the chebBasis basis(given a pointer to node, over a given interval x*/
void getCoeffsFromChebPolynomial(sollya_mpfi_t**coeffs, sollya_mpfi_t *chebCoeffs, int n, sollya_mpfi_t x);

/*****************************************************************************/
/*************Functions related to bounding polynomials in ChebBasis**********/
/*****************************************************************************/

/* This function computes an interval bound for a polynomial in cheb basis. */
/*The coefficients are given in coeffs. We have n coeffs*/
/* by just adding the absolute values of the coeffs        */

void chebPolynomialBoundSimple(sollya_mpfi_t bound, int n, sollya_mpfi_t *coeffs);


/* This function computes an interval bound for a polynomial in cheb basis. */
/*The coefficients are given in coeffs. We have n coeffs*/
/* we will use a refined method for this        */
int chebPolynomialBoundRefined(sollya_mpfi_t bound, int n, sollya_mpfi_t *coeffs);

/* This function computes an interval bound for a polynomial in cheb basis. */
/*One day this function may become more complex*/
void chebPolynomialBoundDefault(sollya_mpfi_t bound, int n, sollya_mpfi_t *coeffs);

/* This function computes an interval bound for a polynomial in cheb basis. */
/*The coefficients are given in coeffs. We have n coeffs*/
/* by just adding the absolute values of the coeffs        */

void evaluateChebPolynomialClenshaw(sollya_mpfi_t bound, int n, sollya_mpfi_t *coeffs, mpfi_t x,mpfi_t x0);




/*cheby model structure:
n- order: polynomial of degree n-1, remainder of order O(x^n)
cheb_array : n chebyshev points kept 
poly_array - array of n coeffs for the polynomial of degree n-1
rem_bound - bound for the remainder
poly_bound - bound for the polynomial (helpful for computations)
x- interval on which the cm is computed
*/
typedef struct cmdl {
int n; 
sollya_mpfi_t rem_bound;
sollya_mpfi_t *poly_array;
sollya_mpfi_t *cheb_array;
sollya_mpfi_t poly_bound;
sollya_mpfi_t x;
sollya_mpfi_t **cheb_matrix;
} chebModel;



/*This function creates an empty chebyshev model
It only allocates the memory, it does not compute anything inside the model
*/
chebModel* createEmptycModel(int n,sollya_mpfi_t x);


/*This function creates an empty chebyshev model 
and  computes the chebyshev points of order n 
*/
chebModel* createEmptycModelCompute(int n,sollya_mpfi_t x, int flag_points, int flag_matrix);

/*This function creates an empty chebyshev model
and copies the values from chebpoints into the new cmodel
(this function assumes that we have already computed the chebpoints
*/
chebModel* createEmptycModelPrecomp(int n,sollya_mpfi_t x, sollya_mpfi_t *chebPoints, sollya_mpfi_t **chebM);

/*This function dealocates a chebmodel
*/
void clearcModel(chebModel *t);

/*This function pretty prints a cheb model
*/
void printcModel(chebModel *t);

/*This function sets the chebModel t with constant ct;
*/
void constcModel(chebModel*t, sollya_mpfi_t ct);

/* Check that models are compatible one with another: i.e. they can be added, mulitplied, copied, etc. */
int cModelsAreCompatible(chebModel *t1, chebModel *t2);


/*This function sets a cheby model t with the values given by anoter cm tt
they should have the same basis and interval, if an incompatibility is detected,
no modification is made.
*/
void copycModel(chebModel *t, chebModel *tt);

/*This function computes the cm for addition of two  given cm's 
The addition of two cheb/taylor models is the same
*/
void addition_CM(chebModel *t,chebModel *child1_tm, chebModel *child2_tm);

/* This function computes the cm for multiplication by a constant */
void ctMultiplication_CM(chebModel*d, chebModel*s, sollya_mpfi_t c);


/*This function computes the cm for multiplication of two 
given cm's;

-- the parameter tightBounds =0 means that we are interested in speed, and we will use a simple algo
for bounding, otherwise we use tightbounding

-- the parameter forComposition=1 means that we are using the multiplication inside a composition,
so we suppose that the bounds for the models are already computed inside the models.

*/
void  multiplication_CM(chebModel *t,chebModel *c1, chebModel *c2, int tightBounds, int forComposition);


void composition_CM(chebModel *t,chebModel *g, chebModel *f, int tightBounding, mpfr_t targetRem);

void base_CMAux(chebModel *t, int typeOfFunction, int nodeType, node *f, mpfr_t p, int n, sollya_mpfi_t x, int verbosity);
/*****TODO: I stopped here***************/
/*This function computes a chebyshev model - for a base function*/
void base_CM(chebModel *t,int nodeType, int n, sollya_mpfi_t x);

/*This function computes a chebyshev model ADlike*/

void interpolation_CM(chebModel *t, node *f, int n, sollya_mpfi_t x);


