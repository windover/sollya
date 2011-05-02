<div class="divExample">
&nbsp;&nbsp;&nbsp;&gt; autosimplify = off;<br>
&nbsp;&nbsp;&nbsp;Automatic pure tree simplification has been deactivated.<br>
&nbsp;&nbsp;&nbsp;&gt; i = 1000;<br>
&nbsp;&nbsp;&nbsp;&gt; i = i + 1;<br>
&nbsp;&nbsp;&nbsp;&gt; print(i);<br>
&nbsp;&nbsp;&nbsp;1000 + 1<br>
&nbsp;&nbsp;&nbsp;&gt; i := i + 1;<br>
&nbsp;&nbsp;&nbsp;&gt; print(i);<br>
&nbsp;&nbsp;&nbsp;1002<br>
&nbsp;&nbsp;&nbsp;&gt; L = [|1,...,5|];<br>
&nbsp;&nbsp;&nbsp;&gt; print(L);<br>
&nbsp;&nbsp;&nbsp;[|1, 2, 3, 4, 5|]<br>
&nbsp;&nbsp;&nbsp;&gt; L[3] = L[3] + 1;<br>
&nbsp;&nbsp;&nbsp;&gt; L[4] := L[4] + 1;<br>
&nbsp;&nbsp;&nbsp;&gt; print(L);<br>
&nbsp;&nbsp;&nbsp;[|1, 2, 3, 4 + 1, 6|]<br>
&nbsp;&nbsp;&nbsp;&gt; L[5] = true;<br>
&nbsp;&nbsp;&nbsp;&gt; L;<br>
&nbsp;&nbsp;&nbsp;[|1, 2, 3, 5, 6, true|]<br>
&nbsp;&nbsp;&nbsp;&gt; s = "Hello world";<br>
&nbsp;&nbsp;&nbsp;&gt; s;<br>
&nbsp;&nbsp;&nbsp;Hello world<br>
&nbsp;&nbsp;&nbsp;&gt; s[1] = "a";<br>
&nbsp;&nbsp;&nbsp;&gt; s;<br>
&nbsp;&nbsp;&nbsp;Hallo world<br>
&nbsp;&nbsp;&nbsp;&gt; s[2] = "foo";<br>
&nbsp;&nbsp;&nbsp;Warning: the string to be assigned is not of length 1.<br>
&nbsp;&nbsp;&nbsp;This command will have no effect.<br>
&nbsp;&nbsp;&nbsp;&gt; L = [|true,1,...,5,9...|];<br>
&nbsp;&nbsp;&nbsp;&gt; L;<br>
&nbsp;&nbsp;&nbsp;[|true, 1, 2, 3, 4, 5, 9...|]<br>
&nbsp;&nbsp;&nbsp;&gt; L[13] = "Hello";<br>
&nbsp;&nbsp;&nbsp;&gt; L;<br>
&nbsp;&nbsp;&nbsp;[|true, 1, 2, 3, 4, 5, 9, 10, 11, 12, 13, 14, 15, "Hello"...|]<br>
</div>
