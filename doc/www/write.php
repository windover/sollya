<a name="write"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","write","write");?> 
<span class="smallDescription">prints an expression without separators 
</span> 
</div> 
<div class="divLibraryName"> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","write","write");?>(<span class="arg">expr1</span>,...,<span class="arg">exprn</span>) : (<span class="type">any type</span>,..., <span class="type">any type</span>) -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","write","write");?>(<span class="arg">expr1</span>,...,<span class="arg">exprn</span>) &gt; <span class="arg">filename</span> : (<span class="type">any type</span>,..., <span class="type">any type</span>, <span class="type">string</span>) -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","write","write");?>(<span class="arg">expr1</span>,...,<span class="arg">exprn</span>) &gt;&gt; <span class="arg">filename</span> : (<span class="type">any type</span>,...,<span class="type">any type</span>, <span class="type">string</span>) -&gt; <span class="type">void</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">expr</span> represents an expression</li> 
<li><span class="arg">filename</span> represents a character sequence indicating a file name</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","write","write");?>(<span class="arg">expr1</span>,...,<span class="arg">exprn</span>) prints the expressions <span class="arg">expr1</span> through 
<span class="arg">exprn</span>. The character sequences corresponding to the expressions are 
concatenated without any separator. No newline is displayed at the 
end.  In contrast to <?php linkTo("command","print","print");?>, <?php linkTo("command","write","write");?> expects the user to give all 
separators and newlines explicitly. 
<br><br> 
If a second argument <span class="arg">filename</span> is given after a single "&gt;", the 
displaying is not output on the standard output of Sollya but if in 
the file <span class="arg">filename</span> that get newly created or overwritten. If a double 
 "&gt;&gt;" is given, the output will be appended to the file <span class="arg">filename</span>. 
<br><br> 
The global variables <?php linkTo("command","display","display");?>, <?php linkTo("command","midpointmode","midpointmode");?> and <?php linkTo("command","fullparentheses","fullparentheses");?> have 
some influence on the formatting of the output (see <?php linkTo("command","display","display");?>, 
<?php linkTo("command","midpointmode","midpointmode");?> and <?php linkTo("command","fullparentheses","fullparentheses");?>). 
<br><br> 
Remark that if one of the expressions <span class="arg">expri</span> given in argument is of 
type <span class="type">string</span>, the character sequence <span class="arg">expri</span> evaluates to is 
displayed. However, if <span class="arg">expri</span> is of type <span class="type">list</span> and this list 
contains a variable of type <span class="type">string</span>, the expression for the list 
is displayed, i.e.  all character sequences get displayed surrounded 
by quotes ("). Nevertheless, escape sequences used upon defining 
character sequences are interpreted immediately. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; write(x + 2 + exp(sin(x))); <br> 
&nbsp;&nbsp;&nbsp;&gt; write("Hello\n");<br> 
&nbsp;&nbsp;&nbsp;x + 2 + exp(sin(x))Hello<br> 
&nbsp;&nbsp;&nbsp;&gt; write("Hello","world\n");<br> 
&nbsp;&nbsp;&nbsp;Helloworld<br> 
&nbsp;&nbsp;&nbsp;&gt; write("Hello","you", 4 + 3, "other persons.\n");<br> 
&nbsp;&nbsp;&nbsp;Helloyou7other persons.<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; write("Hello","\n");<br> 
&nbsp;&nbsp;&nbsp;Hello<br> 
&nbsp;&nbsp;&nbsp;&gt; write([|"Hello"|],"\n");<br> 
&nbsp;&nbsp;&nbsp;[|"Hello"|]<br> 
&nbsp;&nbsp;&nbsp;&gt; s = "Hello";<br> 
&nbsp;&nbsp;&nbsp;&gt; write(s,[|s|],"\n");<br> 
&nbsp;&nbsp;&nbsp;Hello[|"Hello"|]<br> 
&nbsp;&nbsp;&nbsp;&gt; t = "Hello\tyou";<br> 
&nbsp;&nbsp;&nbsp;&gt; write(t,[|t|],"\n");<br> 
&nbsp;&nbsp;&nbsp;Hello	you[|"Hello\tyou"|]<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; write(x + 2 + exp(sin(x))) &gt; "foo.sol";<br> 
&nbsp;&nbsp;&nbsp;&gt; readfile("foo.sol");<br> 
&nbsp;&nbsp;&nbsp;x + 2 + exp(sin(x))<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 4: </h2> 
&nbsp;&nbsp;&nbsp;&gt; write(x + 2 + exp(sin(x))) &gt;&gt; "foo.sol";<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","print","print");?>, <?php linkTo("command","printexpansion","printexpansion");?>, <?php linkTo("command","printdouble","printdouble");?>, <?php linkTo("command","printsingle","printsingle");?>, <?php linkTo("command","printxml","printxml");?>, <?php linkTo("command","readfile","readfile");?>, <?php linkTo("command","autosimplify","autosimplify");?>, <?php linkTo("command","display","display");?>, <?php linkTo("command","midpointmode","midpointmode");?>, <?php linkTo("command","fullparentheses","fullparentheses");?>, <?php linkTo("command","evaluate","evaluate");?>, <?php linkTo("command","roundingwarnings","roundingwarnings");?>, <?php linkTo("command","autosimplify","autosimplify");?> 
</div> 
