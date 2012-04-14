<a name="roundcorrectly"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","roundcorrectly","roundcorrectly");?> 
<span class="smallDescription">rounds an approximation range correctly to some precision 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library name:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_roundcorrectly(sollya_obj_t)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","roundcorrectly","roundcorrectly");?>(<span class="arg">range</span>) : <span class="type">range</span> -&gt; <span class="type">constant</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">range</span> represents a range in which an exact value lies</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>Let <span class="arg">range</span> be a range of values, determined by some approximation 
process, safely bounding an unknown value v. The command 
<?php linkTo("command","roundcorrectly","roundcorrectly");?>(<span class="arg">range</span>) determines a precision such that for this precision, 
rounding to the nearest any value in <span class="arg">range</span> yields to the same 
result, i.e. to the correct rounding of v. 
<br><br> 
If no such precision exists, a warning is displayed and <?php linkTo("command","roundcorrectly","roundcorrectly");?> 
evaluates to NaN. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; printbinary(roundcorrectly([1.010001_2; 1.0101_2]));<br> 
&nbsp;&nbsp;&nbsp;1.01_2<br> 
&nbsp;&nbsp;&nbsp;&gt; printbinary(roundcorrectly([1.00001_2; 1.001_2]));<br> 
&nbsp;&nbsp;&nbsp;1_2<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; roundcorrectly([-1; 1]);<br> 
&nbsp;&nbsp;&nbsp;@NaN@<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","round","round");?>, <?php linkTo("command","mantissa","mantissa");?>, <?php linkTo("command","exponent","exponent");?>, <?php linkTo("command","precision","precision");?> 
</div> 
