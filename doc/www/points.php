<a name="points"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","points","points");?> 
<span class="smallDescription">controls the number of points chosen by Sollya in certain commands. 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library names:</h2> 
<span class="commandline type">void sollya_lib_set_points_and_print(sollya_obj_t)</span> 
<span class="commandline type">void sollya_lib_set_points(sollya_obj_t)</span> 
<span class="commandline type">sollya_obj_t sollya_lib_get_points()</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","points","points");?> = <span class="arg">n</span> : <span class="type">integer</span> -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","points","points");?> = <span class="arg">n</span> ! : <span class="type">integer</span> -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","points","points");?> : <span class="type">constant</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">n</span> represents the number of points</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","points","points");?> is a global variable. Its value represents the number of points 
used in numerical algorithms of Sollya (namely <?php linkTo("command","dirtyinfnorm","dirtyinfnorm");?>, 
<?php linkTo("command","dirtyintegral","dirtyintegral");?>, <?php linkTo("command","dirtyfindzeros","dirtyfindzeros");?>, <?php linkTo("command","plot","plot");?>). 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; f=x^2*sin(1/x);<br> 
&nbsp;&nbsp;&nbsp;&gt; points=10;<br> 
&nbsp;&nbsp;&nbsp;The number of points has been set to 10.<br> 
&nbsp;&nbsp;&nbsp;&gt; dirtyfindzeros(f, [0;1]);<br> 
&nbsp;&nbsp;&nbsp;[|0, 0.318309886183790671537767526745028724068919291480918|]<br> 
&nbsp;&nbsp;&nbsp;&gt; points=100;<br> 
&nbsp;&nbsp;&nbsp;The number of points has been set to 100.<br> 
&nbsp;&nbsp;&nbsp;&gt; dirtyfindzeros(f, [0;1]);<br> 
&nbsp;&nbsp;&nbsp;[|0, 2.4485375860291590118289809749617594159147637806224e-2, 3.97887357729738339422209408431285905086149114351147e-2, 4.54728408833986673625382181064326748669884702115589e-2, 5.3051647697298445256294587790838120678153215246819e-2, 6.3661977236758134307553505349005744813783858296183e-2, 7.9577471545947667884441881686257181017229822870229e-2, 0.106103295394596890512589175581676241356306430493638, 0.159154943091895335768883763372514362034459645740459, 0.318309886183790671537767526745028724068919291480918|]<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","dirtyinfnorm","dirtyinfnorm");?>, <?php linkTo("command","dirtyintegral","dirtyintegral");?>, <?php linkTo("command","dirtyfindzeros","dirtyfindzeros");?>, <?php linkTo("command","plot","plot");?>, <?php linkTo("command","diam","diam");?>, <?php linkTo("command","prec","prec");?> 
</div> 
