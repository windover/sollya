<div class="divExample">
&nbsp;&nbsp;&nbsp;&gt; L = [| 1, 2, [|"a", "b", [|true, false|] |] |];<br>
&nbsp;&nbsp;&nbsp;&gt; L[2][2][1];<br>
&nbsp;&nbsp;&nbsp;false<br>
&nbsp;&nbsp;&nbsp;&gt; L[2][2][1] = true;<br>
&nbsp;&nbsp;&nbsp;Warning: the first element of the left-hand side is not an identifier.<br>
&nbsp;&nbsp;&nbsp;This command will have no effect.<br>
&nbsp;&nbsp;&nbsp;&gt; L[2][2] = "c";<br>
&nbsp;&nbsp;&nbsp;Warning: the first element of the left-hand side is not an identifier.<br>
&nbsp;&nbsp;&nbsp;This command will have no effect.<br>
&nbsp;&nbsp;&nbsp;&gt; L[2] = 3;<br>
&nbsp;&nbsp;&nbsp;&gt; L;<br>
&nbsp;&nbsp;&nbsp;[|1, 2, 3|]<br>
</div>
