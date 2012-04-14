<a name="horner"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","horner","horner");?> 
<span class="smallDescription">brings all polynomial subexpressions of an expression to Horner form 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library name:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_horner(sollya_obj_t)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","horner","horner");?>(<span class="arg">function</span>) : <span class="type">function</span> -&gt; <span class="type">function</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">function</span> represents the expression to be rewritten in Horner form</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>The command <?php linkTo("command","horner","horner");?> rewrites the expression representing the function 
<span class="arg">function</span> in a way such that all polynomial subexpressions (or the 
whole expression itself, if it is a polynomial) are written in Horner 
form.  The command <?php linkTo("command","horner","horner");?> does not endanger the safety of 
computations even in Sollya's floating-point environment: the 
function returned is mathematically equal to the function <span class="arg">function</span>. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; print(horner(1 + 2 * x + 3 * x^2));<br> 
&nbsp;&nbsp;&nbsp;1 + x * (2 + x * 3)<br> 
&nbsp;&nbsp;&nbsp;&gt; print(horner((x + 1)^7));<br> 
&nbsp;&nbsp;&nbsp;1 + x * (7 + x * (21 + x * (35 + x * (35 + x * (21 + x * (7 + x))))))<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; print(horner(exp((x + 1)^5) - log(asin(x + x^3) + x)));<br> 
&nbsp;&nbsp;&nbsp;exp(1 + x * (5 + x * (10 + x * (10 + x * (5 + x))))) - log(asin(x * (1 + x^2)) + x)<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","canonical","canonical");?>, <?php linkTo("command","print","print");?>, <?php linkTo("command","coeff","coeff");?>, <?php linkTo("command","degree","degree");?>, <?php linkTo("command","autosimplify","autosimplify");?>, <?php linkTo("command","simplifysafe","simplifysafe");?> 
</div> 
