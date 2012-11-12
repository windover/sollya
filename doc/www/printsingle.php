<a name="printsingle"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","printsingle","printsingle");?> 
<span class="smallDescription">prints a constant value as a hexadecimal single precision number 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library name:</h2> 
<span class="commandline type">void sollya_lib_printsingle(sollya_obj_t)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","printsingle","printsingle");?>(<span class="arg">constant</span>) : <span class="type">constant</span> -&gt; <span class="type">void</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">constant</span> represents a constant</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>Prints a constant value as a hexadecimal number on 8 hexadecimal 
digits. The hexadecimal number represents the integer equivalent to 
the 32 bit memory representation of the constant considered as a 
single precision number. 
<br><br> 
If the constant value does not hold on a single precision number, it 
is first rounded to the nearest single precision number before it is 
displayed. A warning is displayed in this case. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; printsingle(3);<br> 
&nbsp;&nbsp;&nbsp;0x40400000<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; prec=100!;<br> 
&nbsp;&nbsp;&nbsp;&gt; verbosity = 1!;<br> 
&nbsp;&nbsp;&nbsp;&gt; printsingle(exp(5));<br> 
&nbsp;&nbsp;&nbsp;Warning: the given expression is not a constant but an expression to evaluate. A faithful evaluation to 100 bits will be used.<br> 
&nbsp;&nbsp;&nbsp;Warning: rounding down occurred before printing a value as a single.<br> 
&nbsp;&nbsp;&nbsp;0x431469c5<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","printdouble","printdouble");?>, <?php linkTo("command","single","single");?> 
</div> 
