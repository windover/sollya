<div class="divExample">
&nbsp;&nbsp;&nbsp;&gt; prec = 24;<br>
&nbsp;&nbsp;&nbsp;The precision has been set to 24 bits.<br>
&nbsp;&nbsp;&nbsp;&gt; a = 0.1;<br>
&nbsp;&nbsp;&nbsp;Warning: Rounding occurred when converting the constant "0.1" to floating-point with 24 bits.<br>
&nbsp;&nbsp;&nbsp;If safe computation is needed, try to increase the precision.<br>
&nbsp;&nbsp;&nbsp;&gt; b = 33554433;<br>
&nbsp;&nbsp;&nbsp;&gt; prec = 64;<br>
&nbsp;&nbsp;&nbsp;The precision has been set to 64 bits.<br>
&nbsp;&nbsp;&nbsp;&gt; display = binary;<br>
&nbsp;&nbsp;&nbsp;Display mode is binary numbers.<br>
&nbsp;&nbsp;&nbsp;&gt; a;<br>
&nbsp;&nbsp;&nbsp;1.10011001100110011001101_2 * 2^(-4)<br>
&nbsp;&nbsp;&nbsp;&gt; 0.1;<br>
&nbsp;&nbsp;&nbsp;Warning: Rounding occurred when converting the constant "0.1" to floating-point with 64 bits.<br>
&nbsp;&nbsp;&nbsp;If safe computation is needed, try to increase the precision.<br>
&nbsp;&nbsp;&nbsp;1.100110011001100110011001100110011001100110011001100110011001101_2 * 2^(-4)<br>
&nbsp;&nbsp;&nbsp;&gt; %24%0.1;<br>
&nbsp;&nbsp;&nbsp;Warning: Rounding occurred when converting the constant "0.1" to floating-point with 24 bits.<br>
&nbsp;&nbsp;&nbsp;If safe computation is needed, try to increase the precision.<br>
&nbsp;&nbsp;&nbsp;1.10011001100110011001101_2 * 2^(-4)<br>
&nbsp;&nbsp;&nbsp;&gt; c = 33554433;<br>
&nbsp;&nbsp;&nbsp;&gt; b;<br>
&nbsp;&nbsp;&nbsp;1.0000000000000000000000001_2 * 2^(25)<br>
&nbsp;&nbsp;&nbsp;&gt; c;<br>
&nbsp;&nbsp;&nbsp;1.0000000000000000000000001_2 * 2^(25)<br>
&nbsp;&nbsp;&nbsp;&gt; %24%33554433;<br>
&nbsp;&nbsp;&nbsp;Warning: Rounding occurred when converting the constant "33554433" to floating-point with 24 bits.<br>
&nbsp;&nbsp;&nbsp;If safe computation is needed, try to increase the precision.<br>
&nbsp;&nbsp;&nbsp;1_2 * 2^(25)<br>
&nbsp;&nbsp;&nbsp;&gt; <br>
&nbsp;&nbsp;&nbsp;&gt; <br>
</div>
