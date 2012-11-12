<a name="parse"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","parse","parse");?> 
<span class="smallDescription">parses an expression contained in a string 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library name:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_parse(sollya_obj_t)</span> 
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
&nbsp;&nbsp;&nbsp;The string remez(exp(x),5,[-1;1]) gives 8.7381909882756203676868315731687604903964388498642e-3 * x^5 + 4.3793696379596015478233171265365272893795005588381e-2 * x^4 + 0.16642465614952768185129433844012193925654065755905 * x^3 + 0.49919698262963614991826575452094101562044819693772 * x^2 + 1.00003834650599815466340068058231011540878088492516 * x + 1.00004475029559502606203712816558243384077522932213<br> 
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
