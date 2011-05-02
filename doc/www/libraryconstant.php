<a name="libraryconstant"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","libraryconstant","libraryconstant");?> 
<span class="smallDescription">binds an external mathematical constant to a variable in Sollya 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","libraryconstant","libraryconstant");?>(<span class="arg">path</span>) : <span class="type">string</span> -&gt; <span class="type">function</span></span> 
 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>The command <?php linkTo("command","libraryconstant","libraryconstant");?> lets you extend the set of mathematical 
constants known to Sollya. 
By default, the only mathematical constant known by Sollya is <?php linkTo("command","pi","pi");?>. 
For particular applications, one may want to 
manipulate other constants, such as Euler's gamma constant, for instance. 
</li><li><?php linkTo("command","libraryconstant","libraryconstant");?> makes it possible to let Sollya know about new constants. 
In order to let it know, you have to provide an implementation of the 
constant you are interested in. This implementation is a C file containing 
a function of the form: 
              void my_ident(mpfr_t result, mp_prec_t prec)  
The semantic of this function is the following: it is an implementation of 
the constant in arbitrary precision. 
my_ident(result, prec) shall set the 
precision of the variable result to a suitable precision (the variable is 
assumed to be already initialized) and store in result an approximate value 
of the constant with a relative error not greater than 2^(1-prec). 
More precisely, if c is the exact value of the constant, the value stored 
in result should satisfy |result-c| &lt;= 2^(1-prec)*|c|. 
</li><li>You can include sollya.h in your implementation and use library  
functionnalities of Sollya for your implementation. However, this requires to 
have compiled Sollya with -fPIC in order to make the Sollya executable 
code position independent and to use a system on with programs, using dlopen 
to open dynamic routines can dynamically open themselves. 
</li><li>To bind your constant into Sollya, you must use the same identifier as the 
function name used in your implementation file (my_ident in the previous 
example). Once the function code has been bound to an identifier, you can use 
a simple assignment to assign the bound identifier to yet another identifier. 
This way, you may use convenient names inside Sollya even if your 
implementation environment requires you to use a less convenient name. 
</li><li>Once your constant is bound, it is considered by Sollya as an infinitely 
accurate constant (i.e. a 0-ary function, exactly like <?php linkTo("command","pi","pi");?>). 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; bashexecute("gcc -fPIC -Wall -c libraryconstantexample.c -I$HOME/.local/include");<br> 
&nbsp;&nbsp;&nbsp;&gt; bashexecute("gcc -shared -o libraryconstantexample libraryconstantexample.o -lgmp -lmpfr");<br> 
&nbsp;&nbsp;&nbsp;&gt; euler_gamma = libraryconstant("./libraryconstantexample");<br> 
&nbsp;&nbsp;&nbsp;&gt; prec = 20!;<br> 
&nbsp;&nbsp;&nbsp;&gt; euler_gamma;<br> 
&nbsp;&nbsp;&nbsp;0.577215<br> 
&nbsp;&nbsp;&nbsp;&gt; prec = 100!;<br> 
&nbsp;&nbsp;&nbsp;&gt; euler_gamma;<br> 
&nbsp;&nbsp;&nbsp;0.577215664901532860606512090082<br> 
&nbsp;&nbsp;&nbsp;&gt; midpointmode = on;<br> 
&nbsp;&nbsp;&nbsp;Midpoint mode has been activated.<br> 
&nbsp;&nbsp;&nbsp;&gt; [euler_gamma];<br> 
&nbsp;&nbsp;&nbsp;0.577215664901532860606512090~0/1~<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","bashexecute","bashexecute");?>, <?php linkTo("command","externalproc","externalproc");?>, <?php linkTo("command","externalplot","externalplot");?>, <?php linkTo("command","pi","pi");?>, <?php linkTo("command","library","library");?>, <?php linkTo("command","evaluate","evaluate");?> 
</div> 
