<div class="divExample">
&nbsp;&nbsp;&nbsp;&gt; s.a = 17;<br>
&nbsp;&nbsp;&nbsp;&gt; s.b = exp(x);<br>
&nbsp;&nbsp;&nbsp;&gt; s.a;<br>
&nbsp;&nbsp;&nbsp;17<br>
&nbsp;&nbsp;&nbsp;&gt; s.b;<br>
&nbsp;&nbsp;&nbsp;exp(x)<br>
&nbsp;&nbsp;&nbsp;&gt; s.b(1);<br>
&nbsp;&nbsp;&nbsp;Warning: rounding has happened. The value displayed is a faithful rounding to 165 bits of the true result.<br>
&nbsp;&nbsp;&nbsp;2.71828182845904523536028747135266249775724709369998<br>
&nbsp;&nbsp;&nbsp;&gt; s.d.a = [-1;1];<br>
&nbsp;&nbsp;&nbsp;&gt; s.d.b = sin(x);<br>
&nbsp;&nbsp;&nbsp;&gt; inf(s.d.a);<br>
&nbsp;&nbsp;&nbsp;-1<br>
&nbsp;&nbsp;&nbsp;&gt; diff(s.d.b);<br>
&nbsp;&nbsp;&nbsp;cos(x)<br>
</div>
