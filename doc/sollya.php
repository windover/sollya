<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<html>
<head>
<title>Users' manual for the Sollya tool - Release 3.0-alpha</title>
<meta name="author" content="Sylvain Chevillard, Christoph Lauter">
<meta name="copyright" content="2009-2011 Laboratoire de l'Informatique du Parallélisme - UMR CNRS - ENS Lyon - UCB Lyon 1 - INRIA 5668; LORIA (CNRS, INPL, INRIA, UHP, U-Nancy 2), Nancy, France; Laboratoire d'Informatique de Paris 6, Équipe PEQUAN, UPMC Université Paris 06 - CNRS - UMR 7606 - LIP6, Paris, France; INRIA Sophia-Antipolis Méditerranée, APICS Team, Sophia-Antipolis, France">
<meta name="keywords" content="help, sollya, User's Manual">
<meta name="description" content="This is part of Sollya User's Manual">
<meta http-equiv="content-type" content="text/html; charset=UTF-8">
<link href="sollyacss.css" type="text/css" rel="stylesheet">
<style type="text/css"><!--

.todo { color:#ff0000;}

* { line-height: 1.3em; }

h2 { font-size: large;}
 --></style>
</head>
<body>

<p>
<h1 style="text-align:center">Users' manual for the <span class="sollya">Sollya</span> tool - Release 3.0-alpha</h1>
<div style="text-align:center; line-height: 1.5em;">Sylvain Chevillard (<a href="sylvain.chevillard@ens-lyon.org">sylvain.chevillard@ens-lyon.org</a>),</div>
<div style="text-align:center; line-height: 1.5em;">Christoph Lauter (<a href="christoph.lauter@ens-lyon.org; line-height: 1.5em;">christoph.lauter@ens-lyon.org</a>)</div>
<div style="text-align:center">and Mioara Joldeș (<a href="mioara.joldes@ens-lyon.fr">mioara.joldes@ens-lyon.fr</a>).</div>

<h2 style="margin-top: 3em;">License</h2>
<p style="font-size:small;">
The <span class="sollya">Sollya</span> tool is Copyright &copy;&nbsp;2006-2011 by<br>
<span style="text-indent:3em; display:block;">Laboratoire de l'Informatique du Parallélisme - UMR CNRS - ENS Lyon - UCB Lyon 1 - INRIA 5668, Lyon, France, </span>
<span style="text-indent:3em;display:block;">LORIA (CNRS, INPL, INRIA, UHP, U-Nancy 2), Nancy, France, </span>
<span style="text-indent:3em;display:block;">Laboratoire d'Informatique de Paris 6, Équipe PEQUAN, UPMC Université Paris 06 - CNRS - UMR 7606 - LIP6, Paris, France, and by</span>
<span style="text-indent:3em;display:block;">INRIA Sophia-Antipolis Méditerranée, APICS Team, Sophia-Antipolis, France.</span>
All rights reserved.
<p style="font-size:small;">
The <span class="sollya">Sollya</span> tool is open software. It is distributed and can be used,
modified and redistributed under the terms of the CeCILL-C licence
available at <a href="http://www.cecill.info/">http://www.cecill.info/</a> and reproduced in the
<code>COPYING</code> file of the distribution. The distribution contains
parts of other libraries as a support for but not integral part of
<span class="sollya">Sollya</span>. These libraries are reigned by the GNU Lesser General Public
License that is available at <a href="http://www.gnu.org/licenses/">http://www.gnu.org/licenses/</a> and
reproduced in the <code>COPYING</code> file of the distribution.
<p style="font-size:small;">
This software (<span class="sollya">Sollya</span>) is distributed WITHOUT ANY WARRANTY; without even the 
implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

<h1><a href="#commandsAndFunctions">Direct access to the list of available commands</a></h1>

<h1>1 - Compilation and installation of the <span class="sollya">Sollya</span> tool</h1>
<h2>1.1 - Compilation dependencies</h2>
<p>
The <span class="sollya">Sollya</span> distribution can be compiled and installed using the usual
<code>./configure</code>, <code>make</code>, <code>make install</code>
procedure. Besides a <code>C</code> and a <code>C++</code> compiler, <span class="sollya">Sollya</span> needs the following
software libraries and tools to be installed. The <code>./configure</code>
script checks for the installation of the libraries. However <span class="sollya">Sollya</span>
will build without error if some of its external tools are not
installed. In this case an error will be displayed at runtime.
<ul>
<li> <code>GMP</code>
</li><li> <code>MPFR</code>
</li><li> <code>MPFI</code>
</li><li> <code>fplll</code>
</li><li> <code>libxml2</code>
</li><li> <code>gnuplot</code> (external tool)
</li></ul>
<p>The use of the external tool <code>rlwrap</code> is highly recommended but
not required. Use the <code>-A</code> option of <code>rlwrap</code> for
correctly displayed ANSI X3.64/ ISO/IEC 6429 colored prompts (see
below).

<h2>1.2 - <span class="sollya">Sollya</span> command line options</h2>
<p>
<span class="sollya">Sollya</span> can read input on standard input or in a file whose name is given 
as an argument when <span class="sollya">Sollya</span> is invoked. The tool will always produce its 
output on standard output, unless specificly instructed by a particular
<span class="sollya">Sollya</span> command that writes to a file.
The following lines are valid invocations of <span class="sollya">Sollya</span>, assuming that 
<code>bash</code> is used as a shell:
<div class="divExample">
&nbsp;/% sollya<br>
...<br>
&nbsp;/% sollya myfile.sollya<br>
...<br>
&nbsp;/% sollya < myfile.sollya<br>
</div>

<p>If a file given as an input does not exist, an error message is displayed.

<p>
All configurations of the internal state of the tool are done by
commands given on the <span class="sollya">Sollya</span> prompt or in <span class="sollya">Sollya</span>
scripts. Nevertheless, some command line options are supported; they
work at a very basic I/O-level and can therefore not be implemented as
commands.
<p>
The following options are supported when calling <span class="sollya">Sollya</span>:
<ul>
<li> <code>--donotmodifystacksize</code>: When invoked, <span class="sollya">Sollya</span> trys to increase
the stack size that is available to a user process to the maximum size
supported by the kernel. On some systems, the correspondent <code>ioctl</code> 
does not work properly. Use the option to prevent <span class="sollya">Sollya</span> from changing the 
stack size.
</li><li> <code>--flush</code>: When this option is given, <span class="sollya">Sollya</span> will flush
all its input and output buffers after parsing and executing each
command resp. sequence of commands. This option is needed when pipes
are used to communicate with <span class="sollya">Sollya</span> from another program.
</li><li> <code>--help</code>: Prints help on the usage of the tool and quits.
</li><li> <code>--nocolor</code>: <span class="sollya">Sollya</span> supports coloring of the output
  using ANSI X3.64/ ISO/IEC 6429 escape sequences. Coloring is
  deactivated when <span class="sollya">Sollya</span> is connected on standard input to a file
  that is not a terminal. This option forces the deactivation of ANSI
  coloring. This might be necessary on very old grey-scale terminals or when
  encountering problems with old versions of <code>rlwrap</code>. 
</li><li> <code>--noprompt</code>: <span class="sollya">Sollya</span> prints a prompt symbol when
  connected on standard input to a pseudo-file that is a terminal. The
  option deactivates the prompt.
</li><li> <code>--oldautoprint</code>: The behaviour of an undocumented
feature for displaying values has changed in <span class="sollya">Sollya</span> from version 1.1
to version 2.0. The old feature is deprecated. If you wish to use it
nevertheless, use this deprecated option.
</li><li> <code>--oldrlwrapcompatible</code>: This option is deprecated. It
  makes <span class="sollya">Sollya</span> emit a non ANSI X3.64 compliant coloring escape
  sequence for making it compatible with versions of <code>rlwrap</code>
  that do not support the <code>-A</code> option. The option is considered
  a hack since it is known to garble the output of the tool under
  some particular circumstances.
</li><li> <code>--warninfile[append] &lt;file&gt;</code>: Normally, <span class="sollya">Sollya</span> emits
  warning and information messages together with all other displayed
  information on either standard output or standard error. This option
  allows all warning and information messages to get redirected to a
  file. The filename to be used must be given after the option.  When
  <code>--warninfile</code> is used, the existing content (if any) of the
  file is first removed before writing to the file. With
  <code>--warninfileappend</code>, the messages are appended to an
  existing file. Even if coloring is used for the displaying all other
  <span class="sollya">Sollya</span> output, no coloring sequences are ever written to the
  file. Let us emphasize on the fact that any file of a unixoid system
  can be used for output, for instance also a named pipe. This allows
  for error messaging to be performed on a separate terminal. The use
  of this option is mutually exclusive with the
  <code>--warnonstderr</code> option.
</li><li> <code>--warnonstderr</code>: Normally, <span class="sollya">Sollya</span> prints warning and
  information messages on standard output, using a warning color 
  when coloring is activated. When this option is given, <span class="sollya">Sollya</span> will 
  output all warning and information messages on standard error. Coloring
  will be used even on standard error, when activated. The use of 
  this option is mutually exclusive with the <code>--warninfile[append]</code>
  option.
</li>
</ul>
<h1>2 - Introduction</h1>
<p>
<span class="sollya">Sollya</span> is an interactive tool for handling numerical functions and working with arbitrary precision. It can evaluate functions accurately, compute polynomial approximations of functions, automatically implement polynomials for use in math libraries, plot functions, compute infinity norms, etc. <span class="sollya">Sollya</span> is also a full-featured script programming language with support for procedures&nbsp;etc.
<p>
Let us begin this manual with an example. <span class="sollya">Sollya</span> does not allow command line edition; since this may quickly become uncomfortable, we highly suggest to use the <code>rlwrap</code> tool with <span class="sollya">Sollya</span>:
<p>
<div class="divExample">
&nbsp;/% rlwrap -A sollya<br>
&nbsp;&nbsp;&nbsp;&gt;
</div>
<p>
<span class="sollya">Sollya</span> manipulates only functions in one variable. The first time that an unbound variable is used, this name is fixed. It will be used to refer to the free variable. For instance, try
<p>
<?php include("introExample1.php"); ?>
<p>
Now, the name 'x' can only be used to refer to the free variable:
<p>
<?php include("introExample2.php"); ?>
<p>
If you really want to unbind 'x', you can use the <code class="com">rename</code> command and change the name of the free variable:
<p>
<?php include("introExample3.php"); ?>
<p>
As you have seen, you can name functions and easily work with them. The basic thing to do with a function is to evaluate it at some point:
<p>
<?php include("introExample4.php"); ?>
<p>
The printed value is generally a faithful rounding of the exact value at the working precision (i.e. one of the two floating-point numbers enclosing the exact value). Internally <span class="sollya">Sollya</span> represents numbers as floating-point numbers in arbitrary precision with radix&nbsp;2: the fact that a faithful rounding is performed in binary does not imply much on the exactness of the digits displayed in decimal. The working precision is controlled by the global variable <code class="com">prec</code>:
<p>
<?php include("introExample5.php"); ?>
<p>
Sometimes a faithful rounding cannot easily be computed. In such a case, a value is printed that was obtained using floating-point approximations without control on the final accuracy:
<p>
<?php include("introExample6.php"); ?>
<p>
The philosophy of <span class="sollya">Sollya</span> is: <em>Whenever something is not exact, print a warning</em>. This explains the warnings in the previous examples. If the result can be shown to be exact, there is no warning:
<p>
<?php include("introExample7.php"); ?>
<p>
Let us finish this Section with a small complete example that shows a bit of what can be done with&nbsp;<span class="sollya">Sollya</span>:
<p>
<!--  Warning: this file must be manually corrected: delete the extra ">" -->
<?php include("introExample8.php"); ?>
<p>
In this example, we define a function f, an interval d and we compute the best degree-2 polynomial approximation of f on d with respect to the infinity norm. In other words, max {|p(x)-f(x)|, x in d} is minimal amongst polynomials with degree not greater than 2. Then, we compute the list of the zeros of the derivative of p-f and add the bounds of d to this list. Finally, we evaluate |p-f| for each point in the list and store the maximum and the point where it is reached. We conclude by printing the result in a formatted way.
<p>
Let us mention as a sidenote that you do not really need to use such a script for computing an infinity norm; as we will see, the command <code class="com">dirtyinfnorm</code> does this for you.

<a name="sec:general_principles"></a>
<h1>3 - General principles</h1>
<p>
The first purpose of <span class="sollya">Sollya</span> is to help people using numerical functions and numerical algorithms in a safe way. It is first designed to be used interactively but it can also be used in scripts (remark: some of the behaviors of <span class="sollya">Sollya</span> slightly change when it is used in scripts. For example, no prompt is printed).
<p>
One of the particularities of <span class="sollya">Sollya</span> is to work with multi-precision arithmetic (it uses the <code>MPFR</code> library). For safety purposes, <span class="sollya">Sollya</span> knows how to use interval arithmetic. It uses interval arithmetic to produce tight and safe results with the precision required by the user.
<p>
The general philosophy of <span class="sollya">Sollya</span> is: <em>When you can perform a computation exactly and sufficiently quickly, do it; when you cannot, do not, unless you have been explicitly asked for.</em>
<p>
The precision of the tool is set by the global variable <code class="key">prec</code>. In general, the variable <code class="key">prec</code> determines the precision of the outputs of commands: more precisely, the command will internally determine how much precision should be used during the computations in order to ensure that the output is a faithfully rounded result with <code class="key">prec</code> bits.
<p>
For decidability and efficiency reasons, this general principle cannot be applied every time, so be careful. Moreover certain commands are known to be unsafe: they give in general excellent results and give almost <code class="key">prec</code> correct bits in output for everyday examples. However they are merely based on heuristics and should not be used when the result must be safe. See the documentation of each command to know precisely how confident you can be with their result.
<p>
A second principle (that comes together with the first one) is the following one: <em>When a computation leads to inexact results, inform the user with a warning</em>. This can be quite irritating in some circumstances: in particular if you are using <span class="sollya">Sollya</span> within other scripts. The global variable <code class="key">verbosity</code> lets you change the level of verbosity of <span class="sollya">Sollya</span>. When the variable is set to 0, <span class="sollya">Sollya</span> becomes completely silent on standard output and prints only very important messages on standard error. Increase <code class="key">verbosity</code> if you want more information about what <span class="sollya">Sollya</span> is doing. Please keep in mind that when you affect a value to a global variable, a message is always printed even if <code class="com">verbosity</code> is set to 0. In order to silently affect a global variable, use&nbsp;<code>!</code>:
<p>
<?php include("introExample9.php"); ?>
<p>
For conviviality reasons, values are displayed in decimal by default. This lets a normal human being understand the numbers they manipulate. But since constants are internally represented in binary, this causes permanent conversions that are sources of roundings. Thus you are loosing in accuracy and <span class="sollya">Sollya</span> is always complaining about inexact results. If you just want to store or communicate your results (to another tools for instance) you can use bit-exact representations available in <span class="sollya">Sollya</span>. The global variable <code class="key">display</code> defines the way constants are displayed. Here is an example of the five available modes:
<p>
<?php include("introExample10.php"); ?>
<p>
Please keep in mind that it is possible to maintain the general verbosity level at
some higher setting while deactivating all warnings on roundings. This
feature is controlled using the <code class="key">roundingwarnings</code> global
variable. It may be set to <code class="key">on</code> or <code class="key">off</code>. By default, the
warnings are activated (<code class="key">roundingwarnings = on</code>) when <span class="sollya">Sollya</span> is
connected on standard input to a pseudo-file that represents a
terminal. They are deactivated when <span class="sollya">Sollya</span> is connected on standard
input to a real file. See <a href="help.php?name=roundingwarnings&amp;goBack=none">roundingwarnings</a> for further details; the behavior is
illustrated with examples there.
<p>
                                                                     As always, the symbol <code>e</code> means (* 10^x). The same way the symbol <code>b</code> means  (* 2^x). The symbol <code>p</code> means (* 16^x) and is used only with the <code>0x</code> prefix. The prefix <code>0x</code> indicates that the digits of the following number until 
a symbol <code>p</code> or white-space are hexadecimal. The suffix <code>_2</code> indicates to <span class="sollya">Sollya</span> that the previous number has been written in binary. <span class="sollya">Sollya</span> can parse these notations even if you are not in the corresponding <code class="key">display</code> mode, so you can always use them.
<p>
You can also use memory-dump hexadecimal notation frequently used to represent IEEE 754 <code>double</code> and <code>single</code> precision numbers. Since this notation does not allow for exactly representing numbers with arbitrary precision, there is no corresponding <code class="key">display</code> mode. However, the commands <code class="com">printdouble</code> respectively <code class="com">printsingle</code> round the value to the nearest <code>double</code> respectively <code>single</code>. The number is then printed in hexadecimal as the integer number corresponding to the memory representation of the IEEE 754 <code>double</code> or <code>single</code> number:
<p>
<?php include("introExample11.php"); ?>
<p>
<span class="sollya">Sollya</span> can parse these memory-dump hexadecimal notation back in any
<code class="key">display</code> mode. The difference of this memory-dump
notation with the hexadecimal notation (as defined above) is made by
the presence or absence of a <code>p</code> indicator.

<a name="variables"></a>
<h1>4 - Variables</h1>
<p>
As already explained, <span class="sollya">Sollya</span> can manipulate variate functional
expressions in one variable. These expressions contain a unique free variable the name
of which is fixed by its first usage in an expression that is not a
left-hand-side of an assignment. This global and unique free variable is 
a variable in the mathematical sense of the term. 
<p>
<span class="sollya">Sollya</span> also provides variables in the sense programming languages
give to the term.  These variables, which must be different in their
name from the global free variable, may be global or declared and
attached to a block of statements, i.e. a begin-end-block. These
programming language variables may hold any object of the <span class="sollya">Sollya</span>
language, as for example functional expressions, strings, intervals,
constant values, procedures, external functions and procedures, etc.
<p>
Global variables need not to be declared. They start existing,
i.e. can be correctly used in expressions that are not left-hand-sides
of assignments, when they are assigned a value in an assignment. Since
they are global, this kind of variables is recommended only for small
<span class="sollya">Sollya</span> scripts.  Larger scripts with code reuse should use
declared variables in order to avoid name clashes for example in loop
variables.
<p>
Declared variables are attached to a begin-end-block. The block
structure builds scopes for declared variables. Declared variables in
inner scopes shadow (global and declared) variables of outer
scopes. The global free variable, i.e. the mathematical variable for
variate functional expressions in one variable, cannot be shadowed. Variables are
declared using the <code class="key">var</code> keyword. See section <a href="help.php?name=var&amp;goBack=none">var</a> for details
on its usage and semantic.
<p>
The following code examples illustrate the use of variables.
<p>
<?php include("introExample12.php"); ?>
<p>
Let us state that a variable identifier, just as every identifier in
<span class="sollya">Sollya</span>, contains at least one character, starts with a ASCII letter
and continues with ASCII letters or numerical digits.
<h1>5 - Data types</h1>
<p>
<span class="sollya">Sollya</span> has a (very) basic system of types. If you try to perform an illicit operation (such as adding a number and a string, for instance), you will get a typing error. Let us see the available data types.
<p>
<h2>5.1 - Booleans</h2>
<p>
There are two special values <code class="key">true</code> and <code class="key">false</code>. Boolean expressions can be constructed using the boolean connectors <code class="key">&&</code> (and), <code class="key">||</code> (or), <code class="key">!</code> (not), and cosmparisons.
<p>
The comparison operators <code class="key"><</code>, <code class="key"><=</code>, <code class="key">></code> and <code class="key">>=</code> can only be used between two numbers or constant expressions.
<p>
The comparison operators <code class="key">==</code> and <code class="key">!=</code> are polymorphic. You can use them to compare any two objects, like two strings, two intervals, etc. As a matter of fact, polymorphism is allowed on both sides: it is possible to compare objects of different type. Such objects of different type, as they can never be syntactically equal, will always compare unequal (see exception for <code class="key">error</code>, section <a href="help.php?name=error&amp;goBack=none">error</a>) and never equal. It is important to remember that testing the equality between two functions will return <code class="key">true</code> if and only if the expression trees representing the two functions are exactly the same. See <a href="help.php?name=error&amp;goBack=none">error</a> for an exception concerning the special object <code class="key">error</code>. Example:
<p>
<?php include("introExample13.php"); ?>

<p><a name="sec:numbers"></a>
<h2>5.2 - Numbers</h2> 
<p>
<span class="sollya">Sollya</span> represents numbers as binary multi-precision floating-point values. For integer values and values in dyadic, binary, hexadecimal or memory dump notation, it 
automatically uses a precision needed for representing the value exactly (unless this behaviour is overridden using the syntax given below). Additionally, automatic precision adaption takes place for all 
integer values (even in decimal notation) written without the exponent sign <code>e</code> or with the exponent sign <code>e</code> and an exponent sufficiently 
small that they are less than 10^999. Otherwise the values are represented with the current precision <code class="com">prec</code>. When a number must be rounded, it is rounded to the precision <code class="com">prec</code> before the expression get evaluated:
<p>
<?php include("introExample14.php"); ?>
<p>
As a matter of fact, each variable has its own precision that corresponds to its intrinsic precision or, if it cannot be represented, to the value of <code class="com">prec</code> when the variable was set. Thus you can work with variables having a precision higher than the current precision.
<p>
The same way, if you define a function that refers to some constant, this constant is stored in the function with the current precision and will keep this value in the future, even if <code class="com">prec</code> becomes smaller.
<p>
If you define a function that refers to some variable, the precision of the variable is kept, independently of the current precision:
<p>
<?php include("introExample15.php"); ?>
<p>
In some rare cases, it is necessary to read in decimal constants with
a particular precision being used in the conversion to the binary
floating-point format, which <span class="sollya">Sollya</span> uses. Setting <code class="key">prec</code> to that
precision may prove to be an insufficient means for doing so, for
example when several different precisions have to be used in one
expression. For these rare cases, <span class="sollya">Sollya</span> provides the following
syntax: decimal constants may be written <code>%</code><em>precision</em><code>%</code><em>constant</em>, where <em>precision</em> is
a constant integer, written in decimal, and <em>constant</em> is the
decimal constant. <span class="sollya">Sollya</span> will convert the constant <em>constant</em>
with precision <em>precision</em>, regardless of the global variable
<code class="key">prec</code> and regardless if <em>constant</em> is an integer or would
otherwise be representable.
<p>
<?php include("introExample44.php"); ?>
<p>
<span class="sollya">Sollya</span> is an environment that uses floating-point arithmetic. The
IEEE 754-2008 standard on floating-point arithmetic does not only
define floating-point numbers that represent real numbers but also
floating-point data representing infinities and Not-a-Numbers (NaNs).
<span class="sollya">Sollya</span> also supports infinities and NaNs in the spirit of the IEEE
754-2008 standard without taking the standard's choices literally. 
<p>
<ul>
<li> Signed infinities are available through the <span class="sollya">Sollya</span> objects
<code>infty, -infty, @Inf@</code> and <code>-@Inf@</code>.
</li><li> Not-a-Numbers are supported through the <span class="sollya">Sollya</span> objects
<code>NaN</code> and <code>@NaN@</code>. <span class="sollya">Sollya</span> does not have support for NaN
payloads, signaling or quiet NaNs or signs of NaNs. Signaling NaNs
are supported on input for single and double precision memory
notation (see section <a href="#sec:general_principles">General Principles</a>). However, they
immediately get converted to plain <span class="sollya">Sollya</span> NaNs.
</li></ul>
<p>
The evaluation of an expression involving a NaN or the evaluation of a
function at a point being NaN always results in a NaN. 
<p>
Infinities are considered to be the limits of expressions tending to
infinity. They are supported as bounds of intervals in some
cases. However, particular commands might prohibit their use even
though there might be a mathematical meaning attached to such
expressions. For example, while <span class="sollya">Sollya</span> will evaluate expressions such
as the limit of e^x when x goes to -infinity, expressed e.g. through
<code>evaluate(exp(x),[-infty;0])</code>, it will not accept to compute
the (finite) value of the integral of e^x between -infinity and 0.
<p>
The following examples give an idea of what can be done with <span class="sollya">Sollya</span>
infinities and NaNs. Here is what can be done with infinities:
<?php include("introExample32.php"); ?>
<p>
And the following example illustrates NaN behavior.
<?php include("introExample33.php"); ?>

<p><a name="sec:rationalmode"></a>
<h2>5.3 - Rational numbers and rational arithmetic</h2>
<p>
The <span class="sollya">Sollya</span> tool is mainly based on floating-point arithmetic:
wherever possible, floating-point algorithms, including algorithms
using interval arithmetic, are used to produce approximate but safe
results. For some particular cases, floating-point arithmetic is not
sufficient: some algorithms just require natural and rational numbers
to be handled exactly. More importantly, for these applications, it is
required that rational numbers be displayed as such.
<p>
<span class="sollya">Sollya</span> implements a particular mode that offers a lightweight support
for rational arithmetic. When needed, it can be enabled by assigning
<code class="com">on</code> to the global variable <code class="com">rationalmode</code>. It is disabled by
assigning <code class="com">off</code>; the default is <code class="com">off</code>.
<p>
When the mode for rational arithmetic is enabled, <span class="sollya">Sollya</span>'s behavior
will change as follows:
<ul>
<li> When a constant expression is given at the <span class="sollya">Sollya</span> prompt,
  <span class="sollya">Sollya</span> will first try to simplify the expression to a rational
  number. If such an evaluation to a rational number is possible,
  <span class="sollya">Sollya</span> will display that number as an integer or a fraction of two
  integers. Only if <span class="sollya">Sollya</span> is not able to simplify the constant
  expression to a rational number, it will launch the default behavior
  of evaluating constant expressions to floating-point numbers that
  are generally faithful roundings of the expressions.
<li> When the global mode <code class="com">autosimplify</code> is <code class="com">on</code>, which is
  the default, <span class="sollya">Sollya</span> will additionally use rational arithmetic while
  trying to simplify expressions given in argument of commands. 
</li></ul>
<p>
Even when <code class="com">rationalmode</code> is <code class="com">on</code>, <span class="sollya">Sollya</span> will not be able to
exhibit integer ratios between transcendental quantities. For example,
<span class="sollya">Sollya</span> will not display 1/6 for arcsin(1/2)/pi but 0.16666... <span class="sollya">Sollya</span>'s evaluator
for rational arithmetic is only able to simplify rational expressions
based on addition, subtraction, multiplication, division, negation,
perfect squares (for square root) and integer powers.
<p>
The following example illustrates what can and what cannot be done
with <span class="sollya">Sollya</span>'s mode for rational arithmetic: 
<p>
<?php include("introExample34.php"); ?>

<h2>5.4 - Intervals and interval arithmetic</h2>
<p>
<span class="sollya">Sollya</span> can manipulate intervals that are closed subsets of the real
numbers. Several ways of defining intervals exist in <span class="sollya">Sollya</span>. There is the
most common way where intervals are composed of two numbers or
constant expressions representing the lower and the upper bound. These
values are separated either by commas or semi-colons. Interval bound 
evaluation is performed in a way that ensures the inclusion property:
all points in the original, unevaluated interval will be contained in
the interval with its bounds evaluated to floating-point numbers. 
<p>
<?php include("introExample16.php"); ?>
<p>
<span class="sollya">Sollya</span> has a mode for printing intervals that are that thin that
their bounds have a number of decimal digits in common when
printed. That mode is called <code class="com">midpointmode</code>; see below for an
introduction and section <a href="help.php?name=midpointmode&amp;goBack=none">midpointmode</a> for details. As <span class="sollya">Sollya</span>
must be able to parse back its own output, a syntax is provided to
input intervals in midpoint&nbsp;mode. However, please pay attention to the fact that the
notation used in midpoint&nbsp;mode generally increases the width of
intervals: hence when an interval is displayed in midpoint&nbsp;mode and
read again, the resulting interval may be wider than the original
interval.
<p>
<?php include("introExample41.php"); ?>
<p>
In some cases, intervals become infinitely thin in theory, in which
case one tends to think of point intervals even if their
floating-point representation is not infinitely thin. <span class="sollya">Sollya</span> provides
a very covenient way for input of such point intervals. Instead of
writing <code>[a;a]</code>, it is possible to just write
<code>[a]</code>. <span class="sollya">Sollya</span> will expand the notation while making sure that
the inclusion property is satisfied:
<p>
<?php include("introExample38.php"); ?>
<p>
When the mode <code class="com">midpointmode</code> is set to <code class="com">on</code> (see
<a href="help.php?name=midpointmode&amp;goBack=none">midpointmode</a>), <span class="sollya">Sollya</span> will display intervals that are
provably reduced to one point in this extended interval syntax. It
will use <code class="com">midpointmode</code> syntax for intervals that are sufficiently
thin but not reduced to one point (see section <a href="help.php?name=midpointmode&amp;goBack=none">midpointmode</a>
for details):
<p>
<?php include("introExample40.php"); ?>
<p>
<span class="sollya">Sollya</span> intervals are internally represented with floating-point
numbers as bounds; rational numbers are not supported here. If bounds
are defined by constant expressions, these are evaluated to
floating-point numbers using the current precision. Numbers or
variables containing numbers keep their precision for the interval
bounds.
<p>
Constant expressions get evaluated to floating-point values
immediately; this includes pi and rational numbers, even when
<code class="com">rationalmode</code> is <code class="com">on</code> (see section <a href="#sec:rationalmode">Rational numbers and rational arithmetic</a> for
this mode).
<p>
<?php include("introExample17.php"); ?>
<p>
You can get the upper-bound (respectively the lower-bound) of an interval with the command <code class="com">sup</code> (respectively <code class="com">inf</code>). The middle of the interval can be computed with the command <code class="com">mid</code>. Let us also mention that these commands can also be used on numbers (in that case, the number is interpreted as an interval containing only one single point. In that case the commands <code class="com">inf</code>, <code class="com">mid</code> and <code class="com">sup</code> are just the identity):
<p>
<?php include("introExample18.php"); ?>
<p>
Let us mention that the <code class="com">mid</code> operator never provokes a
rounding. It is rewritten as an unevaluated expression in terms of
<code class="com">inf</code> and <code class="com">sup</code>.
<p>
<span class="sollya">Sollya</span> permits intervals to also have non-real bounds, such as
infinities or NaNs. When evaluating certain expressions, in particular
given as interval bounds, <span class="sollya">Sollya</span> will itself generate intervals
containing infinities or NaNs. When evaluation yields an interval with
a NaN bound, the given expression is most likely undefined or
numerically unstable. Such results should not be trusted; a warning is
displayed.
<p>
While computations on intervals with bounds being NaN will always
fail, <span class="sollya">Sollya</span> will try to interpret infinities in the common way as
limits. However, this is not guaranteed to work, even if it is
guaranteed that no unsafe results will be produced. See also section
<a href="#sec:numbers">Numbers</a> for more detail on infinities in <span class="sollya">Sollya</span>.
   The behavior of interval arithmetic on intervals containing infinities or NaNs is subject to debate; moreover, there is no complete consensus on what should be the result of the evaluation of a function f over an interval I containing points where f is not defined. <span class="sollya">Sollya</span> has its own philosophy regarding these questions. This philosophy is explained in <a href="#IntervalArithmeticPhilopshy">Appendix&nbsp;9</a> at the end of this document.

<p>
<?php include("introExample39.php"); ?>
<p>
<span class="sollya">Sollya</span> internally uses interval arithmetic extensively to provide
safe answers. In order to provide for algorithms written in the
<span class="sollya">Sollya</span> language being able to use interval arithmetic, <span class="sollya">Sollya</span> offers
native support of interval arithmetic. Intervals can be added,
subtracted, multiplied, divided, raised to powers, for short, given in
argument to any <span class="sollya">Sollya</span> function. The tool will apply the rules of
interval arithmetic in order to compute output intervals that safely
encompass the hull of the image of the function on the given interval:
<p>
<?php include("introExample42.php"); ?>
<p>
When such expressions involving intervals are given, <span class="sollya">Sollya</span> will
follow the rules of interval arithmetic in precision <code class="com">prec</code> for
immediately evaluating them to interval enclosures. While <span class="sollya">Sollya</span>'s
evaluator always guarantees the inclusion property, it also applies
some optimisations in some cases in order to make the image interval
as thin as possible. For example, <span class="sollya">Sollya</span> will use a Taylor expansion
based evaluation if a composed function, call it f, is applied to an
interval. In other words, in this case <span class="sollya">Sollya</span> will behave as if the
<code class="com">evaluate</code> command (see section <a href="help.php?name=evaluate&amp;goBack=none">evaluate</a>) were implicitly
used. In most cases, the result will be different from the one obtained
by replacing all occurences of the free variable of a function by the 
interval the function is to be evaluated on:
<p>
<?php include("introExample43.php"); ?>
<p>
<h2>5.5 - Functions</h2>
<p>
<span class="sollya">Sollya</span> knows only about functions with one single variable. The first time in a session that an unbound name is used (without being assigned) it determines the name used to refer to the free variable.
<p>
The basic functions available in <span class="sollya">Sollya</span> are the following:
<ul>
<li> <code class="com">+</code>, <code class="com">-</code>, <code class="com">*</code>, <code class="com">/</code>, <code class="com">^</code>
</li><li> <code class="com">sqrt</code>
</li><li> <code class="com">abs</code>
</li><li> <code class="com">sin</code>, <code class="com">cos</code>, <code class="com">tan</code>, <code class="com">sinh</code>, <code class="com">cosh</code>, <code class="com">tanh</code>
</li><li> <code class="com">asin</code>, <code class="com">acos</code>, <code class="com">atan</code>, <code class="com">asinh</code>, <code class="com">acosh</code>, <code class="com">atanh</code>
</li><li> <code class="com">exp</code>, <code class="com">expm1</code> (defined as <code>expm1(x)</code> = exp(x)-1)
</li><li> <code class="com">log</code> (natural logarithm), <code class="com">log2</code> (binary logarithm), <code class="com">log10</code> (decimal logarithm), <code class="com">log1p</code> (defined as <code>log1p(x)</code> = log(1+x))
</li><li> <code class="com">erf</code>, <code class="com">erfc</code>
</li><li> <code class="com">single</code>, <code class="com">double</code>, <code class="com">doubleextended</code>, <code class="com">doubledouble</code>, <code class="com">tripledouble</code> (see sections <a href="help.php?name=single&amp;goBack=none">single</a>, <a href="help.php?name=double&amp;goBack=none">double</a>, <a href="help.php?name=doubleextended&amp;goBack=none">doubleextended</a>, <a href="help.php?name=doubledouble&amp;goBack=none">doubledouble</a> and <a href="help.php?name=tripledouble&amp;goBack=none">tripledouble</a>)
</li><li> <code class="com">SG</code>, <code class="com">D</code>, <code class="com">DE</code>, <code class="com">DD</code>, <code class="com">TD</code> (see sections <a href="help.php?name=single&amp;goBack=none">single</a>, <a href="help.php?name=double&amp;goBack=none">double</a>, <a href="help.php?name=doubleextended&amp;goBack=none">doubleextended</a>, <a href="help.php?name=doubledouble&amp;goBack=none">doubledouble</a> and <a href="help.php?name=tripledouble&amp;goBack=none">tripledouble</a>)
</li><li> <code class="com">floor</code>, <code class="com">ceil</code>, <code class="com">nearestint</code>.
</li></ul>
<p>
The constant pi is available through the keyword <code class="key">pi</code> as a 0-ary function: 
<p>
<?php include("introExample19.php"); ?>
<p>
The reader may wish to see Sections <a href="help.php?name=library&amp;goBack=none">library</a> and <a href="help.php?name=function&amp;goBack=none">function</a> for ways of dynamically adding other base functions to Sollya.
<h2>5.6 - Strings</h2>
<p>
Anything written between quotes is interpreted as a string. The infix operator <code class="com">@</code> concatenates two strings. To get the length of a string, use the <code class="com">length</code> function. You can access the i-th character of a string using brackets (see the example below). There is no character type in <span class="sollya">Sollya</span>: the i-th character of a string is returned as a string itself.
<p>
<?php include("introExample20.php"); ?>
<p>
Strings may contain the following escape sequences:
<code>\\</code>, <code>\&ldquo;</code>,
<code>\?</code>, <code>\'</code>,
<code>\n</code>, <code>\t</code>,
<code>\a</code>, <code>\b</code>,
<code>\f</code>, <code>\r</code>,
<code>\v</code>, <code>\x</code>[hexadecimal number] and
<code>\</code>[octal number]. Refer to the C99 standard for their
meaning.
<p>
<h2>5.7 - Particular values</h2>
<p>
<span class="sollya">Sollya</span> knows about some particular values. These values do not really have a type. They can be stored in variables and in lists. A (possibly not exhaustive) list of such values is the following one:
<p>
<ul>
<li> <code class="com">on</code>, <code class="com">off</code> (see sections <a href="help.php?name=on&amp;goBack=none">on</a> and <a href="help.php?name=off&amp;goBack=none">off</a>)
</li><li> <code class="com">dyadic</code>, <code class="com">powers</code>, <code class="com">binary</code>, <code class="com">decimal</code>, <code class="com">hexadecimal</code> (see sections <a href="help.php?name=dyadic&amp;goBack=none">dyadic</a>, <a href="help.php?name=powers&amp;goBack=none">powers</a>, <a href="help.php?name=binary&amp;goBack=none">binary</a>, <a href="help.php?name=decimal&amp;goBack=none">decimal</a> and <a href="help.php?name=hexadecimal&amp;goBack=none">hexadecimal</a>)
</li><li> <code class="com">file</code>, <code class="com">postscript</code>, <code class="com">postscriptfile</code> (see sections <a href="help.php?name=file&amp;goBack=none">file</a>, <a href="help.php?name=postscript&amp;goBack=none">postscript</a> and <a href="help.php?name=postscriptfile&amp;goBack=none">postscriptfile</a>)
</li><li> <code class="com">RU</code>, <code class="com">RD</code>, <code class="com">RN</code>, <code class="com">RZ</code> (see sections <a href="help.php?name=ru&amp;goBack=none">ru</a>, <a href="help.php?name=rd&amp;goBack=none">rd</a>, <a href="help.php?name=rn&amp;goBack=none">rn</a> and <a href="help.php?name=rz&amp;goBack=none">rz</a>)
</li><li> <code class="com">absolute</code>, <code class="com">relative</code> (see sections <a href="help.php?name=absolute&amp;goBack=none">absolute</a> and <a href="help.php?name=relative&amp;goBack=none">relative</a>)
</li><li> <code class="com">floating</code>, <code class="com">fixed</code> (see sections <a href="help.php?name=floating&amp;goBack=none">floating</a> and <a href="help.php?name=fixed&amp;goBack=none">fixed</a>)
</li><li> <code class="com">single</code>, <code class="com">double</code>, <code class="com">doubleextended</code>, <code class="com">doubledouble</code>, <code class="com">tripledouble</code> (see sections <a href="help.php?name=single&amp;goBack=none">single</a>, <a href="help.php?name=double&amp;goBack=none">double</a>, <a href="help.php?name=doubleextended&amp;goBack=none">doubleextended</a>, <a href="help.php?name=doubledouble&amp;goBack=none">doubledouble</a> and <a href="help.php?name=tripledouble&amp;goBack=none">tripledouble</a>)
</li><li> <code class="com">SG</code>, <code class="com">D</code>, <code class="com">DE</code>, <code class="com">DD</code>, <code class="com">TD</code> (see sections <a href="help.php?name=single&amp;goBack=none">single</a>, <a href="help.php?name=double&amp;goBack=none">double</a>, <a href="help.php?name=doubleextended&amp;goBack=none">doubleextended</a>, <a href="help.php?name=doubledouble&amp;goBack=none">doubledouble</a> and <a href="help.php?name=tripledouble&amp;goBack=none">tripledouble</a>)
</li><li> <code class="com">perturb</code> (see section <a href="help.php?name=perturb&amp;goBack=none">perturb</a>)
</li><li> <code class="com">honorcoeffprec</code> (see section <a href="help.php?name=honorcoeffprec&amp;goBack=none">honorcoeffprec</a>)
</li><li> <code class="com">default</code> (see section <a href="help.php?name=default&amp;goBack=none">default</a>)
</li><li> <code class="com">error</code> (see section <a href="help.php?name=error&amp;goBack=none">error</a>)
</li><li> <code class="com">void</code> (see section <a href="help.php?name=void&amp;goBack=none">void</a>)
</li></ul>
<p>
<h2>5.8 - Lists</h2>
<p>
Objects can be grouped into lists. A list can contain elements with different types. As for strings, you can concatenate two lists with <code class="com">@</code>. The function <code class="com">length</code> also gives the length of a list.
<p>
You can prepend an element to a list using <code class="com">.:</code> and you can append an element to a list using <code class="com">:.</code>\\ The following example illustrates some features:
<p>
<?php include("introExample21.php"); ?>
<p>
Lists can be considered arrays and elements of lists can be
referenced using brackets. Possible indices start at 0. The
following example illustrates this point:
<p>
<?php include("introExample22.php"); ?>
<p>
Please be aware of the fact that the complexity for accessing an
element of the list using indices is&nbsp;O(n), where n is the length of the whole list.
<p>
Lists may contain ellipses indicated by <code>,...,</code> between
elements that are constant and evaluate to integers that are
incrementally ordered. <span class="sollya">Sollya</span> translates such ellipses to the full
list upon evaluation. The use of ellipses between elements that are not
constants is not allowed. This feature is provided for ease of
programming; remark that the complexity for expanding such lists is
high. For illustration, see the following example:
<p>
<?php include("introExample23.php"); ?>
<p>
Lists may be continued to infinity by means of the <code>...</code>
indicator after the last element given. At least one element must
explicitly be given. If the last element given is a constant
expression that evaluates to an integer, the list is considered as
continued to infinity by all integers greater than that last
element. If the last element is another object, the list is considered
as continued to infinity by re-duplicating this last element. Let us remark
that bracket notation is supported for such end-elliptic lists even
for implicitly given elements. However, evaluation complexity is
high. Combinations of ellipses inside a list and in its end are
possible. The usage of lists described here is best illustrated by the
following examples:
<p>
<?php include("introExample24.php"); ?>
<p>

<h2>5.9 - Structures</h2>
<p>
In a similar way as in lists, <span class="sollya">Sollya</span>
allows data to be grouped in - untyped - structures. A structure forms
an object to which other objects can be added as elements and
identified by their names. The elements of a structure can be
retrieved under their name and used as usual. The following sequence
shows that point:
<p>
<?php include("introExample46.php"); ?>

<p>
Structures can also be defined literally using the syntax illustrated
in the next example. They will also be printed in that syntax.
<p>
<?php include("introExample47.php"); ?>

<p>
If the variable <code class="com">a</code> is bound to an existing structure, it is possible to use the ``dot notation'' <code class="com">a.b</code> to assign the value of the field <code class="com">b</code> of the structure <code class="com">a</code>. This works even if <code class="com">b</code> is not yet a field of <code class="com">a</code>: in this case a new field is created inside the structure <code class="com">a</code>. 

<p>
Besides, the dot notation can be used even when <code class="com">a</code> is unassigned. In this case a new structure is created with a field <code class="com">b</code>, and this structure is bound to <code class="com">a</code>. However, the dot notation cannot be used if <code class="com">a</code> is already bound to something that is not a structure.

<p>
These principles apply recursively: for instance, if <code class="com">a</code> is a structure that contains only one field <code class="com">d</code>, the command <code class="com">a.b.c = 3</code> creates a new field named <code class="com">b</code> inside the structure <code class="com">a</code>; this field itself is a structure containing the field <code class="com">c</code>. The command <code class="com">a.d.c = 3</code> is allowed if <code class="com">a.d</code> is already a structure, but forbidden otherwise (e.g. if <code class="com">a.d</code> was equal to <code class="com">sin(x)</code>). This is summed up in the following example.

<p>
<?php include("introExample48.php"); ?>

<p>
When printed, the elements of a structure are not sorted in any
manner. They get printed in an arbitrary order that just maintains the
order given in the definition of literate structures. That said, when
compared, two structures compare equal iff they contain the same
number of identifiers, with the same names and iff the elements of
corresponding names all compare equal. This means the order does
not matter in comparisons and otherwise does only for printing.

<p>The following example illustrates this matter:
<p>
<?php include("introExample49.php"); ?>

<h1>6 - Iterative language elements: assignments, conditional statements and loops</h1>
<p>
<h2>6.1 - Blocks</h2>
<p>
Statements in <span class="sollya">Sollya</span> can be grouped in blocks, so-called
begin-end-blocks.  This can be done using the key tokens <code class="key">{</code> and
<code class="key">}</code>. Blocks declared this way are considered to be one single
statement. As already explained in section <a href="#variables">Variables</a>, using
begin-end-blocks also opens the possibility of declaring variables
through the keyword <code class="key">var</code>. 
<p>
<h2>6.2 - Assignments</h2>
<p>
<span class="sollya">Sollya</span> has two different assignment operators, <code>=</code> and
<code>:=</code>. The assignment operator <code>=</code> assigns its
right-hand-object ``as is'', i.e. without evaluating functional
expressions. For instance, <code>i = i + 1;</code> will dereferentiate the
identifier <code>i</code> with some content, notate it y, build up the
expression (function) y + 1 and assign this expression back to
<code>i</code>. In the example, if <code>i</code> stood for the value 1000,
the statement <code>i = i + 1;</code> would assign ``1000 + 1'' -- and not
``1001'' -- to <code>i</code>. The assignment operator <code>:=</code> evaluates
constant functional expressions before assigning them. On other
expressions it behaves like <code>=</code>. Still in the example, the
statement <code>i := i + 1;</code> really assigns 1001 to <code>i</code>.
<p>
Both <span class="sollya">Sollya</span> assignment operators support indexing of lists or strings
elements using brackets on the left-hand-side of the assignment
operator. The indexed element of the list or string gets replaced by
the right-hand-side of the assignment operator.  When indexing strings
this way, that right-hand side must evaluate to a string of length
1. End-elliptic lists are supported with their usual semantic for
this kind of assignment.  When referencing and assigning a value in
the implicit part of the end-elliptic list, the list gets expanded to
the corresponding length.
<p>
The following examples well illustrate the behavior of assignment
statements:
<p>
<?php include("introExample25.php"); ?>
<p>
The indexing of lists on left-hand sides of assignments is reduced to
the first order. Multiple indexing of lists of lists on assignment is
not supported for complexity reasons. Multiple indexing is possible in
right-hand sides.
<p>
<?php include("introExample45.php"); ?>
<p>
<h2>6.3 - Conditional statements</h2>
<p>
<span class="sollya">Sollya</span> supports conditional statements expressed with the keywords
<code class="key">if</code>, <code class="key">then</code> and optionally <code class="key">else</code>. Let us mention that only
conditional statements are supported and not conditional expressions. 
<p>
The following examples illustrate both syntax and semantic of
conditional statements in <span class="sollya">Sollya</span>. Concerning syntax, be aware that there must not be any semicolon
before the <code class="key">else</code> keyword.
<p>
<?php include("introExample26.php"); ?>
<p>
<h2>6.4 - Loops</h2>
<p>
<span class="sollya">Sollya</span> supports three kinds of loops. General <em>while-condition</em>
loops can be expressed using the keywords <code class="key">while</code> and
<code class="key">do</code>. One has to be aware of the fact that the condition test is
executed always before the loop, there is no <em>do-until-condition</em>
loop. Consider the following examples for both syntax and semantic:
<p>
<?php include("introExample27.php"); ?>
<p>
The second kind of loops are loops on a variable ranging from a
numerical start value and a end value. These kind of loops can be
expressed using the keywords <code class="key">for</code>, <code class="key">from</code>, <code class="key">to</code>, <code class="key">do</code>
and optionally <code class="key">by</code>. The <code class="key">by</code> statement indicates the width of
the steps on the variable from the start value to the end value. Once
again, syntax and semantic are best explained with an example:
<p>
<?php include("introExample28.php"); ?>
<p>
The third kind of loops are loops on a variable ranging on values
contained in a list. In order to ensure the termination of the loop,
that list must not be end-elliptic. The loop is expressed using the
keywords <code class="key">for</code>, <code class="key">in</code> and <code class="key">do</code> as in the following
examples:
<p>
<?php include("introExample29.php"); ?>
<p>
For both types of <code class="key">for</code> loops, assigning the loop variable is
allowed and possible. When the loop terminates, the loop variable will
contain the value that made the loop condition fail. Consider the
following examples:
<p>
<?php include("introExample30.php"); ?>
<p>
<h1>7 - Functional language elements: procedures and pattern matching</h1>
<h2>7.1 - Procedures</h2>
<p>
<span class="sollya">Sollya</span> has some elements of functional languages. In order to 
avoid confusion with mathematical functions, the associated 
programming objects are called <em>procedures</em> in <span class="sollya">Sollya</span>. 
<p>
<span class="sollya">Sollya</span> procedures are common objects that can be, for example,
assigned to variables or stored in lists. Procedures are declared by
the <code class="key">proc</code> keyword; see section <a href="help.php?name=proc&amp;goBack=none">proc</a> for details. The
returned procedure object must then be assigned to a variable. It can
hence be applied to arguments with common application syntax. The
<code class="key">procedure</code> keyword provides an abbreviation for declaring and
assigning a procedure; see section <a href="help.php?name=procedure&amp;goBack=none">procedure</a> for details.
<p>
<span class="sollya">Sollya</span> procedures can return objects using the <code class="key">return</code> keyword
at the end of the begin-end-block of the procedure. Section
<a href="help.php?name=return&amp;goBack=none">return</a> gives details on the usage of <code class="key">return</code>. Procedures
further can take any type of object in argument, in particular also
other procedures that are then applied to arguments. Procedures can
be declared inside other procedures. 
<p>
Common <span class="sollya">Sollya</span> procedures are declared with a certain number of formal
parameters. When the procedure is applied to actual parameters, a
check is performed if the right number of actual parameters is
given. Then the actual parameters are applied to the formal
parameters. In some cases, it is required that the number of
parameters of a procedure be variable. <span class="sollya">Sollya</span> provides support for
the case with procedures with an arbitrary number of actual arguments.
When the procedure is called, those actual arguments are gathered in a
list which is applied to the only formal list parameter of a procedure
with an arbitrary number of arguments. See section <a href="help.php?name=procedure&amp;goBack=none">procedure</a>
for the exact syntax and details; an example is given just below.
<p>
Let us remark that declaring a procedure does not involve any evaluation or
other interpretation of the procedure body. In particular, this means
that constants are evaluated to floating-point values inside <span class="sollya">Sollya</span>
when the procedure is applied to actual parameters and the global
precision valid at this moment.
<p>
<span class="sollya">Sollya</span> procedures are well illustrated with the following examples:
<p>
<?php include("introExample31.php"); ?>
<p>
<?php include("introExample35.php"); ?>
<p>
<?php include("introExample36.php"); ?>
<p>
<?php include("introExample37.php"); ?>
<p>
<span class="sollya">Sollya</span> also supports external procedures, i.e. procedures written in
<code>C</code> (or some other language) and dynamically bound to <span class="sollya">Sollya</span>
identifiers. See <a href="help.php?name=externalproc&amp;goBack=none">externalproc</a> for details.

<h2>7.2 - Pattern matching</h2>
<p>
Starting with version 3.0, <span class="sollya">Sollya</span> supports matching expressions with
expression patterns. This feature is important for an extended
functional programming style. Further, and most importantly, it allows
expression trees to be recursively decomposed using native constructs
of the <span class="sollya">Sollya</span> language. This means no help from external procedures
or other compiled-language mechanisms is needed here anymore.
<p>
Basically, pattern matching supports relies on one <span class="sollya">Sollya</span> construct:
<div style="margin-left: 50px;">
  <code class="key">match <em>expr</em> with<br>
  <em>pattern1</em> : (<em>return-expr1</em>)<br>
  <em>pattern2</em> : (<em>return-expr2</em>)<br>
  ... <br>
  <em>patternN</em> : (<em>return-exprN</em>)</code>
</div>

<p>That construct has the following semantic: try to match the
expression <em>expr</em> with the patterns <em>pattern1</em> through <em>patternN</em>,
 proceeding in natural order. If a pattern
<em>patternI</em> is found that matches, evaluate the whole
<code class="key">match&nbsp;...&nbsp;with</code> construct to the return expression <em>return-exprI</em>
associated with the matching pattern <em>patternI</em>. If no matching
pattern is found, display an error warning and return <code class="key">error</code>.
<p>
Matching a pattern means the following: 
<ul>
  <li> If a pattern does not contain any programming-language-level
    variables (different from the free mathematical variable), it
    matches expressions that are syntactically equal to itself. For
    instance, the pattern <code class="key">exp(sin(3&nbsp;*&nbsp;x))</code> will match the
    expression <code class="key">exp(sin(3&nbsp;*&nbsp;x))</code>.
  </li><li> If a pattern does contain variables, it matches an expression
    <em>expr</em> if these variables can be bound to subexpressions of
    <em>expr</em> such that once the pattern is evaluated with that
    variable binding, it becomes syntactically equal to the expression
    <em>expr</em>. For instance, the pattern <code class="key">exp(sin(a&nbsp;*&nbsp;x))</code> will
    match the expression <code class="key">exp(sin(3&nbsp;*&nbsp;x))</code> as it is possible to
    bind <code class="key">a</code> to <code class="key">3</code> such that <code class="key">exp(sin(a&nbsp;*&nbsp;x))</code> evaluates
    to <code class="key">exp(sin(3&nbsp;*&nbsp;x))</code>.
</li></ul>
<p>
If a pattern <em>patternI</em> with variables is matched in a
<code class="key">match&nbsp;...&nbsp;with</code> construct, the variables in the pattern stay bound
during the evaluation of the corresponding return expression <em>return-exprI</em>.
 This allows subexpressions to be extracted from
expressions and/or recursively handled as needed.
<p>
The following examples illustrate the basic principles of pattern
matching in <span class="sollya">Sollya</span>:
<p>
<?php include("introExample50.php"); ?>
<p>
As <span class="sollya">Sollya</span> is not a purely functional language, the
<code class="key">match ...&nbsp;with</code> construct can also be used in a more imperative style,
which makes it become closer to constructs like <code class="key">switch</code> in
<code>C</code> or <code>Perl</code>. In lieu of a simple return expression, a whole
block of imperative statements can be given. The expression to be
returned by that block is indicated in the end of a the block, using
the <code class="key">return</code> keyword. That syntax is illustrated in the next
example:
<p>
<?php include("introExample51.php"); ?>
<p>
In the case when no return statement is indicated for a
statement-block in a <code class="key">match&nbsp;...&nbsp;with</code> construct, the construct
evaluates to the special value <code class="key">void</code> if that pattern matches. 
<p>
In order to well understand pattern matching in <span class="sollya">Sollya</span>, it is
important to realize the meaning of variables in patterns. This
meaning is different from the one usually found for variables. In a
pattern, variables are never evaluated to whatever they might have set
before the pattern is executed. In contrast, all variables in patterns
are new, free variables that will freshly be bound to subexpressions
of the matching expression. If a variable of the same name already
exists, it will be shadowed during the evaluation of the statement
block and the return expression corresponding to the matching
expression. This type of semantic implies that patterns can never be
computed at run-time, they must always be hard-coded
beforehand. However this is necessary to make pattern matching
context-free.
<p>
As a matter of course, all variables figuring in the expression <em>expr</em>
 to be matched are evaluated before pattern matching is
attempted. In fact, <em>expr</em> is a usual <span class="sollya">Sollya</span> expression, not a
pattern.
<p>
In <span class="sollya">Sollya</span>, the use of variables in patterns does not need to be
linear. This means the same variable might appear twice or more in a
pattern. Such a pattern will only match an expression if it contains
the same subexpression, associated with the variable, in all places
indicated by the variable in the pattern.
<p>
The following examples illustrate the use of variables in patterns in
detail:
<p>
<?php include("introExample52.php"); ?>
<p>
<?php include("introExample53.php"); ?>
<p>
Pattern matching is meant to be a means to decompose expressions
structurally. For this reason and in an analogous way to variables, no
evaluation is performed at all on (sub-)expressions that form constant
functions. As a consequence, patterns only match constant expressions
only if they are structurally identical. For example <code class="key">5+1</code> only
matches <code class="key">5+1</code> and not <code class="key">1+5</code>, <code class="key">3+3</code> nor <code class="key">6</code>.
<p>
This general rule on constant expressions admits one exception.
Intervals in <span class="sollya">Sollya</span> can be defined using constant expressions as
bounds. These bounds are immediately evaluated to floating-point
constants, though. In order to permit pattern matching on intervals,
constant expressions given as bounds of intervals that form patterns
are evaluated before pattern matching. However, in order not conflict
with the rules of no evaluation of variables, these constant
expressions as bounds of intervals in patterns must not contain free
variables.
<p>
<?php include("introExample54.php"); ?>
<p>
The <span class="sollya">Sollya</span> keyword <code class="key">default</code> has a special meaning in patterns.
It acts like a wild-card, matching any (sub-)expression, as long as
the whole expression stays correctly typed. Upon matching with
<code class="key">default</code>, no variable gets bound. This feature is illustrated in
the next example:
<p>
<?php include("introExample55.php"); ?>
<p>
In <span class="sollya">Sollya</span>, pattern matching is possible on the following <span class="sollya">Sollya</span>
types and operations defined on them:
<ul>
<li> Expressions that define univariate functions, as explained above,
</li><li> Intervals with one, two or no bound defined in the pattern by a variable,
</li><li> Character sequences, literate or defined using the <code class="key">@</code> operator, possibly with a variable on one of the sides of the <code class="key">@</code> operator,
</li><li> Lists, literate, literate with variables or defined using the <code class="key">.:</code>, <code class="key">:.</code> and <code class="key">@</code> operators, possibly with a variable on one of the sides of the <code class="key">@</code> operator or one or two variables for <code class="key">.:</code> and <code class="key">:.</code>,
</li><li> Structures, literate or literate with variables, and
</li><li> All other <span class="sollya">Sollya</span> objects, matchable with themselves (<code class="key">DE</code> matches <code class="key">DE</code>, <code class="key">on</code> matches <code class="key">on</code>, <code class="key">perturb</code> matches <code class="key">perturb</code> etc.)
</li></ul>
<p>
<?php include("introExample56.php"); ?>
<p>
Concerning intervals, please pay attention to the fact that expressions involving 
intervals are immediately evaluated and that structural pattern matching on functions
on intervals is not possible. This point is illustrated in the next example:
<p>
<?php include("introExample57.php"); ?>
<p>
With respect to pattern matching on lists or character sequences
defined using the <code class="key">@</code> operator, the following is to be mentionned:
<ul>
<li> Patterns like <code class="key">a @ b</code> are not allowed as they would need to
  perform an ambiguous cut of the list or character sequence to be
  matched. This restriction is maintained even if the variables (here
  <code class="key">a</code> and <code class="key">b</code>) are constrained by other occurrences in the
  pattern (for example in a list) which would make the cut
  unambiguous.
</li><li> Recursive use of the <code class="key">@</code> operator (even mixed with the
  operators <code class="key">.:</code> and <code class="key">:.</code>) is possible under the condition
  that there must not exist any other parenthezation of the term in
  concatenations (<code class="key">@</code>) such that the rule of one single variable
  for <code class="key">@</code> above gets violated. For instance,
  <code class="key">( [| 1 |] @ a) @ (b @ [| 4 |])</code> is not possible as it can be re-parenthesized
  <code class="key">[| 1 |] @ (a @ b) @ [| 4 |]</code>, which exhibits the ambiguous case.
</li><li> For lists that are end-elliptic, i.e. prolongated to infinity,
  the <code class="key">@</code> operator does not work for cases that would imply the
  cut of a finite list at the end of an infinite list. It does however
  work for all cases of cuts of infinite lists at the end of infinite
  lists when the necessary suffix condition is fulfilled.
</li></ul>

<p>These points are illustrated in this example:

<?php include("introExample58.php"); ?>
<p>
As mentionned above, pattern matching on <span class="sollya">Sollya</span> structures is
possible. Patterns for such a match are given in a literately,
i.e. using the syntax <code class="key">{ .a&nbsp;=&nbsp;<em>exprA</em>, .b&nbsp;=&nbsp;<em>exprB</em>,&nbsp;...&nbsp;}</code>. A structure pattern <em>sp</em> will be matched by a
structure <em>s</em> iff that structure <em>s</em> contains at least all the
elements (like <code class="key">.a</code>, <code class="key">.b</code> etc.) of the structure pattern
<em>sp</em> and iff each of the elements of the structure <em>s</em> matches
the pattern in the corresponding element of the structure pattern <em>sp</em>. The user should be aware that fact that the structure to be
matched is only supposed to have at least the elements of the pattern
but that it may contain more elements is a particular <span class="sollya">Sollya</span>
feature. For instance with pattern matching, it is hence possible to
ensure that access to particular elements will be possible in a
particular code segment. The following example is meant to clarify
this point:
<p>
<?php include("introExample59.php"); ?>

<p><a name="commandsAndFunctions"></a>
<h1>8 - Commands and functions</h1>
<p>
The list of commands of Sollya is available in two flavours:
<ul>
  <li>As a <a href="help.php">single page containing the description of all the commands.</a></li>
  <li>Or with <a href="help.php?name=listOfCommands&amp;goBack=none">each command on a different page</a> (faster to load).</li>
</ul>

<p><a name="IntervalArithmeticPhilopshy"></a>
<h1>9 - Appendix: interval arithmetic philosophy in <span class="sollya">Sollya</span></h1>
<p>
Although it is currently based on the MPFI library, <span class="sollya">Sollya</span> has its own way of interpreting interval arithmetic when infinities or NaN occur, or when a function is evaluated on an interval containing points out of its domain, etc. This philosophy may differ from the one applied in MPFI. It is also possible that the behavior of <span class="sollya">Sollya</span> does not correspond to the behavior that one would expect, e.g. as a natural consequence of the IEEE-754 standard.

<p>
The topology that we consider is always the usual topology of R bar: R U {-infinity, +infinity}. For any function, if one of its arguments is empty (respectively NaN), we return empty (respectively NaN).

<h2>9.1 - Univariate functions</h2>
<p>
Let f be a univariate basic function and I an interval. We denote by J the result of the interval evaluation of f over I in <span class="sollya">Sollya</span>. If I is completely included in the domain of f, J will usually be the smallest interval (at the current precision) containing the exact image f(I) However, in some cases, it may happen that J is not as small as possible. It is guaranteed however, that J tends to f(I) when the precision of the tool tends to infinity.

<p>
When f is not defined at some point x but is defined on a neighborhood of x, we consider that the ``value'' of f at x is the convex hull of the limit points of f around x. For instance, consider the evaluation of f= tan on [0, Pi]. It is not defined at Pi/2 (and only at this point). The limit points of f around Pi/2 are -infinity and +infinity, so, we return [-infinity, +infinity]. Another example: f=sin on [+infinity]. The function has no limit at this point, but all points of [-1, 1] are limit points. So, we return [-1,1].

<p>
Finally, if I contains a subinterval on which f is not defined, we return [NaN, NaN] (example: sqrt([-1, 2])).

<h2>9.2 - Bivariate functions</h2>
<p>
Let f be a bivariate function and I1 and I2 be intervals. If I1=[x] and I2=[y] are both point-intervals, we return the convex hull of the limit points of f around (x, y) if it exists. In particular, if f is defined at (x, y) we return its value (or a small interval around it, if it is not exactly representable). As an example [1]/[+infinity] returns [0]. Also, [1]/[0] returns [-infinity, +infinity] (note that <span class="sollya">Sollya</span> does not consider signed zeros). If it is not possible to give a meaning to the expression f(I1, I2), we return NaN: for instance [0]/[0] or [0]*[+infinity].

<p>
If one and only one of the intervals is a point-interval (say I1 = [x]), we consider the partial function g: y -> f(x,y) and return the value that would be obtained when evaluating g on I2. For instance, in order to evaluate [0]/I2, we consider the function g defined for every y != 0 by g(y)=0/y=0. Hence, g(I2) = [0] (even if I2 contains 0, by the argument of limit-points). In particular, please note that [0]/[-1, 1] returns [0] even though [0]/[0] returns NaN. This rule even holds when g can only be defined as limit points: for instance, in the case I1/[0] we consider g: x -> x/0. This function cannot be defined <em>stricto sensu</em>, but we can give it a meaning by considering 0 as a limit. Hence g is multivalued and its value is {-infinity, +infinity} for every x. Hence, I1/[0] returns [-infinity, +infinity] when I1 is not a point-interval.

<p>
Finally, if neither I1 nor I2 are point-intervals, we try to give a meaning to f(I1, I2) by an argument of limit-points when possible. For instance [1, 2] / [0, 1] returns [1, +infinity].

<p>
As a special exception to these rules, [0]^[0] returns [1].

</body>
