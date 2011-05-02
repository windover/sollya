<a name="dieonerrormode"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","dieonerrormode","dieonerrormode");?> 
<span class="smallDescription">global variable controlling if Sollya is exited on an error or not. 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","dieonerrormode","dieonerrormode");?> = <span class="arg">activation value</span> : <span class="type">on|off</span> -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","dieonerrormode","dieonerrormode");?> = <span class="arg">activation value</span> ! : <span class="type">on|off</span> -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","dieonerrormode","dieonerrormode");?> : <span class="type">on|off</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">activation value</span> controls if Sollya is exited on an error or not.</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","dieonerrormode","dieonerrormode");?> is a global variable. When its value is <?php linkTo("command","off","off");?>, which is the default, 
Sollya will not exit on any syntax, typing, side-effect errors. These 
errors will be caught by the tool, even if a memory might be leaked at  
that point. On evaluation, the <?php linkTo("command","error","error");?> special value will be produced. 
</li><li>When the value of the <?php linkTo("command","dieonerrormode","dieonerrormode");?> variable is <?php linkTo("command","on","on");?>, Sollya will exit 
on any syntax, typing, side-effect errors. A warning message will 
be printed in these cases at appropriate <?php linkTo("command","verbosity","verbosity");?> levels.  
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; verbosity = 1!;<br> 
&nbsp;&nbsp;&nbsp;&gt; dieonerrormode = off;<br> 
&nbsp;&nbsp;&nbsp;Die-on-error mode has been deactivated.<br> 
&nbsp;&nbsp;&nbsp;&gt; for i from true to false do i + "Salut";<br> 
&nbsp;&nbsp;&nbsp;Warning: one of the arguments of the for loop does not evaluate to a constant.<br> 
&nbsp;&nbsp;&nbsp;The for loop will not be executed.<br> 
&nbsp;&nbsp;&nbsp;&gt; exp(17);<br> 
&nbsp;&nbsp;&nbsp;Warning: rounding has happened. The value displayed is a faithful rounding of the true result.<br> 
&nbsp;&nbsp;&nbsp;2.41549527535752982147754351803858238798675673527224e7<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; verbosity = 1!;<br> 
&nbsp;&nbsp;&nbsp;&gt; dieonerrormode = off!;<br> 
&nbsp;&nbsp;&nbsp;&gt; 5 */&nbsp;&nbsp;4;<br> 
&nbsp;&nbsp;&nbsp;Warning: syntax error, unexpected DIVTOKEN.<br> 
&nbsp;&nbsp;&nbsp;The last symbol read has been "/".<br> 
&nbsp;&nbsp;&nbsp;Will skip input until next semicolon after the unexpected token. May leak memory.<br> 
&nbsp;&nbsp;&nbsp;&nbsp; exp(17);<br> 
&nbsp;&nbsp;&nbsp;Warning: rounding has happened. The value displayed is a faithful rounding of the true result.<br> 
&nbsp;&nbsp;&nbsp;2.41549527535752982147754351803858238798675673527224e7<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; verbosity = 1!;<br> 
&nbsp;&nbsp;&nbsp;&gt; dieonerrormode;<br> 
&nbsp;&nbsp;&nbsp;off<br> 
&nbsp;&nbsp;&nbsp;&gt; dieonerrormode = on!;<br> 
&nbsp;&nbsp;&nbsp;&gt; dieonerrormode;<br> 
&nbsp;&nbsp;&nbsp;on<br> 
&nbsp;&nbsp;&nbsp;&gt; for i from true to false do i + "Salut";<br> 
&nbsp;&nbsp;&nbsp;Warning: one of the arguments of the for loop does not evaluate to a constant.<br> 
&nbsp;&nbsp;&nbsp;The for loop will not be executed.<br> 
&nbsp;&nbsp;&nbsp;Warning: some syntax, typing or side-effect error has occurred.<br> 
&nbsp;&nbsp;&nbsp;As the die-on-error mode is activated, the tool will be exited.<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 4: </h2> 
&nbsp;&nbsp;&nbsp;&gt; verbosity = 1!;<br> 
&nbsp;&nbsp;&nbsp;&gt; dieonerrormode = on!;<br> 
&nbsp;&nbsp;&nbsp;&gt; 5 */&nbsp;&nbsp;4;<br> 
&nbsp;&nbsp;&nbsp;Warning: syntax error, unexpected DIVTOKEN.<br> 
&nbsp;&nbsp;&nbsp;The last symbol read has been "/".<br> 
&nbsp;&nbsp;&nbsp;Will skip input until next semicolon after the unexpected token. May leak memory.<br> 
&nbsp;&nbsp;&nbsp;Warning: some syntax, typing or side-effect error has occurred.<br> 
&nbsp;&nbsp;&nbsp;As the die-on-error mode is activated, the tool will be exited.<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 5: </h2> 
&nbsp;&nbsp;&nbsp;&gt; verbosity = 0!;<br> 
&nbsp;&nbsp;&nbsp;&gt; dieonerrormode = on!;<br> 
&nbsp;&nbsp;&nbsp;&gt; 5 */&nbsp;&nbsp;4;<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","on","on");?>, <?php linkTo("command","off","off");?>, <?php linkTo("command","verbosity","verbosity");?>, <?php linkTo("command","error","error");?> 
</div> 
