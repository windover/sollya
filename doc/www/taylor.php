<a name="taylor"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","taylor","taylor");?> 
<span class="smallDescription">computes a Taylor expansion of a function in a point 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library name:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_taylor(sollya_obj_t, sollya_obj_t, sollya_obj_t)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","taylor","taylor");?>(<span class="arg">function</span>, <span class="arg">degree</span>, <span class="arg">point</span>) : (<span class="type">function</span>, <span class="type">integer</span>, <span class="type">constant</span>) -&gt; <span class="type">function</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">function</span> represents the function to be expanded</li> 
<li><span class="arg">degree</span> represents the degree of the expansion to be delivered</li> 
<li><span class="arg">point</span> represents the point in which the function is to be developped</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>The command <?php linkTo("command","taylor","taylor");?> returns an expression that is a Taylor expansion 
of function <span class="arg">function</span> in point <span class="arg">point</span> having the degree <span class="arg">degree</span>. 
<br><br> 
Let f be the function <span class="arg">function</span>, t be the point <span class="arg">point</span> and 
n be the degree <span class="arg">degree</span>. Then, <?php linkTo("command","taylor","taylor");?>(<span class="arg">function</span>,<span class="arg">degree</span>,<span class="arg">point</span>)  
evaluates to an expression mathematically equal to 
     f(t) + f'(t) * x + ... + 1/(n!) * f[n](t) * x^n. 
In other words, if p(x) denotes the polynomial returned by <?php linkTo("command","taylor","taylor");?>, 
p(x-t) is the Taylor polynomial of degree n of f developped at point t. 
<br><br> 
Remark that <?php linkTo("command","taylor","taylor");?> evaluates to 0 if the degree <span class="arg">degree</span> is negative. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; print(taylor(exp(x),3,1));<br> 
&nbsp;&nbsp;&nbsp;exp(1) + x * (exp(1) + x * (0.5 * exp(1) + x * exp(1) / 6))<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; print(taylor(asin(x),7,0));<br> 
&nbsp;&nbsp;&nbsp;x * (1 + x^2 * (1 / 6 + x^2 * (9 / 120 + x^2 * 225 / 5040)))<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; print(taylor(erf(x),6,0));<br> 
&nbsp;&nbsp;&nbsp;x * (1 / sqrt((pi) / 4) + x^2 * ((sqrt((pi) / 4) * 4 / (pi) * (-2)) / 6 + x^2 * (sqrt((pi) / 4) * 4 / (pi) * 12) / 120))<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","remez","remez");?>, <?php linkTo("command","fpminimax","fpminimax");?>, <?php linkTo("command","taylorform","taylorform");?> 
</div> 
