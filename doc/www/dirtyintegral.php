<a name="dirtyintegral"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","dirtyintegral","dirtyintegral");?> 
<span class="smallDescription">computes a numerical approximation of the integral of a function on an interval. 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","dirtyintegral","dirtyintegral");?>(<span class="arg">f</span>,<span class="arg">I</span>) : (<span class="type">function</span>, <span class="type">range</span>) -&gt; <span class="type">constant</span></span> 
 
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
<li><?php linkTo("command","dirtyintegral","dirtyintegral");?>(<span class="arg">f</span>,<span class="arg">I</span>) computes an approximation of the integral of <span class="arg">f</span> on <span class="arg">I</span>. 
</li><li>The interval must be bound. If the interval contains one of -Inf or +Inf, the  
result of <?php linkTo("command","dirtyintegral","dirtyintegral");?> is NaN, even if the integral has a meaning. 
</li><li>The result of this command depends on the global variables <?php linkTo("command","prec","prec");?> and <?php linkTo("command","points","points");?>. 
The method used is the trapezium rule applied at n evenly distributed 
points in the interval, where n is the value of global variable <?php linkTo("command","points","points");?>. 
</li><li>This command computes a numerical approximation of the exact value of the  
integral. It should not be used if safety is critical. In this case, use 
command <?php linkTo("command","integral","integral");?> instead. 
</li><li>Warning: this command is currently known to be unsatisfactory. If you really 
need to compute integrals, think of using an other tool or report a feature 
request to sylvain.chevillard@ens-lyon.org. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; sin(10);<br> 
&nbsp;&nbsp;&nbsp;-0.54402111088936981340474766185137728168364301291621<br> 
&nbsp;&nbsp;&nbsp;&gt; dirtyintegral(cos(x),[0;10]);<br> 
&nbsp;&nbsp;&nbsp;-0.54400304905152629822448058882475382036536298356281<br> 
&nbsp;&nbsp;&nbsp;&gt; points=2000!;<br> 
&nbsp;&nbsp;&nbsp;&gt; dirtyintegral(cos(x),[0;10]);<br> 
&nbsp;&nbsp;&nbsp;-0.54401997751158321972222697312583199035995837926892<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","prec","prec");?>, <?php linkTo("command","points","points");?>, <?php linkTo("command","integral","integral");?> 
</div> 
