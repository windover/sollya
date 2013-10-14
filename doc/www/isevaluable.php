<a name="isevaluable"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","isevaluable","isevaluable");?> 
<span class="smallDescription">tests whether a function can be evaluated at a point  
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","isevaluable","isevaluable");?>(<span class="arg">function</span>, <span class="arg">constant</span>) : (<span class="type">function</span>, <span class="type">constant</span>) -&gt; <span class="type">boolean</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">function</span> represents a function</li> 
<li><span class="arg">constant</span> represents a constant point</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","isevaluable","isevaluable");?> applied to function <span class="arg">function</span> and a constant <span class="arg">constant</span> returns 
a boolean indicating whether or not a subsequent call to <?php linkTo("command","evaluate","evaluate");?> on the 
same function <span class="arg">function</span> and constant <span class="arg">constant</span> will produce a numerical 
result or NaN. This means <?php linkTo("command","isevaluable","isevaluable");?> returns false iff <?php linkTo("command","evaluate","evaluate");?> will return NaN. 
</li><li>The command <?php linkTo("command","isevaluable","isevaluable");?> is now considered DEPRECATED in Sollya. 
As checks for NaNs are now possible in Sollya, the command <?php linkTo("command","isevaluable","isevaluable");?> 
can be fully emulated with a call to evaluate and a couple of tests,  
as shown below in the last example. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; isevaluable(sin(pi * 1/x), 0.75);<br> 
&nbsp;&nbsp;&nbsp;true<br> 
&nbsp;&nbsp;&nbsp;&gt; print(evaluate(sin(pi * 1/x), 0.75));<br> 
&nbsp;&nbsp;&nbsp;-0.86602540378443864676372317075293618347140262690518<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; isevaluable(sin(pi * 1/x), 0.5);<br> 
&nbsp;&nbsp;&nbsp;true<br> 
&nbsp;&nbsp;&nbsp;&gt; print(evaluate(sin(pi * 1/x), 0.5));<br> 
&nbsp;&nbsp;&nbsp;[-1.72986452514381269516508615031098129542836767991679e-12715;7.5941198201187963145069564314525661706039084390067e-12716]<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; isevaluable(sin(pi * 1/x), 0);<br> 
&nbsp;&nbsp;&nbsp;true<br> 
&nbsp;&nbsp;&nbsp;&gt; print(evaluate(sin(pi * 1/x), 0));<br> 
&nbsp;&nbsp;&nbsp;[-1;1]<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 4: </h2> 
&nbsp;&nbsp;&nbsp;&gt; procedure isEvaluableEmulation(f, c) {<br> 
&nbsp;&nbsp;&nbsp;&nbsp; 	&nbsp;&nbsp;return match evaluate(f, c) with <br> 
&nbsp;&nbsp;&nbsp;&nbsp; 	&nbsp;&nbsp;	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;NaN : (false)<br> 
&nbsp;&nbsp;&nbsp;&nbsp; 		&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[NaN;NaN] : (false)<br> 
&nbsp;&nbsp;&nbsp;&nbsp; 		&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;default : (true);<br> 
&nbsp;&nbsp;&nbsp;&nbsp; };<br> 
&nbsp;&nbsp;&nbsp;&gt; isEvaluableEmulation(sin(pi * 1/x), 0.75);<br> 
&nbsp;&nbsp;&nbsp;true<br> 
&nbsp;&nbsp;&nbsp;&gt; isEvaluableEmulation(sin(pi * 1/x), 0.5);<br> 
&nbsp;&nbsp;&nbsp;true<br> 
&nbsp;&nbsp;&nbsp;&gt; isEvaluableEmulation(sin(pi * 1/x), 0);<br> 
&nbsp;&nbsp;&nbsp;true<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","evaluate","evaluate");?> 
</div> 
