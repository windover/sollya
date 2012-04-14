<a name="prec"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","prec","prec");?> 
<span class="smallDescription">controls the precision used in numerical computations. 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library names:</h2> 
<span class="commandline type">void sollya_lib_set_prec_and_print(sollya_obj_t)</span> 
<span class="commandline type">void sollya_lib_set_prec(sollya_obj_t)</span> 
<span class="commandline type">sollya_obj_t sollya_lib_get_prec()</span> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","prec","prec");?> is a global variable. Its value represents the precision of the  
floating-point format used in numerical computations. 
</li><li>Many commands try to adapt their working precision in order to have  
approximately n correct bits in output, where n is the value of <?php linkTo("command","prec","prec");?>. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; display=binary!;<br> 
&nbsp;&nbsp;&nbsp;&gt; prec=50;<br> 
&nbsp;&nbsp;&nbsp;The precision has been set to 50 bits.<br> 
&nbsp;&nbsp;&nbsp;&gt; dirtyinfnorm(exp(x),[1;2]);<br> 
&nbsp;&nbsp;&nbsp;1.110110001110011001001011100011010100110111011011_2 * 2^(2)<br> 
&nbsp;&nbsp;&nbsp;&gt; prec=100;<br> 
&nbsp;&nbsp;&nbsp;The precision has been set to 100 bits.<br> 
&nbsp;&nbsp;&nbsp;&gt; dirtyinfnorm(exp(x),[1;2]);<br> 
&nbsp;&nbsp;&nbsp;1.11011000111001100100101110001101010011011101101011011100110000110011101000111011101000100000011011_2 * 2^(2)<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","evaluate","evaluate");?>, <?php linkTo("command","diam","diam");?> 
</div> 
