<a name="or"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","or","||");?> 
<span class="smallDescription">boolean OR operator 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library name:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_or(sollya_obj_t, sollya_obj_t)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><span class="arg">expr1</span> <?php linkTo("command","or","||");?> <span class="arg">expr2</span> : (<span class="type">boolean</span>, <span class="type">boolean</span>) -&gt; <span class="type">boolean</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">expr1</span> and <span class="arg">expr2</span> represent boolean expressions</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","or","||");?> evaluates to the boolean OR of the two 
boolean expressions <span class="arg">expr1</span> and <span class="arg">expr2</span>. <?php linkTo("command","or","||");?> evaluates to  
true iff at least one of <span class="arg">expr1</span> or <span class="arg">expr2</span> evaluates to true. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; false || false;<br> 
&nbsp;&nbsp;&nbsp;false<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; (1 == exp(0)) || (0 == log(1));<br> 
&nbsp;&nbsp;&nbsp;true<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","and","&&");?>, <?php linkTo("command","not","!");?> 
</div> 
