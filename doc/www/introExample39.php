<div class="divExample">
&nbsp;&nbsp;&nbsp;&gt; evaluate(exp(x),[-infty;0]);<br>
&nbsp;&nbsp;&nbsp;[0;1]<br>
&nbsp;&nbsp;&nbsp;&gt; dirtyinfnorm(exp(x),[-infty;0]);<br>
&nbsp;&nbsp;&nbsp;Warning: a bound of the interval is infinite or NaN.<br>
&nbsp;&nbsp;&nbsp;This command cannot handle such intervals.<br>
&nbsp;&nbsp;&nbsp;@NaN@<br>
&nbsp;&nbsp;&nbsp;&gt; <br>
&nbsp;&nbsp;&nbsp;&gt; f = log(x);<br>
&nbsp;&nbsp;&nbsp;&gt; [f(0); f(1)];<br>
&nbsp;&nbsp;&nbsp;Warning: the given expression is not a constant but an expression to evaluate<br>
&nbsp;&nbsp;&nbsp;and a faithful evaluation is not possible.<br>
&nbsp;&nbsp;&nbsp;Will use a plain floating-point evaluation, which might yield a completely wrong value.<br>
&nbsp;&nbsp;&nbsp;Warning: inclusion property is satisfied but the diameter may be greater than the least possible.<br>
&nbsp;&nbsp;&nbsp;[-@Inf@;0]<br>
&nbsp;&nbsp;&nbsp;&gt; <br>
</div>
