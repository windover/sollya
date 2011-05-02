<a name="readxml"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","readxml","readxml");?> 
<span class="smallDescription">reads an expression written as a MathML-Content-Tree in a file 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","readxml","readxml");?>(<span class="arg">filename</span>) : <span class="type">string</span> -&gt; <span class="type">function</span> | <span class="type">error</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">filename</span> represents a character sequence indicating a file name</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","readxml","readxml");?>(<span class="arg">filename</span>) reads the first occurrence of a lambda 
application with one bounded variable on applications of the supported 
basic functions in file <span class="arg">filename</span> and returns it as a Sollya 
functional expression. 
<br><br> 
If the file <span class="arg">filename</span> does not contain a valid MathML-Content tree, 
<?php linkTo("command","readxml","readxml");?> tries to find an "annotation encoding" markup of type 
"sollya/text". If this annotation contains a character sequence 
that can be parsed by <?php linkTo("command","parse","parse");?>, <?php linkTo("command","readxml","readxml");?> returns that expression.  Otherwise 
<?php linkTo("command","readxml","readxml");?> displays a warning and returns an <?php linkTo("command","error","error");?> variable of type 
<span class="type">error</span>. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; readxml("readxmlexample.xml");<br> 
&nbsp;&nbsp;&nbsp;2 + x + exp(sin(x))<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","printxml","printxml");?>, <?php linkTo("command","readfile","readfile");?>, <?php linkTo("command","parse","parse");?>, <?php linkTo("command","error","error");?> 
</div> 
