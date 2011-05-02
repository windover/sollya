<div class="divExample">
&nbsp;&nbsp;&nbsp;&gt; match exp(x) with <br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;exp(x)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: (1) <br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;sin(x)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: (2)<br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;default&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: (3);<br>
&nbsp;&nbsp;&nbsp;1<br>
&nbsp;&nbsp;&nbsp;&gt; <br>
&nbsp;&nbsp;&nbsp;&gt; match sin(x) with <br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;exp(x)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: (1) <br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;sin(x)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: (2)<br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;default&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: (3);<br>
&nbsp;&nbsp;&nbsp;2<br>
&nbsp;&nbsp;&nbsp;&gt; <br>
&nbsp;&nbsp;&nbsp;&gt; match exp(sin(x)) with<br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;exp(x)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: ("Exponential of x")<br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;exp(sin(x)) : ("Exponential of sine of x")<br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;default&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: ("Something else");<br>
&nbsp;&nbsp;&nbsp;Exponential of sine of x<br>
&nbsp;&nbsp;&nbsp;&gt; <br>
&nbsp;&nbsp;&nbsp;&gt; match exp(sin(x)) with<br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;exp(x)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: ("Exponential of x")<br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;exp(a)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: ("Exponential of " @ a)<br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;default&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: ("Something else");<br>
&nbsp;&nbsp;&nbsp;Exponential of sin(x)<br>
&nbsp;&nbsp;&nbsp;&gt; <br>
&nbsp;&nbsp;&nbsp;&gt; <br>
&nbsp;&nbsp;&nbsp;&gt; procedure differentiate(f) {<br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;return match f with <br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;g + h&nbsp;&nbsp;&nbsp;: (differentiate(g) + differentiate(h))<br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;g * h&nbsp;&nbsp;&nbsp;: (differentiate(g) * h + differentiate(h) * g)<br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;g / h&nbsp;&nbsp;&nbsp;: ((differentiate(g) * h - differentiate(h) * g) / (h^2))<br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;exp(x)&nbsp;&nbsp;: (exp(x))<br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;sin(x)&nbsp;&nbsp;: (cos(x))<br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;cos(x)&nbsp;&nbsp;: (-sin(x))<br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;g(h)&nbsp;&nbsp;&nbsp;&nbsp;: ((differentiate(g))(h) * differentiate(h))<br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;x&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: (1)<br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;h(x)&nbsp;&nbsp;&nbsp;&nbsp;: (NaN)<br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;c&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: (0);<br>
&nbsp;&nbsp;&nbsp;&nbsp; };<br>
&nbsp;&nbsp;&nbsp;&gt; <br>
&nbsp;&nbsp;&nbsp;&gt; differentiate(exp(sin(x + x)));<br>
&nbsp;&nbsp;&nbsp;exp(sin(x * 2)) * cos(x * 2) * 2<br>
&nbsp;&nbsp;&nbsp;&gt; diff(exp(sin(x + x)));<br>
&nbsp;&nbsp;&nbsp;exp(sin(x * 2)) * cos(x * 2) * 2<br>
&nbsp;&nbsp;&nbsp;&gt; <br>
</div>
