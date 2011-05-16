<a name="round"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","round","round");?> 
<span class="smallDescription">rounds a number to a floating-point format. 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","round","round");?>(<span class="arg">x</span>,<span class="arg">n</span>,<span class="arg">mode</span>) : (<span class="type">constant</span>, <span class="type">integer</span>, <span class="type">RN|RZ|RU|RD</span>) -&gt; <span class="type">constant</span></span> 
<span class="commandline"><?php linkTo("command","round","round");?>(<span class="arg">x</span>,<span class="arg">format</span>,<span class="arg">mode</span>) : (<span class="type">constant</span>, <span class="type">D|double|DD|doubledouble|DE|doubleextended|TD|tripledouble</span>, <span class="type">RN|RZ|RU|RD</span>) -&gt; <span class="type">constant</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">x</span> is a constant to be rounded.</li> 
<li><span class="arg">n</span> is the precision of the target format.</li> 
<li><span class="arg">format</span> is the name of a supported floating-point format.</li> 
<li><span class="arg">mode</span> is the desired rounding mode.</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>If used with an integer parameter <span class="arg">n</span>, <?php linkTo("command","round","round");?>(<span class="arg">x</span>,<span class="arg">n</span>,<span class="arg">mode</span>) rounds <span class="arg">x</span> to a floating-point number with  
precision <span class="arg">n</span>, according to rounding-mode <span class="arg">mode</span>.  
</li><li>If used with a format parameter <span class="arg">format</span>, <?php linkTo("command","round","round");?>(<span class="arg">x</span>,<span class="arg">format</span>,<span class="arg">mode</span>) rounds <span class="arg">x</span> to a floating-point number in the  
floating-point format <span class="arg">format</span>, according to rounding-mode <span class="arg">mode</span>.  
</li><li>Subnormal numbers are not handled are handled only if a <span class="arg">format</span> parameter is given 
that is different from <?php linkTo("command","doubleextended","doubleextended");?>. The range of possible exponents is the  
range used for all numbers represented in Sollya (e.g. basically the range  
used in the library MPFR).  
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; display=binary!;<br> 
&nbsp;&nbsp;&nbsp;&gt; round(Pi,20,RN);<br> 
&nbsp;&nbsp;&nbsp;1.100100100001111111_2 * 2^(1)<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; printdouble(round(exp(17),53,RU));<br> 
&nbsp;&nbsp;&nbsp;0x417709348c0ea4f9<br> 
&nbsp;&nbsp;&nbsp;&gt; printdouble(D(exp(17)));<br> 
&nbsp;&nbsp;&nbsp;0x417709348c0ea4f9<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; display=binary!;<br> 
&nbsp;&nbsp;&nbsp;&gt; a=2^(-1100);<br> 
&nbsp;&nbsp;&nbsp;&gt; round(a,53,RN);<br> 
&nbsp;&nbsp;&nbsp;1_2 * 2^(-1100)<br> 
&nbsp;&nbsp;&nbsp;&gt; round(a,D,RN);<br> 
&nbsp;&nbsp;&nbsp;0<br> 
&nbsp;&nbsp;&nbsp;&gt; double(a);<br> 
&nbsp;&nbsp;&nbsp;0<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","rn","RN");?>, <?php linkTo("command","rd","RD");?>, <?php linkTo("command","ru","RU");?>, <?php linkTo("command","rz","RZ");?>, <?php linkTo("command","halfprecision","halfprecision");?>, <?php linkTo("command","single","single");?>, <?php linkTo("command","double","double");?>, <?php linkTo("command","doubleextended","doubleextended");?>, <?php linkTo("command","doubledouble","doubledouble");?>, <?php linkTo("command","quad","quad");?>, <?php linkTo("command","tripledouble","tripledouble");?>, <?php linkTo("command","roundcoefficients","roundcoefficients");?>, <?php linkTo("command","roundcorrectly","roundcorrectly");?>, <?php linkTo("command","printdouble","printdouble");?>, <?php linkTo("command","printsingle","printsingle");?>, <?php linkTo("command","ceil","ceil");?>, <?php linkTo("command","floor","floor");?>, <?php linkTo("command","nearestint","nearestint");?> 
</div> 
