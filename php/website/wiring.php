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
   <title>Solar Design - Wiring Details</title>
   <script language="javascript" src="gnuae.js"></script>   
</head>
   
   <body background="../images/seneca3-bg.jpg">
   
   <h2 align=center>Solar Design - Wiring Details</h2>
   
<?php
   
   gui_init_db("gnuaetest");
   include "support.php";

   $id="mod2mod";
   print <<<_HTML_
   <table>
   <tr><td>
   <form name=$id onSubmit="return updateWirig($id)">
_HTML_;
   echo "<label>Modules to charger</td><td>";
   wireTypes('type1');
   echo "</td><td>";
   awg('type2');
   echo "</td><td><label>Length<input type=text size=3 value=0 onChange=updateWiring($id)>";
   echo "</td><td></tr><tr>";

   echo "</td><td><label>Charger to Batteries</td><td>";
   wireTypes('type1');
   echo "</td><td>";
   awg('type2');
   echo "</td><td><label>Length<input type=text size=3 value=0 onChange=updateWiring($id)>";
   echo "</td><td></tr><tr>";

   echo "</td><td><label>Batteries to Inverter</td><td>";
   wireTypes('type1');
   echo "</td><td>";
   awg('type2');
   echo "</td><td><label>Length<input type=text size=3 value=0 onChange=updateWiring($id)>";
   echo "</td><td></tr><tr>";

   echo "</td><td><label>Inverter to Building</td><td>";
   wireTypes('type1');
   echo "</td><td>";
   awg('type2');
   echo "</td><td><label>Length<input type=text size=3 value=0 onChange=updateWiring($id)>";
   echo "</td><td></tr><tr>";

   echo "</td><td><label>Wind Generator to charger</td><td>";
   wireTypes('type1');
   echo "</td><td>";
   awg('type2');
   echo "</td><td><label>Length<input type=text size=3 value=0 onChange=updateWiring($id)>";
   echo "</td><td></tr><tr>";

   echo "</td><td><label>Module to Module</td><td>";
   wireTypes('type1');
   echo "</td><td>";
   awg('type2');
   echo "</td><td><label>Length<input type=text size=3 value=0 onChange=updateWiring($id)>";
   echo "</td><td></tr><tr>";

   echo "</form></table>";

?>

   <br><br><hr>
   <div id="status">
   </div>
   
   <!--#include virtual="footer.html" -->
   
   </body>
</html>
  