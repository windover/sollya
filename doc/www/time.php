<a name="time"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","time","time");?> 
<span class="smallDescription">procedure for timing Sollya code. 
</span> 
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
&nbsp;&nbsp;&nbsp;0.154830999999999999986073639934858192646061070263386s were spent computing p = -3.3426550293345171908513995127407122194691200059639e-17 + x * (0.99999999973628359955372011464713121003442988167693 + x * (7.8802751877302786684499343799047732495568873819693e-16 + x * (-0.166666661386013037032912982196741385680498698107285 + x * (-5.3734444911159112186289355138557504839692987221233e-15 + x * (8.3333037186548537651002133031675072810009327877148e-3 + x * (1.33797221389218815884112341005509831429347230871284e-14 + x * (-1.98344863018277416493268155154158924422004290239026e-4 + x * (-1.3789116451286674170531616441916183417598709732816e-14 + x * (2.6876259495430304684251822024896210963401672262005e-6 + x * 5.0282378350010211058128384123578805586173782863605e-15)))))))))<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; write(time({ p=remez(sin(x),10,[-1;1]); write("The error is 2^(", log2(dirtyinfnorm(p-sin(x),[-1;1])), ")\n"); }), " s were spent\n");<br> 
&nbsp;&nbsp;&nbsp;The error is 2^(log2(2.39602467695631727848641768186659313738474584992648e-11))<br> 
&nbsp;&nbsp;&nbsp;0.28779800000000000000099920072216264088638126850128 s were spent<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; t = time(bashexecute("sleep 10"));<br> 
&nbsp;&nbsp;&nbsp;&gt; write(~(t-10),"s of execution overhead.\n");<br> 
&nbsp;&nbsp;&nbsp;1.90299999999999844280118566075543640181422233581543e-3s of execution overhead.<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 4: </h2> 
&nbsp;&nbsp;&nbsp;&gt; ratio := time(p=remez(sin(x),10,[-1;1]))/time(nop(10));<br> 
&nbsp;&nbsp;&nbsp;&gt; write("This ratio = ", ratio, " should somehow be independent of the type of machine.\n");<br> 
&nbsp;&nbsp;&nbsp;This ratio = 5.4844252677794178864967765929433019096305590326358 should somehow be independent of the type of machine.<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","timing","timing");?>, <?php linkTo("command","nop","nop");?> 
</div> 
