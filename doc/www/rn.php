<a name="rn"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","rn","RN");?> 
<span class="smallDescription">constant representing rounding-to-nearest mode. 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library names:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_round_to_nearest()</span> 
<span class="commandline type">int sollya_lib_is_round_to_nearest(sollya_obj_t)</span> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","rn","RN");?> is used in command <?php linkTo("command","round","round");?> to specify that the value must be rounded 
to the nearest representable floating-point number. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; display=binary!;<br> 
&nbsp;&nbsp;&nbsp;&gt; round(Pi,20,RN);<br> 
&nbsp;&nbsp;&nbsp;1.100100100001111111_2 * 2^(1)<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","rd","RD");?>, <?php linkTo("command","ru","RU");?>, <?php linkTo("command","rz","RZ");?>, <?php linkTo("command","round","round");?>, <?php linkTo("command","nearestint","nearestint");?> 
</div> 
