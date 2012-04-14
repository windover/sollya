<a name="erf"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","erf","erf");?> 
<span class="smallDescription">the error function. 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library names:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_erf(sollya_obj_t)</span> 
<span class="commandline type">sollya_obj_t sollya_lib_build_function_erf(sollya_obj_t)</span> 
<span class="commandline type">#define SOLLYA_ERF(x) sollya_lib_build_function_erf(x)</span> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","erf","erf");?> is the error function defined by: 
erf(x) = (2/sqrt(Pi)) * integral(exp(-t^2), [0;x]) 
</li><li>It is defined for every real number x. 
</ul> 
</div> 
<div class="divExamples"> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","erfc","erfc");?>, <?php linkTo("command","exp","exp");?> 
</div> 
