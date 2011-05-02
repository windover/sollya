<div class="divExample">
&nbsp;&nbsp;&nbsp;&gt; restart;<br>
&nbsp;&nbsp;&nbsp;The tool has been restarted.<br>
&nbsp;&nbsp;&nbsp;&gt; a.f = exp(x);<br>
&nbsp;&nbsp;&nbsp;&gt; a.dom = [-1;1];<br>
&nbsp;&nbsp;&nbsp;&gt; a.info.text = "My akrnoximation problem";<br>
&nbsp;&nbsp;&nbsp;&gt; a;<br>
&nbsp;&nbsp;&nbsp;{ .info = { .text = "My akrnoximation problem" }, .dom = [-1;1], .f = exp(x) }<br>
&nbsp;&nbsp;&nbsp;&gt; <br>
&nbsp;&nbsp;&nbsp;&gt; a.info.text = "My approximation problem";<br>
&nbsp;&nbsp;&nbsp;&gt; a;<br>
&nbsp;&nbsp;&nbsp;{ .info = { .text = "My approximation problem" }, .dom = [-1;1], .f = exp(x) }<br>
&nbsp;&nbsp;&nbsp;&gt; <br>
&nbsp;&nbsp;&nbsp;&gt; b = exp(x);<br>
&nbsp;&nbsp;&nbsp;&gt; b.a = 5;<br>
&nbsp;&nbsp;&nbsp;Warning: cannot modify an element of something that is not a structure.<br>
&nbsp;&nbsp;&nbsp;Warning: the last assignment will have no effect.<br>
&nbsp;&nbsp;&nbsp;&gt; b;<br>
&nbsp;&nbsp;&nbsp;exp(x)<br>
&nbsp;&nbsp;&nbsp;&gt; <br>
&nbsp;&nbsp;&nbsp;&gt; a.dom.a = -1;<br>
&nbsp;&nbsp;&nbsp;Warning: cannot modify an element of something that is not a structure.<br>
&nbsp;&nbsp;&nbsp;Warning: the last assignment will have no effect.<br>
&nbsp;&nbsp;&nbsp;&gt; a;<br>
&nbsp;&nbsp;&nbsp;{ .info = { .text = "My approximation problem" }, .dom = [-1;1], .f = exp(x) }<br>
</div>
