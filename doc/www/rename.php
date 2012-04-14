<a name="rename"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","rename","rename");?> 
<span class="smallDescription">rename the free variable. 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library name:</h2> 
<span class="commandline type">void sollya_lib_name_free_variable(const char *)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","rename","rename");?>(<span class="arg">ident1</span>,<span class="arg">ident2</span>) : <span class="type">void</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">ident1</span> is the current name of the free variable.</li> 
<li><span class="arg">ident2</span> is a fresh name.</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","rename","rename");?> permits a change of the name of the free variable. Sollya can handle 
only one free variable at a time. The first time in a session that an 
unbound name is used in a context where it can be interpreted as a free 
variable, the name is used to represent the free variable of Sollya. In the 
following, this name can be changed using <?php linkTo("command","rename","rename");?>. 
</li><li>Be careful: if <span class="arg">ident2</span> has been set before, its value will be lost. Use 
the command <?php linkTo("command","isbound","isbound");?> to know if <span class="arg">ident2</span> is already used or not. 
</li><li>If <span class="arg">ident1</span> is not the current name of the free variable, an error occurs. 
</li><li>If <?php linkTo("command","rename","rename");?> is used at a time when the name of the free variable has not been 
defined, <span class="arg">ident1</span> is just ignored and the name of the free variable is set 
to <span class="arg">ident2</span>. 
</li><li>It is always possible to use the special keyword _x_ to denote the free 
variable. Hence <span class="arg">ident1</span> can be _x_. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; f=sin(x);<br> 
&nbsp;&nbsp;&nbsp;&gt; f;<br> 
&nbsp;&nbsp;&nbsp;sin(x)<br> 
&nbsp;&nbsp;&nbsp;&gt; rename(x,y);<br> 
&nbsp;&nbsp;&nbsp;&gt; f;<br> 
&nbsp;&nbsp;&nbsp;sin(y)<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; a=1;<br> 
&nbsp;&nbsp;&nbsp;&gt; f=sin(x);<br> 
&nbsp;&nbsp;&nbsp;&gt; rename(x,a);<br> 
&nbsp;&nbsp;&nbsp;&gt; a;<br> 
&nbsp;&nbsp;&nbsp;a<br> 
&nbsp;&nbsp;&nbsp;&gt; f;<br> 
&nbsp;&nbsp;&nbsp;sin(a)<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; verbosity=1!;<br> 
&nbsp;&nbsp;&nbsp;&gt; f=sin(x);<br> 
&nbsp;&nbsp;&nbsp;&gt; rename(y, z);<br> 
&nbsp;&nbsp;&nbsp;Warning: the current free variable is named "x" and not "y". Can only rename the free variable.<br> 
&nbsp;&nbsp;&nbsp;The last command will have no effect.<br> 
&nbsp;&nbsp;&nbsp;&gt; rename(_x_, z);<br> 
&nbsp;&nbsp;&nbsp;Information: the free variable has been renamed from "x" to "z".<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 4: </h2> 
&nbsp;&nbsp;&nbsp;&gt; verbosity=1!;<br> 
&nbsp;&nbsp;&nbsp;&gt; rename(x,y);<br> 
&nbsp;&nbsp;&nbsp;Information: the free variable has been named "y".<br> 
&nbsp;&nbsp;&nbsp;&gt; isbound(x);<br> 
&nbsp;&nbsp;&nbsp;false<br> 
&nbsp;&nbsp;&nbsp;&gt; isbound(y);<br> 
&nbsp;&nbsp;&nbsp;true<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","isbound","isbound");?> 
</div> 
