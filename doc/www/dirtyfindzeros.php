<a name="dirtyfindzeros"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","dirtyfindzeros","dirtyfindzeros");?> 
<span class="smallDescription">gives a list of numerical values listing the zeros of a function on an interval. 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","dirtyfindzeros","dirtyfindzeros");?>(<span class="arg">f</span>,<span class="arg">I</span>) : (<span class="type">function</span>, <span class="type">range</span>) -&gt; <span class="type">list</span></span> 
 
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
<li><?php linkTo("command","dirtyfindzeros","dirtyfindzeros");?>(<span class="arg">f</span>,<span class="arg">I</span>) returns a list containing some zeros of <span class="arg">f</span> in the 
interval <span class="arg">I</span>. The values in the list are numerical approximation of the exact 
zeros. The precision of these approximations is approximately the precision 
stored in <?php linkTo("command","prec","prec");?>. If <span class="arg">f</span> does not have two zeros very close to each other, it  
can be expected that all zeros are listed. However, some zeros may be 
forgotten. This command should be considered as a numerical algorithm and 
should not be used if safety is critical. 
</li><li>More precisely, the algorithm relies on global variables <?php linkTo("command","prec","prec");?> and <?php linkTo("command","points","points");?> and it performs the following steps:  
let n be the value of variable <?php linkTo("command","points","points");?> and t be the value 
of variable <?php linkTo("command","prec","prec");?>. 
<ul> 
<li> Evaluate |f| at n evenly distributed points in the interval I. 
     The working precision to be used is automatically chosen in order to ensure that the sign 
     is correct. 
</li><li> Whenever f changes its sign for two consecutive points, 
     find an approximation x of its zero with precision t using 
     Newton's algorithm. The number of steps in Newton's iteration depends on t: 
     the precision of the approximation is supposed to be doubled at each step. 
</li><li> Add this value to the list. 
</li></ul> 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; dirtyfindzeros(sin(x),[-5;5]);<br> 
&nbsp;&nbsp;&nbsp;[|-3.14159265358979323846264338327950288419716939937508, 0, 3.14159265358979323846264338327950288419716939937508|]<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; L1=dirtyfindzeros(x^2*sin(1/x),[0;1]);<br> 
&nbsp;&nbsp;&nbsp;&gt; points=1000!;<br> 
&nbsp;&nbsp;&nbsp;&gt; L2=dirtyfindzeros(x^2*sin(1/x),[0;1]);<br> 
&nbsp;&nbsp;&nbsp;&gt; length(L1); length(L2);<br> 
&nbsp;&nbsp;&nbsp;18<br> 
&nbsp;&nbsp;&nbsp;25<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","prec","prec");?>, <?php linkTo("command","points","points");?>, <?php linkTo("command","findzeros","findzeros");?>, <?php linkTo("command","dirtyinfnorm","dirtyinfnorm");?>, <?php linkTo("command","numberroots","numberroots");?> 
</div> 
