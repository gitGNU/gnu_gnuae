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
   <title>Solar Design - NEC Calculator</title>
   <script language="javascript" src="gnuae.js"></script>   
</head>
   
   <div id="result">
   <body background="../images/seneca3-bg.jpg">   

   <h2 align=center>Solar Design - NEC Calculator</h2>
   
<?php
   
   //gui_init_db("gnuaetest");
   include "support.php";

   if (isset($_GET['volts'])) {
     $volts = $_GET['volts'];
   } else {
     $volts = 0;
   }
   if (isset($_GET['watts'])) {
     $watts = $_GET['watts'];
   } else {
     $watts = 0;
   }
   if (isset($_GET['amps'])) {
     $amps = $_GET['amps'];
   } else {
     $amps = 0;
   }

   if (isset($_GET['loss'])) {
     $loss = $_GET['loss'];
   } else {
     $loss = 0;
   }

   if (isset($_GET['drop'])) {
     $drop = $_GET['drop'];
   } else {
     $drop = 0;
   }

   if (isset($_GET['temp'])) {
     $temp = $_GET['temp'];
   } else {
     $temp = 0;
   }

   if (isset($_GET['distance'])) {
     $distance = $_GET['distance'];
   } else {
     $distance = 0;
   }

   if (isset($_GET['lossamps'])) {
     $lossamps = $_GET['lossamps'];
   } else {
     $lossamps = 0;
   }

   if (isset($_GET['lossvolts'])) {
     $lossvolts = $_GET['lossvolts'];
   } else {
     $lossvolts = 0;
   }

// Make the calculation for watts, volts, or amps using two of the three values
   if ($watts && $volts) {
     $amps = nec_amps($watts, $volts);
   } else if ($watts && $amps) {
     $volts = nec_volts($watts, $amps);
   } else if ($amps && $volts) {
     $watts = nec_watts($volts, $amps);
   }

// Make the calculations for voltage loss and drop
   $loss = nec_volt_loss($distance, $awg, $lossamps, $temp, $conductors);
   $drop = nec_volt_drop($awg, $distance, $lossvolts, $lossamps, $temp, $conductors);

print <<<_HTML_

  This is a series of calculators that can be used when brain storming, that
  don't effect anything else in for this project. This is also useful for small
   projects, where you know the data for loads, etc... and don't mind entering
  it manually.<p>
  
  To use this calculator, set two of the three fields, the third field
  becomes the solution.<p>
  
  <!-- <form name="necform" action=neccalc.php?watts=$watts&amps=$amps&volts=$volts&loss=$loss&drop=$drop> -->
  <form name="necform" onSubmit="return updateNEC('calc')">
  <label>Watts
  <input type=text id=watts size=4 value=$watts onchange=updateNEC('watts')>
  <label>Volts
  <input type=text id=volts size=3 value=$volts onchange=updateNEC('volts')>
  <label>Amps
  <input type=text id=amps  size=3 value=$amps onchange=updateNEC('amps')>
  <input type=button name=button value="Reset Fields" onClick=updateNEC('reset1')>
  <input type=button name=button value="Calculate" onClick=updateNEC('calc1')>
  <p>
  <hr>

  Here you can calculate the Voltage loss and voltage drop for a given length of
  wires. If you don't know the wire type, just use the default of 'THWN2'. Conductors
  is how many wires are actually carrying current. Amps is usually the maximum, for
  example if you have a 60Amp charge controller, then that's the amperage you want to
  use. Voltage is the maximum voltage expected, for example the input voltage of
  48 volts used by some charge controllers.<p>
     
  <label>Amps
  <input type=text id=lossamps  size=3 value=$lossamps onchange=updateNEC('lossamps')>
  <label>Volts
  <input type=text id=lossvolts  size=3 value=$lossvolts onchange=updateNEC('lossvolts')>
  <label>Distance
  <input type=text id=distance  size=3 value=$distance onchange=updateNEC('distance')>
_HTML_;
wireAWG('fooby', 'updateWiring');
wireNames('fooby', 'updateWiring');
conductors('fooby', 'updateWiring');
print <<<_HTML_
<p>
<label>Voltage Loss
<input type=text id=loss  size=3 value=$loss onchange=updateNEC('loss')>
  <label>Voltage Drop
  <input type=text id=drop  size=3 value=$drop onchange=updateNEC('drop')>
  <label>Temperature
  <input type=text id=temp  size=3 value=$temp onchange=updateNEC('temp')>
  <input type=button name=button value="Reset Fields" onClick=updateNEC('reset2')>
  <input type=button name=button value="Calculate" onClick=updateNEC('calc2')>
  <p><hr>
  <p>
_HTML_;
wireAWG('awg', 'updateNEC');
conduitSize('cond', 'updateNEC');
conduitNames('cond', 'updateNEC');
wireNames('cond', 'updateNEC');
conductors('cond', 'updateNEC');
print <<<_HTML_
   </form>
_HTML_;

?>

   <br><br><hr>
   <div id="status">
   </div>
   
   </div>
   <!--#include virtual="footer.html" -->
   
   </body>
</html>
  