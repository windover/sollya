<a name="implementpoly"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","implementpoly","implementpoly");?> 
<span class="smallDescription">implements a polynomial using double, double-double and triple-double arithmetic and generates a Gappa proof 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library names:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_implementpoly(sollya_obj_t, sollya_obj_t,</span> 
<span class="commandline type">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;sollya_obj_t, sollya_obj_t,</span> 
<span class="commandline type">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;sollya_obj_t, sollya_obj_t, ...)</span> 
<span class="commandline type">sollya_obj_t sollya_lib_v_implementpoly(sollya_obj_t, sollya_obj_t,</span> 
<span class="commandline type">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;sollya_obj_t, sollya_obj_t,</span> 
<span class="commandline type">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;sollya_obj_t, sollya_obj_t, va_list)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","implementpoly","implementpoly");?>(<span class="arg">polynomial</span>, <span class="arg">range</span>, <span class="arg">error bound</span>, <span class="arg">format</span>, <span class="arg">functionname</span>, <span class="arg">filename</span>) : (<span class="type">function</span>, <span class="type">range</span>, <span class="type">constant</span>, <span class="type">D|double|DD|doubledouble|TD|tripledouble</span>, <span class="type">string</span>, <span class="type">string</span>) -&gt; <span class="type">function</span></span> 
<span class="commandline"><?php linkTo("command","implementpoly","implementpoly");?>(<span class="arg">polynomial</span>, <span class="arg">range</span>, <span class="arg">error bound</span>, <span class="arg">format</span>, <span class="arg">functionname</span>, <span class="arg">filename</span>, <span class="arg">honor coefficient precisions</span>) : (<span class="type">function</span>, <span class="type">range</span>, <span class="type">constant</span>, <span class="type">D|double|DD|doubledouble|TD|tripledouble</span>, <span class="type">string</span>, <span class="type">string</span>, <span class="type">honorcoeffprec</span>) -&gt; <span class="type">function</span></span> 
<span class="commandline"><?php linkTo("command","implementpoly","implementpoly");?>(<span class="arg">polynomial</span>, <span class="arg">range</span>, <span class="arg">error bound</span>, <span class="arg">format</span>, <span class="arg">functionname</span>, <span class="arg">filename</span>, <span class="arg">proof filename</span>) : (<span class="type">function</span>, <span class="type">range</span>, <span class="type">constant</span>, <span class="type">D|double|DD|doubledouble|TD|tripledouble</span>, <span class="type">string</span>, <span class="type">string</span>, <span class="type">string</span>) -&gt; <span class="type">function</span></span> 
<span class="commandline"><?php linkTo("command","implementpoly","implementpoly");?>(<span class="arg">polynomial</span>, <span class="arg">range</span>, <span class="arg">error bound</span>, <span class="arg">format</span>, <span class="arg">functionname</span>, <span class="arg">filename</span>, <span class="arg">honor coefficient precisions</span>, <span class="arg">proof filename</span>) : (<span class="type">function</span>, <span class="type">range</span>, <span class="type">constant</span>, <span class="type">D|double|DD|doubledouble|TD|tripledouble</span>, <span class="type">string</span>, <span class="type">string</span>, <span class="type">honorcoeffprec</span>, <span class="type">string</span>) -&gt; <span class="type">function</span></span> 
 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>The command <?php linkTo("command","implementpoly","implementpoly");?> implements the polynomial <span class="arg">polynomial</span> in range 
<span class="arg">range</span> as a function called <span class="arg">functionname</span> in C code 
using double, double-double and triple-double arithmetic in a way that 
the rounding error (estimated at its first order) is bounded by <span class="arg">error bound</span>.  
The produced code is output in a file named <span class="arg">filename</span>. The 
argument <span class="arg">format</span> indicates the double, double-double or triple-double 
format of the variable in which the polynomial varies, influencing 
also in the signature of the C function. 
<br><br> 
If a seventh or eighth argument <span class="arg">proof filename</span> is given and if this 
argument evaluates to a variable of type <span class="type">string</span>, the command 
<?php linkTo("command","implementpoly","implementpoly");?> will produce a Gappa proof that the 
rounding error is less than the given bound. This proof will be output 
in Gappa syntax in a file name <span class="arg">proof filename</span>. 
<br><br> 
The command <?php linkTo("command","implementpoly","implementpoly");?> returns the polynomial that has been 
implemented. As the command <?php linkTo("command","implementpoly","implementpoly");?> tries to adapt the precision 
needed in each evaluation step to its strict minimum and as it applies 
renormalization to double-double and triple-double precision 
coefficients to bring them to a round-to-nearest expansion form, the 
returned polynomial may differ from the polynomial 
<span class="arg">polynomial</span>. Nevertheless the difference will be small enough that 
the rounding error bound with regard to the polynomial <span class="arg">polynomial</span> 
(estimated at its first order) will be less than the given error 
bound. 
<br><br> 
If a seventh argument <span class="arg">honor coefficient precisions</span> is given and 
evaluates to a variable <?php linkTo("command","honorcoeffprec","honorcoeffprec");?> of type <span class="type">honorcoeffprec</span>, 
<?php linkTo("command","implementpoly","implementpoly");?> will honor the precision of the given polynomial 
<span class="arg">polynomials</span>. This means if a coefficient needs a double-double or a 
triple-double to be exactly stored, <?php linkTo("command","implementpoly","implementpoly");?> will allocate appropriate 
space and use a double-double or triple-double operation even if the 
automatic (heuristic) determination implemented in command <?php linkTo("command","implementpoly","implementpoly");?> 
indicates that the coefficient could be stored on less precision or, 
respectively, the operation could be performed with less 
precision. The use of <?php linkTo("command","honorcoeffprec","honorcoeffprec");?> has advantages and 
disadvantages. If the polynomial <span class="arg">polynomial</span> given has not been 
determined by a process considering directly polynomials with 
floating-point coefficients, <?php linkTo("command","honorcoeffprec","honorcoeffprec");?> should not be 
indicated. The <?php linkTo("command","implementpoly","implementpoly");?> command can then determine the needed 
precision using the same error estimation as used for the 
determination of the precisions of the operations. Generally, the 
coefficients will get rounded to double, double-double and 
triple-double precision in a way that minimizes their number and 
respects the rounding error bound <span class="arg">error bound</span>.  Indicating 
<?php linkTo("command","honorcoeffprec","honorcoeffprec");?> may in this case short-circuit most precision 
estimations leading to sub-optimal code. On the other hand, if the 
polynomial <span class="arg">polynomial</span> has been determined with floating-point 
precisions in mind, <?php linkTo("command","honorcoeffprec","honorcoeffprec");?> should be indicated because such 
polynomials often are very sensitive in terms of error propagation with 
regard to their coefficients' values. Indicating <?php linkTo("command","honorcoeffprec","honorcoeffprec");?> 
prevents the <?php linkTo("command","implementpoly","implementpoly");?> command from rounding the coefficients and 
altering by many orders of magnitude the approximation error of the 
polynomial with regard to the function it approximates. 
<br><br> 
The implementer behind the <?php linkTo("command","implementpoly","implementpoly");?> command makes some assumptions on 
its input and verifies them. If some assumption cannot be verified, 
the implementation will not succeed and <?php linkTo("command","implementpoly","implementpoly");?> will evaluate to a 
variable <?php linkTo("command","error","error");?> of type <span class="type">error</span>. The same behaviour is observed if 
some file is not writable or some other side-effect fails, e.g. if 
the implementer runs out of memory. 
<br><br> 
As error estimation is performed only on the first order, the code 
produced by the <?php linkTo("command","implementpoly","implementpoly");?> command should be considered valid iff a 
Gappa proof has been produced and successfully run 
in Gappa. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; implementpoly(1 - 1/6 * x^2 + 1/120 * x^4, [-1b-10;1b-10], 1b-30, D, "p","implementation.c");<br> 
&nbsp;&nbsp;&nbsp;1 + x^2 * (-0.166666666666666657414808128123695496469736099243164 + x^2 * 8.3333333333333332176851016015461937058717012405395e-3)<br> 
&nbsp;&nbsp;&nbsp;&gt; readfile("implementation.c");<br> 
&nbsp;&nbsp;&nbsp;#define p_coeff_0h 1.00000000000000000000000000000000000000000000000000000000000000000000000000000000e+00<br> 
&nbsp;&nbsp;&nbsp;#define p_coeff_2h -1.66666666666666657414808128123695496469736099243164062500000000000000000000000000e-01<br> 
&nbsp;&nbsp;&nbsp;#define p_coeff_4h 8.33333333333333321768510160154619370587170124053955078125000000000000000000000000e-03<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;void p(double *p_resh, double x) {<br> 
&nbsp;&nbsp;&nbsp;double p_x_0_pow2h;<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;p_x_0_pow2h = x * x;<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;double p_t_1_0h;<br> 
&nbsp;&nbsp;&nbsp;double p_t_2_0h;<br> 
&nbsp;&nbsp;&nbsp;double p_t_3_0h;<br> 
&nbsp;&nbsp;&nbsp;double p_t_4_0h;<br> 
&nbsp;&nbsp;&nbsp;double p_t_5_0h;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;p_t_1_0h = p_coeff_4h;<br> 
&nbsp;&nbsp;&nbsp;p_t_2_0h = p_t_1_0h * p_x_0_pow2h;<br> 
&nbsp;&nbsp;&nbsp;p_t_3_0h = p_coeff_2h + p_t_2_0h;<br> 
&nbsp;&nbsp;&nbsp;p_t_4_0h = p_t_3_0h * p_x_0_pow2h;<br> 
&nbsp;&nbsp;&nbsp;p_t_5_0h = p_coeff_0h + p_t_4_0h;<br> 
&nbsp;&nbsp;&nbsp;*p_resh = p_t_5_0h;<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;}<br> 
&nbsp;&nbsp;&nbsp;<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; implementpoly(1 - 1/6 * x^2 + 1/120 * x^4, [-1b-10;1b-10], 1b-30, D, "p","implementation.c","implementation.gappa");<br> 
&nbsp;&nbsp;&nbsp;1 + x^2 * (-0.166666666666666657414808128123695496469736099243164 + x^2 * 8.3333333333333332176851016015461937058717012405395e-3)<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; verbosity = 1!;<br> 
&nbsp;&nbsp;&nbsp;&gt; q = implementpoly(1 - simplify(TD(1/6)) * x^2,[-1b-10;1b-10],1b-60,DD,"p","implementation.c");<br> 
&nbsp;&nbsp;&nbsp;Warning: at least one of the coefficients of the given polynomial has been rounded in a way<br> 
&nbsp;&nbsp;&nbsp;that the target precision can be achieved at lower cost. Nevertheless, the implemented polynomial<br> 
&nbsp;&nbsp;&nbsp;is different from the given one.<br> 
&nbsp;&nbsp;&nbsp;&gt; printexpansion(q);<br> 
&nbsp;&nbsp;&nbsp;0x3ff0000000000000 + x^2 * 0xbfc5555555555555<br> 
&nbsp;&nbsp;&nbsp;&gt; r = implementpoly(1 - simplify(TD(1/6)) * x^2,[-1b-10;1b-10],1b-60,DD,"p","implementation.c",honorcoeffprec);<br> 
&nbsp;&nbsp;&nbsp;Warning: the infered precision of the 2th coefficient of the polynomial is greater than<br> 
&nbsp;&nbsp;&nbsp;the necessary precision computed for this step. This may make the automatic determination<br> 
&nbsp;&nbsp;&nbsp;of precisions useless.<br> 
&nbsp;&nbsp;&nbsp;&gt; printexpansion(r);<br> 
&nbsp;&nbsp;&nbsp;0x3ff0000000000000 + x^2 * (0xbfc5555555555555 + 0xbc65555555555555 + 0xb905555555555555)<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 4: </h2> 
&nbsp;&nbsp;&nbsp;&gt; p = 0x3ff0000000000000 + x * (0x3ff0000000000000 + x * (0x3fe0000000000000 + x * (0x3fc5555555555559 + x * (0x3fa55555555555bd + x * (0x3f811111111106e2 + x * (0x3f56c16c16bf5eb7 + x * (0x3f2a01a01a292dcd + x * (0x3efa01a0218a016a + x * (0x3ec71de360331aad + x * (0x3e927e42e3823bf3 + x * (0x3e5ae6b2710c2c9a + x * (0x3e2203730c0a7c1d + x * 0x3de5da557e0781df))))))))))));<br> 
&nbsp;&nbsp;&nbsp;&gt; q = implementpoly(p,[-1/2;1/2],1b-60,D,"p","implementation.c",honorcoeffprec,"implementation.gappa");<br> 
&nbsp;&nbsp;&nbsp;&gt; if (q != p) then print("During implementation, rounding has happened.") else print("Polynomial implemented as given.");	<br> 
&nbsp;&nbsp;&nbsp;Polynomial implemented as given.<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","honorcoeffprec","honorcoeffprec");?>, <?php linkTo("command","roundcoefficients","roundcoefficients");?>, <?php linkTo("command","double","double");?>, <?php linkTo("command","doubledouble","doubledouble");?>, <?php linkTo("command","tripledouble","tripledouble");?>, <?php linkTo("command","readfile","readfile");?>, <?php linkTo("command","printexpansion","printexpansion");?>, <?php linkTo("command","error","error");?>, <?php linkTo("command","remez","remez");?>, <?php linkTo("command","fpminimax","fpminimax");?>, <?php linkTo("command","taylor","taylor");?>, <?php linkTo("command","implementconstant","implementconstant");?> 
</div> 
