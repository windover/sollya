<a name="supnorm"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","supnorm","supnorm");?> 
<span class="smallDescription">computes an interval bounding the supremum norm of an approximation error (absolute or relative) between a given polynomial and a function. 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library name:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_supnorm(sollya_obj_t, sollya_obj_t, sollya_obj_t, sollya_obj_t, sollya_obj_t)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","supnorm","supnorm");?>(<span class="arg">p</span>, <span class="arg">f</span>, <span class="arg">I</span>, <span class="arg">errorType</span>, <span class="arg">accuracy</span>) : (<span class="type">function</span>, <span class="type">function</span>, <span class="type">range</span>, <span class="type">absolute|relative</span>, <span class="type">constant</span>) -&gt; <span class="type">range</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">p</span> is a polynomial.</li> 
<li><span class="arg">f</span> is a function.</li> 
<li><span class="arg">I</span> is an interval.</li> 
<li><span class="arg">errorType</span> is the type of error to be considered: <?php linkTo("command","absolute","absolute");?> or <?php linkTo("command","relative","relative");?> (see details below).</li> 
<li><span class="arg">accuracy</span> is a constant that controls the relative tightness of the interval returned. </li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","supnorm","supnorm");?>(<span class="arg">p</span>, <span class="arg">f</span>, <span class="arg">I</span>, <span class="arg">errorType</span>, <span class="arg">accuracy</span>) tries to compute an 
interval bound r=[l,u] for the supremum norm of the error function 
epsilon_absolute=p-f (when <span class="arg">errorType</span> evaluates to <?php linkTo("command","absolute","absolute");?>) 
or epsilon_relative=p/f-1 (when <span class="arg">errorType</span> evaluates to <?php linkTo("command","relative","relative");?>), 
over the interval I, such that sup{|epsilon(x)|, x in I} C r 
and 0&lt;|u/l-1|&lt; <span class="arg">accuracy</span>. If <?php linkTo("command","supnorm","supnorm");?> succeeds in computing a suitable 
interval r, which it returns, that interval is guaranteed to contain the 
supremum norm value and to satisfy the required quality. Otherwise, <?php linkTo("command","supnorm","supnorm");?> 
evaluates to <?php linkTo("command","error","error");?>, displaying a corresponding error message. These failure 
cases are rare and basically happen only for functions which are too 
complicated. 
</li><li>Roughly speaking, <?php linkTo("command","supnorm","supnorm");?> is based on <?php linkTo("command","taylorform","taylorform");?> to obtain a higher 
degree polynomial approximation for <span class="arg">f</span>. This process is coupled with 
an a posteriori validation of a potential supremum norm upper bound.  
The validation is based on showing a certain polynomial the problem gets 
reduced to does not vanish. In cases when this process alone does not  
succeed, for instance because <?php linkTo("command","taylorform","taylorform");?> is unable to compute a  
sufficiently good approximation to <span class="arg">f</span>, <?php linkTo("command","supnorm","supnorm");?> falls back to 
bisecting the working interval until safe supremum norm bounds can be 
computed with the required accuracy or until the width of the 
subintervals becomes less than <?php linkTo("command","diam","diam");?> times the original interval <span class="arg">I</span>,  
in which case <?php linkTo("command","supnorm","supnorm");?> fails. 
</li><li>The algorithm used for <?php linkTo("command","supnorm","supnorm");?> is quite complex, which makes it impossible  
to explain it here in further detail.  
Please find a complete description in the following article:<br> 
  
   Sylvain Chevillard, John Harrison, Mioara Joldes, Christoph Lauter<br> 
   Efficient and accurate computation of upper bounds of approximation errors<br> 
   Journal of Theoretical Computer Science (TCS), 2010<br> 
   LIP Research Report number RR LIP2010-2<br> 
   http://prunel.ccsd.cnrs.fr/ensl-00445343/fr/<br> 
</li><li>In practical cases, <?php linkTo("command","supnorm","supnorm");?> should be able to automatically handle 
removable discontinuities that relative errors might have. This means 
that usually, if <span class="arg">f</span> vanishes at a point x0 in the interval 
considered, the approximation polynomial <span class="arg">p</span> is designed such that it 
also vanishes at the same point with a multiplicity large 
enough. Hence, although <span class="arg">f</span> vanishes, epsilon_relative=p/f-1 may be  
defined by continuous extension at such points x0, called  
removable discontinuities (see Example 3). 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; p = remez(exp(x), 5, [-1;1]);<br> 
&nbsp;&nbsp;&nbsp;&gt; midpointmode=on!;<br> 
&nbsp;&nbsp;&nbsp;&gt; supnorm(p, exp(x), [-1;1], absolute, 2^(-40));<br> 
&nbsp;&nbsp;&nbsp;0.452055210438~2/7~e-4<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; prec=200!;<br> 
&nbsp;&nbsp;&nbsp;&gt; midpointmode=on!;<br> 
&nbsp;&nbsp;&nbsp;&gt; d = [1;2];<br> 
&nbsp;&nbsp;&nbsp;&gt; f = exp(cos(x)^2 + 1);<br> 
&nbsp;&nbsp;&nbsp;&gt; p = remez(1,15,d,1/f,1e-40);<br> 
&nbsp;&nbsp;&nbsp;&gt; theta=1b-60;<br> 
&nbsp;&nbsp;&nbsp;&gt; prec=default!;<br> 
&nbsp;&nbsp;&nbsp;&gt; mode=relative;<br> 
&nbsp;&nbsp;&nbsp;&gt; supnorm(p,f,d,mode,theta);<br> 
&nbsp;&nbsp;&nbsp;0.30893006200251428~5/6~e-13<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; midpointmode=on!;<br> 
&nbsp;&nbsp;&nbsp;&gt; mode=relative;<br> 
&nbsp;&nbsp;&nbsp;&gt; theta=1b-135;<br> 
&nbsp;&nbsp;&nbsp;&gt; d = [-1b-2;1b-2];<br> 
&nbsp;&nbsp;&nbsp;&gt; f = expm1(x);<br> 
&nbsp;&nbsp;&nbsp;&gt; p = x * (1 +&nbsp;&nbsp;x * ( 2097145 * 2^(-22) + x * ( 349527 * 2^(-21) + x * (87609 * 2^(-21) + x * 4369 * 2^(-19))))); <br> 
&nbsp;&nbsp;&nbsp;&gt; theta=1b-40;<br> 
&nbsp;&nbsp;&nbsp;&gt; supnorm(p,f,d,mode,theta);<br> 
&nbsp;&nbsp;&nbsp;0.98349131972~2/3~e-7<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","dirtyinfnorm","dirtyinfnorm");?>, <?php linkTo("command","infnorm","infnorm");?>, <?php linkTo("command","checkinfnorm","checkinfnorm");?>, <?php linkTo("command","absolute","absolute");?>, <?php linkTo("command","relative","relative");?>, <?php linkTo("command","taylorform","taylorform");?>, <?php linkTo("command","autodiff","autodiff");?>, <?php linkTo("command","numberroots","numberroots");?>, <?php linkTo("command","diam","diam");?> 
</div> 
