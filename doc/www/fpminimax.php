<a name="fpminimax"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","fpminimax","fpminimax");?> 
<span class="smallDescription">computes a good polynomial approximation with fixed-point or floating-point coefficients 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","fpminimax","fpminimax");?>(<span class="arg">f</span>, <span class="arg">n</span>, <span class="arg">formats</span>, <span class="arg">range</span>, <span class="arg">indic1</span>, <span class="arg">indic2</span>, <span class="arg">indic3</span>, <span class="arg">P</span>) : (<span class="type">function</span>, <span class="type">integer</span>, <span class="type">list</span>, <span class="type">range</span>, <span class="type">absolute|relative</span> | <span class="type">fixed|floating</span> | <span class="type">function</span>, <span class="type">absolute|relative</span> | <span class="type">fixed|floating</span> | <span class="type">function</span>, <span class="type">absolute|relative</span> | <span class="type">fixed|floating</span> | <span class="type">function</span>, <span class="type">function</span>) -&gt; <span class="type">function</span></span> 
<span class="commandline"><?php linkTo("command","fpminimax","fpminimax");?>(<span class="arg">f</span>, <span class="arg">monomials</span>, <span class="arg">formats</span>, <span class="arg">range</span>, <span class="arg">indic1</span>, <span class="arg">indic2</span>, <span class="arg">indic3</span>, <span class="arg">P</span>) : (<span class="type">function</span>, <span class="type">list</span>, <span class="type">list</span>, <span class="type">range</span>,  <span class="type">absolute|relative</span> | <span class="type">fixed|floating</span> | <span class="type">function</span>, <span class="type">absolute|relative</span> | <span class="type">fixed|floating</span> | <span class="type">function</span>, <span class="type">absolute|relative</span> | <span class="type">fixed|floating</span> | <span class="type">function</span>, <span class="type">function</span>) -&gt; <span class="type">function</span></span> 
<span class="commandline"><?php linkTo("command","fpminimax","fpminimax");?>(<span class="arg">f</span>, <span class="arg">n</span>, <span class="arg">formats</span>, <span class="arg">L</span>, <span class="arg">indic1</span>, <span class="arg">indic2</span>, <span class="arg">indic3</span>, <span class="arg">P</span>) : (<span class="type">function</span>, <span class="type">integer</span>, <span class="type">list</span>, <span class="type">list</span>,  <span class="type">absolute|relative</span> | <span class="type">fixed|floating</span> | <span class="type">function</span>, <span class="type">absolute|relative</span> | <span class="type">fixed|floating</span> | <span class="type">function</span>, <span class="type">absolute|relative</span> | <span class="type">fixed|floating</span> | <span class="type">function</span>, <span class="type">function</span>) -&gt; <span class="type">function</span></span> 
<span class="commandline"><?php linkTo("command","fpminimax","fpminimax");?>(<span class="arg">f</span>, <span class="arg">monomials</span>, <span class="arg">formats</span>, <span class="arg">L</span>, <span class="arg">indic1</span>, <span class="arg">indic2</span>, <span class="arg">indic3</span>, <span class="arg">P</span>) : (<span class="type">function</span>, <span class="type">list</span>, <span class="type">list</span>, <span class="type">list</span>,  <span class="type">absolute|relative</span> | <span class="type">fixed|floating</span> | <span class="type">function</span>, <span class="type">absolute|relative</span> | <span class="type">fixed|floating</span> | <span class="type">function</span>, <span class="type">absolute|relative</span> | <span class="type">fixed|floating</span> | <span class="type">function</span>, <span class="type">function</span>) -&gt; <span class="type">function</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">f</span> is the function to be approximated</li> 
<li><span class="arg">n</span> is the degree of the polynomial that must approximate <span class="arg">f</span></li> 
<li><span class="arg">monomials</span> is the list of monomials that must be used to represent the polynomial that approximates <span class="arg">f</span></li> 
<li><span class="arg">formats</span> is a list indicating the formats that the coefficients of the polynomial must have</li> 
<li><span class="arg">range</span> is the interval where the function must be approximated</li> 
<li><span class="arg">L</span> is a list of interpolation points used by the method</li> 
<li><span class="arg">indic1</span> (optional) is one of the optional indication parameters. See the detailed description below.</li> 
<li><span class="arg">indic2</span> (optional) is one of the optional indication parameters. See the detailed description below.</li> 
<li><span class="arg">indic3</span> (optional) is one of the optional indication parameters. See the detailed description below.</li> 
<li><span class="arg">P</span> (optional) is the minimax polynomial to be considered for solving the problem.</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","fpminimax","fpminimax");?> uses a heuristic (but practically efficient) method to find a 
good polynomial approximation of a function <span class="arg">f</span> on an interval <span class="arg">range</span>. It 
implements the method published in the article:<br> 
Efficient polynomial L^\infty - approximations  
Nicolas Brisebarre and Sylvain Chevillard<br> 
Proceedings of the 18th IEEE Symposium on Computer Arithmetic (ARITH 18)<br> 
pp. 169-176 
</li><li>The basic usage of this command is <?php linkTo("command","fpminimax","fpminimax");?>(<span class="arg">f</span>, <span class="arg">n</span>, <span class="arg">formats</span>, <span class="arg">range</span>). 
It computes a polynomial approximation of f with degree at most n 
on the interval <span class="arg">range</span>. <span class="arg">formats</span> is a list of integers or format types  
(such as <?php linkTo("command","double","double");?>, <?php linkTo("command","doubledouble","doubledouble");?>, etc.). The polynomial returned by the 
command has its coefficients that fit the formats indications. For  
instance, if formats[0] is 35, the coefficient of degree 0 of the  
polynomial will fit a floating-point format of 35 bits. If formats[1]  
is D, the coefficient of degree 1 will be representable by a floating-point 
number with a precision of 53 bits (which is not necessarily an IEEE 754 
double precision number. See the remark below), etc. 
</li><li>The second argument may be either an integer or a list of integers 
interpreted as the list of desired monomials. For instance, the list 
[|0,2,4,6|] indicates that the polynomial must be even and of 
degree at most 6. Giving an integer n as second argument is equivalent 
as giving [|0,...,n|].<br> 
The list of formats is interpreted with respect to the list of monomials. For 
instance, if the list of monomials is [|0,2,4,6|] and the list 
of formats is [|161,107,53,24|], the coefficients of degree 0 is  
searched as a floating-point number with precision 161, the coefficient of  
degree 2 is searched as a number of precision 107, and so on. 
</li><li>The list of formats may contain either integers or format types 
(<?php linkTo("command","halfprecision","halfprecision");?>, <?php linkTo("command","single","single");?>, <?php linkTo("command","double","double");?>, <?php linkTo("command","doubledouble","doubledouble");?>, <?php linkTo("command","tripledouble","tripledouble");?>, <?php linkTo("command","doubleextended","doubleextended");?> 
and <?php linkTo("command","quad","quad");?>). The list may be too large or even infinite. Only the first 
indications will be considered. For instance, for a degree n polynomial, 
formats[n+1] and above will be discarded. This lets one use elliptical 
indications for the last coefficients. 
</li><li>The floating-point coefficients considered by <?php linkTo("command","fpminimax","fpminimax");?> do not have an 
exponent range. In particular, in the format list, <?php linkTo("command","double","double");?> is an exact synonym 
for 53. Currently, <?php linkTo("command","fpminimax","fpminimax");?> only ensures that the corresponding coefficient 
has at most 53 bits of mantissa. It does not imply that it is an 
IEEE-754 double. 
</li><li>By default, the list of formats is interpreted as a list of floating-point 
formats. This may be changed by passing <?php linkTo("command","fixed","fixed");?> as an optional argument (see 
below). Let us take an example: <?php linkTo("command","fpminimax","fpminimax");?>(f, 2, [107, DD, 53], [0;1]). 
Here the optional argument is missing (we could have set it to <?php linkTo("command","floating","floating");?>). 
Thus, <?php linkTo("command","fpminimax","fpminimax");?> will search for a polynomial of degree 2 with a constant  
coefficient that is a 107 bits floating-point number, etc.<br> 
Currently, <?php linkTo("command","doubledouble","doubledouble");?> is just a synonym for 107 and <?php linkTo("command","tripledouble","tripledouble");?> a  
synonym for 161. This behavior may change in the future (taking into 
account the fact that some double-doubles are not representable with 
107 bits).<br> 
Second example: <?php linkTo("command","fpminimax","fpminimax");?>(f, 2, [25, 18, 30], [0;1], <?php linkTo("command","fixed","fixed");?>). 
In this case, <?php linkTo("command","fpminimax","fpminimax");?> will search for a polynomial of degree 2 with a 
constant coefficient of the form m/2^25 where m is an 
integer. In other words, it is a fixed-point number with 25 bits after 
the point. Note that even with argument <?php linkTo("command","fixed","fixed");?>, the formats list is  
allowed to contain <?php linkTo("command","halfprecision","halfprecision");?>, <?php linkTo("command","single","single");?>, <?php linkTo("command","double","double");?>, <?php linkTo("command","doubleextended","doubleextended");?>,  
<?php linkTo("command","doubledouble","doubledouble");?>, <?php linkTo("command","quad","quad");?> or <?php linkTo("command","tripledouble","tripledouble");?>. In this this case, it is just  
a synonym for 11, 24, 53, 64, 107, 113 or 161. This is deprecated and  
may change in the future. 
</li><li>The fourth argument may be a range or a list. Lists are for advanced users 
that know what they are doing. The core of the  method is a kind of 
approximated interpolation. The list given here is a list of points that 
must be considered for the interpolation. It must contain at least as  
many points as unknown coefficients. If you give a list, it is also  
recommended that you provide the minimax polynomial as last argument. 
If you give a range, the list of points will be automatically computed. 
</li><li>The fifth, sixth and seventh arguments are optional. By default, <?php linkTo("command","fpminimax","fpminimax");?> 
will approximate f while optimizing the relative error, and interpreting 
the list of formats as a list of floating-point formats.<br> 
This default behavior may be changed with these optional arguments. You 
may provide zero, one, two or three of the arguments in any order. 
This lets the user indicate only the non-default arguments.<br> 
The three possible arguments are: <ul> 
<li> <?php linkTo("command","relative","relative");?> or <?php linkTo("command","absolute","absolute");?>: the error to be optimized; 
</li><li> <?php linkTo("command","floating","floating");?> or <?php linkTo("command","fixed","fixed");?>: formats of the coefficients; 
</li><li> a constrained part q. 
</li></ul> 
The constrained part lets the user assign in advance some of the 
coefficients. For instance, for approximating exp(x), it may 
be interesting to search for a polynomial p of the form 
                p = 1 + x + x^2/2 + a3 x^3 + a4 x^4. 
Thus, there is a constrained part q = 1 + x + x^2/2 and the unknown 
polynomial should be considered in the monomial basis [|3, 4|]. 
Calling <?php linkTo("command","fpminimax","fpminimax");?> with monomial basis [|3,4|] and constrained 
part q, will return a polynomial with the right form. 
</li><li>The last argument is for advanced users. It is the minimax polynomial that 
approximates the function f in the monomial basis. If it is not given 
this polynomial will be automatically computed by <?php linkTo("command","fpminimax","fpminimax");?>. 
<br> 
This minimax polynomial is used to compute the list of interpolation 
points required by the method. In general, you do not have to provide this 
argument. But if you want to obtain several polynomials of the same degree 
that approximate the same function on the same range, just changing the 
formats, you should probably consider computing only once the minimax 
polynomial and the list of points instead of letting <?php linkTo("command","fpminimax","fpminimax");?> recompute 
them each time. 
<br> 
Note that in the case when a constrained part is given, the minimax  
polynomial must take that into account. For instance, in the previous 
example, the minimax would be obtained by the following command: 
       P = remez(1-(1+x+x^2/2)/exp(x), [|3,4|], range, 1/exp(x)); 
Note that the constrained part is not to be added to P. 
</li><li>Note that <?php linkTo("command","fpminimax","fpminimax");?> internally computes a minimax polynomial (using 
the same algorithm as <?php linkTo("command","remez","remez");?> command). Thus <?php linkTo("command","fpminimax","fpminimax");?> may encounter 
the same problems as <?php linkTo("command","remez","remez");?>. In particular, it may be very slow  
when Haar condition is not fulfilled. Another consequence is that 
currently <?php linkTo("command","fpminimax","fpminimax");?> has to be run with a sufficiently high working precision. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; P = fpminimax(cos(x),6,[|DD, DD, D...|],[-1b-5;1b-5]);<br> 
&nbsp;&nbsp;&nbsp;&gt; printexpansion(P);<br> 
&nbsp;&nbsp;&nbsp;(0x3ff0000000000000 + 0xbc09fda20235c100) + x * ((0x3b29ecd485d34781 + 0xb7c1cbc97120359a) + x * (0xbfdfffffffffff98 + x * (0xbbfa6e0b3183cb0d + x * (0x3fa5555555145337 + x * (0x3ca3540480618939 + x * 0xbf56c138142d8c3b)))))<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; P = fpminimax(sin(x),6,[|32...|],[-1b-5;1b-5], fixed, absolute);<br> 
&nbsp;&nbsp;&nbsp;&gt; display = powers!;<br> 
&nbsp;&nbsp;&nbsp;&gt; P;<br> 
&nbsp;&nbsp;&nbsp;x * (1 + x^2 * (-357913941 * 2^(-31) + x^2 * (35789873 * 2^(-32))))<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; P = fpminimax(exp(x), [|3,4|], [|D,24|], [-1/256; 1/246], 1+x+x^2/2);<br> 
&nbsp;&nbsp;&nbsp;&gt; display = powers!;<br> 
&nbsp;&nbsp;&nbsp;&gt; P;<br> 
&nbsp;&nbsp;&nbsp;1 + x * (1 + x * (1 * 2^(-1) + x * (375300225001191 * 2^(-51) + x * (5592621 * 2^(-27)))))<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 4: </h2> 
&nbsp;&nbsp;&nbsp;&gt; f = cos(exp(x));<br> 
&nbsp;&nbsp;&nbsp;&gt; pstar = remez(f, 5, [-1b-7;1b-7]);<br> 
&nbsp;&nbsp;&nbsp;&gt; listpoints = dirtyfindzeros(f-pstar, [-1b-7; 1b-7]);<br> 
&nbsp;&nbsp;&nbsp;&gt; P1 = fpminimax(f, 5, [|DD...|], listpoints, absolute, default, default, pstar);<br> 
&nbsp;&nbsp;&nbsp;&gt; P2 = fpminimax(f, 5, [|D...|], listpoints, absolute, default, default, pstar);<br> 
&nbsp;&nbsp;&nbsp;&gt; P3 = fpminimax(f, 5, [|D, D, D, 24...|], listpoints, absolute, default, default, pstar);<br> 
&nbsp;&nbsp;&nbsp;&gt; print("Error of pstar: ", dirtyinfnorm(f-pstar, [-1b-7; 1b-7]));<br> 
&nbsp;&nbsp;&nbsp;Error of pstar:&nbsp;&nbsp;7.9048441305459735102879831325718745399379329453102e-16<br> 
&nbsp;&nbsp;&nbsp;&gt; print("Error of P1:&nbsp;&nbsp;&nbsp;&nbsp;", dirtyinfnorm(f-P1, [-1b-7; 1b-7]));<br> 
&nbsp;&nbsp;&nbsp;Error of P1:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;7.9048441305459735159848647089192667442047469404883e-16<br> 
&nbsp;&nbsp;&nbsp;&gt; print("Error of P2:&nbsp;&nbsp;&nbsp;&nbsp;", dirtyinfnorm(f-P2, [-1b-7; 1b-7]));<br> 
&nbsp;&nbsp;&nbsp;Error of P2:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;8.2477144579950871061147021597406077993657714575238e-16<br> 
&nbsp;&nbsp;&nbsp;&gt; print("Error of P3:&nbsp;&nbsp;&nbsp;&nbsp;", dirtyinfnorm(f-P3, [-1b-7; 1b-7]));<br> 
&nbsp;&nbsp;&nbsp;Error of P3:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1.08454277156993282593701156841863009789063333951055e-15<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","remez","remez");?>, <?php linkTo("command","dirtyfindzeros","dirtyfindzeros");?>, <?php linkTo("command","absolute","absolute");?>, <?php linkTo("command","relative","relative");?>, <?php linkTo("command","fixed","fixed");?>, <?php linkTo("command","floating","floating");?>, <?php linkTo("command","default","default");?>, <?php linkTo("command","halfprecision","halfprecision");?>, <?php linkTo("command","single","single");?>, <?php linkTo("command","double","double");?>, <?php linkTo("command","doubleextended","doubleextended");?>, <?php linkTo("command","doubledouble","doubledouble");?>, <?php linkTo("command","quad","quad");?>, <?php linkTo("command","tripledouble","tripledouble");?>, <?php linkTo("command","implementpoly","implementpoly");?>, <?php linkTo("command","coeff","coeff");?>, <?php linkTo("command","degree","degree");?>, <?php linkTo("command","roundcoefficients","roundcoefficients");?>, <?php linkTo("command","guessdegree","guessdegree");?> 
</div> 
