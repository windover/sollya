<a name="midpointmode"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","midpointmode","midpointmode");?> 
<span class="smallDescription">global variable controlling the way intervals are displayed. 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library names:</h2> 
<span class="commandline type">void sollya_lib_set_midpointmode_and_print(sollya_obj_t)</span> 
<span class="commandline type">void sollya_lib_set_midpointmode(sollya_obj_t)</span> 
<span class="commandline type">sollya_obj_t sollya_lib_get_midpointmode()</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","midpointmode","midpointmode");?> = <span class="arg">activation value</span> : <span class="type">on|off</span> -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","midpointmode","midpointmode");?> = <span class="arg">activation value</span> ! : <span class="type">on|off</span> -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","midpointmode","midpointmode");?> : <span class="type">on|off</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">activation value</span> enables or disables the mode.</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","midpointmode","midpointmode");?> is a global variable. When its value is <?php linkTo("command","off","off");?>, intervals are displayed 
as usual (in the form [a;b]). 
When its value is <?php linkTo("command","on","on");?>, and if a and b have the same first significant digits, 
the interval in displayed in a way that lets one immediately see the common 
digits of the two bounds. 
</li><li>This mode is supported only with <?php linkTo("command","display","display");?> set to <?php linkTo("command","decimal","decimal");?>. In other modes of  
display, <?php linkTo("command","midpointmode","midpointmode");?> value is simply ignored. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; a = round(Pi,30,RD);<br> 
&nbsp;&nbsp;&nbsp;&gt; b = round(Pi,30,RU);<br> 
&nbsp;&nbsp;&nbsp;&gt; d = [a,b];<br> 
&nbsp;&nbsp;&nbsp;&gt; d;<br> 
&nbsp;&nbsp;&nbsp;[3.1415926516056060791015625;3.1415926553308963775634765625]<br> 
&nbsp;&nbsp;&nbsp;&gt; midpointmode=on!;<br> 
&nbsp;&nbsp;&nbsp;&gt; d;<br> 
&nbsp;&nbsp;&nbsp;0.314159265~1/6~e1<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","on","on");?>, <?php linkTo("command","off","off");?>, <?php linkTo("command","roundingwarnings","roundingwarnings");?>, <?php linkTo("command","display","display");?>, <?php linkTo("command","decimal","decimal");?> 
</div> 
