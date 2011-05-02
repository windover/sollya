<a name="rz"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","rz","RZ");?> 
<span class="smallDescription">constant representing rounding-to-zero mode. 
</span> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","rz","RZ");?> is used in command <?php linkTo("command","round","round");?> to specify that the value must be rounded 
to the closest floating-point number towards zero. It just consists in  
truncating the value to the desired format. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; display=binary!;<br> 
&nbsp;&nbsp;&nbsp;&gt; round(Pi,20,RZ);<br> 
&nbsp;&nbsp;&nbsp;1.1001001000011111101_2 * 2^(1)<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","rd","RD");?>, <?php linkTo("command","ru","RU");?>, <?php linkTo("command","rn","RN");?>, <?php linkTo("command","round","round");?>, <?php linkTo("command","floor","floor");?>, <?php linkTo("command","ceil","ceil");?> 
</div> 
