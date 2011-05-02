<a name="autodiff"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","autodiff","autodiff");?> 
<span class="smallDescription">Computes the first n derivatives of a function at a point or over an interval. 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","autodiff","autodiff");?>(<span class="arg">f</span>, <span class="arg">n</span>, <span class="arg">x0</span>) : (<span class="type">function</span>, <span class="type">integer</span>, <span class="type">constant</span>) -&gt; <span class="type">list</span></span> 
<span class="commandline"><?php linkTo("command","autodiff","autodiff");?>(<span class="arg">f</span>, <span class="arg">n</span>, <span class="arg">I</span>) : (<span class="type">function</span>, <span class="type">integer</span>, <span class="type">range</span>) -&gt; <span class="type">list</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">f</span> is the function to be differentiated.</li> 
<li><span class="arg">n</span> is the order of differentiation.</li> 
<li><span class="arg">x0</span> is the point at which the function is differentiated.</li> 
<li><span class="arg">I</span> is the interval over which the function is differentiated.</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","autodiff","autodiff");?> computes the first n derivatives of f at point x0. The computation 
is performed numerically, without symbolically differentiating the expression 
of f. Yet, the computation is safe since small interval enclosures are 
produced. More precisely, <?php linkTo("command","autodiff","autodiff");?> returns a list [f_0, ..., f_n] such that, 
for each i, f_i is a small interval enclosing the exact value of f^(i)(x0). 
</li><li>Since it does not perform any symbolic differentiation, <?php linkTo("command","autodiff","autodiff");?> is much  
more efficient than <?php linkTo("command","diff","diff");?> and should be prefered when only numerical values 
are necessary. 
</li><li>If an interval I is provided instead of a point x0, the list returned by 
<?php linkTo("command","autodiff","autodiff");?> satisfies: for each i, f^(i)(I) is included in f_i. A particular use 
is when one wants to know the successive derivatives of a function at a non 
representable point such as pi. In this case, it suffices to call <?php linkTo("command","autodiff","autodiff");?> 
with the (almost) point interval I = [<?php linkTo("command","pi","pi");?>]. 
</li><li>When I is almost a point interval, the returned enclosures f_i are also 
almost point intervals. However, when the interval I begins to be fairly 
large, the enclosures can be deeply overestimated due to the dependecy 
phenomenon present with interval arithmetic. 
</li><li>As a particular case, f_0 is an enclosure of the image of f over I. 
However, since the algorithm is not specially designed for this purpose it is 
not very efficient for this particular task. In particular, it is not able to 
return a finite enclosure for functions with removable singularities 
(e.g. sin(x)/x at 0). The command <?php linkTo("command","evaluate","evaluate");?> is much more efficient for 
computing an accurate enclosure of the image of a function over an interval. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; L = autodiff(exp(cos(x))+sin(exp(x)), 5, 0);<br> 
&nbsp;&nbsp;&nbsp;&gt; midpointmode = on!;<br> 
&nbsp;&nbsp;&nbsp;&gt; for f_i in L do f_i;<br> 
&nbsp;&nbsp;&nbsp;0.3559752813266941742012789792982961497379810154498~2/4~e1<br> 
&nbsp;&nbsp;&nbsp;0.5403023058681397174009366074429766037323104206179~0/3~<br> 
&nbsp;&nbsp;&nbsp;-0.3019450507398802024611853185539984893647499733880~6/2~e1<br> 
&nbsp;&nbsp;&nbsp;-0.252441295442368951995750696489089699886768918239~6/4~e1<br> 
&nbsp;&nbsp;&nbsp;0.31227898756481033145214529184139729746320579069~1/3~e1<br> 
&nbsp;&nbsp;&nbsp;-0.16634307959006696033484053579339956883955954978~3/1~e2<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; f = log(cos(x)+x);<br> 
&nbsp;&nbsp;&nbsp;&gt; L = autodiff(log(cos(x)+x), 5, [2,4]);<br> 
&nbsp;&nbsp;&nbsp;&gt; L[0];<br> 
&nbsp;&nbsp;&nbsp;[0;1.27643852425465597132446653114905059102580436018893]<br> 
&nbsp;&nbsp;&nbsp;&gt; evaluate(f, [2,4]);<br> 
&nbsp;&nbsp;&nbsp;[0.45986058925497069206106494332976097408234056912429;1.20787210589964169595901037621103012113048821362855]<br> 
&nbsp;&nbsp;&nbsp;&gt; fprime = diff(f);<br> 
&nbsp;&nbsp;&nbsp;&gt; L[1];<br> 
&nbsp;&nbsp;&nbsp;[2.53086745013099407167484456656211083053393118778677e-2;1.75680249530792825137263909451182909413591288733649]<br> 
&nbsp;&nbsp;&nbsp;&gt; evaluate(fprime,[2,4]);<br> 
&nbsp;&nbsp;&nbsp;[2.71048755415961996452136364304380881763456815673085e-2;1.10919530663943290837397225788623531405558431279949]<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; L = autodiff(sin(x)/x, 0, [-1,1]);<br> 
&nbsp;&nbsp;&nbsp;&gt; L[0];<br> 
&nbsp;&nbsp;&nbsp;[-@Inf@;@Inf@]<br> 
&nbsp;&nbsp;&nbsp;&gt; evaluate(sin(x)/x, [-1,1]);<br> 
&nbsp;&nbsp;&nbsp;[0.5403023058681397174009366074429766037323104206179;1]<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","diff","diff");?>, <?php linkTo("command","evaluate","evaluate");?> 
</div> 
