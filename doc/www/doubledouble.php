<a name="doubledouble"></a> 
<div class="divName"> 
<h2 class="name">Names:</h2> <?php linkTo("command","doubledouble","doubledouble");?>, <?php linkTo("command","dd","DD");?> 
<span class="smallDescription">represents a number as the sum of two IEEE doubles. 
</span> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","doubledouble","doubledouble");?> is both a function and a constant. 
</li><li>As a function, it rounds its argument to the nearest number that can be written 
as the sum of two double precision numbers. 
</li><li>The algorithm used to compute <?php linkTo("command","doubledouble","doubledouble");?>(x) is the following: let xh = <?php linkTo("command","double","double");?>(x) 
and let xl = <?php linkTo("command","double","double");?>(x - xh). Return the number xh + xl. Note that if the current  
precision is not sufficient to exactly represent xh + xl, a rounding will occur 
and the result of <?php linkTo("command","doubledouble","doubledouble");?>(x) will be useless. 
</li><li>As a constant, it symbolizes the double-double precision format. It is used in  
contexts when a precision format is necessary, e.g. in the commands  
<?php linkTo("command","round","round");?>, <?php linkTo("command","roundcoefficients","roundcoefficients");?> and <?php linkTo("command","implementpoly","implementpoly");?>. 
See the corresponding help pages for examples. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; verbosity=1!;<br> 
&nbsp;&nbsp;&nbsp;&gt; a = 1+ 2^(-100);<br> 
&nbsp;&nbsp;&nbsp;&gt; DD(a);<br> 
&nbsp;&nbsp;&nbsp;1.0000000000000000000000000000007888609052210118054<br> 
&nbsp;&nbsp;&nbsp;&gt; prec=50!;<br> 
&nbsp;&nbsp;&nbsp;&gt; DD(a);<br> 
&nbsp;&nbsp;&nbsp;Warning: double rounding occurred on invoking the double-double rounding operator.<br> 
&nbsp;&nbsp;&nbsp;Try to increase the working precision.<br> 
&nbsp;&nbsp;&nbsp;1<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","halfprecision","halfprecision");?>, <?php linkTo("command","single","single");?>, <?php linkTo("command","double","double");?>, <?php linkTo("command","doubleextended","doubleextended");?>, <?php linkTo("command","quad","quad");?>, <?php linkTo("command","tripledouble","tripledouble");?>, <?php linkTo("command","roundcoefficients","roundcoefficients");?>, <?php linkTo("command","implementpoly","implementpoly");?>, <?php linkTo("command","round","round");?> 
</div> 
