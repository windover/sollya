<a name="le"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","le","&lt;=");?> 
<span class="smallDescription">less-than-or-equal-to operator 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><span class="arg">expr1</span> <?php linkTo("command","le","&lt;=");?> <span class="arg">expr2</span> : (<span class="type">constant</span>, <span class="type">constant</span>) -&gt; <span class="type">boolean</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">expr1</span> and <span class="arg">expr2</span> represent constant expressions</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>The operator <?php linkTo("command","le","&lt;=");?> evaluates to true iff its operands <span class="arg">expr1</span> and 
<span class="arg">expr2</span> evaluate to two floating-point numbers a1 
respectively a2 with the global precision <?php linkTo("command","prec","prec");?> and 
a1 is less than or equal to a2. The user should 
be aware of the fact that because of floating-point evaluation, the 
operator <?php linkTo("command","le","&lt;=");?> is not exactly the same as the mathematical 
operation "less-than-or-equal-to". 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; 5 &lt;= 4;<br> 
&nbsp;&nbsp;&nbsp;false<br> 
&nbsp;&nbsp;&nbsp;&gt; 5 &lt;= 5;<br> 
&nbsp;&nbsp;&nbsp;true<br> 
&nbsp;&nbsp;&nbsp;&gt; 5 &lt;= 6;<br> 
&nbsp;&nbsp;&nbsp;true<br> 
&nbsp;&nbsp;&nbsp;&gt; exp(2) &lt;= exp(1);<br> 
&nbsp;&nbsp;&nbsp;false<br> 
&nbsp;&nbsp;&nbsp;&gt; log(1) &lt;= exp(2);<br> 
&nbsp;&nbsp;&nbsp;true<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; prec = 12;<br> 
&nbsp;&nbsp;&nbsp;The precision has been set to 12 bits.<br> 
&nbsp;&nbsp;&nbsp;&gt; 16385.1 &lt;= 16384.1;<br> 
&nbsp;&nbsp;&nbsp;true<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","equal","==");?>, <?php linkTo("command","neq","!=");?>, <?php linkTo("command","ge","&gt;=");?>, <?php linkTo("command","gt","&gt;");?>, <?php linkTo("command","lt","&lt;");?>, <?php linkTo("command","in","in");?>, <?php linkTo("command","not","!");?>, <?php linkTo("command","and","&&");?>, <?php linkTo("command","or","||");?>, <?php linkTo("command","prec","prec");?>, <?php linkTo("command","max","max");?>, <?php linkTo("command","min","min");?> 
</div> 
