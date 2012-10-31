<a name="verbosity"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","verbosity","verbosity");?> 
<span class="smallDescription">global variable controlling the amount of information displayed by commands. 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library names:</h2> 
<span class="commandline type">void sollya_lib_set_verbosity_and_print(sollya_obj_t)</span> 
<span class="commandline type">void sollya_lib_set_verbosity(sollya_obj_t)</span> 
<span class="commandline type">sollya_obj_t sollya_lib_get_verbosity()</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","verbosity","verbosity");?> = <span class="arg">n</span> : <span class="type">integer</span> -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","verbosity","verbosity");?> = <span class="arg">n</span> ! : <span class="type">integer</span> -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","verbosity","verbosity");?> : <span class="type">integer</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">n</span> controls the amount of information to be displayed</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","verbosity","verbosity");?> accepts any integer value. At level 0, commands do not display anything 
on standard output. Note that very critical information may however be displayed on 
standard error. 
</li><li>Default level is 1. It displays important information such as warnings when  
roundings happen. 
</li><li>For higher levels more information is displayed depending on the command. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; verbosity=0!;<br> 
&nbsp;&nbsp;&nbsp;&gt; 1.2+"toto";<br> 
&nbsp;&nbsp;&nbsp;error<br> 
&nbsp;&nbsp;&nbsp;&gt; verbosity=1!;<br> 
&nbsp;&nbsp;&nbsp;&gt; 1.2+"toto";<br> 
&nbsp;&nbsp;&nbsp;Warning: Rounding occurred when converting the constant "1.2" to floating-point with 165 bits.<br> 
&nbsp;&nbsp;&nbsp;If safe computation is needed, try to increase the precision.<br> 
&nbsp;&nbsp;&nbsp;Warning: at least one of the given expressions or a subexpression is not correctly typed<br> 
&nbsp;&nbsp;&nbsp;or its evaluation has failed because of some error on a side-effect.<br> 
&nbsp;&nbsp;&nbsp;error<br> 
&nbsp;&nbsp;&nbsp;&gt; verbosity=2!;<br> 
&nbsp;&nbsp;&nbsp;&gt; 1.2+"toto";<br> 
&nbsp;&nbsp;&nbsp;Warning: Rounding occurred when converting the constant "1.2" to floating-point with 165 bits.<br> 
&nbsp;&nbsp;&nbsp;If safe computation is needed, try to increase the precision.<br> 
&nbsp;&nbsp;&nbsp;Warning: at least one of the given expressions or a subexpression is not correctly typed<br> 
&nbsp;&nbsp;&nbsp;or its evaluation has failed because of some error on a side-effect.<br> 
&nbsp;&nbsp;&nbsp;Information: the expression or a partial evaluation of it has been the following:<br> 
&nbsp;&nbsp;&nbsp;(1.19999999999999999999999999999999999999999999999999) + ("toto")<br> 
&nbsp;&nbsp;&nbsp;error<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","roundingwarnings","roundingwarnings");?>, <?php linkTo("command","suppressmessage","suppressmessage");?>, <?php linkTo("command","unsuppressmessage","unsuppressmessage");?>, <?php linkTo("command","showmessagenumbers","showmessagenumbers");?>, <?php linkTo("command","getsuppressedmessages","getsuppressedmessages");?> 
</div> 
