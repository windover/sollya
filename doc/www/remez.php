<a name="remez"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","remez","remez");?> 
<span class="smallDescription">computes the minimax of a function on an interval. 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","remez","remez");?>(<span class="arg">f</span>, <span class="arg">n</span>, <span class="arg">range</span>, <span class="arg">w</span>, <span class="arg">quality</span>) : (<span class="type">function</span>, <span class="type">integer</span>, <span class="type">range</span>, <span class="type">function</span>, <span class="type">constant</span>) -&gt; <span class="type">function</span></span> 
<span class="commandline"><?php linkTo("command","remez","remez");?>(<span class="arg">f</span>, <span class="arg">L</span>, <span class="arg">range</span>, <span class="arg">w</span>, <span class="arg">quality</span>) : (<span class="type">function</span>, <span class="type">list</span>, <span class="type">range</span>, <span class="type">function</span>, <span class="type">constant</span>) -&gt; <span class="type">function</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">f</span> is the function to be approximated</li> 
<li><span class="arg">n</span> is the degree of the polynomial that must approximate <span class="arg">f</span></li> 
<li><span class="arg">L</span> is a list of monomials that can be used to represent the polynomial that must approximate <span class="arg">f</span></li> 
<li><span class="arg">range</span> is the interval where the function must be approximated</li> 
<li><span class="arg">w</span> (optional) is a weight function. Default is 1.</li> 
<li><span class="arg">quality</span> (optional) is a parameter that controls the quality of the returned polynomial <span class="arg">p</span>, with respect to the exact minimax p*. Default is 1e-5.</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","remez","remez");?> computes an approximation of the function f with respect to  
the weight function w on the interval <span class="arg">range</span>. More precisely, it  
searches a polynomial p such that ||p*w-f|| is  
(almost) minimal among all polynomials p of a certain form. The norm is 
the infinity norm, e.g. ||g|| = max {|g(x)|, x in <span class="arg">range</span>}. 
</li><li>If w=1 (the default case), it consists in searching the best  
polynomial approximation of f with respect to the absolute error. 
If f=1 and w is of the form 1/g, it consists in  
searching the best polynomial approximation of g with respect to the  
relative error. 
</li><li>If n is given, the polynomial p is searched among the  
polynomials with degree not greater than n. 
If <span class="arg">L</span> is given, the polynomial p is searched as a linear combination  
of monomials X^k where k belongs to <span class="arg">L</span>. 
<span class="arg">L</span> may contain ellipses but cannot be end-elliptic. 
</li><li>The polynomial is obtained by a convergent iteration called Remez' algorithm.  
The algorithm computes a sequence p1, ..., pk, ...  
such that ek = ||<span class="arg">pk*w-f</span>|| converges towards  
the optimal value e. The algorithm is stopped when the relative error  
between ek and e is less than <span class="arg">quality</span>. 
</li><li>Note: the algorithm may not converge in certain cases. Moreover, it may  
converge towards a polynomial that is not optimal. These cases correspond to  
the cases when the Haar condition is not fulfilled. 
See [Cheney - Approximation theory] for details. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; p = remez(exp(x),5,[0;1]);<br> 
&nbsp;&nbsp;&nbsp;&gt; degree(p);<br> 
&nbsp;&nbsp;&nbsp;5<br> 
&nbsp;&nbsp;&nbsp;&gt; dirtyinfnorm(p-exp(x),[0;1]);<br> 
&nbsp;&nbsp;&nbsp;1.12956984638214536849843017679626063762687501534126e-6<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; p = remez(1,[|0,2,4,6,8|],[0,Pi/4],1/cos(x));<br> 
&nbsp;&nbsp;&nbsp;&gt; canonical=on!;<br> 
&nbsp;&nbsp;&nbsp;&gt; p;<br> 
&nbsp;&nbsp;&nbsp;0.99999999994393749280444571988532724907643631727381 + -0.49999999571557467737204931630836834563663039748203 * x^2 + 4.16666132335010905188253972212748718651775241902969e-2 * x^4 + -1.38865291475286141707180658383176799662601691348739e-3 * x^6 + 2.437267919111162694221738667927916761689966804242e-5 * x^8<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; p1 = remez(exp(x),5,[0;1],default,1e-5);<br> 
&nbsp;&nbsp;&nbsp;&gt; p2 = remez(exp(x),5,[0;1],default,1e-10);<br> 
&nbsp;&nbsp;&nbsp;&gt; p3 = remez(exp(x),5,[0;1],default,1e-15);<br> 
&nbsp;&nbsp;&nbsp;&gt; dirtyinfnorm(p1-exp(x),[0;1]);<br> 
&nbsp;&nbsp;&nbsp;1.12956984638214536849843017679626063762687501534126e-6<br> 
&nbsp;&nbsp;&nbsp;&gt; dirtyinfnorm(p2-exp(x),[0;1]);<br> 
&nbsp;&nbsp;&nbsp;1.12956980227478687332174207517728389861926659249056e-6<br> 
&nbsp;&nbsp;&nbsp;&gt; dirtyinfnorm(p3-exp(x),[0;1]);<br> 
&nbsp;&nbsp;&nbsp;1.12956980227478687332174207517728389861926659249056e-6<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","dirtyinfnorm","dirtyinfnorm");?>, <?php linkTo("command","infnorm","infnorm");?>, <?php linkTo("command","fpminimax","fpminimax");?>, <?php linkTo("command","guessdegree","guessdegree");?>, <?php linkTo("command","taylorform","taylorform");?>, <?php linkTo("command","taylor","taylor");?> 
</div> 
