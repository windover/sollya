<a name="worstcase"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","worstcase","worstcase");?> 
<span class="smallDescription">searches for hard-to-round cases of a function 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","worstcase","worstcase");?>(<span class="arg">function</span>, <span class="arg">preimage precision</span>, <span class="arg">preimage exponent range</span>, <span class="arg">image precision</span>, <span class="arg">error bound</span>) : (<span class="type">function</span>, <span class="type">integer</span>, <span class="type">range</span>, <span class="type">integer</span>, <span class="type">constant</span>) -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","worstcase","worstcase");?>(<span class="arg">function</span>, <span class="arg">preimage precision</span>, <span class="arg">preimage exponent range</span>, <span class="arg">image precision</span>, <span class="arg">error bound</span>, <span class="arg">filename</span>) : (<span class="type">function</span>, <span class="type">integer</span>, <span class="type">range</span>, <span class="type">integer</span>, <span class="type">constant</span>, <span class="type">string</span>) -&gt; <span class="type">void</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">function</span> represents the function to be considered</li> 
<li><span class="arg">preimage precision</span> represents the precision of the preimages</li> 
<li><span class="arg">preimage exponent range</span> represents the exponents in the preimage format</li> 
<li><span class="arg">image precision</span> represents the precision of the format the images are to be rounded to</li> 
<li><span class="arg">error bound</span> represents the upper bound for the search w.r.t. the relative rounding error</li> 
<li><span class="arg">filename</span> represents a character sequence containing a filename</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>The <?php linkTo("command","worstcase","worstcase");?> command is deprecated. It searches for hard-to-round cases of 
a function. The command <?php linkTo("command","searchgal","searchgal");?> has a comparable functionality. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; worstcase(exp(x),24,[1,2],24,1b-26);<br> 
&nbsp;&nbsp;&nbsp;prec = 165<br> 
&nbsp;&nbsp;&nbsp;x = 1.99999988079071044921875		f(x) = 7.3890552520751953125		eps = 4.5998601423446695596184695493764120138001954979037e-9 = 2^(-27.695763) <br> 
&nbsp;&nbsp;&nbsp;x = 2		f(x) = 7.38905620574951171875		eps = 1.44563608749673018122228379395533417878125150587072e-8 = 2^(-26.043720) <br> 
&nbsp;&nbsp;&nbsp;<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","round","round");?>, <?php linkTo("command","searchgal","searchgal");?>, <?php linkTo("command","evaluate","evaluate");?> 
</div> 
