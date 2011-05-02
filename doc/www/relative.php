<a name="relative"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","relative","relative");?> 
<span class="smallDescription">indicates a relative error for <?php linkTo("command","externalplot","externalplot");?>, <?php linkTo("command","fpminimax","fpminimax");?> or <?php linkTo("command","supnorm","supnorm");?> 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","relative","relative");?> : <span class="type">absolute|relative</span></span> 
 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>The use of <?php linkTo("command","relative","relative");?> in the command <?php linkTo("command","externalplot","externalplot");?> indicates that during 
plotting in <?php linkTo("command","externalplot","externalplot");?> a relative error is to be considered. 
<br><br> 
See <?php linkTo("command","externalplot","externalplot");?> for details. 
</li><li>Used with <?php linkTo("command","fpminimax","fpminimax");?>, <?php linkTo("command","relative","relative");?> indicates that <?php linkTo("command","fpminimax","fpminimax");?> must try to minimize 
the relative error. 
<br><br> 
See <?php linkTo("command","fpminimax","fpminimax");?> for details. 
</li><li>When given in argument to <?php linkTo("command","supnorm","supnorm");?>, <?php linkTo("command","relative","relative");?> indicates that a relative error 
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
<span class="category">See also: </span><?php linkTo("command","externalplot","externalplot");?>, <?php linkTo("command","fpminimax","fpminimax");?>, <?php linkTo("command","absolute","absolute");?>, <?php linkTo("command","bashexecute","bashexecute");?>, <?php linkTo("command","supnorm","supnorm");?> 
</div> 
