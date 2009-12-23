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
   <title>Solar Design - Projects</title>
   
<?php


//
function projedit($op) {
   global $projid, $projname, $projinfo, $projlat, $projlon;
   global $projsunhours, $projwindhours, $projspeed, $projlocation;
   
   print <<<_HTML_
   <label>Project Name
   <input type=text id=projname size=26 value="$projname" onchange=updateProject()>
   <label>Project ID
   <input type=text id=projid size=7 value="$projid" readonly="readonly">
   <br>
   <label>Hours of Sun
    <input type=text id=sunhours size=7 value="$projsunhours" onchange=updateProject()>
   <label>Hours of Wind
    <input type=text id=windhours size=7 value="$projwindhours" onchange=updateProject()>
   <label>Wind Speed
    <input type=text id=speed size=7 value="$projspeed" onchange=updateProject()>
   <br>
    <label>Latitude
    <input type=text id=latitude size=7 value="$projlat" onchange=updateProject()>
    <label>Longitude
    <input type=text id=longitude size=7 value="$projlon" onchange=updateProject()>
   <p>
   <label>Project Description
   <br>
<!--    <textarea type=text id=projinfo cols=46 rows=4 onmouseout=updateProject()> -->
    <textarea type=text id=projinfo cols=46 rows=4 onchange=updateProject()>
   $projinfo
    </textarea>
    <p>
   <form action=project.php?projid=$projid&projname=$tmpname&projinfo=$tmpinfo&latitude=$projlat&longitude=$projlon&sunhours=$projsunhours&windhours=$projwindhours&speed=$speed&location=$projlocation&op=write method=post>
   <!--
   <form onSubmit="return updateProject()">
   -->
   <input type=submit value="Save Update" onsubmit=updateProject()>
   <input type=button name=button value="Update Project" onClick=newProject('write')>
  </form>
_HTML_;
   $foo = $_SERVER['QUERY_STRING'];
   echo "<br>Query string is: $foo <br>";
}
   
//phpinfo();
$projid = $_GET['projid'];
$projname = $_GET['projname'];
//$projinfo = $_GET['projinfo'];
$op = $_GET['op'];

if ($projid == 0) {
  gui_init_db("gnuaetest");
}

// Look to see if this project already exists in the database. If it
// does, then we just update the record. If it doesn't, then we create
// a new record.
if ($op != "write") {
  $proj = gui_get_project($projid, $projname);
  if (count($proj)) {
    $projname = $proj[0];
    $projinfo = $proj[1];
    $projsunhours = $proj[2];
    $projwindhours = $proj[3];
    $projspeed = $proj[4];
    $projlocation = $proj[5];
    $projlat = $proj[6];
    $projlon = $proj[7];
    $op = "update";
  } else {
    $op = "new";
  }
}

if ($op == "new") {
  // Create a new project
  echo "<h3>Creating a new project</h3>";
  $projid = gui_new_project($projname, "", 0.0, 0.0, 0.0, "none", 0.0, 0.0);
  $projname = "unnamed project";
  $projinfo = "";
  $projsunhours = 0.0;
  $projwindhours = 0.0;
  $projspeed = 0.0;
  $projlocation = "";
  $projlat = 0.0;
  $projlon = 0.0;
  projedit($op);
} else if ($op == "update") {
  // Update an existing project
  echo "<h3>Updating an existing project</h3>";
  projedit($op);
} else if ($op == "find") {
  // Update an existing project
  echo "<h3>Finding an existing project</h3>";
} else if ($op == "write") {
  // phpinfo();
  
  // Update an existing project
  echo "<h3>Writing project</h3>";
  // these two fields often have embedded spaces, which we can't pass
  // as arguments. So we convert these to underscrores to be safe as a
  // simple serialize/unserialize step.
  $tmpname=str_replace(' ', '_', $projname);
  $tmpinfo=str_replace(' ', '_', $projinfo);

  $projlat = $_GET['latitude'];
  $projlon = $_GET['longitude'];
  $projsunhours = $_GET['sunhours'];
  $projwindhours = $_GET['windhours'];
  $projspeed =  $_GET['speed'];
  $projlocation =  $_GET['location'];
  gui_update_project($projid, $projname, $projinfo, $projsunhours, $projwindhours, $projspeed, $projlocation, $projlatitude, $projlongitude);
  echo "$projname updated..."; 
}

?>

<!--#include virtual="footer.html" -->
  
</body>
</html>

