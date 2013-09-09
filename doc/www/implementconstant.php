<a name="implementconstant"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","implementconstant","implementconstant");?> 
<span class="smallDescription">implements a constant in arbitrary precision 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library names:</h2> 
<span class="commandline type">void sollya_lib_implementconstant(sollya_obj_t, ...);</span> 
<span class="commandline type">void sollya_lib_v_implementconstant(sollya_obj_t, va_list);</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","implementconstant","implementconstant");?>(<span class="arg">expr</span>) : <span class="type">constant</span> -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","implementconstant","implementconstant");?>(<span class="arg">expr</span>,<span class="arg">filename</span>) : (<span class="type">constant</span>, <span class="type">string</span>) -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","implementconstant","implementconstant");?>(<span class="arg">expr</span>,<span class="arg">filename</span>,<span class="arg">functionname</span>) : (<span class="type">constant</span>, <span class="type">string</span>, <span class="type">string</span>) -&gt; <span class="type">void</span></span> 
 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>The command <?php linkTo("command","implementconstant","implementconstant");?> implements the constant expression <span class="arg">expr</span> in  
arbitrary precision. More precisely, it generates the source code (written 
in C, and using MPFR) of a C function const_something with the following 
signature: 
  
          void const_something (mpfr_ptr y, mp_prec_t prec) 
  
Let us denote by c the exact mathematical value of the constant defined by 
the expression <span class="arg">expr</span>. When called with arguments y and prec (where the 
variable y is supposed to be already initialized), the function 
mpfr_const_something sets the precision of y to a suitable precision and 
stores in it an approximate value of c such that 
                            |y-c| &lt;= |c|*2^(1-prec). 
</li><li>When no filename <span class="arg">filename</span> is given or if <?php linkTo("command","default","default");?> is given as 
<span class="arg">filename</span>, the source code produced by <?php linkTo("command","implementconstant","implementconstant");?> is printed on 
standard output. Otherwise, when <span class="arg">filename</span> is given as a  
string of characters, the source code is output to a file  
named <span class="arg">filename</span>. If that file cannot be opened and/or  
written to, <?php linkTo("command","implementconstant","implementconstant");?> fails and has no other effect. 
</li><li>When <span class="arg">functionname</span> is given as an argument to <?php linkTo("command","implementconstant","implementconstant");?> and 
<span class="arg">functionname</span> evaluates to a string of characters, the default name 
for the C function const_something is 
replaced by <span class="arg">functionname</span>. When <?php linkTo("command","default","default");?> is given as <span class="arg">functionname</span>, 
the default name is used nevertheless, as if no <span class="arg">functionname</span> 
argument were given.  When choosing a character sequence for 
<span class="arg">functionname</span>, the user should keep attention to the fact that 
<span class="arg">functionname</span> must be a valid C identifier in order to enable 
error-free compilation of the produced code. 
</li><li>If <span class="arg">expr</span> refers to a constant defined with <?php linkTo("command","libraryconstant","libraryconstant");?>, the produced 
code uses the external code implementing this constant. The user should 
keep in mind that it is up to them to make sure the symbol for that  
external code can get resolved when the newly generated code is to  
be loaded. 
</li><li>If a subexpression of <span class="arg">expr</span> evaluates to 0, <?php linkTo("command","implementconstant","implementconstant");?> will most 
likely fail with an error message. 
</li><li><?php linkTo("command","implementconstant","implementconstant");?> is unable to implement constant expressions <span class="arg">expr</span> that 
contain procedure-based functions, i.e. functions created from Sollya 
procedures using the <?php linkTo("command","function","function");?> construct. If <span class="arg">expr</span> contains such a 
procedure-based function, <?php linkTo("command","implementconstant","implementconstant");?> prints a warning and fails 
silently. The reason for this lack of functionality is that the 
produced C source code, which is supposed to be compiled, would have 
to call back to the Sollya interpreter in order to evaluate the 
procedure-based function. 
</li><li>Similarily, <?php linkTo("command","implementconstant","implementconstant");?> is currently unable to implement constant 
expressions <span class="arg">expr</span> that contain library-based functions, i.e. 
functions dynamically bound to Sollya using the <?php linkTo("command","library","library");?> construct. 
If <span class="arg">expr</span> contains such a library-based function, <?php linkTo("command","implementconstant","implementconstant");?> prints 
a warning and fails silently. Support for this feature is in principle 
feasible from a technical standpoint and might be added in a future 
release of Sollya. 
</li><li>Currently, non-differentiable functions such as <?php linkTo("command","double","double");?>, <?php linkTo("command","doubledouble","doubledouble");?>, 
<?php linkTo("command","tripledouble","tripledouble");?>, <?php linkTo("command","single","single");?>, <?php linkTo("command","halfprecision","halfprecision");?>, <?php linkTo("command","quad","quad");?>, <?php linkTo("command","doubleextended","doubleextended");?>,  
<?php linkTo("command","floor","floor");?>, <?php linkTo("command","ceil","ceil");?>, <?php linkTo("command","nearestint","nearestint");?> are not supported by <?php linkTo("command","implementconstant","implementconstant");?>.  
If <?php linkTo("command","implementconstant","implementconstant");?> encounters one of them, a warning message is displayed  
and no code is produced. However, if <?php linkTo("command","autosimplify","autosimplify");?> equals on, it is  
possible that Sollya silently simplifies subexpressions of <span class="arg">expr</span>  
containing such functions and that <?php linkTo("command","implementconstant","implementconstant");?> successfully produces  
code for evaluating <span class="arg">expr</span>. 
</li><li>While it produces an MPFR-based C source code for <span class="arg">expr</span>, <?php linkTo("command","implementconstant","implementconstant");?> 
takes architectural and system-dependent parameters into account.  For 
example, it checks whether literal constants figuring in <span class="arg">expr</span> can be 
represented on a C long int type or if they must 
be stored in a different manner not to affect their accuracy. These 
tests, performed by Sollya during execution of <?php linkTo("command","implementconstant","implementconstant");?>, depend 
themselves on the architecture Sollya is running on. Users should 
keep this matter in mind, especially when trying to compile source 
code on one machine whilst it has been produced on another. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; implementconstant(exp(1)+log(2)/sqrt(1/10));<br> 
&nbsp;&nbsp;&nbsp;/*<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;This code was generated using non-trivial code generation commands of<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;the Sollya software program.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Before using, modifying and/or integrating this code into other<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;software, review the copyright and license status of this generated<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;code. In particular, see the exception below.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Sollya is<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Copyright 2006-2013 by<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Laboratoire de l'Informatique du Parallelisme, UMR CNRS - ENS Lyon -<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;UCB Lyon 1 - INRIA 5668,<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Laboratoire d'Informatique de Paris 6, equipe PEQUAN, UPMC Universite<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Paris 06 - CNRS - UMR 7606 - LIP6, Paris, France<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;and by<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Centre de recherche INRIA Sophia-Antipolis Mediterranee, equipe APICS,<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Sophia Antipolis, France.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Contributors Ch. Lauter, S. Chevillard, M. Joldes<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;christoph.lauter@ens-lyon.org<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;sylvain.chevillard@ens-lyon.org<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;joldes@lass.fr<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The Sollya software is a computer program whose purpose is to provide<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;an environment for safe floating-point code development. It is<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;particularily targeted to the automatized implementation of<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mathematical floating-point libraries (libm). Amongst other features,<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;it offers a certified infinity norm, an automatic polynomial<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;implementer and a fast Remez algorithm.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The Sollya software is governed by the CeCILL-C license under French<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;law and abiding by the rules of distribution of free software.&nbsp;&nbsp;You<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;can use, modify and/ or redistribute the software under the terms of<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;the CeCILL-C license as circulated by CEA, CNRS and INRIA at the<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;following URL "http://www.cecill.info".<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;As a counterpart to the access to the source code and rights to copy,<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;modify and redistribute granted by the license, users are provided<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;only with a limited warranty and the software's author, the holder of<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;the economic rights, and the successive licensors have only limited<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;liability.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;In this respect, the user's attention is drawn to the risks associated<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;with loading, using, modifying and/or developing or reproducing the<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;software by the user in light of its specific status of free software,<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;that may mean that it is complicated to manipulate, and that also<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;therefore means that it is reserved for developers and experienced<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;professionals having in-depth computer knowledge. Users are therefore<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;encouraged to load and test the software's suitability as regards<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;their requirements in conditions enabling the security of their<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;systems and/or data to be ensured and, more generally, to use and<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;operate it in the same conditions as regards security.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The fact that you are presently reading this means that you have had<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;knowledge of the CeCILL-C license and that you accept its terms.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The Sollya program is distributed WITHOUT ANY WARRANTY; without even<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PURPOSE.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;This generated program is distributed WITHOUT ANY WARRANTY; without<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;even the implied warranty of MERCHANTABILITY or FITNESS FOR A<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PARTICULAR PURPOSE.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;As a special exception, you may create a larger work that contains<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;part or all of this software generated using Sollya and distribute<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;that work under terms of your choice, so long as that work isn't<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;itself a numerical code generator using the skeleton of this code or a<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;modified version thereof as a code skeleton.&nbsp;&nbsp;Alternatively, if you<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;modify or redistribute this generated code itself, or its skeleton,<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;you may (at your option) remove this special exception, which will<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;cause this generated code and its skeleton and the resulting Sollya<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;output files to be licensed under the CeCILL-C licence without this<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;special exception.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;This special exception was added by the Sollya copyright holders in<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;version 4.1 of Sollya.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;*/<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;#include &lt;mpfr.h&gt;<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;void<br> 
&nbsp;&nbsp;&nbsp;const_something (mpfr_ptr y, mp_prec_t prec)<br> 
&nbsp;&nbsp;&nbsp;{<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;/* Declarations */<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_t tmp1;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_t tmp2;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_t tmp3;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_t tmp4;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_t tmp5;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_t tmp6;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_t tmp7;<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;/* Initializations */<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_init2 (tmp2, prec+5);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_init2 (tmp1, prec+3);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_init2 (tmp4, prec+8);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_init2 (tmp3, prec+7);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_init2 (tmp6, prec+11);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_init2 (tmp7, prec+11);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_init2 (tmp5, prec+11);<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;/* Core */<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_set_prec (tmp2, prec+4);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_set_ui (tmp2, 1, MPFR_RNDN);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_set_prec (tmp1, prec+3);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_exp (tmp1, tmp2, MPFR_RNDN);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_set_prec (tmp4, prec+8);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_set_ui (tmp4, 2, MPFR_RNDN);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_set_prec (tmp3, prec+7);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_log (tmp3, tmp4, MPFR_RNDN);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_set_prec (tmp6, prec+11);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_set_ui (tmp6, 1, MPFR_RNDN);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_set_prec (tmp7, prec+11);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_set_ui (tmp7, 10, MPFR_RNDN);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_set_prec (tmp5, prec+11);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_div (tmp5, tmp6, tmp7, MPFR_RNDN);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_set_prec (tmp4, prec+7);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_sqrt (tmp4, tmp5, MPFR_RNDN);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_set_prec (tmp2, prec+5);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_div (tmp2, tmp3, tmp4, MPFR_RNDN);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_set_prec (y, prec+3);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_add (y, tmp1, tmp2, MPFR_RNDN);<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;/* Cleaning stuff */<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_clear(tmp1);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_clear(tmp2);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_clear(tmp3);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_clear(tmp4);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_clear(tmp5);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_clear(tmp6);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_clear(tmp7);<br> 
&nbsp;&nbsp;&nbsp;}<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; implementconstant(sin(13/17),"sine_of_thirteen_seventeenth.c");<br> 
&nbsp;&nbsp;&nbsp;&gt; readfile("sine_of_thirteen_seventeenth.c");<br> 
&nbsp;&nbsp;&nbsp;/*<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;This code was generated using non-trivial code generation commands of<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;the Sollya software program.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Before using, modifying and/or integrating this code into other<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;software, review the copyright and license status of this generated<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;code. In particular, see the exception below.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Sollya is<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Copyright 2006-2013 by<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Laboratoire de l'Informatique du Parallelisme, UMR CNRS - ENS Lyon -<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;UCB Lyon 1 - INRIA 5668,<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Laboratoire d'Informatique de Paris 6, equipe PEQUAN, UPMC Universite<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Paris 06 - CNRS - UMR 7606 - LIP6, Paris, France<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;and by<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Centre de recherche INRIA Sophia-Antipolis Mediterranee, equipe APICS,<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Sophia Antipolis, France.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Contributors Ch. Lauter, S. Chevillard, M. Joldes<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;christoph.lauter@ens-lyon.org<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;sylvain.chevillard@ens-lyon.org<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;joldes@lass.fr<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The Sollya software is a computer program whose purpose is to provide<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;an environment for safe floating-point code development. It is<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;particularily targeted to the automatized implementation of<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mathematical floating-point libraries (libm). Amongst other features,<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;it offers a certified infinity norm, an automatic polynomial<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;implementer and a fast Remez algorithm.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The Sollya software is governed by the CeCILL-C license under French<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;law and abiding by the rules of distribution of free software.&nbsp;&nbsp;You<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;can use, modify and/ or redistribute the software under the terms of<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;the CeCILL-C license as circulated by CEA, CNRS and INRIA at the<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;following URL "http://www.cecill.info".<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;As a counterpart to the access to the source code and rights to copy,<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;modify and redistribute granted by the license, users are provided<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;only with a limited warranty and the software's author, the holder of<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;the economic rights, and the successive licensors have only limited<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;liability.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;In this respect, the user's attention is drawn to the risks associated<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;with loading, using, modifying and/or developing or reproducing the<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;software by the user in light of its specific status of free software,<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;that may mean that it is complicated to manipulate, and that also<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;therefore means that it is reserved for developers and experienced<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;professionals having in-depth computer knowledge. Users are therefore<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;encouraged to load and test the software's suitability as regards<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;their requirements in conditions enabling the security of their<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;systems and/or data to be ensured and, more generally, to use and<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;operate it in the same conditions as regards security.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The fact that you are presently reading this means that you have had<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;knowledge of the CeCILL-C license and that you accept its terms.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The Sollya program is distributed WITHOUT ANY WARRANTY; without even<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PURPOSE.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;This generated program is distributed WITHOUT ANY WARRANTY; without<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;even the implied warranty of MERCHANTABILITY or FITNESS FOR A<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PARTICULAR PURPOSE.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;As a special exception, you may create a larger work that contains<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;part or all of this software generated using Sollya and distribute<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;that work under terms of your choice, so long as that work isn't<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;itself a numerical code generator using the skeleton of this code or a<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;modified version thereof as a code skeleton.&nbsp;&nbsp;Alternatively, if you<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;modify or redistribute this generated code itself, or its skeleton,<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;you may (at your option) remove this special exception, which will<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;cause this generated code and its skeleton and the resulting Sollya<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;output files to be licensed under the CeCILL-C licence without this<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;special exception.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;This special exception was added by the Sollya copyright holders in<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;version 4.1 of Sollya.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;*/<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;#include &lt;mpfr.h&gt;<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;void<br> 
&nbsp;&nbsp;&nbsp;const_something (mpfr_ptr y, mp_prec_t prec)<br> 
&nbsp;&nbsp;&nbsp;{<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;/* Declarations */<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_t tmp1;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_t tmp2;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_t tmp3;<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;/* Initializations */<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_init2 (tmp2, prec+6);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_init2 (tmp3, prec+6);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_init2 (tmp1, prec+6);<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;/* Core */<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_set_prec (tmp2, prec+6);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_set_ui (tmp2, 13, MPFR_RNDN);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_set_prec (tmp3, prec+6);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_set_ui (tmp3, 17, MPFR_RNDN);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_set_prec (tmp1, prec+6);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_div (tmp1, tmp2, tmp3, MPFR_RNDN);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_set_prec (y, prec+2);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_sin (y, tmp1, MPFR_RNDN);<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;/* Cleaning stuff */<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_clear(tmp1);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_clear(tmp2);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_clear(tmp3);<br> 
&nbsp;&nbsp;&nbsp;}<br> 
&nbsp;&nbsp;&nbsp;<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; implementconstant(asin(1/3 * pi),default,"arcsin_of_one_third_pi");<br> 
&nbsp;&nbsp;&nbsp;/*<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;This code was generated using non-trivial code generation commands of<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;the Sollya software program.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Before using, modifying and/or integrating this code into other<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;software, review the copyright and license status of this generated<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;code. In particular, see the exception below.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Sollya is<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Copyright 2006-2013 by<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Laboratoire de l'Informatique du Parallelisme, UMR CNRS - ENS Lyon -<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;UCB Lyon 1 - INRIA 5668,<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Laboratoire d'Informatique de Paris 6, equipe PEQUAN, UPMC Universite<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Paris 06 - CNRS - UMR 7606 - LIP6, Paris, France<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;and by<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Centre de recherche INRIA Sophia-Antipolis Mediterranee, equipe APICS,<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Sophia Antipolis, France.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Contributors Ch. Lauter, S. Chevillard, M. Joldes<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;christoph.lauter@ens-lyon.org<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;sylvain.chevillard@ens-lyon.org<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;joldes@lass.fr<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The Sollya software is a computer program whose purpose is to provide<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;an environment for safe floating-point code development. It is<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;particularily targeted to the automatized implementation of<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mathematical floating-point libraries (libm). Amongst other features,<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;it offers a certified infinity norm, an automatic polynomial<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;implementer and a fast Remez algorithm.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The Sollya software is governed by the CeCILL-C license under French<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;law and abiding by the rules of distribution of free software.&nbsp;&nbsp;You<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;can use, modify and/ or redistribute the software under the terms of<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;the CeCILL-C license as circulated by CEA, CNRS and INRIA at the<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;following URL "http://www.cecill.info".<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;As a counterpart to the access to the source code and rights to copy,<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;modify and redistribute granted by the license, users are provided<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;only with a limited warranty and the software's author, the holder of<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;the economic rights, and the successive licensors have only limited<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;liability.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;In this respect, the user's attention is drawn to the risks associated<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;with loading, using, modifying and/or developing or reproducing the<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;software by the user in light of its specific status of free software,<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;that may mean that it is complicated to manipulate, and that also<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;therefore means that it is reserved for developers and experienced<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;professionals having in-depth computer knowledge. Users are therefore<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;encouraged to load and test the software's suitability as regards<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;their requirements in conditions enabling the security of their<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;systems and/or data to be ensured and, more generally, to use and<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;operate it in the same conditions as regards security.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The fact that you are presently reading this means that you have had<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;knowledge of the CeCILL-C license and that you accept its terms.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The Sollya program is distributed WITHOUT ANY WARRANTY; without even<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PURPOSE.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;This generated program is distributed WITHOUT ANY WARRANTY; without<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;even the implied warranty of MERCHANTABILITY or FITNESS FOR A<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PARTICULAR PURPOSE.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;As a special exception, you may create a larger work that contains<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;part or all of this software generated using Sollya and distribute<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;that work under terms of your choice, so long as that work isn't<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;itself a numerical code generator using the skeleton of this code or a<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;modified version thereof as a code skeleton.&nbsp;&nbsp;Alternatively, if you<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;modify or redistribute this generated code itself, or its skeleton,<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;you may (at your option) remove this special exception, which will<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;cause this generated code and its skeleton and the resulting Sollya<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;output files to be licensed under the CeCILL-C licence without this<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;special exception.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;This special exception was added by the Sollya copyright holders in<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;version 4.1 of Sollya.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;*/<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;#include &lt;mpfr.h&gt;<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;void<br> 
&nbsp;&nbsp;&nbsp;arcsin_of_one_third_pi (mpfr_ptr y, mp_prec_t prec)<br> 
&nbsp;&nbsp;&nbsp;{<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;/* Declarations */<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_t tmp1;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_t tmp2;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_t tmp3;<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;/* Initializations */<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_init2 (tmp2, prec+8);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_init2 (tmp3, prec+8);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_init2 (tmp1, prec+8);<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;/* Core */<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_set_prec (tmp2, prec+8);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_const_pi (tmp2, MPFR_RNDN);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_set_prec (tmp3, prec+8);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_set_ui (tmp3, 3, MPFR_RNDN);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_set_prec (tmp1, prec+8);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_div (tmp1, tmp2, tmp3, MPFR_RNDN);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_set_prec (y, prec+2);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_asin (y, tmp1, MPFR_RNDN);<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;/* Cleaning stuff */<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_clear(tmp1);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_clear(tmp2);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_clear(tmp3);<br> 
&nbsp;&nbsp;&nbsp;}<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 4: </h2> 
&nbsp;&nbsp;&nbsp;&gt; implementconstant(ceil(log(19 + 1/3)),"constant_code.c","magic_constant");<br> 
&nbsp;&nbsp;&nbsp;&gt; readfile("constant_code.c");<br> 
&nbsp;&nbsp;&nbsp;/*<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;This code was generated using non-trivial code generation commands of<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;the Sollya software program.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Before using, modifying and/or integrating this code into other<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;software, review the copyright and license status of this generated<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;code. In particular, see the exception below.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Sollya is<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Copyright 2006-2013 by<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Laboratoire de l'Informatique du Parallelisme, UMR CNRS - ENS Lyon -<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;UCB Lyon 1 - INRIA 5668,<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Laboratoire d'Informatique de Paris 6, equipe PEQUAN, UPMC Universite<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Paris 06 - CNRS - UMR 7606 - LIP6, Paris, France<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;and by<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Centre de recherche INRIA Sophia-Antipolis Mediterranee, equipe APICS,<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Sophia Antipolis, France.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Contributors Ch. Lauter, S. Chevillard, M. Joldes<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;christoph.lauter@ens-lyon.org<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;sylvain.chevillard@ens-lyon.org<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;joldes@lass.fr<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The Sollya software is a computer program whose purpose is to provide<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;an environment for safe floating-point code development. It is<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;particularily targeted to the automatized implementation of<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mathematical floating-point libraries (libm). Amongst other features,<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;it offers a certified infinity norm, an automatic polynomial<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;implementer and a fast Remez algorithm.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The Sollya software is governed by the CeCILL-C license under French<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;law and abiding by the rules of distribution of free software.&nbsp;&nbsp;You<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;can use, modify and/ or redistribute the software under the terms of<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;the CeCILL-C license as circulated by CEA, CNRS and INRIA at the<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;following URL "http://www.cecill.info".<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;As a counterpart to the access to the source code and rights to copy,<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;modify and redistribute granted by the license, users are provided<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;only with a limited warranty and the software's author, the holder of<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;the economic rights, and the successive licensors have only limited<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;liability.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;In this respect, the user's attention is drawn to the risks associated<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;with loading, using, modifying and/or developing or reproducing the<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;software by the user in light of its specific status of free software,<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;that may mean that it is complicated to manipulate, and that also<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;therefore means that it is reserved for developers and experienced<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;professionals having in-depth computer knowledge. Users are therefore<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;encouraged to load and test the software's suitability as regards<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;their requirements in conditions enabling the security of their<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;systems and/or data to be ensured and, more generally, to use and<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;operate it in the same conditions as regards security.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The fact that you are presently reading this means that you have had<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;knowledge of the CeCILL-C license and that you accept its terms.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The Sollya program is distributed WITHOUT ANY WARRANTY; without even<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PURPOSE.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;This generated program is distributed WITHOUT ANY WARRANTY; without<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;even the implied warranty of MERCHANTABILITY or FITNESS FOR A<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PARTICULAR PURPOSE.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;As a special exception, you may create a larger work that contains<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;part or all of this software generated using Sollya and distribute<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;that work under terms of your choice, so long as that work isn't<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;itself a numerical code generator using the skeleton of this code or a<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;modified version thereof as a code skeleton.&nbsp;&nbsp;Alternatively, if you<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;modify or redistribute this generated code itself, or its skeleton,<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;you may (at your option) remove this special exception, which will<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;cause this generated code and its skeleton and the resulting Sollya<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;output files to be licensed under the CeCILL-C licence without this<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;special exception.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;This special exception was added by the Sollya copyright holders in<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;version 4.1 of Sollya.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;*/<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;#include &lt;mpfr.h&gt;<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;void<br> 
&nbsp;&nbsp;&nbsp;magic_constant (mpfr_ptr y, mp_prec_t prec)<br> 
&nbsp;&nbsp;&nbsp;{<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;/* Initializations */<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;/* Core */<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_set_prec (y, prec);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_set_ui (y, 3, MPFR_RNDN);<br> 
&nbsp;&nbsp;&nbsp;}<br> 
&nbsp;&nbsp;&nbsp;<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 5: </h2> 
&nbsp;&nbsp;&nbsp;&gt; bashexecute("gcc -fPIC -Wall -c libraryconstantexample.c -I$HOME/.local/include");<br> 
&nbsp;&nbsp;&nbsp;&gt; bashexecute("gcc -shared -o libraryconstantexample libraryconstantexample.o -lgmp -lmpfr");<br> 
&nbsp;&nbsp;&nbsp;&gt; euler_gamma = libraryconstant("./libraryconstantexample");<br> 
&nbsp;&nbsp;&nbsp;&gt; implementconstant(euler_gamma^(1/3));<br> 
&nbsp;&nbsp;&nbsp;/*<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;This code was generated using non-trivial code generation commands of<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;the Sollya software program.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Before using, modifying and/or integrating this code into other<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;software, review the copyright and license status of this generated<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;code. In particular, see the exception below.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Sollya is<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Copyright 2006-2013 by<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Laboratoire de l'Informatique du Parallelisme, UMR CNRS - ENS Lyon -<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;UCB Lyon 1 - INRIA 5668,<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Laboratoire d'Informatique de Paris 6, equipe PEQUAN, UPMC Universite<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Paris 06 - CNRS - UMR 7606 - LIP6, Paris, France<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;and by<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Centre de recherche INRIA Sophia-Antipolis Mediterranee, equipe APICS,<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Sophia Antipolis, France.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Contributors Ch. Lauter, S. Chevillard, M. Joldes<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;christoph.lauter@ens-lyon.org<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;sylvain.chevillard@ens-lyon.org<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;joldes@lass.fr<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The Sollya software is a computer program whose purpose is to provide<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;an environment for safe floating-point code development. It is<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;particularily targeted to the automatized implementation of<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mathematical floating-point libraries (libm). Amongst other features,<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;it offers a certified infinity norm, an automatic polynomial<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;implementer and a fast Remez algorithm.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The Sollya software is governed by the CeCILL-C license under French<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;law and abiding by the rules of distribution of free software.&nbsp;&nbsp;You<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;can use, modify and/ or redistribute the software under the terms of<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;the CeCILL-C license as circulated by CEA, CNRS and INRIA at the<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;following URL "http://www.cecill.info".<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;As a counterpart to the access to the source code and rights to copy,<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;modify and redistribute granted by the license, users are provided<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;only with a limited warranty and the software's author, the holder of<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;the economic rights, and the successive licensors have only limited<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;liability.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;In this respect, the user's attention is drawn to the risks associated<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;with loading, using, modifying and/or developing or reproducing the<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;software by the user in light of its specific status of free software,<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;that may mean that it is complicated to manipulate, and that also<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;therefore means that it is reserved for developers and experienced<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;professionals having in-depth computer knowledge. Users are therefore<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;encouraged to load and test the software's suitability as regards<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;their requirements in conditions enabling the security of their<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;systems and/or data to be ensured and, more generally, to use and<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;operate it in the same conditions as regards security.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The fact that you are presently reading this means that you have had<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;knowledge of the CeCILL-C license and that you accept its terms.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The Sollya program is distributed WITHOUT ANY WARRANTY; without even<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PURPOSE.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;This generated program is distributed WITHOUT ANY WARRANTY; without<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;even the implied warranty of MERCHANTABILITY or FITNESS FOR A<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PARTICULAR PURPOSE.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;As a special exception, you may create a larger work that contains<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;part or all of this software generated using Sollya and distribute<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;that work under terms of your choice, so long as that work isn't<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;itself a numerical code generator using the skeleton of this code or a<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;modified version thereof as a code skeleton.&nbsp;&nbsp;Alternatively, if you<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;modify or redistribute this generated code itself, or its skeleton,<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;you may (at your option) remove this special exception, which will<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;cause this generated code and its skeleton and the resulting Sollya<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;output files to be licensed under the CeCILL-C licence without this<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;special exception.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;This special exception was added by the Sollya copyright holders in<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;version 4.1 of Sollya.<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;*/<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;#include &lt;mpfr.h&gt;<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;void<br> 
&nbsp;&nbsp;&nbsp;const_something (mpfr_ptr y, mp_prec_t prec)<br> 
&nbsp;&nbsp;&nbsp;{<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;/* Declarations */<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_t tmp1;<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;/* Initializations */<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_init2 (tmp1, prec+1);<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;/* Core */<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;euler_gamma (tmp1, prec+1);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_set_prec (y, prec+2);<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_root (y, tmp1, 3, MPFR_RNDN);<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;/* Cleaning stuff */<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_clear(tmp1);<br> 
&nbsp;&nbsp;&nbsp;}<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","implementpoly","implementpoly");?>, <?php linkTo("command","libraryconstant","libraryconstant");?>, <?php linkTo("command","library","library");?>, <?php linkTo("command","function","function");?> 
</div> 
