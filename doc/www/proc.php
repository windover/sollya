<a name="proc"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","proc","proc");?> 
<span class="smallDescription">defines a Sollya procedure 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","proc","proc");?>(<span class="arg">formal parameter1</span>, <span class="arg">formal parameter2</span>,..., <span class="arg">formal parameter n</span>) { <span class="arg">procedure body</span> } : <span class="type">void</span> -&gt; <span class="type">procedure</span></span> 
<span class="commandline"><?php linkTo("command","proc","proc");?>(<span class="arg">formal parameter1</span>, <span class="arg">formal parameter2</span>,..., <span class="arg">formal parameter n</span>) { <span class="arg">procedure body</span> <?php linkTo("command","return","return");?> <span class="arg">expression</span>; } : <span class="type">void</span> -&gt; <span class="type">procedure</span></span> 
<span class="commandline"><?php linkTo("command","proc","proc");?>(<span class="arg">formal list parameter</span> = ...) { <span class="arg">procedure body</span> } : <span class="type">void</span> -&gt; <span class="type">procedure</span></span> 
<span class="commandline"><?php linkTo("command","proc","proc");?>(<span class="arg">formal list parameter</span> = ...) { <span class="arg">procedure body</span> <?php linkTo("command","return","return");?> <span class="arg">expression</span>; } : <span class="type">void</span> -&gt; <span class="type">procedure</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">formal parameter1</span>, <span class="arg">formal parameter2</span> through <span class="arg">formal parameter n</span> represent identifiers used as formal parameters</li> 
<li><span class="arg">formal list parameter</span> represents an identifier used as a formal parameter for the list of an arbitrary number of parameters</li> 
<li><span class="arg">procedure body</span> represents the imperative statements in the body of the procedure</li> 
<li><span class="arg">expression</span> represents the expression <?php linkTo("command","proc","proc");?> shall evaluate to</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>The <?php linkTo("command","proc","proc");?> keyword allows for defining procedures in the Sollya 
language. These procedures are common Sollya objects that can be 
applied to actual parameters after definition. Upon such an 
application, the Sollya interpreter applies the actual parameters to 
the formal parameters <span class="arg">formal parameter1</span> through <span class="arg">formal parameter n</span> 
(resp. builds up the list of arguments and applies it to the list 
<span class="arg">formal list parameter</span>) and executes the <span class="arg">procedure body</span>. The 
procedure applied to actual parameters evaluates then to the 
expression <span class="arg">expression</span> in the <?php linkTo("command","return","return");?> statement after the <span class="arg">procedure body</span>  
or to <?php linkTo("command","void","void");?>, if no return statement is given (i.e. a <?php linkTo("command","return","return");?> 
<?php linkTo("command","void","void");?> statement is implicitly given). 
</li><li>Sollya procedures defined by <?php linkTo("command","proc","proc");?> have no name. They can be bound 
to an identifier by assigning the procedure object a <?php linkTo("command","proc","proc");?> 
expression produces to an identifier. However, it is possible to use 
procedures without giving them any name. For instance, Sollya 
procedures, i.e. procedure objects, can be elements of lists. They can 
even be given as an argument to other internal Sollya procedures. See 
also <?php linkTo("command","procedure","procedure");?> on this subject. 
</li><li>Upon definition of a Sollya procedure using <?php linkTo("command","proc","proc");?>, no type check 
is performed. More precisely, the statements in <span class="arg">procedure body</span> are 
merely parsed but not interpreted upon procedure definition with 
<?php linkTo("command","proc","proc");?>. Type checks are performed once the procedure is applied to 
actual parameters or to <?php linkTo("command","void","void");?>. At this time, if the procedure was 
defined using several different formal parameters <span class="arg">formal parameter 1</span> 
through <span class="arg">formal parameter n</span>, it is checked whether the number of 
actual parameters corresponds to the number of formal parameters. If 
the procedure was defined using the syntax for a procedure with an 
arbitrary number of parameters by giving a <span class="arg">formal list parameter</span>, 
the number of actual arguments is not checked but only a list &lt;formal 
list parameter&gt; of appropriate length is built up. Type checks are 
further performed upon execution of each statement in <span class="arg">procedure body</span> 
and upon evaluation of the expression <span class="arg">expression</span> to be returned. 
<br><br> 
Procedures defined by <?php linkTo("command","proc","proc");?> containing a <?php linkTo("command","quit","quit");?> or <?php linkTo("command","restart","restart");?> command 
cannot be executed (i.e. applied). Upon application of a procedure, 
the Sollya interpreter checks beforehand for such a statement. If one 
is found, the application of the procedure to its arguments evaluates 
to <?php linkTo("command","error","error");?>. A warning is displayed. Remark that in contrast to other 
type or semantic correctness checks, this check is really performed 
before interpreting any other statement in the body of the procedure. 
</li><li>Through the <?php linkTo("command","var","var");?> keyword it is possible to declare local 
variables and thus to have full support of recursive procedures. This 
means a procedure defined using <?php linkTo("command","proc","proc");?> may contain in its <span class="arg">procedure body</span>  
an application of itself to some actual parameters: it suffices 
to assign the procedure (object) to an identifier with an appropriate 
name. 
</li><li>Sollya procedures defined using <?php linkTo("command","proc","proc");?> may return other 
procedures. Further <span class="arg">procedure body</span> may contain assignments of 
locally defined procedure objects to identifiers. See <?php linkTo("command","var","var");?> for the 
particular behaviour of local and global variables. 
</li><li>The expression <span class="arg">expression</span> returned by a procedure is evaluated with 
regard to Sollya commands, procedures and external 
procedures. Simplification may be performed.  However, an application 
of a procedure defined by <?php linkTo("command","proc","proc");?> to actual parameters evaluates to the 
expression <span class="arg">expression</span> that may contain the free global variable or 
that may be composed. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; succ = proc(n) { return n + 1; };<br> 
&nbsp;&nbsp;&nbsp;&gt; succ(5);<br> 
&nbsp;&nbsp;&nbsp;6<br> 
&nbsp;&nbsp;&nbsp;&gt; 3 + succ(0);<br> 
&nbsp;&nbsp;&nbsp;4<br> 
&nbsp;&nbsp;&nbsp;&gt; succ;<br> 
&nbsp;&nbsp;&nbsp;proc(n)<br> 
&nbsp;&nbsp;&nbsp;{<br> 
&nbsp;&nbsp;&nbsp;nop;<br> 
&nbsp;&nbsp;&nbsp;return (n) + (1);<br> 
&nbsp;&nbsp;&nbsp;}<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; add = proc(m,n) { var res; res := m + n; return res; };<br> 
&nbsp;&nbsp;&nbsp;&gt; add(5,6);<br> 
&nbsp;&nbsp;&nbsp;11<br> 
&nbsp;&nbsp;&nbsp;&gt; add;<br> 
&nbsp;&nbsp;&nbsp;proc(m, n)<br> 
&nbsp;&nbsp;&nbsp;{<br> 
&nbsp;&nbsp;&nbsp;var res;<br> 
&nbsp;&nbsp;&nbsp;res := (m) + (n);<br> 
&nbsp;&nbsp;&nbsp;return res;<br> 
&nbsp;&nbsp;&nbsp;}<br> 
&nbsp;&nbsp;&nbsp;&gt; verbosity = 1!;<br> 
&nbsp;&nbsp;&nbsp;&gt; add(3);<br> 
&nbsp;&nbsp;&nbsp;Warning: at least one of the given expressions or a subexpression is not correctly typed<br> 
&nbsp;&nbsp;&nbsp;or its evaluation has failed because of some error on a side-effect.<br> 
&nbsp;&nbsp;&nbsp;error<br> 
&nbsp;&nbsp;&nbsp;&gt; add(true,false);<br> 
&nbsp;&nbsp;&nbsp;Warning: at least one of the given expressions or a subexpression is not correctly typed<br> 
&nbsp;&nbsp;&nbsp;or its evaluation has failed because of some error on a side-effect.<br> 
&nbsp;&nbsp;&nbsp;Warning: the given expression or command could not be handled.<br> 
&nbsp;&nbsp;&nbsp;error<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; succ = proc(n) { return n + 1; };<br> 
&nbsp;&nbsp;&nbsp;&gt; succ(5);<br> 
&nbsp;&nbsp;&nbsp;6<br> 
&nbsp;&nbsp;&nbsp;&gt; succ(x);<br> 
&nbsp;&nbsp;&nbsp;1 + x<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 4: </h2> 
&nbsp;&nbsp;&nbsp;&gt; hey = proc() { print("Hello world."); };<br> 
&nbsp;&nbsp;&nbsp;&gt; hey();<br> 
&nbsp;&nbsp;&nbsp;Hello world.<br> 
&nbsp;&nbsp;&nbsp;&gt; print(hey());<br> 
&nbsp;&nbsp;&nbsp;Hello world.<br> 
&nbsp;&nbsp;&nbsp;void<br> 
&nbsp;&nbsp;&nbsp;&gt; hey;<br> 
&nbsp;&nbsp;&nbsp;proc()<br> 
&nbsp;&nbsp;&nbsp;{<br> 
&nbsp;&nbsp;&nbsp;print("Hello world.");<br> 
&nbsp;&nbsp;&nbsp;return void;<br> 
&nbsp;&nbsp;&nbsp;}<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 5: </h2> 
&nbsp;&nbsp;&nbsp;&gt; fac = proc(n) { var res; if (n == 0) then res := 1 else res := n * fac(n - 1); return res; };<br> 
&nbsp;&nbsp;&nbsp;&gt; fac(5);<br> 
&nbsp;&nbsp;&nbsp;120<br> 
&nbsp;&nbsp;&nbsp;&gt; fac(11);<br> 
&nbsp;&nbsp;&nbsp;39916800<br> 
&nbsp;&nbsp;&nbsp;&gt; fac;<br> 
&nbsp;&nbsp;&nbsp;proc(n)<br> 
&nbsp;&nbsp;&nbsp;{<br> 
&nbsp;&nbsp;&nbsp;var res;<br> 
&nbsp;&nbsp;&nbsp;if (n) == (0) then<br> 
&nbsp;&nbsp;&nbsp;res := 1<br> 
&nbsp;&nbsp;&nbsp;else<br> 
&nbsp;&nbsp;&nbsp;res := (n) * (fac((n) - (1)));<br> 
&nbsp;&nbsp;&nbsp;return res;<br> 
&nbsp;&nbsp;&nbsp;}<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 6: </h2> 
&nbsp;&nbsp;&nbsp;&gt; myprocs = [| proc(m,n) { return m + n; }, proc(m,n) { return m - n; } |];<br> 
&nbsp;&nbsp;&nbsp;&gt; (myprocs[0])(5,6);<br> 
&nbsp;&nbsp;&nbsp;11<br> 
&nbsp;&nbsp;&nbsp;&gt; (myprocs[1])(5,6);<br> 
&nbsp;&nbsp;&nbsp;-1<br> 
&nbsp;&nbsp;&nbsp;&gt; succ = proc(n) { return n + 1; };<br> 
&nbsp;&nbsp;&nbsp;&gt; pred = proc(n) { return n - 1; };<br> 
&nbsp;&nbsp;&nbsp;&gt; applier = proc(p,n) { return p(n); };<br> 
&nbsp;&nbsp;&nbsp;&gt; applier(succ,5);<br> 
&nbsp;&nbsp;&nbsp;6<br> 
&nbsp;&nbsp;&nbsp;&gt; applier(pred,5);<br> 
&nbsp;&nbsp;&nbsp;4<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 7: </h2> 
&nbsp;&nbsp;&nbsp;&gt; verbosity = 1!;<br> 
&nbsp;&nbsp;&nbsp;&gt; myquit = proc(n) { print(n); quit; };<br> 
&nbsp;&nbsp;&nbsp;&gt; myquit;<br> 
&nbsp;&nbsp;&nbsp;proc(n)<br> 
&nbsp;&nbsp;&nbsp;{<br> 
&nbsp;&nbsp;&nbsp;print(n);<br> 
&nbsp;&nbsp;&nbsp;quit;<br> 
&nbsp;&nbsp;&nbsp;return void;<br> 
&nbsp;&nbsp;&nbsp;}<br> 
&nbsp;&nbsp;&nbsp;&gt; myquit(5);<br> 
&nbsp;&nbsp;&nbsp;Warning: a quit or restart command may not be part of a procedure body.<br> 
&nbsp;&nbsp;&nbsp;The procedure will not be executed.<br> 
&nbsp;&nbsp;&nbsp;Warning: an error occurred while executing a procedure.<br> 
&nbsp;&nbsp;&nbsp;Warning: the given expression or command could not be handled.<br> 
&nbsp;&nbsp;&nbsp;error<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 8: </h2> 
&nbsp;&nbsp;&nbsp;&gt; printsucc = proc(n) { var succ; succ = proc(n) { return n + 1; }; print("Successor of",n,"is",succ(n)); };<br> 
&nbsp;&nbsp;&nbsp;&gt; printsucc(5);<br> 
&nbsp;&nbsp;&nbsp;Successor of 5 is 6<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 9: </h2> 
&nbsp;&nbsp;&nbsp;&gt; makeadd = proc(n) { var add; print("n =",n); add = proc(m,n) { return n + m; }; return add; };<br> 
&nbsp;&nbsp;&nbsp;&gt; makeadd(4);<br> 
&nbsp;&nbsp;&nbsp;n = 4<br> 
&nbsp;&nbsp;&nbsp;proc(m, n)<br> 
&nbsp;&nbsp;&nbsp;{<br> 
&nbsp;&nbsp;&nbsp;nop;<br> 
&nbsp;&nbsp;&nbsp;return (n) + (m);<br> 
&nbsp;&nbsp;&nbsp;}<br> 
&nbsp;&nbsp;&nbsp;&gt; (makeadd(4))(5,6);<br> 
&nbsp;&nbsp;&nbsp;n = 4<br> 
&nbsp;&nbsp;&nbsp;11<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 10: </h2> 
&nbsp;&nbsp;&nbsp;&gt; sumall = proc(L = ...) { var acc, i; acc = 0; for i in L do acc = acc + i; return acc; };<br> 
&nbsp;&nbsp;&nbsp;&gt; sumall;<br> 
&nbsp;&nbsp;&nbsp;proc(L = ...)<br> 
&nbsp;&nbsp;&nbsp;{<br> 
&nbsp;&nbsp;&nbsp;var acc, i;<br> 
&nbsp;&nbsp;&nbsp;acc = 0;<br> 
&nbsp;&nbsp;&nbsp;for i in L do<br> 
&nbsp;&nbsp;&nbsp;acc = (acc) + (i);<br> 
&nbsp;&nbsp;&nbsp;return acc;<br> 
&nbsp;&nbsp;&nbsp;}<br> 
&nbsp;&nbsp;&nbsp;&gt; sumall();<br> 
&nbsp;&nbsp;&nbsp;0<br> 
&nbsp;&nbsp;&nbsp;&gt; sumall(2);<br> 
&nbsp;&nbsp;&nbsp;2<br> 
&nbsp;&nbsp;&nbsp;&gt; sumall(2,5);<br> 
&nbsp;&nbsp;&nbsp;7<br> 
&nbsp;&nbsp;&nbsp;&gt; sumall(2,5,7,9,16);<br> 
&nbsp;&nbsp;&nbsp;39<br> 
&nbsp;&nbsp;&nbsp;&gt; sumall @ [|1,...,10|];<br> 
&nbsp;&nbsp;&nbsp;55<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","return","return");?>, <?php linkTo("command","externalproc","externalproc");?>, <?php linkTo("command","void","void");?>, <?php linkTo("command","quit","quit");?>, <?php linkTo("command","restart","restart");?>, <?php linkTo("command","var","var");?>, <?php linkTo("command","concat","@");?>, <?php linkTo("command","bind","bind");?>, <?php linkTo("command","error","error");?> 
</div> 
