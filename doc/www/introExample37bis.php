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
&nbsp;&nbsp;&nbsp;Warning: a SIGSEGV signal has been handled.<br>
&nbsp;&nbsp;&nbsp;Warning: the last command could not be executed. May leak memory.<br>
&nbsp;&nbsp;&nbsp;Warning: releasing the variable frame stack.<br>
&nbsp;&nbsp;&nbsp;&nbsp; canonical = on!;<br>
&nbsp;&nbsp;&nbsp;&gt; for i from 0 to 4 do T[i];<br>
&nbsp;&nbsp;&nbsp;Warning: the identifier "T" is neither assigned to, nor bound to a library function nor external procedure, nor equal to the current free variable.<br>
&nbsp;&nbsp;&nbsp;Will interpret "T" as "x".<br>
&nbsp;&nbsp;&nbsp;Warning: at least one of the given expressions or a subexpression is not correctly typed<br>
&nbsp;&nbsp;&nbsp;or its evaluation has failed because of some error on a side-effect.<br>
&nbsp;&nbsp;&nbsp;error<br>
&nbsp;&nbsp;&nbsp;Warning: the identifier "T" is neither assigned to, nor bound to a library function nor external procedure, nor equal to the current free variable.<br>
&nbsp;&nbsp;&nbsp;Will interpret "T" as "x".<br>
&nbsp;&nbsp;&nbsp;Warning: at least one of the given expressions or a subexpression is not correctly typed<br>
&nbsp;&nbsp;&nbsp;or its evaluation has failed because of some error on a side-effect.<br>
&nbsp;&nbsp;&nbsp;error<br>
&nbsp;&nbsp;&nbsp;Warning: the identifier "T" is neither assigned to, nor bound to a library function nor external procedure, nor equal to the current free variable.<br>
&nbsp;&nbsp;&nbsp;Will interpret "T" as "x".<br>
&nbsp;&nbsp;&nbsp;Warning: at least one of the given expressions or a subexpression is not correctly typed<br>
&nbsp;&nbsp;&nbsp;or its evaluation has failed because of some error on a side-effect.<br>
&nbsp;&nbsp;&nbsp;error<br>
&nbsp;&nbsp;&nbsp;Warning: the identifier "T" is neither assigned to, nor bound to a library function nor external procedure, nor equal to the current free variable.<br>
&nbsp;&nbsp;&nbsp;Will interpret "T" as "x".<br>
&nbsp;&nbsp;&nbsp;Warning: at least one of the given expressions or a subexpression is not correctly typed<br>
&nbsp;&nbsp;&nbsp;or its evaluation has failed because of some error on a side-effect.<br>
&nbsp;&nbsp;&nbsp;error<br>
&nbsp;&nbsp;&nbsp;Warning: the identifier "T" is neither assigned to, nor bound to a library function nor external procedure, nor equal to the current free variable.<br>
&nbsp;&nbsp;&nbsp;Will interpret "T" as "x".<br>
&nbsp;&nbsp;&nbsp;Warning: at least one of the given expressions or a subexpression is not correctly typed<br>
&nbsp;&nbsp;&nbsp;or its evaluation has failed because of some error on a side-effect.<br>
&nbsp;&nbsp;&nbsp;error<br>
</div>
