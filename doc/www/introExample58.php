<div class="divExample">
&nbsp;&nbsp;&nbsp;&gt; match [| exp(sin(x)), sin(x), 4, DE(x), 9... |] with<br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;exp(a) .: (a .: (([||] :. 4) @ (b @ [| 13... |]))) : <br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;{ "a = ", a, ", b = ", b; };<br>
&nbsp;&nbsp;&nbsp;a = sin(x), b = [|doubleextended(x), 9, 10, 11, 12|]<br>
&nbsp;&nbsp;&nbsp;&gt; <br>
&nbsp;&nbsp;&nbsp;&gt; match [| 1, 2, 3, 4, D... |] with <br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;a @ [| 4, D...|] : (a);<br>
&nbsp;&nbsp;&nbsp;[|1, 2, 3|]<br>
&nbsp;&nbsp;&nbsp;&gt; <br>
&nbsp;&nbsp;&nbsp;&gt; match [| 1, 2, 3, 4, D... |] with <br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;a @ [| D...|] : (a);<br>
&nbsp;&nbsp;&nbsp;[|1, 2, 3, 4|]<br>
&nbsp;&nbsp;&nbsp;&gt; <br>
&nbsp;&nbsp;&nbsp;&gt; match [| 1, 2, 3, 4... |] with <br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;a @ [| 3...|] : (a);<br>
&nbsp;&nbsp;&nbsp;[|1, 2|]<br>
&nbsp;&nbsp;&nbsp;&gt; <br>
&nbsp;&nbsp;&nbsp;&gt; match [| 1, 2, 3, 4... |] with <br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;a @ [| 4...|] : (a);<br>
&nbsp;&nbsp;&nbsp;[|1, 2, 3|]<br>
&nbsp;&nbsp;&nbsp;&gt; <br>
&nbsp;&nbsp;&nbsp;&gt; match [| 1, 2, 3, 4... |] with <br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;a @ [| 17...|] : (a);<br>
&nbsp;&nbsp;&nbsp;[|1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16|]<br>
&nbsp;&nbsp;&nbsp;&gt; <br>
&nbsp;&nbsp;&nbsp;&gt; match [| 1, 2, 3, 4... |] with <br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;a @ [| 17, 18, 19 |] : (a)<br>
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;default&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: ("Something else");<br>
&nbsp;&nbsp;&nbsp;Something else<br>
</div>
