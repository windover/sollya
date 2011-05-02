<a name="tripledouble"></a> 
<div class="divName"> 
<h2 class="name">Names:</h2> <?php linkTo("command","tripledouble","tripledouble");?>, <?php linkTo("command","td","TD");?> 
<span class="smallDescription">represents a number as the sum of three IEEE doubles. 
</span> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","tripledouble","tripledouble");?> is both a function and a constant. 
</li><li>As a function, it rounds its argument to the nearest number that can be written 
as the sum of three double precision numbers. 
</li><li>The algorithm used to compute <?php linkTo("command","tripledouble","tripledouble");?>(x) is the following: let xh = <?php linkTo("command","double","double");?>(x), 
let xm = <?php linkTo("command","double","double");?>(x - xh) and let xl = <?php linkTo("command","double","double");?>(x - xh - xm).  
Return the number xh + xm + xl. Note that if the 
current precision is not sufficient to represent exactly xh + xm + xl, a rounding will 
occur and the result of <?php linkTo("command","tripledouble","tripledouble");?>(x) will be useless. 
</li><li>As a constant, it symbolizes the triple-double precision format. It is used in  
contexts when a precision format is necessary, e.g. in the commands  
<?php linkTo("command","roundcoefficients","roundcoefficients");?> and <?php linkTo("command","implementpoly","implementpoly");?>. 
See the corresponding help pages for examples. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; verbosity=1!;<br> 
&nbsp;&nbsp;&nbsp;&gt; a = 1+ 2^(-55)+2^(-115);<br> 
&nbsp;&nbsp;&nbsp;&gt; TD(a);<br> 
&nbsp;&nbsp;&nbsp;1.00000000000000002775557561562891353466491600711096<br> 
&nbsp;&nbsp;&nbsp;&gt; prec=110!;<br> 
&nbsp;&nbsp;&nbsp;&gt; TD(a);<br> 
&nbsp;&nbsp;&nbsp;Warning: double rounding occurred on invoking the triple-double rounding operator.<br> 
&nbsp;&nbsp;&nbsp;Try to increase the working precision.<br> 
&nbsp;&nbsp;&nbsp;1.000000000000000027755575615628913<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","single","single");?>, <?php linkTo("command","double","double");?>, <?php linkTo("command","doubleextended","doubleextended");?>, <?php linkTo("command","doubledouble","doubledouble");?>, <?php linkTo("command","roundcoefficients","roundcoefficients");?>, <?php linkTo("command","implementpoly","implementpoly");?>, <?php linkTo("command","fpminimax","fpminimax");?>, <?php linkTo("command","printexpansion","printexpansion");?> 
</div> 
