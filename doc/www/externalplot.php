<a name="externalplot"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","externalplot","externalplot");?> 
<span class="smallDescription">plots the error of an external code with regard to a function 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","externalplot","externalplot");?>(<span class="arg">filename</span>, <span class="arg">mode</span>, <span class="arg">function</span>, <span class="arg">range</span>, <span class="arg">precision</span>) : (<span class="type">string</span>, <span class="type">absolute|relative</span>, <span class="type">function</span>, <span class="type">range</span>, <span class="type">integer</span>) -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","externalplot","externalplot");?>(<span class="arg">filename</span>, <span class="arg">mode</span>, <span class="arg">function</span>, <span class="arg">range</span>, <span class="arg">precision</span>, <span class="arg">perturb</span>) : (<span class="type">string</span>, <span class="type">absolute|relative</span>, <span class="type">function</span>, <span class="type">range</span>, <span class="type">integer</span>, <span class="type">perturb</span>) -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","externalplot","externalplot");?>(<span class="arg">filename</span>, <span class="arg">mode</span>, <span class="arg">function</span>, <span class="arg">range</span>, <span class="arg">precision</span>, <span class="arg">plot mode</span>, <span class="arg">result filename</span>) : (<span class="type">string</span>, <span class="type">absolute|relative</span>, <span class="type">function</span>, <span class="type">range</span>, <span class="type">integer</span>, <span class="type">file|postscript|postscriptfile</span>, <span class="type">string</span>) -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","externalplot","externalplot");?>(<span class="arg">filename</span>, <span class="arg">mode</span>, <span class="arg">function</span>, <span class="arg">range</span>, <span class="arg">precision</span>, <span class="arg">perturb</span>, <span class="arg">plot mode</span>, <span class="arg">result filename</span>) : (<span class="type">string</span>, <span class="type">absolute|relative</span>, <span class="type">function</span>, <span class="type">range</span>, <span class="type">integer</span>, <span class="type">perturb</span>, <span class="type">file|postscript|postscriptfile</span>, <span class="type">string</span>) -&gt; <span class="type">void</span></span> 
 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>The command <?php linkTo("command","externalplot","externalplot");?> plots the error of an external function 
evaluation code sequence implemented in the object file named 
<span class="arg">filename</span> with regard to the function <span class="arg">function</span>.  If <span class="arg">mode</span> 
evaluates to <span class="arg">absolute</span>, the difference of both functions is 
considered as an error function; if <span class="arg">mode</span> evaluates to <span class="arg">relative</span>, 
the difference is divided by the function <span class="arg">function</span>. The resulting 
error function is plotted on all floating-point numbers with 
<span class="arg">precision</span> significant mantissa bits in the range <span class="arg">range</span>.  
<br><br> 
If the sixth argument of the command <?php linkTo("command","externalplot","externalplot");?> is given and evaluates to 
<?php linkTo("command","perturb","perturb");?>, each of the floating-point numbers the function is evaluated at gets perturbed by a 
random value that is uniformly distributed in +/-1 ulp 
around the original <span class="arg">precision</span> bit floating-point variable. 
<br><br> 
If a sixth and seventh argument, respectively a seventh and eighth 
argument in the presence of <?php linkTo("command","perturb","perturb");?> as a sixth argument, are given 
that evaluate to a variable of type <span class="type">file|postscript|postscriptfile</span> respectively to a 
character sequence of type <span class="type">string</span>, <?php linkTo("command","externalplot","externalplot");?> will plot 
(additionally) to a file in the same way as the command <?php linkTo("command","plot","plot");?> 
does. See <?php linkTo("command","plot","plot");?> for details. 
<br><br> 
The external function evaluation code given in the object file name 
<span class="arg">filename</span> is supposed to define a function name f as 
follows (here in C syntax): void f(mpfr_t rop, mpfr_t op).  
This function is supposed to evaluate op with an accuracy corresponding 
to the precision of rop and assign this value to 
rop. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; bashexecute("gcc -fPIC -c externalplotexample.c");<br> 
&nbsp;&nbsp;&nbsp;&gt; bashexecute("gcc -shared -o externalplotexample externalplotexample.o -lgmp -lmpfr");<br> 
&nbsp;&nbsp;&nbsp;&gt; externalplot("./externalplotexample",relative,exp(x),[-1/2;1/2],12,perturb);<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","plot","plot");?>, <?php linkTo("command","asciiplot","asciiplot");?>, <?php linkTo("command","perturb","perturb");?>, <?php linkTo("command","absolute","absolute");?>, <?php linkTo("command","relative","relative");?>, <?php linkTo("command","file","file");?>, <?php linkTo("command","postscript","postscript");?>, <?php linkTo("command","postscriptfile","postscriptfile");?>, <?php linkTo("command","bashexecute","bashexecute");?>, <?php linkTo("command","externalproc","externalproc");?>, <?php linkTo("command","library","library");?> 
</div> 
