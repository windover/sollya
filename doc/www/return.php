<a name="return"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","return","return");?> 
<span class="smallDescription">indicates an expression to be returned in a procedure 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","return","return");?> <span class="arg">expression</span> : <span class="type">void</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">expression</span> represents the expression to be returned</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>The keyword <?php linkTo("command","return","return");?> allows for returning the (evaluated) expression 
<span class="arg">expression</span> at the end of a begin-end-block ({}-block) used as a 
Sollya procedure body. See <?php linkTo("command","proc","proc");?> for further details concerning 
Sollya procedure definitions. 
<br><br>  
Statements for returning expressions using <?php linkTo("command","return","return");?> are only possible 
 at the end of a begin-end-block used as a Sollya procedure 
 body. Only one <?php linkTo("command","return","return");?> statement can be given per begin-end-block. 
</li><li>If at the end of a procedure definition using <?php linkTo("command","proc","proc");?> no <?php linkTo("command","return","return");?> 
statement is given, a <?php linkTo("command","return","return");?> <?php linkTo("command","void","void");?> statement is implicitely 
added. Procedures, i.e. procedure objects, when printed out in Sollya 
defined with an implicit <?php linkTo("command","return","return");?> <?php linkTo("command","void","void");?> statement are displayed with 
this statement explicitly given. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; succ = proc(n) { var res; res := n + 1; return res; };<br> 
&nbsp;&nbsp;&nbsp;&gt; succ(5);<br> 
&nbsp;&nbsp;&nbsp;6<br> 
&nbsp;&nbsp;&nbsp;&gt; succ;<br> 
&nbsp;&nbsp;&nbsp;proc(n)<br> 
&nbsp;&nbsp;&nbsp;{<br> 
&nbsp;&nbsp;&nbsp;var res;<br> 
&nbsp;&nbsp;&nbsp;res := (n) + (1);<br> 
&nbsp;&nbsp;&nbsp;return res;<br> 
&nbsp;&nbsp;&nbsp;}<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; hey = proc(s) { print("Hello",s); };<br> 
&nbsp;&nbsp;&nbsp;&gt; hey("world");<br> 
&nbsp;&nbsp;&nbsp;Hello world<br> 
&nbsp;&nbsp;&nbsp;&gt; hey;<br> 
&nbsp;&nbsp;&nbsp;proc(s)<br> 
&nbsp;&nbsp;&nbsp;{<br> 
&nbsp;&nbsp;&nbsp;print("Hello", s);<br> 
&nbsp;&nbsp;&nbsp;return void;<br> 
&nbsp;&nbsp;&nbsp;}<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","proc","proc");?>, <?php linkTo("command","void","void");?> 
</div> 
