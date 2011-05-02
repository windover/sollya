<a name="pi"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","pi","pi");?> 
<span class="smallDescription">the constant Pi. 
</span> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","pi","pi");?> is the constant Pi, defined as half the period of sine and cosine. 
</li><li>In Sollya, <?php linkTo("command","pi","pi");?> is considered a 0-ary function. This way, the constant  
is not evaluated at the time of its definition but at the time of its use. For  
instance, when you define a constant or a function relating to Pi, the current 
precision at the time of the definition does not matter. What is important is  
the current precision when you evaluate the function or the constant value. 
</li><li>Remark that when you define an interval, the bounds are first evaluated and  
then the interval is defined. In this case, <?php linkTo("command","pi","pi");?> will be evaluated as any  
other constant value at the definition time of the interval, thus using the  
current precision at this time. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; verbosity=1!; prec=12!;<br> 
&nbsp;&nbsp;&nbsp;&gt; a = 2*pi;<br> 
&nbsp;&nbsp;&nbsp;&gt; a;<br> 
&nbsp;&nbsp;&nbsp;Warning: rounding has happened. The value displayed is a faithful rounding of the true result.<br> 
&nbsp;&nbsp;&nbsp;6.283<br> 
&nbsp;&nbsp;&nbsp;&gt; prec=20!;<br> 
&nbsp;&nbsp;&nbsp;&gt; a;<br> 
&nbsp;&nbsp;&nbsp;Warning: rounding has happened. The value displayed is a faithful rounding of the true result.<br> 
&nbsp;&nbsp;&nbsp;6.283187<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; display=binary;<br> 
&nbsp;&nbsp;&nbsp;Display mode is binary numbers.<br> 
&nbsp;&nbsp;&nbsp;&gt; prec=12!;<br> 
&nbsp;&nbsp;&nbsp;&gt; d = [pi; 5];<br> 
&nbsp;&nbsp;&nbsp;&gt; d;<br> 
&nbsp;&nbsp;&nbsp;[1.1001001_2 * 2^(1);1.01_2 * 2^(2)]<br> 
&nbsp;&nbsp;&nbsp;&gt; prec=20!;<br> 
&nbsp;&nbsp;&nbsp;&gt; d;<br> 
&nbsp;&nbsp;&nbsp;[1.1001001_2 * 2^(1);1.01_2 * 2^(2)]<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","cos","cos");?>, <?php linkTo("command","sin","sin");?>, <?php linkTo("command","tan","tan");?>, <?php linkTo("command","asin","asin");?>, <?php linkTo("command","acos","acos");?>, <?php linkTo("command","atan","atan");?>, <?php linkTo("command","evaluate","evaluate");?>, <?php linkTo("command","prec","prec");?>, <?php linkTo("command","libraryconstant","libraryconstant");?> 
</div> 
