<a name="numberroots"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","numberroots","numberroots");?> 
<span class="smallDescription">Computes the number of roots of a polynomial in a given range. 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","numberroots","numberroots");?>(<span class="arg">p</span>, <span class="arg">I</span>) : (<span class="type">function</span>, <span class="type">range</span>) -&gt; <span class="type">integer</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">p</span> is a polynomial.</li> 
<li><span class="arg">I</span> is an interval.</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","numberroots","numberroots");?> rigorously computes the number of roots of polynomial the p in 
the interval I. The technique used is Sturm's algorithm. The value returned 
is not just a numerical estimation of the number of roots of p in I: it is 
the exact number of roots. 
</li><li>The command <?php linkTo("command","findzeros","findzeros");?> computes safe enclosures of all the zeros of a 
function, without forgetting any, but it is not guaranteed to separate them 
all in distinct intervals. <?php linkTo("command","numberroots","numberroots");?> is more accurate since it guarantees  
the exact number of roots. However, it does not compute them. It may be used, 
for instance, to certify that <?php linkTo("command","findzeros","findzeros");?> did not put two distinct roots in  
the same interval. 
</li><li>Multiple roots are counted only once. 
</li><li>The interval I must be bounded. The algorithm cannot handle unbounded 
intervals. Moreover, the interval is considered as a closed interval: if one 
(or both) of the endpoints of I are roots of p, they are counted. 
</li><li>The argument p can be any expression, but if Sollya fails to prove that 
it is a polynomial an error is produced. Also, please note that if the 
coefficients of p or the endpoints of I are not exactly representable, 
they are first numerically evaluated, before the algorithm is used. In that 
case, the counted number of roots corresponds to the rounded polynomial on 
the rounded interval *and not* to the exact parameters given by the user. 
A warning is displayed to inform the user. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; numberroots(1+x-x^2, [1,2]);<br> 
&nbsp;&nbsp;&nbsp;1<br> 
&nbsp;&nbsp;&nbsp;&gt; findzeros(1+x-x^2, [1,2]);<br> 
&nbsp;&nbsp;&nbsp;[|[1.617919921875;1.6180419921875]|]<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; numberroots((1+x)*(1-x), [-1,1]);<br> 
&nbsp;&nbsp;&nbsp;2<br> 
&nbsp;&nbsp;&nbsp;&gt; numberroots(x^2, [-1,1]);<br> 
&nbsp;&nbsp;&nbsp;1<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; verbosity = 1!;<br> 
&nbsp;&nbsp;&nbsp;&gt; numberroots(x-pi, [0,4]);<br> 
&nbsp;&nbsp;&nbsp;Warning: the 0th coefficient of the polynomial is neither a floating point<br> 
&nbsp;&nbsp;&nbsp;constant nor can be evaluated without rounding to a floating point constant.<br> 
&nbsp;&nbsp;&nbsp;Will faithfully evaluate it with the current precision (165 bits) <br> 
&nbsp;&nbsp;&nbsp;1<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 4: </h2> 
&nbsp;&nbsp;&nbsp;&gt; verbosity = 1!;<br> 
&nbsp;&nbsp;&nbsp;&gt; numberroots(1+x-x^2, [0, @Inf@]);<br> 
&nbsp;&nbsp;&nbsp;Warning: the given interval must have finite bounds.<br> 
&nbsp;&nbsp;&nbsp;Warning: at least one of the given expressions or a subexpression is not correctly typed<br> 
&nbsp;&nbsp;&nbsp;or its evaluation has failed because of some error on a side-effect.<br> 
&nbsp;&nbsp;&nbsp;error<br> 
&nbsp;&nbsp;&nbsp;&gt; numberroots(exp(x), [0, 1]);<br> 
&nbsp;&nbsp;&nbsp;Warning: the given function must be a polynomial in this context.<br> 
&nbsp;&nbsp;&nbsp;Warning: at least one of the given expressions or a subexpression is not correctly typed<br> 
&nbsp;&nbsp;&nbsp;or its evaluation has failed because of some error on a side-effect.<br> 
&nbsp;&nbsp;&nbsp;error<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","dirtyfindzeros","dirtyfindzeros");?>, <?php linkTo("command","findzeros","findzeros");?> 
</div> 
