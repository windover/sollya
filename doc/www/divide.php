<a name="divide"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","divide","/");?> 
<span class="smallDescription">division function 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library names:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_div(sollya_obj_t, sollya_obj_t)</span> 
<span class="commandline type">sollya_obj_t sollya_lib_build_function_div(sollya_obj_t, sollya_obj_t)</span> 
<span class="commandline type">#define SOLLYA_DIV(x,y) sollya_lib_build_function_div((x), (y))</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><span class="arg">function1</span> <?php linkTo("command","divide","/");?> <span class="arg">function2</span> : (<span class="type">function</span>, <span class="type">function</span>) -&gt; <span class="type">function</span></span> 
<span class="commandline"><span class="arg">interval1</span> <?php linkTo("command","divide","/");?> <span class="arg">interval2</span> : (<span class="type">range</span>, <span class="type">range</span>) -&gt; <span class="type">range</span></span> 
<span class="commandline"><span class="arg">interval1</span> <?php linkTo("command","divide","/");?> <span class="arg">constant</span> : (<span class="type">range</span>, <span class="type">constant</span>) -&gt; <span class="type">range</span></span> 
<span class="commandline"><span class="arg">interval1</span> <?php linkTo("command","divide","/");?> <span class="arg">constant</span> : (<span class="type">constant</span>, <span class="type">range</span>) -&gt; <span class="type">range</span></span> 
 
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
<li><?php linkTo("command","divide","/");?> represents the division (function) on reals.  
The expression <span class="arg">function1</span> <?php linkTo("command","divide","/");?> <span class="arg">function2</span> stands for 
the function composed of the division function and the two 
functions <span class="arg">function1</span> and <span class="arg">function2</span>, where <span class="arg">function1</span> is 
the numerator and <span class="arg">function2</span> the denominator. 
</li><li><?php linkTo("command","divide","/");?> can be used for interval arithmetic on intervals 
(ranges). <?php linkTo("command","divide","/");?> will evaluate to an interval that safely 
encompasses all images of the division function with arguments 
varying in the given intervals. If the intervals given contain points 
where the division function is not defined, infinities and NaNs will be 
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
&nbsp;&nbsp;&nbsp;&gt; 5 / 2;<br> 
&nbsp;&nbsp;&nbsp;2.5<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; x / 2;<br> 
&nbsp;&nbsp;&nbsp;x * 0.5<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; x / x;<br> 
&nbsp;&nbsp;&nbsp;1<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 4: </h2> 
&nbsp;&nbsp;&nbsp;&gt; 3 / 0;<br> 
&nbsp;&nbsp;&nbsp;@NaN@<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 5: </h2> 
&nbsp;&nbsp;&nbsp;&gt; diff(sin(x) / exp(x));<br> 
&nbsp;&nbsp;&nbsp;(exp(x) * cos(x) - sin(x) * exp(x)) / exp(x)^2<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 6: </h2> 
&nbsp;&nbsp;&nbsp;&gt; [1;2] / [3;4];<br> 
&nbsp;&nbsp;&nbsp;[0.25;0.66666666666666666666666666666666666666666666666668]<br> 
&nbsp;&nbsp;&nbsp;&gt; [1;2] / 17;<br> 
&nbsp;&nbsp;&nbsp;[5.8823529411764705882352941176470588235294117647058e-2;0.11764705882352941176470588235294117647058823529412]<br> 
&nbsp;&nbsp;&nbsp;&gt; -13 / [4;17];<br> 
&nbsp;&nbsp;&nbsp;[-3.25;-0.76470588235294117647058823529411764705882352941175]<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","plus","+");?>, <?php linkTo("command","minus","-");?>, <?php linkTo("command","mult","*");?>, <?php linkTo("command","power","^");?> 
</div> 
