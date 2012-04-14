<a name="numerator"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","numerator","numerator");?> 
<span class="smallDescription">gives the numerator of an expression 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library name:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_numerator(sollya_obj_t)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","numerator","numerator");?>(<span class="arg">expr</span>) : <span class="type">function</span> -&gt; <span class="type">function</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">expr</span> represents an expression</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>If <span class="arg">expr</span> represents a fraction <span class="arg">expr1</span>/<span class="arg">expr2</span>, <?php linkTo("command","numerator","numerator");?>(<span class="arg">expr</span>) 
returns the numerator of this fraction, i.e. <span class="arg">expr1</span>. 
<br><br> 
If <span class="arg">expr</span> represents something else, <?php linkTo("command","numerator","numerator");?>(<span class="arg">expr</span>)  
returns the expression itself, i.e. <span class="arg">expr</span>. 
<br><br> 
Note that for all expressions <span class="arg">expr</span>, <?php linkTo("command","numerator","numerator");?>(<span class="arg">expr</span>) <?php linkTo("command","divide","/");?> <?php linkTo("command","denominator","denominator");?>(<span class="arg">expr</span>) 
is equal to <span class="arg">expr</span>. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; numerator(5/3);<br> 
&nbsp;&nbsp;&nbsp;5<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; numerator(exp(x));<br> 
&nbsp;&nbsp;&nbsp;exp(x)<br> 
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
<span class="category">See also: </span><?php linkTo("command","denominator","denominator");?>, <?php linkTo("command","rationalmode","rationalmode");?> 
</div> 
