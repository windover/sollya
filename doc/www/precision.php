<a name="precision"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","precision","precision");?> 
<span class="smallDescription">returns the precision necessary to represent a number. 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library name:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_precision(sollya_obj_t)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","precision","precision");?>(<span class="arg">x</span>) : <span class="type">constant</span> -&gt; <span class="type">integer</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">x</span> is a dyadic number.</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","precision","precision");?>(x) is by definition |x| if x equals 0, NaN, or Inf. 
</li><li>If <span class="arg">x</span> is not zero, it can be uniquely written as x = m*2^e where 
m is an odd integer and e is an integer. <?php linkTo("command","precision","precision");?>(x) returns the number 
of bits necessary to write m in binary (i.e. ceil(log2(m))). 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; a=round(Pi,20,RN);<br> 
&nbsp;&nbsp;&nbsp;&gt; precision(a);<br> 
&nbsp;&nbsp;&nbsp;19<br> 
&nbsp;&nbsp;&nbsp;&gt; m=mantissa(a);<br> 
&nbsp;&nbsp;&nbsp;&gt; ceil(log2(m));<br> 
&nbsp;&nbsp;&nbsp;19<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","mantissa","mantissa");?>, <?php linkTo("command","exponent","exponent");?>, <?php linkTo("command","round","round");?> 
</div> 
