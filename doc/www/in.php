<a name="in"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","in","in");?> 
<span class="smallDescription">containment test operator 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><span class="arg">expr</span> <?php linkTo("command","in","in");?> <span class="arg">range1</span> : (<span class="type">constant</span>, <span class="type">range</span>) -&gt; <span class="type">boolean</span></span> 
<span class="commandline"><span class="arg">range1</span> <?php linkTo("command","in","in");?> <span class="arg">range2</span> : (<span class="type">range</span>, <span class="type">range</span>) -&gt; <span class="type">boolean</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">expr</span> represents a constant expression</li> 
<li><span class="arg">range1</span> and <span class="arg">range2</span> represent ranges (intervals)</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>When its first operand is a constant expression <span class="arg">expr</span>, 
the operator <?php linkTo("command","in","in");?> evaluates to true iff the constant value 
of the expression <span class="arg">expr</span> is contained in the interval <span class="arg">range1</span>. 
</li><li>When both its operands are ranges (intervals),  
the operator <?php linkTo("command","in","in");?> evaluates to true iff all values 
in <span class="arg">range1</span> are contained in the interval <span class="arg">range2</span>. 
</li><li><?php linkTo("command","in","in");?> is also used as a keyword for loops over the different 
elements of a list. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; 5 in [-4;7];<br> 
&nbsp;&nbsp;&nbsp;true<br> 
&nbsp;&nbsp;&nbsp;&gt; 4 in [-1;1];<br> 
&nbsp;&nbsp;&nbsp;false<br> 
&nbsp;&nbsp;&nbsp;&gt; 0 in sin([-17;17]);<br> 
&nbsp;&nbsp;&nbsp;true<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; [5;7] in [2;8];<br> 
&nbsp;&nbsp;&nbsp;true<br> 
&nbsp;&nbsp;&nbsp;&gt; [2;3] in [4;5];<br> 
&nbsp;&nbsp;&nbsp;false<br> 
&nbsp;&nbsp;&nbsp;&gt; [2;3] in [2.5;5];<br> 
&nbsp;&nbsp;&nbsp;false<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; for i in [|1,...,5|] do print(i);<br> 
&nbsp;&nbsp;&nbsp;1<br> 
&nbsp;&nbsp;&nbsp;2<br> 
&nbsp;&nbsp;&nbsp;3<br> 
&nbsp;&nbsp;&nbsp;4<br> 
&nbsp;&nbsp;&nbsp;5<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","equal","==");?>, <?php linkTo("command","neq","!=");?>, <?php linkTo("command","ge","&gt;=");?>, <?php linkTo("command","gt","&gt;");?>, <?php linkTo("command","le","&lt;=");?>, <?php linkTo("command","lt","&lt;");?>, <?php linkTo("command","not","!");?>, <?php linkTo("command","and","&&");?>, <?php linkTo("command","or","||");?>, <?php linkTo("command","prec","prec");?>, <?php linkTo("command","print","print");?> 
</div> 
