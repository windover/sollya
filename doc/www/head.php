<a name="head"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","head","head");?> 
<span class="smallDescription">gives the first element of a list. 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library name:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_head(sollya_obj_t)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","head","head");?>(<span class="arg">L</span>) : <span class="type">list</span> -&gt; <span class="type">any type</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">L</span> is a list.</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","head","head");?>(<span class="arg">L</span>) returns the first element of the list <span class="arg">L</span>. It is equivalent 
to L[0]. 
</li><li>If <span class="arg">L</span> is empty, the command will fail with an error. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; head([|1,2,3|]);<br> 
&nbsp;&nbsp;&nbsp;1<br> 
&nbsp;&nbsp;&nbsp;&gt; head([|1,2...|]);<br> 
&nbsp;&nbsp;&nbsp;1<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","tail","tail");?> 
</div> 
