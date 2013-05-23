<a name="bashexecute"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","bashexecute","bashexecute");?> 
<span class="smallDescription">executes a shell command. 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library name:</h2> 
<span class="commandline type">void sollya_lib_bashexecute(sollya_obj_t)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","bashexecute","bashexecute");?>(<span class="arg">command</span>) : <span class="type">string</span> -&gt; <span class="type">void</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">command</span> is a command to be interpreted by the shell.</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","bashexecute","bashexecute");?>(<span class="arg">command</span>) lets the shell interpret <span class="arg">command</span>. It is useful to execute 
some external code within Sollya. 
</li><li><?php linkTo("command","bashexecute","bashexecute");?> does not return anything. It just executes its argument. However, if 
<span class="arg">command</span> produces an output in a file, this result can be imported in Sollya 
with help of commands like <?php linkTo("command","execute","execute");?>, <?php linkTo("command","readfile","readfile");?> and <?php linkTo("command","parse","parse");?>. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; bashexecute("LANG=C date");<br> 
&nbsp;&nbsp;&nbsp;Thu May 23 16:23:35 CEST 2013<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","execute","execute");?>, <?php linkTo("command","readfile","readfile");?>, <?php linkTo("command","parse","parse");?>, <?php linkTo("command","bashevaluate","bashevaluate");?> 
</div> 
