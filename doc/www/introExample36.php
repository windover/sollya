<div class="divExample">
&nbsp;&nbsp;&nbsp;&gt; fac = proc(n) { var res; if (n == 0) then res := 1 else res := n * fac(n - 1); return res; };<br>
&nbsp;&nbsp;&nbsp;&gt; fac(5);<br>
&nbsp;&nbsp;&nbsp;120<br>
&nbsp;&nbsp;&nbsp;&gt; fac(11);<br>
&nbsp;&nbsp;&nbsp;39916800<br>
&nbsp;&nbsp;&nbsp;&gt; fac;<br>
&nbsp;&nbsp;&nbsp;proc(n)<br>
&nbsp;&nbsp;&nbsp;{<br>
&nbsp;&nbsp;&nbsp;var res;<br>
&nbsp;&nbsp;&nbsp;if (n) == (0) then<br>
&nbsp;&nbsp;&nbsp;res := 1<br>
&nbsp;&nbsp;&nbsp;else<br>
&nbsp;&nbsp;&nbsp;res := (n) * (fac((n) - (1)));<br>
&nbsp;&nbsp;&nbsp;return res;<br>
&nbsp;&nbsp;&nbsp;}<br>
</div>
