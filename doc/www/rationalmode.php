<a name="rationalmode"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","rationalmode","rationalmode");?> 
<span class="smallDescription">global variable controlling if rational arithmetic is used or not. 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library names:</h2> 
<span class="commandline type">void sollya_lib_set_rationalmode_and_print(sollya_obj_t)</span> 
<span class="commandline type">void sollya_lib_set_rationalmode(sollya_obj_t)</span> 
<span class="commandline type">sollya_obj_t sollya_lib_get_rationalmode()</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","rationalmode","rationalmode");?> = <span class="arg">activation value</span> : <span class="type">on|off</span> -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","rationalmode","rationalmode");?> = <span class="arg">activation value</span> ! : <span class="type">on|off</span> -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","rationalmode","rationalmode");?> : <span class="type">on|off</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">activation value</span> controls if rational arithmetic should be used or not</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","rationalmode","rationalmode");?> is a global variable. When its value is <?php linkTo("command","off","off");?>, which is the default, 
Sollya will not use rational arithmetic to simplify expressions. All computations, 
including the evaluation of constant expressions given on the Sollya prompt, 
will be performed using floating-point and interval arithmetic. Constant expressions 
will be approximated by floating-point numbers, which are in most cases faithful  
roundings of the expressions, when shown at the prompt.  
</li><li>When the value of the global variable <?php linkTo("command","rationalmode","rationalmode");?> is <?php linkTo("command","on","on");?>, Sollya will use  
rational arithmetic when simplifying expressions. Constant expressions, given  
at the Sollya prompt, will be simplified to rational numbers and displayed  
as such when they are in the set of the rational numbers. Otherwise, flaoting-point 
and interval arithmetic will be used to compute a floating-point approximation, 
which is in most cases a faithful rounding of the constant expression. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; rationalmode=off!;<br> 
&nbsp;&nbsp;&nbsp;&gt; 19/17 + 3/94;<br> 
&nbsp;&nbsp;&nbsp;1.1495619524405506883604505632040050062578222778473<br> 
&nbsp;&nbsp;&nbsp;&gt; rationalmode=on!;<br> 
&nbsp;&nbsp;&nbsp;&gt; 19/17 + 3/94;<br> 
&nbsp;&nbsp;&nbsp;1837 / 1598<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; rationalmode=off!;<br> 
&nbsp;&nbsp;&nbsp;&gt; exp(19/17 + 3/94);<br> 
&nbsp;&nbsp;&nbsp;3.15680977395514136754709208944824276340328162814418<br> 
&nbsp;&nbsp;&nbsp;&gt; rationalmode=on!;<br> 
&nbsp;&nbsp;&nbsp;&gt; exp(19/17 + 3/94);<br> 
&nbsp;&nbsp;&nbsp;3.15680977395514136754709208944824276340328162814418<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","on","on");?>, <?php linkTo("command","off","off");?>, <?php linkTo("command","numerator","numerator");?>, <?php linkTo("command","denominator","denominator");?>, <?php linkTo("command","simplifysafe","simplifysafe");?>, <?php linkTo("command","rationalapprox","rationalapprox");?>, <?php linkTo("command","autosimplify","autosimplify");?> 
</div> 
