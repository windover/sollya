<a name="printexpansion"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","printexpansion","printexpansion");?> 
<span class="smallDescription">prints a polynomial in Horner form with its coefficients written as a expansions of double precision numbers 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library name:</h2> 
<span class="commandline type">void sollya_lib_printexpansion(sollya_obj_t)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","printexpansion","printexpansion");?>(<span class="arg">polynomial</span>) : <span class="type">function</span> -&gt; <span class="type">void</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">polynomial</span> represents the polynomial to be printed</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>The command <?php linkTo("command","printexpansion","printexpansion");?> prints the polynomial <span class="arg">polynomial</span> in Horner form 
writing its coefficients as expansions of double precision 
numbers. The double precision numbers themselves are displayed in 
hexadecimal memory notation (see <?php linkTo("command","printdouble","printdouble");?>).  
<br><br> 
If some of the coefficients of the polynomial <span class="arg">polynomial</span> are not 
floating-point constants but constant expressions, they are evaluated 
to floating-point constants using the global precision <?php linkTo("command","prec","prec");?>.  If a 
rounding occurs in this evaluation, a warning is displayed. 
<br><br> 
If the exponent range of double precision is not sufficient to display 
all the mantissa bits of a coefficient, the coefficient is displayed 
rounded and a warning is displayed. 
<br><br> 
If the argument <span class="arg">polynomial</span> does not a polynomial, nothing but a 
warning or a newline is displayed. Constants can be displayed using 
<?php linkTo("command","printexpansion","printexpansion");?> since they are polynomials of degree 0. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; printexpansion(roundcoefficients(taylor(exp(x),5,0),[|DD...|]));<br> 
&nbsp;&nbsp;&nbsp;0x3ff0000000000000 + x * (0x3ff0000000000000 + x * (0x3fe0000000000000 + x * ((0x3fc5555555555555 + 0x3c65555555555555) + x * ((0x3fa5555555555555 + 0x3c45555555555555) + x * (0x3f81111111111111 + 0x3c01111111111111)))))<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; printexpansion(remez(exp(x),5,[-1;1]));<br> 
&nbsp;&nbsp;&nbsp;(0x3ff0002eec90e5a6 + 0x3c9ea6a6a0087757 + 0xb8eb3e644ef44998) + x * ((0x3ff00028358fd3ac + 0x3c8ffa7d96c95f7a + 0xb91da9809b13dd54 + 0x35c0000000000000) + x * ((0x3fdff2d7e6a9fea5 + 0x3c74460e4c0e4fe2 + 0x38fcd1b6b4e85bb0 + 0x3590000000000000) + x * ((0x3fc54d6733b4839e + 0x3c6654e4d8614a44 + 0xb905c7a26b66ea92 + 0xb598000000000000) + x * ((0x3fa66c209b7150a8 + 0x3c34b1bba8f78092 + 0xb8c75f6eb90dae02 + 0x3560000000000000) + x * (0x3f81e554242ab128 + 0xbc23e920a76e760c + 0x38c0589c2cae6caf + 0x3564000000000000)))))<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; verbosity = 1!;<br> 
&nbsp;&nbsp;&nbsp;&gt; prec = 3500!;<br> 
&nbsp;&nbsp;&nbsp;&gt; printexpansion(pi);<br> 
&nbsp;&nbsp;&nbsp;(0x400921fb54442d18 + 0x3ca1a62633145c07 + 0xb92f1976b7ed8fbc + 0x35c4cf98e804177d + 0x32631d89cd9128a5 + 0x2ec0f31c6809bbdf + 0x2b5519b3cd3a431b + 0x27e8158536f92f8a + 0x246ba7f09ab6b6a9 + 0xa0eedd0dbd2544cf + 0x1d779fb1bd1310ba + 0x1a1a637ed6b0bff6 + 0x96aa485fca40908e + 0x933e501295d98169 + 0x8fd160dbee83b4e0 + 0x8c59b6d799ae131c + 0x08f6cf70801f2e28 + 0x05963bf0598da483 + 0x023871574e69a459 + 0x8000000005702db3 + 0x8000000000000000)<br> 
&nbsp;&nbsp;&nbsp;Warning: the expansion is not complete because of the limited exponent range of double precision.<br> 
&nbsp;&nbsp;&nbsp;Warning: rounding occurred while printing.<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","printdouble","printdouble");?>, <?php linkTo("command","horner","horner");?>, <?php linkTo("command","print","print");?>, <?php linkTo("command","prec","prec");?>, <?php linkTo("command","remez","remez");?>, <?php linkTo("command","taylor","taylor");?>, <?php linkTo("command","roundcoefficients","roundcoefficients");?>, <?php linkTo("command","fpminimax","fpminimax");?>, <?php linkTo("command","implementpoly","implementpoly");?> 
</div> 
