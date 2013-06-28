<a name="rationalapprox"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","rationalapprox","rationalapprox");?> 
<span class="smallDescription">returns a fraction close to a given number. 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library name:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_rationalapprox(sollya_obj_t, sollya_obj_t)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","rationalapprox","rationalapprox");?>(<span class="arg">x</span>,<span class="arg">n</span>) : (<span class="type">constant</span>, <span class="type">integer</span>) -&gt; <span class="type">function</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">x</span> is a number to approximate.</li> 
<li><span class="arg">n</span> is a integer (representing a format).</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","rationalapprox","rationalapprox");?>(<span class="arg">x</span>,<span class="arg">n</span>) returns a constant function of the form a/b where a and b are 
integers. The value a/b is an approximation of <span class="arg">x</span>. The quality of this  
approximation is determined by the parameter <span class="arg">n</span> that indicates the number of 
correct bits that a/b should have. 
</li><li>The command is not safe in the sense that it is not ensured that the error  
between a/b and <span class="arg">x</span> is less than 2^(-n). 
</li><li>The following algorithm is used: <span class="arg">x</span> is first rounded downwards and upwards to 
a format of <span class="arg">n</span> bits, thus obtaining an interval [xl,xu]. This interval is then 
developped into a continued fraction as far as the representation is the same 
for every elements of [xl,xu]. The corresponding fraction is returned. 
</li><li>Since rational numbers are not a primitive object of Sollya, the fraction is 
returned as a constant function. This can be quite amazing, because Sollya 
immediately simplifies a constant function by evaluating it when the constant 
has to be displayed. 
To avoid this, you can use <?php linkTo("command","print","print");?> (that displays the expression representing 
the constant and not the constant itself) or the commands <?php linkTo("command","numerator","numerator");?>  
and <?php linkTo("command","denominator","denominator");?>. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; pi10 = rationalapprox(Pi,10);<br> 
&nbsp;&nbsp;&nbsp;&gt; pi50 = rationalapprox(Pi,50);<br> 
&nbsp;&nbsp;&nbsp;&gt; pi100 = rationalapprox(Pi,100);<br> 
&nbsp;&nbsp;&nbsp;&gt; print( pi10, ": ", dirtysimplify(floor(-log2(abs(pi10-Pi)/Pi))), "bits." );<br> 
&nbsp;&nbsp;&nbsp;3.140625 :&nbsp;&nbsp;11 bits.<br> 
&nbsp;&nbsp;&nbsp;&gt; print( pi50, ": ", dirtysimplify(floor(-log2(abs(pi50-Pi)/Pi))), "bits." );<br> 
&nbsp;&nbsp;&nbsp;85563208 / 27235615 :&nbsp;&nbsp;51 bits.<br> 
&nbsp;&nbsp;&nbsp;&gt; print( pi100, ": ", dirtysimplify(floor(-log2(abs(pi100-Pi)/Pi))), "bits." );<br> 
&nbsp;&nbsp;&nbsp;4422001152019829 / 1407566683404023 :&nbsp;&nbsp;100 bits.<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; a=0.1;<br> 
&nbsp;&nbsp;&nbsp;&gt; b=rationalapprox(a,4);<br> 
&nbsp;&nbsp;&nbsp;&gt; numerator(b); denominator(b);<br> 
&nbsp;&nbsp;&nbsp;1<br> 
&nbsp;&nbsp;&nbsp;10<br> 
&nbsp;&nbsp;&nbsp;&gt; print(dirtysimplify(floor(-log2(abs((b-a)/a)))), "bits.");<br> 
&nbsp;&nbsp;&nbsp;166 bits.<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","print","print");?>, <?php linkTo("command","numerator","numerator");?>, <?php linkTo("command","denominator","denominator");?>, <?php linkTo("command","rationalmode","rationalmode");?> 
</div> 
