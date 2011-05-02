<div class="divExample">
&nbsp;&nbsp;&nbsp;&gt; f = exp(x) + 5;<br>
&nbsp;&nbsp;&nbsp;&gt; f(-infty);<br>
&nbsp;&nbsp;&nbsp;5<br>
&nbsp;&nbsp;&nbsp;&gt; evaluate(f,[-infty;infty]);<br>
&nbsp;&nbsp;&nbsp;[5;@Inf@]<br>
&nbsp;&nbsp;&nbsp;&gt; f(infty);<br>
&nbsp;&nbsp;&nbsp;Warning: the given expression is undefined or numerically unstable.<br>
&nbsp;&nbsp;&nbsp;@NaN@<br>
&nbsp;&nbsp;&nbsp;&gt; [-infty;5] * [3;4];<br>
&nbsp;&nbsp;&nbsp;[-@Inf@;20]<br>
&nbsp;&nbsp;&nbsp;&gt; -infty < 5;<br>
&nbsp;&nbsp;&nbsp;true<br>
&nbsp;&nbsp;&nbsp;&gt; log(0);<br>
&nbsp;&nbsp;&nbsp;Warning: the given expression is undefined or numerically unstable.<br>
&nbsp;&nbsp;&nbsp;@NaN@<br>
&nbsp;&nbsp;&nbsp;&gt; [log(0);17];<br>
&nbsp;&nbsp;&nbsp;Warning: the given expression is not a constant but an expression to evaluate<br>
&nbsp;&nbsp;&nbsp;and a faithful evaluation is not possible.<br>
&nbsp;&nbsp;&nbsp;Will use a plain floating-point evaluation, which might yield a completely wrong value.<br>
&nbsp;&nbsp;&nbsp;Warning: inclusion property is satisfied but the diameter may be greater than the least possible.<br>
&nbsp;&nbsp;&nbsp;[-@Inf@;17]<br>
&nbsp;&nbsp;&nbsp;&gt; <br>
</div>
