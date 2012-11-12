<a name="timing"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","timing","timing");?> 
<span class="smallDescription">global variable controlling timing measures in Sollya. 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library names:</h2> 
<span class="commandline type">void sollya_lib_set_timing_and_print(sollya_obj_t)</span> 
<span class="commandline type">void sollya_lib_set_timing(sollya_obj_t)</span> 
<span class="commandline type">sollya_obj_t sollya_lib_get_timing()</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","timing","timing");?> = <span class="arg">activation value</span> : <span class="type">on|off</span> -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","timing","timing");?> = <span class="arg">activation value</span> ! : <span class="type">on|off</span> -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","timing","timing");?> : <span class="type">on|off</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">activation value</span> controls if timing should be performed or not</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","timing","timing");?> is a global variable. When its value is <?php linkTo("command","on","on");?>, the time spent in each  
command is measured and displayed (for <?php linkTo("command","verbosity","verbosity");?> levels higher than 1). 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; verbosity=1!;<br> 
&nbsp;&nbsp;&nbsp;&gt; timing=on;<br> 
&nbsp;&nbsp;&nbsp;Timing has been activated.<br> 
&nbsp;&nbsp;&nbsp;&gt; p=remez(sin(x),10,[-1;1]);<br> 
&nbsp;&nbsp;&nbsp;Information: Remez: computing the matrix spent 2 ms<br> 
&nbsp;&nbsp;&nbsp;Information: Remez: computing the quality of approximation spent 20 ms<br> 
&nbsp;&nbsp;&nbsp;Information: Remez: computing the quality of approximation spent 10 ms<br> 
&nbsp;&nbsp;&nbsp;Information: Remez: computing the quality of approximation spent 10 ms<br> 
&nbsp;&nbsp;&nbsp;Information: computing a minimax approximation spent 166 ms<br> 
&nbsp;&nbsp;&nbsp;Information: assignment spent 178 ms<br> 
&nbsp;&nbsp;&nbsp;Information: full execution of the last parse chunk spent 200 ms<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","on","on");?>, <?php linkTo("command","off","off");?>, <?php linkTo("command","time","time");?> 
</div> 
