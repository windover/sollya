<div class="divExample">
&nbsp;&nbsp;&nbsp;&gt; 3/0;<br>
&nbsp;&nbsp;&nbsp;Warning: the given expression is undefined or numerically unstable.<br>
&nbsp;&nbsp;&nbsp;@NaN@<br>
&nbsp;&nbsp;&nbsp;&gt; (-3)/0;<br>
&nbsp;&nbsp;&nbsp;Warning: the given expression is undefined or numerically unstable.<br>
&nbsp;&nbsp;&nbsp;@NaN@<br>
&nbsp;&nbsp;&nbsp;&gt; infty/infty;<br>
&nbsp;&nbsp;&nbsp;Warning: the given expression is undefined or numerically unstable.<br>
&nbsp;&nbsp;&nbsp;@NaN@<br>
&nbsp;&nbsp;&nbsp;&gt; infty + infty;<br>
&nbsp;&nbsp;&nbsp;Warning: the given expression is undefined or numerically unstable.<br>
&nbsp;&nbsp;&nbsp;@Inf@<br>
&nbsp;&nbsp;&nbsp;&gt; infty - infty;<br>
&nbsp;&nbsp;&nbsp;Warning: the given expression is undefined or numerically unstable.<br>
&nbsp;&nbsp;&nbsp;@NaN@<br>
&nbsp;&nbsp;&nbsp;&gt; f = exp(x) + 5;<br>
&nbsp;&nbsp;&nbsp;&gt; f(NaN);<br>
&nbsp;&nbsp;&nbsp;@NaN@<br>
&nbsp;&nbsp;&nbsp;&gt; NaN == 5;<br>
&nbsp;&nbsp;&nbsp;false<br>
&nbsp;&nbsp;&nbsp;&gt; NaN == NaN;<br>
&nbsp;&nbsp;&nbsp;false<br>
&nbsp;&nbsp;&nbsp;&gt; NaN != NaN;<br>
&nbsp;&nbsp;&nbsp;false<br>
&nbsp;&nbsp;&nbsp;&gt; X = "Vive la Republique!";<br>
&nbsp;&nbsp;&nbsp;&gt; !(X == X);<br>
&nbsp;&nbsp;&nbsp;false<br>
&nbsp;&nbsp;&nbsp;&gt; X = 5;<br>
&nbsp;&nbsp;&nbsp;&gt; !(X == X);<br>
&nbsp;&nbsp;&nbsp;false<br>
&nbsp;&nbsp;&nbsp;&gt; X = NaN;<br>
&nbsp;&nbsp;&nbsp;&gt; !(X == X);<br>
&nbsp;&nbsp;&nbsp;true<br>
&nbsp;&nbsp;&nbsp;&gt; <br>
</div>
