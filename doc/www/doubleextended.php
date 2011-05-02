<a name="doubleextended"></a> 
<div class="divName"> 
<h2 class="name">Names:</h2> <?php linkTo("command","doubleextended","doubleextended");?>, <?php linkTo("command","de","DE");?> 
<span class="smallDescription">computes the nearest number with 64 bits of mantissa. 
</span> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","doubleextended","doubleextended");?> is a function that computes the nearest floating-point number with 
64 bits of mantissa to a given number. Since it is a function, it can be 
composed with other Sollya functions such as <?php linkTo("command","exp","exp");?>, <?php linkTo("command","sin","sin");?>, etc. 
</li><li>It does not handle subnormal numbers. The range of possible exponents is the  
range used for all numbers represented in Sollya (e.g. basically the range  
used in the library MPFR). 
</li><li>Since it is a function and not a command, its behavior is a bit different from  
the behavior of <?php linkTo("command","round","round");?>(x,64,RN) even if the result is exactly the same. 
<?php linkTo("command","round","round");?>(x,64,RN) is immediately evaluated whereas <?php linkTo("command","doubleextended","doubleextended");?>(x) can be composed  
with other functions (and thus be plotted and so on). 
</li><li>Be aware that <?php linkTo("command","doubleextended","doubleextended");?> cannot be used as a constant to represent a format in the 
commands <?php linkTo("command","roundcoefficients","roundcoefficients");?> and <?php linkTo("command","implementpoly","implementpoly");?> (contrary to <?php linkTo("command","d","D");?>, <?php linkTo("command","dd","DD");?>,and <?php linkTo("command","td","TD");?>). However, it 
can be used in <?php linkTo("command","round","round");?>. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; display=binary!;<br> 
&nbsp;&nbsp;&nbsp;&gt; DE(0.1);<br> 
&nbsp;&nbsp;&nbsp;1.100110011001100110011001100110011001100110011001100110011001101_2 * 2^(-4)<br> 
&nbsp;&nbsp;&nbsp;&gt; round(0.1,64,RN);<br> 
&nbsp;&nbsp;&nbsp;1.100110011001100110011001100110011001100110011001100110011001101_2 * 2^(-4)<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; D(2^(-2000));<br> 
&nbsp;&nbsp;&nbsp;0<br> 
&nbsp;&nbsp;&nbsp;&gt; DE(2^(-2000));<br> 
&nbsp;&nbsp;&nbsp;8.7098098162172166755761954947788722958591037427053e-603<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; verbosity=1!;<br> 
&nbsp;&nbsp;&nbsp;&gt; f = sin(DE(x));<br> 
&nbsp;&nbsp;&nbsp;&gt; f(pi);<br> 
&nbsp;&nbsp;&nbsp;Warning: rounding has happened. The value displayed is a faithful rounding of the true result.<br> 
&nbsp;&nbsp;&nbsp;-5.0165576126683320235573270803307570138315616702549e-20<br> 
&nbsp;&nbsp;&nbsp;&gt; g = sin(round(x,64,RN));<br> 
&nbsp;&nbsp;&nbsp;Warning: at least one of the given expressions or a subexpression is not correctly typed<br> 
&nbsp;&nbsp;&nbsp;or its evaluation has failed because of some error on a side-effect.<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","roundcoefficients","roundcoefficients");?>, <?php linkTo("command","single","single");?>, <?php linkTo("command","double","double");?>, <?php linkTo("command","doubledouble","doubledouble");?>, <?php linkTo("command","tripledouble","tripledouble");?>, <?php linkTo("command","round","round");?> 
</div> 
