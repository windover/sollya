<a name="accurateinfnorm"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","accurateinfnorm","accurateinfnorm");?> 
<span class="smallDescription">computes a faithful rounding of the infinity norm of a function  
</span> 
</div> 
<div class="divLibraryName"> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","accurateinfnorm","accurateinfnorm");?>(<span class="arg">function</span>,<span class="arg">range</span>,<span class="arg">constant</span>) : (<span class="type">function</span>, <span class="type">range</span>, <span class="type">constant</span>) -&gt; <span class="type">constant</span></span> 
<span class="commandline"><?php linkTo("command","accurateinfnorm","accurateinfnorm");?>(<span class="arg">function</span>,<span class="arg">range</span>,<span class="arg">constant</span>,<span class="arg">exclusion range 1</span>,...,<span class="arg">exclusion range n</span>) : (<span class="type">function</span>, <span class="type">range</span>, <span class="type">constant</span>, <span class="type">range</span>, ..., <span class="type">range</span>) -&gt; <span class="type">constant</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">function</span> represents the function whose infinity norm is to be computed</li> 
<li><span class="arg">range</span> represents the infinity norm is to be considered on</li> 
<li><span class="arg">constant</span> represents the number of bits in the significant of the result</li> 
<li><span class="arg">exclusion range 1</span> through <span class="arg">exclusion range n</span> represent ranges to be excluded </li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>The command <?php linkTo("command","accurateinfnorm","accurateinfnorm");?> computes an upper bound to the infinity norm of 
function <span class="arg">function</span> in <span class="arg">range</span>. This upper bound is the least 
floating-point number greater than the value of the infinity norm that 
lies in the set of dyadic floating point numbers having <span class="arg">constant</span> 
significant mantissa bits. This means the value <?php linkTo("command","accurateinfnorm","accurateinfnorm");?> evaluates to 
is at the time an upper bound and a faithful rounding to <span class="arg">constant</span> 
bits of the infinity norm of function <span class="arg">function</span> on range <span class="arg">range</span>. 
<br><br> 
If given, the fourth and further arguments of the command <?php linkTo("command","accurateinfnorm","accurateinfnorm");?>, 
<span class="arg">exclusion range 1</span> through <span class="arg">exclusion range n</span> the infinity norm of 
the function <span class="arg">function</span> is not to be considered on. 
</li><li>The command <?php linkTo("command","accurateinfnorm","accurateinfnorm");?> is now considered DEPRECATED in Sollya. 
Users should be aware about the fact that the algorithm behind 
<?php linkTo("command","accurateinfnorm","accurateinfnorm");?> is highly inefficient and that other, better suited 
algorithms, such as <?php linkTo("command","supnorm","supnorm");?>, are available inside Sollya. As a 
matter of fact, while <?php linkTo("command","accurateinfnorm","accurateinfnorm");?> is maintained for compatibility reasons 
with legacy Sollya codes, users are advised to avoid using <?php linkTo("command","accurateinfnorm","accurateinfnorm");?> 
in new Sollya scripts and to replace it, where possible, by the 
<?php linkTo("command","supnorm","supnorm");?> command. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; p = remez(exp(x), 5, [-1;1]);<br> 
&nbsp;&nbsp;&nbsp;&gt; accurateinfnorm(p - exp(x), [-1;1], 20);<br> 
&nbsp;&nbsp;&nbsp;4.52055246569216251373291015625e-5<br> 
&nbsp;&nbsp;&nbsp;&gt; accurateinfnorm(p - exp(x), [-1;1], 30);<br> 
&nbsp;&nbsp;&nbsp;4.5205513970358879305422306060791015625e-5<br> 
&nbsp;&nbsp;&nbsp;&gt; accurateinfnorm(p - exp(x), [-1;1], 40);<br> 
&nbsp;&nbsp;&nbsp;4.520551396713923253400935209356248378753662109375e-5<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; p = remez(exp(x), 5, [-1;1]);<br> 
&nbsp;&nbsp;&nbsp;&gt; midpointmode = on!;<br> 
&nbsp;&nbsp;&nbsp;&gt; infnorm(p - exp(x), [-1;1]);<br> 
&nbsp;&nbsp;&nbsp;0.45205~5/7~e-4<br> 
&nbsp;&nbsp;&nbsp;&gt; accurateinfnorm(p - exp(x), [-1;1], 40);<br> 
&nbsp;&nbsp;&nbsp;4.520551396713923253400935209356248378753662109375e-5<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","infnorm","infnorm");?>, <?php linkTo("command","dirtyinfnorm","dirtyinfnorm");?>, <?php linkTo("command","supnorm","supnorm");?>, <?php linkTo("command","checkinfnorm","checkinfnorm");?>, <?php linkTo("command","remez","remez");?>, <?php linkTo("command","diam","diam");?> 
</div> 
