<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<html>
<head>
<title>Users' manual for the Sollya tool - SVN trunk</title>
<meta name="author" content="Sylvain Chevillard" >
<meta name="copyright" content="2009-2013 Laboratoire de l'Informatique du Parallélisme - UMR CNRS - ENS Lyon - UCB Lyon 1 - INRIA 5668; LORIA (CNRS, INPL, INRIA, UHP, U-Nancy 2), Nancy, France; Laboratoire d'Informatique de Paris 6, Équipe PEQUAN, UPMC Université Paris 06 - CNRS - UMR 7606 - LIP6, Paris, France; INRIA Sophia-Antipolis Méditerranée, APICS Team, Sophia-Antipolis, France">
<meta name="keywords" content="help, sollya, User's Manual">
<meta name="description" content="This is part of Sollya User's Manual">
<meta http-equiv="content-type" content="text/html; charset=UTF-8">
<link href="sollyacss.css" type="text/css" rel="stylesheet">
<style type="text/css"><!--

.todo { color:#ff0000;}

* { line-height: 1.3em; }

h2 {
 font-size: large;
 padding-top: 15px;
}

h3 {
 font-size: medium;
 padding-top: 5px;
}

table {
  margin-left:auto;
  margin-right: auto;
}

dl { counter-reset: item -1; }
dd:before { content: counter(item) ". "; counter-increment: item; }
dd.omit:before { content: "\00a0\00a0\00a0\00a0"; }

 --></style>
</head>
<body>

<p>
<h1 style="text-align:center">Users' manual for the <span class="sollya">Sollya</span> tool - SVN trunk</h1>
<div style="text-align:center; line-height: 1.5em;">Sylvain Chevillard (<a href="sylvain.chevillard@ens-lyon.org">sylvain.chevillard@ens-lyon.org</a>),</div>
<div style="text-align:center; line-height: 1.5em;">Christoph Lauter (<a href="christoph.lauter@ens-lyon.org; line-height: 1.5em;">christoph.lauter@ens-lyon.org</a>)</div>
<div style="text-align:center">and Mioara Joldeș (<a href="joldes@lass.fr">joldes@lass.fr</a>).</div>

<h2 style="margin-top: 3em;">License</h2>
<p style="font-size:small;">
The <span class="sollya">Sollya</span> tool is Copyright &copy;&nbsp;2006-2013 by<br>
<span style="text-indent:3em; display:block;">Laboratoire de l'Informatique du Parallélisme - UMR CNRS - ENS Lyon - UCB Lyon 1 - INRIA 5668, Lyon, France, </span>
<span style="text-indent:3em;display:block;">LORIA (CNRS, INPL, INRIA, UHP, U-Nancy 2), Nancy, France, </span>
<span style="text-indent:3em;display:block;">Laboratoire d'Informatique de Paris 6, Équipe PEQUAN, UPMC Université Paris 06 - CNRS - UMR 7606 - LIP6, Paris, France,</span>
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

<h1>1 - Compilation and installation of <span class="sollya">Sollya</span></h1>
<p>
<span class="sollya">Sollya</span> comes in two flavors:
<ul>
  <li>Either as an interactive tool. This is achieved by running the <span class="sollya">Sollya</span> executable file.</li>
  <li>Or as a C library that provides all the features of the tool within the C programming language.</li>
</ul>
<p>
The installation of the tool and the library follow the same steps, desribed below. The present documentation focuses more on the interactive tool. As a matter of fact, the library works exactly the same way as the tool, so it is necessary to know a little about the tool in order to correctly use the library. The reader who is only interested in the library should at least read the following Sections&nbsp;<a href="#sec:introduction">Introduction</a>,  <a href="#sec:general_principles">General Principles</a> and <a href="#sec:data_types">Data Types</a>. A documentation specifically describing the library usage is available in <a href="#Libsollya">Appendix&nbsp;10</a> at the end of the present documentation.

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
not required to use the <span class="sollya">Sollya</span> interactive tool. Use the <code>-A</code> option of <code>rlwrap</code> for
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

<p><a name="sec:introduction"></a>
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
<span class="sollya">Sollya</span> has a reserved keyword that can always be used to refer to the free variable. This keyword is <code class="key">_x_</code>. This is particularly useful in contexts when the name of the variable is not known: typically when refering to the free variable in a pattern matching or inside a procedure.
<p>
<?php include("introExample3bis.php"); ?>
<p>
As you have seen, you can name functions and easily work with them. The basic thing to do with a function is to evaluate it at some point:
<p>
<?php include("introExample4.php"); ?>
<p>
The printed value is generally a faithful rounding of the exact value at the working precision (i.e. one of the two floating-point numbers enclosing the exact value). Internally <span class="sollya">Sollya</span> represents numbers as floating-point numbers in arbitrary precision with radix&nbsp;2: the fact that a faithful rounding is performed in binary does not imply much on the exactness of the digits displayed in decimal. The working precision is controlled by the global variable <code class="key">prec</code>:
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

<a name="sec:data_types"></a>
<h1>5 - Data types</h1>
<p>
<span class="sollya">Sollya</span> has a (very) basic system of types. If you try to perform an illicit operation (such as adding a number and a string, for instance), you will get a typing error. Let us see the available data types.
<p>
<h2>5.1 - Booleans</h2>
<p>
There are two special values <code class="key">true</code> and <code class="key">false</code>. Boolean expressions can be constructed using the boolean connectors <code class="key">&&</code> (and), <code class="key">||</code> (or), <code class="key">!</code> (not), and cosmparisons.
<p>
The comparison operators <code class="key"><</code>, <code class="key">&lt;=</code>, <code class="key">></code> and <code class="key">&gt;=</code> can only be used between two numbers or constant expressions.
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
</li><li> <code class="com">halfprecision</code>, <code class="com">single</code>, <code class="com">double</code>, <code class="com">doubleextended</code>, <code class="com">doubledouble</code>, <code class="com">quad</code>, <code class="com">tripledouble</code> (see sections <a href="help.php?name=halfprecision&amp;goBack=none">halfprecision</a>, <a href="help.php?name=single&amp;goBack=none">single</a>, <a href="help.php?name=double&amp;goBack=none">double</a>, <a href="help.php?name=doubleextended&amp;goBack=none">doubleextended</a>, <a href="help.php?name=doubledouble&amp;goBack=none">doubledouble</a>, <a href="help.php?name=quad&amp;goBack=none">quad</a> and <a href="help.php?name=tripledouble&amp;goBack=none">tripledouble</a>)
</li><li> <code class="com">HP</code>, <code class="com">SG</code>, <code class="com">D</code>, <code class="com">DE</code>, <code class="com">DD</code>, <code class="com">QD</code>, <code class="com">TD</code> (see sections <a href="help.php?name=halfprecision&amp;goBack=none">halfprecision</a>, <a href="help.php?name=single&amp;goBack=none">single</a>, <a href="help.php?name=double&amp;goBack=none">double</a>, <a href="help.php?name=doubleextended&amp;goBack=none">doubleextended</a>, <a href="help.php?name=doubledouble&amp;goBack=none">doubledouble</a>, <a href="help.php?name=quad&amp;goBack=none">quad</a> and <a href="help.php?name=tripledouble&amp;goBack=none">tripledouble</a>)
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
</li><li> <code class="com">halfprecision</code>, <code class="com">single</code>, <code class="com">double</code>, <code class="com">doubleextended</code>, <code class="com">doubledouble</code>, <code class="com">quad</code>, <code class="com">tripledouble</code> (see sections <a href="help.php?name=halfprecision&amp;goBack=none">halfprecision</a>, <a href="help.php?name=single&amp;goBack=none">single</a>, <a href="help.php?name=double&amp;goBack=none">double</a>, <a href="help.php?name=doubleextended&amp;goBack=none">doubleextended</a>, <a href="help.php?name=doubledouble&amp;goBack=none">doubledouble</a>, <a href="help.php?name=quad&amp;goBack=none">quad</a> and <a href="help.php?name=tripledouble&amp;goBack=none">tripledouble</a>)
</li><li> <code class="com">HP</code>, <code class="com">SG</code>, <code class="com">D</code>, <code class="com">DE</code>, <code class="com">DD</code>, <code class="com">QD</code>, <code class="com">TD</code> (see sections <a href="help.php?name=halfprecision&amp;goBack=none">halfprecision</a>, <a href="help.php?name=single&amp;goBack=none">single</a>, <a href="help.php?name=double&amp;goBack=none">double</a>, <a href="help.php?name=doubleextended&amp;goBack=none">doubleextended</a>, <a href="help.php?name=doubledouble&amp;goBack=none">doubledouble</a>, <a href="help.php?name=quad&amp;goBack=none">quad</a> and <a href="help.php?name=tripledouble&amp;goBack=none">tripledouble</a>)
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
You can prepend an element to a list using <code class="com">.:</code> and you can append an element to a list using <code class="com">:.</code><br> The following example illustrates some features:
<p>
<?php include("introExample21.php"); ?>
<p>
Lists can be considered arrays and elements of lists can be
referenced using brackets. Possible indices start at 0. The
following example illustrates this point:
<p>
<?php include("introExample22.php"); ?>
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
If the variable <code class="com">a</code> is bound to an existing structure, it is possible to use the &ldquo;dot notation&rdquo; <code class="com">a.b</code> to assign the value of the field <code class="com">b</code> of the structure <code class="com">a</code>. This works even if <code class="com">b</code> is not yet a field of <code class="com">a</code>: in this case a new field is created inside the structure <code class="com">a</code>. 

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
right-hand-object &ldquo;as is&rdquo;, i.e. without evaluating functional
expressions. For instance, <code>i = i + 1;</code> will dereferentiate the
identifier <code>i</code> with some content, notate it y, build up the
expression (function) y + 1 and assign this expression back to
<code>i</code>. In the example, if <code>i</code> stood for the value 1000,
the statement <code>i = i + 1;</code> would assign &ldquo;1000 + 1&rdquo; -- and not
&ldquo;1001&rdquo; -- to <code>i</code>. The assignment operator <code>:=</code> evaluates
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
Let us note that, when writing a procedure, one does not know what will be the name of the free variable at run-time. This is typically the context when one should use the special keyword <code class="key">_x_</code>:
<p>
<?php include("introExample37bis.php"); ?>
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
pattern is found, display an error warning and return <code class="key">error</code>. Note that the parentheses around the expressions <em>return-exprI</em> are mandatory.
<p>
Matching a pattern means the following: 
<ul>
  <li> If a pattern does not contain any programming-language-level
    variables (different from the free mathematical variable), it
    matches expressions that are syntactically equal to itself. For
    instance, the pattern <code class="key">exp(sin(3&nbsp;*&nbsp;x))</code> will match the
    expression <code class="key">exp(sin(3&nbsp;*&nbsp;x))</code>, but it does not match <code class="key">exp(sin(x&nbsp;*&nbsp;3))</code> because the expressions are not syntactically equal.
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
matching in <span class="sollya">Sollya</span>. One can remark that it is useful to use the keyword <code class="key">_x_</code> when one wants to be sure to refer to the free variable in a pattern matching:
<p>
<?php include("introExample50.php"); ?>
<p>
As <span class="sollya">Sollya</span> is not a purely functional language, the
<code class="key">match ...&nbsp;with</code> construct can also be used in a more imperative style,
which makes it become closer to constructs like <code class="key">switch</code> in
<code>C</code> or <code>Perl</code>. In lieu of a simple return expression, a whole
block of imperative statements can be given. The expression to be
returned by that block is indicated in the end of the block, using
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
functions. As a consequence, patterns match constant expressions
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
the pattern in the corresponding element of the structure pattern <em>sp</em>. The user should be aware of the fact that the structure to be
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
When f is not defined at some point x but is defined on a neighborhood of x, we consider that the &ldquo;value&rdquo; of f at x is the convex hull of the limit points of f around x. For instance, consider the evaluation of f= tan on [0, Pi]. It is not defined at Pi/2 (and only at this point). The limit points of f around Pi/2 are -infinity and +infinity, so, we return [-infinity, +infinity]. Another example: f=sin on [+infinity]. The function has no limit at this point, but all points of [-1, 1] are limit points. So, we return [-1,1].

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

<p><a name="Libsollya"></a>
<h1>10 - Appendix: the <span class="sollya">Sollya</span> library</h1>
 <h2>10.1 - Introduction</h2>
<p>
The header file of the <span class="sollya">Sollya</span> library is <code>sollya.h</code>. Its inclusion may provoke the inclusion of other header files, such as <code>gmp.h</code>, <code>mpfr.h</code> or <code>mpfi.h</code>.

<p>
The library provides a virtual <span class="sollya">Sollya</span> session that is perfectly similar to an interactive session: global variables such as <code>verbosity</code>, <code>prec</code>, <code>display</code>, <code>midpointmode</code>, etc. are maintained and affect the behavior of the library, warning messages are displayed when something is not exact, etc. Please notice that the <span class="sollya">Sollya</span> library currently is <strong>not</strong> re-entrant and can only be opened once. A process using the library must hence not be multi-threaded and is limited to one single virtual <span class="sollya">Sollya</span> session.

<p>
In order to get started with the <span class="sollya">Sollya</span> library, the first thing to do is hence to initialize this virtual session. This is performed with the <code>sollya_lib_init</code> function. Accordingly, one should close the session at the end of the program (which has the effect of releasing all the memory used by <span class="sollya">Sollya</span>). Please notice that <span class="sollya">Sollya</span> uses its own allocation functions and registers them to <code>GMP</code> using the custom allocation functions provided by <code>GMP</code>. Particular precautions should hence be taken when using the <span class="sollya">Sollya</span> library in a program that also registers its own functions to <code>GMP</code>: in that case <code>sollya_lib_init_with_custom_memory_functions</code> should be used instead of <code>sollya_lib_init</code> for initializing the library. This is discussed in <a href="#customMemoryFunctions">a specific section.</a>
<p>
In the usual case when <span class="sollya">Sollya</span> is used in a program that does not register allocation functions to&nbsp;<code>GMP</code>, a minimal file using the library is hence the following.

<div class="divExample">
#include &lt;sollya.h&gt;<br>
<br>
int main(void) {<br>
&nbsp;&nbsp;sollya_lib_init();<br>
<br>
&nbsp;&nbsp;&nbsp;&nbsp;/* Functions of the library can be called here */<br>
<br>
&nbsp;&nbsp;sollya_lib_close();<br>
&nbsp;&nbsp;return 0;<br>
}<br>
</div>

<p>
Suppose that this code is saved in a file called <code>foo.c</code>. The compilation is performed as usual without forgetting to link against <code>libsollya</code> (since the libraries <code>libgmp</code>, <code>libmpfr</code> and <code>libmpfi</code> are dependencies of <span class="sollya">Sollya</span>, it might also be necessary to explicitly link against them):
<div class="divExample">
&nbsp;&nbsp;/% cc foo.c -c<br>
&nbsp;&nbsp;/% cc foo.o -o foo -lsollya -lmpfi -lmpfr -lgmp<br>
</div>

 <h2>10.2 - Sollya object data-type</h2>
<p>
The library provides a single data type called <code>sollya_obj_t</code> that can contain any <span class="sollya">Sollya</span> object (a <span class="sollya">Sollya</span> object is anything that can be stored in a variable within the interactive tool. See Section <a href="#sec:data_types">Data Types</a> of the present documentation for details). Please notice that <code>sollya_obj_t</code> is in fact a pointer type; this has two consequences:
<ul>
  <li> <code>NULL</code> is a placeholder that can be used as a <code>sollya_obj_t</code> in some contexts. This placeholder is particularly useful as an end marker for functions with a variable number of arguments (see Sections <a href="#creating_lists">Lists</a> and <a href="#library_commands_and_functions">Commands and functions.</a></li>
  <li> An assignment with the &ldquo;=&rdquo; sign does not copy an object but only copies the reference to it. In order to perform a (deep) copy, the <code>sollya_lib_copy_obj()</code> function is available.</li>
</ul>
<p>
Except for a few functions for which the contrary is explicitly specified, the following conventions are used:
<ul>
  <li>  A function does not touch its arguments. Hence if <code>sollya_lib_foo</code> is a function of the library, a call to <code>sollya_lib_foo(a)</code> leaves the object referenced by <code>a</code> unchanged (the notable exceptions to that rule are the functions containing <code>build</code> in their name, e.g., <code>sollya_lib_build_foo</code>).</li>
  <li> A function that returns a <code>sollya_obj_t</code> creates a new object (this means that memory is dynamically allocated for that object). The memory allocated for that object should manually be cleared when the object is no longer used and all references to it (on the stack) get out of reach, e.g. on a function return: this is performed by the <code>sollya_lib_clear_obj()</code> function. By convenience <code>sollya_lib_clear_obj(NULL)</code> is a valid call, which just does nothing.</li>
</ul>
<p>
In general, except if the user perfectly knows what they are doing, the following rules should be applied (here <code>a</code> and <code>b</code> are C variables of type <code>sollya_obj_t</code>, and <code>sollya_lib_foo</code> and <code>sollya_lib_bar</code> are functions of the library):
<ul>
  <li> One should never write <code>a = b</code>. Instead, use <code>a = sollya_lib_copy_obj(b)</code>.</li>
  <li> One should never write <code>a = sollya_lib_foo(a)</code> because one loses the reference to the object initially referenced by the variable <code>a</code> (which is hence not cleared).</li>
  <li> One should never chain function calls such as, e.g., <code>a = sollya_lib_foo(sollya_lib_bar(b))</code> (the reference to the object created by <code>sollya_lib_bar(b)</code> would be lost and hence not cleared).</li>
  <li> A variable <code>a</code> should never be used twice at the left-hand side of the &ldquo;=&rdquo; sign (or as an lvalue in general) without performing <code>sollya_lib_clear_obj(a)</code> in-between.</li>
  <li> In an assignment of the form &ldquo;<code>a = ...</code>&rdquo;, the right-hand side should always be a function call (i.e., something like <code>a = sollya_lib_foo(...);</code>).</li>
</ul>
<p>
Please notice that <code>sollya_lib_close()</code> clears the memory allocated by the virtual <span class="sollya">Sollya</span> session but not the objects that have been created and stored in C variables. All the <code>sollya_obj_t</code> created by function calls should be cleared manually.
<p>
We can now write a simple Hello World program using the <span class="sollya">Sollya</span> library:
<div class="divExample">
#include &lt;sollya.h&gt;<br>
<br>
int main(void) {<br>
&nbsp;&nbsp;sollya_obj_t s1, s2, s;<br>
&nbsp;&nbsp;sollya_lib_init();<br>
<br>
&nbsp;&nbsp;s1 = sollya_lib_string("Hello ");<br>
&nbsp;&nbsp;s2 = sollya_lib_string("World!");<br>
&nbsp;&nbsp;s = sollya_lib_concat(s1, s2);<br>
&nbsp;&nbsp;sollya_lib_clear_obj(s1);<br>
&nbsp;&nbsp;sollya_lib_clear_obj(s2);<br>
<br>
&nbsp;&nbsp;sollya_lib_printf("%b\n", s);<br>
&nbsp;&nbsp;sollya_lib_clear_obj(s);<br>
&nbsp;&nbsp;sollya_lib_close();<br>
&nbsp;&nbsp;return 0;<br>
}<br>
</div>

<p>
A universal function allows the user to execute any expression, as if it were given at the prompt of the <span class="sollya">Sollya</span> tool, and to get a <code>sollya_obj_t</code> containing the result of the evaluation: this function is <code>sollya_lib_parse_string("some expression here")</code>. This is very convenient, and indeed, any script written in the <span class="sollya">Sollya</span> language, could easily be converted into a C program by intensively using <code>sollya_lib_parse_string</code>. However, this should not be the preferred way if efficiency is targeted because (as its name suggests) this function uses a parser to decompose its argument, then constructs intermediate data structures to store the abstract interpretation of the expression, etc. Low-level functions are provided for efficiently creating <span class="sollya">Sollya</span> objects; they are detailed in the next Section.
<p>
<h2>10.3 - Conventions in use in the library</h2>
<p>
The library follows some conventions that are useful to remember:
<ul>
  <li> When a function is a direct transposition of a command or function available in the interactive tool, it returns a <code>sollya_obj_t</code>. This is true, even when it would sound natural to return, e.g. an <code>int</code>. For instance <code>sollya_lib_get_verbosity()</code> returns a <code>sollya_obj_t</code>, whose integer value must then be recovered with <code>sollya_lib_get_constant_as_int</code>. This forces the user to declare (and clear afterwards) a temporary <code>sollya_obj_t</code> to store the value, but this is the price of homogeneity in the library.</li>
  <li> When a function returns an integer, this integer generally is a boolean in the usual C meaning, i.e. 0 represents false and any non-zero value represents true. In many cases, the integer returned by the function indicates a status of success or failure: the convention is &ldquo;false means failure&rdquo; and &ldquo;true means success&rdquo;. In case of failure, the convention is that the function did not touch any of its arguments.</li>
  <li> When a function would need to return several things, or when a function would need to return something together with a status of failure or success, the convention is that pointers are given as the first arguments of the function. These pointers shall point to valid addresses where the function will store the results. This can sometimes give obscure signatures, when the function would in principle returns a pointer and actually takes as argument a pointer to a pointer (this typically happens when the function allocates a segment of memory and should return a pointer to that segment of memory).</li>
</ul>

<h2>10.4 - Displaying <span class="sollya">Sollya</span> objects and numerical values</h2>
<p>
Within the interactive tool, the most simple way of displaying the content of a variable or the value of an expression is to write the name of the variable or the expression, followed by the character &ldquo;;&rdquo;. As a result, <span class="sollya">Sollya</span> evaluates the expression or the variable and displays the result. Alternatively, a set of objects can be displayed the same way, separating the objects with commas. In library mode, the same behavior can be reproduced using the function <code>void sollya_lib_autoprint(sollya_obj_t, ...)</code>. Please notice that this function has a variable number of arguments: they are all displayed, until an argument equal to <code>NULL</code> is found. The <code>NULL</code> argument is mandatory, even if only one object shall be displayed (the function has no other way to know if other arguments follow or not). So, if only one argument should be displayed, the correct function call is <code>sollya_lib_autoprint(arg, NULL)</code>. Accordingly, if two arguments should be displayed, the function call is <code>sollya_lib_autoprint(arg1, arg2, NULL)</code>, etc. The function <code>void sollya_lib_v_autoprint(sollya_obj_t, va_list)</code> is the same, but it takes a <code>va_list</code> argument instead of a variable number of arguments.
<p>
Further, there is another way of printing formatted strings containing <span class="sollya">Sollya</span> objects, using a <code>printf</code>-like syntax. Eight functions are provided, namely:
<ul>
  <li> <code>sollya_lib_printf</code>, <code>sollya_lib_v_printf</code>,</li>
  <li> <code>sollya_lib_fprintf</code>, <code>sollya_lib_v_fprintf</code>,</li>
  <li> <code>sollya_lib_sprintf</code>, <code>sollya_lib_v_sprintf</code>,</li>
  <li> <code>sollya_lib_snprintf</code> and <code>sollya_lib_v_snprintf</code>.</li>
</ul>
<p>
Each one of these functions overloads the usual function (respectively, <code>printf</code>, <code>vprintf</code>, <code>fprintf</code>, <code>vfprintf</code>, <code>sprintf</code>, <code>vsprintf</code>, <code>snprintf</code> and <code>vsnprintf</code>). The full syntax of conversions specifiers supported with the usual functions is handled (please note that the style using '<code>$</code>' &ndash;&nbsp;as in <code>%3$</code> or <code>%*3$</code>&nbsp;&ndash; is not handled though. It is not included in the C99 standard anyway). Additionally, the following conversion specifiers are provided:
<ul>
  <li> <code>%b</code>: corresponds to a <code>sollya_obj_t</code> argument. There is no precision modifier support.</li>
  <li> <code>%v</code>: corresponds to a <code>mpfr_t</code> argument. An optional precision modifier can be applied (e.g. <code>%.5v</code>).</li>
  <li> <code>%w</code>: corresponds to a <code>mpfi_t</code> argument. An optional precision modifier can be applied (e.g. <code>%.5w</code>).</li>
  <li> <code>%r</code>: corresponds to a <code>mpq_t</code> argument. There is no precision modifier support.</li>
</ul>
<p>
When one of the above conversion specifiers is used, the corresponding argument is displayed as it would be within the interactive tool: i.e. the way the argument is displayed depends on <span class="sollya">Sollya</span> environment variables, such as <code>prec</code>, <code>display</code>, <code>midpointmode</code>, etc. When a precision modifier n is used, the argument is first rounded to a binary precision of roughly log2(10)*n bits (i.e. roughly equivalent to n decimal digits) before being displayed. As with traditional <code>printf</code>, the precision modifier can be replaced with&nbsp;<code>*</code> which causes the precision to be determined by an additional <code>int</code> argument.
<p>
Flag characters (e.g., &lsquo;<code>#</code>&rsquo;, &lsquo;<code>0</code>&rsquo;, etc.) are allowed but have no effect, except flag character &lsquo;<code>-</code>&rsquo; that is supported with its usual meaning of left-aligning the converted value. The full syntax for minimum field width is supported: it can be given directly as an integer in the format string (e.g., <code>%22b</code>) or it can be replaced with&nbsp;<code>*</code>, which causes the field width to be determined by an additional <code>int</code> argument. As usual, a negative field width is taken as a &lsquo;<code>-</code>&rsquo; flag followed by a positive width.
<p>
As a special (and sometimes convenient) case, <code>%b</code> accepts that its corresponding <code>sollya_obj_t</code> argument be <code>NULL</code>: in this particular case, the string &ldquo;NULL&rdquo; is used in the displayed string. Please notice that, except for the particular case of <code>NULL</code>, the behavior of <code>sollya_lib_printf</code> is completely undefined if the argument of <code>%b</code> is not a valid <span class="sollya">Sollya</span> object.
<p>
The <code>sollya_lib_printf</code> functions return an integer with the same meaning as the traditional <code>printf</code> functions. It indicates the number of characters that have been output (excluding the final <code>\0</code> character). Similarly, the conversion specifier <code>%n</code> can be used, even together with the <span class="sollya">Sollya</span> conversion specifiers <code>%b</code>, <code>%v</code>, <code>%w</code> and <code>%r</code>. The functions <code>sollya_lib_snprintf</code> and <code>sollya_lib_v_snprintf</code> will
never write more characters than indicated by their size argument (including the final <code>\0</code> character). If the output gets truncated due to this limit, they will return the number of characters (excluding the final <code>\0</code> character) that would have been output if there had not been any truncation. In case of error, all <code>sollya_lib_printf</code> functions return a negative value.

<h2>10.5 Creating <span class="sollya">Sollya</span> objects</h2>
<p>
<span class="sollya">Sollya</span> objects conceptually fall into one of five categories: numerical constants (e.g. 1 or 1.5), functional expressions (they might contain numerical constants, e.g., sin(cos(x+1.5))), other simple objects (intervals, strings, built-in constants such as <code>dyadic</code>, etc.), lists of objects (e.g., <code>[|1, "Hello"|]</code>) and structures (e.g., <code>{.a = 1; .b = "Hello"}</code>).

<h3>10.5.1 - Numerical constants</h3>
<p>
Table <a href="#creating_numerical_constant">Creating numerical constants</a> lists the different functions available to construct numerical constants. A <span class="sollya">Sollya</span> constant is always created without rounding (whatever the value of global variable <code>prec</code> is at the moment of the function call): a sufficient precision is always allocated so that the constant is stored exactly. The objects returned by these functions are newly allocated and copies of the argument. For instance, after the instruction <code>a = sollya_lib_constant(b)</code>, the user will eventually have to clear <code>a</code> (with <code>sollya_lib_clear(a)</code>) and <code>b</code> (with <code>mpfr_clear(b)</code>).
<p>
The function <code>sollya_lib_constant_from_double</code> (or more conveniently its shortcut <code>SOLLYA_CONST</code>) is probably the preferred way for constructing numerical constants. As the name indicates it, its argument is a <code>double</code>; however, due to implicit casting in&nbsp;C, it is perfectly possible to give an <code>int</code> as argument: it will be converted into a <code>double</code> (without rounding if the integer fits on 53&nbsp;bits) before being passed to <code>SOLLYA_CONST</code>. On the contrary, the user should be aware of the fact that if decimal non-integer constants are given, C rules of rounding (to double) are applied, regardless of the setting of the <span class="sollya">Sollya</span> precision variable <code>prec</code>.

  <a name="creating_numerical_constant"></a>
  <table border="1" rules="cols">
    <caption>Creating numerical constants (Creates a fresh <code>sollya_obj_t</code>. Conversion is always exact)</caption>
    <tr><th align="center">Type of the argument</th> <th align="center">Name of the function</th> <th align="center">Shortcut macro</th> </tr>
    <tr><td align="left"><code>double</code></td> <td align="center"><code>sollya_lib_constant_from_double(x)</code></td> <td align="left"><code>SOLLYA_CONST(x)</code></td> </tr>
    <tr><td align="left"><code>uint64_t</code></td> <td align="center"><code>sollya_lib_constant_from_uint64(x)</code></td> <td align="left"><code>SOLLYA_CONST_UI64(x)</code></td> </tr>
    <tr><td align="left"><code>int64_t</code></td> <td align="center"><code>sollya_lib_constant_from_int64(x)</code></td> <td align="left"><code>SOLLYA_CONST_SI64(x)</code></td> </tr>
    <tr><td align="left"><code>int</code></td> <td align="center"><code>sollya_lib_constant_from_int(x)</code></td> <td align="left">N/A</td> </tr>
    <tr><td align="left"><code>mpfr_t</code></td> <td align="center"><code>sollya_lib_constant(x)</code></td> <td align="left">N/A</td> </tr>
  </table>

<h3>10.5.2 - Functional expressions</h3>
<p>
Functional expressions are built by composition of basic functions with constants and the free mathematical variable. Since it is convenient to build such expressions by chaining function calls, the library provides functions that &ldquo;eat up&rdquo; their arguments (actually embedding them in a bigger expression). The convention is that functions that eat up their arguments are prefixed by <code>sollya_lib_build_</code>. For the purpose of building expressions, shortcut macros for the corresponding functions exist. They are all listed in Table <a href="#build_expr">Building functional expressions.</a>
<p>
It is worth mentioning that, although <code>SOLLYA_X_</code> and <code>SOLLYA_PI</code> are used without parentheses (as if they denoted constants), they are in fact function calls that create a new object each time they are used. The absence of parentheses is just more convenient for constructing expressions, such as, e.g. <code>SOLLYA_COS(SOLLYA_X_)</code>.
    <a name="build_expr"></a>
    <table border="1" rules="cols">
    <caption>Building functional expressions (Eats up arguments, embedding them in the returned object.)</caption>
    <tr><th align="center">Name in the interactive tool</th> <th align="center">Function to build it</th> <th align="center">Shortcut macro</th> </tr>
<tr> <td align="center"><code>_x_</code> </td> <td align="left"> <code>sollya_lib_build_function_free_variable()</code> </td> <td align="left"> <code>SOLLYA_X_</code></td></tr>
<tr> <td align="center"><code>pi</code> </td> <td align="left"> <code>sollya_lib_build_function_pi()</code> </td> <td align="left"> <code>SOLLYA_PI</code></td></tr>
<tr> <td align="center"><code>e1 + e2</code> </td> <td align="left"> <code>sollya_lib_build_function_add(e1, e2)</code> </td> <td align="left"> <code>SOLLYA_ADD(e1, e2)</code></td></tr>
<tr> <td align="center"><code>e1 - e2</code> </td> <td align="left"> <code>sollya_lib_build_function_sub(e1, e2)</code> </td> <td align="left"> <code>SOLLYA_SUB(e1, e2)</code></td></tr>
<tr> <td align="center"><code>e1 * e2</code> </td> <td align="left"> <code>sollya_lib_build_function_mul(e1, e2)</code> </td> <td align="left"> <code>SOLLYA_MUL(e1, e2)</code></td></tr>
<tr> <td align="center"><code>e1 / e2</code> </td> <td align="left"> <code>sollya_lib_build_function_div(e1, e2)</code> </td> <td align="left"> <code>SOLLYA_DIV(e1, e2)</code></td></tr>
<tr> <td align="center"><code>pow(e1, e2)</code> </td> <td align="left"> <code>sollya_lib_build_function_pow(e1, e2)</code> </td> <td align="left"> <code>SOLLYA_POW(e1, e2)</code></td></tr>
<tr> <td align="center"><code>-e</code> </td> <td align="left"> <code>sollya_lib_build_function_neg(e)</code> </td> <td align="left"> <code>SOLLYA_NEG(e)</code></td></tr>
<tr> <td align="center"><code>sqrt(e)</code> </td> <td align="left"> <code>sollya_lib_build_function_sqrt(e)</code> </td> <td align="left"> <code>SOLLYA_SQRT(e)</code></td></tr>
<tr> <td align="center"><code>abs(e)</code> </td> <td align="left"> <code>sollya_lib_build_function_abs(e)</code> </td> <td align="left"> <code>SOLLYA_ABS(e)</code></td></tr>
<tr> <td align="center"><code>erf(e)</code> </td> <td align="left"> <code>sollya_lib_build_function_erf(e)</code> </td> <td align="left"> <code>SOLLYA_ERF(e)</code></td></tr>
<tr> <td align="center"><code>erfc(e)</code> </td> <td align="left"> <code>sollya_lib_build_function_erfc(e)</code> </td> <td align="left"> <code>SOLLYA_ERFC(e)</code></td></tr>
<tr> <td align="center"><code>exp(e)</code> </td> <td align="left"> <code>sollya_lib_build_function_exp(e)</code> </td> <td align="left"> <code>SOLLYA_EXP(e)</code></td></tr>
<tr> <td align="center"><code>expm1(e)</code> </td> <td align="left"> <code>sollya_lib_build_function_expm1(e)</code> </td> <td align="left"> <code>SOLLYA_EXPM1(e)</code></td></tr>
<tr> <td align="center"><code>log(e)</code> </td> <td align="left"> <code>sollya_lib_build_function_log(e)</code> </td> <td align="left"> <code>SOLLYA_LOG(e)</code></td></tr>
<tr> <td align="center"><code>log2(e)</code> </td> <td align="left"> <code>sollya_lib_build_function_log2(e)</code> </td> <td align="left"> <code>SOLLYA_LOG2(e)</code></td></tr>
<tr> <td align="center"><code>log10(e)</code> </td> <td align="left"> <code>sollya_lib_build_function_log10(e)</code> </td> <td align="left"> <code>SOLLYA_LOG10(e)</code></td></tr>
<tr> <td align="center"><code>log1p(e)</code> </td> <td align="left"> <code>sollya_lib_build_function_log1p(e)</code> </td> <td align="left"> <code>SOLLYA_LOG1P(e)</code></td></tr>
<tr> <td align="center"><code>sin(e)</code> </td> <td align="left"> <code>sollya_lib_build_function_sin(e)</code> </td> <td align="left"> <code>SOLLYA_SIN(e)</code></td></tr>
<tr> <td align="center"><code>cos(e)</code> </td> <td align="left"> <code>sollya_lib_build_function_cos(e)</code> </td> <td align="left"> <code>SOLLYA_COS(e)</code></td></tr>
<tr> <td align="center"><code>tan(e)</code> </td> <td align="left"> <code>sollya_lib_build_function_tan(e)</code> </td> <td align="left"> <code>SOLLYA_TAN(e)</code></td></tr>
<tr> <td align="center"><code>asin(e)</code> </td> <td align="left"> <code>sollya_lib_build_function_asin(e)</code> </td> <td align="left"> <code>SOLLYA_ASIN(e)</code></td></tr>
<tr> <td align="center"><code>acos(e)</code> </td> <td align="left"> <code>sollya_lib_build_function_acos(e)</code> </td> <td align="left"> <code>SOLLYA_ACOS(e)</code></td></tr>
<tr> <td align="center"><code>atan(e)</code> </td> <td align="left"> <code>sollya_lib_build_function_atan(e)</code> </td> <td align="left"> <code>SOLLYA_ATAN(e)</code></td></tr>
<tr> <td align="center"><code>sinh(e)</code> </td> <td align="left"> <code>sollya_lib_build_function_sinh(e)</code> </td> <td align="left"> <code>SOLLYA_SINH(e)</code></td></tr>
<tr> <td align="center"><code>cosh(e)</code> </td> <td align="left"> <code>sollya_lib_build_function_cosh(e)</code> </td> <td align="left"> <code>SOLLYA_COSH(e)</code></td></tr>
<tr> <td align="center"><code>tanh(e)</code> </td> <td align="left"> <code>sollya_lib_build_function_tanh(e)</code> </td> <td align="left"> <code>SOLLYA_TANH(e)</code></td></tr>
<tr> <td align="center"><code>asinh(e)</code> </td> <td align="left"> <code>sollya_lib_build_function_asinh(e)</code> </td> <td align="left"> <code>SOLLYA_ASINH(e)</code></td></tr>
<tr> <td align="center"><code>acosh(e)</code> </td> <td align="left"> <code>sollya_lib_build_function_acosh(e)</code> </td> <td align="left"> <code>SOLLYA_ACOSH(e)</code></td></tr>
<tr> <td align="center"><code>atanh(e)</code> </td> <td align="left"> <code>sollya_lib_build_function_atanh(e)</code> </td> <td align="left"> <code>SOLLYA_ATANH(e)</code></td></tr>
<tr> <td align="center"><code>D(e)</code>, <code>double(e)</code> </td> <td align="left"> <code>sollya_lib_build_function_double(e)</code> </td> <td align="left"> <code>SOLLYA_D(e)</code></td></tr>
<tr> <td align="center"><code>SG(e)</code>, <code>single(e)</code> </td> <td align="left"> <code>sollya_lib_build_function_single(e)</code> </td> <td align="left"> <code>SOLLYA_SG(e)</code></td></tr>
<tr> <td align="center"><code>QD(e)</code>, <code>quad(e)</code> </td> <td align="left"> <code>sollya_lib_build_function_quad(e)</code> </td> <td align="left"> <code>SOLLYA_QD(e)</code></td></tr>
<tr> <td align="center"><code>HP(e)</code>, <code>halfprecision(e)</code> </td> <td align="left"> <code>sollya_lib_build_function_halfprecision(e)</code> </td> <td align="left"> <code>SOLLYA_HP(e)</code></td></tr>
<tr> <td align="center"><code>DD(e)</code>, <code>doubledouble(e)</code> </td> <td align="left"> <code>sollya_lib_build_function_double_double(e)</code> </td> <td align="left"> <code>SOLLYA_DD(e)</code></td></tr>
<tr> <td align="center"><code>TD(e)</code>, <code>tripledouble(e)</code> </td> <td align="left"> <code>sollya_lib_build_function_triple_double(e)</code> </td> <td align="left"> <code>SOLLYA_TD(e)</code></td></tr>
<tr> <td align="center"><code>DE(e)</code>, <code>doubleextended(e)</code> </td> <td align="left"> <code>sollya_lib_build_function_doubleextended(e)</code> </td> <td align="left"> <code>SOLLYA_DE(e)</code></td></tr>
<tr> <td align="center"><code>ceil(e)</code> </td> <td align="left"> <code>sollya_lib_build_function_ceil(e)</code> </td> <td align="left"> <code>SOLLYA_CEIL(e)</code></td></tr>
<tr> <td align="center"><code>floor(e)</code> </td> <td align="left"> <code>sollya_lib_build_function_floor(e)</code> </td> <td align="left"> <code>SOLLYA_FLOOR(e)</code></td></tr>
<tr> <td align="center"><code>nearestint(e)</code> </td> <td align="left"> <code>sollya_lib_build_function_nearestint(e)</code> </td> <td align="left"> <code>SOLLYA_NEARESTINT(e)</code></td></tr>
  </table>

<p>
For each function of the form <code>sollya_lib_build_function_foo</code>, there exists a function called <code>sollya_lib_foo</code>. There are two differences between them:
<ul>
  <li> First, <code>sollya_lib_foo</code> does not &ldquo;eat up&rdquo; its argument. This can sometimes be useful, e.g., if one has an expression stored in a variable <code>a</code> and one wants to build the expression <code>exp(a)</code> without loosing the reference to the expression represented by <code>a</code>.</li>
  <li> Second, while <code>sollya_lib_build_function_foo</code> mechanically constructs an expression, function <code>sollya_lib_foo</code> also evaluates it, as far as this is possible without rounding.<br>
For instance, after the instructions <code>a = SOLLYA_CONST(0); b = sollya_lib_exp(a);</code> the variable <code>b</code> contains the number 1, whereas it would have contained the expression "<code>exp(0)</code>" if it had been created by <code>b = sollya_lib_build_function(a)</code>.</li>
</ul>
<p>
Actually, <code>sollya_lib_foo</code> has exactly the same behavior as writing an expression at the prompt within the interactive tool. In particular, it is possible to give a range as an argument to <code>sollya_lib_foo</code>: the returned object will be the result of the evaluation of function <code>foo</code> on that range by interval arithmetic. In contrast, trying to use <code>sollya_lib_build_function_foo</code> on a range would result in a typing error.

<h3>10.5.3 - Library functions, library constants and procedure functions</h3>
<p>
In addition to the mathematical base functions and constants provided
by <span class="sollya">Sollya</span> and listed in the Section above, the user may bind other
mathematical functions and constants to <span class="sollya">Sollya</span> objects under the
condition that they can provide code to evaluate these functions or
constants. The mechanism behind is similar to the one available in
interactive <span class="sollya">Sollya</span> through the <code>library</code>, <code>libraryconstant</code>
and <code>function</code> commands (see commands <a href="help.php?name=library">library</a>, <a href="help.php?name=libraryconstant">libraryconstant</a> and <a href="help.php?name=function">function</a>).
<p>
With the <span class="sollya">Sollya</span> library, this binding is done through one of the
following functions:
<ul>
<li> Binding of a (non-constant) mathematical function for which evaluation code is available through a <code>C</code> pointer to a function: <br>
<code>sollya_obj_t sollya_lib_libraryfunction(sollya_obj_t e, </code> <br>
<code>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;char *name, </code> <br>
<code>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int (*f)(mpfi_t, mpfi_t, int));</code> <br>
<code>sollya_obj_t sollya_lib_build_function_libraryfunction(sollya_obj_t e, </code> <br>
<code>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;char *name, </code> <br>
<code>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int (*f)(mpfi_t, mpfi_t, int));</code><br>
<p>
These two functions construct a <span class="sollya">Sollya</span> object representing f(e)
where e is given as the <span class="sollya">Sollya</span> object <code>e</code> and f is given as
the pointer to a function <code>f(mpfi_t y, mpfi_t x, int n)</code>. This
code must evaluate the n-th derivative of f over the interval x,
yielding y. 
<p>
As usual, <code>sollya_lib_build_function_libraryfunction</code> &ldquo;eats up&rdquo;
the object <code>e</code>, while the function
<code>sollya_lib_libraryfunction</code> does not.
<p>
The <code>name</code> argument of the function is taken as a suggestion to
the name the <span class="sollya">Sollya</span> object representing the function should be
printed as when displayed. The user may choose to provide <code>NULL</code>
instead.  In any case, upon the binding, the <span class="sollya">Sollya</span> library will
determine a unique displaying name for the function. If it is not yet
taken as a name (for some other <span class="sollya">Sollya</span> object or <span class="sollya">Sollya</span> keyword),
the suggested name will be used. If no suggested name is provided, the
name of the dynamic object behind the pointer to the
function will be used if it can be determined. Otherwise, a
more-or-less random name is used. If the (suggested) base name is
already taken, the name is unified appending an underscore and a
unique number to it. The <code>name</code> argument is never &ldquo;eaten up&rdquo;,
i.e., it is up to the user to free any memory allocated to that
pointer.</li>
<li> Binding of a mathematical constant for which evaluation code is 
available through a <code>C</code> pointer to a function: <br>
<code>sollya_obj_t sollya_lib_libraryconstant(char *name, </code> <br>
<code>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;void (*c)(mpfr_t, mp_prec_t));</code> <br>
<code>sollya_obj_t sollya_lib_build_function_libraryconstant(char *name, </code> <br>
<code>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;void (*c)(mpfr_t, mp_prec_t));</code><br>

<p>
These two functions construct a <span class="sollya">Sollya</span> object representing the
mathematical constant c for which a pointer to a function
<code>c(mpfr_t rop, mp_prec_t prec)</code> is provided. This code must
evaluate the constant to precision <code>prec</code> and affect the result
to <code>rop</code>. See command <a href="help.php?name=libraryconstant">libraryconstant</a> for details with
respect to <code>prec</code>.
<p>
The same remark as above concerning the suggested displaying name
of the <span class="sollya">Sollya</span> object applies for the <code>name</code> argument.</li>
<li> Binding of a mathematical function for which evaluation code is 
available through a <span class="sollya">Sollya</span> object representing a <span class="sollya">Sollya</span> procedure: <br>
<code>sollya_obj_t sollya_lib_procedurefunction(sollya_obj_t e, sollya_obj_t f);</code>  <br>
<code>sollya_obj_t sollya_lib_build_function_procedurefunction(sollya_obj_t e, </code> <br>
<code>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;sollya_obj_t f);</code><br>

<p>
These two functions construct a <span class="sollya">Sollya</span> library object representing f(e)
where e corresponds to the mathematical function (or constant) given with argument
<code>e</code> and where f is given as a <span class="sollya">Sollya</span> procedure <code>f(x, n, p)</code> evaluating the
n-th derivative of f over the interval x with precision p. See command <a href="help.php?name=function">function</a> 
concerning details of the arguments of that <span class="sollya">Sollya</span> procedure.
<p>
As usual, <code>sollya_lib_build_function_procedurefunction</code> &ldquo;eats
up&rdquo; its arguments <code>e</code> and <code>f</code> while
<code>sollya_obj_t sollya_lib_procedurefunction</code> does not.
<p>
Currently, the only way of constructing a <span class="sollya">Sollya</span> library object
representing a <span class="sollya">Sollya</span> procedure is to use
<code>sollya_lib_parse_string</code>.
</li>
</ul>

<h3>10.5.4 - Other simple objects</h3>
<p>
Other simple objects are created with functions listed in Table&nbsp;<a href="#creating_sollya_obj_t">Creating <span class="sollya">Sollya</span> objects from scratch</a>. The functions with a name of the form <code>sollya_lib_range_something</code> follow the same convention as <code>sollya_lib_constant</code>: they build a new object from a copy of their argument, and the conversion is always exact, whatever the value of <code>prec</code> is.
<p>
Please note that in the interactive tool, <code>D</code> either denotes the discrete mathematical function that maps a real number to its closest <code>double</code> number, or is used as a symbolic constant to indicate that the <code>double</code> format must be used (as an argument of <code>round</code> for instance). In the library, they are completely distinct objects, the mathematical function being obtained with <code>sollya_lib_build_function_double</code> and the symbolic constant with <code>sollya_lib_double_obj</code>. The same holds for other formats (<code>DD</code>, <code>SG</code>, etc.)
    <a name="creating_sollya_obj_t"></a>
    <table border="1" rules="cols">
    <caption>Creating <span class="sollya">Sollya</span> objects from scratch (Returns a new <code>sollya_obj_t</code>)</caption>
    <tr><th align="center">Name in the interactive tool</th> <th align="center">Function to create it</th> </tr>
<tr> <td align="center"><code>on</code> </td> <td align="left"> <code>sollya_lib_on();</code> </td> </tr>
<tr> <td align="center"><code>off</code> </td> <td align="left"> <code>sollya_lib_off();</code> </td> </tr>
<tr> <td align="center"><code>dyadic</code> </td> <td align="left"> <code>sollya_lib_dyadic();</code> </td> </tr>
<tr> <td align="center"><code>powers</code> </td> <td align="left"> <code>sollya_lib_powers();</code> </td> </tr>
<tr> <td align="center"><code>binary</code> </td> <td align="left"> <code>sollya_lib_binary();</code> </td> </tr>
<tr> <td align="center"><code>hexadecimal</code> </td> <td align="left"> <code>sollya_lib_hexadecimal();</code> </td> </tr>
<tr> <td align="center"><code>file</code> </td> <td align="left"> <code>sollya_lib_file();</code> </td> </tr>
<tr> <td align="center"><code>postscript</code> </td> <td align="left"> <code>sollya_lib_postscript();</code> </td> </tr>
<tr> <td align="center"><code>postscriptfile</code> </td> <td align="left"> <code>sollya_lib_postscriptfile();</code> </td> </tr>
<tr> <td align="center"><code>perturb</code> </td> <td align="left"> <code>sollya_lib_perturb();</code> </td> </tr>
<tr> <td align="center"><code>RD</code> </td> <td align="left"> <code>sollya_lib_round_down();</code> </td> </tr>
<tr> <td align="center"><code>RU</code> </td> <td align="left"> <code>sollya_lib_round_up();</code> </td> </tr>
<tr> <td align="center"><code>RZ</code> </td> <td align="left"> <code>sollya_lib_round_towards_zero();</code> </td> </tr>
<tr> <td align="center"><code>RN</code> </td> <td align="left"> <code>sollya_lib_round_to_nearest();</code> </td> </tr>
<tr> <td align="center"><code>honorcoeffprec</code> </td> <td align="left"> <code>sollya_lib_honorcoeffprec();</code> </td> </tr>
<tr> <td align="center"><code>true</code> </td> <td align="left"> <code>sollya_lib_true();</code> </td> </tr>
<tr> <td align="center"><code>false</code> </td> <td align="left"> <code>sollya_lib_false();</code> </td> </tr>
<tr> <td align="center"><code>void</code> </td> <td align="left"> <code>sollya_lib_void();</code> </td> </tr>
<tr> <td align="center"><code>default</code> </td> <td align="left"> <code>sollya_lib_default();</code> </td> </tr>
<tr> <td align="center"><code>decimal</code> </td> <td align="left"> <code>sollya_lib_decimal();</code> </td> </tr>
<tr> <td align="center"><code>absolute</code> </td> <td align="left"> <code>sollya_lib_absolute();</code> </td> </tr>
<tr> <td align="center"><code>relative</code> </td> <td align="left"> <code>sollya_lib_relative();</code> </td> </tr>
<tr> <td align="center"><code>fixed</code> </td> <td align="left"> <code>sollya_lib_fixed();</code> </td> </tr>
<tr> <td align="center"><code>floating</code> </td> <td align="left"> <code>sollya_lib_floating();</code> </td> </tr>
<tr> <td align="center"><code>error</code> </td> <td align="left"> <code>sollya_lib_error();</code> </td> </tr>
<tr> <td align="center"><code>D, double</code> </td> <td align="left"> <code>sollya_lib_double_obj();</code> </td> </tr>
<tr> <td align="center"><code>SG, single</code> </td> <td align="left"> <code>sollya_lib_single_obj();</code> </td> </tr>
<tr> <td align="center"><code>QD, quad</code> </td> <td align="left"> <code>sollya_lib_quad_obj();</code> </td> </tr>
<tr> <td align="center"><code>HP, halfprecision</code> </td> <td align="left"> <code>sollya_lib_halfprecision_obj();</code> </td> </tr>
<tr> <td align="center"><code>DE, doubleextended</code> </td> <td align="left"> <code>sollya_lib_doubleextended_obj();</code> </td> </tr>
<tr> <td align="center"><code>DD, doubledouble</code> </td> <td align="left"> <code>sollya_lib_double_double_obj();</code> </td> </tr>
<tr> <td align="center"><code>TD, tripledouble</code> </td> <td align="left"> <code>sollya_lib_triple_double_obj();</code> </td> </tr>
<tr> <td align="center"><code>"Hello"</code> </td> <td align="left">  <code>sollya_lib_string("Hello")</code> </td> </tr>
<tr> <td align="center"><code>[1, 3.5]</code> </td> <td align="left">  <code>sollya_lib_range_from_interval(a);</code> </td> </tr>
    <tr> <td align="center"><code>[1, 3.5]</code> </td> <td align="left">  <code>sollya_lib_range_from_bounds(b, c);</code></td> </tr>
  </table>
<p>In the last lines of the table, <code>a</code> is a <code>mpfi_t</code> containing the interval [1, 3.5], <code>b</code> and <code>c</code> are <code>mpfr_t</code> respectively containing the numbers 1 and 3.5. Conversion from a <code>mpfi_t</code> or a <code>mpfr_t</code> to a <code>sollya_obj_t</code> is always exact.

<a name="creating_lists"></a>
<h3>10.5.5 - Lists</h3>
<p>
There are actually two kinds of lists: regular lists (such as, e.g., <code>[|1, 2, 3|]</code>) and semi-infinite lists (such as, e.g. <code>[|1, 2...|]</code>). Withing the interactive tool, the ellipsis &ldquo;<code>...</code>&rdquo; can sometimes be used as a shortcut to define regular lists, e.g. <code>[|1, 2, ..., 10|]</code>.
<p>
In the library, there is no symbol for the ellipsis, and there are two distinct types: one for regular lists and one for semi-infinite lists (called end-elliptic). Defining a regular list with an ellipsis is not possible in the library (except of course with <code>sollya_lib_parse_string</code>).
<p>
Constructing regular lists is achieved through three functions:
<ul>
  <li> <code>sollya_obj_t sollya_lib_list(sollya_obj_t[] L, int n)</code>: this function returns a new object that is a list the elements of which are copies of <code>L[0]</code>, ..., <code>L[n-1]</code>.</li>
  <li> <code>sollya_obj_t sollya_lib_build_list(sollya_obj_t obj1, ...)</code>: this function accepts a variable number of arguments. The last one <strong>must</strong> be <code>NULL</code>. It &ldquo;eats up&rdquo; its arguments and returns a list containing the objects given as arguments. Since arguments are eaten up, they may be directly produced by function calls, without being stored in variables. A typical use could be<br>
    <code>sollya_lib_build_list(SOLLYA_CONST(1), SOLLYA_CONST(2), SOLLYA_CONST(3), NULL);</code><br></li>
  <li> <code>sollya_obj_t sollya_lib_v_build_list(va_list)</code>: the same as the previous functions, but with a <code>va_list</code>.</li>
</ul>
<p>
Following the same conventions, end-elliptic lists can be constructed with the following functions:
<ul>
  <li> <code>sollya_obj_t sollya_lib_end_elliptic_list(sollya_obj_t[] L, int n)</code>.</li>
  <li> <code>sollya_obj_t sollya_lib_build_end_elliptic_list(sollya_obj_t obj1, ...)</code>.</li>
  <li> <code>sollya_obj_t sollya_lib_v_build_end_elliptic_list(va_list)</code>.</li>
</ul>

<p><a name="creating_structures"></a>
<h3>10.5.6 - Structures</h3>
<p>
<span class="sollya">Sollya</span> structures are also available in library mode as any other <span class="sollya">Sollya</span> object. The support for <span class="sollya">Sollya</span> structures is however minimal and creating them might seem cumbersome (users are encouraged to make well-founded feature requests if they feel the need for better support of structures). The only function available to create structures is<br>
<code>int sollya_lib_create_structure(sollya_obj_t *res, sollya_obj_t s, char *name,</code><br>
<code>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;sollya_obj_t val).</code>

<p>
This function returns a boolean integer: false means failure, and true means success. Three cases of success are possible. In all cases, the function creates a new object and stores it at the address referred to by <code>res</code>.
<ul>
  <li>  If <code>s</code> is <code>NULL</code>: <code>*res</code> is filled with a structure with only one field. This field is named after the string <code>name</code> and contains a copy of the object <code>val</code>.</li>
  <li> If <code>s</code> is an already existing structure that has a field named after the string <code>name</code>: <code>*res</code> is filled with a newly created structure. This structure is the same as <code>s</code> except that the field corresponding to <code>name</code> contains a copy of <code>val</code>.</li>
  <li> If <code>s</code> is an already existing structure that does <strong>not</strong> have a field named after the string <code>name</code>: <code>*res</code> is filled with a newly created structure. This structure is the same as <code>s</code> except that it has been augmented with a field corresponding to <code>name</code> and that contains a copy of <code>val</code>.</li>
</ul>
<p>
Please notice that <code>s</code> is not changed by this function: the structure stored in <code>*res</code> is a new one that does not refer to any of the components of <code>s</code>. As a consequence, one should not forget to explicitly clear <code>s</code> as well as <code>*res</code> when they become useless.

<h2>10.6 - Getting the type of an object</h2>
<p>
Functions are provided that allow the user to test the type of a <span class="sollya">Sollya</span> object. They are listed in Table&nbsp;<a href="#type_of_an_object">Testing the type of a <span class="sollya">Sollya</span> object</a>. They all return an <code>int</code> interpreted as the boolean result of the test. Please note that from a typing point of view, a mathematical constant and a non-constant functional expression are both functions.

  <a name="type_of_an_object"></a>
  <table border="1" rules="cols">
    <caption>Testing the type of a <span class="sollya">Sollya</span> object (Returns non-zero if true, 0 otherwise)</caption>
      <tr> <td align="left"><code>sollya_lib_obj_is_function(obj)</code> </td></tr>
      <tr> <td align="left"><code>sollya_lib_obj_is_range(obj)</code> </td></tr>
      <tr> <td align="left"><code>sollya_lib_obj_is_string(obj)</code> </td></tr>
      <tr> <td align="left"><code>sollya_lib_obj_is_list(obj)</code> </td></tr>
      <tr> <td align="left"><code>sollya_lib_obj_is_end_elliptic_list(obj)</code> </td></tr>
      <tr> <td align="left"><code>sollya_lib_obj_is_structure(obj)</code> </td></tr>
      <tr style="border-bottom: 1px solid black;"> <td align="left"><code>sollya_lib_obj_is_error(obj)</code></td></tr>
      <tr> <td style="padding-top: 5px;" align="left"><code>sollya_lib_is_on(obj)</code></td></tr>
      <tr> <td align="left"><code>sollya_lib_is_off(obj)</code> </td></tr>
      <tr> <td align="left"><code>sollya_lib_is_dyadic(obj)</code> </td></tr>
      <tr> <td align="left"><code>sollya_lib_is_powers(obj)</code> </td></tr>
      <tr> <td align="left"><code>sollya_lib_is_binary(obj)</code> </td></tr>
      <tr> <td align="left"><code>sollya_lib_is_hexadecimal(obj)</code> </td></tr>
      <tr> <td align="left"><code>sollya_lib_is_file(obj)</code> </td></tr>
      <tr> <td align="left"><code>sollya_lib_is_postscript(obj)</code> </td></tr>
      <tr> <td align="left"><code>sollya_lib_is_postscriptfile(obj)</code> </td></tr>
      <tr> <td align="left"><code>sollya_lib_is_perturb(obj)</code> </td></tr>
      <tr> <td align="left"><code>sollya_lib_is_round_down(obj)</code> </td></tr>
      <tr> <td align="left"><code>sollya_lib_is_round_up(obj)</code> </td></tr>
      <tr> <td align="left"><code>sollya_lib_is_round_towards_zero(obj)</code> </td></tr>
      <tr> <td align="left"><code>sollya_lib_is_round_to_nearest(obj)</code> </td></tr>
      <tr> <td align="left"><code>sollya_lib_is_honorcoeffprec(obj)</code> </td></tr>
      <tr> <td align="left"><code>sollya_lib_is_true(obj)</code> </td></tr>
      <tr> <td align="left"><code>sollya_lib_is_false(obj)</code> </td></tr>
      <tr> <td align="left"><code>sollya_lib_is_void(obj)</code> </td></tr>
      <tr> <td align="left"><code>sollya_lib_is_default(obj)</code> </td></tr>
      <tr> <td align="left"><code>sollya_lib_is_decimal(obj)</code> </td></tr>
      <tr> <td align="left"><code>sollya_lib_is_absolute(obj)</code> </td></tr>
      <tr> <td align="left"><code>sollya_lib_is_relative(obj)</code> </td></tr>
      <tr> <td align="left"><code>sollya_lib_is_fixed(obj)</code> </td></tr>
      <tr> <td align="left"><code>sollya_lib_is_floating(obj)</code> </td></tr>
      <tr> <td align="left"><code>sollya_lib_is_double_obj(obj)</code> </td></tr>
      <tr> <td align="left"><code>sollya_lib_is_single_obj(obj)</code> </td></tr>
      <tr> <td align="left"><code>sollya_lib_is_quad_obj(obj)</code> </td></tr>
      <tr> <td align="left"><code>sollya_lib_is_halfprecision_obj(obj)</code> </td></tr>
      <tr> <td align="left"><code>sollya_lib_is_doubleextended_obj(obj)</code> </td></tr>
      <tr> <td align="left"><code>sollya_lib_is_double_double_obj(obj)</code> </td></tr>
      <tr> <td align="left"><code>sollya_lib_is_triple_double_obj(obj)</code> </td></tr>
      <tr> <td align="left"><code>sollya_lib_is_pi(obj)</code> </td></tr>
  </table>

<h2>10.7 - Recovering the value of a range</h2>
<p>
If a <code>sollya_obj_t</code> is a range, it is possible to recover the values corresponding to the bounds of the range. The range can be recovered either as a <code>mpfi_t</code> or as two <code>mpfr_t</code> (one per bound). This is achieved with the following conversion functions:
<ul>
  <li> <code>int sollya_lib_get_interval_from_range(mpfi_t res, sollya_obj_t arg)</code>,</li>
  <li> <code>int sollya_lib_get_bounds_from_range(mpfr_t res_left, mpfr_t res_right,</code><br>
       <code>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;sollya_obj_t arg)</code>.</li>
</ul>
<p>
They return a boolean integer: false means failure (i.e., if the <code>sollya_obj_t</code> is not a range) and true means success. These functions follow the same conventions as those of the <code>MPFR</code> and <code>MPFI</code> libraries: the variables <code>res</code>, <code>res_left</code> and <code>res_right</code> must be initialized beforehand, and are used to store the result of the conversion. Also, the functions <code>sollya_lib_get_something_from_range</code> <strong>do not change the internal precision</strong> of <code>res</code>, <code>res_left</code> and <code>res_right</code>. If the internal precision is sufficient to perform the conversion without rounding, then it is guaranteed to be exact. If, on the contrary, the internal precision is not sufficient, the actual bounds of the range stored in <code>arg</code> will be rounded at the target precision using a rounding mode that ensures that the inclusion property remains valid, i.e. <code>arg</code> is a subset of <code>res</code> (resp. <code>arg</code> is a subset of [<code>res_left</code>, <code>res_right</code>]).
<p>
Function  <code>int sollya_lib_get_prec_of_range(mp_prec_t *prec, sollya_obj_t arg)</code> stores at <code>*prec</code> a precision that is guaranteed to be sufficient to represent the range stored in <code>arg</code> without rounding. The returned value of this function is a boolean that follows the same convention as above. In conclusion, this is an example of a completely safe conversion:
<p>
<div class="divExample">
&nbsp;&nbsp;...<br>
&nbsp;&nbsp;mp_prec_t prec;<br>
&nbsp;&nbsp;mpfr_t a, b;<br>
<br>
&nbsp;&nbsp;if (!sollya_lib_get_prec_of_range(&amp;prec, arg)) {<br>
&nbsp;&nbsp;&nbsp;&nbsp;sollya_lib_printf("Unexpected error: %b is not a range\n", arg);<br>
&nbsp;&nbsp;}<br>
&nbsp;&nbsp;else {<br>
&nbsp;&nbsp;&nbsp;&nbsp;mpfr_init2(a, prec);<br>
&nbsp;&nbsp;&nbsp;&nbsp;mpfr_init2(b, prec);<br>
&nbsp;&nbsp;&nbsp;&nbsp;sollya_lib_get_bounds_from_range(a, b, arg);<br>
<br>
&nbsp;&nbsp;&nbsp;&nbsp;/* Now [a, b] = arg exactly */<br>
&nbsp;&nbsp;}<br>
&nbsp;&nbsp;...<br>
</div>

<h2>10.8 - Recovering the value of a numerical constant or a constant expression</h2>
<p>
From a conceptual point of view, a numerical constant is nothing but a very simple constant functional expression. Hence there is no difference in <span class="sollya">Sollya</span> between the way constants and constant expressions are handled. The functions presented in this Section allow one to recover the value of such constants or constant expressions into usual C data types.
<p>
A constant expression being given, three cases are possible:
<ul>
  <li> When naively evaluated at the current global precision, the expression always leads to provably exact computations (i.e., at each step of the evaluation, no rounding happens). For instance numerical constants or simple expressions such as (exp(0)+5)/16 fall in this category.</li>
  <li> The constant expressions would be exactly representable at some precision but this is not straightforward from a naive evaluation at the current global precision. An example would be sin(pi/3)/sqrt(3) or even 1 + 2^(-<code>prec</code>-10).</li>
  <li> Finally, a third possibility is that the value of the expression is not exactly representable at any precision on a binary floating-point number. Possible examples are pi or 1/10.</li>
</ul>
<p>
From now on, we suppose that <code>arg</code> is a <code>sollya_obj_t</code> that contains a constant expression (or, as a particular case, a numerical constant). The general scheme followed by the conversion functions is the following: <span class="sollya">Sollya</span> chooses an initial working precision greater than the target precision. If the value of <code>arg</code> is easily proved to be exactly representable at that precision, <span class="sollya">Sollya</span> first computes this exact value and then rounds it to the nearest number of the target format (ties-to-even). Otherwise, <span class="sollya">Sollya</span> tries to adapt the working precision automatically in order to ensure that the result of the conversion is one of both floating-point numbers in the target format that are closest the exact value (a faithful rounding). A warning message indicates that the conversion is not exact and that a faithful rounding has been performed. In some cases really hard to evaluate, the algorithm can even fail to find a faithful rounding. In that case, too, a warning message is emitted indicating that the result of the conversion should not be trusted. Let us remark that these messages can be caught instead of being displayed and adapted handling can be provided by the user of the library at each emission of a warning (see Section&nbsp;<a href="#callbacks">Warning messages in library mode</a>).
<p>
The conversion functions are the following. They return a boolean integer: false means failure (i.e., <code>arg</code> is not a constant expression) and true means success.
<ul>
  <li> <code>int sollya_lib_get_constant_as_double(double *res, sollya_obj_t arg)</code></li>
  <li> <code>int sollya_lib_get_constant_as_int(int *res, sollya_obj_t arg)</code></li>
  <li> <code>int sollya_lib_get_constant_as_int64(int64_t *res, sollya_obj_t arg)</code></li>
  <li> <code>int sollya_lib_get_constant_as_uint64(uint64_t *res, sollya_obj_t arg)</code></li>
  <li> <code>int sollya_lib_get_constant(mpfr_t res, sollya_obj_t arg)</code>: the result of the conversion is stored in <code>res</code>. Please note that <code>res</code> must be initialized beforehand and that its internal precision is not modified by the algorithm.</li>
</ul>
<p>
Function  <code>int sollya_lib_get_prec_of_constant(mp_prec_t *prec, sollya_obj_t arg)</code> tries to find a precision that would be sufficient to exactly represent the value of <code>arg</code> without rounding. If it manages to find such a precision, it stores it at <code>*prec</code> and returns true. If it does not manage to find such a precision, or if <code>arg</code> is not a constant expression, it returns false and <code>*prec</code> is left unchanged.
<p>
In conclusion, here is an example of use for converting a constant expression to a <code>mpfr_t</code>:
<p>
<div class="divExample">
&nbsp;&nbsp;...<br>
&nbsp;&nbsp;mp_prec_t prec;<br>
&nbsp;&nbsp;mpfr_t a;<br>
&nbsp;&nbsp;int test = 0;<br>
<br>
&nbsp;&nbsp;test = sollya_lib_get_prec_of_constant(&amp;prec, arg);<br>
&nbsp;&nbsp;if (test) {<br>
&nbsp;&nbsp;&nbsp;&nbsp;mpfr_init2(a, prec);<br>
&nbsp;&nbsp;&nbsp;&nbsp;sollya_lib_get_constant(a, arg); /* Exact conversion */<br>
&nbsp;&nbsp;}<br>
&nbsp;&nbsp;else {<br>
&nbsp;&nbsp;&nbsp;&nbsp;mpfr_init2(a, 165); /* Initialization at some default precision */<br>
&nbsp;&nbsp;&nbsp;&nbsp;test = sollya_lib_get_constant(a, arg);<br>
&nbsp;&nbsp;&nbsp;&nbsp;if (!test) {<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;sollya_lib_printf("Error: %b is not a constant expression\n", arg);<br>
&nbsp;&nbsp;&nbsp;&nbsp;}<br>
&nbsp;&nbsp;}<br>
&nbsp;&nbsp;...<br>
</div>

<h2>10.9 - Converting a string from <span class="sollya">Sollya</span> to C</h2>
<p>
If <code>arg</code> is a <code>sollya_obj_t</code> that contains a string, that string can be recovered using<br>
<code>int sollya_lib_get_string(char **res, sollya_obj_t arg)</code>.<br>
If <code>arg</code> really is a string, this function allocates enough memory on the heap to store the corresponding string, it copies the string at that newly allocated place, and sets <code>*res</code> so that it points to it. The function returns a boolean integer: false means failure (i.e., <code>arg</code> is not a string) and true means success.
<p>
Since this function allocates memory on the heap, this memory should manually be cleared by the user with <code>sollya_lib_free</code> once it becomes useless.

<h2>10.10 - Recovering the contents of a <span class="sollya">Sollya</span> list</h2>
<p>
It is possible to recover the i-th element of a list <code>arg</code> (as one would do using <code>arg[i]</code> withing <span class="sollya">Sollya</span>) with the following function:<br>
  <code>int sollya_lib_get_element_in_list(sollya_obj_t *res, sollya_obj_t arg, int i)</code>.<br>
It returns a boolean integer: false means failure (i.e. <code>arg</code> is not a list or the index is out of range) and true means success. In case of success, a copy of the i-th element of <code>arg</code> is stored at the address referred to by <code>res</code>. Since it is a copy, it should be cleared with <code>sollya_lib_clear_obj</code> when it becomes useless. Please notice that this function works with regular lists as well as with end-elliptic lists, just as within the interactive tool.
<p>
Another function allows user to recover all elements of a list in a single call. This function returns a C array of <code>sollya_obj_t</code> objects and has the following signature:<br>
<code>int sollya_lib_get_list_elements(sollya_obj_t **L, int *n, int *end_ell,</code><br>
<code>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;sollya_obj_t arg).</code><br>
Three cases are possible:
<ul>
  <li> If <code>arg</code> is a regular list of length N, the function allocates memory on the heap for N <code>sollya_obj_t</code>, sets <code>*L</code> so that it points to that memory segment, and copies each of the elements N of <code>arg</code> to <code>(*L)[0]</code>, ..., <code>(*L)[N-1]</code>. Finally, it sets <code>*n</code> to N, <code>*end_ell</code> to zero and returns true. A particular case is when <code>arg</code> is the empty list: everything is the same except that no memory is allocated and <code>*L</code> is left unchanged.</li>
  <li> If <code>arg</code> is an end-elliptic list containing N elements plus the ellipsis. The function allocates memory on the heap for N <code>sollya_obj_t</code>, sets <code>*L</code> so that it points to that memory segment, and copies each of the elements N of <code>arg</code> at <code>(*L)[0]</code>, ..., <code>(*L)[N-1]</code>. Finally, it sets <code>*n</code> to N, <code>*end_ell</code> to a non-zero value and returns true. The only difference between a regular list and an end-elliptic list containing the same elements is hence that <code>*end_ell</code> is set to a non-zero value in the latter.</li>
  <li> If <code>arg</code> is neither a regular nor an end-elliptic list, <code>*L</code>, <code>*n</code> and <code>*end_ell</code> are left unchanged and the function returns false.</li>
</ul>
<p>
In case of success, please notice that <code>(*L)[0]</code>, ..., <code>(*L)[N-1]</code> should manually be cleared with <code>sollya_lib_clear_obj</code> when they become useless. Also, the pointer <code>*L</code> itself should be cleared with <code>sollya_lib_free</code> since it points to a segment of memory allocated on the heap by <span class="sollya">Sollya</span>.

<h2>10.11 - Recovering the contents of a <span class="sollya">Sollya</span> structure</h2>
<p>
If <code>arg</code> is a <code>sollya_obj_t</code> that contains a structure, the contents of a given field can be recovered using<br>
<code>int sollya_lib_get_element_in_structure(sollya_obj_t *res, char *name,</code><br>
<code>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;sollya_obj_t arg).</code><br>
If <code>arg</code> really is a structure and if that structure has a field named after the string <code>name</code>, this function copies the contents of that field into the <span class="sollya">Sollya</span> object <code>*res</code>. The function returns a boolean integer: false means failure (i.e., if <code>arg</code> is not a structure or if it does not have a field named after <code>name</code>) and true means success.
<p>
It is also possible to get all the field names and their contents. This is achieved through the function<br>
<code>int sollya_lib_get_structure_elements(char ***names, sollya_obj_t **objs, int *n,</code><br>
<code>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;sollya_obj_t arg).</code><br>
If <code>arg</code> really is a structure, say with N fields called &ldquo;fieldA&rdquo;, ..., &ldquo;fieldZ&rdquo;, this functions sets <code>*n</code> to&nbsp;N, allocates and fills an array of N strings and sets <code>*names</code> so that it points to that segment of memory (hence <code>(*names)[0]</code> is the string &ldquo;fieldA&rdquo;, ..., <code>(*names)[N-1]</code> is the string &ldquo;fieldZ&rdquo;). Moreover, it allocates memory for N <code>sollya_obj_t</code>, sets <code>*objs</code> so that it points on that memory segment, and copies the contents of each of the N fields at <code>(*objs)[0]</code>, ..., <code>(*objs)[N-1]</code>. Finally it returns true. If <code>arg</code> is not a structure, the function simply returns false without doing anything. Please note that since <code>*names</code> and <code>*objs</code> point to memory segments that have been dynamically allocated, they should manually be cleared by the user with <code>sollya_lib_free</code> once they become useless.

<h2>10.12 - Decomposing a functional expression</h2>
<p>
If a <code>sollya_obj_t</code> contains a functional expression, one can decompose the expression tree using the following functions. These functions all return a boolean integer: true in case of success (i.e., if the <code>sollya_obj_t</code> argument really contains a functional expression) and false otherwise.

    <a name="list_of_sollya_base_function_t"></a>
    <table border="1" rules="cols">
    <caption>List of values defined in type <code>sollya_base_function_t</code></caption>
<tr> <td align="center">  <code>SOLLYA_BASE_FUNC_COS</code>   </td> <td align="center">  <code>SOLLYA_BASE_FUNC_DOUBLE</code> </td> <td align="center"> <code>SOLLYA_BASE_FUNC_LOG</code> </td></tr>
<tr> <td align="center">  <code>SOLLYA_BASE_FUNC_ACOS</code>  </td> <td align="center">  <code>SOLLYA_BASE_FUNC_DOUBLEDOUBLE</code>      </td> <td align="center"> <code>SOLLYA_BASE_FUNC_LOG_2</code> </td></tr>
<tr> <td align="center">  <code>SOLLYA_BASE_FUNC_ACOSH</code> </td> <td align="center">  <code>SOLLYA_BASE_FUNC_DOUBLEEXTENDED</code>    </td> <td align="center"> <code>SOLLYA_BASE_FUNC_LOG_10</code></td></tr>
<tr> <td align="center">  <code>SOLLYA_BASE_FUNC_COSH</code>  </td> <td align="center">  <code>SOLLYA_BASE_FUNC_TRIPLEDOUBLE</code>      </td> <td align="center"> <code>SOLLYA_BASE_FUNC_LOG_1P</code> </td></tr>
<tr> <td align="center">  <code>SOLLYA_BASE_FUNC_SIN</code>   </td> <td align="center">  <code>SOLLYA_BASE_FUNC_HALFPRECISION</code>     </td> <td align="center"> <code>SOLLYA_BASE_FUNC_EXP</code> </td></tr>
<tr> <td align="center">  <code>SOLLYA_BASE_FUNC_ASIN</code>  </td> <td align="center">  <code>SOLLYA_BASE_FUNC_SINGLE</code>            </td> <td align="center"> <code>SOLLYA_BASE_FUNC_EXP_M1</code> </td></tr>
<tr> <td align="center">  <code>SOLLYA_BASE_FUNC_ASINH</code> </td> <td align="center">  <code>SOLLYA_BASE_FUNC_QUAD</code>              </td> <td align="center"> <code>SOLLYA_BASE_FUNC_NEG</code>  </td></tr>
<tr> <td align="center">  <code>SOLLYA_BASE_FUNC_SINH</code>  </td> <td align="center">  <code>SOLLYA_BASE_FUNC_FLOOR</code>             </td> <td align="center"> <code>SOLLYA_BASE_FUNC_SUB</code> </td></tr>
<tr> <td align="center">  <code>SOLLYA_BASE_FUNC_TAN</code>   </td> <td align="center">  <code>SOLLYA_BASE_FUNC_CEIL</code>              </td> <td align="center"> <code>SOLLYA_BASE_FUNC_ADD</code> </td></tr>
<tr> <td align="center">  <code>SOLLYA_BASE_FUNC_ATAN</code>  </td> <td align="center">  <code>SOLLYA_BASE_FUNC_NEARESTINT</code>        </td> <td align="center"> <code>SOLLYA_BASE_FUNC_MUL</code> </td></tr>
<tr> <td align="center">  <code>SOLLYA_BASE_FUNC_ATANH</code> </td> <td align="center">  <code>SOLLYA_BASE_FUNC_LIBRARYCONSTANT</code>   </td> <td align="center"> <code>SOLLYA_BASE_FUNC_DIV</code>   </td></tr>
<tr> <td align="center">  <code>SOLLYA_BASE_FUNC_TANH</code>  </td> <td align="center">  <code>SOLLYA_BASE_FUNC_LIBRARYFUNCTION</code>   </td> <td align="center"> <code>SOLLYA_BASE_FUNC_POW</code></td></tr>
<tr> <td align="center">  <code>SOLLYA_BASE_FUNC_ERF</code>   </td> <td align="center">  <code>SOLLYA_BASE_FUNC_PROCEDUREFUNCTION</code> </td> <td align="center"> <code>SOLLYA_BASE_FUNC_SQRT</code>    </td></tr>
<tr> <td align="center">  <code>SOLLYA_BASE_FUNC_ERFC</code>  </td> <td align="center">  <code>SOLLYA_BASE_FUNC_FREE_VARIABLE</code>     </td> <td align="center"> <code>SOLLYA_BASE_FUNC_PI</code>     </td></tr>
<tr> <td align="center">  <code>SOLLYA_BASE_FUNC_ABS</code>   </td> <td align="center">  <code>SOLLYA_BASE_FUNC_CONSTANT</code>          </td> <td align="center"> </td></tr>
  </table>

<ul>
  <li> <code>int sollya_lib_get_function_arity(int *n, sollya_obj_t f)</code>: it stores the arity of the head function in <code>f</code> at the address referred to by <code>n</code>. Currently, the mathematical functions handled in <span class="sollya">Sollya</span> are at most dyadic. Mathematical constants are considered as 0-adic functions. The free variable is regarded as the identity function applied to the free variable: its arity is hence 1.</li>
  <li> <code>int sollya_lib_get_head_function(sollya_base_function_t *type, sollya_obj_t f)</code>:<br>
it stores the type of <code>f</code> at the address referred to by <code>type</code>. The <code>sollya_base_function_t</code> is an enum type listing all possible cases (see Table&nbsp;<a href="#list_of_sollya_base_function_t">List of values defined in type <code>sollya_base_function_t</code></a>).</li>
  <li> <code>int sollya_lib_get_subfunctions(sollya_obj_t f, int *n, ...)</code>: let us denote by <code>g_1</code>, ..., <code>g_k</code> the arguments following the argument <code>n</code>. They must be of type <code>sollya_obj_t *</code>. The function stores the arity of <code>f</code> at the address referred to by <code>n</code> (except if <code>n</code> is <code>NULL</code>, in which case, <code>sollya_lib_get_subfunctions</code> simply ignores it and goes on). Suppose that <code>f</code> contains an expression of the form f<sub>0</sub>(f<sub>1</sub>,...,f<sub>s</sub>) (as a particular case, if <code>f</code> is just the free variable, it is regarded in this context as the identity function applied to the free variable, so both f<sub>0</sub> and f<sub>1</sub> are the free variable). For each i from 1 to s, the expression corresponding to f<sub>i</sub> is stored at the address referred to by <code>g_i</code>, unless one of the <code>g_i</code> is <code>NULL</code> in which case the function returns when encountering it. In practice, it means that the user should always put <code>NULL</code> as last argument, in order to prevent the case when they would not provide enough variables <code>g_i</code>. They can check afterwards that they provided enough variables by checking the value contained at the address referred to by <code>n</code>. If the user does not put <code>NULL</code> as last argument and do not provide enough variables <code>g_i</code>, the algorithm will continue storing arguments at random places in the memory (on the contrary, providing more arguments than necessary does not harm: useless arguments are simply ignored and left unchanged). In the case when f<sub>0</sub> is a library function, a library constant or a procedure function, and if the user provides a non-<code>NULL</code> argument <code>g_t</code> after <code>g_s</code>, additionnal information is returned in the remaining argument:
  <ul>
    <li> If f<sub>0</sub> is a library function, a <span class="sollya">Sollya</span> object corresponding to the expression f<sub>0</sub>(x) is stored at the address referred to by <code>g_t</code>. This allows the user to get a <span class="sollya">Sollya</span> object corresponding to function f<sub>0</sub>. This object can further be used to evaluate f<sub>0</sub> at points or to build new expressions involving f<sub>0</sub>. Please notice that a library function object is not necessarily the result of a call to the <code>library</code> command: it can also be, e.g., the derivative of a function created by a call to <code>library</code>.</li>
    <li> If f<sub>0</sub> is a procedure function, a <span class="sollya">Sollya</span> object corresponding to the expression f<sub>0</sub>(x) is stored at the address referred to by <code>g_t</code>. The same remarks as above apply.</li>
    <li> If f<sub>0</sub> is a library constant, f<sub>0</sub> itself is stored at the address referred to by <code>g_t</code>. In this particular case, t=1 and the object referred to by <code>g_t</code> simply gets a copy of <code>f</code>. This (somehow useless) mechanism is made only to handle the cases of library functions, procedure functions and library constants in a unified way.</li>
  </ul>
Please note that the objects that have been stored in variables <code>g_i</code> must manually be cleared once they become useless.</li>
  <li> <code>int sollya_lib_v_get_subfunctions(sollya_obj_t f, int *n, va_list va)</code>: the same as the previous function, but with a <code>va_list</code> argument.</li>
  <li> <code>int sollya_lib_decompose_function(sollya_obj_t f, sollya_base_function_t *type,</code><br>
       <code>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int *n, ...)</code>:<br>
this function is a all-in-one function equivalent to using <code>sollya_lib_get_head_function</code> and <code>sollya_lib_get_subfunctions</code> in only one function call.</li>
  <li> <code>int sollya_lib_v_decompose_function(sollya_obj_t f, sollya_base_function_t *type,</code><br>
      <code>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int *n, va_list va)</code>:<br>
the same as the previous function, but with a <code>va_list</code>.</li>
</ul>
<p>
As an example of use of these functions, the following code returns 1 if <code>f</code> denotes a functional expression made only of constants (i.e., without the free variable), and returns 0 otherwise:
<p>
<div class="divExample">
#include &lt;sollya.h&gt;<br>
<br>
/* Note: we suppose that the library has already been initialized */<br>
int is_made_of_constants(sollya_obj_t f) {<br>
&nbsp;&nbsp;sollya_obj_t tmp1 = NULL;<br>
&nbsp;&nbsp;sollya_obj_t tmp2 = NULL;<br>
&nbsp;&nbsp;int n, r, res;<br>
&nbsp;&nbsp;sollya_base_function_t type;<br>
<br>
&nbsp;&nbsp;r = sollya_lib_decompose_function(f, &amp;type, &amp;n, &amp;tmp1, &amp;tmp2, NULL);<br>
&nbsp;&nbsp;if (!r) { sollya_lib_printf("Not a mathematical function\n"); res = 0; }<br>
&nbsp;&nbsp;else if (n &gt;= 3) {<br>
&nbsp;&nbsp;&nbsp;&nbsp;sollya_lib_printf("Unexpected error: %b has more than two arguments.\n", f);<br>
&nbsp;&nbsp;&nbsp;&nbsp;res = 0;<br>
&nbsp;&nbsp;}<br>
&nbsp;&nbsp;else {<br>
&nbsp;&nbsp;&nbsp;&nbsp;switch (type) {<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;case SOLLYA_BASE_FUNC_FREE_VARIABLE: res = 0; break;<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;case SOLLYA_BASE_FUNC_PI: res = 1; break;<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;case SOLLYA_BASE_FUNC_CONSTANT: res = 1; break;<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;case SOLLYA_BASE_FUNC_LIBRARYCONSTANT: res = 1; break;<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;default:<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;res = is_made_of_constants(tmp1);<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;if ((res) && (n==2)) res = is_made_of_constants(tmp2);<br>
&nbsp;&nbsp;&nbsp;&nbsp;}<br>
&nbsp;&nbsp;}<br>
<br>
&nbsp;&nbsp;if (tmp1) sollya_lib_clear_obj(tmp1);<br>
&nbsp;&nbsp;if (tmp2) sollya_lib_clear_obj(tmp2);<br>
<br>
&nbsp;&nbsp;return res;<br>
}<br>
</div>

<p>
Functions are provided to allow the user to retrieve further information from library function, library constant or procedure function objects:
<ul>
  <li> <code>int sollya_lib_decompose_libraryfunction(int (**f)(mpfi_t, mpfi_t, int),</code><br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<code>int *deriv, sollya_obj_t *e,</code><br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<code>sollya_obj_t g)</code>:<br> assume that <code>g</code> represents an expression f<sub>0</sub>(f<sub>1</sub>) where f<sub>0</sub> is a library function. Then, f<sub>0</sub> is the n-th derivative (for some n) of a function provided within Sollya via an external C function <code>int func(mpfi_t, mpfi_t, int)</code>.<br>
As a result of a call to <code>sollya_lib_decompose_libraryfunction</code>, the value n is stored at the address referred to by <code>deriv</code>, a pointer to <code>func</code> is stored at the address referred to by <code>f</code> and a Sollya object representing f<sub>1</sub> is stored at the address referred to by <code>e</code>. Please notice that the object stored in <code>e</code> must manually be cleared once it becomes useless. Upon success, a boolean integer representing true is returned. If <code>g</code> is not a library function object, nothing happens and false is returned.</li>
  <li> <code>int sollya_lib_decompose_procedurefunction(sollya_obj_t *f, int *deriv,</code><br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<code>sollya_obj_t *e, sollya_obj_t g)</code>:<br>
assume that <code>g</code> represents an expression f<sub>0</sub>(f<sub>1</sub>) where f<sub>0</sub> is a procedure function. Then, f<sub>0</sub> is the n-th derivative (for some n) of a function provided within Sollya via a procedure <code>proc(X, n, p) {...}</code>.<br>
As a result of a call to <code>sollya_lib_decompose_procedurefunction</code>, the value n is stored at the address referred to by <code>deriv</code>, a Sollya object representing the procedure is stored at the address referred to by <code>f</code>, a Sollya object representing f<sub>1</sub> is stored at the address referred to by <code>e</code>. Please notice that the objects stored in <code>f</code> and <code>e</code> must manually be cleared once they become useless. Upon success, a boolean integer representing true is returned. If <code>g</code> is not a procedure function object, nothing happens and false is returned.</li>
  <li> <code>int sollya_lib_decompose_libraryconstant(void (**f)(mpfr_t, mp_prec_t),</code><br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<code>sollya_obj_t c)</code>:<br>
assume that <code>c</code> is a constant provided via an external C function <code>void func(mpfr_t, mp_prec_t)</code>. As a result of a call to <code>sollya_lib_decompose_libraryconstant</code>, a pointer to <code>func</code> is stored at the address referred to by <code>f</code> and a boolean integer representing true is returned. Otherwise, nothing happens and false is returned.</li>
</ul>

<h2>10.13 - Faithfully evaluate a functional expression</h2>
<p>
Let us suppose that <code>f</code> is a functional expression and <code>a</code> is a numerical value or a constant expression. One of the very convenient features of the interactive tool is that the user can simply write <code>f(a)</code> at the prompt: the tool automatically adapts its internal precision in order to compute a value that is a faithful rounding (at the current tool precision) of the true value f(a). Sometimes it does not achieve to find a faithful rounding, but in any case, if the result is not proved to be exact, a warning is displayed explaining how confident one should be with respect to the returned value. This feature is made available within the library with the two following functions:
<ul>
  <li> <code>sollya_fp_result_t</code><br>
      <code>&nbsp;&nbsp;sollya_lib_evaluate_function_at_constant_expression(mpfr_t res, sollya_obj_t f,</code><br>
      <code>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;sollya_obj_t a,</code><br>
      <code>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_t *cutoff)</code>,</li>
  <li> <code>sollya_fp_result_t</code><br>
      <code>&nbsp;&nbsp;sollya_lib_evaluate_function_at_point(mpfr_t res, sollya_obj_t f,</code><br>
      <code>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mpfr_t a, mpfr_t *cutoff)</code>.</li>
</ul>
<p>
In the former, the argument <code>a</code> is any <code>sollya_obj_t</code> containing a numerical constant or a constant expression, while in the latter <code>a</code> is a constant already stored in a <code>mpfr_t</code>. These functions store the result in <code>res</code> and return a <code>sollya_fp_result_t</code> which is an enum type described in Table&nbsp;<a href="#list_of_sollya_fp_result_t">List of values defined in type <code>sollya_fp_result_t</code></a>). In order to understand the role of the <code>cutoff</code> parameter and the value returned by the function, it is necessary to describe the algorithm in a nutshell:
<div style="width:100%; border-bottom: 1px solid black; margin-top: 15px;"></div>
<dl>
  <dd class="omit"><strong>Input:</strong> a functional expression <code>f</code>, a constant expression <code>a</code>, a target precision q, a parameter epsilon.</dd>
  <dd>Choose an initial working precision p.</dd>
  <dd>Evaluate <code>a</code> with interval arithmetic, performing the computations at precision p.</dd>
  <dd>Replace the occurrences of the free variable in <code>f</code> by the interval obtained at step 2. Evaluate the resulting expression with interval arithmetic, performing the computations at precision p. This yields an interval I = [x,y].</dd>
  <dd>Examine the following cases successively (RN denotes rounding to nearest at precision&nbsp;q):
    <ol style="list-style-type: lower-alpha;">
      <li> If RN(x) = RN(y), set <code>res</code> to that value and return.</li>
      <li> If I does not contain any floating-point number at precision q, set <code>res</code> to one of both floating-point numbers enclosing I and return.</li>
      <li> If I contains exactly one floating-point number at precision q, set <code>res</code> to that number and return.</li>
      <li> If all numbers in I are smaller than epsilon in absolute value, then set <code>res</code> to 0 and return.</li>
      <li> If p has already been increased many times, then set <code>res</code> to some value in I and return.</li>
      <li> Otherwise, increase p and go back to step 2.</li>
    </ol>
  </dd>
</dl>
<div style="width:100%; border-bottom: 1px solid black; margin-bottom: 15px;"></div>
<p>
The target precision q is chosen to be the precision of the <code>mpfr_t</code> variable <code>res</code>. The parameter epsilon corresponds to the parameter <code>cutoff</code>. The reason why <code>cutoff</code> is a pointer is that, most of the time, the user may not want to provide it, and using a pointer makes it possible to pass <code>NULL</code> instead. So, if <code>NULL</code> is given, epsilon is set to 0. If <code>cutoff</code> is not <code>NULL</code>, the absolute value of <code>*cutoff</code> is used as value for epsilon. Using a non-zero value for epsilon can be useful when one does not care about the precise value of f(a) whenever its absolute value is below a given threshold. Typically, if one wants to compute the maximum of |f(a<sub>1</sub>)|, ..., |f(a<sub>n</sub>)|, it is not necessary to spend too much effort on the computation of |f(a<sub>i</sub>)| if one already knows that it is smaller than epsilon = max {|f(a<sub>1</sub>)|,...,|f(a<sub>i-1</sub>)|}.

    <a name="list_of_sollya_fp_result_t"></a>
    <table border="1" rules="cols">
    <caption>List of values defined in type <code>sollya_fp_result_t</code></caption>
    <tr><th align="center">Value</th> <th align="center">Meaning</th></tr>
    <tr><td style="padding-bottom: 15px;" align="left"><code>SOLLYA_FP_OBJ_NO_FUNCTION</code> </td> <td style="padding-bottom: 15px;" align="left"> <code>f</code> is not a functional expression.</td> </tr>
    <tr><td style="padding-bottom: 15px;" align="left"><code>SOLLYA_FP_EXPRESSION_NOT_CONSTANT</code> </td> <td style="padding-bottom: 15px;" align="left"> <code>a</code> is not a constant expression.</td> </tr>
    <tr><td style="padding-bottom: 15px;" align="left"><code>SOLLYA_FP_FAILURE</code> </td> <td style="padding-bottom: 15px;" align="left"> The algorithm ended up at step (e) and I contained NaN. This typically happens when a is not in the definition domain of f.</td> </tr>
    <tr><td style="padding-bottom: 15px;" align="left"><code>SOLLYA_FP_CUTOFF_IS_NAN</code> </td> <td style="padding-bottom: 15px;" align="left"> <code>cutoff</code> was not <code>NULL</code> and the value of <code>*cutoff</code> is NaN.</td> </tr>
    <tr><td style="padding-bottom: 15px;" align="left"><code>SOLLYA_FP_INFINITY</code> </td> <td style="padding-bottom: 15px;" align="left"> The algorithm ended up at step (a) with I of the form [+infinity, +infinity] or [-infinity, -infinity]. Hence f(a) is proved to be an exact infinity.</td> </tr>
    <tr><td style="padding-bottom: 15px;" align="left"><code>SOLLYA_FP_PROVEN_EXACT</code> </td> <td style="padding-bottom: 15px;" align="left"> The algorithm ended up at step (a) with a finite value and x = RN(x) = RN(y) = y.</td> </tr>
    <tr><td style="padding-bottom: 15px;" align="left"><code>SOLLYA_FP_CORRECTLY_ROUNDED_PROVEN_INEXACT</code> </td> <td style="padding-bottom: 15px;" align="left"> The algorithm ended up at step (b) with a finite value and <code>res</code> &lt; x &lt;= y or x &lt;= y &lt; <code>res</code>.</td> </tr>
    <tr><td style="padding-bottom: 15px;" align="left"><code>SOLLYA_FP_CORRECTLY_ROUNDED</code> </td> <td style="padding-bottom: 15px;" align="left"> The algorithm ended up at step (a) with a finite value and x &lt;= <code>res</code> &lt;= y. (Please notice that this means that the algorithm did not manage to conclude whether the result is exact or not. However, it might have been able to conclude if the working precision had been increased.)</td> </tr>
    <tr><td style="padding-bottom: 15px;" align="left"><code>SOLLYA_FP_FAITHFUL_PROVEN_INEXACT</code> </td> <td style="padding-bottom: 15px;" align="left"> The algorithm ended up at step (b) with a finite value and <code>res</code> &lt; x &lt;= y or x &lt;= y &lt; <code>res</code>.</td> </tr>
    <tr><td style="padding-bottom: 15px;" align="left"><code>SOLLYA_FP_FAITHFUL</code> </td> <td style="padding-bottom: 15px;" align="left"> The algorithm ended up at step (c) with a finite value. (again, the algorithm did not manage to conclude whether the result is exact or not, but it might have been able to conclude with a larger working precision).</td> </tr>
    <tr><td style="padding-bottom: 15px;" align="left"><code>SOLLYA_FP_BELOW_CUTOFF</code> </td> <td style="padding-bottom: 15px;" align="left"> The algorithm ended up at step (d).</td> </tr>
    <tr><td style="padding-bottom: 15px;" align="left"><code>SOLLYA_FP_NOT_FAITHFUL_ZERO_CONTAINED_BELOW_THRESHOLD</code> </td> <td style="padding-bottom: 15px;" align="left"> The algorithm ended up at step (e) and I was of the form [-delta1, delta2] where 0 &lt; delta1, delta2 &lt;&lt; 1 (below some threshold of the algorithm). This typically happens when f(a) exactly equals zero, but the algorithm does not manage to prove this exact equality.</td> </tr>
    <tr><td style="padding-bottom: 15px;" align="left"><code>SOLLYA_FP_NOT_FAITHFUL_ZERO_CONTAINED_NOT_BELOW_THRESHOLD</code> </td> <td style="padding-bottom: 15px;" align="left"> The algorithm ended up at step (e) with an interval I containing 0 but too large to fall in the above case. (In general, this should be considered as a case of failure and the value stored in <code>res</code> might be completely irrelevant.)</td> </tr>
    <tr><td style="padding-bottom: 15px;" align="left"><code>SOLLYA_FP_NOT_FAITHFUL_ZERO_NOT_CONTAINED</code> </td> <td style="padding-bottom: 15px;" align="left"> The algorithm ended up at step (e) with an interval I that does not contain 0. (Again, this should be considered as a case of failure.)</td> </tr>
    <tr><td style="padding-bottom: 15px;" align="left"><code>SOLLYA_FP_NOT_FAITHFUL_INFINITY_CONTAINED</code> </td> <td style="padding-bottom: 15px;" align="left"> The algorithm ended up at step (e) and (at least) one of the bounds of I was infinite. This typically happens when the limit of f(x) when x goes to a is infinite.</td> </tr>
  </table>

<p>
In the interactive tool, it is also possible to write <code>f(a)</code> when <code>a</code> contains an interval: <span class="sollya">Sollya</span> performs the evaluation using an enhanced interval arithmetic, e.g., using L'Hopital's rule to produce finite (yet valid of course) enclosures even in cases when f exhibits removable singularities (for instance sin(x)/x over an interval containing 0). This feature is achieved in the library with the function<br>
<code>int sollya_lib_evaluate_function_over_interval(mpfi_t res, sollya_obj_t f, mpfi_t a).</code><br>

<p>
This function returns a boolean integer: false means failure (i.e., <code>f</code> is not a functional expression), in which case <code>res</code> is left unchanged, and true means success, in which case <code>res</code> contains the result of the evaluation. The function might succeed, and yet <code>res</code> might contain something useless such as an unbounded interval or even [NaN, NaN] (this happens for instance when <code>a</code> contains points that lie in the interior of the complement of the definition domain of <code>f</code>). It is the user's responsibility to check afterwards whether the computed interval is bounded, unbounded or NaN.

<h2>10.14 - Name of the free variable</h2>
<p>
The default name for the free variable is the same in the library and in the interactive tool: it is <code>_x_</code>. In the interactive tool, this name is automatically changed at the first use of an undefined symbol. Accordingly in library mode, if an object is defined by <code>sollya_lib_parse_string</code> with an expression containing an undefined symbol, that symbol will become the free variable name if it has not already been changed before. But what if one does not use <code>sollya_lib_parse_string</code> (because it is not efficient) but one wants to change the name of the free variable? The name can be changed with <code>sollya_lib_name_free_variable("some_name")</code>.
<p>
It is possible to get the current name of the free variable with <code>sollya_lib_get_free_variable_name()</code>. This function returns a <code>char *</code> containing the current name of the free variable. Please note that this <code>char *</code> is dynamically allocated on the heap and should be cleared after its use with <code>sollya_lib_free()</code> (see below).

<a name="library_commands_and_functions"></a>
<h2>10.15 - Commands and functions</h2>
<p>
Besides some exceptions, every command and every function available in the <span class="sollya">Sollya</span> interactive tool has its equivalent (with a very close syntax) in the library. Section&nbsp;<a href="#commandsAndFunctions">List of available commands</a> of the present documentation gives the library syntax as well as the interactive tool syntax of each commands and functions. The same information is available within the interactive tool by typing <code>help some_command</code>. So if one knows the name of a command or function in the interactive tool, it is easy to recover its library name and signature.
<p>
There are some commands and functions available in interactive mode which, for syntactical reasons, have a different function name in the <span class="sollya">Sollya</span> library:
<ul>
  <li> The <span class="sollya">Sollya</span> language construction <code>(obj1)(obj2, obj3, ...)</code> which applies the object <code>obj1</code> to the objects <code>obj2</code>, <code>obj3</code>, etc. is expressed in the <span class="sollya">Sollya</span> library through a call to<br>
 <code>sollya_obj_t sollya_lib_apply(sollya_obj_t obj1, sollya_obj_t obj2, ...)</code><br>
 resp. <code>sollya_obj_t sollya_lib_v_apply(sollya_obj_t obj1, sollya_obj_t obj2, va_list)</code>.</li>
</ul>
<p>
A particular point is worth mentioning: some functions of the tool such as <code>remez</code> for instance have a variable number of arguments. For instance, one might call <code>remez(exp(x), 4, [0,1])</code> or <code>remez(1, 4, [0,1], 1/exp(x))</code>. This feature is rendered in the C library by the use of variadic functions (functions with an arbitrary number of arguments), as they are permitted by the C standard. The notable difference is that there must <strong>always be an explicit NULL argument</strong> at the end of the function call. Hence one can write <code>sollya_lib_remez(a, b, c, NULL)</code> or <code>sollya_lib_remez(a, b, c, d, NULL)</code>. It is very easy to forget the <code>NULL</code> argument and to use for instance <code>sollya_lib_remez(a, b, c)</code>. This is <strong>completely wrong</strong> because the memory will be read until a <code>NULL</code> pointer is found. In the best case, this will lead to an error or a result obviously wrong, but it could also lead to subtle, not-easy-to-debug errors. The user is advised to be particularly careful with respect to this point.
<p>
Each command or function accepting a variable number of arguments comes in a <code>sollya_lib_v_</code> version accepting a <code>va_list</code> parameter containing the list of optional arguments. For instance, one might write a function that takes as arguments a function f, an interval I, optionally a weight function w, optionally a quality parameter q. That function would display the minimax obtained when approximating f over I (possibly with weight w and quality q) by polynomials of degree n=2 to 20. So, that function would get a variable number of arguments (i.e. a <code>va_list</code> in fact) and pass them straight to remez. In that case, one needs to use the <code>v_remez</code> version, as the following code shows:

<div class="divExample">
#include &lt;sollya.h&gt;<br>
#include &lt;stdarg.h&gt;<br>
<br>
/* Note: we suppose that the library has already been initialized */<br>
void my_function(sollya_obj_t f, sollya_obj_t I, ...) {<br>
&nbsp;&nbsp;sollya_obj_t n, res;<br>
&nbsp;&nbsp;int i;<br>
&nbsp;&nbsp;va_list va;<br>
<br>
&nbsp;&nbsp;for(i=2;i&lt;=20;i++) {<br>
&nbsp;&nbsp;&nbsp;&nbsp;n = SOLLYA_CONST(i);<br>
&nbsp;&nbsp;&nbsp;&nbsp;va_start(va, I);<br>
&nbsp;&nbsp;&nbsp;&nbsp;res = sollya_lib_v_remez(f, n, I, va);<br>
&nbsp;&nbsp;&nbsp;&nbsp;sollya_lib_printf("Approximation of degree %b is %b\n", n, res);<br>
&nbsp;&nbsp;&nbsp;&nbsp;va_end(va);<br>
&nbsp;&nbsp;&nbsp;&nbsp;sollya_lib_clear_obj(n);<br>
&nbsp;&nbsp;&nbsp;&nbsp;sollya_lib_clear_obj(res);<br>
&nbsp;&nbsp;}<br>
<br>
&nbsp;&nbsp;return;<br>
}<br>
</div>

<p>
<a name="callbacks"></a>
<h2>10.16 - Warning messages in library mode</h2>
<p>
The philosophy of <span class="sollya">Sollya</span> is &ldquo;whenever something is not exact, explicitly warn about that&rdquo;. This is a nice feature since this ensures that the user always perfectly knows the degree of confidence they can have in a result (is it exact? or only faithful? or even purely numerical, without any warranty?) However, it is sometimes desirable to hide some (or all) of these messages. This is especially true in library mode where messages coming from <span class="sollya">Sollya</span> are intermingled with the messages of the main program. The library hence provides a specific mechanism to catch all messages emitted by the <span class="sollya">Sollya</span> core and handle each of them specifically: installation of a callback for messages.
<p>
Before describing the principle of the message callback, it seems appropriate to recall that several mechanisms are available in the interactive tool to filter the messages emitted by <span class="sollya">Sollya</span>. These mechanisms are also available in library mode for completeness. When a message is emitted, it has two characteristics: a verbosity level and an id (a number uniquely identifying the message). After it has been emitted, it passes through the following steps where it can be filtered. If it has not been filtered (and only in this case) it is displayed.
<ol>
  <li> If the verbosity level of the message if greater than the value of the environment variable <code>verbosity</code>, it is filtered.</li>
  <li> If the environment variable <code>roundingwarnings</code> is set to <code>off</code> and if the message informs the user that a rounding occurred, it is filtered.</li>
  <li> If the id of the message has been registered with the <code>suppressmessage</code> command, the message is filtered.</li>
  <li> If a message callback has been installed and if the message has not been previously filtered, it is handled by the callback, which decides to filter it or to permit its displaying.</li>
</ol>
<p>
A message callback is a function of the form <code>int my_callback(sollya_msg_t msg, void *data)</code>. It receives as input an object representing the message and a user-defined pointer. It performs whatever treatment seems appropriate and returns an integer interpreted as a boolean. If the returned value is false, the message is not displayed. If, on the contrary, the returned value is true, the message is displayed as usual. By default, no callback is installed and all messages are displayed. To install a callback, use <code>sollya_lib_install_msg_callback(my_callback, data)</code>. The <code>(void *)</code> pointer <code>data</code> is arbitrary (it can be <code>NULL</code>) and is simply transmitted as second argument at each call of the callback. It can be used, e.g., to point to a segment of memory where some information should be stored from a call of the callback to another.
<p>
Please remember that, if a message is filtered because of one of the three other mechanisms, it will never be transmitted to the callback. Hence, in library mode, if one wants to catch every single message through the callback, one should set the value of <code>verbosity</code> to <code>MAX_INT</code>, set <code>roundingwarnings</code> to <code>on</code> (this is the default anyway) and one should not use the <code>suppressmessage</code> mechanism.
<p>
It is possible to come back to the default behavior, using <code>sollya_lib_uninstall_msg_callback()</code>. Please notice that callbacks do not stack over each other: i.e., if some callback <code>callback1</code> is installed, and if one installs another one <code>callback2</code>, then the effect of <code>sollya_lib_uninstall_msg_callback()</code> is to come back to the default behavior, <strong>and not</strong> to come back to callback <code>callback1</code>.
<p>
Both <code>sollya_lib_install_msg_callback</code> and <code>sollya_lib_uninstall_msg_callback</code> return an integer interpreted as a boolean: false means failure and true means success.
<p>
It is possible to get the currently installed callback using <code>sollya_lib_get_msg_callback(cb_ptr, data_ptr)</code>. This stores the current callback at the address referred to by <code>cb_ptr</code> (the type of <code>cb_ptr</code> is hence <code>int (**)(sollya_msg_t, void *)</code>) and stores the current data pointer at the address referred to by <code>data_ptr</code> (which has hence <code>(void **)</code> type). The arguments <code>cb_ptr</code> and <code>data_ptr</code> can be <code>NULL</code> in which case the corresponding argument is not retrieved (please take care of the difference between <code>data_ptr</code> being <code>NULL</code> and <code>data_ptr</code> pointing to a <code>(void *)</code> pointer which value is <code>NULL</code>). If no callback is currently installed, the <code>NULL</code> value is stored at the addresses referred to by <code>cb_ptr</code> and <code>data_ptr</code>.
<p>
The type <code>sollya_msg_t</code> is indeed a pointer and its content is only accessible during the callback call: it does not make sense to keep it for further use after the callback call. Currently the type has only two accessors:
<ul>
  <li> <code>int sollya_lib_get_msg_id(sollya_msg_t msg)</code> returns an integer that identifies the type of the message. The message types are listed in the file <code>sollya-messages.h</code>. Please note that this file not only lists the possible identifiers but only defines meaningful names to each possible message number (e.g., <code>SOLLYA_MSG_UNDEFINED_ERROR</code> is an alias for the number 2 but is more meaningful to understand what the message is about). It is recommended to use these names instead of numerical values.</li>
  <li> <code>char *sollya_lib_msg_to_text(sollya_msg_t msg)</code> returns a generic string briefly summarizing the contents of the message. Please note that this <code>char *</code> is dynamically allocated on the heap and should manually be cleared with <code>sollya_lib_free</code> when it becomes useless.</li>
</ul>
<p>In the future, other accessors could be added (to get the verbosity level at which the message has been emitted, to get data associated with the message, etc.) The developers of <span class="sollya">Sollya</span> are open to suggestions and feature requests on this subject.
<p>
As an illustration let us give a few examples of possible use of callbacks:
<p>
<strong>Example 1:</strong> A callback that filters everything.
<div class="divExample">
int hide_everything(sollya_msg_t msg, void *data) {<br>
&nbsp;&nbsp;return 0;<br>
}<br>
</div>

<p>
<strong>Example 2:</strong> filter everything but the messages indicating that a comparison is uncertain.
<div class="divExample">
int keep_comparison_warnings(sollya_msg_t msg, void *data) {<br>
&nbsp;&nbsp;switch(sollya_lib_get_msg_id(msg)) {<br>
&nbsp;&nbsp;&nbsp;&nbsp;case SOLLYA_MSG_TEST_RELIES_ON_FP_RESULT_THAT_IS_NOT_FAITHFUL:<br>
&nbsp;&nbsp;&nbsp;&nbsp;case SOLLYA_MSG_TEST_RELIES_ON_FP_RESULT:<br>
&nbsp;&nbsp;&nbsp;&nbsp;case SOLLYA_MSG_TEST_RELIES_ON_FP_RESULT_FAITHFUL_BUT_UNDECIDED:<br>
&nbsp;&nbsp;&nbsp;&nbsp;case SOLLYA_MSG_TEST_RELIES_ON_FP_RESULT_FAITHFUL_BUT_NOT_REAL:<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;return 1;<br>
&nbsp;&nbsp;&nbsp;&nbsp;default:<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;return 0;<br>
&nbsp;&nbsp;}<br>
}<br>
</div>

<p>
<strong>Example 3:</strong> ensuring perfect silence for a particular function call (uses the callback defined in Example&nbsp;1).
<div class="divExample">
...<br>
int (*old_callback)(sollya_msg_t, void *);<br>
void *old_data;<br>
sollya_lib_get_msg_callback(&amp;old_callback, &amp;old_data);<br>
sollya_lib_install_msg_callback(hide_everything, NULL);<br>
&nbsp;&nbsp;/* Here takes place the function call that must be completely silent */<br>
if (old_callback) sollya_lib_install_msg_callback(old_callback, old_data);<br>
...<br>
</div>

<p>
<strong>Example 4:</strong> using the <code>(void *)</code> data argument to store information from a call to another.
<div class="divExample">
int set_flag_on_problem(sollya_msg_t msg, void *data) {<br>
&nbsp;&nbsp;switch(sollya_lib_get_msg_id(msg)) {<br>
&nbsp;&nbsp;&nbsp;&nbsp;case SOLLYA_MSG_DOUBLE_ROUNDING_ON_CONVERSION:<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*((int *)(data)) = 1;<br>
&nbsp;&nbsp;}<br>
&nbsp;&nbsp;return 1;<br>
}<br>
<br>
...<br>
<br>
int main() {<br>
&nbsp;&nbsp;int flag_double_rounding = 0;<br>
&nbsp;&nbsp;...<br>
&nbsp;&nbsp;sollya_lib_init();<br>
&nbsp;&nbsp;sollya_lib_install_msg_callback(set_flag_on_problem, &amp;flag_double_rounding);<br>
&nbsp;&nbsp;...<br>
}<br>
</div>

<p>
More involved examples are possible: for instance, instead of setting a flag, it is possible to keep in some variable what the last message was. One may even implement a stack mechanism and store the messages in a stack, in order to handle them later. (Please remember however that <code>sollya_msg_t</code> is a pointer type and that the <code>sollya_msg_t</code> object received as argument of a callback call has no more meaning once the callback call returned. If a stack mechanism is implemented it should store information such as the message ID, or the message text, as given by <code>sollya_lib_get_msg_id</code> and <code>sollya_lib_msg_to_text</code>, but not the <code>sollya_msg_t</code> object itself.)

<a name="customMemoryFunctions"></a>
<h2>10.17 - Using <span class="sollya">Sollya</span> in a program that has its own allocation functions</h2>
<p>
<span class="sollya">Sollya</span> uses its own allocation functions: as a consequence, pointers that have been allocated by <span class="sollya">Sollya</span> functions must be freed using <code>sollya_lib_free</code> instead of the usual <code>free</code> function. Another consequence is that <span class="sollya">Sollya</span> registers its own allocation functions to the <code>GMP</code> library, using the mechanism provided by <code>GMP</code>, so that <code>GMP</code> also uses <span class="sollya">Sollya</span> allocation functions behind the scene, when the user performs a call to, e.g., <code>mpz_init</code>, <code>mpfr_init2</code>, etc.
<p>
In general, this is completely harmless and the user might even not notice it. However, this is a problem if <span class="sollya">Sollya</span> is used in a program that also uses its own allocation functions and that has already registered these functions to <code>GMP</code>. Actually:
<ul>
  <li> If the main program has already registered allocation functions to <code>GMP</code> and if <span class="sollya">Sollya</span> is naively initialized with <code>sollya_lib_init()</code>, <span class="sollya">Sollya</span> will register its own allocation functions, thus overriding the previously registered functions.</li>
  <li> If the user initializes first <span class="sollya">Sollya</span>, and then registers its own allocation functions to <code>GMP</code>, the exact opposite happens: <span class="sollya">Sollya</span> allocation functions are overridden by those of the user, and this will likely cause <span class="sollya">Sollya</span> to crash (or worst, silently behave not reliably).</li>
</ul>
<p>
In order to solve this issue, <span class="sollya">Sollya</span> provides a chaining mechanism that we are now going to describe. The idea is the following: suppose that the main program should use a function <code>custom_malloc</code>. The user should not use <code>mp_set_memory_functions</code> as usual, but should instead initialize <span class="sollya">Sollya</span> with the initializing function described above. This will cause <span class="sollya">Sollya</span> to register an allocation function <code>sollya_lib_malloc</code> to <code>GMP</code>. This function overloads <code>custom_malloc</code>: when called, it uses <code>custom_malloc</code> to perform the actual allocation and does nothing else but some internal accounting and verification for that allocation. To repeat, the actual allocation is done by <code>custom_malloc</code>; hence from the point of view of the user, the mechanism is completely transparent and equivalent to directly registering <code>custom_malloc</code> to <code>GMP</code>. The same holds for all other allocation functions: in particular, this is true for <code>free</code> as well: if a function <code>custom_free</code> is given at the initialization of <span class="sollya">Sollya</span>, then the function <code>sollya_lib_free</code> eventually uses <code>custom_free</code> to free the memory. 
<p>
The initialization function providing this mechanism is:<br>
<code>int sollya_lib_init_with_custom_memory_functions(</code><br>
<code>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;void *(*custom_malloc)(size_t),</code><br>
<code>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;void *(*custom_calloc)(size_t, size_t),</code><br>
<code>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;void *(*custom_realloc)(void *, size_t),</code><br>
<code>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;void (*custom_free)(void *),</code><br>
<code>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;void *(*custom_realloc_with_size)(void *, size_t, size_t),</code><br>
<code>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;void (*custom_free_with_size)(void *, size_t)).</code><br>
None of the arguments is mandatory: if the user does not want to provide an argument, they may use <code>NULL</code> as a placeholder for that argument. In that case, the corresponding <span class="sollya">Sollya</span> default function will be used. Indeed, the default initializing function <code>sollya_lib_init()</code> is just an alias to <code>sollya_lib_init_with_custom_memory_functions(NULL, NULL, NULL, NULL, NULL, NULL)</code>.
<p>
Please notice, that if <code>custom_malloc</code> is provided, then the function <code>sollya_lib_malloc</code> will be defined as an overloaded version of <code>custom_malloc</code>. Hence, <code>custom_malloc</code> will eventually be used for all the allocations performed by <span class="sollya">Sollya</span> (including the allocation of memory for its own purpose). This is true also for <code>custom_calloc</code>, <code>custom_realloc</code> and <code>custom_free</code>. However, this is not the case for <code>custom_realloc_with_size</code> and <code>custom_free_with_size</code>: these functions are only required for the registration to <code>GMP</code> and are not used by <span class="sollya">Sollya</span> itself (except of course when <span class="sollya">Sollya</span> allocates function through a call to a <code>GMP</code>, <code>MPFR</code> or <code>MPFI</code> function). Thus, to sum up:
<ul>
  <li> If the user only wants to register their own functions to <code>GMP</code> through <span class="sollya">Sollya</span>, they  only need to provide <code>custom_malloc</code>, <code>custom_realloc_with_size</code> and <code>custom_free_with_size</code> at the initialization of <span class="sollya">Sollya</span> (actually an overloaded version will be registered to <code>GMP</code> but this is transparent for the user, as explained above).</li>
  <li> If the user also wants <span class="sollya">Sollya</span> to use their custom allocation functions for all allocations of memory by <span class="sollya">Sollya</span>, then they also need to provide <code>custom_calloc</code>, <code>custom_realloc</code> and <code>custom_free</code>.</li>
</ul>
<p>
Of course, even if the user registers <code>custom_malloc</code>, <code>custom_free</code>, etc., at the initialization of <span class="sollya">Sollya</span>, they stay free to use them for their own allocation needs: only allocations performed by <code>GMP</code> (and consequently <code>MPFR</code> and <code>MPFI</code>) and allocations performed by <span class="sollya">Sollya</span> have to use the chaining mechanism. However, for the convenience of the user, the library also provides access to the allocation functions of <span class="sollya">Sollya</span>. They are the following:
<ul>
  <li> <code>void sollya_lib_free(void *)</code></li>
  <li> <code>void *sollya_lib_malloc(size_t)</code></li>
  <li> <code>void *sollya_lib_calloc(size_t, size_t)</code></li>
  <li> <code>void *sollya_lib_realloc(void *, size_t)</code>.</li>
</ul>
<p>No access to the overloaded version of <code>custom_realloc_with_size</code> and <code>custom_free_with_size</code> is provided, but if the user really wants to retrieve them, they can do it with <code>mp_get_memory_functions</code> since they are registered to <code>GMP</code>.

</body>
