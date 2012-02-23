<a name="max"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","max","max");?> 
<span class="smallDescription">determines which of given constant expressions has maximum value 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","max","max");?>(<span class="arg">expr1</span>,<span class="arg">expr2</span>,...,<span class="arg">exprn</span>) : (<span class="type">constant</span>, <span class="type">constant</span>, ..., <span class="type">constant</span>) -&gt; <span class="type">constant</span></span> 
<span class="commandline"><?php linkTo("command","max","max");?>(<span class="arg">l</span>) : <span class="type">list</span> -&gt; <span class="type">constant</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">expr</span> are constant expressions.</li> 
<li><span class="arg">l</span> is a list of constant expressions.</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","max","max");?> determines which of a given set of constant expressions 
<span class="arg">expr</span> has maximum value. To do so, <?php linkTo("command","max","max");?> tries to increase the 
precision used for evaluation until it can decide the ordering or some 
maximum precision is reached. In the latter case, a warning is printed 
indicating that there might actually be another expression that has a 
greater value. 
</li><li>Even though <?php linkTo("command","max","max");?> determines the maximum expression by evaluation, it  
returns the expression that is maximum as is, i.e. as an expression 
tree that might be evaluated to any accuracy afterwards. 
</li><li><?php linkTo("command","max","max");?> can be given either an arbitrary number of constant 
expressions in argument or a list of constant expressions. The list 
however must not be end-elliptic. 
</li><li>Users should be aware that the behavior of <?php linkTo("command","max","max");?> follows the IEEE 
754-2008 standard with respect to NaNs. In particular, <?php linkTo("command","max","max");?> 
evaluates to NaN if and only if all arguments of <?php linkTo("command","max","max");?> are 
NaNs. This means that NaNs may disappear during computations. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; max(1,2,3,exp(5),log(0.25));<br> 
&nbsp;&nbsp;&nbsp;1.48413159102576603421115580040552279623487667593878e2<br> 
&nbsp;&nbsp;&nbsp;&gt; max(17);<br> 
&nbsp;&nbsp;&nbsp;17<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; l = [|1,2,3,exp(5),log(0.25)|];<br> 
&nbsp;&nbsp;&nbsp;&gt; max(l);<br> 
&nbsp;&nbsp;&nbsp;1.48413159102576603421115580040552279623487667593878e2<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; print(max(exp(17),sin(62)));<br> 
&nbsp;&nbsp;&nbsp;exp(17)<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 4: </h2> 
&nbsp;&nbsp;&nbsp;&gt; verbosity = 1!;<br> 
&nbsp;&nbsp;&nbsp;&gt; print(max(17 + log2(13)/log2(9),17 + log(13)/log(9)));<br> 
&nbsp;&nbsp;&nbsp;Warning: maximum computation relies on floating-point result that is faithfully evaluated and different faithful roundings toggle the result.<br> 
&nbsp;&nbsp;&nbsp;17 + log2(13) / log2(9)<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","min","min");?>, <?php linkTo("command","equal","==");?>, <?php linkTo("command","neq","!=");?>, <?php linkTo("command","ge","&gt;=");?>, <?php linkTo("command","gt","&gt;");?>, <?php linkTo("command","lt","&lt;");?>, <?php linkTo("command","le","&lt;=");?>, <?php linkTo("command","in","in");?>, <?php linkTo("command","inf","inf");?>, <?php linkTo("command","sup","sup");?> 
</div> 
