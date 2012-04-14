<a name="function"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","function","function");?> 
<span class="smallDescription">keyword for declaring a procedure-based function or a keyword representing a <span class="type">function</span> type  
</span> 
</div> 
<div class="divLibraryName"> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","function","function");?>(<span class="arg">procedure</span>)  : <span class="type">procedure</span> -&gt; <span class="type">function</span></span> 
<span class="commandline"><?php linkTo("command","function","function");?> : <span class="type">type type</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">procedure</span> is a procedure of type (<span class="type">range</span>, <span class="type">integer</span>, <span class="type">integer</span>) -&gt; <span class="type">range</span></li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>For the sake of safety and mathematical consistency, Sollya 
distinguishes clearly between functions, seen in the mathematical 
sense of the term, i.e. mappings, and procedures, seen in the sense 
Computer Science gives to functions, i.e. pieces of code that compute 
results for arguments following an algorithm. In some cases however, 
it is interesting to use such Computer Science procedures as 
realisations of mathematical functions, e.g. in order to plot them or 
even to perform polynomial approximation on them. The <?php linkTo("command","function","function");?> keyword 
allows for such a transformation of a Sollya procedure into a Sollya 
function.  
</li><li>The procedure to be used as a function through <?php linkTo("command","function","function");?>(<span class="arg">procedure</span>) 
must be of type (<span class="type">range</span>, <span class="type">integer</span>, <span class="type">integer</span>) 
-&gt; <span class="type">range</span>. This means it must take in argument 
an interval X, a degree of differentiation n and a 
working precision p. It must return in result an interval 
Y encompassing the image f^(n)(X) of the 
n-th derivative of the implemented function f, 
i.e. f^(n)(X) c Y. In order to allow 
Sollya's algorithms to work properly, the procedure must ensure that, 
whenever (p, diam(X)) tends to (infinity, 0), 
the computed over-estimated bounding Y tends to the actual image f^(n)(X). 
</li><li>The user must be aware that they are responsible of the correctness 
of the procedure. If, for some n and X, <span class="arg">procedure</span> returns an interval Y 
such that f^n(X) is not included in Y, <?php linkTo("command","function","function");?> will successfully 
return a function without any complain, but this function might behave 
inconsistently in further computations. 
</li><li>For cases when the procedure does not have the correct signature or 
does not return a finite interval as a result <?php linkTo("command","function","function");?>(<span class="arg">procedure</span>) 
evaluates to Not-A-Number (resp. to an interval of Not-A-Numbers for 
interval evaluation). 
</li><li><?php linkTo("command","function","function");?> also represents the <span class="type">function</span> type for declarations 
of external procedures by means of <?php linkTo("command","externalproc","externalproc");?>. 
<br><br> 
Remark that in contrast to other indicators, type indicators like 
<?php linkTo("command","function","function");?> cannot be handled outside the <?php linkTo("command","externalproc","externalproc");?> context.  In 
particular, they cannot be assigned to variables. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; procedure EXP(X,n,p) {<br> 
&nbsp;&nbsp;&nbsp;&nbsp; 	&nbsp;&nbsp;var res, oldPrec;<br> 
&nbsp;&nbsp;&nbsp;&nbsp; 	&nbsp;&nbsp;oldPrec = prec;<br> 
&nbsp;&nbsp;&nbsp;&nbsp; 	&nbsp;&nbsp;prec = p!;<br> 
&nbsp;&nbsp;&nbsp;&nbsp; 	&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp; 	&nbsp;&nbsp;res = exp(X);<br> 
&nbsp;&nbsp;&nbsp;&nbsp; 	&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp; 	&nbsp;&nbsp;prec = oldPrec!;<br> 
&nbsp;&nbsp;&nbsp;&nbsp; 	&nbsp;&nbsp;return res;<br> 
&nbsp;&nbsp;&nbsp;&nbsp; };<br> 
&nbsp;&nbsp;&nbsp;&gt; f = function(EXP);<br> 
&nbsp;&nbsp;&nbsp;&gt; f(1);<br> 
&nbsp;&nbsp;&nbsp;2.71828182845904523536028747135266249775724709369998<br> 
&nbsp;&nbsp;&nbsp;&gt; exp(1);<br> 
&nbsp;&nbsp;&nbsp;2.71828182845904523536028747135266249775724709369998<br> 
&nbsp;&nbsp;&nbsp;&gt; f(x + 3);<br> 
&nbsp;&nbsp;&nbsp;(function(proc(X, n, p)<br> 
&nbsp;&nbsp;&nbsp;{<br> 
&nbsp;&nbsp;&nbsp;var res, oldPrec;<br> 
&nbsp;&nbsp;&nbsp;oldPrec = prec;<br> 
&nbsp;&nbsp;&nbsp;prec = p!;<br> 
&nbsp;&nbsp;&nbsp;res = exp(X);<br> 
&nbsp;&nbsp;&nbsp;prec = oldPrec!;<br> 
&nbsp;&nbsp;&nbsp;return res;<br> 
&nbsp;&nbsp;&nbsp;}))(3 + x)<br> 
&nbsp;&nbsp;&nbsp;&gt; diff(f);<br> 
&nbsp;&nbsp;&nbsp;diff(function(proc(X, n, p)<br> 
&nbsp;&nbsp;&nbsp;{<br> 
&nbsp;&nbsp;&nbsp;var res, oldPrec;<br> 
&nbsp;&nbsp;&nbsp;oldPrec = prec;<br> 
&nbsp;&nbsp;&nbsp;prec = p!;<br> 
&nbsp;&nbsp;&nbsp;res = exp(X);<br> 
&nbsp;&nbsp;&nbsp;prec = oldPrec!;<br> 
&nbsp;&nbsp;&nbsp;return res;<br> 
&nbsp;&nbsp;&nbsp;}))<br> 
&nbsp;&nbsp;&nbsp;&gt; (diff(f))(0);<br> 
&nbsp;&nbsp;&nbsp;1<br> 
&nbsp;&nbsp;&nbsp;&gt; g = f(sin(x));<br> 
&nbsp;&nbsp;&nbsp;&gt; g(17);<br> 
&nbsp;&nbsp;&nbsp;0.382358169993866834026905546416556413595734583420876<br> 
&nbsp;&nbsp;&nbsp;&gt; diff(g);<br> 
&nbsp;&nbsp;&nbsp;(diff(function(proc(X, n, p)<br> 
&nbsp;&nbsp;&nbsp;{<br> 
&nbsp;&nbsp;&nbsp;var res, oldPrec;<br> 
&nbsp;&nbsp;&nbsp;oldPrec = prec;<br> 
&nbsp;&nbsp;&nbsp;prec = p!;<br> 
&nbsp;&nbsp;&nbsp;res = exp(X);<br> 
&nbsp;&nbsp;&nbsp;prec = oldPrec!;<br> 
&nbsp;&nbsp;&nbsp;return res;<br> 
&nbsp;&nbsp;&nbsp;})))(sin(x)) * cos(x)<br> 
&nbsp;&nbsp;&nbsp;&gt; (diff(g))(1);<br> 
&nbsp;&nbsp;&nbsp;1.25338076749344683697237458088447611474812675164344<br> 
&nbsp;&nbsp;&nbsp;&gt; p = remez(f,3,[-1/2;1/2]);<br> 
&nbsp;&nbsp;&nbsp;&gt; p;<br> 
&nbsp;&nbsp;&nbsp;0.9996712090142519365811043588840936667986880903378 + x * (0.99973702983570053280233869785694438940067223265505 + x * (0.51049729360256555535800202052281444451304355667385 + x * 0.1698143246071767617700502198641549152447429302716))<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","proc","proc");?>, <?php linkTo("command","library","library");?>, <?php linkTo("command","procedure","procedure");?>, <?php linkTo("command","externalproc","externalproc");?>, <?php linkTo("command","boolean","boolean");?>, <?php linkTo("command","constant","constant");?>, <?php linkTo("command","integer","integer");?>, <?php linkTo("command","listof","list of");?>, <?php linkTo("command","range","range");?>, <?php linkTo("command","string","string");?> 
</div> 
