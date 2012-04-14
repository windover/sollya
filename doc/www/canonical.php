<a name="canonical"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","canonical","canonical");?> 
<span class="smallDescription">brings all polynomial subexpressions of an expression to canonical form or activates, deactivates or checks canonical form printing 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library names:</h2> 
<span class="commandline type">void sollya_lib_set_canonical_and_print(sollya_obj_t)</span> 
<span class="commandline type">void sollya_lib_set_canonical(sollya_obj_t)</span> 
<span class="commandline type">sollya_obj_t sollya_lib_canonical(sollya_obj_t)</span> 
<span class="commandline type">sollya_obj_t sollya_lib_get_canonical()</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","canonical","canonical");?>(<span class="arg">function</span>) : <span class="type">function</span> -&gt; <span class="type">function</span></span> 
<span class="commandline"><?php linkTo("command","canonical","canonical");?> = <span class="arg">activation value</span> : <span class="type">on|off</span> -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","canonical","canonical");?> = <span class="arg">activation value</span> ! : <span class="type">on|off</span> -&gt; <span class="type">void</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">function</span> represents the expression to be rewritten in canonical form</li> 
<li><span class="arg">activation value</span> represents <?php linkTo("command","on","on");?> or <?php linkTo("command","off","off");?>, i.e. activation or deactivation</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>The command <?php linkTo("command","canonical","canonical");?> rewrites the expression representing the function 
<span class="arg">function</span> in a way such that all polynomial subexpressions (or the 
whole expression itself, if it is a polynomial) are written in 
canonical form, i.e. as a sum of monomials in the canonical base. The 
canonical base is the base of the integer powers of the global free 
variable. The command <?php linkTo("command","canonical","canonical");?> does not endanger the safety of 
computations even in Sollya's floating-point environment: the 
function returned is mathematically equal to the function <span class="arg">function</span>. 
</li><li>An assignment <?php linkTo("command","canonical","canonical");?> = <span class="arg">activation value</span>, where <span class="arg">activation value</span> 
is one of <?php linkTo("command","on","on");?> or <?php linkTo("command","off","off");?>, activates respectively deactivates the 
automatic printing of polynomial expressions in canonical form, 
i.e. as a sum of monomials in the canonical base. If automatic 
printing in canonical form is deactivated, automatic printing yields to 
displaying polynomial subexpressions in Horner form. 
<br><br> 
If the assignment <?php linkTo("command","canonical","canonical");?> = <span class="arg">activation value</span> is followed by an 
exclamation mark, no message indicating the new state is 
displayed. Otherwise the user is informed of the new state of the 
global mode by an indication. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; print(canonical(1 + x * (x + 3 * x^2)));<br> 
&nbsp;&nbsp;&nbsp;1 + x^2 + 3 * x^3<br> 
&nbsp;&nbsp;&nbsp;&gt; print(canonical((x + 1)^7));<br> 
&nbsp;&nbsp;&nbsp;1 + 7 * x + 21 * x^2 + 35 * x^3 + 35 * x^4 + 21 * x^5 + 7 * x^6 + x^7<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; print(canonical(exp((x + 1)^5) - log(asin(((x + 2) + x)^4 * (x + 1)) + x)));<br> 
&nbsp;&nbsp;&nbsp;exp(1 + 5 * x + 10 * x^2 + 10 * x^3 + 5 * x^4 + x^5) - log(asin(16 + 80 * x + 160 * x^2 + 160 * x^3 + 80 * x^4 + 16 * x^5) + x)<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; canonical;<br> 
&nbsp;&nbsp;&nbsp;off<br> 
&nbsp;&nbsp;&nbsp;&gt; (x + 2)^9;<br> 
&nbsp;&nbsp;&nbsp;512 + x * (2304 + x * (4608 + x * (5376 + x * (4032 + x * (2016 + x * (672 + x * (144 + x * (18 + x))))))))<br> 
&nbsp;&nbsp;&nbsp;&gt; canonical = on;<br> 
&nbsp;&nbsp;&nbsp;Canonical automatic printing output has been activated.<br> 
&nbsp;&nbsp;&nbsp;&gt; (x + 2)^9;<br> 
&nbsp;&nbsp;&nbsp;512 + 2304 * x + 4608 * x^2 + 5376 * x^3 + 4032 * x^4 + 2016 * x^5 + 672 * x^6 + 144 * x^7 + 18 * x^8 + x^9<br> 
&nbsp;&nbsp;&nbsp;&gt; canonical;<br> 
&nbsp;&nbsp;&nbsp;on<br> 
&nbsp;&nbsp;&nbsp;&gt; canonical = off!;<br> 
&nbsp;&nbsp;&nbsp;&gt; (x + 2)^9;<br> 
&nbsp;&nbsp;&nbsp;512 + x * (2304 + x * (4608 + x * (5376 + x * (4032 + x * (2016 + x * (672 + x * (144 + x * (18 + x))))))))<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","horner","horner");?>, <?php linkTo("command","print","print");?>, <?php linkTo("command","autosimplify","autosimplify");?> 
</div> 
