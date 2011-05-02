<div class="divExample">
&nbsp;&nbsp;&nbsp;&gt; L = [| "foo" |];<br>
&nbsp;&nbsp;&nbsp;&gt; L = L:.1;<br>
&nbsp;&nbsp;&nbsp;&gt; L = "bar".:L;<br>
&nbsp;&nbsp;&nbsp;&gt; L;<br>
&nbsp;&nbsp;&nbsp;[|"bar", "foo", 1|]<br>
&nbsp;&nbsp;&nbsp;&gt; L[1];<br>
&nbsp;&nbsp;&nbsp;foo<br>
&nbsp;&nbsp;&nbsp;&gt; L@L;<br>
&nbsp;&nbsp;&nbsp;[|"bar", "foo", 1, "bar", "foo", 1|]<br>
</div>
