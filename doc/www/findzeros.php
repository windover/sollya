<a name="findzeros"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","findzeros","findzeros");?> 
<span class="smallDescription">gives a list of intervals containing all zeros of a function on an interval. 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","findzeros","findzeros");?>(<span class="arg">f</span>,<span class="arg">I</span>) : (<span class="type">function</span>, <span class="type">range</span>) -&gt; <span class="type">list</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">f</span> is a function.</li> 
<li><span class="arg">I</span> is an interval.</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","findzeros","findzeros");?>(<span class="arg">f</span>,<span class="arg">I</span>) returns a list of intervals <span class="arg">I1</span>, ... ,<span class="arg">In</span> such that, for  
every zero z of f, there exists some k such that z is in Ik. 
</li><li>The list may contain intervals <span class="arg">Ik</span> that do not contain any zero of <span class="arg">f</span>. 
An interval <span class="arg">Ik</span> may contain many zeros of <span class="arg">f</span>. 
</li><li>This command is meant for cases when safety is critical. If you want to be sure 
not to forget any zero, use <?php linkTo("command","findzeros","findzeros");?>. However, if you just want to know  
numerical values for the zeros of <span class="arg">f</span>, <?php linkTo("command","dirtyfindzeros","dirtyfindzeros");?> should be quite  
satisfactory and a lot faster. 
</li><li>If d denotes the value of global variable <?php linkTo("command","diam","diam");?>, the algorithm ensures 
that for each k, |Ik| &lt; d*|I|. 
</li><li>The algorithm used is basically a bisection algorithm. It is the same algorithm 
that the one used for <?php linkTo("command","infnorm","infnorm");?>. See the help page of this command for more  
details. In short, the behavior of the algorithm depends on global variables 
<?php linkTo("command","prec","prec");?>, <?php linkTo("command","diam","diam");?>, <?php linkTo("command","taylorrecursions","taylorrecursions");?> and <?php linkTo("command","hopitalrecursions","hopitalrecursions");?>. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; findzeros(sin(x),[-5;5]);<br> 
&nbsp;&nbsp;&nbsp;[|[-3.14208984375;-3.140869140625], [-1.220703125e-3;1.220703125e-3], [3.140869140625;3.14208984375]|]<br> 
&nbsp;&nbsp;&nbsp;&gt; diam=1e-10!;<br> 
&nbsp;&nbsp;&nbsp;&gt; findzeros(sin(x),[-5;5]);<br> 
&nbsp;&nbsp;&nbsp;[|[-3.14159265370108187198638916015625;-3.141592652536928653717041015625], [-1.16415321826934814453125e-9;1.16415321826934814453125e-9], [3.141592652536928653717041015625;3.14159265370108187198638916015625]|]<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","dirtyfindzeros","dirtyfindzeros");?>, <?php linkTo("command","infnorm","infnorm");?>, <?php linkTo("command","prec","prec");?>, <?php linkTo("command","diam","diam");?>, <?php linkTo("command","taylorrecursions","taylorrecursions");?>, <?php linkTo("command","hopitalrecursions","hopitalrecursions");?>, <?php linkTo("command","numberroots","numberroots");?> 
</div> 
