<div class="divExample">
&nbsp;&nbsp;&nbsp;&gt; prec = 50!;<br>
&nbsp;&nbsp;&nbsp;&gt; a = 4097.1;<br>
&nbsp;&nbsp;&nbsp;Warning: Rounding occurred when converting the constant "4097.1" to floating-point with 50 bits.<br>
&nbsp;&nbsp;&nbsp;If safe computation is needed, try to increase the precision.<br>
&nbsp;&nbsp;&nbsp;&gt; prec = 12!;<br>
&nbsp;&nbsp;&nbsp;&gt; f = x + a;<br>
&nbsp;&nbsp;&nbsp;&gt; g = x + 4097.1;<br>
&nbsp;&nbsp;&nbsp;Warning: Rounding occurred when converting the constant "4097.1" to floating-point with 12 bits.<br>
&nbsp;&nbsp;&nbsp;If safe computation is needed, try to increase the precision.<br>
&nbsp;&nbsp;&nbsp;&gt; prec = 120;<br>
&nbsp;&nbsp;&nbsp;The precision has been set to 120 bits.<br>
&nbsp;&nbsp;&nbsp;&gt; f;<br>
&nbsp;&nbsp;&nbsp;4.097099999999998544808477163314819335e3 + x<br>
&nbsp;&nbsp;&nbsp;&gt; g;<br>
&nbsp;&nbsp;&nbsp;4098 + x<br>
</div>
