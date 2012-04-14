<a name="dirtyinfnorm"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","dirtyinfnorm","dirtyinfnorm");?> 
<span class="smallDescription">computes a numerical approximation of the infinity norm of a function on an interval. 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library name:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_dirtyinfnorm(sollya_obj_t, sollya_obj_t)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","dirtyinfnorm","dirtyinfnorm");?>(<span class="arg">f</span>,<span class="arg">I</span>) : (<span class="type">function</span>, <span class="type">range</span>) -&gt; <span class="type">constant</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">f</span> is a function.</li> 
<li><span class="arg">I</span> is an interval.</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","dirtyinfnorm","dirtyinfnorm");?>(<span class="arg">f</span>,<span class="arg">I</span>) computes an approximation of the infinity norm of the  
given function f on the interval I, e.g. max {|f(x)|, x in I}. 
</li><li>The interval must be bound. If the interval contains one of -Inf or +Inf, the  
result of <?php linkTo("command","dirtyinfnorm","dirtyinfnorm");?> is NaN. 
</li><li>The result of this command depends on the global variables <?php linkTo("command","prec","prec");?> and <?php linkTo("command","points","points");?>. 
Therefore, the returned result is generally a good approximation of the exact 
infinity norm, with precision <?php linkTo("command","prec","prec");?>. However, the result is generally  
underestimated and should not be used when safety is critical. 
Use <?php linkTo("command","infnorm","infnorm");?> instead. 
</li><li>The following algorithm is used: let n be the value of variable <?php linkTo("command","points","points");?> 
and t be the value of variable <?php linkTo("command","prec","prec");?>. 
<ul> 
<li> Evaluate |f| at n evenly distributed points in the 
     interval I. The evaluation are faithful roundings of the exact 
     results at precision t. 
</li><li> Whenever the derivative of f changes its sign for two consecutive  
     points, find an approximation x of its zero with precision t. 
     Then compute a faithful rounding of |f(x)| at precision t. 
</li><li> Return the maximum of all computed values. 
</li></ul> 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; dirtyinfnorm(sin(x),[-10;10]);<br> 
&nbsp;&nbsp;&nbsp;1<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; prec=15!;<br> 
&nbsp;&nbsp;&nbsp;&gt; dirtyinfnorm(exp(cos(x))*sin(x),[0;5]);<br> 
&nbsp;&nbsp;&nbsp;1.45856<br> 
&nbsp;&nbsp;&nbsp;&gt; prec=40!;<br> 
&nbsp;&nbsp;&nbsp;&gt; dirtyinfnorm(exp(cos(x))*sin(x),[0;5]);<br> 
&nbsp;&nbsp;&nbsp;1.458528537135<br> 
&nbsp;&nbsp;&nbsp;&gt; prec=100!;<br> 
&nbsp;&nbsp;&nbsp;&gt; dirtyinfnorm(exp(cos(x))*sin(x),[0;5]);<br> 
&nbsp;&nbsp;&nbsp;1.458528537136237644438147455024<br> 
&nbsp;&nbsp;&nbsp;&gt; prec=200!;<br> 
&nbsp;&nbsp;&nbsp;&gt; dirtyinfnorm(exp(cos(x))*sin(x),[0;5]);<br> 
&nbsp;&nbsp;&nbsp;1.458528537136237644438147455023841718299214087993682374094153<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; dirtyinfnorm(x^2, [log(0);log(1)]);<br> 
&nbsp;&nbsp;&nbsp;@NaN@<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","prec","prec");?>, <?php linkTo("command","points","points");?>, <?php linkTo("command","infnorm","infnorm");?>, <?php linkTo("command","checkinfnorm","checkinfnorm");?>, <?php linkTo("command","supnorm","supnorm");?> 
</div> 
