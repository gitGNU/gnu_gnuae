<!--
// 
//   Copyright (C) 2009, 2010 Free Software Foundation, Inc.
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
   <title>Solar Design - Projects</title>
   <script language="javascript" src="gnuae.js"></script>
</head>
<body background="../images/seneca3-bg.jpg">   
<?php

//phpinfo();
   if (isset($_GET['projid'])) {       
     $projid = $_GET['projid'];
   } else {
     $projid = 0;
   }

  if (isset($_GET['projname'])) {       
    $projname = $_GET['projname'];
    //$projinfo = $_GET['projinfo'];
  } else {
    $projname = 'none';
  }

  if (isset($_GET['op'])) {       
    $op = $_GET['op'];
  } else {
    $op ='new';
  }

  if (isset($_GET['sunhours'])) {
    $sunhours = $_GET['sunhours'];
  } else {
    $sunhours = 0;
  }

  if (isset($_GET['windhours'])) {
    $windhours = $_GET['windhours'];
  } else {
    $windhours = 0;
  }

  if (isset($_GET['speed '])) {
    $speed = $_GET['speed '];
  } else {
    $speed = 0;
  }

  if (isset($_GET['location'])) {
    $location = $_GET['location'];
  } else {
    $location = "";
  }

  if (isset($_GET['latitude'])) {
    $latitude = $_GET['latitude'];
  } else {
    $latitude = 0;
  }

  if (isset($_GET['longitude'])) {
    $longitude = $_GET['longitude'];
  } else {
    $longitude = 0;
  }

function projedit($op) {
   global $projid, $projname, $projinfo, $latitude, $longitude;
   global $sunhours, $windhours, $speed, $location;
   
   print <<<_HTML_
   <label>Project Name
   <input type='text' id='editprojname' size='26' value="$projname" onchange="updateProject('write')">
   <label>Project ID
   <input type='text' id='editprojid' size='7' value="$projid" readonly="readonly">
   <br>
   <label>Hours of Sun
    <input type='text' id='sunhours' size='7' value="$sunhours" onchange="updateProject('write')">
   <label>Hours of Wind
    <input type='text' id='windhours' size='7' value="$windhours" onchange="updateProject('write')">
   <label>Wind Speed
    <input type='text' id='speed' size='7' value="$speed" onchange="updateProject('write')">
   <br>
    <label>Latitude
    <input type='text' id='latitude' size='7' value="$latitude" onchange="updateProject('write')">
    <label>Longitude
    <input type='text' id='longitude' size='7' value="$longitude" onchange="updateProject('write')">
   <p>
   <label>Project Description
   <br>
<!--    <textarea type='text' id='projinfo' cols='46' rows='4' onmouseout="updateProject()"> -->
    <textarea type='text' id='projinfo' cols='46' rows='4' onchange="updateProject()">
   $projinfo
    </textarea>
    <p>
   <form action=project.php?projid=$projid&projname=$projname&projinfo=$projinfo&latitude=$latitude&longitude=$longitude&sunhours=$sunhours&windhours=$windhours&speed=$speed&location=$location&op=write method=post>
   <input type='button' name='updateproject' value="Update Project" onClick="return updateProject('done')">
   <input type='button' name='updateproject' value="Done, add loads" onClick="return updateProject('done')">     
  </form>
_HTML_;
   // if (isset($_SERVER['QUERY_STRING'])) {
   //   $foo = $_SERVER['QUERY_STRING'];
   //   echo "<br>Query string is: $foo <br>";
   // } else {
   //   echo "<br>No Query string <br>";
   // }
}
   

// if ($projid == 0) {
  gui_init_db("gnuaetest");
//}

// Look to see if this project already exists in the database. If it
// does, then we just update the record. If it doesn't, then we create
// a new record.
if ($op == 'edit') {
  $proj = gui_get_project($projid, $projname);
  //var_dump($proj);
  if (count($proj)) {
    $projname = $proj[0];
    $projinfo = $proj[1];
    $sunhours = $proj[2];
    $windhours = $proj[3];
    $speed = $proj[4];
    $location = $proj[5];
    $latitude = $proj[6];
    $longitude = $proj[7];
    echo "<h3>Updating an existing project #$projid</h3>";
    projedit($op);
  } else {
    $op = "new";
  }
}

if ($op == "new") {
  // Create a new project
  echo "<h3>Creating a new project</h3>";
  $projid = gui_new_project($projname, "", 0.0, 0.0, 0.0, "none", 0.0, 0.0);
  $projinfo = "";
  $sunhours = 0.0;
  $windhours = 0.0;
  $speed = 0.0;
  $location = "";
  $latitude = 0.0;
  $longitude = 0.0;
  projedit($op);
} else if ($op == "write") {
  // Update an existing project
  echo "<h3>Writing project: $projname</h3>";
  gui_update_project($projid, $projname, $projinfo, $sunhours, $windhours, $speed, $location, $latitude, $longitude);
  //  echo "$projname updated..."; 
  projedit($op);
}

?>

<!--#include virtual="footer.html" -->
  
</body>
</html>

