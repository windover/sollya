<a name="var"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","var","var");?> 
<span class="smallDescription">declaration of a local variable in a scope 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","var","var");?> <span class="arg">identifier1</span>, <span class="arg">identifier2</span>,... , <span class="arg">identifiern</span> : <span class="type">void</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">identifier1</span>, <span class="arg">identifier2</span>,... , <span class="arg">identifiern</span> represent variable identifiers</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>The keyword <?php linkTo("command","var","var");?> allows for the declaration of local variables 
<span class="arg">identifier1</span> through <span class="arg">identifiern</span> in a begin-end-block ({}-block). 
Once declared as a local variable, an identifier will shadow 
identifiers declared in higher scopes and undeclared identifiers 
available at top-level. 
<br><br> 
Variable declarations using <?php linkTo("command","var","var");?> are only possible in the 
beginning of a begin-end-block. Several <?php linkTo("command","var","var");?> statements can be 
given. Once another statement is given in a begin-end-block, no more 
<?php linkTo("command","var","var");?> statements can be given. 
<br><br> 
Variables declared by <?php linkTo("command","var","var");?> statements are dereferenced as <?php linkTo("command","error","error");?> 
until they are assigned a value.  
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; exp(x); <br> 
&nbsp;&nbsp;&nbsp;exp(x)<br> 
&nbsp;&nbsp;&nbsp;&gt; a = 3; <br> 
&nbsp;&nbsp;&nbsp;&gt; {var a, b; a=5; b=3; {var a; var b; b = true; a = 1; a; b;}; a; b; }; <br> 
&nbsp;&nbsp;&nbsp;1<br> 
&nbsp;&nbsp;&nbsp;true<br> 
&nbsp;&nbsp;&nbsp;5<br> 
&nbsp;&nbsp;&nbsp;3<br> 
&nbsp;&nbsp;&nbsp;&gt; a;<br> 
&nbsp;&nbsp;&nbsp;3<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","error","error");?>, <?php linkTo("command","proc","proc");?> 
</div> 
