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

  //phpinfo();

$id = $_GET['loadid'];
$name = $_GET['loadname'];
$data = gui_get_load_data($name);
gui_add_item($name, $name, $id, 2, 3, 4);

$item = gui_list_items();
sort($item);
$size = count($item) - 1;
echo "Got ", $size, " items in the list";
var_dump($item);

for ($i = 0; $i < $size; $i++) {
  $data = gui_get_load_data($name);
  print <<<_HTML_
    <form>
    <b>$data[1]</b> weekly usage:
      <label>Hours
      <input type=text id=$data[0]_hours   size=2 value=$data[3] onchange=SayHello()>
      <label>Days
      <input type=text id=$data[0]_days    size=2 value=$data[4] onchange=SayHello()>
      <label>Minutes
      <input type=text id=$data[0]_minutes size=2 value=$data[5] onchange=SayHello()>
      </form>
_HTML_;
}

echo "<h2>$id</h2>";
echo "<h2>$name</h2>";

?>
