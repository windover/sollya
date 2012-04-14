<a name="substitute"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","substitute","substitute");?> 
<span class="smallDescription">replace the occurrences of the free variable in an expression. 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library name:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_substitute(sollya_obj_t, sollya_obj_t)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","substitute","substitute");?>(<span class="arg">f</span>,<span class="arg">g</span>) : (<span class="type">function</span>, <span class="type">function</span>) -&gt; <span class="type">function</span></span> 
<span class="commandline"><?php linkTo("command","substitute","substitute");?>(<span class="arg">f</span>,<span class="arg">t</span>) : (<span class="type">function</span>, <span class="type">constant</span>) -&gt; <span class="type">constant</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">f</span> is a function.</li> 
<li><span class="arg">g</span> is a function.</li> 
<li><span class="arg">t</span> is a real number.</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","substitute","substitute");?>(<span class="arg">f</span>, <span class="arg">g</span>) produces the function (f o g) : x -&gt; f(g(x)). 
</li><li><?php linkTo("command","substitute","substitute");?>(<span class="arg">f</span>, <span class="arg">t</span>) is the constant f(t). Note that the constant is 
represented by its expression until it has been evaluated (exactly the same 
way as if you type the expression <span class="arg">f</span> replacing instances of the free variable  
by <span class="arg">t</span>). 
</li><li>If <span class="arg">f</span> is stored in a variable <span class="arg">F</span>, the effect of the commands <?php linkTo("command","substitute","substitute");?>(<span class="arg">F</span>,<span class="arg">g</span>) or <?php linkTo("command","substitute","substitute");?>(<span class="arg">F</span>,<span class="arg">t</span>) is absolutely equivalent to  
writing <span class="arg">F(g)</span> resp. <span class="arg">F(t)</span>. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; f=sin(x);<br> 
&nbsp;&nbsp;&nbsp;&gt; g=cos(x);<br> 
&nbsp;&nbsp;&nbsp;&gt; substitute(f,g);<br> 
&nbsp;&nbsp;&nbsp;sin(cos(x))<br> 
&nbsp;&nbsp;&nbsp;&gt; f(g);<br> 
&nbsp;&nbsp;&nbsp;sin(cos(x))<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; a=1;<br> 
&nbsp;&nbsp;&nbsp;&gt; f=sin(x);<br> 
&nbsp;&nbsp;&nbsp;&gt; substitute(f,a);<br> 
&nbsp;&nbsp;&nbsp;0.84147098480789650665250232163029899962256306079837<br> 
&nbsp;&nbsp;&nbsp;&gt; f(a);<br> 
&nbsp;&nbsp;&nbsp;0.84147098480789650665250232163029899962256306079837<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","evaluate","evaluate");?>, <?php linkTo("command","composepolynomials","composepolynomials");?> 
</div> 
