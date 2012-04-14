<a name="fixed"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","fixed","fixed");?> 
<span class="smallDescription">indicates that fixed-point formats should be used for <?php linkTo("command","fpminimax","fpminimax");?> 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library names:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_fixed()</span> 
<span class="commandline type">int sollya_lib_is_fixed(sollya_obj_t)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","fixed","fixed");?> : <span class="type">fixed|floating</span></span> 
 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>The use of <?php linkTo("command","fixed","fixed");?> in the command <?php linkTo("command","fpminimax","fpminimax");?> indicates that the list of 
formats given as argument is to be considered to be a list of fixed-point 
formats. 
See <?php linkTo("command","fpminimax","fpminimax");?> for details. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; fpminimax(cos(x),6,[|32,32,32,32,32,32,32|],[-1;1],fixed);<br> 
&nbsp;&nbsp;&nbsp;0.9999997480772435665130615234375 + x^2 * (-0.4999928693287074565887451171875 + x^2 * (4.163351492024958133697509765625e-2 + x^2 * (-1.338223926723003387451171875e-3)))<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","fpminimax","fpminimax");?>, <?php linkTo("command","floating","floating");?> 
</div> 
