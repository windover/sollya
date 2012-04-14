<a name="floating"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","floating","floating");?> 
<span class="smallDescription">indicates that floating-point formats should be used for <?php linkTo("command","fpminimax","fpminimax");?> 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library names:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_floating()</span> 
<span class="commandline type">int sollya_lib_is_floating(sollya_obj_t)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","floating","floating");?> : <span class="type">fixed|floating</span></span> 
 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>The use of <?php linkTo("command","floating","floating");?> in the command <?php linkTo("command","fpminimax","fpminimax");?> indicates that the list of 
formats given as argument is to be considered to be a list of floating-point 
formats. 
See <?php linkTo("command","fpminimax","fpminimax");?> for details. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; fpminimax(cos(x),6,[|D...|],[-1;1],floating);<br> 
&nbsp;&nbsp;&nbsp;0.99999974816012948686250183527590706944465637207031 + x * (5.5210044061222495131782035802443168321913900126185e-14 + x * (-0.4999928698019768802396356477402150630950927734375 + x * (-3.95371609372064761555136192612768146546591008227978e-13 + x * (4.16335155285858099505347240665287245064973831176758e-2 + x * (5.2492670395835122748014980938834327670386437070249e-13 + x * (-1.33822408807599468535953768366653093835338950157166e-3))))))<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","fpminimax","fpminimax");?>, <?php linkTo("command","fixed","fixed");?> 
</div> 
