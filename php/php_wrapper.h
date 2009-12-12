/* 
 *   Copyright (C) 2009 Free Software Foundation, Inc.
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef PHP_GNUAE_H
#define PHP_GNUAE_H 1

#ifdef ZTS
#include "TSRM.h"
#endif

#include "gnuae.h"

#if 1
ZEND_BEGIN_MODULE_GLOBALS(gnuae)
item_t **items;
long count;
ZEND_END_MODULE_GLOBALS(gnuae)
#else
ZEND_DECLARE_MODULE_GLOBALS(gnuae)
#endif

#ifdef ZTS
#define GNUAE_G(v) TSRMG(gnuae_globals_id, zend_gnuae_globals *, v)
#else
#define GNUAE_G(v) (gnuae_globals.v)
#endif

int list_names(char *);
     
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

// These functions are all related to GUI support
PHP_FUNCTION(gui_init);
// List the names of the various items so we can create a menu
PHP_FUNCTION(gui_list_names);
PHP_FUNCTION(gui_add_item);
PHP_FUNCTION(gui_list_items);
PHP_FUNCTION(gui_get_load_data);

extern zend_module_entry gnuae_module_entry;
#define phpext_gnuae_ptr &gnuae_module_entry

#endif

// local Variables:
// mode: C++
// indent-tabs-mode: t
// End:
