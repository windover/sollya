<div class="divExample">
&nbsp;&nbsp;&nbsp;&gt; restart;<br>
&nbsp;&nbsp;&nbsp;The tool has been restarted.<br>
&nbsp;&nbsp;&nbsp;&gt; prec=50;<br>
&nbsp;&nbsp;&nbsp;The precision has been set to 50 bits.<br>
&nbsp;&nbsp;&nbsp;&gt; f=cos(2*exp(x));<br>
&nbsp;&nbsp;&nbsp;&gt; d=[-1/8;1/8];<br>
&nbsp;&nbsp;&nbsp;&gt; p=remez(f,2,d);<br>
&nbsp;&nbsp;&nbsp;&gt; derivativeZeros = dirtyfindzeros(diff(p-f),d);<br>
&nbsp;&nbsp;&nbsp;&gt; derivativeZeros = inf(d).:derivativeZeros:.sup(d);<br>
&nbsp;&nbsp;&nbsp;&gt; maximum=0;<br>
&nbsp;&nbsp;&nbsp;&gt; for t in derivativeZeros do {<br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;r = evaluate(abs(p-f), t);<br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;if r > maximum then { maximum=r; argmaximum=t; };<br>
&nbsp;&nbsp;&nbsp;&nbsp; };<br>
&nbsp;&nbsp;&nbsp;&gt; print("The infinity norm of", p-f, "is", maximum, "and is reached at", argmaximum);<br>
&nbsp;&nbsp;&nbsp;The infinity norm of -0.416265572875373 + x * (-1.798067209218835 + x * (-3.89710727747639e-2)) - cos(2 * exp(x)) is 8.630659443624325e-4 and is reached at -5.801672331417684e-2<br>
</div>
