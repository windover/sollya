<a name="bind"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","bind","bind");?> 
<span class="smallDescription">partially applies a procedure to an argument, returning a procedure with one argument less 
</span> 
</div> 
<div class="divLibraryName"> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","bind","bind");?>(<span class="arg">proc</span>, <span class="arg">ident</span>, <span class="arg">obj</span>) : (<span class="type">procedure</span>, <span class="type">identifier type</span>, <span class="type">any type</span>) -&gt; <span class="type">procedure</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">proc</span> is a procedure to be partially applied to an argument</li> 
<li><span class="arg">ident</span> is one of the formal arguments of <span class="arg">proc</span></li> 
<li><span class="arg">obj</span> is any Sollya object <span class="arg">ident</span> is to be bound to</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","bind","bind");?> allows a formal parameter <span class="arg">ident</span> of a procedure <span class="arg">proc</span> to  
be bound to an object <span class="arg">obj</span>, hence <span class="arg">proc</span> to be partially applied. 
The result of this curryfied application, returned by <?php linkTo("command","bind","bind");?>, is  
a procedure with one argument less. This way, <?php linkTo("command","bind","bind");?> permits  
specialization of a generic procedure, parameterized e.g. by a function 
or range. 
</li><li>In the case when <span class="arg">proc</span> does not have a formal parameter named  
<span class="arg">ident</span>, <?php linkTo("command","bind","bind");?> prints a warning and returns the procedure  
<span class="arg">proc</span> unmodified.  
</li><li><?php linkTo("command","bind","bind");?> always returns a procedure, even if <span class="arg">proc</span> only has one  
argument, which gets bound to <span class="arg">ident</span>. In this case, <?php linkTo("command","bind","bind");?> 
returns a procedure which does not take any argument. Hence  
evaluation, which might provoke side effects, is only performed 
once the procedure gets used. 
</li><li><?php linkTo("command","bind","bind");?> does not work on procedures with an arbitrary number 
of arguments. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; procedure add(X,Y) { return X + Y; };<br> 
&nbsp;&nbsp;&nbsp;&gt; succ = bind(add,X,1);<br> 
&nbsp;&nbsp;&nbsp;&gt; succ(5);<br> 
&nbsp;&nbsp;&nbsp;6<br> 
&nbsp;&nbsp;&nbsp;&gt; succ;<br> 
&nbsp;&nbsp;&nbsp;proc(Y)<br> 
&nbsp;&nbsp;&nbsp;{<br> 
&nbsp;&nbsp;&nbsp;nop;<br> 
&nbsp;&nbsp;&nbsp;return (proc(X, Y)<br> 
&nbsp;&nbsp;&nbsp;{<br> 
&nbsp;&nbsp;&nbsp;nop;<br> 
&nbsp;&nbsp;&nbsp;return (X) + (Y);<br> 
&nbsp;&nbsp;&nbsp;})(1, Y);<br> 
&nbsp;&nbsp;&nbsp;}<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; procedure add(X,Y) { return X + Y; };<br> 
&nbsp;&nbsp;&nbsp;&gt; succ = bind(add,X,1);<br> 
&nbsp;&nbsp;&nbsp;&gt; five = bind(succ,Y,4);<br> 
&nbsp;&nbsp;&nbsp;&gt; five();<br> 
&nbsp;&nbsp;&nbsp;5<br> 
&nbsp;&nbsp;&nbsp;&gt; five;<br> 
&nbsp;&nbsp;&nbsp;proc()<br> 
&nbsp;&nbsp;&nbsp;{<br> 
&nbsp;&nbsp;&nbsp;nop;<br> 
&nbsp;&nbsp;&nbsp;return (proc(Y)<br> 
&nbsp;&nbsp;&nbsp;{<br> 
&nbsp;&nbsp;&nbsp;nop;<br> 
&nbsp;&nbsp;&nbsp;return (proc(X, Y)<br> 
&nbsp;&nbsp;&nbsp;{<br> 
&nbsp;&nbsp;&nbsp;nop;<br> 
&nbsp;&nbsp;&nbsp;return (X) + (Y);<br> 
&nbsp;&nbsp;&nbsp;})(1, Y);<br> 
&nbsp;&nbsp;&nbsp;})(4);<br> 
&nbsp;&nbsp;&nbsp;}<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; verbosity = 1!;<br> 
&nbsp;&nbsp;&nbsp;&gt; procedure add(X,Y) { return X + Y; };<br> 
&nbsp;&nbsp;&nbsp;&gt; foo = bind(add,R,1);<br> 
&nbsp;&nbsp;&nbsp;Warning: the given procedure has no argument named "R". The procedure is returned unchanged.<br> 
&nbsp;&nbsp;&nbsp;&gt; foo;<br> 
&nbsp;&nbsp;&nbsp;proc(X, Y)<br> 
&nbsp;&nbsp;&nbsp;{<br> 
&nbsp;&nbsp;&nbsp;nop;<br> 
&nbsp;&nbsp;&nbsp;return (X) + (Y);<br> 
&nbsp;&nbsp;&nbsp;}<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","procedure","procedure");?>, <?php linkTo("command","proc","proc");?>, <?php linkTo("command","function","function");?>, <?php linkTo("command","concat","@");?> 
</div> 
