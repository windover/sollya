<a name="log"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","log","log");?> 
<span class="smallDescription">natural logarithm. 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library names:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_log(sollya_obj_t)</span> 
<span class="commandline type">sollya_obj_t sollya_lib_build_function_log(sollya_obj_t)</span> 
<span class="commandline type">#define SOLLYA_LOG(x) sollya_lib_build_function_log(x)</span> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","log","log");?> is the natural logarithm defined as the inverse of the exponential 
function: log(y) is the unique real number x such that exp(x)=y. 
</li><li>It is defined only for y in [0; +Inf]. 
</ul> 
</div> 
<div class="divExamples"> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","exp","exp");?>, <?php linkTo("command","log2","log2");?>, <?php linkTo("command","log10","log10");?> 
</div> 
