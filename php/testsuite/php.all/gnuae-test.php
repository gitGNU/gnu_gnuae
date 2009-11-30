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
$foo = nec_volt_drop(8, 150, 12, 5, 75, 3);
if (bccomp($foo, '2.70650362968') == 0) {
  pass("nec_volt_drop(8, 150, 12, 5, 75, 3) == $foo");
 } else {
  fail("nec_volt_drop(8, 150, 12, 5, 75, 3) == $foo");
 }

// NEC Voltage Loss
$foo = nec_volt_loss(150, 8, 5, 75, 3);
if (bccomp($foo, '2.70650362968') == 0) {
  pass("nec_volt_loss(8, 150, 12, 5, 75, 3) == $foo");
 } else {
  fail("nec_volt_lossp(8, 150, 12, 5, 75, 3) == $foo");
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

// Dump the totals
totals();

?>


