<a name="unsuppressmessage"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","unsuppressmessage","unsuppressmessage");?> 
<span class="smallDescription">unsuppresses the displaying of messages with a certain number 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library name:</h2> 
<span class="commandline type">void sollya_lib_unsuppressmessage(sollya_obj_t, ...);</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","unsuppressmessage","unsuppressmessage");?>(<span class="arg">msg num 1</span>, ..., <span class="arg">msg num n</span>)   : (<span class="type">integer</span>, ..., <span class="type">integer</span>) -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","unsuppressmessage","unsuppressmessage");?>(<span class="arg">msg list</span>)   : <span class="type">list</span> -&gt; <span class="type">void</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">msg num 1</span> thru <span class="arg">msg num n</span> represent the numbers of n messages to be suppressed</li> 
<li><span class="arg">msg list</span> represents a list with numbers of messages to be suppressed</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>The <?php linkTo("command","unsuppressmessage","unsuppressmessage");?> command allows particular warning and information 
messages that have been suppressed from message output to be 
unsuppressed, i.e. activated for display again. Every Sollya warning 
or information message (that is not fatal to the tool's execution) has 
a message number. When these message numbers <span class="arg">msg num 1</span> thru <span class="arg">msg num n</span>  
are given to <?php linkTo("command","unsuppressmessage","unsuppressmessage");?>, the corresponding message are displayed 
again, as they are by default at according verbosity levels. Actually, 
the <?php linkTo("command","unsuppressmessage","unsuppressmessage");?> command just reverts the effects of the <?php linkTo("command","suppressmessage","suppressmessage");?> 
command. 
</li><li>Instead of giving <?php linkTo("command","unsuppressmessage","unsuppressmessage");?> several message numbers <span class="arg">msg num 1</span> thru 
<span class="arg">msg num n</span> or calling <?php linkTo("command","unsuppressmessage","unsuppressmessage");?> several times, it is possible to give 
a whole list <span class="arg">msg list</span> of message numbers to <?php linkTo("command","unsuppressmessage","unsuppressmessage");?>. 
</li><li>The user should be aware that <?php linkTo("command","unsuppressmessage","unsuppressmessage");?> presents sticky behavior for 
the warning and information messages suppressed from output.  In fact, 
<?php linkTo("command","unsuppressmessage","unsuppressmessage");?> just unsuppresses the warning or information messages given 
in argument.  All other suppressed messages stay suppressed until they 
get unsuppressed by subsequent calls to <?php linkTo("command","unsuppressmessage","unsuppressmessage");?> or the Sollya tool 
is restarted. This behavior distinguishes message suppression from 
other global states of the Sollya tool. The user may use 
<?php linkTo("command","getsuppressedmessages","getsuppressedmessages");?> to obtain a list of currently suppressed 
messages. In particular, in order to unsuppressed all currently 
suppressed warning or information messages, the user may feed the 
output of <?php linkTo("command","getsuppressedmessages","getsuppressedmessages");?> (a list) into <?php linkTo("command","unsuppressmessage","unsuppressmessage");?>. 
</li><li>The user should also note that unsuppressing warning or information 
messages with <?php linkTo("command","unsuppressmessage","unsuppressmessage");?> just reverts the effects of the <?php linkTo("command","suppressmessage","suppressmessage");?> 
command but that other conditions exist that affect the actual displaying  
of a message, such as global verbosity (see <?php linkTo("command","verbosity","verbosity");?>) and modes 
like rounding warnings (see <?php linkTo("command","roundingwarnings","roundingwarnings");?>). A message will not just  
get displayed because it was unsuppressed with <?php linkTo("command","unsuppressmessage","unsuppressmessage");?>. 
</li><li>When <?php linkTo("command","unsuppressmessage","unsuppressmessage");?> is used on message numbers that do not exist in the 
current version of the tool, a warning is displayed. The call has no 
other effect though. 
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
&nbsp;&nbsp;&nbsp;&gt; suppressmessage(174);<br> 
&nbsp;&nbsp;&nbsp;&gt; 0.1;<br> 
&nbsp;&nbsp;&nbsp;0.1<br> 
&nbsp;&nbsp;&nbsp;&gt; suppressmessage(174);<br> 
&nbsp;&nbsp;&nbsp;&gt; 0.1;<br> 
&nbsp;&nbsp;&nbsp;0.1<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; verbosity = 12;<br> 
&nbsp;&nbsp;&nbsp;The verbosity level has been set to 12.<br> 
&nbsp;&nbsp;&nbsp;&gt; showmessagenumbers = on; <br> 
&nbsp;&nbsp;&nbsp;Displaying of message numbers has been activated.<br> 
&nbsp;&nbsp;&nbsp;&gt; diff(exp(x * 0.1));<br> 
&nbsp;&nbsp;&nbsp;Warning (174): Rounding occurred when converting the constant "0.1" to floating-point with 165 bits.<br> 
&nbsp;&nbsp;&nbsp;If safe computation is needed, try to increase the precision.<br> 
&nbsp;&nbsp;&nbsp;Information (196): formally differentiating a function.<br> 
&nbsp;&nbsp;&nbsp;Information (197): differentiating the expression 'exp(x * 0.1)'<br> 
&nbsp;&nbsp;&nbsp;Information (204): extraction of coefficient terms from a polynomial uses a special algorithm for Horner forms.<br> 
&nbsp;&nbsp;&nbsp;Information (207): no Horner simplification will be performed because the given tree is already in Horner form.<br> 
&nbsp;&nbsp;&nbsp;Information (207): no Horner simplification will be performed because the given tree is already in Horner form.<br> 
&nbsp;&nbsp;&nbsp;Information (207): no Horner simplification will be performed because the given tree is already in Horner form.<br> 
&nbsp;&nbsp;&nbsp;Information (207): no Horner simplification will be performed because the given tree is already in Horner form.<br> 
&nbsp;&nbsp;&nbsp;exp(x * 0.1) * 0.1<br> 
&nbsp;&nbsp;&nbsp;&gt; suppressmessage([| 174, 207, 196 |]);<br> 
&nbsp;&nbsp;&nbsp;&gt; diff(exp(x * 0.1));<br> 
&nbsp;&nbsp;&nbsp;Information (197): differentiating the expression 'exp(x * 0.1)'<br> 
&nbsp;&nbsp;&nbsp;Information (204): extraction of coefficient terms from a polynomial uses a special algorithm for Horner forms.<br> 
&nbsp;&nbsp;&nbsp;exp(x * 0.1) * 0.1<br> 
&nbsp;&nbsp;&nbsp;&gt; unsuppressmessage([| 174, 196 |]);<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; verbosity = 12;<br> 
&nbsp;&nbsp;&nbsp;The verbosity level has been set to 12.<br> 
&nbsp;&nbsp;&nbsp;&gt; showmessagenumbers = on;<br> 
&nbsp;&nbsp;&nbsp;Displaying of message numbers has been activated.<br> 
&nbsp;&nbsp;&nbsp;&gt; suppressmessage(207, 387, 390, 388, 391, 196, 195, 197, 205);<br> 
&nbsp;&nbsp;&nbsp;&gt; getsuppressedmessages();<br> 
&nbsp;&nbsp;&nbsp;[|195, 196, 197, 205, 207, 387, 388, 390, 391|]<br> 
&nbsp;&nbsp;&nbsp;&gt; evaluate(x/sin(x) - 1, [-1;1]);<br> 
&nbsp;&nbsp;&nbsp;[0;0.85081571768092561791175324139865019347039665509409]<br> 
&nbsp;&nbsp;&nbsp;&gt; unsuppressmessage(getsuppressedmessages());<br> 
&nbsp;&nbsp;&nbsp;&gt; getsuppressedmessages();<br> 
&nbsp;&nbsp;&nbsp;[| |]<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","getsuppressedmessages","getsuppressedmessages");?>, <?php linkTo("command","suppressmessage","suppressmessage");?>, <?php linkTo("command","unsuppressmessage","unsuppressmessage");?>, <?php linkTo("command","verbosity","verbosity");?>, <?php linkTo("command","roundingwarnings","roundingwarnings");?> 
</div> 
