<a name="denominator"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","denominator","denominator");?> 
<span class="smallDescription">gives the denominator of an expression 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library name:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_denominator(sollya_obj_t)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","denominator","denominator");?>(<span class="arg">expr</span>) : <span class="type">function</span> -&gt; <span class="type">function</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">expr</span> represents an expression</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>If <span class="arg">expr</span> represents a fraction <span class="arg">expr1</span>/<span class="arg">expr2</span>, <?php linkTo("command","denominator","denominator");?>(<span class="arg">expr</span>) 
returns the denominator of this fraction, i.e. <span class="arg">expr2</span>. 
<br><br> 
If <span class="arg">expr</span> represents something else, <?php linkTo("command","denominator","denominator");?>(<span class="arg">expr</span>)  
returns 1. 
<br><br> 
Note that for all expressions <span class="arg">expr</span>, <?php linkTo("command","numerator","numerator");?>(<span class="arg">expr</span>) <?php linkTo("command","divide","/");?> <?php linkTo("command","denominator","denominator");?>(<span class="arg">expr</span>) 
is equal to <span class="arg">expr</span>. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; denominator(5/3);<br> 
&nbsp;&nbsp;&nbsp;3<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; denominator(exp(x));<br> 
&nbsp;&nbsp;&nbsp;1<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; a = 5/3;<br> 
&nbsp;&nbsp;&nbsp;&gt; b = numerator(a)/denominator(a);<br> 
&nbsp;&nbsp;&nbsp;&gt; print(a);<br> 
&nbsp;&nbsp;&nbsp;5 / 3<br> 
&nbsp;&nbsp;&nbsp;&gt; print(b);<br> 
&nbsp;&nbsp;&nbsp;5 / 3<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 4: </h2> 
&nbsp;&nbsp;&nbsp;&gt; a = exp(x/3);<br> 
&nbsp;&nbsp;&nbsp;&gt; b = numerator(a)/denominator(a);<br> 
&nbsp;&nbsp;&nbsp;&gt; print(a);<br> 
&nbsp;&nbsp;&nbsp;exp(x / 3)<br> 
&nbsp;&nbsp;&nbsp;&gt; print(b);<br> 
&nbsp;&nbsp;&nbsp;exp(x / 3)<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","numerator","numerator");?>, <?php linkTo("command","rationalmode","rationalmode");?> 
</div> 
