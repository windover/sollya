<a name="infnorm"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","infnorm","infnorm");?> 
<span class="smallDescription">computes an interval bounding the infinity norm of a function on an interval. 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library names:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_infnorm(sollya_obj_t, sollya_obj_t, ...)</span> 
<span class="commandline type">sollya_obj_t sollya_lib_v_infnorm(sollya_obj_t, sollya_obj_t, va_list)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","infnorm","infnorm");?>(<span class="arg">f</span>,<span class="arg">I</span>,<span class="arg">filename</span>,<span class="arg">Ilist</span>) : (<span class="type">function</span>, <span class="type">range</span>, <span class="type">string</span>, <span class="type">list</span>) -&gt; <span class="type">range</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">f</span> is a function.</li> 
<li><span class="arg">I</span> is an interval.</li> 
<li><span class="arg">filename</span> (optional) is the name of the file into a proof will be saved.</li> 
<li><span class="arg">IList</span> (optional) is a list of intervals to be excluded.</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","infnorm","infnorm");?>(<span class="arg">f</span>,<span class="arg">range</span>) computes an interval bounding the infinity norm of the  
given function f on the interval I, e.g. computes an interval J 
such that max {|f(x)|, x in I} C J. 
</li><li>If <span class="arg">filename</span> is given, a proof in English will be produced (and stored in file 
called <span class="arg">filename</span>) proving that  max {|f(x)|, x in I} C J. 
</li><li>If a list <span class="arg">IList</span> of intervals <span class="arg">I1</span>, ... ,<span class="arg">In</span> is given, the infinity norm will 
be computed on I \ (I1 U ... U I2). 
</li><li>The function <span class="arg">f</span> is assumed to be at least twice continuous on <span class="arg">I</span>. More  
generally, if <span class="arg">f</span> is Ck, global variables <?php linkTo("command","hopitalrecursions","hopitalrecursions");?> and 
<?php linkTo("command","taylorrecursions","taylorrecursions");?> must have values not greater than k.   
</li><li>If the interval is reduced to a single point, the result of <?php linkTo("command","infnorm","infnorm");?> is an  
interval containing the exact absolute value of <span class="arg">f</span> at this point. 
</li><li>If the interval is not bound, the result will be [0, +Inf]  
which is correct but perfectly useless. <?php linkTo("command","infnorm","infnorm");?> is not meant to be used with  
infinite intervals. 
</li><li>The result of this command depends on the global variables <?php linkTo("command","prec","prec");?>, <?php linkTo("command","diam","diam");?>, 
<?php linkTo("command","taylorrecursions","taylorrecursions");?> and <?php linkTo("command","hopitalrecursions","hopitalrecursions");?>. The contribution of each variable is  
not easy even to analyse. 
<ul> 
<li> The algorithm uses interval arithmetic with precision <?php linkTo("command","prec","prec");?>. The 
     precision should thus be set high enough to ensure that no critical 
     cancellation will occur. 
</li><li> When an evaluation is performed on an interval [a,b], if the result 
     is considered being too large, the interval is split into [a,(a+b)/2] 
     and [(a+b)/2,b] and so on recursively. This recursion step 
     is  not performed if the (b-a) &lt; d*|I| where d is the value 
     of variable <?php linkTo("command","diam","diam");?>. In other words, <?php linkTo("command","diam","diam");?> controls the minimum length of an 
     interval during the algorithm. 
</li><li> To perform the evaluation of a function on an interval, Taylor's rule is 
     applied, e.g. f([a,b]) C f(m) + [a-m, b-m]*f'([a,b]) 
     where m=(a+b)/2. This rule is recursively applied n times 
     where n is the value of variable <?php linkTo("command","taylorrecursions","taylorrecursions");?>. Roughly speaking, 
     the evaluations will avoid decorrelation up to order n. 
</li><li> When a function of the form g/h has to be evaluated on an 
     interval [a,b] and when g and h vanish at a same point 
     z of the interval, the ratio may be defined even if the expression 
     g(z)/h(z)=0/0 does not make any sense. In this case, L'Hopital's rule 
     may be used and (g/h)([a,b]) C (g'/h')([a,b]). 
     Since the same can occur with the ratio g'/h', the rule is applied 
     recursively. The variable <?php linkTo("command","hopitalrecursions","hopitalrecursions");?> controls the number of  
     recursion steps. 
</li></ul> 
</li><li>The algorithm used for this command is quite complex to be explained here.  
Please find a complete description in the following article:<br> 
     S. Chevillard and C. Lauter<br> 
     A certified infinity norm for the implementation of elementary functions<br> 
     LIP Research Report number RR2007-26<br> 
     http://prunel.ccsd.cnrs.fr/ensl-00119810<br> 
</li><li>Users should be aware about the fact that the algorithm behind 
<?php linkTo("command","infnorm","infnorm");?> is inefficient in most cases and that other, better suited 
algorithms, such as <?php linkTo("command","supnorm","supnorm");?>, are available inside Sollya. As a 
matter of fact, while <?php linkTo("command","infnorm","infnorm");?> is maintained for compatibility reasons 
with legacy Sollya codes, users are advised to avoid using <?php linkTo("command","infnorm","infnorm");?> 
in new Sollya scripts and to replace it, where possible, by the 
<?php linkTo("command","supnorm","supnorm");?> command. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; infnorm(exp(x),[-2;3]);<br> 
&nbsp;&nbsp;&nbsp;[2.00855369231876677409285296545817178969879078385537e1;2.00855369231876677409285296545817178969879078385544e1]<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; infnorm(exp(x),[-2;3],"proof.txt");<br> 
&nbsp;&nbsp;&nbsp;[2.00855369231876677409285296545817178969879078385537e1;2.00855369231876677409285296545817178969879078385544e1]<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; infnorm(exp(x),[-2;3],[| [0;1], [2;2.5] |]);<br> 
&nbsp;&nbsp;&nbsp;[2.00855369231876677409285296545817178969879078385537e1;2.00855369231876677409285296545817178969879078385544e1]<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 4: </h2> 
&nbsp;&nbsp;&nbsp;&gt; infnorm(exp(x),[-2;3],"proof.txt", [| [0;1], [2;2.5] |]);<br> 
&nbsp;&nbsp;&nbsp;[2.00855369231876677409285296545817178969879078385537e1;2.00855369231876677409285296545817178969879078385544e1]<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 5: </h2> 
&nbsp;&nbsp;&nbsp;&gt; infnorm(exp(x),[1;1]);<br> 
&nbsp;&nbsp;&nbsp;[2.71828182845904523536028747135266249775724709369989;2.71828182845904523536028747135266249775724709369998]<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 6: </h2> 
&nbsp;&nbsp;&nbsp;&gt; infnorm(exp(x), [log(0);log(1)]);<br> 
&nbsp;&nbsp;&nbsp;[0;@Inf@]<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","prec","prec");?>, <?php linkTo("command","diam","diam");?>, <?php linkTo("command","hopitalrecursions","hopitalrecursions");?>, <?php linkTo("command","taylorrecursions","taylorrecursions");?>, <?php linkTo("command","dirtyinfnorm","dirtyinfnorm");?>, <?php linkTo("command","checkinfnorm","checkinfnorm");?>, <?php linkTo("command","supnorm","supnorm");?>, <?php linkTo("command","findzeros","findzeros");?>, <?php linkTo("command","diff","diff");?>, <?php linkTo("command","taylorrecursions","taylorrecursions");?>, <?php linkTo("command","autodiff","autodiff");?>, <?php linkTo("command","numberroots","numberroots");?>, <?php linkTo("command","taylorform","taylorform");?> 
</div> 
