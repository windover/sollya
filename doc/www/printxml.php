<a name="printxml"></a> 
<div class="divName"> 
<h2 class="name">Name:</h2> <?php linkTo("command","printxml","printxml");?> 
<span class="smallDescription">prints an expression as an MathML-Content-Tree 
</span> 
</div> 
<div class="divUsage"> 
<h2 class="category">Usage: </h2> 
<span class="commandline"><?php linkTo("command","printxml","printxml");?>(<span class="arg">expr</span>) : <span class="type">function</span> -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","printxml","printxml");?>(<span class="arg">expr</span>) &gt; <span class="arg">filename</span> : (<span class="type">function</span>, <span class="type">string</span>) -&gt; <span class="type">void</span></span> 
<span class="commandline"><?php linkTo("command","printxml","printxml");?>(<span class="arg">expr</span>) &gt; &gt; <span class="arg">filename</span> : (<span class="type">function</span>, <span class="type">string</span>) -&gt; <span class="type">void</span></span> 
 
</div> 
<div class="divParameters"> 
<h2 class="category">Parameters: </h2> 
<ul> 
<li><span class="arg">expr</span> represents a functional expression</li> 
<li><span class="arg">filename</span> represents a character sequence indicating a file name</li> 
</ul> 
</div> 
<div class="divDescription"> 
<h2 class="category">Description: </h2><ul> 
<li><?php linkTo("command","printxml","printxml");?>(<span class="arg">expr</span>) prints the functional expression <span class="arg">expr</span> as a tree of 
MathML Content Definition Markups. This XML tree can be re-read in 
external tools or by usage of the <?php linkTo("command","readxml","readxml");?> command. 
<br><br> 
If a second argument <span class="arg">filename</span> is given after a single "&gt;", the 
MathML tree is not output on the standard output of Sollya but if in 
the file <span class="arg">filename</span> that get newly created or overwritten. If a double 
"&gt;" is given, the output will be appended to the file <span class="arg">filename</span>. 
</ul> 
</div> 
<div class="divExamples"> 
<div class="divExample"> 
<h2 class="category">Example 1: </h2> 
&nbsp;&nbsp;&nbsp;&gt; printxml(x + 2 + exp(sin(x)));<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&lt;?xml version="1.0" encoding="UTF-8"?&gt;<br> 
&nbsp;&nbsp;&nbsp;&lt;!-- generated by sollya: http://sollya.gforge.inria.fr/ --&gt;<br> 
&nbsp;&nbsp;&nbsp;&lt;!-- syntax: printxml(...);&nbsp;&nbsp;&nbsp;example: printxml(x^2-2*x+5); --&gt;<br> 
&nbsp;&nbsp;&nbsp;&lt;?xml-stylesheet type="text/xsl" href="http://sollya.gforge.inria.fr/mathmlc2p-web.xsl"?&gt;<br> 
&nbsp;&nbsp;&nbsp;&lt;?xml-stylesheet type="text/xsl" href="mathmlc2p-web.xsl"?&gt;<br> 
&nbsp;&nbsp;&nbsp;&lt;!-- This stylesheet allows direct web browsing of MathML-c XML files (http:// or file://) --&gt;<br> 
&nbsp;&nbsp;&nbsp;<br> 
&nbsp;&nbsp;&nbsp;&lt;math xmlns="http://www.w3.org/1998/Math/MathML"&gt;<br> 
&nbsp;&nbsp;&nbsp;&lt;semantics&gt;<br> 
&nbsp;&nbsp;&nbsp;&lt;annotation-xml encoding="MathML-Content"&gt;<br> 
&nbsp;&nbsp;&nbsp;&lt;lambda&gt;<br> 
&nbsp;&nbsp;&nbsp;&lt;bvar&gt;&lt;ci&gt; x &lt;/ci&gt;&lt;/bvar&gt;<br> 
&nbsp;&nbsp;&nbsp;&lt;apply&gt;<br> 
&nbsp;&nbsp;&nbsp;&lt;apply&gt;<br> 
&nbsp;&nbsp;&nbsp;&lt;plus/&gt;<br> 
&nbsp;&nbsp;&nbsp;&lt;apply&gt;<br> 
&nbsp;&nbsp;&nbsp;&lt;plus/&gt;<br> 
&nbsp;&nbsp;&nbsp;&lt;ci&gt; x &lt;/ci&gt;<br> 
&nbsp;&nbsp;&nbsp;&lt;cn type="integer" base="10"&gt; 2 &lt;/cn&gt;<br> 
&nbsp;&nbsp;&nbsp;&lt;/apply&gt;<br> 
&nbsp;&nbsp;&nbsp;&lt;apply&gt;<br> 
&nbsp;&nbsp;&nbsp;&lt;exp/&gt;<br> 
&nbsp;&nbsp;&nbsp;&lt;apply&gt;<br> 
&nbsp;&nbsp;&nbsp;&lt;sin/&gt;<br> 
&nbsp;&nbsp;&nbsp;&lt;ci&gt; x &lt;/ci&gt;<br> 
&nbsp;&nbsp;&nbsp;&lt;/apply&gt;<br> 
&nbsp;&nbsp;&nbsp;&lt;/apply&gt;<br> 
&nbsp;&nbsp;&nbsp;&lt;/apply&gt;<br> 
&nbsp;&nbsp;&nbsp;&lt;/apply&gt;<br> 
&nbsp;&nbsp;&nbsp;&lt;/lambda&gt;<br> 
&nbsp;&nbsp;&nbsp;&lt;/annotation-xml&gt;<br> 
&nbsp;&nbsp;&nbsp;&lt;annotation encoding="sollya/text"&gt;(x + 1b1) + exp(sin(x))&lt;/annotation&gt;<br> 
&nbsp;&nbsp;&nbsp;&lt;/semantics&gt;<br> 
&nbsp;&nbsp;&nbsp;&lt;/math&gt;<br> 
&nbsp;&nbsp;&nbsp;<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 2: </h2> 
&nbsp;&nbsp;&nbsp;&gt; printxml(x + 2 + exp(sin(x))) &gt; "foo.xml";<br> 
</div> 
<div class="divExample"> 
<h2 class="category">Example 3: </h2> 
&nbsp;&nbsp;&nbsp;&gt; printxml(x + 2 + exp(sin(x))) &gt;&gt; "foo.xml";<br> 
</div> 
</div> 
<div class="divSeeAlso"> 
<span class="category">See also: </span><?php linkTo("command","readxml","readxml");?>, <?php linkTo("command","print","print");?>, <?php linkTo("command","write","write");?> 
</div> 