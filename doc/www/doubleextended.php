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
</li><li><?php linkTo("command","doubleextended","doubleextended");?> now does handle subnormal numbers for a presumed exponent width 
of the double-extended format of 15 bits. This means, with respect to  
rounding, <?php linkTo("command","doubleextended","doubleextended");?> behaves as a IEEE 754-2008 binary79 with a 64 bit  
significand (with a hidden bit normal range), one sign bit and a  
15 bit exponent field would behave. This behavior may be different 
from the one observed on Intel-based IA32/Intel64 processors (or compatible 
versions from other vendors). However it is the one seen on HP/Intel  
Itanium when the precision specifier is double-extended and pseudo-denormals 
are activated. 
</li><li>Since it is a function and not a command, its behavior is a bit different from  
the behavior of <?php linkTo("command","round","round");?>(x,64,RN) even if the result is exactly the same. 
<?php linkTo("command","round","round");?>(x,64,RN) is immediately evaluated whereas <?php linkTo("command","doubleextended","doubleextended");?>(x) can be composed  
with other functions (and thus be plotted and so on). 
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
&nbsp;&nbsp;&nbsp;&gt; DE(2^(-20000));<br> 
&nbsp;&nbsp;&nbsp;0<br> 
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
<span class="category">See also: </span><?php linkTo("command","roundcoefficients","roundcoefficients");?>, <?php linkTo("command","halfprecision","halfprecision");?>, <?php linkTo("command","single","single");?>, <?php linkTo("command","double","double");?>, <?php linkTo("command","doubledouble","doubledouble");?>, <?php linkTo("command","quad","quad");?>, <?php linkTo("command","tripledouble","tripledouble");?>, <?php linkTo("command","round","round");?> 
</div> 
