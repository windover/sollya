<a name="file"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","file","file");?> 
<span class="smallDescription">special value for commands <?php linkTo("command","plot","plot");?> and <?php linkTo("command","externalplot","externalplot");?> 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library names:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_file()</span> 
<span class="commandline type">int sollya_lib_is_file(sollya_obj_t)</span> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","file","file");?> is a special value used in commands <?php linkTo("command","plot","plot");?> and <?php linkTo("command","externalplot","externalplot");?> to save 
the result of the command in a data file. 
</li><li>As any value it can be affected to a variable and stored in lists. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; savemode=file;<br> 
&nbsp;&nbsp;&nbsp;&gt; name="plotSinCos";<br> 
&nbsp;&nbsp;&nbsp;&gt; plot(sin(x),0,cos(x),[-Pi,Pi],savemode, name);<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","externalplot","externalplot");?>, <?php linkTo("command","plot","plot");?>, <?php linkTo("command","postscript","postscript");?>, <?php linkTo("command","postscriptfile","postscriptfile");?> 
</div> 
