<a name="execute"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","execute","execute");?> 
<span class="smallDescription">executes the content of a file 
</span> 
</div> 
<div class="divLibraryName"> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","execute","execute");?>(<span class="arg">filename</span>) : <span class="type">string</span> -&gt; <span class="type">void</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">filename</span> is a string representing a file name</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","execute","execute");?> opens the file indicated by <span class="arg">filename</span>, and executes the sequence of  
commands it contains. This command is evaluated at execution time: this way you 
can modify the file <span class="arg">filename</span> (for instance using <?php linkTo("command","bashexecute","bashexecute");?>) and execute it 
just after. 
</li><li>If <span class="arg">filename</span> contains a command <?php linkTo("command","execute","execute");?>, it will be executed recursively. 
</li><li>If <span class="arg">filename</span> contains a call to <?php linkTo("command","restart","restart");?>, it will be neglected. 
</li><li>If <span class="arg">filename</span> contains a call to <?php linkTo("command","quit","quit");?>, the commands following <?php linkTo("command","quit","quit");?> 
in <span class="arg">filename</span> will be neglected. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; a=2;<br> 
&nbsp;&nbsp;&nbsp;&gt; a;<br> 
&nbsp;&nbsp;&nbsp;2<br> 
&nbsp;&nbsp;&nbsp;&gt; print("a=1;") &gt; "example.sollya";<br> 
&nbsp;&nbsp;&nbsp;&gt; execute("example.sollya"); <br> 
&nbsp;&nbsp;&nbsp;&gt; a;<br> 
&nbsp;&nbsp;&nbsp;1<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; verbosity=1!;<br> 
&nbsp;&nbsp;&nbsp;&gt; print("a=1; restart; a=2;") &gt; "example.sollya";<br> 
&nbsp;&nbsp;&nbsp;&gt; execute("example.sollya"); <br> 
&nbsp;&nbsp;&nbsp;Warning: a restart command has been used in a file read into another.<br> 
&nbsp;&nbsp;&nbsp;This restart command will be neglected.<br> 
&nbsp;&nbsp;&nbsp;&gt; a;<br> 
&nbsp;&nbsp;&nbsp;2<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; verbosity=1!;<br> 
&nbsp;&nbsp;&nbsp;&gt; print("a=1; quit; a=2;") &gt; "example.sollya";<br> 
&nbsp;&nbsp;&nbsp;&gt; execute("example.sollya"); <br> 
&nbsp;&nbsp;&nbsp;Warning: the execution of a file read by execute demanded stopping the interpretation but it is not stopped.<br> 
&nbsp;&nbsp;&nbsp;&gt; a;<br> 
&nbsp;&nbsp;&nbsp;1<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","parse","parse");?>, <?php linkTo("command","readfile","readfile");?>, <?php linkTo("command","write","write");?>, <?php linkTo("command","print","print");?>, <?php linkTo("command","bashexecute","bashexecute");?>, <?php linkTo("command","quit","quit");?>, <?php linkTo("command","restart","restart");?> 
</div> 
