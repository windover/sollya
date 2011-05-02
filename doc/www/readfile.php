<a name="readfile"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","readfile","readfile");?> 
<span class="smallDescription">reads the content of a file into a string variable 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","readfile","readfile");?>(<span class="arg">filename</span>) : <span class="type">string</span> -&gt; <span class="type">string</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">filename</span> represents a character sequence indicating a file name</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","readfile","readfile");?> opens the file indicated by <span class="arg">filename</span>, reads it and puts its 
contents in a character sequence of type <span class="type">string</span> that is returned. 
<br><br> 
If the file indicated by <span class="arg">filename</span> cannot be opened for reading, a 
warning is displayed and <?php linkTo("command","readfile","readfile");?> evaluates to an <?php linkTo("command","error","error");?> variable of 
type <span class="type">error</span>. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; print("Hello world") &gt; "myfile.txt";<br> 
&nbsp;&nbsp;&nbsp;&gt; t = readfile("myfile.txt"); <br> 
&nbsp;&nbsp;&nbsp;&gt; t;<br> 
&nbsp;&nbsp;&nbsp;Hello world<br> 
&nbsp;&nbsp;&nbsp;<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; verbosity=1!;<br> 
&nbsp;&nbsp;&nbsp;&gt; readfile("afile.txt");<br> 
&nbsp;&nbsp;&nbsp;Warning: the file "afile.txt" could not be opened for reading.<br> 
&nbsp;&nbsp;&nbsp;Warning: at least one of the given expressions or a subexpression is not correctly typed<br> 
&nbsp;&nbsp;&nbsp;or its evaluation has failed because of some error on a side-effect.<br> 
&nbsp;&nbsp;&nbsp;error<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","parse","parse");?>, <?php linkTo("command","execute","execute");?>, <?php linkTo("command","write","write");?>, <?php linkTo("command","print","print");?>, <?php linkTo("command","bashexecute","bashexecute");?>, <?php linkTo("command","error","error");?> 
</div> 
