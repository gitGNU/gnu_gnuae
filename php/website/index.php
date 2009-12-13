<html>
<head>
<meta name="author" content="Rob Savoye">
   <title>Solar Designs</title>
   
   <!-- php.default.min.js is from http://phpjs.org/. This is a collection
   of Javascript functions that mimic PHP functions. We primarily use
   these for passing complex data around.
   <script language="javascript" src="php.default.min.js"></script>
    -->
   <script language="javascript" src="gnuae.js"></script>

<script>
var rows1=[];
var rows2=[];

<?php

  // include '/usr/local/src/debug/auto_prepend.php';
  // xdebug_start_trace("/tmp/foo");

// These globals are for the initial project data
$projname = "Project Name";
$projid = "000000";
$projinfo = "Other information you want associated with this project profile.";
$projlat = 0;
$projlon = 0;

  // $bar = gui_list_names("loads");
  // $ii = count($bar) - 1;          // the first record is always a blank line.

$boo = gui_get_load_data("Laptop");
$ii = count($boo) - 1;
while ($ii) {
  ?>
  rows1[rows1.length]=<?php echo '"'.$boo[$ii].'"'?>;
  <?php
      $ii = $ii - 1;
  }
  ?>
</script>

   </head>
   
   <body background="../images/seneca3-bg.jpg">
   
   <h2 align=center>Solar Design</h2>
   
   <table border=0 width=85%>
   <tr><td valign=top width=15%>
   
   <center>
   <font size=-1.5>
   <a href="../index.html"><img border=0 src=../buttons/home-trans.gif></a><br>
   <a href="../contact.html"><img border=0 src=../buttons/contact-trans.gif></a><br>
   <a href="../lab.html"><img border=0 src=../buttons/lab-trans.gif></a><br>
   <a href="../software.html"><img border=0 src=../buttons/software-trans.gif></a><br>
   <a href="../projects.html"><img border=0 src=../buttons/projects-trans.gif></a><br>
   
   </td>
   <td>
   
   <?php

  // these two fields often have embedded spaces, which we can't pass
  // as arguments. So we convert these to underscrores to be safe as a
  // simple serialize/unserialize step.
  $tmpname=str_replace(' ', '_', $projname);
  $tmpinfo=str_replace(' ', '_', $projinfo);

  print <<<_HTML_
    <label>Project Name
    <input type=text id=projname size=26 value="$projname" onchange=updateProject() >
    <label>Project ID
    <input type=text id=projid size=12 value="$projid" onchange=updateProject() >
    <p>
    <textarea type=text id=projinfo cols=46 rows=4 onmouseout=updateProject()>
$projinfo
    </textarea>
    <p>
    <label>Latitude
    <input type=text id=latitude value=$projlat size=7 onchange=updateProject()>
    <label>Longitude
    <input type=text id=longitude  value=$projlon size=7 onchange=updateProject()>
  <form action=newLoad.php?projid=$projid&projname=$tmpname&projinfo=$tmpinfo&projlat=$projlat&projlon=$projlon method=post>
    <input type=submit value="Save Update" onsubmit=updateProject()>
  </form>
  <hr><p>
_HTML_;
  
/* // NEC Voltage Drop */
/* $foo = nec_volt_drop(2, 140, 48.1, 32.1, 67.8, 2); */
/* echo $foo . "<p>"; */

/* // NEC Voltage Loss */
/* $foo = nec_volt_loss(140, 2, 23.4, 56.7, 2); */
/* echo $foo . "<p>"; */

// Make a menu
echo "<h3>Select Loads</h3>";
echo "<div id=main>";
$foo = gui_list_names("loads");
sort ($foo);
$size=count($foo);
echo "<select id='load' onchange=newLoad() >";
for ($i = 0; $i < $size; $i++) {
  echo "<option value=>$foo[$i]</option>";
}
echo "</select>";
echo "</div>";

// xdebug_stop_trace();
// include '/usr/local/src/debug/auto_append.php';
?>

<br><br><hr>
<div id="result"></div>
  
  <br><br><hr>
  
  <div id="summary"></div>
  
  <br><br><br><hr>
  <div id="continue">
  Continue<p>  
  </div>
  
  </td>
  </tr>
  
  </table>
  
<!--#include virtual="../footer.html" -->
  
</body>
</html>
  