<a name="round"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","round","round");?> 
<span class="smallDescription">rounds a number to a floating-point format. 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library name:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_round(sollya_obj_t, sollya_obj_t, sollya_obj_t)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","round","round");?>(<span class="arg">x</span>,<span class="arg">n</span>,<span class="arg">mode</span>) : (<span class="type">constant</span>, <span class="type">integer</span>, <span class="type">RN|RZ|RU|RD</span>) -&gt; <span class="type">constant</span></span> 
<span class="commandline"><?php linkTo("command","round","round");?>(<span class="arg">x</span>,<span class="arg">format</span>,<span class="arg">mode</span>) : (<span class="type">constant</span>, <span class="type">HP|halfprecision|SG|single|D|double|DE|doubleextended|DD|doubledouble|QD|quad|TD|tripledouble</span>, <span class="type">RN|RZ|RU|RD</span>) -&gt; <span class="type">constant</span></span> 
 
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
</li><li>Subnormal numbers are handled for the case when <span class="arg">format</span> is one of 
<?php linkTo("command","halfprecision","halfprecision");?>, <?php linkTo("command","single","single");?>, <?php linkTo("command","double","double");?>, <?php linkTo("command","doubleextended","doubleextended");?>, <?php linkTo("command","doubledouble","doubledouble");?>, 
<?php linkTo("command","quad","quad");?> or <?php linkTo("command","tripledouble","tripledouble");?>. Otherwise, when <span class="arg">format</span> is an integer, 
<?php linkTo("command","round","round");?> does not take any exponent range into consideration, 
i.e. typically uses the full exponent range of the underlying MPFR 
library. 
</li><li>It is worth mentionning that the result of <?php linkTo("command","round","round");?> does not depend on 
the current global precision of Sollya, unless a warning is 
displayed. As a matter of fact, <?php linkTo("command","round","round");?> rounds the given constant or 
constant expression <span class="arg">x</span> applying all rules of IEEE 754 correct 
rounding, unless a warning is displayed. The result of <?php linkTo("command","round","round");?> is 
hence the floating-point value of the given precision <span class="arg">n</span> or format 
<span class="arg">format</span> that is nearest (resp. just below or just above, depending on 
<span class="arg">mode</span>), computed as if infinite precision were used for evaluating 
the constant <span class="arg">x</span>, unless a warning is displayed. 
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
