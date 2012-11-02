<a name="showmessagenumbers"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","showmessagenumbers","showmessagenumbers");?> 
<span class="smallDescription">activates, deactivates or inspects the state variable controlling the displaying of numbers for messages 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library names:</h2> 
<span class="commandline type">void sollya_lib_set_showmessagenumbers_and_print(sollya_obj_t)</span> 
<span class="commandline type">void sollya_lib_set_showmessagenumbers(sollya_obj_t)</span> 
<span class="commandline type">sollya_obj_t sollya_lib_get_showmessagenumbers()</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","showmessagenumbers","showmessagenumbers");?> = <span class="arg">activation value</span> : <span class="type">on|off</span> -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","showmessagenumbers","showmessagenumbers");?> = <span class="arg">activation value</span> ! : <span class="type">on|off</span> -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","showmessagenumbers","showmessagenumbers");?> : <span class="type">on|off</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">activation value</span> represents <?php linkTo("command","on","on");?> or <?php linkTo("command","off","off");?>, i.e. activation or deactivation</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>An assignment <?php linkTo("command","showmessagenumbers","showmessagenumbers");?> = <span class="arg">activation value</span>, where <span class="arg">activation value</span> 
is one of <?php linkTo("command","on","on");?> or <?php linkTo("command","off","off");?>, activates respectively deactivates the 
displaying of numbers for warning and information messages. Every 
Sollya warning or information message (that is not fatal to the 
tool's execution) has a message number. By default, these numbers are 
not displayed when a message is output. When message number displaying 
is activated, the message numbers are displayed together with the 
message. This allows the user to recover the number of a particular 
message in order to suppress resp. unsuppress the displaying of this 
particular message (see <?php linkTo("command","suppressmessage","suppressmessage");?> and <?php linkTo("command","unsuppressmessage","unsuppressmessage");?>). 
</li><li>The user should be aware of the fact that message number display 
activation resp. deactivation through <?php linkTo("command","showmessagenumbers","showmessagenumbers");?> does not affect message 
displaying in general. For instance, even with message number 
displaying activated, messages with only displayed when general 
verbosity and rounding warning mode are set accordingly. 
</li><li>If the assignment <?php linkTo("command","showmessagenumbers","showmessagenumbers");?> = <span class="arg">activation value</span> is followed by an 
exclamation mark, no message indicating the new state is 
displayed. Otherwise the user is informed of the new state of the 
global mode by an indication. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; verbosity = 1;<br> 
&nbsp;&nbsp;&nbsp;The verbosity level has been set to 1.<br> 
&nbsp;&nbsp;&nbsp;&gt; 0.1;<br> 
&nbsp;&nbsp;&nbsp;Warning: Rounding occurred when converting the constant "0.1" to floating-point with 165 bits.<br> 
&nbsp;&nbsp;&nbsp;If safe computation is needed, try to increase the precision.<br> 
&nbsp;&nbsp;&nbsp;0.1<br> 
&nbsp;&nbsp;&nbsp;&gt; showmessagenumbers = on;<br> 
&nbsp;&nbsp;&nbsp;Displaying of message numbers has been activated.<br> 
&nbsp;&nbsp;&nbsp;&gt; 0.1;<br> 
&nbsp;&nbsp;&nbsp;Warning (174): Rounding occurred when converting the constant "0.1" to floating-point with 165 bits.<br> 
&nbsp;&nbsp;&nbsp;If safe computation is needed, try to increase the precision.<br> 
&nbsp;&nbsp;&nbsp;0.1<br> 
&nbsp;&nbsp;&nbsp;&gt; showmessagenumbers;<br> 
&nbsp;&nbsp;&nbsp;on<br> 
&nbsp;&nbsp;&nbsp;&gt; showmessagenumbers = off!;<br> 
&nbsp;&nbsp;&nbsp;&gt; 0.1;<br> 
&nbsp;&nbsp;&nbsp;Warning: Rounding occurred when converting the constant "0.1" to floating-point with 165 bits.<br> 
&nbsp;&nbsp;&nbsp;If safe computation is needed, try to increase the precision.<br> 
&nbsp;&nbsp;&nbsp;0.1<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; showmessagenumbers = on;<br> 
&nbsp;&nbsp;&nbsp;Displaying of message numbers has been activated.<br> 
&nbsp;&nbsp;&nbsp;&gt; verbosity = 1;<br> 
&nbsp;&nbsp;&nbsp;The verbosity level has been set to 1.<br> 
&nbsp;&nbsp;&nbsp;&gt; diff(0.1 * x + 1.5 * x^2);<br> 
&nbsp;&nbsp;&nbsp;Warning (174): Rounding occurred when converting the constant "0.1" to floating-point with 165 bits.<br> 
&nbsp;&nbsp;&nbsp;If safe computation is needed, try to increase the precision.<br> 
&nbsp;&nbsp;&nbsp;0.1 + 3 * x<br> 
&nbsp;&nbsp;&nbsp;&gt; verbosity = 0;<br> 
&nbsp;&nbsp;&nbsp;The verbosity level has been set to 0.<br> 
&nbsp;&nbsp;&nbsp;&gt; diff(0.1 * x + 1.5 * x^2);<br> 
&nbsp;&nbsp;&nbsp;0.1 + 3 * x<br> 
&nbsp;&nbsp;&nbsp;&gt; verbosity = 12;<br> 
&nbsp;&nbsp;&nbsp;The verbosity level has been set to 12.<br> 
&nbsp;&nbsp;&nbsp;&gt; diff(0.1 * x + 1.5 * x^2);<br> 
&nbsp;&nbsp;&nbsp;Warning (174): Rounding occurred when converting the constant "0.1" to floating-point with 165 bits.<br> 
&nbsp;&nbsp;&nbsp;If safe computation is needed, try to increase the precision.<br> 
&nbsp;&nbsp;&nbsp;Information (196): formally differentiating a function.<br> 
&nbsp;&nbsp;&nbsp;Information (197): differentiating the expression '0.1 * x + 1.5 * x^2'<br> 
&nbsp;&nbsp;&nbsp;Information (205): extraction of coefficient terms from a polynomial uses a special algorithm for canonical forms.<br> 
&nbsp;&nbsp;&nbsp;Information (195): expression '0.1 + 2 * 1.5 * x' has been simplified to expression '0.1 + 3 * x'.<br> 
&nbsp;&nbsp;&nbsp;Information (207): no Horner simplification will be performed because the given tree is already in Horner form.<br> 
&nbsp;&nbsp;&nbsp;0.1 + 3 * x<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","getsuppressedmessages","getsuppressedmessages");?>, <?php linkTo("command","suppressmessage","suppressmessage");?>, <?php linkTo("command","unsuppressmessage","unsuppressmessage");?>, <?php linkTo("command","verbosity","verbosity");?>, <?php linkTo("command","roundingwarnings","roundingwarnings");?> 
</div> 
