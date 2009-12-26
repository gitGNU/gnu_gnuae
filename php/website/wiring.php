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
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

//
// This file populates a table of the main wire runs between components.
// It uses the calculated peak load to suggest the minimum wire gauge,
// based on the length of the wire run, and other criteria like voltage
// drop or voltage loss.

// You have to have chosen an inverter, charge controller, and modules
// for the calculations to be correct, as that data is used for
// the voltages.
//
-->

<html>
<head>
<meta name="author" content="Rob Savoye">
   <title>Solar Design - Wiring Details</title>
   <script language="javascript" src="gnuae.js"></script>   
</head>
   
   <body background="../images/seneca3-bg.jpg">
   
   <h2 align=center>Solar Design - Wiring Details</h2>
   
<?php
   
   //   gui_init_db("gnuaetest");
   include "support.php";

   print <<<_HTML_
   <table>
   <tr><td>
   <form name=$id onChange="return updateWiring('fixme')">
_HTML_;

   echo "<label>Modules to charger</td><td>";
   wireDetails('mod2charg');
    
// Charger to Batteries wire details
   echo "</td><td><label>Charger to Batteries</td><td>";
   wireDetails('charg2batt');

   echo "</td><td><label>Batteries to Inverter</td><td>";
   wireDetails('batt2invert');

   echo "</td><td><label>Inverter to Building</td><td>";
   wireDetails('invert2bld');

   echo "</td><td><label>Wind Generator to charger</td><td>";
   wireDetails('gen2charg');

   echo "</td><td><label>Modules to Module</td><td>";
   wireDetails('mod2mod');
   echo "</form></table>";

?>

   <br><br><hr>
   <div id="status">
   </div>
   
   <!--#include virtual="footer.html" -->
   
   </body>
</html>
  