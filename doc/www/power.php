<a name="power"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","power","^");?> 
<span class="smallDescription">power function 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><span class="arg">function1</span> <?php linkTo("command","power","^");?> <span class="arg">function2</span> : (<span class="type">function</span>, <span class="type">function</span>) -&gt; <span class="type">function</span></span> 
<span class="commandline"><span class="arg">interval1</span> <?php linkTo("command","power","^");?> <span class="arg">interval2</span> : (<span class="type">range</span>, <span class="type">range</span>) -&gt; <span class="type">range</span></span> 
<span class="commandline"><span class="arg">interval1</span> <?php linkTo("command","power","^");?> <span class="arg">constant</span> : (<span class="type">range</span>, <span class="type">constant</span>) -&gt; <span class="type">range</span></span> 
<span class="commandline"><span class="arg">interval1</span> <?php linkTo("command","power","^");?> <span class="arg">constant</span> : (<span class="type">constant</span>, <span class="type">range</span>) -&gt; <span class="type">range</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">function1</span> and <span class="arg">function2</span> represent functions</li> 
<li><span class="arg">interval1</span> and <span class="arg">interval2</span> represent intervals (ranges)</li> 
<li><span class="arg">constant</span> represents a constant or constant expression</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","power","^");?> represents the power (function) on reals.  
The expression <span class="arg">function1</span> <?php linkTo("command","power","^");?> <span class="arg">function2</span> stands for 
the function composed of the power function and the two 
functions <span class="arg">function1</span> and <span class="arg">function2</span>, where <span class="arg">function1</span> is 
the base and <span class="arg">function2</span> the exponent. 
If <span class="arg">function2</span> is a constant integer, <?php linkTo("command","power","^");?> is defined 
on negative values of <span class="arg">function1</span>. Otherwise <?php linkTo("command","power","^");?> 
is defined as exp(y * log(x)). 
</li><li>Note that whenever several <?php linkTo("command","power","^");?> are composed, the priority goes 
to the last <?php linkTo("command","power","^");?>. This corresponds to the natural way of 
thinking when a tower of powers is written on a paper. 
Thus, 2^3^5 is interpreted as 2^(3^5). 
</li><li><?php linkTo("command","power","^");?> can be used for interval arithmetic on intervals 
(ranges). <?php linkTo("command","power","^");?> will evaluate to an interval that safely 
encompasses all images of the power function with arguments 
varying in the given intervals. If the intervals given contain points 
where the power function is not defined, infinities and NaNs will be 
produced in the output interval.  Any combination of intervals with 
intervals or constants (resp. constant expressions) is 
supported. However, it is not possible to represent families of 
functions using an interval as one argument and a function (varying in 
the free variable) as the other one. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; 5 ^ 2;<br> 
&nbsp;&nbsp;&nbsp;25<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; x ^ 2;<br> 
&nbsp;&nbsp;&nbsp;x^2<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; 3 ^ (-5);<br> 
&nbsp;&nbsp;&nbsp;4.1152263374485596707818930041152263374485596707818e-3<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 4: </h2> 
&nbsp;&nbsp;&nbsp;&gt; (-3) ^ (-2.5);<br> 
&nbsp;&nbsp;&nbsp;@NaN@<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 5: </h2> 
&nbsp;&nbsp;&nbsp;&gt; diff(sin(x) ^ exp(x));<br> 
&nbsp;&nbsp;&nbsp;sin(x)^exp(x) * ((cos(x) * exp(x)) / sin(x) + exp(x) * log(sin(x)))<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 6: </h2> 
&nbsp;&nbsp;&nbsp;&gt; 2^3^5;<br> 
&nbsp;&nbsp;&nbsp;1.4134776518227074636666380005943348126619871175005e73<br> 
&nbsp;&nbsp;&nbsp;&gt; (2^3)^5;<br> 
&nbsp;&nbsp;&nbsp;32768<br> 
&nbsp;&nbsp;&nbsp;&gt; 2^(3^5);<br> 
&nbsp;&nbsp;&nbsp;1.4134776518227074636666380005943348126619871175005e73<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 7: </h2> 
&nbsp;&nbsp;&nbsp;&gt; [1;2] ^ [3;4];<br> 
&nbsp;&nbsp;&nbsp;[1;1.60000000000000000000000000000000000000000000000007e1]<br> 
&nbsp;&nbsp;&nbsp;&gt; [1;2] ^ 17;<br> 
&nbsp;&nbsp;&nbsp;[1;131072]<br> 
&nbsp;&nbsp;&nbsp;&gt; 13 ^ [-4;17];<br> 
&nbsp;&nbsp;&nbsp;[3.501277966457757081334687160813696999404782745702e-5;8650415919381337933]<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","plus","+");?>, <?php linkTo("command","minus","-");?>, <?php linkTo("command","mult","*");?>, <?php linkTo("command","divide","/");?> 
</div> 
