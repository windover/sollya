<div class="divExample">
&nbsp;&nbsp;&nbsp;&gt; sumall = proc(args = ...) { var i, acc; acc = 0; for i in args do acc = acc + i; return acc; };<br>
&nbsp;&nbsp;&nbsp;&gt; sumall;<br>
&nbsp;&nbsp;&nbsp;proc(args = ...)<br>
&nbsp;&nbsp;&nbsp;{<br>
&nbsp;&nbsp;&nbsp;var i, acc;<br>
&nbsp;&nbsp;&nbsp;acc = 0;<br>
&nbsp;&nbsp;&nbsp;for i in args do<br>
&nbsp;&nbsp;&nbsp;acc = (acc) + (i);<br>
&nbsp;&nbsp;&nbsp;return acc;<br>
&nbsp;&nbsp;&nbsp;}<br>
&nbsp;&nbsp;&nbsp;&gt; sumall();<br>
&nbsp;&nbsp;&nbsp;0<br>
&nbsp;&nbsp;&nbsp;&gt; sumall(1);<br>
&nbsp;&nbsp;&nbsp;1<br>
&nbsp;&nbsp;&nbsp;&gt; sumall(1,5);<br>
&nbsp;&nbsp;&nbsp;6<br>
&nbsp;&nbsp;&nbsp;&gt; sumall(1,5,9);<br>
&nbsp;&nbsp;&nbsp;15<br>
&nbsp;&nbsp;&nbsp;&gt; sumall @ [|1,5,9,4,8|];<br>
&nbsp;&nbsp;&nbsp;27<br>
&nbsp;&nbsp;&nbsp;&gt; <br>
</div>
