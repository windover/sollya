<a name="equal"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","equal","==");?> 
<span class="smallDescription">equality test operator 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library name:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_cmp_equal(sollya_obj_t, sollya_obj_t)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><span class="arg">expr1</span> <?php linkTo("command","equal","==");?> <span class="arg">expr2</span> : (<span class="type">any type</span>, <span class="type">any type</span>) -&gt; <span class="type">boolean</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">expr1</span> and <span class="arg">expr2</span> represent expressions</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>The operator <?php linkTo("command","equal","==");?> evaluates to true iff its operands <span class="arg">expr1</span> and 
<span class="arg">expr2</span> are syntactically equal and different from <?php linkTo("command","error","error");?> or constant 
expressions that are not constants and that evaluate to the same 
floating-point number with the global precision <?php linkTo("command","prec","prec");?>. The user should 
be aware of the fact that because of floating-point evaluation, the 
operator <?php linkTo("command","equal","==");?> is not exactly the same as the mathematical 
equality. Further remark that according to IEEE 754-2008 floating-point 
rules, which Sollya emulates, floating-point data which are NaN do not 
compare equal to any other floating-point datum, including NaN.  
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; "Hello" == "Hello";<br> 
&nbsp;&nbsp;&nbsp;true<br> 
&nbsp;&nbsp;&nbsp;&gt; "Hello" == "Salut";<br> 
&nbsp;&nbsp;&nbsp;false<br> 
&nbsp;&nbsp;&nbsp;&gt; "Hello" == 5;<br> 
&nbsp;&nbsp;&nbsp;false<br> 
&nbsp;&nbsp;&nbsp;&gt; 5 + x == 5 + x;<br> 
&nbsp;&nbsp;&nbsp;true<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; 1 == exp(0);<br> 
&nbsp;&nbsp;&nbsp;true<br> 
&nbsp;&nbsp;&nbsp;&gt; asin(1) * 2 == pi;<br> 
&nbsp;&nbsp;&nbsp;true<br> 
&nbsp;&nbsp;&nbsp;&gt; exp(5) == log(4);<br> 
&nbsp;&nbsp;&nbsp;false<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; sin(pi/6) == 1/4;<br> 
&nbsp;&nbsp;&nbsp;false<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 4: </h2> 
&nbsp;&nbsp;&nbsp;&gt; prec = 12;<br> 
&nbsp;&nbsp;&nbsp;The precision has been set to 12 bits.<br> 
&nbsp;&nbsp;&nbsp;&gt; verbosity = 1!;<br> 
&nbsp;&nbsp;&nbsp;&gt; 16384.1 == 16385.1;<br> 
&nbsp;&nbsp;&nbsp;Warning: Rounding occurred when converting the constant "16384.1" to floating-point with 12 bits.<br> 
&nbsp;&nbsp;&nbsp;If safe computation is needed, try to increase the precision.<br> 
&nbsp;&nbsp;&nbsp;Warning: Rounding occurred when converting the constant "16385.1" to floating-point with 12 bits.<br> 
&nbsp;&nbsp;&nbsp;If safe computation is needed, try to increase the precision.<br> 
&nbsp;&nbsp;&nbsp;true<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 5: </h2> 
&nbsp;&nbsp;&nbsp;&gt; error == error;<br> 
&nbsp;&nbsp;&nbsp;false<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 6: </h2> 
&nbsp;&nbsp;&nbsp;&gt; a = "Biba";<br> 
&nbsp;&nbsp;&nbsp;&gt; b = NaN;<br> 
&nbsp;&nbsp;&nbsp;&gt; a == a;<br> 
&nbsp;&nbsp;&nbsp;true<br> 
&nbsp;&nbsp;&nbsp;&gt; b == b;<br> 
&nbsp;&nbsp;&nbsp;false<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","neq","!=");?>, <?php linkTo("command","gt","&gt;");?>, <?php linkTo("command","ge","&gt;=");?>, <?php linkTo("command","le","&lt;=");?>, <?php linkTo("command","lt","&lt;");?>, <?php linkTo("command","in","in");?>, <?php linkTo("command","not","!");?>, <?php linkTo("command","and","&&");?>, <?php linkTo("command","or","||");?>, <?php linkTo("command","error","error");?>, <?php linkTo("command","prec","prec");?> 
</div> 
