<a name="getsuppressedmessages"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","getsuppressedmessages","getsuppressedmessages");?> 
<span class="smallDescription">returns a list of numbers of messages that have been suppressed from message output 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library name:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_getsuppressedmessages();</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","getsuppressedmessages","getsuppressedmessages");?>()   : <span class="type">void</span> -&gt; <span class="type">list</span></span> 
 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>The <?php linkTo("command","getsuppressedmessages","getsuppressedmessages");?> command allows the user to inspect the state of warning 
and information message suppression. When called, <?php linkTo("command","getsuppressedmessages","getsuppressedmessages");?> returns a 
list of integers numbers that stand for the warning and information 
messages that have been suppressed.  If no message is suppressed, 
<?php linkTo("command","getsuppressedmessages","getsuppressedmessages");?> returns an empty list. 
</li><li>Every Sollya warning or information message (that is not fatal to the 
tool's execution) has a message number. By default, these numbers are 
not displayed when a message is output. When message number displaying 
is activated using <?php linkTo("command","showmessagenumbers","showmessagenumbers");?>, the message numbers are 
displayed together with the message. This allows the user to match the 
numbers returned in a list by <?php linkTo("command","getsuppressedmessages","getsuppressedmessages");?> with the actual warning and 
information messages. 
</li><li>The list of message numbers returned by <?php linkTo("command","getsuppressedmessages","getsuppressedmessages");?> is suitable to be fed 
into the <?php linkTo("command","unsuppressmessage","unsuppressmessage");?> command. This way, the user may unsuppress 
all warning and information messages that have been suppressed. 
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
&nbsp;&nbsp;&nbsp;&gt; suppressmessage(407);<br> 
&nbsp;&nbsp;&nbsp;&gt; 0.1;<br> 
&nbsp;&nbsp;&nbsp;0.1<br> 
&nbsp;&nbsp;&nbsp;&gt; getsuppressedmessages();<br> 
&nbsp;&nbsp;&nbsp;[|174, 407|]<br> 
&nbsp;&nbsp;&nbsp;&gt; suppressmessage(207, 196);<br> 
&nbsp;&nbsp;&nbsp;&gt; getsuppressedmessages();<br> 
&nbsp;&nbsp;&nbsp;[|174, 196, 207, 407|]<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; suppressmessage(174, 209, 13, 24, 196);<br> 
&nbsp;&nbsp;&nbsp;&gt; suppressmessage([| 16, 17 |]);<br> 
&nbsp;&nbsp;&nbsp;&gt; suppressmessage(19);<br> 
&nbsp;&nbsp;&nbsp;&gt; unsuppressmessage([| 13, 17 |]);<br> 
&nbsp;&nbsp;&nbsp;&gt; getsuppressedmessages();<br> 
&nbsp;&nbsp;&nbsp;[|16, 19, 24, 174, 196, 209|]<br> 
&nbsp;&nbsp;&nbsp;&gt; unsuppressmessage(getsuppressedmessages());<br> 
&nbsp;&nbsp;&nbsp;&gt; getsuppressedmessages();<br> 
&nbsp;&nbsp;&nbsp;[| |]<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; verbosity = 12;<br> 
&nbsp;&nbsp;&nbsp;The verbosity level has been set to 12.<br> 
&nbsp;&nbsp;&nbsp;&gt; suppressmessage(174);<br> 
&nbsp;&nbsp;&nbsp;&gt; exp(x * 0.1);<br> 
&nbsp;&nbsp;&nbsp;Information: no Horner simplification will be performed because the given tree is already in Horner form.<br> 
&nbsp;&nbsp;&nbsp;exp(x * 0.1)<br> 
&nbsp;&nbsp;&nbsp;&gt; getsuppressedmessages();<br> 
&nbsp;&nbsp;&nbsp;[|174|]<br> 
&nbsp;&nbsp;&nbsp;&gt; verbosity = 0;<br> 
&nbsp;&nbsp;&nbsp;The verbosity level has been set to 0.<br> 
&nbsp;&nbsp;&nbsp;&gt; exp(x * 0.1);<br> 
&nbsp;&nbsp;&nbsp;exp(x * 0.1)<br> 
&nbsp;&nbsp;&nbsp;&gt; getsuppressedmessages();<br> 
&nbsp;&nbsp;&nbsp;[|174|]<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","getsuppressedmessages","getsuppressedmessages");?>, <?php linkTo("command","suppressmessage","suppressmessage");?>, <?php linkTo("command","unsuppressmessage","unsuppressmessage");?>, <?php linkTo("command","verbosity","verbosity");?>, <?php linkTo("command","roundingwarnings","roundingwarnings");?> 
</div> 
