<div class="divExample">
&nbsp;&nbsp;&nbsp;&gt; a = { .f = exp(x), .dom = [-1;1] };<br>
&nbsp;&nbsp;&nbsp;&gt; a;<br>
&nbsp;&nbsp;&nbsp;{ .f = exp(x), .dom = [-1;1] }<br>
&nbsp;&nbsp;&nbsp;&gt; a.f;<br>
&nbsp;&nbsp;&nbsp;exp(x)<br>
&nbsp;&nbsp;&nbsp;&gt; a.dom;<br>
&nbsp;&nbsp;&nbsp;[-1;1]<br>
&nbsp;&nbsp;&nbsp;&gt; b.f = sin(x);<br>
&nbsp;&nbsp;&nbsp;&gt; b.dom = [-1b-5;1b-5];<br>
&nbsp;&nbsp;&nbsp;&gt; b;<br>
&nbsp;&nbsp;&nbsp;{ .dom = [-3.125e-2;3.125e-2], .f = sin(x) }<br>
&nbsp;&nbsp;&nbsp;&gt; { .f = asin(x), .dom = [-1;1] }.f(1);<br>
&nbsp;&nbsp;&nbsp;Warning: rounding has happened. The value displayed is a faithful rounding of the true result.<br>
&nbsp;&nbsp;&nbsp;1.57079632679489661923132169163975144209858469968754<br>
</div>
