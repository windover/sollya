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
&nbsp;&nbsp;&nbsp;0.20640099999999999999490338242758014075661776587367s were spent computing p = 9.0486898749977990986908851357759191711354777014602e-17 * x^10 + 2.68762595115123596299959320959141640012683406736586e-6 * x^9 + -2.4247978492521313349073232289246205727856268698001e-16 * x^8 + -1.98344863020965929701245606503586461226130937598776e-4 * x^7 + 2.2748214757753544349162426281857910162575492126267e-16 * x^6 + 8.3333037186560980567697821420813799547276481409702e-3 * x^5 + -8.5747151989720669741706961303549531312110511218869e-17 * x^4 + -0.166666661386013237076216566493953847771564552744173 * x^3 + 1.05699558969863875841493332282097022580493449058156e-17 * x^2 + 0.99999999973628365676559825181776417246038944720794 * x + (-3.12065309566018830243163208536426045628106466008778e-19)<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; write(time({ p=remez(sin(x),10,[-1;1]); write("The error is 2^(", log2(dirtyinfnorm(p-sin(x),[-1;1])), ")\n"); }), " s were spent\n");<br> 
&nbsp;&nbsp;&nbsp;The error is 2^(log2(2.39601979446524486606649528289933482070294808074097e-11))<br> 
&nbsp;&nbsp;&nbsp;0.365272000000000000006529499163576701903366483747959 s were spent<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; t = time(bashexecute("sleep 10"));<br> 
&nbsp;&nbsp;&nbsp;&gt; write(~(t-10),"s of execution overhead.\n");<br> 
&nbsp;&nbsp;&nbsp;2.34399999999999886224344436413957737386226654052734e-3s of execution overhead.<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 4: </h2> 
&nbsp;&nbsp;&nbsp;&gt; ratio := time(p=remez(sin(x),10,[-1;1]))/time(nop(10));<br> 
&nbsp;&nbsp;&nbsp;&gt; write("This ratio = ", ratio, " should somehow be independent of the type of machine.\n");<br> 
&nbsp;&nbsp;&nbsp;This ratio = 6.3890959784222808122117142549582080815932104221717 should somehow be independent of the type of machine.<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","timing","timing");?>, <?php linkTo("command","nop","nop");?> 
</div> 
