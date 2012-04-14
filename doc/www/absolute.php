<a name="absolute"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","absolute","absolute");?> 
<span class="smallDescription">indicates an absolute error for <?php linkTo("command","externalplot","externalplot");?>, <?php linkTo("command","fpminimax","fpminimax");?> or <?php linkTo("command","supnorm","supnorm");?> 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library names:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_absolute()</span> 
<span class="commandline type">int sollya_lib_is_absolute(sollya_obj_t)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","absolute","absolute");?> : <span class="type">absolute|relative</span></span> 
 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>The use of <?php linkTo("command","absolute","absolute");?> in the command <?php linkTo("command","externalplot","externalplot");?> indicates that during 
plotting in <?php linkTo("command","externalplot","externalplot");?> an absolute error is to be considered. 
<br><br> 
See <?php linkTo("command","externalplot","externalplot");?> for details. 
</li><li>Used with <?php linkTo("command","fpminimax","fpminimax");?>, <?php linkTo("command","absolute","absolute");?> indicates that <?php linkTo("command","fpminimax","fpminimax");?> must try to minimize 
the absolute error. 
<br><br> 
See <?php linkTo("command","fpminimax","fpminimax");?> for details. 
</li><li>When given in argument to <?php linkTo("command","supnorm","supnorm");?>, <?php linkTo("command","absolute","absolute");?> indicates that an absolute error 
is to be considered for supremum norm computation. 
<br><br> 
See <?php linkTo("command","supnorm","supnorm");?> for details. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; bashexecute("gcc -fPIC -c externalplotexample.c");<br> 
&nbsp;&nbsp;&nbsp;&gt; bashexecute("gcc -shared -o externalplotexample externalplotexample.o -lgmp -lmpfr");<br> 
&nbsp;&nbsp;&nbsp;&gt; externalplot("./externalplotexample",absolute,exp(x),[-1/2;1/2],12,perturb);<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","externalplot","externalplot");?>, <?php linkTo("command","fpminimax","fpminimax");?>, <?php linkTo("command","relative","relative");?>, <?php linkTo("command","bashexecute","bashexecute");?>, <?php linkTo("command","supnorm","supnorm");?> 
</div> 
