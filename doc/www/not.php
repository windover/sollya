<a name="not"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","not","!");?> 
<span class="smallDescription">boolean NOT operator 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library name:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_negate(sollya_obj_t)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","not","!");?> <span class="arg">expr</span> : <span class="type">boolean</span> -&gt; <span class="type">boolean</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">expr</span> represents a boolean expression</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","not","!");?> evaluates to the boolean NOT of the boolean expression 
<span class="arg">expr</span>. <?php linkTo("command","not","!");?> <span class="arg">expr</span> evaluates to true iff <span class="arg">expr</span> does not evaluate 
to true. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; ! false;<br> 
&nbsp;&nbsp;&nbsp;true<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; ! (1 == exp(0));<br> 
&nbsp;&nbsp;&nbsp;false<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","and","&&");?>, <?php linkTo("command","or","||");?> 
</div> 
