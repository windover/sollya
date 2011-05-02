<a name="diam"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","diam","diam");?> 
<span class="smallDescription">parameter used in safe algorithms of Sollya and controlling the maximal length of the involved intervals. 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","diam","diam");?> = <span class="arg">width</span> : <span class="type">constant</span> -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","diam","diam");?> = <span class="arg">width</span> ! : <span class="type">constant</span> -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","diam","diam");?> : <span class="type">constant</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">width</span> represents the maximal relative width of the intervals used</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","diam","diam");?> is a global variable. Its value represents the maximal width allowed 
for intervals involved in safe algorithms of Sollya (namely <?php linkTo("command","infnorm","infnorm");?>, 
<?php linkTo("command","checkinfnorm","checkinfnorm");?>, <?php linkTo("command","accurateinfnorm","accurateinfnorm");?>, <?php linkTo("command","integral","integral");?>, <?php linkTo("command","findzeros","findzeros");?>, <?php linkTo("command","supnorm","supnorm");?>). 
</li><li>More precisely, <?php linkTo("command","diam","diam");?> is relative to the width of the input interval of 
the command. For instance, suppose that <?php linkTo("command","diam","diam");?>=1e-5: if <?php linkTo("command","infnorm","infnorm");?> is called 
on interval [0;1], the maximal width of an interval will be 1e-5. But if it 
is called on interval [0;1e-3], the maximal width will be 1e-8. 
</ul> 
</div> 
<div class="divExamples"> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","infnorm","infnorm");?>, <?php linkTo("command","checkinfnorm","checkinfnorm");?>, <?php linkTo("command","accurateinfnorm","accurateinfnorm");?>, <?php linkTo("command","integral","integral");?>, <?php linkTo("command","findzeros","findzeros");?>, <?php linkTo("command","supnorm","supnorm");?> 
</div> 
