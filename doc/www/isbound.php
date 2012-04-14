<a name="isbound"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","isbound","isbound");?> 
<span class="smallDescription">indicates whether a variable is bound or not. 
</span> 
</div> 
<div class="divLibraryName"> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","isbound","isbound");?>(<span class="arg">ident</span>) : <span class="type">boolean</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">ident</span> is a name.</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","isbound","isbound");?>(<span class="arg">ident</span>) returns a boolean value indicating whether the name <span class="arg">ident</span> 
is used or not to represent a variable. It returns true when <span class="arg">ident</span> is the  
name used to represent the global variable or if the name is currently used 
to refer to a (possibly local) variable. 
</li><li>When a variable is defined in a block and has not been defined outside,  
<?php linkTo("command","isbound","isbound");?> returns true when called inside the block, and false outside. 
Note that <?php linkTo("command","isbound","isbound");?> returns true as soon as a variable has been declared with  
<?php linkTo("command","var","var");?>, even if no value is actually stored in it. 
</li><li>If <span class="arg">ident1</span> is bound to a variable and if <span class="arg">ident2</span> refers to the global  
variable, the command <?php linkTo("command","rename","rename");?>(<span class="arg">ident2</span>, <span class="arg">ident1</span>) hides the value of <span class="arg">ident1</span> 
which becomes the global variable. However, if the global variable is again 
renamed, <span class="arg">ident1</span> gets its value back. In this case, <?php linkTo("command","isbound","isbound");?>(<span class="arg">ident1</span>) returns 
true. If <span class="arg">ident1</span> was not bound before, <?php linkTo("command","isbound","isbound");?>(<span class="arg">ident1</span>) returns false after 
that <span class="arg">ident1</span> has been renamed. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; isbound(x);<br> 
&nbsp;&nbsp;&nbsp;false<br> 
&nbsp;&nbsp;&nbsp;&gt; isbound(f);<br> 
&nbsp;&nbsp;&nbsp;false<br> 
&nbsp;&nbsp;&nbsp;&gt; isbound(g);<br> 
&nbsp;&nbsp;&nbsp;false<br> 
&nbsp;&nbsp;&nbsp;&gt; f=sin(x);<br> 
&nbsp;&nbsp;&nbsp;&gt; isbound(x);<br> 
&nbsp;&nbsp;&nbsp;true<br> 
&nbsp;&nbsp;&nbsp;&gt; isbound(f);<br> 
&nbsp;&nbsp;&nbsp;true<br> 
&nbsp;&nbsp;&nbsp;&gt; isbound(g);<br> 
&nbsp;&nbsp;&nbsp;false<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; isbound(a);<br> 
&nbsp;&nbsp;&nbsp;false<br> 
&nbsp;&nbsp;&nbsp;&gt; { var a; isbound(a); };<br> 
&nbsp;&nbsp;&nbsp;true<br> 
&nbsp;&nbsp;&nbsp;&gt; isbound(a);<br> 
&nbsp;&nbsp;&nbsp;false<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; f=sin(x);<br> 
&nbsp;&nbsp;&nbsp;&gt; isbound(x);<br> 
&nbsp;&nbsp;&nbsp;true<br> 
&nbsp;&nbsp;&nbsp;&gt; rename(x,y);<br> 
&nbsp;&nbsp;&nbsp;&gt; isbound(x);<br> 
&nbsp;&nbsp;&nbsp;false<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 4: </h2> 
&nbsp;&nbsp;&nbsp;&gt; x=1;<br> 
&nbsp;&nbsp;&nbsp;&gt; f=sin(y);<br> 
&nbsp;&nbsp;&nbsp;&gt; rename(y,x);<br> 
&nbsp;&nbsp;&nbsp;&gt; f;<br> 
&nbsp;&nbsp;&nbsp;sin(x)<br> 
&nbsp;&nbsp;&nbsp;&gt; x;<br> 
&nbsp;&nbsp;&nbsp;x<br> 
&nbsp;&nbsp;&nbsp;&gt; isbound(x);<br> 
&nbsp;&nbsp;&nbsp;true<br> 
&nbsp;&nbsp;&nbsp;&gt; rename(x,y);<br> 
&nbsp;&nbsp;&nbsp;&gt; isbound(x);<br> 
&nbsp;&nbsp;&nbsp;true<br> 
&nbsp;&nbsp;&nbsp;&gt; x;<br> 
&nbsp;&nbsp;&nbsp;1<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","rename","rename");?> 
</div> 
