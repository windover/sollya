<a name="print"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","print","print");?> 
<span class="smallDescription">prints an expression 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","print","print");?>(<span class="arg">expr1</span>,...,<span class="arg">exprn</span>) : (<span class="type">any type</span>,..., <span class="type">any type</span>) -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","print","print");?>(<span class="arg">expr1</span>,...,<span class="arg">exprn</span>) &gt; <span class="arg">filename</span> : (<span class="type">any type</span>,..., <span class="type">any type</span>, <span class="type">string</span>) -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","print","print");?>(<span class="arg">expr1</span>,...,<span class="arg">exprn</span>) &gt;&gt; <span class="arg">filename</span> : (<span class="type">any type</span>,...,<span class="type">any type</span>, <span class="type">string</span>) -&gt; <span class="type">void</span></span> 
 
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
<li><?php linkTo("command","print","print");?>(<span class="arg">expr1</span>,...,<span class="arg">exprn</span>) prints the expressions <span class="arg">expr1</span> through 
<span class="arg">exprn</span> separated by spaces and followed by a newline. 
<br><br> 
If a second argument <span class="arg">filename</span> is given after a single  "&gt;", the 
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
by double quotes ("). Nevertheless, escape sequences used upon defining 
character sequences are interpreted immediately. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; print(x + 2 + exp(sin(x))); <br> 
&nbsp;&nbsp;&nbsp;x + 2 + exp(sin(x))<br> 
&nbsp;&nbsp;&nbsp;&gt; print("Hello","world");<br> 
&nbsp;&nbsp;&nbsp;Hello world<br> 
&nbsp;&nbsp;&nbsp;&gt; print("Hello","you", 4 + 3, "other persons.");<br> 
&nbsp;&nbsp;&nbsp;Hello you 7 other persons.<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; print("Hello");<br> 
&nbsp;&nbsp;&nbsp;Hello<br> 
&nbsp;&nbsp;&nbsp;&gt; print([|"Hello"|]);<br> 
&nbsp;&nbsp;&nbsp;[|"Hello"|]<br> 
&nbsp;&nbsp;&nbsp;&gt; s = "Hello";<br> 
&nbsp;&nbsp;&nbsp;&gt; print(s,[|s|]);<br> 
&nbsp;&nbsp;&nbsp;Hello [|"Hello"|]<br> 
&nbsp;&nbsp;&nbsp;&gt; t = "Hello\tyou";<br> 
&nbsp;&nbsp;&nbsp;&gt; print(t,[|t|]);<br> 
&nbsp;&nbsp;&nbsp;Hello	you [|"Hello\tyou"|]<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; print(x + 2 + exp(sin(x))) &gt; "foo.sol";<br> 
&nbsp;&nbsp;&nbsp;&gt; readfile("foo.sol");<br> 
&nbsp;&nbsp;&nbsp;x + 2 + exp(sin(x))<br> 
&nbsp;&nbsp;&nbsp;<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 4: </h2> 
&nbsp;&nbsp;&nbsp;&gt; print(x + 2 + exp(sin(x))) &gt;&gt; "foo.sol";<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 5: </h2> 
&nbsp;&nbsp;&nbsp;&gt; display = decimal;<br> 
&nbsp;&nbsp;&nbsp;Display mode is decimal numbers.<br> 
&nbsp;&nbsp;&nbsp;&gt; a = evaluate(sin(pi * x), 0.25);<br> 
&nbsp;&nbsp;&nbsp;&gt; b = evaluate(sin(pi * x), [0.25; 0.25 + 1b-50]);<br> 
&nbsp;&nbsp;&nbsp;&gt; print(a);<br> 
&nbsp;&nbsp;&nbsp;0.70710678118654752440084436210484903928483593768847<br> 
&nbsp;&nbsp;&nbsp;&gt; display = binary;<br> 
&nbsp;&nbsp;&nbsp;Display mode is binary numbers.<br> 
&nbsp;&nbsp;&nbsp;&gt; print(a);<br> 
&nbsp;&nbsp;&nbsp;1.01101010000010011110011001100111111100111011110011001001000010001011001011111011000100110110011011101010100101010111110100111110001110101101111011000001011101010001_2 * 2^(-1)<br> 
&nbsp;&nbsp;&nbsp;&gt; display = hexadecimal;<br> 
&nbsp;&nbsp;&nbsp;Display mode is hexadecimal numbers.<br> 
&nbsp;&nbsp;&nbsp;&gt; print(a);<br> 
&nbsp;&nbsp;&nbsp;0xb.504f333f9de6484597d89b3754abe9f1d6f60ba88p-4<br> 
&nbsp;&nbsp;&nbsp;&gt; display = dyadic;<br> 
&nbsp;&nbsp;&nbsp;Display mode is dyadic numbers.<br> 
&nbsp;&nbsp;&nbsp;&gt; print(a);<br> 
&nbsp;&nbsp;&nbsp;33070006991101558613323983488220944360067107133265b-165<br> 
&nbsp;&nbsp;&nbsp;&gt; display = powers;<br> 
&nbsp;&nbsp;&nbsp;Display mode is dyadic numbers in integer-power-of-2 notation.<br> 
&nbsp;&nbsp;&nbsp;&gt; print(a);<br> 
&nbsp;&nbsp;&nbsp;33070006991101558613323983488220944360067107133265 * 2^(-165)<br> 
&nbsp;&nbsp;&nbsp;&gt; display = decimal;<br> 
&nbsp;&nbsp;&nbsp;Display mode is decimal numbers.<br> 
&nbsp;&nbsp;&nbsp;&gt; midpointmode = off;<br> 
&nbsp;&nbsp;&nbsp;Midpoint mode has been deactivated.<br> 
&nbsp;&nbsp;&nbsp;&gt; print(b);<br> 
&nbsp;&nbsp;&nbsp;[0.70710678118654752440084436210484903928483593768844;0.70710678118654949743721782517557347782646274417048]<br> 
&nbsp;&nbsp;&nbsp;&gt; midpointmode = on;<br> 
&nbsp;&nbsp;&nbsp;Midpoint mode has been activated.<br> 
&nbsp;&nbsp;&nbsp;&gt; print(b);<br> 
&nbsp;&nbsp;&nbsp;0.7071067811865~4/5~<br> 
&nbsp;&nbsp;&nbsp;&gt; display = dyadic;<br> 
&nbsp;&nbsp;&nbsp;Display mode is dyadic numbers.<br> 
&nbsp;&nbsp;&nbsp;&gt; print(b);<br> 
&nbsp;&nbsp;&nbsp;[2066875436943847413332748968013809022504194195829b-161;16535003495550825444196237019385936414432675156571b-164]<br> 
&nbsp;&nbsp;&nbsp;&gt; display = decimal;<br> 
&nbsp;&nbsp;&nbsp;Display mode is decimal numbers.<br> 
&nbsp;&nbsp;&nbsp;&gt; autosimplify = off;<br> 
&nbsp;&nbsp;&nbsp;Automatic pure tree simplification has been deactivated.<br> 
&nbsp;&nbsp;&nbsp;&gt; fullparentheses = off;<br> 
&nbsp;&nbsp;&nbsp;Full parentheses mode has been deactivated.<br> 
&nbsp;&nbsp;&nbsp;&gt; print(x + x * ((x + 1) + 1));<br> 
&nbsp;&nbsp;&nbsp;x + x * (x + 1 + 1)<br> 
&nbsp;&nbsp;&nbsp;&gt; fullparentheses = on;<br> 
&nbsp;&nbsp;&nbsp;Full parentheses mode has been activated.<br> 
&nbsp;&nbsp;&nbsp;&gt; print(x + x * ((x + 1) + 1));<br> 
&nbsp;&nbsp;&nbsp;x + (x * ((x + 1) + 1))<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","write","write");?>, <?php linkTo("command","printexpansion","printexpansion");?>, <?php linkTo("command","printdouble","printdouble");?>, <?php linkTo("command","printsingle","printsingle");?>, <?php linkTo("command","printxml","printxml");?>, <?php linkTo("command","readfile","readfile");?>, <?php linkTo("command","autosimplify","autosimplify");?>, <?php linkTo("command","display","display");?>, <?php linkTo("command","midpointmode","midpointmode");?>, <?php linkTo("command","fullparentheses","fullparentheses");?>, <?php linkTo("command","evaluate","evaluate");?>, <?php linkTo("command","rationalmode","rationalmode");?> 
</div> 
