<a name="simplify"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","simplify","simplify");?> 
<span class="smallDescription">simplifies an expression representing a function 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library name:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_simplify(sollya_obj_t)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","simplify","simplify");?>(<span class="arg">function</span>) : <span class="type">function</span> -&gt; <span class="type">function</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">function</span> represents the expression to be simplified</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>The command <?php linkTo("command","simplify","simplify");?> simplifies constant subexpressions of the 
expression given in argument representing the function 
<span class="arg">function</span>. Those constant subexpressions are evaluated using 
floating-point arithmetic with the global precision <?php linkTo("command","prec","prec");?>. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; print(simplify(sin(pi * x)));<br> 
&nbsp;&nbsp;&nbsp;sin(3.14159265358979323846264338327950288419716939937508 * x)<br> 
&nbsp;&nbsp;&nbsp;&gt; print(simplify(erf(exp(3) + x * log(4))));<br> 
&nbsp;&nbsp;&nbsp;erf(2.00855369231876677409285296545817178969879078385544e1 + x * 1.3862943611198906188344642429163531361510002687205)<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; prec = 20!;<br> 
&nbsp;&nbsp;&nbsp;&gt; t = erf(0.5);<br> 
&nbsp;&nbsp;&nbsp;&gt; s = simplify(erf(0.5));<br> 
&nbsp;&nbsp;&nbsp;&gt; prec = 200!;<br> 
&nbsp;&nbsp;&nbsp;&gt; t;<br> 
&nbsp;&nbsp;&nbsp;0.5204998778130465376827466538919645287364515757579637000588058<br> 
&nbsp;&nbsp;&nbsp;&gt; s;<br> 
&nbsp;&nbsp;&nbsp;0.52050018310546875<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","simplifysafe","simplifysafe");?>, <?php linkTo("command","autosimplify","autosimplify");?>, <?php linkTo("command","prec","prec");?>, <?php linkTo("command","evaluate","evaluate");?>, <?php linkTo("command","horner","horner");?>, <?php linkTo("command","rationalmode","rationalmode");?> 
</div> 
