<a name="searchgal"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","searchgal","searchgal");?> 
<span class="smallDescription">searches for a preimage of a function such that the rounding the image yields an error smaller than a constant 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library name:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_searchgal(sollya_obj_t, sollya_obj_t, sollya_obj_t,</span> 
<span class="commandline type">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;sollya_obj_t, sollya_obj_t, sollya_obj_t)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","searchgal","searchgal");?>(<span class="arg">function</span>, <span class="arg">start</span>, <span class="arg">preimage precision</span>, <span class="arg">steps</span>, <span class="arg">format</span>, <span class="arg">error bound</span>) : (<span class="type">function</span>, <span class="type">constant</span>, <span class="type">integer</span>, <span class="type">integer</span>, <span class="type">HP|halfprecision|SG|single|D|double|DE|doubleextended|DD|doubledouble|QD|quad|TD|tripledouble</span>, <span class="type">constant</span>) -&gt; <span class="type">list</span></span> 
<span class="commandline"><?php linkTo("command","searchgal","searchgal");?>(<span class="arg">list of functions</span>, <span class="arg">start</span>, <span class="arg">preimage precision</span>, <span class="arg">steps</span>, <span class="arg">list of format</span>, <span class="arg">list of error bounds</span>) : (<span class="type">list</span>, <span class="type">constant</span>, <span class="type">integer</span>, <span class="type">integer</span>, <span class="type">list</span>, <span class="type">list</span>) -&gt; <span class="type">list</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">function</span> represents the function to be considered</li> 
<li><span class="arg">start</span> represents a value around which the search is to be performed</li> 
<li><span class="arg">preimage precision</span> represents the precision (discretization) for the eligible preimage values</li> 
<li><span class="arg">steps</span> represents the binary logarithm (log2) of the number of search steps to be performed</li> 
<li><span class="arg">format</span> represents the format the image of the function is to be rounded to</li> 
<li><span class="arg">error bound</span> represents a upper bound on the relative rounding error when rounding the image</li> 
<li><span class="arg">list of functions</span> represents the functions to be considered</li> 
<li><span class="arg">list of formats</span> represents the respective formats the images of the functions are to be rounded to</li> 
<li><span class="arg">list of error bounds</span> represents a upper bound on the relative rounding error when rounding the image</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>The command <?php linkTo("command","searchgal","searchgal");?> searches for a preimage z of function 
<span class="arg">function</span> or a list of functions <span class="arg">list of functions</span> such that 
z is a floating-point number with <span class="arg">preimage precision</span> 
significant mantissa bits and the image y of the function, 
respectively each image yi of the functions, rounds to 
format <span class="arg">format</span> respectively to the corresponding format in <span class="arg">list of format</span>  
with a relative rounding error less than <span class="arg">error bound</span> 
respectively the corresponding value in <span class="arg">list of error bounds</span>. During 
this search, at most 2^<span class="arg">steps</span> attempts are made. The search 
starts with a preimage value equal to <span class="arg">start</span>. This value is then 
increased and decreased by 1 ulp in precision <span class="arg">preimage precision</span>  
until a value is found or the step limit is reached. 
<br><br> 
If the search finds an appropriate preimage z, <?php linkTo("command","searchgal","searchgal");?> 
evaluates to a list containing this value. Otherwise, <?php linkTo("command","searchgal","searchgal");?> 
evaluates to an empty list. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; searchgal(log(x),2,53,15,DD,1b-112);<br> 
&nbsp;&nbsp;&nbsp;[| |]<br> 
&nbsp;&nbsp;&nbsp;&gt; searchgal(log(x),2,53,18,DD,1b-112);<br> 
&nbsp;&nbsp;&nbsp;[|2.0000000000384972054234822280704975128173828125|]<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; f = exp(x);<br> 
&nbsp;&nbsp;&nbsp;&gt; s = searchgal(f,2,53,18,DD,1b-112);<br> 
&nbsp;&nbsp;&nbsp;&gt; if (s != [||]) then {<br> 
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;v = s[0];<br> 
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;print("The rounding error is 2^(",evaluate(log2(abs(DD(f)/f - 1)),v),")");<br> 
&nbsp;&nbsp;&nbsp;&nbsp; } else print("No value found");<br> 
&nbsp;&nbsp;&nbsp;The rounding error is 2^( -1.12106878438809380148206984258358542322113874177832e2 )<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; searchgal([|sin(x),cos(x)|],1,53,15,[|D,D|],[|1b-62,1b-60|]);<br> 
&nbsp;&nbsp;&nbsp;[|1.00000000000159494639717649988597258925437927246094|]<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","round","round");?>, <?php linkTo("command","double","double");?>, <?php linkTo("command","doubledouble","doubledouble");?>, <?php linkTo("command","tripledouble","tripledouble");?>, <?php linkTo("command","evaluate","evaluate");?>, <?php linkTo("command","worstcase","worstcase");?> 
</div> 
