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
<li><span class="arg">L</span> is a list of integers or a list of functions and indicates the basis for the approximation of <span class="arg">f</span></li> 
<li><span class="arg">range</span> is the interval where the function must be approximated</li> 
<li><span class="arg">w</span> (optional) is a weight function. Default is 1.</li> 
<li><span class="arg">quality</span> (optional) is a parameter that controls the quality of the returned polynomial <span class="arg">p</span>, with respect to the exact minimax p*. Default is 1e-5.</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","remez","remez");?> computes an approximation of the function f with respect to 
the weight function w on the interval <span class="arg">range</span>. More precisely, it 
searches p such that ||p*w-f|| is 
(almost) minimal among all p of a certain form. The norm is 
the infinity norm, e.g. ||g|| = max {|g(x)|, x in <span class="arg">range</span>}. 
</li><li>If w=1 (the default case), it consists in searching the best 
polynomial approximation of f with respect to the absolute error. 
If f=1 and w is of the form 1/g, it consists in 
searching the best polynomial approximation of g with respect to the 
relative error. 
</li><li>If n is given, p is searched among the polynomials with degree not 
greater than n. 
If <span class="arg">L</span> is given and is a list of integers, p is searched as a linear 
combination of monomials X^k where k belongs to <span class="arg">L</span>. 
In the case when <span class="arg">L</span> is a list of integers, it may contain ellipses but cannot 
be end-elliptic. 
If <span class="arg">L</span> is given and is a list of functions g_k, p is searched as a 
linear combination of the g_k. In that case <span class="arg">L</span> cannot contain ellipses. 
It is the user responsability to check that the g_k are linearly independent 
over the interval <span class="arg">range</span>. Moreover, the functions w*g_k must be at least 
twice differentiable over <span class="arg">range</span>. If these conditions are not fulfilled, the 
algorithm might fail or even silently return a result as if it successfully 
found the minimax, though the returned p is not optimal. 
</li><li>The polynomial is obtained by a convergent iteration called Remez' 
algorithm (and an extension of this algorithm, due to Stiefel). 
The algorithm computes a sequence p1, ..., pk, ... 
such that ek = ||<span class="arg">pk*w-f</span>|| converges towards 
the optimal value e. The algorithm is stopped when the relative error 
between ek and e is less than <span class="arg">quality</span>. 
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
<div class="divExample"> 
<h2 class="category">Example 4: </h2> 
&nbsp;&nbsp;&nbsp;&gt; L = [|exp(x), sin(x), cos(x)-1, sin(x^3)|];<br> 
&nbsp;&nbsp;&nbsp;&gt; g = (2^x-1)/x;<br> 
&nbsp;&nbsp;&nbsp;&gt; p1 = remez(g, L, [-1/16;1/16]);<br> 
&nbsp;&nbsp;&nbsp;&gt; p2 = remez(g, 3, [-1/16;1/16]);<br> 
&nbsp;&nbsp;&nbsp;&gt; dirtyinfnorm(p1 - g, [-1/16;1/16]);<br> 
&nbsp;&nbsp;&nbsp;9.8841323805554845968308959691395564355375312205068e-8<br> 
&nbsp;&nbsp;&nbsp;&gt; dirtyinfnorm(p2 - g, [-1/16;1/16]);<br> 
&nbsp;&nbsp;&nbsp;2.5433780105975429703888838928671089431318650967714e-9<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","dirtyinfnorm","dirtyinfnorm");?>, <?php linkTo("command","infnorm","infnorm");?>, <?php linkTo("command","fpminimax","fpminimax");?>, <?php linkTo("command","guessdegree","guessdegree");?>, <?php linkTo("command","taylorform","taylorform");?>, <?php linkTo("command","taylor","taylor");?> 
</div> 
