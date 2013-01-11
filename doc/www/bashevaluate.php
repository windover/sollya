<a name="bashevaluate"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","bashevaluate","bashevaluate");?> 
<span class="smallDescription">executes a shell command and returns its output as a string 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library names:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_bashevaluate(sollya_obj_t, ...)</span> 
<span class="commandline type">sollya_obj_t sollya_lib_v_bashevaluate(sollya_obj_t, va_list)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","bashevaluate","bashevaluate");?>(<span class="arg">command</span>) : <span class="type">string</span> -&gt; <span class="type">string</span></span> 
<span class="commandline"><?php linkTo("command","bashevaluate","bashevaluate");?>(<span class="arg">command</span>,<span class="arg">input</span>) : (<span class="type">string</span>, <span class="type">string</span>) -&gt; <span class="type">string</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">command</span> is a command to be interpreted by the shell.</li> 
<li><span class="arg">input</span> is an optional character sequence to be fed to the command.</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","bashevaluate","bashevaluate");?>(<span class="arg">command</span>) will execute the shell command <span class="arg">command</span> in a shell. 
All output on the command's standard output is collected and returned  
as a character sequence. 
</li><li>If an additional argument <span class="arg">input</span> is given in a call to 
<?php linkTo("command","bashevaluate","bashevaluate");?>(<span class="arg">command</span>,<span class="arg">input</span>), this character sequence is written to the 
standard input of the command <span class="arg">command</span> that gets executed. 
</li><li>All characters output by <span class="arg">command</span> are included in the character 
sequence to which <?php linkTo("command","bashevaluate","bashevaluate");?> evaluates but two exceptions. Every NULL 
character ('\0') in the output is replaced with 
'?' as Sollya is unable to handle character sequences containing that 
character. Additionally, if the output ends in a newline character 
('\n'), this character is stripped off. Other 
newline characters which are not at the end of the output are left as 
such. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; bashevaluate("LANG=C date");<br> 
&nbsp;&nbsp;&nbsp;Fri Jan 11 14:24:16 CET 2013<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; [| bashevaluate("echo Hello") |];<br> 
&nbsp;&nbsp;&nbsp;[|"Hello"|]<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; a = bashevaluate("sed -e 's/a/e/g;'", "Hallo");<br> 
&nbsp;&nbsp;&nbsp;&gt; a;<br> 
&nbsp;&nbsp;&nbsp;Hello<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","bashexecute","bashexecute");?> 
</div> 
