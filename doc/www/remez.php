<a name="remez"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","remez","remez");?> 
<span class="smallDescription">computes the minimax of a function on an interval. 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library names:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_remez(sollya_obj_t, sollya_obj_t, sollya_obj_t, ...)</span> 
<span class="commandline type">sollya_obj_t sollya_lib_v_remez(sollya_obj_t, sollya_obj_t, sollya_obj_t,</span> 
<span class="commandline type">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;va_list)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","remez","remez");?>(<span class="arg">f</span>, <span class="arg">n</span>, <span class="arg">range</span>, <span class="arg">w</span>, <span class="arg">quality</span>, <span class="arg">bounds</span>) : (<span class="type">function</span>, <span class="type">integer</span>, <span class="type">range</span>, <span class="type">function</span>, <span class="type">constant</span>, <span class="type">range</span>) -&gt; <span class="type">function</span></span> 
<span class="commandline"><?php linkTo("command","remez","remez");?>(<span class="arg">f</span>, <span class="arg">L</span>, <span class="arg">range</span>, <span class="arg">w</span>, <span class="arg">quality</span>, <span class="arg">bounds</span>) : (<span class="type">function</span>, <span class="type">list</span>, <span class="type">range</span>, <span class="type">function</span>, <span class="type">constant</span>, <span class="type">range</span>) -&gt; <span class="type">function</span></span> 
 
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
<li><span class="arg">bounds</span> (optional) is a parameter that allows the user to make the algorithm stop earlier, whenever a given accuracy is reached or a given accuracy is proved unreachable. Default is [0, +Inf].</li> 
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
In the case when <span class="arg">L</span> is a list of integers, it may contain ellipses but 
cannot be end-elliptic. 
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
such that ek = ||pk*w-f|| converges towards 
the optimal value e. The algorithm is stopped when the relative error 
between ek and e is less than <span class="arg">quality</span>. 
</li><li>The optional argument <span class="arg">bounds</span> is an interval [satisfying_err, target_err] 
with the following behavior:<ul> 
  <li> if, during the algorithm, we manage to prove that target_err is 
    unreachable, we stop the algorithm returning the last computed 
    polynomial. 
  </li><li> if, during the algorithm, we obtain a polynomial with an error smaller 
    than satisfying_err, we stop the algorithm returning that polynomial. 
  </li><li> otherwise we loop until we find an optimal polynomial with the required 
    quality, as usual.</li></ul> 
Examples of use:<br> 
  [0, +Inf] (compute the optimal polynomial with the required quality)<br> 
  [target_err] (stops as soon as a polynomial achieving target_err is 
                obtained or as soon as such a polynomial is proved not to 
                exist).<br> 
  [0, target_err] (finds the optimal polynomial, but provided that its error 
                   is smaller than target_err).<br> 
  [satisfying_err, +Inf] (stops as soon as a polynomial achieving 
                          satisfying_err is obtained. If such a polynomial 
                          does not exist, returns the optimal polynomial). 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; p = remez(exp(x),5,[0;1]);<br> 
&nbsp;&nbsp;&nbsp;&gt; degree(p);<br> 
&nbsp;&nbsp;&nbsp;5<br> 
&nbsp;&nbsp;&nbsp;&gt; dirtyinfnorm(p-exp(x),[0;1]);<br> 
&nbsp;&nbsp;&nbsp;1.12956981510961487071711938292660776072226345893629e-6<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; p = remez(1,[|0,2,4,6,8|],[0,Pi/4],1/cos(x));<br> 
&nbsp;&nbsp;&nbsp;&gt; canonical=on!;<br> 
&nbsp;&nbsp;&nbsp;&gt; p;<br> 
&nbsp;&nbsp;&nbsp;0.99999999994393732180959690352543887130348096061124 + -0.499999995715568577687720530637215446709494672222587 * x^2 + 4.1666613233473633009941059480570275870113220089059e-2 * x^4 + -1.3886529147145693651355523880319714051047635695061e-3 * x^6 + 2.4372679177224179934800328511009205218114284220126e-5 * x^8<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; p1 = remez(exp(x),5,[0;1],default,1e-5);<br> 
&nbsp;&nbsp;&nbsp;&gt; p2 = remez(exp(x),5,[0;1],default,1e-10);<br> 
&nbsp;&nbsp;&nbsp;&gt; p3 = remez(exp(x),5,[0;1],default,1e-15);<br> 
&nbsp;&nbsp;&nbsp;&gt; dirtyinfnorm(p1-exp(x),[0;1]);<br> 
&nbsp;&nbsp;&nbsp;1.12956981510961487071711938292660776072226345893629e-6<br> 
&nbsp;&nbsp;&nbsp;&gt; dirtyinfnorm(p2-exp(x),[0;1]);<br> 
&nbsp;&nbsp;&nbsp;1.12956980227478675612619255125474525171079325793124e-6<br> 
&nbsp;&nbsp;&nbsp;&gt; dirtyinfnorm(p3-exp(x),[0;1]);<br> 
&nbsp;&nbsp;&nbsp;1.12956980227478675612619255125474525171079325793124e-6<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 4: </h2> 
&nbsp;&nbsp;&nbsp;&gt; L = [|exp(x), sin(x), cos(x)-1, sin(x^3)|];<br> 
&nbsp;&nbsp;&nbsp;&gt; g = (2^x-1)/x;<br> 
&nbsp;&nbsp;&nbsp;&gt; p1 = remez(g, L, [-1/16;1/16]);<br> 
&nbsp;&nbsp;&nbsp;&gt; p2 = remez(g, 3, [-1/16;1/16]);<br> 
&nbsp;&nbsp;&nbsp;&gt; dirtyinfnorm(p1 - g, [-1/16;1/16]);<br> 
&nbsp;&nbsp;&nbsp;9.8841323829271038137685646777951687620288462194745e-8<br> 
&nbsp;&nbsp;&nbsp;&gt; dirtyinfnorm(p2 - g, [-1/16;1/16]);<br> 
&nbsp;&nbsp;&nbsp;2.54337800593461418356437401152248866818783932027105e-9<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 5: </h2> 
&nbsp;&nbsp;&nbsp;&gt; f = sin(x);<br> 
&nbsp;&nbsp;&nbsp;&gt; I = [-3b-5;-1b-1074];<br> 
&nbsp;&nbsp;&nbsp;&gt; time(popt = remez(1, [|1, 3, 4, 5, 7, 8, 9|], I, 1/f));<br> 
&nbsp;&nbsp;&nbsp;0.58334899999999999991098786900067807437153533101081<br> 
&nbsp;&nbsp;&nbsp;&gt; time(p1 = remez(1, [|1, 3, 4, 5, 7, 8, 9|], I, 1/f, default, [0, 1b-73]));<br> 
&nbsp;&nbsp;&nbsp;0.359515999999999999957832341745955773149034939706326<br> 
&nbsp;&nbsp;&nbsp;&gt; time(p2 = remez(1, [|1, 3, 4, 5, 7, 8, 9|], I, 1/f, default, [3b-72, +@Inf@]));<br> 
&nbsp;&nbsp;&nbsp;0.455625000000000000052041704279304212832357734441757<br> 
&nbsp;&nbsp;&nbsp;&gt; dirtyinfnorm(popt/f-1, I);<br> 
&nbsp;&nbsp;&nbsp;2.06750931454112835098093903810531156576504665659064e-22<br> 
&nbsp;&nbsp;&nbsp;&gt; dirtyinfnorm(p1/f-1, I);<br> 
&nbsp;&nbsp;&nbsp;2.49711266837493110470637913808914046704452778960875e-22<br> 
&nbsp;&nbsp;&nbsp;&gt; dirtyinfnorm(p2/f-1, I);<br> 
&nbsp;&nbsp;&nbsp;5.4567247553615435246376977231253834265248756996947e-22<br> 
&nbsp;&nbsp;&nbsp;&gt; 1b-73;<br> 
&nbsp;&nbsp;&nbsp;1.05879118406787542383540312584955245256423950195312e-22<br> 
&nbsp;&nbsp;&nbsp;&gt; 3b-72;<br> 
&nbsp;&nbsp;&nbsp;6.3527471044072525430124187550973147153854370117187e-22<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","dirtyinfnorm","dirtyinfnorm");?>, <?php linkTo("command","infnorm","infnorm");?>, <?php linkTo("command","fpminimax","fpminimax");?>, <?php linkTo("command","guessdegree","guessdegree");?>, <?php linkTo("command","taylorform","taylorform");?>, <?php linkTo("command","taylor","taylor");?> 
</div> 
