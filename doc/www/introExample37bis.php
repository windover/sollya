<div class="divExample">
&nbsp;&nbsp;&nbsp;&gt; ChebPolynomials = proc(n) {<br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;var i, res;<br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;if (n<0) then res = [||]<br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;else if (n==0) then res = [|1|]<br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;else {<br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;res = [|1, _x_|];<br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;for i from 2 to n do res[i] = horner(2*_x_*res[i-1]-res[i-2]);<br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;};<br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;return res;<br>
&nbsp;&nbsp;&nbsp;&nbsp; };<br>
&nbsp;&nbsp;&nbsp;&gt; <br>
&nbsp;&nbsp;&nbsp;&gt; f = sin(x);<br>
&nbsp;&nbsp;&nbsp;&gt; T = ChebPolynomials(4);<br>
&nbsp;&nbsp;&nbsp;&gt; canonical = on!;<br>
&nbsp;&nbsp;&nbsp;&gt; for i from 0 to 4 do T[i];<br>
&nbsp;&nbsp;&nbsp;1<br>
&nbsp;&nbsp;&nbsp;x<br>
&nbsp;&nbsp;&nbsp;-1 + 2 * x^2<br>
&nbsp;&nbsp;&nbsp;-3 * x + 4 * x^3<br>
&nbsp;&nbsp;&nbsp;1 + -8 * x^2 + 8 * x^4<br>
</div>
