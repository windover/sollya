<a name="hopitalrecursions"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","hopitalrecursions","hopitalrecursions");?> 
<span class="smallDescription">controls the number of recursion steps when applying L'Hopital's rule. 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","hopitalrecursions","hopitalrecursions");?> = <span class="arg">n</span> : <span class="type">integer</span> -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","hopitalrecursions","hopitalrecursions");?> = <span class="arg">n</span> ! : <span class="type">integer</span> -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","hopitalrecursions","hopitalrecursions");?> : <span class="type">integer</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">n</span> represents the number of recursions</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","hopitalrecursions","hopitalrecursions");?> is a global variable. Its value represents the number of steps of 
recursion that are tried when applying L'Hopital's rule. This rule is applied 
by the interval evaluator present in the core of Sollya (and particularly 
visible in commands like <?php linkTo("command","infnorm","infnorm");?>). 
</li><li>If an expression of the form f/g has to be evaluated by interval  
arithmetic on an interval I and if f and g have a common zero 
in I, a direct evaluation leads to NaN. 
Sollya implements a safe heuristic to avoid this, based on L'Hopital's rule: in  
such a case, it can be shown that (f/g)(I) C (f'/g')(I). Since 
the same problem may exist for f'/g', the rule is applied recursively. 
The number of step in this recursion process is controlled by <?php linkTo("command","hopitalrecursions","hopitalrecursions");?>. 
</li><li>Setting <?php linkTo("command","hopitalrecursions","hopitalrecursions");?> to 0 makes Sollya use this rule only once; 
setting it to 1 makes Sollya use the rule twice, and so on. 
In particular: the rule is always applied at least once, if necessary. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; hopitalrecursions=0;<br> 
&nbsp;&nbsp;&nbsp;The number of recursions for Hopital's rule has been set to 0.<br> 
&nbsp;&nbsp;&nbsp;&gt; evaluate(log(1+x)^2/x^2,[-1/2; 1]);<br> 
&nbsp;&nbsp;&nbsp;[-@Inf@;@Inf@]<br> 
&nbsp;&nbsp;&nbsp;&gt; hopitalrecursions=1;<br> 
&nbsp;&nbsp;&nbsp;The number of recursions for Hopital's rule has been set to 1.<br> 
&nbsp;&nbsp;&nbsp;&gt; evaluate(log(1+x)^2/x^2,[-1/2; 1]);<br> 
&nbsp;&nbsp;&nbsp;[-2.52258872223978123766892848583270627230200053744108;6.7725887222397812376689284858327062723020005374411]<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","taylorrecursions","taylorrecursions");?>, <?php linkTo("command","infnorm","infnorm");?>, <?php linkTo("command","findzeros","findzeros");?>, <?php linkTo("command","evaluate","evaluate");?> 
</div> 
