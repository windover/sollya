<a name="sup"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","sup","sup");?> 
<span class="smallDescription">gives the upper bound of an interval. 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","sup","sup");?>(<span class="arg">I</span>) : <span class="type">range</span> -&gt; <span class="type">constant</span></span> 
<span class="commandline"><?php linkTo("command","sup","sup");?>(<span class="arg">x</span>) : <span class="type">constant</span> -&gt; <span class="type">constant</span></span> 
 
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
<li>Returns the upper bound of the interval <span class="arg">I</span>. Each bound of an interval has its  
own precision, so this command is exact, even if the current precision is too  
small to represent the bound. 
</li><li>When called on a real number <span class="arg">x</span>, <?php linkTo("command","sup","sup");?> considers it as an interval formed 
of a single point: [x, x]. In other words, <?php linkTo("command","sup","sup");?> behaves like the identity. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; sup([1;3]);<br> 
&nbsp;&nbsp;&nbsp;3<br> 
&nbsp;&nbsp;&nbsp;&gt; sup(5);<br> 
&nbsp;&nbsp;&nbsp;5<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; display=binary!;<br> 
&nbsp;&nbsp;&nbsp;&gt; I=[0; 0.111110000011111_2];<br> 
&nbsp;&nbsp;&nbsp;&gt; sup(I);<br> 
&nbsp;&nbsp;&nbsp;1.11110000011111_2 * 2^(-1)<br> 
&nbsp;&nbsp;&nbsp;&gt; prec=12!;<br> 
&nbsp;&nbsp;&nbsp;&gt; sup(I);<br> 
&nbsp;&nbsp;&nbsp;1.11110000011111_2 * 2^(-1)<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","inf","inf");?>, <?php linkTo("command","mid","mid");?>, <?php linkTo("command","max","max");?>, <?php linkTo("command","min","min");?> 
</div> 
