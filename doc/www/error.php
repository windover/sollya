<a name="error"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","error","error");?> 
<span class="smallDescription">expression representing an input that is wrongly typed or that cannot be executed 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","error","error");?> : <span class="type">error</span></span> 
 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>The variable <?php linkTo("command","error","error");?> represents an input during the evaluation of 
which a type or execution error has been detected or is to be 
detected. Inputs that are syntactically correct but wrongly typed 
evaluate to <?php linkTo("command","error","error");?> at some stage.  Inputs that are correctly typed 
but containing commands that depend on side-effects that cannot be 
performed or inputs that are wrongly typed at meta-level (cf. <?php linkTo("command","parse","parse");?>), 
evaluate to <?php linkTo("command","error","error");?>. 
<br><br> 
Remark that in contrast to all other elements of the Sollya language, 
<?php linkTo("command","error","error");?> compares neither equal nor unequal to itself. This provides a 
means of detecting syntax errors inside the Sollya language itself 
without introducing issues of two different wrongly typed inputs being 
equal. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; print(5 + "foo");<br> 
&nbsp;&nbsp;&nbsp;error<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; error;<br> 
&nbsp;&nbsp;&nbsp;error<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; error == error;<br> 
&nbsp;&nbsp;&nbsp;false<br> 
&nbsp;&nbsp;&nbsp;&gt; error != error;<br> 
&nbsp;&nbsp;&nbsp;false<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 4: </h2> 
&nbsp;&nbsp;&nbsp;&gt; correct = 5 + 6;<br> 
&nbsp;&nbsp;&nbsp;&gt; incorrect = 5 + "foo";<br> 
&nbsp;&nbsp;&nbsp;&gt; correct == correct;<br> 
&nbsp;&nbsp;&nbsp;true<br> 
&nbsp;&nbsp;&nbsp;&gt; incorrect == incorrect;<br> 
&nbsp;&nbsp;&nbsp;false<br> 
&nbsp;&nbsp;&nbsp;&gt; errorhappened = !(incorrect == incorrect);<br> 
&nbsp;&nbsp;&nbsp;&gt; errorhappened;<br> 
&nbsp;&nbsp;&nbsp;true<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","void","void");?>, <?php linkTo("command","parse","parse");?>, <?php linkTo("command","equal","==");?>, <?php linkTo("command","neq","!=");?> 
</div> 
