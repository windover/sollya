<a name="display"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","display","display");?> 
<span class="smallDescription">sets or inspects the global variable specifying number notation 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library names:</h2> 
<span class="commandline type">void sollya_lib_set_display_and_print(sollya_obj_t)</span> 
<span class="commandline type">void sollya_lib_set_display(sollya_obj_t)</span> 
<span class="commandline type">sollya_obj_t sollya_lib_get_display()</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","display","display");?> = <span class="arg">notation value</span> : <span class="type">decimal|binary|dyadic|powers|hexadecimal</span> -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","display","display");?> = <span class="arg">notation value</span> ! : <span class="type">decimal|binary|dyadic|powers|hexadecimal</span> -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","display","display");?> : <span class="type">decimal|binary|dyadic|powers|hexadecimal</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">notation value</span> represents a variable of type <span class="type">decimal|binary|dyadic|powers|hexadecimal</span></li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>An assignment <?php linkTo("command","display","display");?> = <span class="arg">notation value</span>, where <span class="arg">notation value</span> is 
one of <?php linkTo("command","decimal","decimal");?>, <?php linkTo("command","dyadic","dyadic");?>, <?php linkTo("command","powers","powers");?>, <?php linkTo("command","binary","binary");?> or <?php linkTo("command","hexadecimal","hexadecimal");?>, activates 
the corresponding notation for output of values in <?php linkTo("command","print","print");?>, <?php linkTo("command","write","write");?> or 
at the Sollya prompt. 
<br><br> 
If the global notation variable <?php linkTo("command","display","display");?> is <?php linkTo("command","decimal","decimal");?>, all numbers will 
be output in scientific decimal notation.  If the global notation 
variable <?php linkTo("command","display","display");?> is <?php linkTo("command","dyadic","dyadic");?>, all numbers will be output as dyadic 
numbers with Gappa notation.  If the global notation variable <?php linkTo("command","display","display");?> 
is <?php linkTo("command","powers","powers");?>, all numbers will be output as dyadic numbers with a 
notation compatible with Maple and PARI/GP.  If the global notation 
variable <?php linkTo("command","display","display");?> is <?php linkTo("command","binary","binary");?>, all numbers will be output in binary 
notation.  If the global notation variable <?php linkTo("command","display","display");?> is <?php linkTo("command","hexadecimal","hexadecimal");?>, 
all numbers will be output in C99/ IEEE754-2008 notation.  All output 
notations can be parsed back by Sollya, inducing no error if the input 
and output precisions are the same (see <?php linkTo("command","prec","prec");?>). 
<br><br> 
If the assignment <?php linkTo("command","display","display");?> = <span class="arg">notation value</span> is followed by an 
exclamation mark, no message indicating the new state is 
displayed. Otherwise the user is informed of the new state of the 
global mode by an indication. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; display = decimal;<br> 
&nbsp;&nbsp;&nbsp;Display mode is decimal numbers.<br> 
&nbsp;&nbsp;&nbsp;&gt; a = evaluate(sin(pi * x), 0.25);<br> 
&nbsp;&nbsp;&nbsp;&gt; a;<br> 
&nbsp;&nbsp;&nbsp;0.70710678118654752440084436210484903928483593768847<br> 
&nbsp;&nbsp;&nbsp;&gt; display = binary;<br> 
&nbsp;&nbsp;&nbsp;Display mode is binary numbers.<br> 
&nbsp;&nbsp;&nbsp;&gt; a;<br> 
&nbsp;&nbsp;&nbsp;1.01101010000010011110011001100111111100111011110011001001000010001011001011111011000100110110011011101010100101010111110100111110001110101101111011000001011101010001_2 * 2^(-1)<br> 
&nbsp;&nbsp;&nbsp;&gt; display = hexadecimal;<br> 
&nbsp;&nbsp;&nbsp;Display mode is hexadecimal numbers.<br> 
&nbsp;&nbsp;&nbsp;&gt; a;<br> 
&nbsp;&nbsp;&nbsp;0xb.504f333f9de6484597d89b3754abe9f1d6f60ba88p-4<br> 
&nbsp;&nbsp;&nbsp;&gt; display = dyadic;<br> 
&nbsp;&nbsp;&nbsp;Display mode is dyadic numbers.<br> 
&nbsp;&nbsp;&nbsp;&gt; a;<br> 
&nbsp;&nbsp;&nbsp;33070006991101558613323983488220944360067107133265b-165<br> 
&nbsp;&nbsp;&nbsp;&gt; display = powers;<br> 
&nbsp;&nbsp;&nbsp;Display mode is dyadic numbers in integer-power-of-2 notation.<br> 
&nbsp;&nbsp;&nbsp;&gt; a;<br> 
&nbsp;&nbsp;&nbsp;33070006991101558613323983488220944360067107133265 * 2^(-165)<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","print","print");?>, <?php linkTo("command","write","write");?>, <?php linkTo("command","decimal","decimal");?>, <?php linkTo("command","dyadic","dyadic");?>, <?php linkTo("command","powers","powers");?>, <?php linkTo("command","binary","binary");?>, <?php linkTo("command","hexadecimal","hexadecimal");?>, <?php linkTo("command","prec","prec");?> 
</div> 
