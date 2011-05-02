<a name="off"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","off","off");?> 
<span class="smallDescription">special value for certain global variables. 
</span> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","off","off");?> is a special value used to deactivate certain functionnalities 
of Sollya. 
</li><li>As any value it can be affected to a variable and stored in lists. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; canonical=on;<br> 
&nbsp;&nbsp;&nbsp;Canonical automatic printing output has been activated.<br> 
&nbsp;&nbsp;&nbsp;&gt; p=1+x+x^2;<br> 
&nbsp;&nbsp;&nbsp;&gt; mode=off;<br> 
&nbsp;&nbsp;&nbsp;&gt; p;<br> 
&nbsp;&nbsp;&nbsp;1 + x + x^2<br> 
&nbsp;&nbsp;&nbsp;&gt; canonical=mode;<br> 
&nbsp;&nbsp;&nbsp;Canonical automatic printing output has been deactivated.<br> 
&nbsp;&nbsp;&nbsp;&gt; p;<br> 
&nbsp;&nbsp;&nbsp;1 + x * (1 + x)<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","on","on");?>, <?php linkTo("command","autosimplify","autosimplify");?>, <?php linkTo("command","canonical","canonical");?>, <?php linkTo("command","timing","timing");?>, <?php linkTo("command","fullparentheses","fullparentheses");?>, <?php linkTo("command","midpointmode","midpointmode");?>, <?php linkTo("command","rationalmode","rationalmode");?>, <?php linkTo("command","roundingwarnings","roundingwarnings");?>, <?php linkTo("command","timing","timing");?>, <?php linkTo("command","dieonerrormode","dieonerrormode");?> 
</div> 
