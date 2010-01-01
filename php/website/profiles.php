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
   <title>Solar Design - Profiles</title>
   <script language="javascript" src="gnuae.js"></script>
</head>
<body background="../images/seneca3-bg.jpg">
<?php
   
// Print the standard header with the selection menu for loads
function profhead($op) {
   global $projid, $projname, $loadname, $godmode;
  
//     <div id=result>
   print <<<_HTML_
     <label>Project Name
     <input type='text' id='projname' size='26' value="$projname" readonly="readonly">
     <label>Project ID
     <input type='text' id='projid' size='7' value="$projid" readonly="readonly">
   <input type='hidden' name='profitems' value='0'>
_HTML_;
   echo "<h3>Select Loads</h3>";

   // Make a menu of all the loads
   $foo = gui_list_names("loads");
   sort ($foo);
   $size=count($foo);
   echo "<form name='necform' action='profiles.php?godmode=$godmode&projid=$projid&op=fixme'>";
   //   echo "<select id='load' onchange=updateProfile('update') >";
   echo "<select id='load' onchange=updateProfile('update') >";
   for ($i = 0; $i < $size; $i++) {
     if ($foo[$i] == $loadname) {
       $enabled = "SELECTED";
     } else {
       $enabled = "";
     }
     echo "<option $enabled>$foo[$i]</option>";
   }
   echo "<p>";
  echo "<div id='result'>";
}

// Print the body with the table of data
function profedit($op) {
  global $projid, $projname;
  global $totalwatts, $totalamps;
  global $godmode;		// turn on extra options
  $days = 0;
  $hours = 0;
  $minutes = 0;
  
  $items = gui_list_items($projid);
  $size = count($items);
  var_dump($items);
  // <form method=post action=profiles.php?godmode=$godmode&projid=$projid&projname=$projname&op=write&days=$days&hours=$hours&minutes=$minutes&id=$id>
  print <<<_HTML_
    <form name="profform" onSubmit="return updateProfile('write','barfoo')">
    <caption>These are the selected loads you have chosen</caption>
    <table border=0>
    <tr><th>Name</th>
    <th>Days</th>
    <th>Hours</th>
    <th>Minutes</th>
    <th>Item ID</th>
    <th>Voltage</th>
    <th>Wattage</th>
    <th>Amperage</th>
    <td></tr><tr>
_HTML_;

  //echo "<script language='javascript'>alert('FIXME: ' + $size)</script>"; 
  // Reset the totals
  $totalwatts = 0;
  $totalamps  = 0;
  
  for ($i = 0; $i < $size; $i++) {
    $data = $items[$i];
    $load = gui_get_data(0, $data[0], "loads");
    $lsize = count($load);
    
    $totalwatts += $load[5];
    $totalamps  +=  $load[5];
    $did = "item[$i]_days";
    $hid = "item[$i]_hours";
    $mid = "item[$i]_minutes";
    print <<<_HTML_
      <tr><td>
      <label><b>$data[0]</b></label>
      </td>
      <td><input type='text' id="$did" size='2' value="$data[3]" onchange="updateProfile('write', $did)">
      <td><input type='text' id="$hid" size='2' value="$data[4]" onchange="updateProfile('write', $did)">
      <td><input type='text' id="$mid" size='2' value="$data[5]" onchange="updateProfile('write', $did])">
      <td><input type='text' size='6' value="$data[3]" readonly="readonly">
      <td><input type='text' size='6' value="$load[4]" readonly="readonly">
      <td><input type='text' size='6' value="$load[5]" readonly="readonly">
      <td><input type='text' size='6' value="$load[6]" readonly="readonly">
      </td></tr>
_HTML_;
  } // end of for loop
  
  print <<<_HTML_
    <tr><td></td><td><b>Totals</b></td><td></td><td></td><td>$size items</td><td></td><td>$totalwatts</td><td>$totalamps</td></tr>;
  </table>
      <!--
      <p><br>
      <input type='submit' id="up" value="Update Values" onSubmit="return updateProfile('write','foobar')">
      -->
  </form>
_HTML_;
  if ($godmode != 'off') {
    print <<<_HTML_
      <p>
      <input type='button' name='button' value="Force Refresh" onClick="loadPage('profiles.php?op=$op&projid=$projid&projname=$projname&godmode=$godmode')">
_HTML_;
  }
  // $bar = "<script language='javascript'>updateProfile('fixme')</script>";
  // echo "$bar";
  echo "</form></select>";
  echo "<br><div id='status'></div>"; 
}

 // Store the calculated totals for display   
$totalwatts = 0;
$totalamps = 0;

// Get parameters from the command line
if (isset($_GET['op'])) {
  $op = $_GET['op'];
} else {
  $op = 'new';
}

if (isset($_GET['godmode'])) {
  $godmode = $_GET['godmode'];
} else {
  $godmode = "off";
}

if (isset($_GET['projid'])) {
  $projid = $_GET['projid'];
} else {
  $projid = 0;
}

if (isset($_GET['projname'])) {
  $projname = str_replace(' ', '_', $_GET['projname']);
} else {
  $projname = 'none';
}

if (isset($_GET['loadname'])) {
  $loadname = str_replace(' ', '_', $_GET['loadname']);
} else {
  $loadname = 'none';
}

if (isset($_GET['type'])) {
  $type = $_GET['type'];
} else {
  $type = 0;
}

if (isset($_GET['id'])) {
  $id = $_GET['id'];
} else {
  $id = 0;
}

if (isset($_GET['quantity'])) {
  $quantity = $_GET['quantity'];
} else {
  $quantity = 0;
}

if (isset($_GET['hours'])) {
  $hours    = $_GET['hours'];
} else {
  $hours = 0;
}

if (isset($_GET['minutes'])) {
  $minutes = $_GET['minutes'];
} else {
  $minutes = 0;
}

if (isset($_GET['days'])) {
  $days = $_GET['days'];
} else {
  $days = 0;
}

if (isset($_GET['location'])) {
  $location = $_GET['location'];
} else {
  $location = 0;
}

gui_init_db("gnuaetest");

// We do this so we can run this file with the command line php,
// which only uses argv, instead of QUERY_STRING. It also does
// have any of the $_GET[] variables either, so this becomes the
// only way to run this standalone.
if (isset($_SERVER["QUERY_STRING"])) {
  $query = $_SERVER["QUERY_STRING"];
} else if (isset($_SERVER["argv"])) {
  $argv = $_SERVER["argv"];
  $query = $argv[1];
}

$tok = strtok($query, '&');
while ($tok !== false) {
  $tmp = "$$tok";
  eval("$tmp;");
  $tok = strtok("&");
}

// Look to see if this project already exists in the database. If it
// does, then we just update the record. If it doesn't, then we create
// a new record.
if ($op != "write") {
  $prof = gui_get_data($projid, $loadname, "loads");
  if (count($prof)) {
    $projid   = $prof[0];
    $projname = $prof[1];
    $profinfo = $prof[2];
    $type     = "LOAD";
    $quantity = $prof[4];
    $hours    = $prof[5];
    $minutes  = $prof[6];
    $days     = $prof[7];
    $op = "update";
  } else {
    $op = "new";
  }
}

// phpinfo();

if ($op == 'new') {
  echo "<script language='javascript'>godmode='$godmode'</script>";
  echo "<script language='javascript'>items='1''</script>";
  echo "<script language='javascript'>projid='$projid'</script>";
  echo "<script language='javascript'>projname='$projname'</script>";
  profhead($op);
  profedit($op);
} else if ($op == 'update') {
  // Update an existing profiles
  echo "<script language='javascript'>items += 1'</script>";
  echo "<h3>Updating an existing profile</h3>";
  //  gui_add_item($projid, $loadname, "", $type, $id, $hours, $minutes, $days);
  profhead($op);
  profedit($op);
} else if ($op == "edit") {
  //echo "<script language='javascript'>alert('FIXME: ' + projid + projname)</script>"; 
  // Update an existing project
  echo "<h3>Finding an existing profile</h3>";
  profhead($op);
  profedit($op);
} else if ($op == "write") {
  //echo "<script language='javascript'>alert('FIXME: ' + projid + projname)</script>"; 
  // Update an existing project
  profhead($op);                // we have no entries, just print the header
  echo "<h3>Writing project</h3>";
  gui_update_item($projid, $loadname, "", $type, $id, $hours, $minutes, $days);
  profedit($op);
}

// if (isset($_SERVER['QUERY_STRING'])) {
//   $foo = $_SERVER['QUERY_STRING'];
//   echo "<br>Query string is: $foo <br>";
// }

?>

  </div>

<!--#include virtual="footer.html" -->
  
</body>
</html>

