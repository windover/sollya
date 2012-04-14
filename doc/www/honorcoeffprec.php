<a name="honorcoeffprec"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","honorcoeffprec","honorcoeffprec");?> 
<span class="smallDescription">indicates the (forced) honoring the precision of the coefficients in <?php linkTo("command","implementpoly","implementpoly");?> 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library names:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_honorcoeffprec()</span> 
<span class="commandline type">int sollya_lib_is_honorcoeffprec(sollya_obj_t)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","honorcoeffprec","honorcoeffprec");?> : <span class="type">honorcoeffprec</span></span> 
 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>Used with command <?php linkTo("command","implementpoly","implementpoly");?>, <?php linkTo("command","honorcoeffprec","honorcoeffprec");?> makes <?php linkTo("command","implementpoly","implementpoly");?> honor 
the precision of the given polynomial. This means if a coefficient 
needs a double-double or a triple-double to be exactly stored, 
<?php linkTo("command","implementpoly","implementpoly");?> will allocate appropriate space and use a double-double 
or triple-double operation even if the automatic (heuristic) 
determination implemented in command <?php linkTo("command","implementpoly","implementpoly");?> indicates that the 
coefficient could be stored on less precision or, respectively, the 
operation could be performed with less precision. See <?php linkTo("command","implementpoly","implementpoly");?> 
for details. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; verbosity = 1!;<br> 
&nbsp;&nbsp;&nbsp;&gt; q = implementpoly(1 - simplify(TD(1/6)) * x^2,[-1b-10;1b-10],1b-60,DD,"p","implementation.c");<br> 
&nbsp;&nbsp;&nbsp;Warning: at least one of the coefficients of the given polynomial has been rounded in a way<br> 
&nbsp;&nbsp;&nbsp;that the target precision can be achieved at lower cost. Nevertheless, the implemented polynomial<br> 
&nbsp;&nbsp;&nbsp;is different from the given one.<br> 
&nbsp;&nbsp;&nbsp;&gt; printexpansion(q);<br> 
&nbsp;&nbsp;&nbsp;0x3ff0000000000000 + x^2 * 0xbfc5555555555555<br> 
&nbsp;&nbsp;&nbsp;&gt; r = implementpoly(1 - simplify(TD(1/6)) * x^2,[-1b-10;1b-10],1b-60,DD,"p","implementation.c",honorcoeffprec);<br> 
&nbsp;&nbsp;&nbsp;Warning: the infered precision of the 2th coefficient of the polynomial is greater than<br> 
&nbsp;&nbsp;&nbsp;the necessary precision computed for this step. This may make the automatic determination<br> 
&nbsp;&nbsp;&nbsp;of precisions useless.<br> 
&nbsp;&nbsp;&nbsp;&gt; printexpansion(r);<br> 
&nbsp;&nbsp;&nbsp;0x3ff0000000000000 + x^2 * (0xbfc5555555555555 + 0xbc65555555555555 + 0xb905555555555555)<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","implementpoly","implementpoly");?>, <?php linkTo("command","printexpansion","printexpansion");?>, <?php linkTo("command","fpminimax","fpminimax");?> 
</div> 
