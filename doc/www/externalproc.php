<a name="externalproc"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","externalproc","externalproc");?> 
<span class="smallDescription">binds an external code to a Sollya procedure 
</span> 
</div> 
<div class="divLibraryName"> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","externalproc","externalproc");?>(<span class="arg">identifier</span>, <span class="arg">filename</span>, <span class="arg">argumenttype</span> -&gt; <span class="arg">resulttype</span>) : (<span class="type">identifier type</span>, <span class="type">string</span>, <span class="type">type type</span>, <span class="type">type type</span>) -&gt; <span class="type">void</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">identifier</span> represents the identifier the code is to be bound to</li> 
<li><span class="arg">filename</span> of type <span class="type">string</span> represents the name of the object file where the code of procedure can be found</li> 
<li><span class="arg">argumenttype</span> represents a definition of the types of the arguments of the Sollya procedure and the external code</li> 
<li><span class="arg">resulttype</span> represents a definition of the result type of the external code</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","externalproc","externalproc");?> allows for binding the Sollya identifier 
<span class="arg">identifier</span> to an external code.  After this binding, when Sollya 
encounters <span class="arg">identifier</span> applied to a list of actual parameters, it 
will evaluate these parameters and call the external code with these 
parameters. If the external code indicated success, it will receive 
the result produced by the external code, transform it to Sollya's 
internal representation and return it. 
<br><br> 
In order to allow correct evaluation and typing of the data in 
parameter and in result to be passed to and received from the external 
code, <?php linkTo("command","externalproc","externalproc");?> has a third parameter <span class="arg">argumenttype</span> -&gt; <span class="arg">resulttype</span>. 
Both <span class="arg">argumenttype</span> and <span class="arg">resulttype</span> are one of <?php linkTo("command","void","void");?>, <?php linkTo("command","constant","constant");?>, 
<?php linkTo("command","function","function");?>, <?php linkTo("command","range","range");?>, <?php linkTo("command","integer","integer");?>, <?php linkTo("command","string","string");?>, <?php linkTo("command","boolean","boolean");?>, <?php linkTo("command","listof","list of");?> <?php linkTo("command","constant","constant");?>, <?php linkTo("command","listof","list of");?> <?php linkTo("command","function","function");?>,  
<?php linkTo("command","listof","list of");?> <?php linkTo("command","range","range");?>, <?php linkTo("command","listof","list of");?> <?php linkTo("command","integer","integer");?>, <?php linkTo("command","listof","list of");?> <?php linkTo("command","string","string");?>, <?php linkTo("command","listof","list of");?> <?php linkTo("command","boolean","boolean");?>. 
<br><br> 
If upon a usage of a procedure bound to an external procedure the type 
of the actual parameters given or its number is not correct, Sollya 
produces a type error. An external function not applied to arguments 
represents itself and prints out with its argument and result types. 
<br><br> 
The external function is supposed to return an integer indicating 
success.  It returns its result depending on its Sollya result type 
as follows. Here, the external procedure is assumed to be implemented 
as a C function. 
<br><br> 
If the Sollya result type is void, the C function has no pointer 
argument for the result.  If the Sollya result type is <?php linkTo("command","constant","constant");?>, the 
first argument of the C function is of C type mpfr_t *, the result is 
returned by affecting the MPFR variable.  If the Sollya result type 
is <?php linkTo("command","function","function");?>, the first argument of the C function is of C type node**, 
the result is returned by the node * pointed with a new node *. 
If the Sollya result type is <?php linkTo("command","range","range");?>, the first argument of the C 
function is of C type mpfi_t *, the result is returned by affecting 
the interval-arithmetic variable.  If the Sollya result type is <?php linkTo("command","integer","integer");?>, the first 
argument of the C function is of C type int *, the result is returned 
by affecting the int variable.  If the Sollya result type is <?php linkTo("command","string","string");?>, 
the first argument of the C function is of C type char **, the result 
is returned by the char * pointed with a new char *.  If the Sollya 
result type is <?php linkTo("command","boolean","boolean");?>, the first argument of the C function is of C 
type int *, the result is returned by affecting the int variable with 
a boolean value.  If the Sollya result type is <?php linkTo("command","listof","list of");?> type, the 
first argument of the C function is of C type chain **, the result is 
returned by the chain * pointed with a new chain *.  This chain 
contains for Sollya type <?php linkTo("command","constant","constant");?> pointers mpfr_t * to new MPFR 
variables, for Sollya type <?php linkTo("command","function","function");?> pointers node * to new nodes, for 
Sollya type <?php linkTo("command","range","range");?> pointers mpfi_t *  to new interval-arithmetic variables, for 
Sollya type <?php linkTo("command","integer","integer");?> pointers int * to new int variables for Sollya 
type <?php linkTo("command","string","string");?> pointers char * to new char * variables and for Sollya 
type <?php linkTo("command","boolean","boolean");?> pointers int * to new int variables representing boolean 
values. 
<br><br>	        
The external procedure affects its possible pointer argument if and 
only if it succeeds.  This means, if the function returns an integer 
indicating failure, it does not leak any memory to the encompassing 
environment. 
<br><br> 
The external procedure receives its arguments as follows: If the 
Sollya argument type is <?php linkTo("command","void","void");?>, no argument array is given.  Otherwise 
the C function receives a C void ** argument representing an array of 
size equal to the arity of the function where each entry (of C type 
void *) represents a value with a C type depending on the 
corresponding Sollya type. If the Sollya type is <?php linkTo("command","constant","constant");?>, the C 
type the void * is to be casted to is mpfr_t *.  If the Sollya type 
is <?php linkTo("command","function","function");?>, the C type the void * is to be casted to is node *.  If 
the Sollya type is <?php linkTo("command","range","range");?>, the C type the void * is to be casted to is 
mpfi_t *.  If the Sollya type is <?php linkTo("command","integer","integer");?>, the C type the void * is to 
be casted to is int *.  If the Sollya type is <?php linkTo("command","string","string");?>, the C type the 
void * is to be casted to is char *.  If the Sollya type is <?php linkTo("command","boolean","boolean");?>, 
the C type the void * is to be casted to is int *.  If the Sollya 
type is <?php linkTo("command","listof","list of");?> type, the C type the void * is to be casted to is 
chain *.  Here depending on type, the values in the chain are to be 
casted to mpfr_t *  for Sollya type <?php linkTo("command","constant","constant");?>, node * for Sollya type 
<?php linkTo("command","function","function");?>, mpfi_t * for Sollya type <?php linkTo("command","range","range");?>, int * for Sollya type 
<?php linkTo("command","integer","integer");?>, char * for Sollya type <?php linkTo("command","string","string");?> and int * for Sollya type 
<?php linkTo("command","boolean","boolean");?>. 
<br><br> 
The external procedure is not supposed to alter the memory pointed by 
its array argument void **. 
<br><br> 
In both directions (argument and result values), empty lists are 
represented by chain * NULL pointers. 
<br><br> 
In contrast to internal procedures, externally bounded procedures can 
be considered to be objects inside Sollya that can be assigned to other 
variables, stored in list etc. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; bashexecute("gcc -fPIC -Wall -c externalprocexample.c");<br> 
&nbsp;&nbsp;&nbsp;&gt; bashexecute("gcc -fPIC -shared -o externalprocexample externalprocexample.o");<br> 
&nbsp;&nbsp;&nbsp;&gt; externalproc(foo, "./externalprocexample", (integer, integer) -&gt; integer);<br> 
&nbsp;&nbsp;&nbsp;&gt; foo;<br> 
&nbsp;&nbsp;&nbsp;foo(integer, integer) -&gt; integer<br> 
&nbsp;&nbsp;&nbsp;&gt; foo(5, 6);<br> 
&nbsp;&nbsp;&nbsp;11<br> 
&nbsp;&nbsp;&nbsp;&gt; verbosity = 1!;<br> 
&nbsp;&nbsp;&nbsp;&gt; foo();<br> 
&nbsp;&nbsp;&nbsp;Warning: at least one of the given expressions or a subexpression is not correctly typed<br> 
&nbsp;&nbsp;&nbsp;or its evaluation has failed because of some error on a side-effect.<br> 
&nbsp;&nbsp;&nbsp;error<br> 
&nbsp;&nbsp;&nbsp;&gt; a = foo;<br> 
&nbsp;&nbsp;&nbsp;&gt; a(5,6);<br> 
&nbsp;&nbsp;&nbsp;11<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","library","library");?>, <?php linkTo("command","libraryconstant","libraryconstant");?>, <?php linkTo("command","externalplot","externalplot");?>, <?php linkTo("command","bashexecute","bashexecute");?>, <?php linkTo("command","void","void");?>, <?php linkTo("command","constant","constant");?>, <?php linkTo("command","function","function");?>, <?php linkTo("command","range","range");?>, <?php linkTo("command","integer","integer");?>, <?php linkTo("command","string","string");?>, <?php linkTo("command","boolean","boolean");?>, <?php linkTo("command","listof","list of");?> 
</div> 
