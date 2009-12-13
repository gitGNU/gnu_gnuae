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

function projSearch() {
  var theQuery = document.getElementById('projname').value;
  // var theQuery = document.getElementById("load").options[document.getElementById("load").selectedIndex].text;  
  //If the form data is *not* blank, query the DB and return the results
  if(theQuery !== "") {
    //Change the content of the "result" DIV to "Searching..."
    //This gives our user confidence that the script is working if it
    //takes a moment for the result to be returned. However the user
    //will likely never see this as the result will be returned in an
    //instant... 
    document.getElementById('result').innerHTML = "Searching for project " + theQuery;
    
    //This sets a variable with the URL (and query strings) to our PHP script
    var url = 'newLoad.php' + theQuery;
    //Open the URL above "asynchronously" (that's what the "true" is
    //for) using the GET method 
    xmlhttp.open('GET', url, true);
    //Check that the PHP script has finished sending us the result
    xmlhttp.onreadystatechange = function() {
      if(xmlhttp.readyState == 4 && xmlhttp.status == 200) {
        //Replace the content of the "result" DIV with the result returned
        // by the PHP script
        document.getElementById('result').innerHTML = xmlhttp.responseText + ' ';
      } else {
        //If the PHP script fails to send a response, or sends back an
        //error, display a simple user-friendly notification 
//        document.getElementById('result').innerHTML = 'Error: preSearch Failed!';
      }
    };
    xmlhttp.send(null);  
  }
}

// This updates the information for this project from the web page.
function updateProject()
{
  var theID = document.getElementById('projid').value;
  var theName = document.getElementById('projname').value;
  var theInfo = document.getElementById('projinfo').value;
  var theLat = document.getElementById('latitude').value;
  var theLon = document.getElementById('longitude').value;

  document.getElementById('result').innerHTML = "Updating project " + theName
    + ": " + theID + ": " + theInfo + ":" + theLat + ":" + theLon;

  //This sets a variable with the URL (and query strings) to our PHP script
  var url = 'updateProject.php?projid=' + theID;
  url += '&projname=' + theName;
  url += '&projinfo=' + theInfo;
  url += '&projlat=' + theLat;
  url += '&projlon=' + theLon;
  
  //Open the URL above "asynchronously" (that's what the "true" is for) using the GET method
  xmlhttp.open('GET', url, true);
  //Check that the PHP script has finished sending us the result
  xmlhttp.onreadystatechange = function() {
    if(xmlhttp.readyState == 4 && xmlhttp.status == 200) {
      //Replace the content of the "result" DIV with the result returned by the PHP script
      document.getElementById('continue').innerHTML = xmlhttp.responseText + ' ';
    } else {
      //If the PHP script fails to send a response, or sends back an error, display a simple user-friendly notification
      //        document.getElementById('result').innerHTML = 'Error: preSearch Failed!';
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
  var url = 'newLoad.php?loadid=' + theID;
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
