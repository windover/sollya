<a name="time"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","time","time");?> 
<span class="smallDescription">procedure for timing Sollya code. 
</span> 
</div> 
<div class="divLibraryName"> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","time","time");?>(<span class="arg">code</span>) : <span class="type">code</span> -&gt; <span class="type">constant</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">code</span> is the code to be timed.</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","time","time");?> permits timing a Sollya instruction, resp. a begin-end block 
of Sollya instructions. The timing value, measured in seconds, is returned 
as a Sollya constant (and not merely displayed as for <?php linkTo("command","timing","timing");?>). This  
permits performing computations of the timing measurement value inside Sollya. 
</li><li>The extended <?php linkTo("command","nop","nop");?> command permits executing a defined number of 
useless instructions. Taking the ratio of the time needed to execute a 
certain Sollya instruction and the time for executing a <?php linkTo("command","nop","nop");?> 
therefore gives a way to abstract from the speed of a particular  
machine when evaluating an algorithm's performance. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; t = time(p=remez(sin(x),10,[-1;1]));<br> 
&nbsp;&nbsp;&nbsp;&gt; write(t,"s were spent computing p = ",p,"\n");<br> 
&nbsp;&nbsp;&nbsp;0.242978000000000000024261842535011624022445175796747s were spent computing p = 5.0282378350010211058128384123578806139307237364901e-15 * x^10 + 2.68762594954303046842518220248962109634016728684035e-6 * x^9 + -1.3789116451286674170531616441916183590574659143235e-14 * x^8 + -1.98344863018277416493268155154158924422004290362704e-4 * x^7 + 1.33797221389218815884112341005509833434214820600635e-14 * x^6 + 8.3333037186548537651002133031675072810009327877946e-3 * x^5 + -5.3734444911159112186289355138557505858711113724049e-15 * x^4 + -0.1666666613860130370329129821967413856804986981073 * x^3 + 7.8802751877302786684499343799047734446049787623868e-16 * x^2 + 0.9999999997362835995537201146471312100344298816769 * x + (-3.3426550293345171908513995127407123097704733272204e-17)<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; write(time({ p=remez(sin(x),10,[-1;1]); write("The error is 2^(", log2(dirtyinfnorm(p-sin(x),[-1;1])), ")\n"); }), " s were spent\n");<br> 
&nbsp;&nbsp;&nbsp;The error is 2^(log2(2.3960246769563172784864176818665931373861902892867e-11))<br> 
&nbsp;&nbsp;&nbsp;0.4395199999999999999856711840884315734001575037837 s were spent<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; t = time(bashexecute("sleep 10"));<br> 
&nbsp;&nbsp;&nbsp;&gt; write(~(t-10),"s of execution overhead.\n");<br> 
&nbsp;&nbsp;&nbsp;1.82399999999999923305793458894186187535524368286133e-3s of execution overhead.<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 4: </h2> 
&nbsp;&nbsp;&nbsp;&gt; ratio := time(p=remez(sin(x),10,[-1;1]))/time(nop(10));<br> 
&nbsp;&nbsp;&nbsp;&gt; write("This ratio = ", ratio, " should somehow be independent of the type of machine.\n");<br> 
&nbsp;&nbsp;&nbsp;This ratio = 6.21652855431309904115326057437160360447329054308859 should somehow be independent of the type of machine.<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","timing","timing");?>, <?php linkTo("command","nop","nop");?> 
</div> 
