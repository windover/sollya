<a name="restart"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","restart","restart");?> 
<span class="smallDescription">brings Sollya back to its initial state 
</span> 
</div> 
<div class="divLibraryName"> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","restart","restart");?> : <span class="type">void</span> -&gt; <span class="type">void</span></span> 
 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>The command <?php linkTo("command","restart","restart");?> brings Sollya back to its initial state.  All 
current state is abandoned, all libraries unbound and all memory freed. 
<br><br> 
The <?php linkTo("command","restart","restart");?> command has no effect when executed inside a Sollya 
script read into a main Sollya script using <?php linkTo("command","execute","execute");?>. It is executed 
in a Sollya script included by a #include macro. 
<br><br> 
Using the <?php linkTo("command","restart","restart");?> command in nested elements of imperative 
programming like for or while loops is possible. Since in most cases 
abandoning the current state of Sollya means altering a loop 
invariant, warnings for the impossibility of continuing a loop may 
follow unless the state is rebuilt. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; print(exp(x));<br> 
&nbsp;&nbsp;&nbsp;exp(x)<br> 
&nbsp;&nbsp;&nbsp;&gt; a = 3;<br> 
&nbsp;&nbsp;&nbsp;&gt; restart;<br> 
&nbsp;&nbsp;&nbsp;The tool has been restarted.<br> 
&nbsp;&nbsp;&nbsp;&gt; print(x);<br> 
&nbsp;&nbsp;&nbsp;x<br> 
&nbsp;&nbsp;&nbsp;&gt; a;<br> 
&nbsp;&nbsp;&nbsp;Warning: the identifier "a" is neither assigned to, nor bound to a library function nor external procedure, nor equal to the current free variable.<br> 
&nbsp;&nbsp;&nbsp;Will interpret "a" as "x".<br> 
&nbsp;&nbsp;&nbsp;x<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; print(exp(x));<br> 
&nbsp;&nbsp;&nbsp;exp(x)<br> 
&nbsp;&nbsp;&nbsp;&gt; for i from 1 to 10 do {<br> 
&nbsp;&nbsp;&nbsp;&nbsp; 	print(i);<br> 
&nbsp;&nbsp;&nbsp;&nbsp; 	if (i == 5) then restart;<br> 
&nbsp;&nbsp;&nbsp;&nbsp; };<br> 
&nbsp;&nbsp;&nbsp;1<br> 
&nbsp;&nbsp;&nbsp;2<br> 
&nbsp;&nbsp;&nbsp;3<br> 
&nbsp;&nbsp;&nbsp;4<br> 
&nbsp;&nbsp;&nbsp;5<br> 
&nbsp;&nbsp;&nbsp;The tool has been restarted.<br> 
&nbsp;&nbsp;&nbsp;Warning: the tool has been restarted inside a for loop.<br> 
&nbsp;&nbsp;&nbsp;The for loop will no longer be executed.<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; print(exp(x));<br> 
&nbsp;&nbsp;&nbsp;exp(x)<br> 
&nbsp;&nbsp;&nbsp;&gt; a = 3;<br> 
&nbsp;&nbsp;&nbsp;&gt; for i from 1 to 10 do {<br> 
&nbsp;&nbsp;&nbsp;&nbsp; 	print(i);<br> 
&nbsp;&nbsp;&nbsp;&nbsp; 	if (i == 5) then {<br> 
&nbsp;&nbsp;&nbsp;&nbsp; 		restart;<br> 
&nbsp;&nbsp;&nbsp;&nbsp; 		i = 7;<br> 
&nbsp;&nbsp;&nbsp;&nbsp; 	};<br> 
&nbsp;&nbsp;&nbsp;&nbsp; };<br> 
&nbsp;&nbsp;&nbsp;1<br> 
&nbsp;&nbsp;&nbsp;2<br> 
&nbsp;&nbsp;&nbsp;3<br> 
&nbsp;&nbsp;&nbsp;4<br> 
&nbsp;&nbsp;&nbsp;5<br> 
&nbsp;&nbsp;&nbsp;The tool has been restarted.<br> 
&nbsp;&nbsp;&nbsp;8<br> 
&nbsp;&nbsp;&nbsp;9<br> 
&nbsp;&nbsp;&nbsp;10<br> 
&nbsp;&nbsp;&nbsp;&gt; print(x);<br> 
&nbsp;&nbsp;&nbsp;x<br> 
&nbsp;&nbsp;&nbsp;&gt; a;<br> 
&nbsp;&nbsp;&nbsp;Warning: the identifier "a" is neither assigned to, nor bound to a library function nor external procedure, nor equal to the current free variable.<br> 
&nbsp;&nbsp;&nbsp;Will interpret "a" as "x".<br> 
&nbsp;&nbsp;&nbsp;x<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","quit","quit");?>, <?php linkTo("command","execute","execute");?> 
</div> 
