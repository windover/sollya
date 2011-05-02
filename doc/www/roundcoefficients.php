<a name="roundcoefficients"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","roundcoefficients","roundcoefficients");?> 
<span class="smallDescription">rounds the coefficients of a polynomial to classical formats. 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","roundcoefficients","roundcoefficients");?>(<span class="arg">p</span>,<span class="arg">L</span>) : (<span class="type">function</span>, <span class="type">list</span>) -&gt; <span class="type">function</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">p</span> is a function. Usually a polynomial.</li> 
<li><span class="arg">L</span> is a list of formats.</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>If <span class="arg">p</span> is a polynomial and <span class="arg">L</span> a list of floating-point formats,  
<?php linkTo("command","roundcoefficients","roundcoefficients");?>(<span class="arg">p</span>,<span class="arg">L</span>) rounds each coefficient of <span class="arg">p</span> to the corresponding format 
in <span class="arg">L</span>. 
</li><li>If <span class="arg">p</span> is not a polynomial, <?php linkTo("command","roundcoefficients","roundcoefficients");?> does not do anything. 
</li><li>If <span class="arg">L</span> contains other elements than <?php linkTo("command","d","D");?>, <?php linkTo("command","double","double");?>, <?php linkTo("command","dd","DD");?>, <?php linkTo("command","doubledouble","doubledouble");?>, <?php linkTo("command","td","TD");?> and 
<?php linkTo("command","tripledouble","tripledouble");?>, an error occurs. 
</li><li>The coefficients in <span class="arg">p</span> corresponding to X^i is rounded to the  
format L[i]. If <span class="arg">L</span> does not contain enough elements 
(e.g. if <?php linkTo("command","length","length");?>(L) &lt; <?php linkTo("command","degree","degree");?>(p)+1), a warning is displayed. However, the 
coefficients corresponding to an element of <span class="arg">L</span> are rounded. The trailing  
coefficients (that do not have a corresponding element in <span class="arg">L</span>) are kept with 
their own precision. 
If <span class="arg">L</span> contains too much elements, the trailing useless elements are ignored. 
In particular <span class="arg">L</span> may be end-elliptic in which case <?php linkTo("command","roundcoefficients","roundcoefficients");?> has the  
natural behavior. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; p=exp(1) + x*(exp(2) + x*exp(3));<br> 
&nbsp;&nbsp;&nbsp;&gt; display=binary!;<br> 
&nbsp;&nbsp;&nbsp;&gt; roundcoefficients(p,[|DD,D,D|]);<br> 
&nbsp;&nbsp;&nbsp;1.010110111111000010101000101100010100010101110110100101010011010101011111101110001010110001000000010011101_2 * 2^(1) + x * (1.110110001110011001001011100011010100110111011010111_2 * 2^(2) + x * (1.010000010101111001011011111101101111101100010000011_2 * 2^(4)))<br> 
&nbsp;&nbsp;&nbsp;&gt; roundcoefficients(p,[|DD,D...|]);<br> 
&nbsp;&nbsp;&nbsp;1.010110111111000010101000101100010100010101110110100101010011010101011111101110001010110001000000010011101_2 * 2^(1) + x * (1.110110001110011001001011100011010100110111011010111_2 * 2^(2) + x * (1.010000010101111001011011111101101111101100010000011_2 * 2^(4)))<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; f=sin(exp(1)*x);<br> 
&nbsp;&nbsp;&nbsp;&gt; display=binary!;<br> 
&nbsp;&nbsp;&nbsp;&gt; f;<br> 
&nbsp;&nbsp;&nbsp;sin(x * (1.0101101111110000101010001011000101000101011101101001010100110101010111111011100010101100010000000100111001111010011110011110001110110001011100111000101100000111101_2 * 2^(1)))<br> 
&nbsp;&nbsp;&nbsp;&gt; roundcoefficients(f,[|D...|]);<br> 
&nbsp;&nbsp;&nbsp;sin(x * (1.0101101111110000101010001011000101000101011101101001010100110101010111111011100010101100010000000100111001111010011110011110001110110001011100111000101100000111101_2 * 2^(1)))<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; p=exp(1) + x*(exp(2) + x*exp(3));<br> 
&nbsp;&nbsp;&nbsp;&gt; verbosity=1!;<br> 
&nbsp;&nbsp;&nbsp;&gt; display=binary!;<br> 
&nbsp;&nbsp;&nbsp;&gt; roundcoefficients(p,[|DD,D|]);<br> 
&nbsp;&nbsp;&nbsp;Warning: the number of the given formats does not correspond to the degree of the given polynomial.<br> 
&nbsp;&nbsp;&nbsp;Warning: the 0th coefficient of the given polynomial does not evaluate to a floating-point constant without any rounding.<br> 
&nbsp;&nbsp;&nbsp;Will evaluate the coefficient in the current precision in floating-point before rounding to the target format.<br> 
&nbsp;&nbsp;&nbsp;Warning: the 1th coefficient of the given polynomial does not evaluate to a floating-point constant without any rounding.<br> 
&nbsp;&nbsp;&nbsp;Will evaluate the coefficient in the current precision in floating-point before rounding to the target format.<br> 
&nbsp;&nbsp;&nbsp;Warning: rounding may have happened.<br> 
&nbsp;&nbsp;&nbsp;1.010110111111000010101000101100010100010101110110100101010011010101011111101110001010110001000000010011101_2 * 2^(1) + x * (1.110110001110011001001011100011010100110111011010111_2 * 2^(2) + x * (1.01000001010111100101101111110110111110110001000001011111001011010100101111011111110001010011011101000100110000111010001110010000010110000101100000111001011100101001_2 * 2^(4)))<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","single","single");?>, <?php linkTo("command","double","double");?>, <?php linkTo("command","doubledouble","doubledouble");?>, <?php linkTo("command","tripledouble","tripledouble");?>, <?php linkTo("command","fpminimax","fpminimax");?>, <?php linkTo("command","remez","remez");?>, <?php linkTo("command","implementpoly","implementpoly");?>, <?php linkTo("command","subpoly","subpoly");?> 
</div> 
