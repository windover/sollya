<a name="approx"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","approx","~");?> 
<span class="smallDescription">floating-point evaluation of a constant expression 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","approx","~");?> <span class="arg">expression</span> : <span class="type">function</span> -&gt; <span class="type">constant</span></span> 
<span class="commandline"><?php linkTo("command","approx","~");?> <span class="arg">something</span> : <span class="type">any type</span> -&gt; <span class="type">any type</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">expression</span> stands for an expression that is a constant</li> 
<li><span class="arg">something</span> stands for some language element that is not a constant expression</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","approx","~");?> <span class="arg">expression</span> evaluates the <span class="arg">expression</span> that is a constant 
term to a floating-point constant. The evaluation may involve a 
rounding. If <span class="arg">expression</span> is not a constant, the evaluated constant is 
a faithful rounding of <span class="arg">expression</span> with <?php linkTo("command","precision","precision");?> bits, unless the 
<span class="arg">expression</span> is exactly 0 as a result of cancellation. In the 
latter case, a floating-point approximation of some (unknown) accuracy 
is returned. 
</li><li><?php linkTo("command","approx","~");?> does not do anything on all language elements that are not a 
constant expression.  In other words, it behaves like the identity 
function on any type that is not a constant expression. It can hence 
be used in any place where one wants to be sure that expressions are 
simplified using floating-point computations to constants of a known 
precision, regardless of the type of actual language elements. 
</li><li><?php linkTo("command","approx","~");?> <?php linkTo("command","error","error");?> evaluates to error and provokes a warning. 
</li><li><?php linkTo("command","approx","~");?> is a prefix operator not requiring parentheses. Its 
precedence is the same as for the unary + and - 
operators. It cannot be repeatedly used without brackets. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; print(exp(5));<br> 
&nbsp;&nbsp;&nbsp;exp(5)<br> 
&nbsp;&nbsp;&nbsp;&gt; print(~ exp(5));<br> 
&nbsp;&nbsp;&nbsp;1.48413159102576603421115580040552279623487667593878e2<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; autosimplify = off!;<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; print(~sin(5 * pi));<br> 
&nbsp;&nbsp;&nbsp;0<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 4: </h2> 
&nbsp;&nbsp;&nbsp;&gt; print(~exp(x));<br> 
&nbsp;&nbsp;&nbsp;exp(x)<br> 
&nbsp;&nbsp;&nbsp;&gt; print(~ "Hello");<br> 
&nbsp;&nbsp;&nbsp;Hello<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 5: </h2> 
&nbsp;&nbsp;&nbsp;&gt; print(~exp(x*5*Pi));<br> 
&nbsp;&nbsp;&nbsp;exp((pi) * 5 * x)<br> 
&nbsp;&nbsp;&nbsp;&gt; print(exp(x* ~(5*Pi)));<br> 
&nbsp;&nbsp;&nbsp;exp(x * 1.57079632679489661923132169163975144209858469968757e1)<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 6: </h2> 
&nbsp;&nbsp;&nbsp;&gt; print(~exp(5)*x);<br> 
&nbsp;&nbsp;&nbsp;1.48413159102576603421115580040552279623487667593878e2 * x<br> 
&nbsp;&nbsp;&nbsp;&gt; print( (~exp(5))*x);<br> 
&nbsp;&nbsp;&nbsp;1.48413159102576603421115580040552279623487667593878e2 * x<br> 
&nbsp;&nbsp;&nbsp;&gt; print(~(exp(5)*x));<br> 
&nbsp;&nbsp;&nbsp;exp(5) * x<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","evaluate","evaluate");?>, <?php linkTo("command","prec","prec");?>, <?php linkTo("command","error","error");?> 
</div> 
