<a name="fullparentheses"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","fullparentheses","fullparentheses");?> 
<span class="smallDescription">activates, deactivates or inspects the state variable controlling output with full parenthesising 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","fullparentheses","fullparentheses");?> = <span class="arg">activation value</span> : <span class="type">on|off</span> -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","fullparentheses","fullparentheses");?> = <span class="arg">activation value</span> ! : <span class="type">on|off</span> -&gt; <span class="type">void</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">activation value</span> represents <?php linkTo("command","on","on");?> or <?php linkTo("command","off","off");?>, i.e. activation or deactivation</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>An assignment <?php linkTo("command","fullparentheses","fullparentheses");?> = <span class="arg">activation value</span>, where <span class="arg">activation value</span> 
is one of <?php linkTo("command","on","on");?> or <?php linkTo("command","off","off");?>, activates respectively deactivates the output 
of expressions with full parenthesising. In full parenthesising mode, 
Sollya commands like <?php linkTo("command","print","print");?>, <?php linkTo("command","write","write");?> and the implicit command when an 
expression is given at the prompt will output expressions with 
parenthesising at all places where it is necessary for expressions 
containing infix operators to be parsed back with the same 
result. Otherwise parentheses around associative operators are 
omitted. 
<br><br> 
If the assignment <?php linkTo("command","fullparentheses","fullparentheses");?> = <span class="arg">activation value</span> is followed by an 
exclamation mark, no message indicating the new state is 
displayed. Otherwise the user is informed of the new state of the 
global mode by an indication. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; autosimplify = off!;<br> 
&nbsp;&nbsp;&nbsp;&gt; fullparentheses = off;<br> 
&nbsp;&nbsp;&nbsp;Full parentheses mode has been deactivated.<br> 
&nbsp;&nbsp;&nbsp;&gt; print(1 + 2 + 3);<br> 
&nbsp;&nbsp;&nbsp;1 + 2 + 3<br> 
&nbsp;&nbsp;&nbsp;&gt; fullparentheses = on;<br> 
&nbsp;&nbsp;&nbsp;Full parentheses mode has been activated.<br> 
&nbsp;&nbsp;&nbsp;&gt; print(1 + 2 + 3);<br> 
&nbsp;&nbsp;&nbsp;(1 + 2) + 3<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","print","print");?>, <?php linkTo("command","write","write");?>, <?php linkTo("command","autosimplify","autosimplify");?> 
</div> 
