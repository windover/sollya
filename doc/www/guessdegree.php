<a name="guessdegree"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","guessdegree","guessdegree");?> 
<span class="smallDescription">returns the minimal degree needed for a polynomial to approximate a function with a certain error on an interval. 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","guessdegree","guessdegree");?>(<span class="arg">f</span>,<span class="arg">I</span>,<span class="arg">eps</span>,<span class="arg">w</span>) : (<span class="type">function</span>, <span class="type">range</span>, <span class="type">constant</span>, <span class="type">function</span>) -&gt; <span class="type">range</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">f</span> is the function to be approximated.</li> 
<li><span class="arg">I</span> is the interval where the function must be approximated.</li> 
<li><span class="arg">eps</span> is the maximal acceptable error.</li> 
<li><span class="arg">w</span> (optional) is a weight function. Default is 1.</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","guessdegree","guessdegree");?> tries to find the minimal degree needed to approximate <span class="arg">f</span> 
on <span class="arg">I</span> by a polynomial with an error err=p*w-f whose infinity norm not greater than <span class="arg">eps</span>. 
More precisely, it finds n minimal such that there exists a 
polynomial p of degree n such that ||p*w-f|| &lt; eps. 
</li><li><?php linkTo("command","guessdegree","guessdegree");?> returns an interval: for common cases, this interval is reduced to a  
single number (e.g. the minimal degree). But in certain cases, <?php linkTo("command","guessdegree","guessdegree");?> does 
not succeed in finding the minimal degree. In such cases the returned interval 
is of the form [n,p] such that: 
<ul> 
<li> no polynomial of degree n-1 gives an error less than <span class="arg">eps</span>. 
</li><li> there exists a polynomial of degree p giving an error less than <span class="arg">eps</span>.  
</li></ul> 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; guessdegree(exp(x),[-1;1],1e-10);<br> 
&nbsp;&nbsp;&nbsp;[10;10]<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; guessdegree(1, [-1;1], 1e-8, 1/exp(x));<br> 
&nbsp;&nbsp;&nbsp;[8;9]<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","dirtyinfnorm","dirtyinfnorm");?>, <?php linkTo("command","remez","remez");?>, <?php linkTo("command","fpminimax","fpminimax");?>, <?php linkTo("command","degree","degree");?> 
</div> 
