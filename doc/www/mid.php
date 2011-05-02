<a name="mid"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","mid","mid");?> 
<span class="smallDescription">gives the middle of an interval. 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","mid","mid");?>(<span class="arg">I</span>) : <span class="type">range</span> -&gt; <span class="type">constant</span></span> 
<span class="commandline"><?php linkTo("command","mid","mid");?>(<span class="arg">x</span>) : <span class="type">constant</span> -&gt; <span class="type">constant</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">I</span> is an interval.</li> 
<li><span class="arg">x</span> is a real number.</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>Returns the middle of the interval <span class="arg">I</span>. If the middle is not exactly 
representable at the current precision, the value is returned as an 
unevaluated expression. 
</li><li>When called on a real number <span class="arg">x</span>, <?php linkTo("command","mid","mid");?> considers it as an interval formed 
of a single point: [x, x]. In other words, <?php linkTo("command","mid","mid");?> behaves like the identity. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; mid([1;3]);<br> 
&nbsp;&nbsp;&nbsp;2<br> 
&nbsp;&nbsp;&nbsp;&gt; mid(17);<br> 
&nbsp;&nbsp;&nbsp;17<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","inf","inf");?>, <?php linkTo("command","sup","sup");?> 
</div> 
