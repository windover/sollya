<a name="subpoly"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","subpoly","subpoly");?> 
<span class="smallDescription">restricts the monomial basis of a polynomial to a list of monomials 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library name:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_subpoly(sollya_obj_t, sollya_obj_t)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","subpoly","subpoly");?>(<span class="arg">polynomial</span>, <span class="arg">list</span>) : (<span class="type">function</span>, <span class="type">list</span>) -&gt; <span class="type">function</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">polynomial</span> represents the polynomial the coefficients are taken from</li> 
<li><span class="arg">list</span> represents the list of monomials to be taken</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","subpoly","subpoly");?> extracts the coefficients of a polynomial <span class="arg">polynomial</span> and builds up a 
new polynomial out of those coefficients associated to monomial degrees figuring in 
the list <span class="arg">list</span>.  
<br><br> 
If <span class="arg">polynomial</span> represents a function that is not a polynomial, subpoly returns 0. 
<br><br> 
If <span class="arg">list</span> is a list that is end-elliptic, let be j the last value explicitly specified 
in the list. All coefficients of the polynomial associated to monomials greater or 
equal to j are taken. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; p = taylor(exp(x),5,0);<br> 
&nbsp;&nbsp;&nbsp;&gt; s = subpoly(p,[|1,3,5|]);<br> 
&nbsp;&nbsp;&nbsp;&gt; print(p);<br> 
&nbsp;&nbsp;&nbsp;1 + x * (1 + x * (0.5 + x * (1 / 6 + x * (1 / 24 + x / 120))))<br> 
&nbsp;&nbsp;&nbsp;&gt; print(s);<br> 
&nbsp;&nbsp;&nbsp;x * (1 + x^2 * (1 / 6 + x^2 / 120))<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; p = remez(atan(x),10,[-1,1]);<br> 
&nbsp;&nbsp;&nbsp;&gt; subpoly(p,[|1,3,5...|]);<br> 
&nbsp;&nbsp;&nbsp;x * (0.99986632941452949026018468446163586361700915018231 + x^2 * (-0.33030478502455936362667794059988443130926433421739 + x^2 * (0.18015929317818756462894237037824735129130095574422 + x * (2.28455841154247882851125015653585766424298569630719e-9 + x * (-8.5156349064111377895500552996061844977507560037484e-2 + x * (-2.71756340962775019916818769239340943524383018921799e-9 + x * (2.08451134307114729373239910549169872454686955894998e-2 + x * 1.10889861181129057657199664386826630081793400489512e-9)))))))<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; subpoly(exp(x),[|1,2,3|]);<br> 
&nbsp;&nbsp;&nbsp;0<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","roundcoefficients","roundcoefficients");?>, <?php linkTo("command","taylor","taylor");?>, <?php linkTo("command","remez","remez");?>, <?php linkTo("command","fpminimax","fpminimax");?>, <?php linkTo("command","implementpoly","implementpoly");?> 
</div> 
