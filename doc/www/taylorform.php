<a name="taylorform"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","taylorform","taylorform");?> 
<span class="smallDescription">computes a rigorous polynomial approximation (polynomial, interval error bound) for a function, based on Taylor expansions. 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library names:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_taylorform(sollya_obj_t, sollya_obj_t, sollya_obj_t, ...)</span> 
<span class="commandline type">sollya_obj_t sollya_lib_v_taylorform(sollya_obj_t, sollya_obj_t, sollya_obj_t, va_list)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","taylorform","taylorform");?>(<span class="arg">f</span>, <span class="arg">n</span>, <span class="arg">x0</span>, <span class="arg">I</span>, <span class="arg">errorType</span>) : (<span class="type">function</span>, <span class="type">integer</span>, <span class="type">constant</span>, <span class="type">range</span>, <span class="type">absolute|relative</span>) -&gt; <span class="type">list</span></span> 
<span class="commandline"><?php linkTo("command","taylorform","taylorform");?>(<span class="arg">f</span>, <span class="arg">n</span>, <span class="arg">x0</span>, <span class="arg">I</span>, <span class="arg">errorType</span>) : (<span class="type">function</span>, <span class="type">integer</span>, <span class="type">range</span>, <span class="type">range</span>, <span class="type">absolute|relative</span>) -&gt; <span class="type">list</span></span> 
<span class="commandline"><?php linkTo("command","taylorform","taylorform");?>(<span class="arg">f</span>, <span class="arg">n</span>, <span class="arg">x0</span>, <span class="arg">errorType</span>) : (<span class="type">function</span>, <span class="type">integer</span>, <span class="type">constant</span>, <span class="type">absolute|relative</span>) -&gt; <span class="type">list</span></span> 
<span class="commandline"><?php linkTo("command","taylorform","taylorform");?>(<span class="arg">f</span>, <span class="arg">n</span>, <span class="arg">x0</span>, <span class="arg">errorType</span>) : (<span class="type">function</span>, <span class="type">integer</span>, <span class="type">range</span>, <span class="type">absolute|relative</span>) -&gt; <span class="type">list</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">f</span> is the function to be approximated.</li> 
<li><span class="arg">n</span> is the degree of the polynomial that must approximate <span class="arg">f</span>.</li> 
<li><span class="arg">x0</span> is the point (it can be a real number or an interval) where the Taylor exansion of the function is to be considered.</li> 
<li><span class="arg">I</span> is the interval over which the function is to be approximated. If this parameter is omitted, the behavior is changed (see detailed description below).</li> 
<li><span class="arg">errorType</span> (optional) is the type of error to be considered. See the detailed description below. Default is <?php linkTo("command","absolute","absolute");?>.</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","taylorform","taylorform");?> computes an approximation polynomial and an interval error bound 
for function f. More precisely, it returns a list L=[p, coeffErrors, Delta] 
where: 
<ul> 
<li> p is an approximation polynomial of degree n which is roughly speaking 
a numerical Taylor expansion of f at the point x0. 
</li><li> coeffsErrors is a list of n+1 intervals. Each interval coeffsErrors[i] 
contains an enclosure of all the errors accumulated when computing the i-th 
coefficient of p. 
</li><li> Delta is an interval that provides a bound for the approximation error 
between p and f. Its significance depends on the <span class="arg">errorType</span> considered. 
</li></ul> 
</li><li>The polynomial p and the bound  Delta are obtained using Taylor Models 
principles. 
</li><li>Please note that x0 can be an interval. In general, it is meant to be a 
small interval approximating a non representable value. If x0 is given as a 
constant expression, it is first numerically evaluated (leading to a faithful 
rounding xapprox0 at precision <?php linkTo("command","prec","prec");?>), and it is then replaced by the (exactly 
representable) point-interval [xapprox0, xapprox0]. In particular, it is not 
the same to call <?php linkTo("command","taylorform","taylorform");?> with x0 = pi and with x0 = [pi], for instance. 
In general, if the point around which one desires to compute the polynomial 
is not exactly representable, one should preferably use a small interval 
for x0. 
</li><li>More formally, the mathematical property ensured by the algorithm may be 
stated as follows. For all xi0 in x0, there exist (small) values 
eps[i] in coeffsErrors[i] such that: 
<br> 
If <span class="arg">errorType</span> is <?php linkTo("command","absolute","absolute");?>, for all x in I, there exists delta in Delta such 
that f(x) - p(x-xi0) = sum{i=0...n} eps[i]*(x-xi0)^i + delta. 
<br> 
If <span class="arg">errorType</span> is <?php linkTo("command","relative","relative");?>, for all x in I, there exists delta in Delta such 
that f(x) - p(x-xi0) = sum{i=0...n} eps[i]*(x-xi0)^i + delta*(x-xi0)^(n+1). 
</li><li>It is also possible to use a large interval for x0, though it is not 
obvious to give an intuitive sense to the result of <?php linkTo("command","taylorform","taylorform");?> in that case. 
A particular case that might be interesting is when x0=I in relative mode. 
In that case, denoting by p_i the coefficient of p of order i, the interval 
p_i + coeffsError[i] gives an enclosure of f^(i)(I)/i!. 
However, the command <?php linkTo("command","autodiff","autodiff");?> is more convenient for computing such 
enclosures. 
</li><li>When the interval I is not given, the approximated Taylor polynomial is 
computed but no remainder is produced. In that case the returned list 
is L=[p, coeffErrors]. 
</li><li>The relative case is especially useful when functions with removable 
singularities are considered. In such a case, this routine is able to compute 
a finite remainder bound, provided that the expansion point given is the 
problematic removable singularity point. 
</li><li>The algorithm does not guarantee that by increasing the degree of the 
approximation, the remainder bound will become smaller. Moreover, it may  
even become larger due to the dependecy phenomenon present with interval 
arithmetic. In order to reduce this phenomenon, a possible solution is to 
split the definition domain I into several smaller intervals.  
</li><li>The command <?php linkTo("command","taylor","taylor");?> also computes a Taylor polynomial of a function. However 
it does not provide a bound on the remainder. Besides, <?php linkTo("command","taylor","taylor");?> is a somehow 
symbolic command: each coefficient of the Taylor polynomial is computed 
exactly and returned as an expression tree exactly equal to theoretical 
value. It is henceforth much more inefficient than <?php linkTo("command","taylorform","taylorform");?> and <?php linkTo("command","taylorform","taylorform");?> 
should be prefered if only numercial (yet safe) computations are required. 
The same difference exists between commands <?php linkTo("command","diff","diff");?> and <?php linkTo("command","autodiff","autodiff");?>. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; TL=taylorform(sin(x)/x, 10, 0, [-1,1], relative);<br> 
&nbsp;&nbsp;&nbsp;&gt; p=TL[0];<br> 
&nbsp;&nbsp;&nbsp;&gt; Delta=TL[2];<br> 
&nbsp;&nbsp;&nbsp;&gt; errors=TL[1];<br> 
&nbsp;&nbsp;&nbsp;&gt; for epsi in errors do epsi;<br> 
&nbsp;&nbsp;&nbsp;[0;0]<br> 
&nbsp;&nbsp;&nbsp;[0;0]<br> 
&nbsp;&nbsp;&nbsp;[0;5.3455294201843912922810729343029637576303937602101e-51]<br> 
&nbsp;&nbsp;&nbsp;[0;0]<br> 
&nbsp;&nbsp;&nbsp;[-3.3409558876152445576756705839393523485189961001313e-52;3.3409558876152445576756705839393523485189961001313e-52]<br> 
&nbsp;&nbsp;&nbsp;[0;0]<br> 
&nbsp;&nbsp;&nbsp;[-1.04404871487976392427364705748104760891218628129103e-53;1.04404871487976392427364705748104760891218628129103e-53]<br> 
&nbsp;&nbsp;&nbsp;[0;0]<br> 
&nbsp;&nbsp;&nbsp;[-1.63132611699963113167757352731413688892529106451724e-55;1.63132611699963113167757352731413688892529106451724e-55]<br> 
&nbsp;&nbsp;&nbsp;[0;0]<br> 
&nbsp;&nbsp;&nbsp;[-1.91171029335894273243465647732125416670932546623114e-57;1.91171029335894273243465647732125416670932546623114e-57]<br> 
&nbsp;&nbsp;&nbsp;&gt; p; Delta;<br> 
&nbsp;&nbsp;&nbsp;1 + x^2 * (-0.16666666666666666666666666666666666666666666666667 + x^2 * (8.3333333333333333333333333333333333333333333333333e-3 + x^2 * (-1.98412698412698412698412698412698412698412698412698e-4 + x^2 * (2.75573192239858906525573192239858906525573192239859e-6 + x^2 * (-2.50521083854417187750521083854417187750521083854419e-8)))))<br> 
&nbsp;&nbsp;&nbsp;[-1.6135797443886066084999806203254010793747502812764e-10;1.6135797443886066084999806203254010793747502812764e-10]<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; TL=taylorform(exp(x), 10, 0, [-1,1], absolute);<br> 
&nbsp;&nbsp;&nbsp;&gt; p=TL[0];<br> 
&nbsp;&nbsp;&nbsp;&gt; Delta=TL[2];<br> 
&nbsp;&nbsp;&nbsp;&gt; p; Delta;<br> 
&nbsp;&nbsp;&nbsp;1 + x * (1 + x * (0.5 + x * (0.16666666666666666666666666666666666666666666666667 + x * (4.1666666666666666666666666666666666666666666666667e-2 + x * (8.3333333333333333333333333333333333333333333333333e-3 + x * (1.38888888888888888888888888888888888888888888888889e-3 + x * (1.98412698412698412698412698412698412698412698412698e-4 + x * (2.4801587301587301587301587301587301587301587301587e-5 + x * (2.75573192239858906525573192239858906525573192239859e-6 + x * 2.7557319223985890652557319223985890652557319223986e-7)))))))))<br> 
&nbsp;&nbsp;&nbsp;[-2.31142719641187619441242534182684745832539555102969e-8;2.7312660755642474420206278018039434042553645532164e-8]<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; TL1 = taylorform(exp(x), 10, log2(10), [-1,1], absolute);<br> 
&nbsp;&nbsp;&nbsp;&gt; TL2 = taylorform(exp(x), 10, [log2(10)], [-1,1], absolute);<br> 
&nbsp;&nbsp;&nbsp;&gt; TL1==TL2;<br> 
&nbsp;&nbsp;&nbsp;false<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 4: </h2> 
&nbsp;&nbsp;&nbsp;&gt; TL1 = taylorform(exp(x), 3, 0, [0,1], relative);<br> 
&nbsp;&nbsp;&nbsp;&gt; TL2 = taylorform(exp(x), 3, 0, relative);<br> 
&nbsp;&nbsp;&nbsp;&gt; TL1[0]==TL2[0];<br> 
&nbsp;&nbsp;&nbsp;true<br> 
&nbsp;&nbsp;&nbsp;&gt; TL1[1]==TL2[1];<br> 
&nbsp;&nbsp;&nbsp;true<br> 
&nbsp;&nbsp;&nbsp;&gt; length(TL1);<br> 
&nbsp;&nbsp;&nbsp;3<br> 
&nbsp;&nbsp;&nbsp;&gt; length(TL2);<br> 
&nbsp;&nbsp;&nbsp;2<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 5: </h2> 
&nbsp;&nbsp;&nbsp;&gt; f = exp(cos(x)); x0 = 0;<br> 
&nbsp;&nbsp;&nbsp;&gt; TL = taylorform(f, 3, x0);<br> 
&nbsp;&nbsp;&nbsp;&gt; T1 = TL[0];<br> 
&nbsp;&nbsp;&nbsp;&gt; T2 = taylor(f, 3, x0);<br> 
&nbsp;&nbsp;&nbsp;&gt; print(coeff(T1, 2));<br> 
&nbsp;&nbsp;&nbsp;-1.35914091422952261768014373567633124887862354684999<br> 
&nbsp;&nbsp;&nbsp;&gt; print(coeff(T2, 2));<br> 
&nbsp;&nbsp;&nbsp;0.5 * exp(1)<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","diff","diff");?>, <?php linkTo("command","autodiff","autodiff");?>, <?php linkTo("command","taylor","taylor");?>, <?php linkTo("command","remez","remez");?> 
</div> 
