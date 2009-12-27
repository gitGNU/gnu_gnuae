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
//   echo '<input type=radio name=$typeid id=$typeid size=3 checked=yes value="copper" onchanged=updateWiring("$typeid")>Copper</input>';
//   echo '<input type=radio name=$typeid id=$typeid size=3 value="aluminum" onchanged=updateWiring("$typid")>Aluminum</input>';
   print <<<_HTML_
    <label>Type
    <select id=$typeid onChange=updateWiring("$typeid")>
    <option>Copper</option>
    <option>Aluminm</option>
    </select>
_HTML_;
}

function wireLength($id) {
  global $mod2mod, $charg2batt, $batt2invert, $invert2bld, $gen2charg, $mod2charg;

  // id contains the name of the element that just changed, so we have to
  // dereference it so we can get to the array value passed in as a
  // parameter.
  $newval = $$id;

  $newid = "wlen_$id";
  echo "</td><td><label>Length<input type=text size=3 id=$newid onChange=updateWiring('$newid') value=$newval[0] >";
}

  // Print all the wire types as a selection menu
function wireNames($id) {

  global $mod2mod, $charg2batt, $batt2invert, $invert2bld, $gen2charg, $mod2charg;

  // id contains the name of the element that just changed, so we have to
  // dereference it so we can get to the array value passed in as a
  // parameter. That value we then use as another variable name, one for
  // each option. This gets set to be selected when eval'd.
  $newval = $$id;
  $select = $newval[1];
  $foo = "on_$select";
  eval("$$foo = 'SELECTED';");

  $newid = "wname_$id";
  print <<<_HTML_
     <select id=$newid onChange=updateWiring("$newid")>
     <option $on_RHH>RHH</option>
     <option $on_RHW>RHW</option>
     <option $on_RHW2>RHW2</option>
     <option $on_THHN>THHN</option>
     <option $on_THHW>THHW</option>
     <option $on_THW>THW</option>
     <option $on_THW2>THW2</option>
     <option $on_THWN>THWN</option>
     <option $on_THWN2>THWN2</option>
     <option $on_XHHW>XHHW</option>
     <option $on_XHHW2>XHHW2</option>
     <option $on_SE>SE</option>
     <option Son_USE>USE</option>
     <option $on_USE2>USE2</option>
     <option $on_TW>TW</option>
     <option $on_UF>UF</option>
     <option $on_TRS>TBS</option>
     <option $on_SA>SA</option>
     <option $on_SIS>SIS</option>
     <option $on_FEP>FEP</option>
     <option $on_FEPB>FEPB</option>
     <option $on_MI>MI</option>
     <option $on_XHH>XHH</option>
     <option $on_ZW2>ZW2</option>
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
function conductors($id)
{
  $newid = "conduct_$id";
  print <<<_HTML_
    <label>Conducters
    <select id=$newid onChange=updateWiring("$newid")>
    <option>2</option>
    <option>4</option>
    <option>6</option>
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
   wireLength($id);
   echo "</td><td>";
   wireNames($id);
   echo "</td><td>";
   conductors($id);
   echo "</td><td>";
   awg($id);
   echo "</td><td>";
   wireMetal($id);
   echo "</td><td></tr><tr>";
}


?>