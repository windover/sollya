<a name="plot"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","plot","plot");?> 
<span class="smallDescription">plots one or several functions 
</span> 
</div> 
<div class="divLibraryName"> 
<h2 class="libraryname">Library names:</h2> 
<span class="commandline type">void sollya_lib_plot(sollya_obj_t, sollya_obj_t, ...)</span> 
<span class="commandline type">void sollya_lib_v_plot(sollya_obj_t, sollya_obj_t, va_list)</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","plot","plot");?>(<span class="arg">f1</span>, ... ,<span class="arg">fn</span>, <span class="arg">I</span>) : (<span class="type">function</span>, ... ,<span class="type">function</span>, <span class="type">range</span>) -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","plot","plot");?>(<span class="arg">f1</span>, ... ,<span class="arg">fn</span>, <span class="arg">I</span>, <?php linkTo("command","file","file");?>, <span class="arg">name</span>) : (<span class="type">function</span>, ... ,<span class="type">function</span>, <span class="type">range</span>, <?php linkTo("command","file","file");?>, <span class="type">string</span>) -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","plot","plot");?>(<span class="arg">f1</span>, ... ,<span class="arg">fn</span>, <span class="arg">I</span>, <?php linkTo("command","postscript","postscript");?>, <span class="arg">name</span>) : (<span class="type">function</span>, ... ,<span class="type">function</span>, <span class="type">range</span>, <?php linkTo("command","postscript","postscript");?>, <span class="type">string</span>) -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","plot","plot");?>(<span class="arg">f1</span>, ... ,<span class="arg">fn</span>, <span class="arg">I</span>, <?php linkTo("command","postscriptfile","postscriptfile");?>, <span class="arg">name</span>) : (<span class="type">function</span>, ... ,<span class="type">function</span>, <span class="type">range</span>, <?php linkTo("command","postscriptfile","postscriptfile");?>, <span class="type">string</span>) -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","plot","plot");?>(<span class="arg">L</span>, <span class="arg">I</span>) : (<span class="type">list</span>, <span class="type">range</span>) -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","plot","plot");?>(<span class="arg">L</span>, <span class="arg">I</span>, <?php linkTo("command","file","file");?>, <span class="arg">name</span>) : (<span class="type">list</span>, <span class="type">range</span>, <?php linkTo("command","file","file");?>, <span class="type">string</span>) -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","plot","plot");?>(<span class="arg">L</span>, <span class="arg">I</span>, <?php linkTo("command","postscript","postscript");?>, <span class="arg">name</span>) : (<span class="type">list</span>, <span class="type">range</span>, <?php linkTo("command","postscript","postscript");?>, <span class="type">string</span>) -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","plot","plot");?>(<span class="arg">L</span>, <span class="arg">I</span>, <?php linkTo("command","postscriptfile","postscriptfile");?>, <span class="arg">name</span>) : (<span class="type">list</span>, <span class="type">range</span>, <?php linkTo("command","postscriptfile","postscriptfile");?>, <span class="type">string</span>) -&gt; <span class="type">void</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">f1</span>, ..., <span class="arg">fn</span> are functions to be plotted.</li> 
<li><span class="arg">L</span> is a list of functions to be plotted.</li> 
<li><span class="arg">I</span> is the interval where the functions have to be plotted.</li> 
<li><span class="arg">name</span> is a string representing the name of a file.</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li>This command plots one or several functions <span class="arg">f1</span>, ... ,<span class="arg">fn</span> on an interval <span class="arg">I</span>. 
Functions can be either given as parameters of <?php linkTo("command","plot","plot");?> or as a list <span class="arg">L</span> 
which elements are functions. 
The functions are drawn on the same plot with different colors. 
</li><li>If <span class="arg">L</span> contains an element that is not a function (or a constant), an error 
occurs. 
</li><li><?php linkTo("command","plot","plot");?> relies on the value of global variable <?php linkTo("command","points","points");?>. Let n be the  
value of this variable. The algorithm is the following: each function is  
evaluated at n evenly distributed points in <span class="arg">I</span>. At each point, the  
computed value is a faithful rounding of the exact value with a sufficiently 
high precision. Each point is finally plotted. 
This should avoid numerical artefacts such as critical cancellations. 
</li><li>You can save the function plot either as a data file or as a postscript file. 
</li><li>If you use argument <?php linkTo("command","file","file");?> with a string <span class="arg">name</span>, Sollya will save a data file 
called name.dat and a gnuplot directives file called name.p. Invoking gnuplot 
on name.p will plot the data stored in name.dat. 
</li><li>If you use argument <?php linkTo("command","postscript","postscript");?> with a string <span class="arg">name</span>, Sollya will save a  
postscript file called name.eps representing your plot. 
</li><li>If you use argument <?php linkTo("command","postscriptfile","postscriptfile");?> with a string <span class="arg">name</span>, Sollya will  
produce the corresponding name.dat, name.p and name.eps. 
</li><li>This command uses gnuplot to produce the final plot. 
If your terminal is not graphic (typically if you use Sollya through  
ssh without -X) 
gnuplot should be able to detect that and produce an ASCII-art version on the 
standard output. If it is not the case, you can either store the plot in a 
postscript file to view it locally, or use <?php linkTo("command","asciiplot","asciiplot");?> command. 
</li><li>If every function is constant, <?php linkTo("command","plot","plot");?> will not plot them but just display 
their value. 
</li><li>If the interval is reduced to a single point, <?php linkTo("command","plot","plot");?> will just display the 
value of the functions at this point. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; plot(sin(x),0,cos(x),[-Pi,Pi]);<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; plot(sin(x),0,cos(x),[-Pi,Pi],postscriptfile,"plotSinCos");<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; plot(exp(0), sin(1), [0;1]);<br> 
&nbsp;&nbsp;&nbsp;1<br> 
&nbsp;&nbsp;&nbsp;0.84147098480789650665250232163029899962256306079837<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 4: </h2> 
&nbsp;&nbsp;&nbsp;&gt; plot(sin(x), cos(x), [1;1]);<br> 
&nbsp;&nbsp;&nbsp;0.84147098480789650665250232163029899962256306079837<br> 
&nbsp;&nbsp;&nbsp;0.54030230586813971740093660744297660373231042061792<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","externalplot","externalplot");?>, <?php linkTo("command","asciiplot","asciiplot");?>, <?php linkTo("command","file","file");?>, <?php linkTo("command","postscript","postscript");?>, <?php linkTo("command","postscriptfile","postscriptfile");?>, <?php linkTo("command","points","points");?> 
</div> 
