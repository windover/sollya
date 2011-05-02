<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<html>
<head>
<?php include("distrib.php"); ?> 
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<meta http-equiv="Content-Language" content="en">
<meta name="keywords" content="Sollya, elementary function, correct rounding, Remez, minimax, infinity norm, infinite norm, supremum norm">
<link rel="shortcut icon" href="http://sollya.gforge.inria.fr/favicon.ico" type="image/x-icon">
<title>Sollya software tool</title>

<style type="text/css"><!--
h2 { font-size: large;}
 --></style>

</head>

<body>
<div><img alt="Sollya is also a beautiful australian flower" src="./sollya.jpg" style="margin: 10px; float: right;"></div>

<h1>Sollya</h1>

<p>Sollya is a tool environment for safe floating-point code
development. It is particularily targeted to the automatized
implementation of mathematical floating-point libraries
(<big><code>libm</code></big>). Amongst other features, it
offers a <a href="http://prunel.ccsd.cnrs.fr/ensl-00119810">certified
infinity (supremum) norm</a> and a fast <a href="http://en.wikipedia.org/wiki/Remez_algorithm">Remez algorithm</a>.</p>

<p><strong>Sollya</strong> is developped
by <a href="http://www.ens-lyon.fr/LIP/Arenaire/">Arénaire</a>, <a href="http://caramel.loria.fr/">Caramel</a>, <a href="http://www-pequan.lip6.fr/">PEQUAN</a> and <a href="http://www-sop.inria.fr/apics/joomla/">APICS</a>.
It is written by <a href="http://www.christoph-lauter.org/">Christoph Lauter</a>,
<a href="http://www-sop.inria.fr/members/Sylvain.Chevillard/">Sylvain Chevillard</a>,
<a href="http://perso.ens-lyon.fr/mioara.joldes/">M. Joldeș</a> and N. Jourdan.

<hr>

<h2>Sollya provides you:</h2>
<ul>    
  <li>a <a href="http://prunel.ccsd.cnrs.fr/ensl-00119810">certified infinity (supremum) norm</a> for computing safe approximation error bounds,</li>

  <li>an automatized implementer for approximation polynomials in <a href="http://lipforge.ens-lyon.fr/www/crlibm/">CRlibm</a>-style C-code with the corresponding <a href="http://lipforge.ens-lyon.fr/www/gappa/">Gappa</a> proof,</li>

  <li>a fast implementation of <a href="http://en.wikipedia.org/wiki/Remez_algorithm">Remez algorithm</a> for computing minimax polynomials,</li>

  <li>a full-featured programming language adapted to analysis of numerical programs like in a Computer-Algebra-System,</li>

  <li>a faithful-rounding, multi-precision evaluator of composed functional expressions extending <a href="http://www.mpfr.org/">MPFR</a>,</li>

  <li>a highly accurate and fast floating-point infinity (supremum) norm,</li>

  <li>support for floating-point rounding operators and expansions in common precisions,</li>

  <li>a special <a href="http://hal.inria.fr/inria-00119513/fr/">floating-point minimax</a> procedure,</li>

  <li>basic <a href="http://www.w3.org/Math/">MathML</a> input and output support,</li>

  <li>interfaces for extending Sollya with your own code and much more...</li>
</ul>

<hr>

<h2>Download Sollya:</h2>
<ul>
  <li> <strong><a href="https://gforge.inria.fr/frs/?group_id=1015&release_id=5855">Sollya 2.9</a></strong> has been released and can be downloaded <a href="https://gforge.inria.fr/frs/download.php/28248/sollya-2.9.tar.gz">here</a>.
  <li> <?php echo "A weekly build (last compiled on $compile_time) of the SVN sources is available as a <a href=\"$targz_name\">tar.gz</a>, as a <a href=\"$tarbz2_name\">tar.bz2</a> and as a <a href=\"$zip_name\">zip</a> file." ?>
  <li> The latest development version is available through anonymous SVN 
    checkout as indicated <a href="http://gforge.inria.fr/scm/?group_id=1015">here</a>. </li>
</ul>

<hr>

<h2>Documentation:</h2>
<ul>
  <li> Sollya comes with an integrated help environment. Just type <code>help;</code> on the Sollya prompt. </li>
  <li> A <a href="https://gforge.inria.fr/frs/download.php/28251/sollya.pdf">complete documentation</a> in one document is available for download <a href="https://gforge.inria.fr/frs/download.php/28251/sollya.pdf">here</a>. </li>
   <li> An online documentation is available:
     <ul><li>A complete introduction to the basic ideas of Sollya, together with a small tutorial is available <a href="sollya.php">here</a>.</li>
         <li>The documentation of all commands available within Sollya can be found <a href="help.php">here as a single page</a> or <a href="help.php?name=listOfCommands">here with each command on a different page</a> (faster to load).</li>
     </ul>
   </li>
</ul>
<hr>

<p><strong>Sollya</strong> is based on the following softwares and software libraries: </p>
<ul>
  <li> A C compiler such as <a href="http://gcc.gnu.org/">gcc</a>, </li>
  <li> a C++ compiler such as <a href="http://gcc.gnu.org/">g++</a>, </li>
  <li> <a href="http://gmplib.org/">the GNU MP Bignum Library</a>, </li>
  <li> <a href="http://www.mpfr.org/">the MPFR library</a> version 2.2.0 or later, </li>
  <li> <a href="http://gforge.inria.fr/projects/mpfi/">the MPFI library</a>, </li>
  <li> <a href="http://perso.ens-lyon.fr/damien.stehle/">the fplll software</a>, </li>
  <li> <a href="http://xmlsoft.org/">the XML C parser and toolkit of Gnome (libxml2)</a>, </li>  
  <li> <a href="http://www.gnu.org/software/bison/">the Bison GNU parser generator</a> version 2.3 or later, </li>  
  <li> <a href="http://www.gnu.org/software/flex/">Flex </a> version 2.5.33 or later, </li>  
  <li> <a href="http://www.gnuplot.info/">gnuplot</a>. </li>  
</ul>
<p> Remark that Bison and Flex are only needed if Sollya is to be
built from a SVN checkout or if the Sollya lexer and parser files are
modified. </p>
<p> The gnuplot software is needed neither for building nor for
  executing Sollya. Sollya is just able to call the gnuplot executable
  with a data set representing the graph of a function. </p>

<hr>

<p><strong>Sollya</strong> is already used by the following projects: </p>
<ul>
  <li> the <a href="http://lipforge.ens-lyon.fr/www/metalibm/">Metalibm</a> project,</li>
  <li> the <a href="http://www.ens-lyon.fr/LIP/Arenaire/Ware/FloPoCo/">FloPoCo</a> project</li>
  <li> and perhaps some others...</li>
</ul>

<hr>

<h2>License</h2>
<p style="font-size:small;">
The Sollya tool and the material of this website is Copyright &copy;&nbsp;2006-2011 by<br>
<span style="text-indent:3em; display:block;">Laboratoire de l'Informatique du Parallélisme - UMR CNRS - ENS Lyon - UCB Lyon 1 - INRIA 5668, Lyon, France,</span>
<span style="text-indent:3em;display:block;">LORIA (CNRS, INPL, INRIA, UHP, U-Nancy 2) Nancy, France,</span>
<span style="text-indent:3em;display:block;">Laboratoire d'Informatique de Paris 6, Équipe PEQUAN, UPMC Université Paris 06 - CNRS - UMR 7606 - LIP6, Paris, France, and by</span>
<span style="text-indent:3em;display:block;">INRIA Sophia-Antipolis Méditerranée, APICS Team, Sophia-Antipolis, France.</span>
All rights reserved.
<p style="font-size:small;">
The Sollya tool is open software. It is distributed and can be used,
modified and redistributed under the terms of the CeCILL-C licence
available at <a href="http://www.cecill.info/">http://www.cecill.info/</a> and reproduced in the <code>COPYING</code> file of the distribution. The distribution contains parts of other libraries as a support for but not integral part of
Sollya. These libraries are reigned by the GNU Lesser General Public
License that is available at <a href="http://www.gnu.org/licenses/">http://www.gnu.org/licenses/</a> and reproduced in the <code>COPYING</code> file of the distribution.
<p style="font-size:small;">
This software, the Sollya tool, is distributed WITHOUT ANY WARRANTY; without even the 
implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

<hr>

<p><?php echo "Last update: ".date("m/d/Y",getlastmod()) ?> </p>

</body>
</html>
