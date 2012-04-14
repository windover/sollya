<a name="composepolynomials"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","composepolynomials","composepolynomials");?> 
<span class="smallDescription">computes an approximation to the composition of two polynomials and bounds the error 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library name:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_composepolynomials(sollya_obj_t, sollya_obj_t)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","composepolynomials","composepolynomials");?>(<span class="arg">p</span>,<span class="arg">q</span>) : (<span class="type">function</span>, <span class="type">function</span>) -&gt; <span class="type">structure</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">p</span> and <span class="arg">q</span> are polynomials</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>Given two polynomials p and q, <?php linkTo("command","composepolynomials","composepolynomials");?>(<span class="arg">p</span>, <span class="arg">q</span>) computes an  
approximation r to the polynomial (p o q) and bounds the 
error polynomial r - (p o q) using interval arithmetic. 
</li><li><?php linkTo("command","composepolynomials","composepolynomials");?> always returns a structure containing two elements, 
poly and radii.  The element 
poly is contains the approximate composed polynomial 
r. The element radii contains a list of n + 1  
intervals ai bounding the coefficients of the 
error polynomial, which is of the same degree n as is the 
composed polynomial (p o q).  This is, there exist 
alphai in ai such that  
sum_i alphai * x^i = r(x) - (p o q)(x). 
</li><li>In the case when either of p or q is not a polynomial, <?php linkTo("command","composepolynomials","composepolynomials");?> 
behaves like <?php linkTo("command","substitute","substitute");?> used in a literate structure. The list of intervals 
bounding the coefficients of the error polynomial is returned empty. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; composepolynomials(1 + 2 * x + 3 * x^2 + 4 * x^3, 5 + 6 * x + 7 * x^2);<br> 
&nbsp;&nbsp;&nbsp;{ .radii = [|[0;0], [0;0], [0;0], [0;0], [0;0], [0;0], [0;0]|], .poly = 586 + x * (1992 + x * (4592 + x * (6156 + x * (6111 + x * (3528 + x * 1372))))) }<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; print(composepolynomials(1/5 * x + exp(17) + log(2) * x^2, x^4 + 1/3 * x^2));<br> 
&nbsp;&nbsp;&nbsp;{ .radii = [|[-3.58732406867153170156474773322218529607747057120388e-43;3.58732406867153170156474773322218529607747057120388e-43], [0;0], [-2.67276471009219564614053646715148187881519688010505e-51;2.67276471009219564614053646715148187881519688010505e-51], [0;0], [-1.06910588403687825845621458686059275152607875204202e-50;1.06910588403687825845621458686059275152607875204202e-50], [0;0], [-2.13821176807375651691242917372118550305215750408404e-50;2.13821176807375651691242917372118550305215750408404e-50], [0;0], [-1.06910588403687825845621458686059275152607875204202e-50;1.06910588403687825845621458686059275152607875204202e-50]|], .poly = 2.41549527535752982147754351803858238798675673527228e7 + x^2 * (6.6666666666666666666666666666666666666666666666666e-2 + x^2 * (0.277016353395549478824136902384241840897277792706698 + x^2 * (0.46209812037329687294482141430545104538366675624017 + x^2 * 0.693147180559945309417232121458176568075500134360259))) }<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; composepolynomials(sin(x),x + x^2);<br> 
&nbsp;&nbsp;&nbsp;{ .radii = [| |], .poly = sin(x * (1 + x)) }<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","substitute","substitute");?> 
</div> 
