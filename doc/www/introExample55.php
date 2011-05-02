<div class="divExample">
&nbsp;&nbsp;&nbsp;&gt; match exp(x) with <br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;sin(x)&nbsp;&nbsp;&nbsp;&nbsp;: ("Sine of x")<br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;atan(x^2) : ("Arctangent of square of x")<br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;default&nbsp;&nbsp;&nbsp;: ("Something else")<br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;exp(x)&nbsp;&nbsp;&nbsp;&nbsp;: ("Exponential of x");<br>
&nbsp;&nbsp;&nbsp;Something else<br>
&nbsp;&nbsp;&nbsp;&gt; <br>
&nbsp;&nbsp;&nbsp;&gt; match atan(x^2) with <br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;sin(x)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: ("Sine of x")<br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;atan(default^2) : ("Arctangent of the square of something")<br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;default&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: ("Something else");<br>
&nbsp;&nbsp;&nbsp;Arctangent of the square of something<br>
&nbsp;&nbsp;&nbsp;&gt; <br>
&nbsp;&nbsp;&nbsp;&gt; match atan(exp(x)^2) with <br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;sin(x)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: ("Sine of x")<br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;atan(default^2) : ("Arctangent of the square of something")<br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;default&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: ("Something else");<br>
&nbsp;&nbsp;&nbsp;Arctangent of the square of something<br>
&nbsp;&nbsp;&nbsp;&gt; <br>
&nbsp;&nbsp;&nbsp;&gt; match exp("Hello world") with <br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;exp(default)&nbsp;&nbsp;&nbsp;&nbsp;: ("A miracle has happened")<br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;default&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: ("Something else");<br>
&nbsp;&nbsp;&nbsp;Warning: at least one of the given expressions or a subexpression is not correctly typed<br>
&nbsp;&nbsp;&nbsp;or its evaluation has failed because of some error on a side-effect.<br>
&nbsp;&nbsp;&nbsp;error<br>
</div>
