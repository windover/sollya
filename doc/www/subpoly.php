<a name="subpoly"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","subpoly","subpoly");?> 
<span class="smallDescription">restricts the monomial basis of a polynomial to a list of monomials 
</span> 
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
&nbsp;&nbsp;&nbsp;x * (0.99986632946591986997581285958052433296267358727229 + x^2 * (-0.330304785504861260596093435534236137298206064685038 + x^2 * (0.180159294636523467997437751178959039617773054107393 + x * (-1.21704858321866028906175835649390114311877360260197e-14 + x * (-8.5156350833702702996505336803770858918120961566741e-2 + x * (1.39681284176342339364451388757935358048374878126733e-14 + x * (2.0845114175434561643018447784809880955983412532269e-2 + x * (-5.6810131012579436265697622426011349460288598691964e-15))))))))<br> 
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
