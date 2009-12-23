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

//XMLhttp variable will hold the XMLHttpRequest object
var xmlhttp = false;
var rows=[];

// This array hold the data for all the selected items
var allloads=[];

// If the user is using Mozilla/Firefox/Safari/etc
if (window.XMLHttpRequest) {
  //Intiate the object
  xmlhttp = new XMLHttpRequest();
  //Set the mime type
  xmlhttp.overrideMimeType('text/xml');
}
// If the user is using IE
else if (window.ActiveXObject) {
  //Intiate the object
  xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
}

// This updates the information for this project from the web page.
function updateProfile(op, name)
{
  var theID = document.getElementById('projid').value;
  var theName = document.getElementById('projname').value;
  var theLoad = document.getElementById("load").options[document.getElementById("load").selectedIndex].text;
  
  
  //This sets a variable with the URL (and query strings) to our PHP script
  var url = 'profiles.php?projid=' + theID;
  url += '&projname=' + theName;
  url += '&op=' + op;
  if (op == 'update') {
    url += '&loadname=' + theLoad;
    // url += '&projinfo=' + document.getElementById('projinfo').value;
    // url += '&days=' + document.getElementById('days').value;
    //    url += '&location=' + document.getElementById('location').value;
    document.getElementById('status').innerHTML = 'Adding to Profile: ' + url;
  }
  
  if (op == 'write') {
    alert("Operation is " + op + ": " + theLoad + " or " + name);  // debugging crap
    // url += '&projinfo=' + document.getElementById('projinfo').value;
    // url += '&days=' + document.getElementById('days').value;
    //    url += '&location=' + document.getElementById('location').value;
    document.getElementById('status').innerHTML = 'Writing Profile' + url;
  }
  
  // alert("URL is " + url);
  // Open the URL above "asynchronously" (that's what the "true" is
  // for) using the GET method 
  xmlhttp.open('GET', url, true);
  // Check that the PHP script has finished sending us the result
  xmlhttp.onreadystatechange = function() {
    if(xmlhttp.readyState == 4 && xmlhttp.status == 200) {
      // Replace the content of the "result" DIV with the result
      // returned by the PHP script
      document.getElementById('result').innerHTML = xmlhttp.responseText + ' ';
      document.getElementById('status').innerHTML = 'updateProfile(' + op + ') done...';
    } else {
      if(xmlhttp.readyState == 3) {
        document.getElementById('status').innerHTML = 'updateProfile(' + op + ') in progress...'
        + xmlhttp.readyState + " : " + xmlhttp.status;
      } else {
        // If the PHP script fails to send a response, or sends back an
        //        error, display a simple user-friendly notification 
        document.getElementById('status').innerHTML = 'Error: updateProfile(' + op + ') Failed!'
        + xmlhttp.readyState + " : " + xmlhttp.status;
      }
    }
  };
  // alert("Writing data to database!" + url);  // debugging crap
  xmlhttp.send(null);
}

// This updates the information for this project from the web page.
function newProject(op)
{
  var theID = document.getElementById('projid').value;
  var theName = document.getElementById('projname').value;

  //  alert("Operation is " + op);  // debugging crap
  
  //This sets a variable with the URL (and query strings) to our PHP script
  var url = 'project.php?projid=' + theID;
  url += '&projname=' + theName;
  url += '&op=' + op;

  if (op == 'write') {
    url += '&projinfo=' + document.getElementById('projinfo').value;
    url += '&latitude=' + document.getElementById('latitude').value;
    url += '&longitude=' + document.getElementById('longitude').value;
    url += '&sunhours=' + document.getElementById('sunhours').value;
    url += '&windhours=' +  document.getElementById('windhours').value;
    url += '&speed=' + document.getElementById('speed').value;
    //    url += '&location=' + document.getElementById('location').value;
    document.getElementById('status').innerHTML = 'updating Project' + url;
    //alert("Writing data to database!" + url);  // debugging crap
  }
  
  // Open the URL above "asynchronously" (that's what the "true" is
  // for) using the GET method 
  xmlhttp.open('GET', url, true);
  // Check that the PHP script has finished sending us the result
  xmlhttp.onreadystatechange = function() {
    if(xmlhttp.readyState == 4 && xmlhttp.status == 200) {
      // Replace the content of the "result" DIV with the result
      // returned by the PHP script
      document.getElementById('result').innerHTML = xmlhttp.responseText + ' ';
      document.getElementById('status').innerHTML = 'newProject(' + op + ') done...';
    } else {
      if(xmlhttp.readyState == 3) {
        document.getElementById('status').innerHTML = 'newProject(' + op + ') in progress...'
        + xmlhttp.readyState + " : " + xmlhttp.status;
      } else {
        // If the PHP script fails to send a response, or sends back an
        //        error, display a simple user-friendly notification 
        document.getElementById('status').innerHTML = 'Error: newProject(' + op + ') Failed!'
        + xmlhttp.readyState + " : " + xmlhttp.status;
      }
    }
  };
  xmlhttp.send(null);
}

// This updates the information for this project from the web page.
function updateProject()
{
  var theID = document.getElementById('projid').value;
  var theName = document.getElementById('projname').value;
  var theInfo = document.getElementById('projinfo').value;
  var theLat = document.getElementById('latitude').value;
  var theLon = document.getElementById('longitude').value;
  var theSunHours = document.getElementById('projsunhours').value;
  var theWindHours = document.getElementById('projwindhours').value;
  var theSpeed = document.getElementById('projspeed').value;
  var theLocation = document.getElementById('projlocation').value;

  document.getElementById('status').innerHTML = "Updating project " + theName
    + ": " + theID + ": " + theInfo + ":" + theLat + ":" + theLon;

  //This sets a variable with the URL (and query strings) to our PHP script
  var url = 'project.php?projid=' + theID;
  url += '&projname=' + theName;
  url += '&projinfo=' + theInfo;
  url += '&latitude=' + theLat;
  url += '&longitude=' + theLon;
  url += '&sunhours=' + theSunHours;
  url += '&windhours=' + theWindHours;
  url += '&speed=' + theSpeed;
  url += '&location=' + thelocation;
  url += '&op=write';

  alert("URL is " + url);

  //Open the URL above "asynchronously" (that's what the "true" is for) using the GET method
  xmlhttp.open('GET', url, true);
  //Check that the PHP script has finished sending us the result
  xmlhttp.onreadystatechange = function() {
    if(xmlhttp.readyState == 4 && xmlhttp.status == 200) {
      // Replace the content of the "result" DIV with the result
      // returned by the PHP script
      document.getElementById('result').innerHTML = xmlhttp.responseText + ' ';
      document.getElementById('status').innerHTML = 'updateProject() done...'
      + xmlhttp.readyState + " : " + xmlhttp.status;
    } else {
      if(xmlhttp.readyState == 3) {
        document.getElementById('status').innerHTML = 'updateProject() in progress...'
        + xmlhttp.readyState + " : " + xmlhttp.status;
      } else {
        // If the PHP script fails to send a response, or sends back an
        //        error, display a simple user-friendly notification 
        document.getElementById('status').innerHTML = 'Error: updateProject() Failed!'
        + xmlhttp.readyState + " : " + xmlhttp.status;
      }
    }
  };
  xmlhttp.send(null);
}

// This updates the information for this project from the web page.
function newLoad()
{
  // Get the selected item from the menu
  var theID = 0;
  var theQuery = document.getElementById("load").options[document.getElementById("load").selectedIndex].text;
  if(theQuery !== "") {
    document.getElementById("result").innerHTML=theQuery;
  }
  
  //This sets a variable with the URL (and query strings) to our PHP script
  var url = 'newload.php?loadid=' + theID;
  url += '&loadname=' + theQuery;
  //Open the URL above "asynchronously" (that's what the "true" is
  //for) using the GET method
  xmlhttp.open('GET', url, true);
  //Check that the PHP script has finished sending us the result
  xmlhttp.onreadystatechange = function() {
    if(xmlhttp.readyState == 4 && xmlhttp.status == 200) {
      //Replace the content of the "result" DIV with the result
      //returned by the PHP script
      document.getElementById('continue').innerHTML = xmlhttp.responseText + ' ';
    } else {
      //If the PHP script fails to send a response, or sends back an
      //        error, display a simple user-friendly notification
      //        document.getElementById('result').innerHTML = 'Error: function Failed!';
      }
  };
  xmlhttp.send(null);
}

// SayHello() prints a message in the document's "hello" area
function SayHello() {
    // var theQuery2 = document.getElementById('load').value;
    var current = document.getElementById("result").innerHTML;
    // Get the selected item from the menu
    var theQuery = document.getElementById("load").options[document.getElementById("load").selectedIndex].text;
    var res = current + "<br>" + theQuery;
    if(theQuery !== "") {
      document.getElementById("result").innerHTML=res;
    }
    // <?php gui_add_item("TV", "TV sucks", 1, 2, 3, 4); ?>;
    // <?php $foobar .= " it"; ?>;
    // foo="<?php gui_get_load_data('TV') ?>";
    // <?php
    //     $boo = gui_get_load_data('Laptop');
    //     //$boo = gui_get_load_data($_GET['test']);
    //     $ii = count($boo);
    //     while ($ii) {
    // ?>
    // rows2[rows2.length]=<?php echo '"'.$boo[$ii].'"'?>;
    // <?php
    //     $ii = $ii - 1;
    //     }
    // ?>
    //foo=<?php echo $foobar ?>;
    document.getElementById("continue").innerHTML=rows1;
    
    rows[rows.length]=theQuery;
    for (var i in rows) {
      res = res + "<br>" + rows[i];
    }    
    document.getElementById("summary").innerHTML=res;
    // This array hold all the data for an item
    var loaditem = [theQuery, 0, 1, 2];
    allloads[allloads.length] = loaditem;
    // document.getElementById("continue").innerHTML=allloads;

    return;
}
