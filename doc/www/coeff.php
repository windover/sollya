<a name="coeff"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","coeff","coeff");?> 
<span class="smallDescription">gives the coefficient of degree n of a polynomial 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library name:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_coeff(sollya_obj_t, sollya_obj_t)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","coeff","coeff");?>(<span class="arg">f</span>,<span class="arg">n</span>) : (<span class="type">function</span>, <span class="type">integer</span>) -&gt; <span class="type">constant</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">f</span> is a function (usually a polynomial).</li> 
<li><span class="arg">n</span> is an integer</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>If <span class="arg">f</span> is a polynomial, <?php linkTo("command","coeff","coeff");?>(<span class="arg">f</span>, <span class="arg">n</span>) returns the coefficient of 
degree <span class="arg">n</span> in <span class="arg">f</span>. 
</li><li>If <span class="arg">f</span> is a function that is not a polynomial, <?php linkTo("command","coeff","coeff");?>(<span class="arg">f</span>, <span class="arg">n</span>) returns 0. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; coeff((1+x)^5,3);<br> 
&nbsp;&nbsp;&nbsp;10<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; coeff(sin(x),0);<br> 
&nbsp;&nbsp;&nbsp;0<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","degree","degree");?>, <?php linkTo("command","roundcoefficients","roundcoefficients");?>, <?php linkTo("command","subpoly","subpoly");?> 
</div> 
