<a name="printdouble"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","printdouble","printdouble");?> 
<span class="smallDescription">prints a constant value as a hexadecimal double precision number 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library name:</h2> 
<span class="commandline type">void sollya_lib_printdouble(sollya_obj_t)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","printdouble","printdouble");?>(<span class="arg">constant</span>) : <span class="type">constant</span> -&gt; <span class="type">void</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">constant</span> represents a constant</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>Prints a constant value as a hexadecimal number on 16 hexadecimal 
digits. The hexadecimal number represents the integer equivalent to 
the 64 bit memory representation of the constant considered as a 
double precision number. 
<br><br> 
If the constant value does not hold on a double precision number, it 
is first rounded to the nearest double precision number before 
displayed. A warning is displayed in this case. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; printdouble(3);<br> 
&nbsp;&nbsp;&nbsp;0x4008000000000000<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; prec=100!;<br> 
&nbsp;&nbsp;&nbsp;&gt; verbosity = 1!;<br> 
&nbsp;&nbsp;&nbsp;&gt; printdouble(exp(5));<br> 
&nbsp;&nbsp;&nbsp;Warning: the given expression is not a constant but an expression to evaluate. A faithful evaluation will be used.<br> 
&nbsp;&nbsp;&nbsp;Warning: rounding down occurred before printing a value as a double.<br> 
&nbsp;&nbsp;&nbsp;0x40628d389970338f<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","printsingle","printsingle");?>, <?php linkTo("command","printexpansion","printexpansion");?>, <?php linkTo("command","double","double");?> 
</div> 
