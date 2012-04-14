<a name="length"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","length","length");?> 
<span class="smallDescription">computes the length of a list or string. 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library name:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_length(sollya_obj_t)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","length","length");?>(<span class="arg">L</span>) : <span class="type">list</span> -&gt; <span class="type">integer</span></span> 
<span class="commandline"><?php linkTo("command","length","length");?>(<span class="arg">s</span>) : <span class="type">string</span> -&gt; <span class="type">integer</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">L</span> is a list.</li> 
<li><span class="arg">s</span> is a string.</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","length","length");?> returns the length of a list or a string, e.g. the number of elements 
or letters. 
</li><li>The empty list or string have length 0. 
If <span class="arg">L</span> is an end-elliptic list, <?php linkTo("command","length","length");?> returns +Inf. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; length("Hello World!");<br> 
&nbsp;&nbsp;&nbsp;12<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; length([|1,...,5|]);<br> 
&nbsp;&nbsp;&nbsp;5<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; length([| |]);<br> 
&nbsp;&nbsp;&nbsp;0<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 4: </h2> 
&nbsp;&nbsp;&nbsp;&gt; length([|1,2...|]);<br> 
&nbsp;&nbsp;&nbsp;@Inf@<br> 
</div> 
</div> 
