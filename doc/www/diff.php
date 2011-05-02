<a name="diff"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","diff","diff");?> 
<span class="smallDescription">differentiation operator 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","diff","diff");?>(<span class="arg">function</span>) : <span class="type">function</span> -&gt; <span class="type">function</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">function</span> represents a function</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","diff","diff");?>(<span class="arg">function</span>) returns the symbolic derivative of the function 
<span class="arg">function</span> by the global free variable. 
<br><br> 
If <span class="arg">function</span> represents a function symbol that is externally bound 
to some code by <?php linkTo("command","library","library");?>, the derivative is performed as a symbolic 
annotation to the returned expression tree. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; diff(sin(x));<br> 
&nbsp;&nbsp;&nbsp;cos(x)<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; diff(x);<br> 
&nbsp;&nbsp;&nbsp;1<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; diff(x^x);<br> 
&nbsp;&nbsp;&nbsp;x^x * (1 + log(x))<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","library","library");?>, <?php linkTo("command","autodiff","autodiff");?>, <?php linkTo("command","taylor","taylor");?>, <?php linkTo("command","taylorform","taylorform");?> 
</div> 
