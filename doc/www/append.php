<a name="append"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","append",":.");?> 
<span class="smallDescription">add an element at the end of a list. 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library name:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_append(sollya_obj_t, sollya_obj_t)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><span class="arg">L</span><?php linkTo("command","append",":.");?><span class="arg">x</span> : (<span class="type">list</span>, <span class="type">any type</span>) -&gt; <span class="type">list</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">L</span> is a list (possibly empty).</li> 
<li><span class="arg">x</span> is an object of any type.</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","append",":.");?> adds the element <span class="arg">x</span> at the end of the list <span class="arg">L</span>. 
</li><li>Note that since <span class="arg">x</span> may be of any type, it can in particular be a list. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; [|2,3,4|]:.5;<br> 
&nbsp;&nbsp;&nbsp;[|2, 3, 4, 5|]<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; [|1,2,3|]:.[|4,5,6|];<br> 
&nbsp;&nbsp;&nbsp;[|1, 2, 3, [|4, 5, 6|]|]<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; [||]:.1;<br> 
&nbsp;&nbsp;&nbsp;[|1|]<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","prepend",".:");?>, <?php linkTo("command","concat","@");?> 
</div> 
