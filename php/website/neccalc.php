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
   
   <body background="../images/seneca3-bg.jpg">
   
   <h2 align=center>Solar Design - NEC Calculator</h2>
   
<?php
   
   gui_init_db("gnuaetest");

   print <<<_HTML_
   
   Start by either creating a new project, or editing an existing one.<p>
   <form name="necform" onSubmit="return updateNEC('fixme')">
   <label>Watts
   <input type=text id=watts size=4 value="0" onchange=updateNEC('watts')>
   <label>Volts
   <input type=text id=volts size=3 value="0" onchange=updateNEC('volts')>
   <label>Amps
   <input type=text id=amps  size=3 value="0" onchange=updateNEC('amps')>
   <input type=button name=button value="Reset Fields" onClick=updateNEC('reset')>
   <p>
   <label>Voltage Loss
   <input type=text id=loss  size=3 value="0" onchange=updateNEC('loss')>
   <label>Voltage Drop
   <input type=text id=drop  size=3 value="0" onchange=updateNEC('drop')>
   <label>Tempeature
   <input type=text id=temp  size=3 value="0" onchange=updateNEC('temp')>
   <input type=button name=button value="Calculate AWG" onClick=updateNEC('calc')>
   <p>
   <select id=wiretype onChange=updateNEC('wiretype')>
     <option>RHH</option>
     <option>RHH</option>
     <option>RHW</option>
     <option>RHW2</option>
     <option>THHN</option>
     <option>THHW</option>
     <option>THW</option>
     <option>THW2</option>
     <option>THWN</option>
     <option>THWN2</option>
     <option>XHHW</option>
     <option>XHHW2</option>
     <option>SE</option>
     <option>USE</option>
     <option>USE2</option>
     <option>TW</option>
     <option>UF</option>
     <option>TBS</option>
     <option>SA</option>
     <option>SIS</option>
     <option>FEP</option>
     <option>FEPB</option>
     <option>MI</option>
     <option>XHH</option>
     <option>ZW2</option>
   </select>
     <label>Diameter
     <select id=conddia onChange=updateNEC('conddia')>
     <option>1/2"</option>
     <option>2/3"</option>
     <option>1"</option>
     <option>1 1/4"</option>
     <option>1 1/2"</option>
     <option>1 3/4"</option>
     <option>2"</option>
     <option>2 1/4"</option>
     <option>2 1/2"</option>
     <option>2 3/4"</option>
     </select>
   <input type=radio name=wtype  size=3 value="coppe" checked=$wtype onchange=updateNEC('type')>Copper</input>
   <input type=radio name=wtype  size=3 value="aluminum" checked=$wtype onchange=updateNEC('type')>Aluminum</input>
   <p>
     <label>AWG
   <select id=awg onChange=updateNEC('awg')>
     <option>18</option>
     <option>16</option>
     <option>14</option>
     <option>12</option>
     <option>10</option>
     <option>8</option>
     <option>6</option>
     <option>4</option>
     <option>3</option>
     <option>1</option>
     <option>1/0</option>
     <option>2/0</option>
     <option>3/0</option>
     <option>4/0</option>
     <option>250</option>
     <option>300</option>
     <option>350</option>
     <option>400</option>
     <option>500</option>
     <option>1000</option>
     <option>1250</option>
     <option>1750</option>
     <option>2000</option>
     </select>
     <label>Conduit Type
   <select id=conduittype onChange=updateNEC('conduit')>
     <option>EMT</option>
     <option>ENT</option>
     <option>FMC</option>
     <option>IMC</option>
     <option>LFNC_B</option>
     <option>LFNC_A</option>
     <option>LFMC</option>
     <option>RMC</option>
     <option>RNC</option>
     <option>PVC_80</option>
     <option>PVC_40</option>
     <option>PVC_A</option>
     <option>PVC_EB</option>
   </select>
     <p>
     <label>Conductors
     <select id=conductors onChange=updateNEC('conductors')>
     <option>2</option>
     <option>3</option>
     <option>4</option>
     <option>5</option>
     <option>6</option>
     <option>7</option>
     <option>8</option>
     <option>9</option>
     <option>10</option>
     <option>12</option>
     </select>
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
  