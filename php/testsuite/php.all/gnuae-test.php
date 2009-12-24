<?php

// phpinfo();

  // DejaGnu API
$passes = 0;
$xpasses = 0;
$fails = 0;
$xfails = 0;

function pass ($msg) {
  global $passes;
  printf("PASS: %s <br>\n", $msg);
  $passes++;
}

function xpass ($msg) {
  global $xpasses;
  printf("XPASS: %s <br>\n", $msg);
  $xpasses++;
}

function fail ($msg) {
  global $fails;
  printf("FAIL: %s <br>\n", $msg);
  $fails++;
}

function xfail ($msg) {
  global $xfails;
  printf("XFAIL: %s <br>\n", $msg);
  $xfails++;
}

function note ($msg) {
  printf("\n%s <br>\n\n", $msg);
}

function totals () {
  global $fails, $passes, $xfails, $xpasses;
  printf("\n# of passes: %d <br>\n", $passes);
  printf("# of failures: %d <br>\n", $fails);
  if ($xfails) {
    printf("# of expected failures: %d <br>\n", $xfails);
  }
  if ($xpasses) {
    printf("# of unexpected sucesses: %d <br>\n", $xpasses);
  }
}

// NEC Voltage Drop
$foo = nec_volt_drop(2, 140, 48.1, 32.1, 67.8, 2);
if (bccomp($foo, '1.4899') == 0) {
  pass("nec_volt_drop(2, 140, 48.1, 32.1, 67.8, 2) == $foo");
 } else {
  fail("nec_volt_drop(2, 140, 48.1, 32.1, 67.8, 2) == $foo");
 }

// NEC Voltage Loss
$foo = nec_volt_loss(140, 2, 23.4, 56.7, 2);
if (bccomp($foo, '') == 0) {
  xpass("nec_volt_loss(140, 2, 23.4, 56.7, 2) == $foo");
 } else {
  xfail("nec_volt_loss(140, 2, 23.4, 56.7, 2) == $foo");
 }

// NEC Watts
$foo = nec_watts(12.6, 6);
if (bccomp($foo, '75.6000061035') == 0) {
  pass("nec_watts(12.6, 6) == $foo");
 } else {
  fail("nec_watts(12.6, 6) == $foo");
 }

// NEC Amps
$foo = nec_amps(12.6,3);
if (bccomp($foo, '4.2000002861') == 0) {
  pass("nec_amps(12.6,3) == $foo");
 } else {
  fail("nec_amps(12.6,3) == $foo");
 }

// NEC Volts
$foo = nec_volts(75.6, 6);
if (bccomp($foo, '12.6') == 0) {
  xpass("nec_volts(75.6, 6) == $foo");
 } else {
  xfail("nec_volts(75.6, 6) == $foo");
 }

// NEC Resistance
$foo = nec_resistance(8, 23);
if (bccomp($foo, '0.576964795589') == 0) {
  pass("nec_resistance(8, 23) == $foo");
 } else {
  fail("nec_resistance(8, 23) == $foo");
 }

// NEC Wire Derate
$foo = nec_wire_derate(8, 120);
if (bccomp($foo, '120') == 0) {
  xpass("nec_wire_derate(8, 120) == $foo");
 } else {
  xfail("nec_wire_derate(8, 120) == $foo");
 }

// NEC Ampacity
$foo = nec_ampacity(12);
if (bccomp($foo, '') == 0) {
  xpass("nec_ampacity(12) == $foo");
 } else {
  xfail("nec_ampacity(12) == $foo");
 }

// NEC Crystal Comp
$foo = nec_crystal_comp(120);
if (bccomp($foo, '') == 0) {
  xpass("nec_crystal_comp(120) == $foo");
 } else {
  xfail("nec_crystal_comp(120) == $foo");
 }

// NEC Over Current
$foo = nec_over_current(3, 3.6);
if (bccomp($foo, '') == 0) {
  xpass("nec_over_current(3, 3.6) == $foo");
 } else {
  xfail("nec_over_current(3, 3.6) == $foo");
 }

// NEC Find Gauge
$foo = nec_find_gauge(140, 48, 45, 75, 3);
if (bccomp($foo, '4') == 0) {
  pass("nec_find_gauge(140, 48, 45, 75, 3) == $foo");
 } else {
  fail("nec_find_gauge(140, 48, 45, 75, 3) == $foo");
 }

// NEC Find Conduit
$foo = nec_find_conduit(2, 2, THHN, EMT);
if (bccomp($foo, '') == 0) {
  xpass("nec_find_conduit(10, 3, THWN2, EMT) == $foo");
 } else {
  xfail("nec_find_conduit(10, 3, THWN2, EMT) == $foo");
 }

// NEC Find Ground
$foo = nec_find_ground();
if (bccomp($foo, '') == 0) {
  xpass("nec_find_ground() == $foo");
 } else {
  xfail("nec_find_ground() == $foo");
 }

// NEC AWG PV 2 PV
$foo = nec_awg_pv2pv(2, 48.3, 45.6, 18.9, 2);
if (bccomp($foo, '18') == 0) {
  pass("nec_awg_pv2pv(2, 48.3, 45.6, 18.9, 2) == $foo");
 } else {
  fail("nec_awg_pv2pv(2, 48.3, 45.6, 18.9, 2) == $foo");
 }

$foo = nec_awg_pv2combiner(20, 48.3, 45.6, 18.9, 2);
if (bccomp($foo, '18') == 0) {
  pass("nec_awg_pv2combiner(20, 48.3, 45.6, 18.9, 2) == $foo");
 } else {
  fail("nec_awg_pv2combiner(20, 48.3, 45.6, 18.9, 2) == $foo");
 }

$foo = nec_awg_combiner2charger(140, 48.3, 45.6, 18.9, 2);
if (bccomp($foo, '2') == 0) {
  pass("nec_awg_combiner2charger(140, 48.3, 45.6, 18.9, 2) == $foo");
 } else {
  fail("nec_awg_combiner2charger(140, 48.3, 45.6, 18.9, 2) == $foo");
 }

$foo = nec_awg_wind2charger(140, 48.3, 45.6, 18.9, 2);
if (bccomp($foo, '4') == 0) {
  pass("nec_awg_wind2charger(140, 48.3, 45.6, 18.9, 2) == $foo");
 } else {
  fail("nec_awg_wind2charger(140, 48.3, 45.6, 18.9, 2) == $foo");
 }

$foo = nec_awg_charger2battery(4, 48.3, 45.6, 18.9, 2);
if (bccomp($foo, '18') == 0) {
  pass("nec_awg_charger2battery(4, 48.3, 45.6, 18.9, 2) == $foo");
 } else {
  fail("nec_awg_charger2battery(4, 48.3, 45.6, 18.9, 2) == $foo");
 }

$foo = nec_awg_battery2inverter(7, 48.3, 45.6, 18.9, 2);
if (bccomp($foo, '16') == 0) {
  pass("nec_awg_battery2inverter(7, 48.3, 45.6, 18.9, 2) == $foo");
 } else {
  fail("nec_awg_battery2inverter(7, 48.3, 45.6, 18.9, 2) == $foo");
 }

//
// GUI API tests
// 

//xdebug_start_trace("foo");

// Test database functions

// This function is only used for testing, and closes the
// connection to the existing database. This way we don't
// pollute the main database with testing data.
gui_init_db("gnuaetest");

// Get the list of names from the tables
$foo = gui_list_names("loads");
$size=count($foo);
if ($size) {
  pass("gui_list_names(load) returns $size entries");  
} else {
  fail("gui_list_names(load) fails to return any entries");  
}

$foo1 = gui_get_data(0, "TV", "loads");
if (count($foo1)) {
  if ($foo1[0] == "TV") {
    pass("gui_get_data(loads) returns legit data");
  } else {
    fail("gui_get_data(loads) fails to legit data");
  }
} else {
  fail("gui_get_data(loads) fails to legit data");
}

$foo2 = gui_list_names("centers");
$size=count($foo2);
if ($size) {
  pass("gui_list_names(centers) returns $size entries");  
} else {
  fail("gui_list_names(centers) fails to return any entries");  
}

$foo3 = gui_get_data(0, "SW4024", "centers");
if (count($foo3)) {
  if ($foo3[0] == "SW4024") {
    pass("gui_get_data(centers) returns legit data");
  } else {
    fail("gui_get_data(centers) fails to legit data");
  }
} else {
  fail("gui_get_data(centers) fails to legit data");
}

$foo4 = gui_list_names("inverters");
$size=count($foo4);
if ($size) {
  pass("gui_list_names(inverters) returns $size entries");  
} else {
  fail("gui_list_names(inverters) fails to return any entries");  
}

$foo5 = gui_get_data(0, "Trace 2548", "inverters");
if (count($foo5)) {
  if ($foo5[0] == "Trace 2548") {
    pass("gui_get_data(inverters) returns legit data");
  } else {
    fail("gui_get_data(inverters) fails to legit data");
  }
} else {
  fail("gui_get_data(inverters) fails to legit data");
}

$foo6 = gui_list_names("combiners");
$size=count($foo6);
if ($size) {
  pass("gui_list_names(combiners) returns $size entries");  
} else {
  fail("gui_list_names(combiners) fails to return any entries");  
}

$foo7 = gui_get_data(0, "PSPV", "combiners");
if (count($foo7)) {
  if ($foo7[0] == "PSPV") {
    pass("gui_get_data(combiners) returns legit data");
  } else {
    fail("gui_get_data(combiners) fails to legit data");
  }
} else {
  fail("gui_get_data(combiners) fails to legit data");
}

$foo8 = gui_list_names("modules");
$size=count($foo8);
if ($size) {
  pass("gui_list_names(modules) returns $size entries");
} else {
  fail("gui_list_names(modules) fails to return any entries");
}

// $foo = gui_get_data(0, "8-KC80-Array", "modules");
// var_dump($foo);
// if (count($foo)) {
//   if ($foo[0] == "8-KC80-Array") {
//     pass("gui_get_data(modules) returns legit data");
//   } else {
//     fail("gui_get_data(modules) fails to legit data");
//   }
// } else {
//   fail("gui_get_data(modules) fails to legit data");
// }

$foo10 = gui_list_names("pumps");
$size=count($foo10);
if ($size) {
  pass("gui_list_names(pumps) returns $size entries");
} else {
  fail("gui_list_names(pumps) fails to return any entries");
}

$foo11 = gui_get_data(0, "ETA", "pumps");
if (count($foo11)) {
  if ($foo11[0] == "ETA") {
    pass("gui_get_data(pumps) returns legit data");
  } else {
    fail("gui_get_data(pumps) fails to legit data");
  }
} else {
  fail("gui_get_data(pumps) fails to legit data");
}

$foo12 = gui_list_names("chargers");
$size=count($foo12);
if ($size) {
  pass("gui_list_names(chargers) returns $size entries");
} else {
  fail("gui_list_names(chargers) fails to return any entries");
}

$foo13 = gui_get_data(0, "C35", "chargers");
if (count($foo13)) {
  if ($foo13[0] == "C35") {
    pass("gui_get_data(chargers) returns legit data");
  } else {
    fail("gui_get_data(chargers) fails to legit data");
  }
} else {
  fail("gui_get_data(chargers) fails to legit data");
}

$foo14 = gui_list_names("batteries");
$size=count($foo14);
if ($size) {
  pass("gui_list_names(batteries) returns $size entries");
} else {
  fail("gui_list_names(batteries) fails to return any entries");
}

$foo15 = gui_get_data(0, "L16H", "batteries");
if (count($foo15)) {
  if ($foo15[0] == "L16H") {
    pass("gui_get_data(batteries) returns legit data");
  } else {
    fail("gui_get_data(batteries) fails to legit data");
  }
} else {
  fail("gui_get_data(batteries) fails to legit data");
}


$foo16 = gui_list_names("wire");
$size=count($foo16);
if ($size) {
  xpass("gui_list_names(wire) returns $size entries");
} else {
  xfail("gui_list_names(wire) fails to return any entries");
}

// $foo = gui_get_data(0, "", "");
// if (count($foo)) {
// if ($foo[0] == "L16H") {
//   pass("gui_get_data() returns legit data");
// } else {
//   fail("gui_get_data() fails to legit data");
// }
// } else {
//   fail("gui_get_data() fails to legit data");
// }

//
// Project API tests
// 

note("<h2>Project Tests</h2>");

// Create a new project entry
$projname = "My Test";
$projdes = "testing, 1,2,3...";
$projid = gui_new_project($projname, $projdes, 1.2, 2.3, 3.4, "none", 4.5, 5.6);
if ($projid) {
  pass("gui_new_project()");
} else {
  fail("gui_new_project()"); 
}

// See if we can read the entry back we just created.
$proj = gui_get_project($projid, $projname);
if ($proj[0] == $projname && $proj[1] == $projdes) {
  pass("gui_get_project(id, name)");
} else {
  fail("gui_get_project(id, name)"); 
}

$proj[0] = "New Name";
$proj[1] = "New Description";
gui_update_project($projid, $proj[0], $proj[1], $proj[2], $proj[3], $proj[4], $proj[5], $proj[6], $proj[7], $proj[8]);
$proj2 = gui_get_project($projid, "New Name");
if ($proj2[0] == $proj[0] && $proj2[1] == $proj[1]) {
  pass("gui_update_project(id, name)");
} else {
  fail("gui_update_project(id, name)"); 
}

gui_erase_project($projid, "New Name");
$proj3 = gui_get_project($projid, "New Name");
if (count($proj3)) {
  fail("gui_erase_project(id, name)");
} else {
  pass("gui_erase_project(id, name)"); 
}

//
// Chosen Items API tests
// 

// gui_get_item(3, "TV");
gui_add_item($projid, "TV", "TV sucks", LOAD, 50050, 2, 3, 4);
gui_add_item($projid, "Stereo", "is great", LOAD, 50051, 6, 7, 8);
$foo17 = gui_list_items($projid);
$size=count($foo17);
if ($size == 2) {
  if ($foo17[1][0] == "TV") { 
    pass("gui_list_items(TV) returns $size entries");
  } else {
    fail("gui_list_items(TV) fails to return any entries"); 
  }
} else {
  fail("gui_list_items(TV) fails to return any entries");
}

gui_erase_item($projid, 50050, "TV");
$foo18 = gui_list_items($projid);
$size=count($foo18);
if ($size == 1) {
  pass("gui_erase_items(TV) returns $size entries");
} else {
  fail("gui_erase_items(TV) fails to return any entries"); 
}

gui_erase_item($projid, 50051, "Stereo");

/* $foo = gui_get_load_data("TV"); */

//var_dump($foo);
//echo $_GET['fooby'];

//xdebug_stop_trace();

// Dump the totals
totals();

?>


