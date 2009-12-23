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
  
print <<<_HTML_

Start by either creating a new project, or editing an existing one.<p>
  <form name="projform" onSubmit="return newProject('write')">
  <label>Project Name
  <input type=text id=projname size=26 value="$projname" onchange=newProject('find') >
  <label>Project ID
  <input type=text id=projid size=12 value="$projid" onchange=newProject('find') >
  
  <input type=button name=button value="New Project" onClick=newProject('new')>
  <input type=button name=button value="Update Project" onClick=newProject('update')>
  <input type=button name=button value="New Profile" onClick=updateProfile('new')>
  </form>
_HTML_;

?>
  
  <br><br><hr>
  <div id="result">
  </div>
  
  <br><br><hr>
  <div id="status">
  </div>
  
<!--#include virtual="footer.html" -->
  
</body>
</html>
  