<a name="taylorrecursions"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","taylorrecursions","taylorrecursions");?> 
<span class="smallDescription">controls the number of recursion steps when applying Taylor's rule. 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library names:</h2> 
<span class="commandline type">void sollya_lib_set_taylorrecursions_and_print(sollya_obj_t)</span> 
<span class="commandline type">void sollya_lib_set_taylorrecursions(sollya_obj_t)</span> 
<span class="commandline type">sollya_obj_t sollya_lib_get_taylorrecursions()</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","taylorrecursions","taylorrecursions");?> = <span class="arg">n</span> : <span class="type">integer</span> -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","taylorrecursions","taylorrecursions");?> = <span class="arg">n</span> ! : <span class="type">integer</span> -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","taylorrecursions","taylorrecursions");?> : <span class="type">integer</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">n</span> represents the number of recursions</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","taylorrecursions","taylorrecursions");?> is a global variable. Its value represents the number of steps 
of recursion that are used when applying Taylor's rule. This rule is applied 
by the interval evaluator present in the core of Sollya (and particularly 
visible in commands like <?php linkTo("command","infnorm","infnorm");?>). 
</li><li>To improve the quality of an interval evaluation of a function f, in  
particular when there are problems of decorrelation), the evaluator of Sollya 
uses Taylor's rule:  f([a,b]) C f(m) + [a-m, b-m]*f'([a,b]) where m=(a+b)/2. 
This rule can be applied recursively. 
The number of step in this recursion process is controlled by <?php linkTo("command","taylorrecursions","taylorrecursions");?>. 
</li><li>Setting <?php linkTo("command","taylorrecursions","taylorrecursions");?> to 0 makes Sollya use this rule only once; 
setting it to 1 makes Sollya use the rule twice, and so on. 
In particular: the rule is always applied at least once. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; f=exp(x);<br> 
&nbsp;&nbsp;&nbsp;&gt; p=remez(f,3,[0;1]);<br> 
&nbsp;&nbsp;&nbsp;&gt; taylorrecursions=0;<br> 
&nbsp;&nbsp;&nbsp;The number of recursions for Taylor evaluation has been set to 0.<br> 
&nbsp;&nbsp;&nbsp;&gt; evaluate(f-p, [0;1]);<br> 
&nbsp;&nbsp;&nbsp;[-0.46839364816268368775174657814112460243249079671039;0.46947781754646820647293019728402934746974652584671]<br> 
&nbsp;&nbsp;&nbsp;&gt; taylorrecursions=1;<br> 
&nbsp;&nbsp;&nbsp;The number of recursions for Taylor evaluation has been set to 1.<br> 
&nbsp;&nbsp;&nbsp;&gt; evaluate(f-p, [0;1]);<br> 
&nbsp;&nbsp;&nbsp;[-0.138131114954063839905475752120786856031651747712954;0.13921528433784835862665937126369160106890747684927]<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","hopitalrecursions","hopitalrecursions");?>, <?php linkTo("command","evaluate","evaluate");?>, <?php linkTo("command","infnorm","infnorm");?> 
</div> 
