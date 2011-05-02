<a name="void"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","void","void");?> 
<span class="smallDescription">the functional result of a side-effect or empty argument resp. the corresponding type 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","void","void");?> : <span class="type">void</span> | <span class="type">type type</span></span> 
 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>The variable <?php linkTo("command","void","void");?> represents the functional result of a 
side-effect or an empty argument.  It is used only in combination with 
the applications of procedures or identifiers bound through 
<?php linkTo("command","externalproc","externalproc");?> to external procedures. 
<br><br> 
The <?php linkTo("command","void","void");?> result produced by a procedure or an external procedure 
is not printed at the prompt. However, it is possible to print it out 
in a print statement or in complex data types such as lists. 
<br><br> 
The <?php linkTo("command","void","void");?> argument is implicit when giving no argument to a 
procedure or an external procedure when applied. It can nevertheless be given 
explicitly.  For example, suppose that foo is a procedure or an 
external procedure with a void argument. Then foo() and foo(void) are 
correct calls to foo. Here, a distinction must be made for procedures having an 
arbitrary number of arguments. In this case, an implicit <?php linkTo("command","void","void");?> 
as the only parameter to a call of such a procedure gets converted into  
an empty list of arguments, an explicit <?php linkTo("command","void","void");?> gets passed as-is in the 
formal list of parameters the procedure receives. 
</li><li><?php linkTo("command","void","void");?> is used also as a type identifier for 
<?php linkTo("command","externalproc","externalproc");?>. Typically, an external procedure taking <?php linkTo("command","void","void");?> as an 
argument or returning <?php linkTo("command","void","void");?> is bound with a signature <?php linkTo("command","void","void");?> -&gt; 
some type or some type -&gt; <?php linkTo("command","void","void");?>. See <?php linkTo("command","externalproc","externalproc");?> for more 
details. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; print(void);<br> 
&nbsp;&nbsp;&nbsp;void<br> 
&nbsp;&nbsp;&nbsp;&gt; void;<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; hey = proc() { print("Hello world."); };<br> 
&nbsp;&nbsp;&nbsp;&gt; hey;<br> 
&nbsp;&nbsp;&nbsp;proc()<br> 
&nbsp;&nbsp;&nbsp;{<br> 
&nbsp;&nbsp;&nbsp;print("Hello world.");<br> 
&nbsp;&nbsp;&nbsp;return void;<br> 
&nbsp;&nbsp;&nbsp;}<br> 
&nbsp;&nbsp;&nbsp;&gt; hey();<br> 
&nbsp;&nbsp;&nbsp;Hello world.<br> 
&nbsp;&nbsp;&nbsp;&gt; hey(void);<br> 
&nbsp;&nbsp;&nbsp;Hello world.<br> 
&nbsp;&nbsp;&nbsp;&gt; print(hey());<br> 
&nbsp;&nbsp;&nbsp;Hello world.<br> 
&nbsp;&nbsp;&nbsp;void<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; bashexecute("gcc -fPIC -Wall -c externalprocvoidexample.c");<br> 
&nbsp;&nbsp;&nbsp;&gt; bashexecute("gcc -fPIC -shared -o externalprocvoidexample externalprocvoidexample.o");<br> 
&nbsp;&nbsp;&nbsp;&gt; externalproc(foo, "./externalprocvoidexample", void -&gt; void);<br> 
&nbsp;&nbsp;&nbsp;&gt; foo;<br> 
&nbsp;&nbsp;&nbsp;foo(void) -&gt; void<br> 
&nbsp;&nbsp;&nbsp;&gt; foo();<br> 
&nbsp;&nbsp;&nbsp;Hello from the external world.<br> 
&nbsp;&nbsp;&nbsp;&gt; foo(void);<br> 
&nbsp;&nbsp;&nbsp;Hello from the external world.<br> 
&nbsp;&nbsp;&nbsp;&gt; print(foo());<br> 
&nbsp;&nbsp;&nbsp;Hello from the external world.<br> 
&nbsp;&nbsp;&nbsp;void<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 4: </h2> 
&nbsp;&nbsp;&nbsp;&gt; procedure blub(L = ...) { print("Argument list:", L); };<br> 
&nbsp;&nbsp;&nbsp;&gt; blub(1);<br> 
&nbsp;&nbsp;&nbsp;Argument list: [|1|]<br> 
&nbsp;&nbsp;&nbsp;&gt; blub();<br> 
&nbsp;&nbsp;&nbsp;Argument list: [| |]<br> 
&nbsp;&nbsp;&nbsp;&gt; blub(void); <br> 
&nbsp;&nbsp;&nbsp;Argument list: [|void|]<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","error","error");?>, <?php linkTo("command","proc","proc");?>, <?php linkTo("command","externalproc","externalproc");?> 
</div> 
