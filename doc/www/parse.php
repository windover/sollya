<a name="parse"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","parse","parse");?> 
<span class="smallDescription">parses an expression contained in a string 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","parse","parse");?>(<span class="arg">string</span>) : <span class="type">string</span> -&gt; <span class="type">function</span> | <span class="type">error</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">string</span> represents a character sequence</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","parse","parse");?>(<span class="arg">string</span>) parses the character sequence <span class="arg">string</span> containing 
an expression built on constants and base functions. 
<br><br> 
If the character sequence does not contain a well-defined expression, 
a warning is displayed indicating a syntax error and <?php linkTo("command","parse","parse");?> returns 
a <?php linkTo("command","error","error");?> of type <span class="type">error</span>. 
</li><li>The character sequence to be parsed by <?php linkTo("command","parse","parse");?> may contain commands that  
return expressions, including <?php linkTo("command","parse","parse");?> itself. Those commands get executed after the string has been parsed. 
<?php linkTo("command","parse","parse");?>(<span class="arg">string</span>) will return the expression computed by the commands contained in the character  
sequence <span class="arg">string</span>. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; parse("exp(x)");<br> 
&nbsp;&nbsp;&nbsp;exp(x)<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; text = "remez(exp(x),5,[-1;1])";<br> 
&nbsp;&nbsp;&nbsp;&gt; print("The string", text, "gives", parse(text));<br> 
&nbsp;&nbsp;&nbsp;The string remez(exp(x),5,[-1;1]) gives 1.00004475029055070643077052482053398765426158966754 + x * (1.00003834652983970735244541124504033817544233075356 + x * (0.49919698262882986492168824494240374771969012861297 + x * (0.166424656075155194415920597322727380932279602909199 + x * (4.37936963873280470271257566207183496659575464236489e-2 + x * 8.7381910388065551140158420278330960479960476713376e-3))))<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; verbosity = 1!;<br> 
&nbsp;&nbsp;&nbsp;&gt; parse("5 + * 3");<br> 
&nbsp;&nbsp;&nbsp;Warning: syntax error, unexpected MULTOKEN. Will try to continue parsing (expecting ";"). May leak memory.<br> 
&nbsp;&nbsp;&nbsp;Warning: the string "5 + * 3" could not be parsed by the miniparser.<br> 
&nbsp;&nbsp;&nbsp;Warning: at least one of the given expressions or a subexpression is not correctly typed<br> 
&nbsp;&nbsp;&nbsp;or its evaluation has failed because of some error on a side-effect.<br> 
&nbsp;&nbsp;&nbsp;error<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","execute","execute");?>, <?php linkTo("command","readfile","readfile");?>, <?php linkTo("command","print","print");?>, <?php linkTo("command","error","error");?>, <?php linkTo("command","dieonerrormode","dieonerrormode");?> 
</div> 
