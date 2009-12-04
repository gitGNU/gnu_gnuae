<?php

// phpinfo();

  // DejaGnu API
$passes = 0;
$fails = 0;

function pass ($msg) {
  global $passes;
  printf("PASS: %s <p>\n", $msg);
  $passes++;
}

function fail ($msg) {
  global $fails;
  printf("FAIL: %s <p>\n", $msg);
  $fails++;
}

function totals () {
  global $fails, $passes;
  printf("\n# of passes: %d <p>\n", $passes);
  printf("# of failures: %d <p>\n", $fails);
}

//----------------------------------------
// The test cases start here.


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
  pass("nec_volt_loss(140, 2, 23.4, 56.7, 2) == $foo");
 } else {
  fail("nec_volt_loss(140, 2, 23.4, 56.7, 2) == $foo");
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
  pass("nec_volts(75.6, 6) == $foo");
 } else {
  fail("nec_volts(75.6, 6) == $foo");
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
  pass("nec_wire_derate(8, 120) == $foo");
 } else {
  fail("nec_wire_derate(8, 120) == $foo");
 }

// NEC Ampacity
$foo = nec_ampacity(12);
if (bccomp($foo, '') == 0) {
  pass("nec_ampacity(12) == $foo");
 } else {
  fail("nec_ampacity(12) == $foo");
 }

// NEC Crystal Comp
$foo = nec_crystal_comp(120);
if (bccomp($foo, '') == 0) {
  pass("nec_crystal_comp(120) == $foo");
 } else {
  fail("nec_crystal_comp(120) == $foo");
 }

// NEC Over Current
$foo = nec_over_current(3, 3.6);
if (bccomp($foo, '') == 0) {
  pass("nec_over_current(3, 3.6) == $foo");
 } else {
  fail("nec_over_current(3, 3.6) == $foo");
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
  pass("nec_find_conduit(10, 3, THWN2, EMT) == $foo");
 } else {
  fail("nec_find_conduit(10, 3, THWN2, EMT) == $foo");
 }

// NEC Find Ground
$foo = nec_find_ground();
if (bccomp($foo, '') == 0) {
  pass("nec_find_ground() == $foo");
 } else {
  fail("nec_find_ground() == $foo");
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

// Get the list of names from the Loads table
$foo = gui_list_names("loads");
$size=count($foo);
if ($size) {
  pass("gui_list_names(load) returns $size entries");  
} else {
  fail("gui_list_names(load) fails to return any entries");  
}

$foo = gui_list_names("centers");
$size=count($foo);
if ($size) {
  pass("gui_list_names(center) returns $size entries");  
} else {
  fail("gui_list_names(center) fails to return any entries");  
}

$foo = gui_list_names("inverter");
$size=count($foo);
if ($size) {
  pass("gui_list_names(inverter) returns $size entries");  
} else {
  fail("gui_list_names(inverter) fails to return any entries");  
}

$foo = gui_list_names("combiners");
$size=count($foo);
if ($size) {
  pass("gui_list_names(combiners) returns $size entries");  
} else {
  fail("gui_list_names(combiners) fails to return any entries");  
}

$foo = gui_list_names("pvpanels");
$size=count($foo);
if ($size) {
  pass("gui_list_names(pvpanels) returns $size entries");  
} else {
  fail("gui_list_names(pvpanels) fails to return any entries");  
}

$foo = gui_list_names("pumps");
$size=count($foo);
if ($size) {
  pass("gui_list_names(pumps) returns $size entries");  
} else {
  fail("gui_list_names(pumps) fails to return any entries");  
}

$foo = gui_list_names("charger");
$size=count($foo);
if ($size) {
  pass("gui_list_names(charger) returns $size entries");  
} else {
  fail("gui_list_names(charger) fails to return any entries");  
}

$foo = gui_list_names("batteries");
$size=count($foo);
if ($size) {
  pass("gui_list_names(batteries) returns $size entries");
} else {
  fail("gui_list_names(batteries) fails to return any entries");
}

$foo = gui_list_names("wire");
$size=count($foo);
if ($size) {
  pass("gui_list_names(wire) returns $size entries");  
} else {
  fail("gui_list_names(wire) fails to return any entries");  
}

// Dump the totals
totals();

?>


