<div class="divExample">
&nbsp;&nbsp;&nbsp;&gt; a = { .f = exp(x), .a = -1, .b = 1 };<br>
&nbsp;&nbsp;&nbsp;&gt; a;<br>
&nbsp;&nbsp;&nbsp;{ .f = exp(x), .a = -1, .b = 1 }<br>
&nbsp;&nbsp;&nbsp;&gt; a.info = "My function";<br>
&nbsp;&nbsp;&nbsp;&gt; a;<br>
&nbsp;&nbsp;&nbsp;{ .info = "My function", .f = exp(x), .a = -1, .b = 1 }<br>
&nbsp;&nbsp;&nbsp;&gt; <br>
&nbsp;&nbsp;&nbsp;&gt; b = { .a = -1, .f = exp(x), .info = "My function", .b = 1 };<br>
&nbsp;&nbsp;&nbsp;&gt; b;<br>
&nbsp;&nbsp;&nbsp;{ .a = -1, .f = exp(x), .info = "My function", .b = 1 }<br>
&nbsp;&nbsp;&nbsp;&gt; <br>
&nbsp;&nbsp;&nbsp;&gt; a == b;<br>
&nbsp;&nbsp;&nbsp;true<br>
&nbsp;&nbsp;&nbsp;&gt; <br>
&nbsp;&nbsp;&nbsp;&gt; b.info = "My other function";<br>
&nbsp;&nbsp;&nbsp;&gt; a == b;<br>
&nbsp;&nbsp;&nbsp;false<br>
&nbsp;&nbsp;&nbsp;&gt; <br>
&nbsp;&nbsp;&nbsp;&gt; b.info = "My function";<br>
&nbsp;&nbsp;&nbsp;&gt; a == b;<br>
&nbsp;&nbsp;&nbsp;true<br>
&nbsp;&nbsp;&nbsp;&gt; b.something = true;<br>
&nbsp;&nbsp;&nbsp;&gt; a == b;<br>
&nbsp;&nbsp;&nbsp;false<br>
</div>
