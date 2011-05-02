<a name="mantissa"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","mantissa","mantissa");?> 
<span class="smallDescription">returns the integer mantissa of a number. 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","mantissa","mantissa");?>(<span class="arg">x</span>) : <span class="type">constant</span> -&gt; <span class="type">integer</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">x</span> is a dyadic number.</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","mantissa","mantissa");?>(x) is by definition x if x equals 0, NaN, or Inf. 
</li><li>If <span class="arg">x</span> is not zero, it can be uniquely written as x = m*2^e where 
m is an odd integer and e is an integer. <?php linkTo("command","mantissa","mantissa");?>(x) returns m.  
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; a=round(Pi,20,RN);<br> 
&nbsp;&nbsp;&nbsp;&gt; e=exponent(a);<br> 
&nbsp;&nbsp;&nbsp;&gt; m=mantissa(a);<br> 
&nbsp;&nbsp;&nbsp;&gt; m;<br> 
&nbsp;&nbsp;&nbsp;411775<br> 
&nbsp;&nbsp;&nbsp;&gt; a-m*2^e;<br> 
&nbsp;&nbsp;&nbsp;0<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","exponent","exponent");?>, <?php linkTo("command","precision","precision");?> 
</div> 
