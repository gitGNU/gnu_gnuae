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

// Start with just one wire type for all conduit calcuations
var nec_wires3 = 1;

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

// This executes a php script, and loads the output into a division
function loadPage(url)
{

  document.getElementById('status').innerHTML = "Loading URL: " + url;
  
  // Open the URL above "asynchronously" (that's what the "true" is
  // for) using the GET method 
  xmlhttp.open('GET', url, true);
  // Check that the PHP script has finished sending us the result
  xmlhttp.onreadystatechange = function() {
    if(xmlhttp.readyState == 4 && xmlhttp.status == 200) {
      // Replace the content of the "result" DIV with the result
      // returned by the PHP script
      document.getElementById('result').innerHTML = xmlhttp.responseText + ' ';
    } else {
      if(xmlhttp.readyState == 3) {
        + xmlhttp.readyState + " : " + xmlhttp.status;
      } else {
        // If the PHP script fails to send a response, or sends back an
        // error, display a simple user-friendly notification 
        document.getElementById('status').innerHTML = 'Error: newProject(' + op + ') Failed!'
        + xmlhttp.readyState + " : " + xmlhttp.status;
      }
    }
  };
  xmlhttp.send(null);
}

// This updates the information for this project from the web page.
function updateWiring(id)
{

  var theResult = document.getElementById(id).value;

//  var theFoo=<?php echo nec_awg_pv2pv(2, 48.3, 45.6, 18.9, 2)?>;
  var theFoo = <?php echo $projname; ?>;
  // var theFoo="<?php echo phpinfo(); ?>";
   document.getElementById('status').innerHTML = 'ID is: ' + id + ":" + theResult + ":" + theFoo;
}

// This updates the information for this project from the web page.
function updateNEC(op)
{
  var theWatts  = document.getElementById('watts').value;
  var theVolts  = document.getElementById('volts').value;
  var theAmps   = document.getElementById('amps').value;
  var theDistance   = document.getElementById('distance').value;
  var theLoss   = document.getElementById('loss').value;
  var theDrop   = document.getElementById('drop').value;
  var theTemp   = document.getElementById('temp').value;
  var theLossAmps   = document.getElementById('lossamps').value;
  var theLossVolts   = document.getElementById('lossvolts').value;
  
  nec_wires3 = document.necform.nec_wires3.value;
  if (nec_wires3 == NaN) {
    nec_wires3 = 1;
  } else {
    nec_wires3++;
  }
  document.necform.nec_wires3.value = nec_wires3;
  
  document.getElementById('status').innerHTML = 'Operation is: ' + op
    + ":" + theWatts + ":" + theVolts + ":" + theAmps;
  
  // This sets a variable with the URL (and query strings) to our PHP script
  var url = 'neccalc.php?op=' + op;
  
  if (op == 'watts') {
    theResult=<?php echo $watts ?>;
    //theResult=<?php echo nec_volts(67.4, 22.4) ?>;
  } else if (op == 'volts') {
    theResult=<?php echo $volts ?>;
    //theResult=<?php echo nec_watts(1, 2, 3) ?>;
  } else if (op == 'amps') {
    theResult=<?php echo $amps ?>;
    //theResult=<?php echo nec_amps(1, 2, 3) ?>;
  } else if (op == 'reset1') {
    theWatts = 0;
    document.getElementById('watts').value = 0;
    theVolts = 0;
    document.getElementById('volts').value = 0;
    theAmps = 0;
    document.getElementById('amps').value = 0;
    theResult = "Resetting all fields";
    return;
  } else if (op == 'reset2') {
    theLoss = 0;
    document.getElementById('loss').value = 0;
    theDrop = 0;
    document.getElementById('drop').value = 0;
    theTemp = 0;
    document.getElementById('temp').value = 0;
    theLossAmps = 0;
    document.getElementById('lossamps').value = 0;
    theLossVolts = 0;
    document.getElementById('lossvolts').value = 0;
    theDistance = 0;
    document.getElementById('distance').value = 0;
    theResult = "Resetting all fields";
    return;
  } else if (op == 'reset3') {
    nec_wires3 = 1;
    document.necform.nec_wires3.value = nec_wires3;
    theResult = "Resetting all fields";
  } else if ((op == 'calc2') || (op == 'lossamps') || (op == 'lossvolts') || (op == 'distance') || (op == 'temp')) {
    if ((theTemp > 0) || (theDistance > 0) || (theLossVolts > 0) || (theLossAmps > 0) || (theAWG > 0)) {
      return;
    }
  } else if (op == 'calc3') {
    url += '&nec_wires3=' + nec_wires3;
  }
  
  url += 'watts=' + theWatts;
  url += '&amps=' + theAmps;
  url += '&volts=' + theVolts;
  url += '&loss=' + theLoss;
  url += '&drop=' + theDrop;
  url += '&temp=' + theTemp;
  url += '&distance=' + theDistance;
  url += '&lossamps=' + theLossAmps;
  url += '&lossvolts=' + theLossVolts;
  // url += 'conduct2=' + document.getElementById('conduct_second').value;;
  // url += 'conduct3=' + document.getElementById('conduct_third').value;;
  // url += 'awg3=' + document.getElementById('awg_third').value;
  // url += 'wire3=' + document.getElementById('wname_third').value;

  loadPage(url);
}

// This updates the information for this project from the web page.
function updateProfile(op, name)
{
  var theID = document.getElementById('projid').value;
  var theName = document.getElementById('projname').value;
  var theLoad = document.getElementById("load").options[document.getElementById("load").selectedIndex].text;
  
  
  // This sets a variable with the URL (and query strings) to our PHP script
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
    //url += '&hours=' + document.getElementById('item[0]_hours').value;
    // url += '&days=' + document.getElementById('item[0]_days').value;
    // url += '&minutes=' + document.getElementById('item[0]_minutes').value;
    //    url += '&location=' + document.getElementById('item[0]_location').value;
    document.getElementById('status').innerHTML = 'Writing Profile' + url;
  }
  
  loadPage(url);
}

// This updates the information for this project from the web page.
function newProject(op)
{

  // Get the default name and ID from the text field.
  var theID = document.getElementById('projid').value;
  var theName = document.getElementById('projname').value;
  
  //This sets a variable with the URL (and query strings) to our PHP script
  var url = 'project.php?projid=' + theID;
  url += '&projname=' + theName;
  url += '&op=' + op;  
  
  loadPage(url);
  //  alert("Operation is " + op);  // debugging crap
//  document.projform.projid.value = document.getElementById('editprojid').value;
}

// This updates the information for this project from the web page.
function updateProject(op)
{
  var theID = document.getElementById('projid').value;
  var theName = document.getElementById('editprojname').value;
  //  var theInfo = document.getElementById('projinfo').value;
  var theLat = document.getElementById('latitude').value;
  var theLon = document.getElementById('longitude').value;
  var theSunHours = document.getElementById('sunhours').value;
  var theWindHours = document.getElementById('windhours').value;
  var theSpeed = document.getElementById('speed').value;
  // var theLocation = document.getElementById('location').value;

   // document.getElementById('status').innerHTML = "Updating project " + theName
   //  + ": " + theID + ": " + theInfo + ":" + theLat + ":" + theLon;

  //This sets a variable with the URL (and query strings) to our PHP script
  var url = 'project.php?projid=' + theID;
  url += '&projname=' + theName;
  //  url += '&projinfo=' + theInfo;
  url += '&latitude=' + theLat;
  url += '&longitude=' + theLon;
  url += '&sunhours=' + theSunHours;
  url += '&windhours=' + theWindHours;
  url += '&speed=' + theSpeed;
  url += '&op=write';

  //  alert("URL is " + url);  // debugging crap

  loadPage(url);
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

  loadPage(url);
}

