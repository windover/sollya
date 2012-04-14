<a name="perturb"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","perturb","perturb");?> 
<span class="smallDescription">indicates random perturbation of sampling points for <?php linkTo("command","externalplot","externalplot");?> 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library names:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_perturb()</span> 
<span class="commandline type">int sollya_lib_is_perturb(sollya_obj_t)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","perturb","perturb");?> : <span class="type">perturb</span></span> 
 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>The use of <?php linkTo("command","perturb","perturb");?> in the command <?php linkTo("command","externalplot","externalplot");?> enables the addition 
of some random noise around each sampling point in <?php linkTo("command","externalplot","externalplot");?>. 
<br><br> 
See <?php linkTo("command","externalplot","externalplot");?> for details. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; bashexecute("gcc -fPIC -c externalplotexample.c");<br> 
&nbsp;&nbsp;&nbsp;&gt; bashexecute("gcc -shared -o externalplotexample externalplotexample.o -lgmp -lmpfr");<br> 
&nbsp;&nbsp;&nbsp;&gt; externalplot("./externalplotexample",relative,exp(x),[-1/2;1/2],12,perturb);<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","externalplot","externalplot");?>, <?php linkTo("command","absolute","absolute");?>, <?php linkTo("command","relative","relative");?>, <?php linkTo("command","bashexecute","bashexecute");?> 
</div> 
