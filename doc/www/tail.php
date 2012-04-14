<a name="tail"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","tail","tail");?> 
<span class="smallDescription">gives the tail of a list. 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library name:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_tail(sollya_obj_t)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","tail","tail");?>(<span class="arg">L</span>) : <span class="type">list</span> -&gt; <span class="type">list</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">L</span> is a list.</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","tail","tail");?>(<span class="arg">L</span>) returns the list <span class="arg">L</span> without its first element. 
</li><li>If <span class="arg">L</span> is empty, the command will fail with an error. 
</li><li><?php linkTo("command","tail","tail");?> can also be used with end-elliptic lists. In this case, the result of 
<?php linkTo("command","tail","tail");?> is also an end-elliptic list. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; tail([|1,2,3|]);<br> 
&nbsp;&nbsp;&nbsp;[|2, 3|]<br> 
&nbsp;&nbsp;&nbsp;&gt; tail([|1,2...|]);<br> 
&nbsp;&nbsp;&nbsp;[|2...|]<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","head","head");?> 
</div> 
