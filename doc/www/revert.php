<a name="revert"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","revert","revert");?> 
<span class="smallDescription">reverts a list. 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library name:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_revert(sollya_obj_t)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","revert","revert");?>(<span class="arg">L</span>) : <span class="type">list</span> -&gt; <span class="type">list</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">L</span> is a list.</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","revert","revert");?>(<span class="arg">L</span>) returns the same list, but with its elements in reverse order. 
</li><li>If <span class="arg">L</span> is an end-elliptic list, <?php linkTo("command","revert","revert");?> will fail with an error. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; revert([| |]);<br> 
&nbsp;&nbsp;&nbsp;[| |]<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; revert([|2,3,5,2,1,4|]);<br> 
&nbsp;&nbsp;&nbsp;[|4, 1, 2, 5, 3, 2|]<br> 
</div> 
</div> 
