#ifndef PHP_GNUAE_H
#define PHP_GNUAE_H 1

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_BEGIN_MODULE_GLOBALS(gnuae)
    long counter;
    zend_bool direction;
ZEND_END_MODULE_GLOBALS(gnuae)

#ifdef ZTS
#define GNUAE_G(v) TSRMG(gnuae_globals_id, zend_gnuae_globals *, v)
#else
#define GNUAE_G(v) (gnuae_globals.v)
#endif
     
#define PHP_GNUAE_WORLD_VERSION "1.0"
#define PHP_GNUAE_WORLD_EXTNAME "gnuae"

PHP_MINIT_FUNCTION(gnuae);
PHP_MSHUTDOWN_FUNCTION(gnuae);
PHP_RINIT_FUNCTION(gnuae);

//PHP_FUNCTION(gnuae_world);

PHP_FUNCTION(nec_volt_drop);
PHP_FUNCTION(nec_volt_loss);

PHP_FUNCTION(nec_watts);
PHP_FUNCTION(nec_amps);
PHP_FUNCTION(nec_volts);
PHP_FUNCTION(nec_resistance);
PHP_FUNCTION(nec_wire_derate);
PHP_FUNCTION(nec_ampacity);
PHP_FUNCTION(nec_crystal_comp);
PHP_FUNCTION(nec_over_current);
PHP_FUNCTION(nec_find_gauge);
PHP_FUNCTION(nec_find_conduit);
PHP_FUNCTION(nec_find_ground);
PHP_FUNCTION(nec_wire_ampacity);

PHP_FUNCTION(nec_awg_pv2pv);
PHP_FUNCTION(nec_awg_pv2combiner);
PHP_FUNCTION(nec_awg_combiner2charger);
PHP_FUNCTION(nec_awg_wind2charger);
PHP_FUNCTION(nec_awg_charger2battery);
PHP_FUNCTION(nec_awg_battery2inverter);


extern zend_module_entry gnuae_module_entry;
#define phpext_gnuae_ptr &gnuae_module_entry

#endif

