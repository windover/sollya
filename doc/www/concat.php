<a name="concat"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","concat","@");?> 
<span class="smallDescription">concatenates two lists or strings or applies a list as arguments to a procedure 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library name:</h2> 
<span class="commandline type">sollya_obj_t sollya_lib_concat(sollya_obj_t, sollya_obj_t)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><span class="arg">L1</span><?php linkTo("command","concat","@");?><span class="arg">L2</span> : (<span class="type">list</span>, <span class="type">list</span>) -&gt; <span class="type">list</span></span> 
<span class="commandline"><span class="arg">string1</span><?php linkTo("command","concat","@");?><span class="arg">string2</span> : (<span class="type">string</span>, <span class="type">string</span>) -&gt; <span class="type">string</span></span> 
<span class="commandline"><span class="arg">proc</span><?php linkTo("command","concat","@");?><span class="arg">L1</span> : (<span class="type">procedure</span>, <span class="type">list</span>) -&gt; <span class="type">any type</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">L1</span> and <span class="arg">L2</span> are two lists.</li> 
<li><span class="arg">string1</span> and <span class="arg">string2</span> are two strings.</li> 
<li><span class="arg">proc</span> is a procedure.</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>In its first usage form, <?php linkTo("command","concat","@");?> concatenates two lists or strings. 
</li><li>In its second usage form, <?php linkTo("command","concat","@");?> applies the elements of a list as 
arguments to a procedure. In the case when <span class="arg">proc</span> is a procedure  
with a fixed number of arguments, a check is done if the number of 
elements in the list corresponds to the number of formal parameters 
of the procedure. An empty list can therefore applied only to a  
procedure that does not take any argument. In the case of a  
procedure with an arbitrary number of arguments, no such check is  
performed. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; [|1,...,3|]@[|7,8,9|];<br> 
&nbsp;&nbsp;&nbsp;[|1, 2, 3, 7, 8, 9|]<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; "Hello "@"World!";<br> 
&nbsp;&nbsp;&nbsp;Hello World!<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; procedure cool(a,b,c) { <br> 
&nbsp;&nbsp;&nbsp;&nbsp; write(a,", ", b," and ",c," are cool guys.\n");<br> 
&nbsp;&nbsp;&nbsp;&nbsp; };<br> 
&nbsp;&nbsp;&nbsp;&gt; cool @ [| "Christoph", "Mioara", "Sylvain" |];<br> 
&nbsp;&nbsp;&nbsp;Christoph, Mioara and Sylvain are cool guys.<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 4: </h2> 
&nbsp;&nbsp;&nbsp;&gt; procedure sayhello() { <br> 
&nbsp;&nbsp;&nbsp;&nbsp; "Hello! how are you?";<br> 
&nbsp;&nbsp;&nbsp;&nbsp; };<br> 
&nbsp;&nbsp;&nbsp;&gt; sayhello();<br> 
&nbsp;&nbsp;&nbsp;Hello! how are you?<br> 
&nbsp;&nbsp;&nbsp;&gt; sayhello @ [||];<br> 
&nbsp;&nbsp;&nbsp;Hello! how are you?<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 5: </h2> 
&nbsp;&nbsp;&nbsp;&gt; procedure add(L = ...) {<br> 
&nbsp;&nbsp;&nbsp;&nbsp; var acc, i;<br> 
&nbsp;&nbsp;&nbsp;&nbsp; acc = 0;<br> 
&nbsp;&nbsp;&nbsp;&nbsp; for i in L do acc = i + acc;<br> 
&nbsp;&nbsp;&nbsp;&nbsp; return acc;<br> 
&nbsp;&nbsp;&nbsp;&nbsp; };<br> 
&nbsp;&nbsp;&nbsp;&gt; add(1,2);<br> 
&nbsp;&nbsp;&nbsp;3<br> 
&nbsp;&nbsp;&nbsp;&gt; add(1,2,3);<br> 
&nbsp;&nbsp;&nbsp;6<br> 
&nbsp;&nbsp;&nbsp;&gt; add @ [|1, 2|];<br> 
&nbsp;&nbsp;&nbsp;3<br> 
&nbsp;&nbsp;&nbsp;&gt; add @ [|1, 2, 3|];<br> 
&nbsp;&nbsp;&nbsp;6<br> 
&nbsp;&nbsp;&nbsp;&gt; add @ [||];<br> 
&nbsp;&nbsp;&nbsp;0<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","prepend",".:");?>, <?php linkTo("command","append",":.");?>, <?php linkTo("command","procedure","procedure");?>, <?php linkTo("command","proc","proc");?>, <?php linkTo("command","bind","bind");?> 
</div> 
