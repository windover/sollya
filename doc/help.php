<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<html>
<head>
<title>Sollya User's Manual</title>
<meta name="author" content="Sylvain Chevillard, Christoph Lauter">
<meta name="copyright" content="2009 Laboratoire de l'Informatique du Parallélisme - UMR CNRS - ENS Lyon - UCB Lyon 1 - INRIA 5668">
<meta name="keywords" content="help, sollya, User's Manual">
<meta name="description" content="This is part of Sollya User's Manual">
<meta http-equiv="content-type" content="text/html; charset=UTF-8">
<link href="sollyacss.css" type="text/css" rel="stylesheet">
</head>

<body>
<?php 

include("ListOfCommands.php");
$command=$_GET['name'];
$shouldGoBack=$_GET['goBack'];
$n=count($listOfCommands)/2;
$allInOne = 0;

function linkTo($style, $somewhere, $something) {
  if ($GLOBALS['allInOne']==1) {
    echo "<a class=\"".$style."\" href=\"#".$somewhere."\">".$something."</a>";
  }
  else {
    echo "<a class=\"".$style."\" href=\"help.php?name=".$somewhere."\">".$something."</a>";
  }
}

function printList() {
  echo "<p><a href=\"..\">Go back to the main page of Sollya</a>\n";
  echo "<h1>Commands available within Sollya</h1>\n";
  echo "<p><a name=\"listOfCommands\"></a>\n";
  echo "<ul id=\"listOfCommands\">\n";
  for($i=0;$i<$GLOBALS['n']; $i++) {
    echo "  <li>";
    linkTo("normal", $GLOBALS['listOfCommands'][2*$i],$GLOBALS['listOfCommands'][1+2*$i]);
    echo "</li>\n";
  }
  echo "</ul>\n";
}

function printCommand($i) {
  echo "<div class=\"block\" id=\"".$GLOBALS['listOfCommands'][2*$i]."\">\n";
  include($GLOBALS['listOfCommands'][2*$i].".php");
  if ($GLOBALS['shouldGoBack']!="none") {
    linkTo("back", "listOfCommands", "Go back to the list of commands");
  }
  echo "</div> <!-- ".$GLOBALS['listOfCommands'][2*$i]." -->\n\n\n";
}



if (($GLOBALS['command']=="")||($GLOBALS['command']=="allInOne")) {
  $GLOBALS['allInOne'] = 1;
  printList();
  echo "<h1>Help pages</h1>\n\n";	
  for($i=0;$i<$GLOBALS['n']; $i++) {
    printCommand($i);
  }
}
else {
  $GLOBALS['allInOne'] = 0;
  if ($GLOBALS['command']=="listOfCommands") { printList(); }
  else {
    $i = array_search($GLOBALS['command'], $GLOBALS['listOfCommands']);
    if ($i === FALSE) {
      echo "<h1>Error</h1>This command does not exist!<br>";
      linkTo("back", "listOfCommands", "Go back to the list of commands");
    }
    else {
      $i = $i/2;
      printCommand($i);
    }
  }
}

?>
</body>
