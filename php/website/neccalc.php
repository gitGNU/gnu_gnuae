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

   if (isset($_GET['conduct3'])) {
     $conduct3 = $_GET['conduct3'];
   } else {
     $conduct3 = 2;
   }

   if (isset($_GET['conduct2'])) {
     $conduct2 = $_GET['conduct2'];
   } else {
     $conduct2 = 2;
   }

// These are the possible paramters for the 3rd block of this page, the conduit
// calculations.
   if (isset($_GET['conduct3'])) {
     $conduct3 = $_GET['conduct3'];
   } else {
     $conduct3 = 2;
   }

   if (isset($_GET['awg3'])) {
     $awg3 = $_GET['awg3'];
   } else {
     $awg3 = '18';
   }

   if (isset($_GET['wire3'])) {
     $wire3 = $_GET['wire3'];
   } else {
     $wire3 = 'THWN2';
   }

   if (isset($_GET['nec_wires3'])) {
     $nec_wires3 = $_GET['nec_wires3'];
   } else {
     $nec_wires3 = 1;
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
  <div id=neccalc3>
_HTML_;
wireAWG('second', 'updateWiring');
wireNames('second', 'updateWiring');
conductors('second', 'updateWiring', $conduct2);
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

  You can only put so much conductors in a given piece of conduit, according to
  NEC, this should be less than half the conduit should be full. This is to avoid
  heat problems, and if you ever run additional wires later, you'll be glad
  to not use too-small conduit.<p>

  To use this calculator, just select type of conduit, the wire's AWG gauge,
  and the wire type. Then specify the number of wires of this type you'll be
  running in this conduit. As an example, any 120VAC circuit is going to have
  a minimum of 3 conductors; ground, neutral, and hot.<p>
_HTML_;
conduitNames('third', 'updateNEC');
echo "<p>";
for ($i=0; $i < $nec_wires3; $i++) {
  wireAWG("third_$i", 'updateNEC');
  wireNames("third_$i", 'updateNEC');
  conductors("third_$i", 'updateNEC', $conduct3);
  // conduitSize("third_$i", 'updateNEC');
  echo "<p>";
}
  print <<<_HTML_
  <input type=button name=calc3 value="More Wires" onClick=updateNEC('calc3')>
  <input type=button name=reset3 value="Reset Fields" onClick=updateNEC('reset3')>
  <input type=hidden name='nec_wires3' value="$nec_wires3">
  </div>
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
  