<a name="integral"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","integral","integral");?> 
<span class="smallDescription">computes an interval bounding the integral of a function on an interval. 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library name:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_integral(sollya_obj_t, sollya_obj_t)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","integral","integral");?>(<span class="arg">f</span>,<span class="arg">I</span>) : (<span class="type">function</span>, <span class="type">range</span>) -&gt; <span class="type">range</span></span> 
 
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
<li><?php linkTo("command","integral","integral");?>(<span class="arg">f</span>,<span class="arg">I</span>) returns an interval J such that the exact value of  
the integral of <span class="arg">f</span> on <span class="arg">I</span> lies in J. 
</li><li>This command is safe but very inefficient. Use <?php linkTo("command","dirtyintegral","dirtyintegral");?> if you just want 
an approximate value. 
</li><li>The result of this command depends on the global variable <?php linkTo("command","diam","diam");?>. 
The method used is the following: <span class="arg">I</span> is cut into intervals of length not  
greater then d*|I| where d is the value 
of global variable <?php linkTo("command","diam","diam");?>. 
On each small interval <span class="arg">J</span>, an evaluation of <span class="arg">f</span> by interval is 
performed. The result is multiplied by the length of <span class="arg">J</span>. Finally all values  
are summed. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; sin(10);<br> 
&nbsp;&nbsp;&nbsp;-0.54402111088936981340474766185137728168364301291621<br> 
&nbsp;&nbsp;&nbsp;&gt; integral(cos(x),[0;10]);<br> 
&nbsp;&nbsp;&nbsp;[-0.54710197983579690224097637163525943075698599257332;-0.54094015130013183848150540881373370744053741191728]<br> 
&nbsp;&nbsp;&nbsp;&gt; diam=1e-5!;<br> 
&nbsp;&nbsp;&nbsp;&gt; integral(cos(x),[0;10]);<br> 
&nbsp;&nbsp;&nbsp;[-0.54432915685955427101857780295936956775293876382777;-0.54371306401249969508039644221927489010425803173555]<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","diam","diam");?>, <?php linkTo("command","dirtyintegral","dirtyintegral");?>, <?php linkTo("command","prec","prec");?> 
</div> 
