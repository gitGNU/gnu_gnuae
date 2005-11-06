#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_wrapper.h"
#include "NEC.h"

static function_entry gnuae_functions[] = {
    PHP_FE(gnuae_world, NULL)
    PHP_FE(nec_watts, NULL)
    {NULL, NULL, NULL}
};

zend_module_entry gnuae_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_GNUAE_WORLD_EXTNAME,
    gnuae_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
#if ZEND_MODULE_API_NO >= 20010901
    PHP_GNUAE_WORLD_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_GNUAE
ZEND_GET_MODULE(gnuae)
#endif

PHP_FUNCTION(gnuae_world)
{
    char *str;
    float res;
    char buf[100];

    nec_toggle_debug(1);
    res = nec_watts(12.0, 3.8);

    sprintf(buf, "Returned %f", res);
    
    //str = estrdup("Hello World");

    str = estrdup(buf);
    
    RETURN_STRING(str, 0);
}

PHP_FUNCTION(nec_volt_loss)
{
  double amps, temp;
  long distance, awg, conductors;
  
  if (zend_parse_parameters(5 TSRMLS_CC, "llddl", &distance, &awg, &amps, &temp, &conductors) == FAILURE) {
    WRONG_PARAM_COUNT;
  }
  
  //  RETURN_DOUBLE(nec_volt_lost(distance, awg, amps, temp, conductors));
  RETURN_BOOL(0);
}

PHP_FUNCTION(nec_volt_drop)
{
  double volts, amps, temp;
  long distance, awg, conductors;
  
  if (zend_parse_parameters(6 TSRMLS_CC, "lldddl", &awg, &distance, &volts, &amps, &temp, &conductors) == FAILURE) {
    WRONG_PARAM_COUNT;
  }
  
  RETURN_DOUBLE(nec_volt_drop(awg, distance, volts, amps, temp, conductors));
}

PHP_FUNCTION(nec_watts)
{
  double amps, volts;
  
  if (zend_parse_parameters(2 TSRMLS_CC, "dd", &volts, &amps) == FAILURE) {
    WRONG_PARAM_COUNT;
  }
  
  RETURN_DOUBLE(nec_watts(volts, amps));
}


PHP_FUNCTION(nec_amps)
{
  double watts, volts;
  
  if (zend_parse_parameters(2 TSRMLS_CC, "dd", &watts, &volts) == FAILURE) {
    WRONG_PARAM_COUNT;
  }
  
  RETURN_DOUBLE(nec_amps(watts, volts));
}

PHP_FUNCTION(nec_volts)
{
  double watts, amps;
  
  if (zend_parse_parameters(2 TSRMLS_CC, "dd", &watts, &amps) == FAILURE) {
    WRONG_PARAM_COUNT;
  }
  
  RETURN_DOUBLE(nec_volts(watts, amps));
}

PHP_FUNCTION(nec_resistance)
{
  double temp;
  long awg;
  
  if (zend_parse_parameters(2 TSRMLS_CC, "ld", &awg, &temp) == FAILURE) {
    WRONG_PARAM_COUNT;
  }
  
  RETURN_DOUBLE(nec_resistance(awg, temp));
}
  
PHP_FUNCTION(nec_wire_derate)
{
  double temp;
  long awg;
  
  if (zend_parse_parameters(2 TSRMLS_CC, "ld", &awg, &temp) == FAILURE) {
    WRONG_PARAM_COUNT;
  }
  
  RETURN_DOUBLE(nec_wire_derate(awg, temp));
}

PHP_FUNCTION(nec_ampacity)
{
  double amps;
  
  if (zend_parse_parameters(2 TSRMLS_CC, "d", &amps) == FAILURE) {
    WRONG_PARAM_COUNT;
  }
  
  RETURN_DOUBLE(nec_ampacity(amps));
}

PHP_FUNCTION(nec_crystal_comp)
{
  double temp;
  
  if (zend_parse_parameters(1 TSRMLS_CC, "ld", &temp) == FAILURE) {
    WRONG_PARAM_COUNT;
  }
  
  RETURN_DOUBLE(nec_crystal_comp(temp));
}

PHP_FUNCTION(nec_over_current)
{
}

PHP_FUNCTION(nec_find_gauge)
{
}

PHP_FUNCTION(nec_find_conduit)
{
}

PHP_FUNCTION(nec_find_ground)
{
}

PHP_FUNCTION(nec_wire_ampacity)
{
  long awg, temp, conductors, conduit;
  zval *wiretype;
  
  if (zend_parse_parameters(5 TSRMLS_CC, "llllo", &awg, &temp, &conductors, &conduit, &wiretype) == FAILURE) {
    WRONG_PARAM_COUNT;
  }
  
  //  RETURN_DOUBLE(nec_wire_ampacity(awg, temp, conductors, conduit, wiretype));
}

PHP_FUNCTION(nec_awg_pv2pv)
{
}

PHP_FUNCTION(nec_awg_pv2combiner)
{
}

PHP_FUNCTION(nec_awg_combiner2charger)
{
}

PHP_FUNCTION(nec_awg_wind2charger)
{
}

PHP_FUNCTION(nec_awg_charger2battery)
{
}

PHP_FUNCTION(nec_awg_battery2inverter)
{
}

