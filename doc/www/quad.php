<a name="quad"></a> 
<div class="divName"> 
<h2 class="name">Names:</h2> <?php linkTo("command","quad","quad");?>, <?php linkTo("command","qd","QD");?> 
<span class="smallDescription">rounding to the nearest IEEE 754 quad (binary128). 
</span> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","quad","quad");?> is both a function and a constant. 
</li><li>As a function, it rounds its argument to the nearest IEEE 754 quad precision (i.e. IEEE754-2008 binary128) number. 
Subnormal numbers are supported as well as standard numbers: it is the real 
rounding described in the standard. 
</li><li>As a constant, it symbolizes the quad precision format. It is used in  
contexts when a precision format is necessary, e.g. in the commands  
<?php linkTo("command","round","round");?> and <?php linkTo("command","roundcoefficients","roundcoefficients");?>. In is not supported for <?php linkTo("command","implementpoly","implementpoly");?>. 
See the corresponding help pages for examples. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; display=binary!;<br> 
&nbsp;&nbsp;&nbsp;&gt; QD(0.1);<br> 
&nbsp;&nbsp;&nbsp;1.100110011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001101_2 * 2^(-4)<br> 
&nbsp;&nbsp;&nbsp;&gt; QD(4.17);<br> 
&nbsp;&nbsp;&nbsp;1.000010101110000101000111101011100001010001111010111000010100011110101110000101000111101011100001010001111010111_2 * 2^(2)<br> 
&nbsp;&nbsp;&nbsp;&gt; QD(1.011_2 * 2^(-16493));<br> 
&nbsp;&nbsp;&nbsp;1.1_2 * 2^(-16493)<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","halfprecision","halfprecision");?>, <?php linkTo("command","single","single");?>, <?php linkTo("command","double","double");?>, <?php linkTo("command","doubleextended","doubleextended");?>, <?php linkTo("command","doubledouble","doubledouble");?>, <?php linkTo("command","tripledouble","tripledouble");?>, <?php linkTo("command","roundcoefficients","roundcoefficients");?>, <?php linkTo("command","implementpoly","implementpoly");?>, <?php linkTo("command","round","round");?>, <?php linkTo("command","printsingle","printsingle");?> 
</div> 
