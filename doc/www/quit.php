<a name="quit"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","quit","quit");?> 
<span class="smallDescription">quits Sollya 
</span> 
</div> 
<div class="divLibraryName"> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","quit","quit");?> : <span class="type">void</span> -&gt; <span class="type">void</span></span> 
 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>The command <?php linkTo("command","quit","quit");?>, when executed, stops the execution of a Sollya 
script and leaves the Sollya interpreter unless the <?php linkTo("command","quit","quit");?> command  
is executed in a Sollya script read into a main Sollya script by 
<?php linkTo("command","execute","execute");?> or #include. 
<br><br> 
Upon exiting the Sollya interpreter, all state is thrown away, all 
memory is deallocated, all bound libraries are unbound and the 
temporary files produced by <?php linkTo("command","plot","plot");?> and <?php linkTo("command","externalplot","externalplot");?> are deleted. 
<br><br> 
If the <?php linkTo("command","quit","quit");?> command does not lead to a halt of the Sollya 
interpreter, a warning is displayed. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; quit;<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","restart","restart");?>, <?php linkTo("command","execute","execute");?>, <?php linkTo("command","plot","plot");?>, <?php linkTo("command","externalplot","externalplot");?>, <?php linkTo("command","return","return");?> 
</div> 
