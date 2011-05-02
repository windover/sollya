<a name="sort"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","sort","sort");?> 
<span class="smallDescription">sorts a list of real numbers. 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","sort","sort");?>(<span class="arg">L</span>) : <span class="type">list</span> -&gt; <span class="type">list</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">L</span> is a list.</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>If <span class="arg">L</span> contains only constant values, <?php linkTo("command","sort","sort");?>(<span class="arg">L</span>) returns the same list, but 
sorted in increasing order. 
</li><li>If <span class="arg">L</span> contains at least one element that is not a constant, the command fails  
with a type error. 
</li><li>If <span class="arg">L</span> is an end-elliptic list, <?php linkTo("command","sort","sort");?> will fail with an error. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; sort([| |]);<br> 
&nbsp;&nbsp;&nbsp;[| |]<br> 
&nbsp;&nbsp;&nbsp;&gt; sort([|2,3,5,2,1,4|]);<br> 
&nbsp;&nbsp;&nbsp;[|1, 2, 2, 3, 4, 5|]<br> 
</div> 
</div> 
