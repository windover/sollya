<a name="procedure"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","procedure","procedure");?> 
<span class="smallDescription">defines and assigns a Sollya procedure 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","procedure","procedure");?> <span class="arg">identifier</span>(<span class="arg">formal parameter1</span>, <span class="arg">formal parameter2</span>,..., <span class="arg">formal parameter n</span>) { <span class="arg">procedure body</span> } : <span class="type">void</span> -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","procedure","procedure");?> <span class="arg">identifier</span>(<span class="arg">formal parameter1</span>, <span class="arg">formal parameter2</span>,..., <span class="arg">formal parameter n</span>) { <span class="arg">procedure body</span> <?php linkTo("command","return","return");?> <span class="arg">expression</span>; } : <span class="type">void</span> -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","procedure","procedure");?> <span class="arg">identifier</span>(<span class="arg">formal list parameter</span> = ...) { <span class="arg">procedure body</span> } : <span class="type">void</span> -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","procedure","procedure");?> <span class="arg">identifier</span>(<span class="arg">formal list parameter</span> = ...) { <span class="arg">procedure body</span> <?php linkTo("command","return","return");?> <span class="arg">expression</span>; } : <span class="type">void</span> -&gt; <span class="type">void</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">identifier</span> represents the name of the procedure to be defined and assigned</li> 
<li><span class="arg">formal parameter1</span>, <span class="arg">formal parameter2</span> through <span class="arg">formal parameter n</span> represent identifiers used as formal parameters</li> 
<li><span class="arg">formal list parameter</span> represents an identifier used as a formal parameter for the list of an arbitrary number of parameters</li> 
<li><span class="arg">procedure body</span> represents the imperative statements in the body of the procedure</li> 
<li><span class="arg">expression</span> represents the expression <?php linkTo("command","procedure","procedure");?> shall evaluate to</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>The <?php linkTo("command","procedure","procedure");?> keyword allows for defining and assigning procedures in 
the Sollya language. It is an abbreviation to a procedure definition 
using <?php linkTo("command","proc","proc");?> with the same formal parameters, procedure body and 
return-expression followed by an assignment of the procedure (object) 
to the identifier <span class="arg">identifier</span>. In particular, all rules concerning 
local variables declared using the <?php linkTo("command","var","var");?> keyword apply for <?php linkTo("command","procedure","procedure");?>. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; procedure succ(n) { return n + 1; };<br> 
&nbsp;&nbsp;&nbsp;&gt; succ(5);<br> 
&nbsp;&nbsp;&nbsp;6<br> 
&nbsp;&nbsp;&nbsp;&gt; 3 + succ(0);<br> 
&nbsp;&nbsp;&nbsp;4<br> 
&nbsp;&nbsp;&nbsp;&gt; succ;<br> 
&nbsp;&nbsp;&nbsp;proc(n)<br> 
&nbsp;&nbsp;&nbsp;{<br> 
&nbsp;&nbsp;&nbsp;nop;<br> 
&nbsp;&nbsp;&nbsp;return (n) + (1);<br> 
&nbsp;&nbsp;&nbsp;}<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; procedure myprint(L = ...) { var i; for i in L do i; };<br> 
&nbsp;&nbsp;&nbsp;&gt; myprint("Lyon","Nancy","Beaverton","Coye-la-Foret","Amberg","Nizhny Novgorod","Cluj-Napoca");<br> 
&nbsp;&nbsp;&nbsp;Lyon<br> 
&nbsp;&nbsp;&nbsp;Nancy<br> 
&nbsp;&nbsp;&nbsp;Beaverton<br> 
&nbsp;&nbsp;&nbsp;Coye-la-Foret<br> 
&nbsp;&nbsp;&nbsp;Amberg<br> 
&nbsp;&nbsp;&nbsp;Nizhny Novgorod<br> 
&nbsp;&nbsp;&nbsp;Cluj-Napoca<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","proc","proc");?>, <?php linkTo("command","var","var");?> 
</div> 
