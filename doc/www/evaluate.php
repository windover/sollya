<a name="evaluate"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","evaluate","evaluate");?> 
<span class="smallDescription">evaluates a function at a constant point or in a range 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","evaluate","evaluate");?>(<span class="arg">function</span>, <span class="arg">constant</span>) : (<span class="type">function</span>, <span class="type">constant</span>) -&gt; <span class="type">constant</span> | <span class="type">range</span></span> 
<span class="commandline"><?php linkTo("command","evaluate","evaluate");?>(<span class="arg">function</span>, <span class="arg">range</span>) : (<span class="type">function</span>, <span class="type">range</span>) -&gt; <span class="type">range</span></span> 
<span class="commandline"><?php linkTo("command","evaluate","evaluate");?>(<span class="arg">function</span>, <span class="arg">function2</span>) : (<span class="type">function</span>, <span class="type">function</span>) -&gt; <span class="type">function</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">function</span> represents a function</li> 
<li><span class="arg">constant</span> represents a constant point</li> 
<li><span class="arg">range</span> represents a range</li> 
<li><span class="arg">function2</span> represents a function that is not constant</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>If its second argument is a constant <span class="arg">constant</span>, <?php linkTo("command","evaluate","evaluate");?> evaluates 
its first argument <span class="arg">function</span> at the point indicated by 
<span class="arg">constant</span>. This evaluation is performed in a way that the result is a 
faithful rounding of the real value of the <span class="arg">function</span> at <span class="arg">constant</span> to 
the current global precision. If such a faithful rounding is not 
possible, <?php linkTo("command","evaluate","evaluate");?> returns a range surely encompassing the real value 
of the function <span class="arg">function</span> at <span class="arg">constant</span>. If even interval evaluation 
is not possible because the expression is undefined or numerically 
unstable, NaN will be produced. 
</li><li>If its second argument is a range <span class="arg">range</span>, <?php linkTo("command","evaluate","evaluate");?> evaluates its 
first argument <span class="arg">function</span> by interval evaluation on this range 
<span class="arg">range</span>. This ensures that the image domain of the function <span class="arg">function</span> 
on the preimage domain <span class="arg">range</span> is surely enclosed in the returned 
range. 
</li><li>In the case when the second argument is a range that is reduced to a 
single point (such that [1;1] for instance), the evaluation 
is performed in the same way as when the second argument is a constant but 
it produces a range as a result: <?php linkTo("command","evaluate","evaluate");?> automatically adjusts the precision 
of the intern computations and returns a range that contains at most three floating-point 
consecutive numbers in precision <?php linkTo("command","prec","prec");?>. This correponds to the same accuracy 
as a faithful rounding of the actual result. If such a faithful rounding 
is not possible, <?php linkTo("command","evaluate","evaluate");?> has the same behavior as in the case when the 
second argument is a constant. 
</li><li>If its second argument is a function <span class="arg">function2</span> that is not a 
constant, <?php linkTo("command","evaluate","evaluate");?> replaces all occurrences of the free variable in 
function <span class="arg">function</span> by function <span class="arg">function2</span>. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; midpointmode=on!;<br> 
&nbsp;&nbsp;&nbsp;&gt; print(evaluate(sin(pi * x), 2.25));<br> 
&nbsp;&nbsp;&nbsp;0.70710678118654752440084436210484903928483593768847<br> 
&nbsp;&nbsp;&nbsp;&gt; print(evaluate(sin(pi * x), [2.25; 2.25]));<br> 
&nbsp;&nbsp;&nbsp;0.707106781186547524400844362104849039284835937688~4/5~<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; print(evaluate(sin(pi * x), 2));<br> 
&nbsp;&nbsp;&nbsp;[-1.72986452514381269516508615031098129542836767991679e-12715;7.5941198201187963145069564314525661706039084390067e-12716]<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; print(evaluate(sin(pi * x), [2, 2.25]));<br> 
&nbsp;&nbsp;&nbsp;[-5.143390272677254630046998919961912407349224165421e-50;0.70710678118654752440084436210484903928483593768866]<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 4: </h2> 
&nbsp;&nbsp;&nbsp;&gt; print(evaluate(sin(pi * x), 2 + 0.25 * x));<br> 
&nbsp;&nbsp;&nbsp;sin((pi) * (2 + 0.25 * x))<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 5: </h2> 
&nbsp;&nbsp;&nbsp;&gt; print(evaluate(sin(pi * 1/x), 0));<br> 
&nbsp;&nbsp;&nbsp;[@NaN@;@NaN@]<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","isevaluable","isevaluable");?> 
</div> 
