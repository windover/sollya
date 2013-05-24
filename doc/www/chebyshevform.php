<a name="chebyshevform"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","chebyshevform","chebyshevform");?> 
<span class="smallDescription">computes a rigorous polynomial approximation  
</span> 
</div> 
<div class="divLibraryName"> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","chebyshevform","chebyshevform");?>(<span class="arg">f</span>, <span class="arg">n</span>, <span class="arg">I</span>) : (<span class="type">function</span>, <span class="type">integer</span>, <span class="type">range</span>) -&gt; <span class="type">list</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">f</span> is the function to be approximated.</li> 
<li><span class="arg">n</span> is the degree of the polynomial that must approximate <span class="arg">f</span>.</li> 
<li><span class="arg">I</span> is the interval over which the function is to be approximated. This interval cannot be a point interval, i.e. its endpoints have to be different.</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","chebyshevform","chebyshevform");?> computes an approximation polynomial and an interval error bound 
for a given function f.  
<br> 
More precisely, it returns a list L=[p, coeffErrors, Delta, chebCoeffs] 
where: 
<ul> 
<li> p is an approximation polynomial of degree n  
which is roughly speaking a numerical Chebyshev interpolation polynomial  
of f over I represented in monomial basis. 
</li><li> coeffsErrors is a list of n+1 intervals. Each  
interval coeffsErrors[i] contains an enclosure of all the  
errors accumulated when computing the i-th coefficient of p. 
</li><li> Delta is an interval that provides a bound for the  
approximation error between p and f. See details below. 
</li><li> chebCoeffs is a list of  
n+1 intervals. These are the interval coefficients obtained for  
the representation of interpolation polynomial considered in Chebyshev  
basis. See details below. 
</li></ul> 
</li><li>The polynomial p and the bound Delta are obtained 
using Chebyshev Models principles. 
</li><li>More formally, the mathematical property ensured by the algorithm may be 
stated as follows: 
<br> 
Using monomial basis representation given by p: there exist  
(small) values eps[i] in coeffsErrors[i]  
such that: 
for all x in I, there exists delta in Delta such 
that f(x) - p(x) = sum{i=0...n} eps[i]*x^i + delta. 
<br> 
Using Chebyshev basis representation given by chebCoeffs:  
there exist values alpha[i] in chebCoeffs[i]  
such that: 
for all x in I, there exists delta in Delta such 
that f(x) - sum{i=0...n} alfa[i]*T_i(y) =delta,  
where [a,b]=I, y=(2*x-b-a)/(b-a) and  T_i(y)  
is the i-th Chebyshev polynomial over [-1,1]. 
</li><li>The algorithm does not guarantee that by increasing the degree of the 
approximation, the remainder bound will become smaller. Moreover, it may  
even become larger due to the dependecy phenomenon present with interval 
arithmetic. In order to reduce this phenomenon, a possible solution is to 
split the definition domain I into several smaller intervals.  
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; TL=chebyshevform(exp(x), 10, [-1,1]);<br> 
&nbsp;&nbsp;&nbsp;&gt; p=TL[0];<br> 
&nbsp;&nbsp;&nbsp;&gt; Delta=TL[2];<br> 
&nbsp;&nbsp;&nbsp;&gt; p; Delta;<br> 
&nbsp;&nbsp;&nbsp;1.00000000000000000000000000000000000000000000000017 + x * (1.0000000002738981919773953471453626764777115166417 + x * (0.50000000002276754368023326882542097365411870042311 + x * (0.166666661190450656168988993421371510533693281444003 + x * (4.16666662114404339731887995095915661615696989046437e-2 + x * (8.3333639749825520034240517636254576844423981913792e-3 + x * (1.38889143636148090706862105537216777944219976325265e-3 + x * (1.98342776066472142284727329700227389403558111865906e-4 + x * (2.47957727598277888282218067965324267955768146489014e-5 + x * (2.82540334409824772663163700125420195118047008360658e-6 + x * 2.81369833337188431358280911630401974906330455923616e-7)))))))))<br> 
&nbsp;&nbsp;&nbsp;[-2.71406412827174505775085010461449926572460824320373e-11;2.71406412827174505775085010461449926572460824320373e-11]<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","taylorform","taylorform");?>, <?php linkTo("command","diff","diff");?>, <?php linkTo("command","autodiff","autodiff");?>, <?php linkTo("command","taylor","taylor");?>, <?php linkTo("command","remez","remez");?> 
</div> 
