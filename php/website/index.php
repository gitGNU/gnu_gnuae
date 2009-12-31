<!--
// 
//   Copyright (C) 2009 Free Software Foundation, Inc.
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU Affero General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
-->

<html>
<head>
<meta name="author" content="Rob Savoye">
   <title>Solar Designs</title>
   
   <script language="javascript" src="gnuae.js"></script>

   <script>
   var rows1=[];

<?php

include "support.php";

// These globals are for the initial project data
$projname = "unamed project";
$projid = 0;
$projinfo = "Other information you want associated with this project profile.";
$projlat = 0;
$projlon = 0;

// $boo = gui_get_data(0, "Laptop", "loads");
// $ii = count($boo) - 1;
// if ($ii > 0) {
//   while ($ii) {
//     ?>
//     rows1[rows1.length]=<?php echo '"'.$boo[$ii].'"'?>;
//     <?php
//         $ii = $ii - 1;
//   }
// }

?>
</script>

</head>

<body background="../images/seneca3-bg.jpg">
  
  <h2 align=center>Solar Design</h2>
  
  <?php
  
  // This parameter just turns on additional button to manually force pages
  // to load when testing.
  if (isset($_GET['godmode'])) {
    $godmode = $_GET['godmode'];
  } else {
    $godmode = "off";
  }

// The numeric ID of this project
  if (isset($_GET['projid'])) {       
    $projid = $_GET['projid'];
  } else {
    $projid = 0;
  }

// The symbolic name for this project
  if (isset($_GET['projname'])) {       
    $projname = $_GET['projname'];
    //$projinfo = $_GET['projinfo'];
  } else {
    $projname = 'none';
  }

print <<<_HTML_
  
  Start by either creating a new project, or editing an existing
  one. Once you have a unique project, then you need to creat a project
  profile. The profile is the list of all the loads you'll select,
  plus how much each item gets used. If you need it, there is also a
  NEC calculator for doing the raw calculations manually. This is
  useful for small projects where you already know the load data.<p> 

  <form name="projform">
  <label>Name
  <input type='text' id='projname' size='26' value="$projname" onchange="newProject('edit')">
  <label>Project ID
  <input type='text' id='projid' size='12' value="$projid" onchange="newProject('edit')">
  <input type='button' name='button' value="Edit Project"  onClick="newProject('edit')">
  <input type='button' name='button' value="New Project"   onClick="newProject('new')">

<p>
_HTML_;
  if ($godmode != 'off') {
print <<<_HTML_
  <input type='button' name='button' value="New Profile"    onClick="loadPage('profiles.php?op=new')">
  <input type='button' name='button' value="Wiring Details" onClick="loadPage('wiring.php')">
  <input type='button' name='button' value="NEC Calculator" onClick="loadPage('neccalc.php')">
_HTML_;
}
  //  <input type=button name=button value="NEC Calculator" onClick="javascript:window.location='neccalc.php';">
?>
  
  </form>
  <br><br><hr>
    <div id="result">
    </div>
    
    <br><br>
      <div id="status">
      </div>
  
<!--#include virtual="footer.html" -->
  
</body>
</html>
  