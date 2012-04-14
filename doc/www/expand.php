<a name="expand"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","expand","expand");?> 
<span class="smallDescription">expands polynomial subexpressions 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library name:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_expand(sollya_obj_t)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","expand","expand");?>(<span class="arg">function</span>) : <span class="type">function</span> -&gt; <span class="type">function</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">function</span> represents a function</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","expand","expand");?>(<span class="arg">function</span>) expands all polynomial subexpressions in function 
<span class="arg">function</span> as far as possible. Factors of sums are multiplied out, 
power operators with constant positive integer exponents are replaced 
by multiplications and divisions are multiplied out, i.e. denomiators 
are brought at the most interior point of expressions. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; print(expand(x^3));<br> 
&nbsp;&nbsp;&nbsp;x * x * x<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; print(expand((x + 2)^3 + 2 * x));<br> 
&nbsp;&nbsp;&nbsp;8 + 12 * x + 6 * x * x + x * x * x + 2 * x<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; print(expand(exp((x + (x + 3))^5)));<br> 
&nbsp;&nbsp;&nbsp;exp(243 + 405 * x + 270 * x * x + 90 * x * x * x + 15 * x * x * x * x + x * x * x * x * x + x * 405 + 108 * x * 5 * x + 54 * x * x * 5 * x + 12 * x * x * x * 5 * x + x * x * x * x * 5 * x + x * x * 270 + 27 * x * x * x * 10 + 9 * x * x * x * x * 10 + x * x * x * x * x * 10 + x * x * x * 90 + 6 * x * x * x * x * 10 + x * x * x * x * x * 10 + x * x * x * x * 5 * x + 15 * x * x * x * x + x * x * x * x * x)<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","simplify","simplify");?>, <?php linkTo("command","simplifysafe","simplifysafe");?>, <?php linkTo("command","horner","horner");?>, <?php linkTo("command","coeff","coeff");?>, <?php linkTo("command","degree","degree");?> 
</div> 
