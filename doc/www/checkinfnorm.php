<a name="checkinfnorm"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","checkinfnorm","checkinfnorm");?> 
<span class="smallDescription">checks whether the infinity norm of a function is bounded by a value 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","checkinfnorm","checkinfnorm");?>(<span class="arg">function</span>,<span class="arg">range</span>,<span class="arg">constant</span>) : (<span class="type">function</span>, <span class="type">range</span>, <span class="type">constant</span>) -&gt; <span class="type">boolean</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">function</span> represents the function whose infinity norm is to be checked</li> 
<li><span class="arg">range</span> represents the infinity norm is to be considered on</li> 
<li><span class="arg">constant</span> represents the upper bound the infinity norm is to be checked to</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>The command <?php linkTo("command","checkinfnorm","checkinfnorm");?> checks whether the infinity norm of the given 
function <span class="arg">function</span> in the range <span class="arg">range</span> can be proven (by Sollya) to 
be less than the given bound <span class="arg">bound</span>. This means, if <?php linkTo("command","checkinfnorm","checkinfnorm");?> 
evaluates to <?php linkTo("command","true","true");?>, the infinity norm has been proven (by Sollya's 
interval arithmetic) to be less than the bound. If <?php linkTo("command","checkinfnorm","checkinfnorm");?> evaluates 
to <?php linkTo("command","false","false");?>, there are two possibilities: either the bound is less than 
or equal to the infinity norm of the function or the bound is greater 
than the infinity norm but Sollya could not conclude using its 
internal interval arithmetic. 
<br><br> 
<?php linkTo("command","checkinfnorm","checkinfnorm");?> is sensitive to the global variable <?php linkTo("command","diam","diam");?>. The smaller <?php linkTo("command","diam","diam");?>, 
the more time Sollya will spend on the evaluation of <?php linkTo("command","checkinfnorm","checkinfnorm");?> in 
order to prove the bound before returning <?php linkTo("command","false","false");?> although the infinity 
norm is bounded by the bound. If <?php linkTo("command","diam","diam");?> is equal to 0, Sollya will 
eventually spend infinite time on instances where the given bound 
<span class="arg">bound</span> is less or equal to the infinity norm of the function 
<span class="arg">function</span> in range <span class="arg">range</span>. In contrast, with <?php linkTo("command","diam","diam");?> being zero, 
<?php linkTo("command","checkinfnorm","checkinfnorm");?> evaluates to <?php linkTo("command","true","true");?> iff the infinity norm of the function in 
the range is bounded by the given bound. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; checkinfnorm(sin(x),[0;1.75], 1);<br> 
&nbsp;&nbsp;&nbsp;true<br> 
&nbsp;&nbsp;&nbsp;&gt; checkinfnorm(sin(x),[0;1.75], 1/2); checkinfnorm(sin(x),[0;20/39],1/2);<br> 
&nbsp;&nbsp;&nbsp;false<br> 
&nbsp;&nbsp;&nbsp;true<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; p = remez(exp(x), 5, [-1;1]);<br> 
&nbsp;&nbsp;&nbsp;&gt; b = dirtyinfnorm(p - exp(x), [-1;1]);<br> 
&nbsp;&nbsp;&nbsp;&gt; checkinfnorm(p - exp(x), [-1;1], b);<br> 
&nbsp;&nbsp;&nbsp;false<br> 
&nbsp;&nbsp;&nbsp;&gt; b1 = round(b, 15, RU);<br> 
&nbsp;&nbsp;&nbsp;&gt; checkinfnorm(p - exp(x), [-1;1], b1);<br> 
&nbsp;&nbsp;&nbsp;true<br> 
&nbsp;&nbsp;&nbsp;&gt; b2 = round(b, 25, RU);<br> 
&nbsp;&nbsp;&nbsp;&gt; checkinfnorm(p - exp(x), [-1;1], b2);<br> 
&nbsp;&nbsp;&nbsp;false<br> 
&nbsp;&nbsp;&nbsp;&gt; diam = 1b-20!;<br> 
&nbsp;&nbsp;&nbsp;&gt; checkinfnorm(p - exp(x), [-1;1], b2);<br> 
&nbsp;&nbsp;&nbsp;true<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","infnorm","infnorm");?>, <?php linkTo("command","dirtyinfnorm","dirtyinfnorm");?>, <?php linkTo("command","supnorm","supnorm");?>, <?php linkTo("command","accurateinfnorm","accurateinfnorm");?>, <?php linkTo("command","remez","remez");?>, <?php linkTo("command","diam","diam");?> 
</div> 
