<a name="degree"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","degree","degree");?> 
<span class="smallDescription">gives the degree of a polynomial. 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library name:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_degree(sollya_obj_t)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","degree","degree");?>(<span class="arg">f</span>) : <span class="type">function</span> -&gt; <span class="type">integer</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">f</span> is a function (usually a polynomial).</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>If <span class="arg">f</span> is a polynomial, <?php linkTo("command","degree","degree");?>(<span class="arg">f</span>) returns the degree of <span class="arg">f</span>. 
</li><li>Contrary to the usage, Sollya considers that the degree of the null polynomial 
is 0. 
</li><li>If <span class="arg">f</span> is a function that is not a polynomial, <?php linkTo("command","degree","degree");?>(<span class="arg">f</span>) returns -1. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; degree((1+x)*(2+5*x^2));<br> 
&nbsp;&nbsp;&nbsp;3<br> 
&nbsp;&nbsp;&nbsp;&gt; degree(0);<br> 
&nbsp;&nbsp;&nbsp;0<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; degree(sin(x));<br> 
&nbsp;&nbsp;&nbsp;-1<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","coeff","coeff");?>, <?php linkTo("command","subpoly","subpoly");?>, <?php linkTo("command","roundcoefficients","roundcoefficients");?> 
</div> 
