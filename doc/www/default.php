<a name="default"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","default","default");?> 
<span class="smallDescription">default value for some commands. 
</span> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","default","default");?> is a special value and is replaced by something depending on the  
context where it is used. It can often be used as a joker, when you want to  
specify one of the optional parameters of a command and not the others: set  
the value of uninteresting parameters to <?php linkTo("command","default","default");?>. 
</li><li>Global variables can be reset by affecting them the special value <?php linkTo("command","default","default");?>. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; p = remez(exp(x),5,[0;1],default,1e-5);<br> 
&nbsp;&nbsp;&nbsp;&gt; q = remez(exp(x),5,[0;1],1,1e-5);<br> 
&nbsp;&nbsp;&nbsp;&gt; p==q;<br> 
&nbsp;&nbsp;&nbsp;true<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; prec;<br> 
&nbsp;&nbsp;&nbsp;165<br> 
&nbsp;&nbsp;&nbsp;&gt; prec=200;<br> 
&nbsp;&nbsp;&nbsp;The precision has been set to 200 bits.<br> 
</div> 
</div> 
