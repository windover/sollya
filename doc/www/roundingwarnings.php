<a name="roundingwarnings"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","roundingwarnings","roundingwarnings");?> 
<span class="smallDescription">global variable controlling whether or not a warning is displayed when roundings occur. 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library names:</h2> 
<span class="commandline type">void sollya_lib_set_roundingwarnings_and_print(sollya_obj_t)</span> 
<span class="commandline type">void sollya_lib_set_roundingwarnings(sollya_obj_t)</span> 
<span class="commandline type">sollya_obj_t sollya_lib_get_roundingwarnings()</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","roundingwarnings","roundingwarnings");?> = <span class="arg">activation value</span> : <span class="type">on|off</span> -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","roundingwarnings","roundingwarnings");?> = <span class="arg">activation value</span> ! : <span class="type">on|off</span> -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","roundingwarnings","roundingwarnings");?> : <span class="type">on|off</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">activation value</span> controls if warnings should be shown or not</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","roundingwarnings","roundingwarnings");?> is a global variable. When its value is <?php linkTo("command","on","on");?>, warnings are 
emitted in appropriate verbosity modes (see <?php linkTo("command","verbosity","verbosity");?>) when roundings 
occur.  When its value is <?php linkTo("command","off","off");?>, these warnings are suppressed. 
</li><li>This mode depends on a verbosity of at least 1. See 
<?php linkTo("command","verbosity","verbosity");?> for more details. 
</li><li>Default is <?php linkTo("command","on","on");?> when the standard input is a terminal and 
<?php linkTo("command","off","off");?> when Sollya input is read from a file. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; verbosity=1!;<br> 
&nbsp;&nbsp;&nbsp;&gt; roundingwarnings = on;<br> 
&nbsp;&nbsp;&nbsp;Rounding warning mode has been activated.<br> 
&nbsp;&nbsp;&nbsp;&gt; exp(0.1);<br> 
&nbsp;&nbsp;&nbsp;Warning: Rounding occurred when converting the constant "0.1" to floating-point with 165 bits.<br> 
&nbsp;&nbsp;&nbsp;If safe computation is needed, try to increase the precision.<br> 
&nbsp;&nbsp;&nbsp;Warning: rounding has happened. The value displayed is a faithful rounding of the true result.<br> 
&nbsp;&nbsp;&nbsp;1.1051709180756476248117078264902466682245471947375<br> 
&nbsp;&nbsp;&nbsp;&gt; roundingwarnings = off;<br> 
&nbsp;&nbsp;&nbsp;Rounding warning mode has been deactivated.<br> 
&nbsp;&nbsp;&nbsp;&gt; exp(0.1);<br> 
&nbsp;&nbsp;&nbsp;1.1051709180756476248117078264902466682245471947375<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","on","on");?>, <?php linkTo("command","off","off");?>, <?php linkTo("command","verbosity","verbosity");?>, <?php linkTo("command","midpointmode","midpointmode");?>, <?php linkTo("command","rationalmode","rationalmode");?> 
</div> 
