<a name="nop"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","nop","nop");?> 
<span class="smallDescription">no operation 
</span> 
</div> 
<div class="divLibraryName"> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","nop","nop");?> : <span class="type">void</span> -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","nop","nop");?>() : <span class="type">void</span> -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","nop","nop");?>(<span class="arg">n</span>) : <span class="type">integer</span> -&gt; <span class="type">void</span></span> 
 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>The command <?php linkTo("command","nop","nop");?> does nothing. This means it is an explicit parse 
element in the Sollya language that finally does not produce any 
result or side-effect. 
</li><li>The command <?php linkTo("command","nop","nop");?> may take an optional positive integer argument <span class="arg">n</span>. The argument controls how much (useless) integer additions Sollya performs while doing nothing.  
With this behaviour, <?php linkTo("command","nop","nop");?> can be used for calibration of timing tests. 
</li><li>The keyword <?php linkTo("command","nop","nop");?> is implicit in some procedure 
definitions. Procedures without imperative body get parsed as if they 
had an imperative body containing one <?php linkTo("command","nop","nop");?> statement. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; nop;<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; nop(100);<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; succ = proc(n) { return n + 1; };<br> 
&nbsp;&nbsp;&nbsp;&gt; succ;<br> 
&nbsp;&nbsp;&nbsp;proc(n)<br> 
&nbsp;&nbsp;&nbsp;{<br> 
&nbsp;&nbsp;&nbsp;nop;<br> 
&nbsp;&nbsp;&nbsp;return (n) + (1);<br> 
&nbsp;&nbsp;&nbsp;}<br> 
&nbsp;&nbsp;&nbsp;&gt; succ(5);<br> 
&nbsp;&nbsp;&nbsp;6<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","proc","proc");?>, <?php linkTo("command","time","time");?> 
</div> 
