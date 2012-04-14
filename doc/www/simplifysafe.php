<a name="simplifysafe"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","simplifysafe","simplifysafe");?> 
<span class="smallDescription">simplifies an expression representing a function 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library name:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_simplifysafe(sollya_obj_t)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","simplifysafe","simplifysafe");?>(<span class="arg">function</span>) : <span class="type">function</span> -&gt; <span class="type">function</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">function</span> represents the expression to be simplified</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>The command <?php linkTo("command","simplifysafe","simplifysafe");?> simplifies the expression given in argument 
representing the function <span class="arg">function</span>.  The command <?php linkTo("command","simplifysafe","simplifysafe");?> does not 
endanger the safety of computations even in Sollya's floating-point 
environment: the function returned is mathematically equal to the 
function <span class="arg">function</span>.  
<br><br> 
Remark that the simplification provided by <?php linkTo("command","simplifysafe","simplifysafe");?> is not perfect: 
they may exist simpler equivalent expressions for expressions returned 
by <?php linkTo("command","simplifysafe","simplifysafe");?>. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; print(simplifysafe((6 + 2) + (5 + exp(0)) * x));<br> 
&nbsp;&nbsp;&nbsp;8 + 6 * x<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; print(simplifysafe((log(x - x + 1) + asin(1))));<br> 
&nbsp;&nbsp;&nbsp;(pi) / 2<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; print(simplifysafe((log(x - x + 1) + asin(1)) - (atan(1) * 2)));<br> 
&nbsp;&nbsp;&nbsp;(pi) / 2 - (pi) / 4 * 2<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","simplify","simplify");?>, <?php linkTo("command","autosimplify","autosimplify");?>, <?php linkTo("command","rationalmode","rationalmode");?>, <?php linkTo("command","horner","horner");?> 
</div> 
