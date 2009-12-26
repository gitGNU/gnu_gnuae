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

<?php

function wireMetal($id) {

  $typeid = "wtype_$id";
  echo '<input type=radio name=$typeid id=$typeid size=3 checked=yes value="copper" onchanged=updateWiring("$typeid")>Copper</input>';
  echo '<input type=radio name=$typeid id=$typeid size=3 value="aluminum" onchanged=updateWiring("$typid")>Aluminum</input>';
}

function wireLength($id) {

  $newid = "wlen_$id";
  echo "</td><td><label>Length<input type=text size=3 value=0 id=$newid onChange=updateWiring('$newid')>";
}

  // Print all the wire types as a selection menu
function wireNames($id) {

  $newid = "wname_$id";
  $typeid = "wtype_$id";
   print <<<_HTML_
     <select id=$newid onChange=updateWiring("$newid")>
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
_HTML_;

}

// Print all the wire sizes as a selection menu
function awg($id)
{
  $newid = "awg_$id";
  print <<<_HTML_
    <label>AWG
    <select id=$newid onChange=updateWiring("$newid")>
     <option>18</op tion>
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
_HTML_;
}

  // Print all the conduit sizes as a selection menu
function conduitSize($id)
{
  $newid = "cdia_$id";
  print <<<_HTML_
    <label>Diameter
    <select id=$newid onChange=updateWiring("$newid")>
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
_HTML_;
}

// Thus prints one line of the table of wire details
function wireDetails($id) {
   wireNames($id);
   echo "</td><td>";
   awg($id);
   wireLength($id);
   wireMetal($id);
   echo "</td><td></tr><tr>";
}


?>