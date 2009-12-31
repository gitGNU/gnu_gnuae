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

   // Get the parameters

// The voltage of the battey bank
   if (isset($_GET['batteryvolts'])) {
       $batteryvolts = $_GET['batteryvolts'];
   } else {
       $batteryvolts = 24;
   }
// the voltage of the PV array
   if (isset($_GET['pvvolts'])) {
       $pvvolts = $_GET['pvvolts'];
   } else {
       $pvvolts = 48;
   }
// the voltage of the wind generator
   if (isset($_GET['windvolts'])) {
       $windvolts = $_GET['windvolts'];
   } else {
       $windvolts = 24;
   }
// Temperature scale, celcius or farenheit
   if (isset($_GET['tempscale'])) {
       $tempscale = $_GET['tempscale'];
   } else {
       $tempscale = "farenheit";
   }
// The lowest temperature to expect
   if (isset($_GET['lowtemp'])) {
       $lowtemp = $_GET['lowtemp'];
   } else {
       $lowtemp = -15;
   }
// The highest temperature to expect
   if (isset($_GET['hightemp'])) {
       $hightemp = $_GET['hightemp'];
   } else {
       $hightemp = 80;
   }

// Get the array of data for the module to module wire run
   if (isset($_GET['mod2mod'])) {
     $mod2mod = explode(",", $_GET['mod2mod']);
   } else {
     $mod2mod = array(0, 'THHN', 2, 18, 'Copper');
   }

// Get the array of data for the module to charge controller wire run
   if (isset($_GET['mod2charg'])) {
     $mod2charg = explode(",", $_GET['mod2charg']);
   } else {
     $mod2charg = array(0, 'THHN', 2, 18, 'Copper');
   }

// Get the array of data for the generator to charger wire run
   if (isset($_GET['gen2charg'])) {
     $gen2charg = explode(",", $_GET['gen2charg']);
   } else {
     $gen2charg = array(0, 'THHN', 2, 18, 'Copper');
   }

// Get the array of data for the module to charge controller wire run
   if (isset($_GET['batt2invert'])) {
     $batt2invert = explode(",", $_GET['batt2invert']);
   } else {
     $batt2invert = array(0, 'THHN', 2, 18, 'Copper');
   }
   if (isset($_GET['invert2bld'])) {
     $invert2bld = explode(",", $_GET['invert2bld']);
   } else {
     $invert2bld = array(0, 'THHN', 2, 18, 'Copper');
   }
   if (isset($_GET['charg2batt'])) {
     $charg2batt = explode(",", $_GET['charg2batt']);
   } else {
     $charg2batt = array(0, 'THHN', 2, 18, 'Copper');
   }

print <<<_HTML_

     This is a table of the wire runs between the major components of
     your power system. You have to specify the length between these
     components yourself. Then chose the type of wire you plan to use,
     the default is fine. The system will calculate the AWG of the wire
     you need, which you can change if you want to. Most systems only use
     copper wire, but you can switch to using aluminum wire for all the
     calculations.<p>
     
     Normally, just two conductors are used for DC systems, but often
     when dealing with voltagr loss and drop issues, the appropriate
     wire gauge may be larger than you want to deal with. In this case
     you can double the number of conductors to reduce the physical size
     of the wire. For example, you could run two pairs of 2AWG instead
     of one pair of 1AWG, which is hard to pull through conduit.<p>
     
     <hr>
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
   
echo "<br><label>Battery Bank Voltage: $batteryvolts";
echo "<br><label>PV Aray Voltage: $pvvolts";
echo "<br><label>Lowest Temperature: $lowtemp";
echo " $tempscale";
echo "<br><label>Highest Temperature: $hightemp";
echo " $tempscale";
echo "<br><label>Wind Generator Voltage: $windvolts<p>";

?>

      <br><br><hr>
	<div id="status">
	</div>
   
	<!--#include virtual="footer.html" -->
   
     </body>
</html>
    