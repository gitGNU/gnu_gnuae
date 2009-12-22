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

#include "php.h"
#include "php_wrapper.h"
#include "NEC.h"
#include "gui.h"
#include "Loads.h"
#include "Battery.h"
#include "Centers.h"
#include "Chargers.h"
#include "Combiners.h"
#include "Inverters.h"
#include "Loads.h"
#include "PVPanel.h"
#include "Pumps.h"
#include "Wire.h"

ZEND_DECLARE_MODULE_GLOBALS(gnuae)

static function_entry gnuae_functions[] = {
    PHP_FE(nec_watts, NULL)
    PHP_FE(nec_volt_drop, NULL)
    PHP_FE(nec_volt_loss, NULL)
    PHP_FE(nec_amps, NULL)
    PHP_FE(nec_volts, NULL)
    PHP_FE(nec_resistance, NULL)
    PHP_FE(nec_wire_derate, NULL)
    PHP_FE(nec_ampacity, NULL)
    PHP_FE(nec_crystal_comp, NULL)
    PHP_FE(nec_over_current, NULL)
    PHP_FE(nec_find_gauge, NULL)
    PHP_FE(nec_find_conduit, NULL)
    PHP_FE(nec_find_ground, NULL)
    PHP_FE(nec_wire_ampacity, NULL)
    PHP_FE(nec_awg_pv2pv, NULL)
    PHP_FE(nec_awg_pv2combiner, NULL)
    PHP_FE(nec_awg_combiner2charger, NULL)
    PHP_FE(nec_awg_wind2charger, NULL)
    PHP_FE(nec_awg_charger2battery, NULL)
    PHP_FE(nec_awg_battery2inverter, NULL)
    PHP_FE(gui_list_names, NULL)
    PHP_FE(gui_init, NULL)
    PHP_FE(gui_init_db, NULL)
    PHP_FE(gui_add_item, NULL)
    PHP_FE(gui_list_items, NULL)
    PHP_FE(gui_erase_item, NULL)
    PHP_FE(gui_get_data, NULL)
    PHP_FE(gui_new_project, NULL)
    PHP_FE(gui_update_project, NULL)
    PHP_FE(gui_get_project, NULL)
    PHP_FE(gui_erase_project, NULL)
    {NULL, NULL, NULL}
};

zend_module_entry gnuae_module_entry = {
    STANDARD_MODULE_HEADER,
    "gnuae",
    gnuae_functions,
    PHP_MINIT(gnuae),
    PHP_MSHUTDOWN(gnuae),
    NULL, //PHP_RINIT(gnuae),
    NULL,
    NULL,
    "1.0",
    STANDARD_MODULE_PROPERTIES
};

ZEND_GET_MODULE(gnuae)

// Called when initializing this module into php
PHP_MINIT_FUNCTION(gnuae)
{

    // REGISTER_INI_ENTRIES();
    // php_error(E_WARNING, __LINE__);

    // These define the various constants needed by PHP.
    
    // from gnuae.h, item types
    REGISTER_LONG_CONSTANT("BATTERY", BATTERY,   CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("CENTER",  CENTER,    CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("CHARGER",  CHARGER,  CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("COMBINER", COMBINER, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("INVERTER", INVERTER, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("LOAD",     LOAD,     CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("PVPANEL",  PVPANEL,  CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("PUMP",     PUMP,     CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("WIRE",     WIRE,     CONST_CS|CONST_PERSISTENT);

    // Conduit types from nec_table.h
    REGISTER_LONG_CONSTANT("EMT",    EMT,    CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ENT",    ENT,    CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("FMC",    FMC,    CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("IMC",    IMC,    CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("LFNC_B", LFNC_B, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("LFNC_A", LFNC_A, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("LFMC",   LFMC,   CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("RMC",    RMC,    CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("RNC",    RNC,    CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("PVC_80", PVC_80, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("PVC_40", PVC_40, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("PVC_A",  PVC_A,  CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("PVC_EB", PVC_EB, CONST_CS|CONST_PERSISTENT);

    // Wire types from nec_table.h
    REGISTER_LONG_CONSTANT("RHH",   RHH,   CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("RHW",   RHW,   CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("RHW2",  RHW2,  CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("THHN",  THHN,  CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("THHW",  THHW,  CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("THW",   THW,   CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("THW2",  THW2,  CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("THWN",  THWN,  CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("THWN2", THWN2, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("XHHW",  XHHW,  CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("XHHW2", XHHW2, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE",    SE,    CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("USE",   USE,   CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("USE2",  USE2,  CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("TW",    TW,    CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("UF",    UF,    CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("TBS",   TBS,   CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SA",    SA,    CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SIS",   SIS,   CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("FEP",   FEP,   CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("FEPB",  FEPB,  CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("MI",    MI,    CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("XHH",   XHH,   CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ZW2",   ZW2,   CONST_CS|CONST_PERSISTENT);
    
    return SUCCESS;
}

// Called when this module is shutdown by php
PHP_MSHUTDOWN_FUNCTION(gnuae)
{
    
    // UNREGISTER_INI_ENTRIES();
    
    return SUCCESS;
}

// Called after each request
PHP_RINIT_FUNCTION(gnuae)
{
    gui_init();

    // GNUAE_G(items) = malloc(sizeof(item_t) * 10);
    GNUAE_G(count) = 0;
    
    return SUCCESS;
}

PHP_FUNCTION(nec_volt_loss)
{
#if 0
  double amps, temp;
  long distance, awg, conductors;
  
  if (zend_parse_parameters(5 TSRMLS_CC, "llddl", &distance, &awg, &amps, &temp, &conductors) == FAILURE) {
    WRONG_PARAM_COUNT;
  }
  // RETURN_DOUBLE(nec_volt_lost(distance, awg, amps, temp, conductors));
  // RETURN_DOUBLE(nec_volt_lost(140, 2, 23.4, 56.7, 2));

  php_printf("<p>VOLT_LOSS: %ld, %ld, %f, %f, %ld<p>", distance, awg, amps, temp, conductors);
#endif
  //nec_volt_lost(140, 2, 23.4, 56.7, 2);
  RETURN_DOUBLE(-1.1);
}

PHP_FUNCTION(nec_volt_drop)
{
  double volts, amps, temp;
  long distance, awg, conductors;
  
  if (zend_parse_parameters(6 TSRMLS_CC, "lldddl", &awg, &distance, &volts, &amps, &temp, &conductors) == FAILURE) {
    WRONG_PARAM_COUNT;
  }
  
  // php_printf("<p>VOLT_LOSS: %ld, %ld, %f, %f, %ld<p>", distance, awg, amps, temp, conductors);
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
  
  php_printf("nec_amps called!");
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
  
  if (zend_parse_parameters(1 TSRMLS_CC, "d", &amps) == FAILURE) {
    WRONG_PARAM_COUNT;
  }
  
  RETURN_DOUBLE(nec_ampacity(amps));
}

PHP_FUNCTION(nec_crystal_comp)
{
  double temp;
  
  if (zend_parse_parameters(1 TSRMLS_CC, "d", &temp) == FAILURE) {
    WRONG_PARAM_COUNT;
  }

  //  php_printf("FOO %d", temp);
  
  //  RETURN_DOUBLE(nec_crystal_comp(temp));
  //  RETURN_DOUBLE(12345.67);
  RETURN_DOUBLE(-1.1);
}

PHP_FUNCTION(nec_over_current)
{
  long strings;
  double isc;
  
  if (zend_parse_parameters(2 TSRMLS_CC, "ld", &strings, &isc) == FAILURE) {
    WRONG_PARAM_COUNT;
  }
  
  //  RETURN_DOUBLE(nec_over_current(strings, isc));
  RETURN_DOUBLE(-1.1);
}

PHP_FUNCTION(nec_find_gauge)
{
  double volts, amps, temp;
  long distance, conductors;
  
  if (zend_parse_parameters(5 TSRMLS_CC, "ldddl", &distance, &volts, &amps, &temp, &conductors) == FAILURE) {
    WRONG_PARAM_COUNT;
  }

  RETURN_LONG(nec_find_gauge(distance, volts, amps, temp, conductors));
}

PHP_FUNCTION(nec_find_conduit)
{
  long conduittype, wiretype;
  long awg, conductors;
  
  if (zend_parse_parameters(4 TSRMLS_CC, "llll", &awg, &conductors, &wiretype, &conduittype) == FAILURE) {
    WRONG_PARAM_COUNT;
  }
  
  RETURN_DOUBLE(nec_find_conduit(awg, conductors, wiretype, conduittype));
}

PHP_FUNCTION(nec_wire_ampacity)
{
  long awg, temp, conductors, conduit, wtype;
  //  zval *wiretype;
  zval *arr, **data;
  HashTable *arr_hash;
  HashPosition pointer;
  int array_count;
  
  if (zend_parse_parameters(5 TSRMLS_CC, "lllll", &awg, &temp, &conductors, &conduit, &wtype) == FAILURE) {
    WRONG_PARAM_COUNT;
  }

#if 0
  switch (Z_TYPE_P(wiretype)) {
  case IS_RESOURCE:
    php_printf("Resource\n");
    break;
  case IS_STRING:
    php_printf("String: ");
    PHPWRITE(Z_STRVAL_P(wiretype), Z_STRLEN_P(wiretype));
    php_printf("\n");
    break;
  case IS_ARRAY:
    php_printf("ARRAY\n");
    arr_hash = Z_ARRVAL_P(arr);
#if 0
    //    array_count = zend_hash_num_elements(arr_hash);
    php_printf("The array passed contains %d elements\n", array_count);
    for(zend_hash_internal_pointer_reset_ex(arr_hash, &pointer);
        zend_hash_get_current_data_ex(arr_hash, (void**) &data, &pointer) == SUCCESS; zend_hash_move_forward_ex(arr_hash, &pointer)) {
      if (Z_TYPE_PP(data) == IS_STRING) {
         PHPWRITE(Z_STRVAL_PP(data), Z_STRLEN_PP(data));
         php_printf("\n");
      }
    }
#endif
    break;
  }
#endif
  
  //  php_printf("<p>Got to here !!<p>");
  RETURN_DOUBLE(nec_wire_ampacity(awg, temp, conductors, conduit, (wiretype_t)wtype));
}

PHP_FUNCTION(nec_awg_pv2pv)
{
  long distance, conductors;
  double amps, temp, volts;

  if (zend_parse_parameters(5 TSRMLS_CC, "ldddl", &distance, &volts, &amps, &temp, &conductors) == FAILURE) {
    WRONG_PARAM_COUNT;
  }
  
  //  php_printf("<p>AWG_PV2PV: %ld, %f, %f, %f, %ld<p>", distance, volts, amps, temp, conductors);
  RETURN_LONG(nec_awg_pv2pv(distance, volts, amps, temp, conductors));
}

PHP_FUNCTION(nec_awg_pv2combiner)
{
  long distance, conductors;
  double volts, amps, temp;

  if (zend_parse_parameters(5 TSRMLS_CC, "ldddl", &distance, &volts, &amps, &temp, &conductors) == FAILURE) {
    WRONG_PARAM_COUNT;
  }
  
  RETURN_LONG(nec_awg_pv2combiner(distance, volts, amps, temp, conductors));
}

PHP_FUNCTION(nec_awg_combiner2charger)
{
  long distance, conductors;
  double volts, amps, temp;

  if (zend_parse_parameters(5 TSRMLS_CC, "ldddl", &distance, &volts, &amps, &temp, &conductors) == FAILURE) {
    WRONG_PARAM_COUNT;
  }
  
  RETURN_LONG(nec_awg_combiner2charger(distance, volts, amps, temp, conductors));
}

PHP_FUNCTION(nec_awg_wind2charger)
{
  long distance, conductors;
  double volts, amps, temp;

  if (zend_parse_parameters(5 TSRMLS_CC, "ldddl", &distance, &volts, &amps, &temp, &conductors) == FAILURE) {
    WRONG_PARAM_COUNT;
  }
  
  RETURN_LONG(nec_awg_wind2charger(distance, volts, amps, temp, conductors));
}

PHP_FUNCTION(nec_awg_charger2battery)
{
  long distance, conductors;
  double volts, amps, temp;

  if (zend_parse_parameters(5 TSRMLS_CC, "ldddl", &distance, &volts, &amps, &temp, &conductors) == FAILURE) {
    WRONG_PARAM_COUNT;
  }
  
  RETURN_LONG(nec_awg_charger2battery(distance, volts, amps, temp, conductors));
}

PHP_FUNCTION(nec_awg_battery2inverter)
{
  long distance, conductors;
  double volts, amps, temp;

  if (zend_parse_parameters(5 TSRMLS_CC, "ldddl", &distance, &volts, &amps, &temp, &conductors) == FAILURE) {
    WRONG_PARAM_COUNT;
  }
  
  RETURN_LONG(nec_awg_battery2inverter(distance, volts, amps, temp, conductors));
}

PHP_FUNCTION(nec_find_ground)
{
  RETURN_DOUBLE(-1.1);
}

PHP_FUNCTION(gui_init)
{
    gui_init();
}

// This is only used to change the default password for testing
PHP_FUNCTION(gui_init_db)
{
    char *str;
    int len;
    zval *result = malloc(sizeof(zval));
    
    if (zend_parse_parameters(1 TSRMLS_CC, "s", &str, &len) == FAILURE) {
	WRONG_PARAM_COUNT;
    }

    gui_init_db(str);
}

PHP_FUNCTION(gui_new_project)
{
    long projid = 0;
    char *name = 0, *description = 0;
    // table_e type;
    long name_len = 0, des_len = 0;
    char *location = 0;
    long location_len = 0;
    double wind = 0.0, hours = 0.0, speed = 0.0;
    double latitude = 0.0, longitude = 0.0;
    project_t proj;

    if (zend_parse_parameters(8 TSRMLS_CC, "ss|dddsdd",
			      &name, &name_len,
			      &description, &des_len,
			      &hours, &wind, &speed,
			      &location, &location_len,
			      &latitude, &longitude) == FAILURE) {
     	WRONG_PARAM_COUNT;
    }
    if (name) {
	proj.name = strndup(name, name_len);
    } else {
	proj.name = "none";
    }
    
    if (description) {
	proj.description = strndup(description, des_len);
    } else {
	proj.description = "none";
    }
    
    if (location) {
	proj.location = strndup(location, des_len);
    } else {
	proj.location = "none";
    }
    
    proj.sunhours = hours;
    proj.windhours = wind;
    proj.windspeed = speed;
    proj.latitude = latitude;
    proj.longitude = longitude;

    projid = gui_new_project(&proj);
    
    RETURN_LONG(projid);
}

PHP_FUNCTION(gui_update_project)
{
    long projid = 0;
    char *name = 0, *description = 0;
    // table_e type;
    long name_len = 0, des_len = 0;
    char *location = 0;
    long location_len = 0;
    double wind = 0.0, hours = 0.0, speed = 0.0;
    double latitude = 0.0, longitude = 0.0;
    project_t proj;

    if (zend_parse_parameters(9 TSRMLS_CC, "lss|dddsdd",
			      &projid,
			      &name, &name_len,
			      &description, &des_len,
			      &hours, &wind, &speed,
			      &location, &location_len,
			      &latitude, &longitude) == FAILURE) {
     	WRONG_PARAM_COUNT;
    }
    if (name) {
	proj.name = strndup(name, name_len);
    } else {
	proj.name = "none";
    }
    
    if (description) {
	proj.description = strndup(description, des_len);
    } else {
	proj.description = "none";
    }
    
    if (location) {
	proj.location = strndup(location, des_len);
    } else {
	proj.location = "none";
    }
    
    proj.sunhours = hours;
    proj.windhours = wind;
    proj.windspeed = speed;
    proj.latitude = latitude;
    proj.longitude = longitude;

    gui_update_project(projid, &proj);
    
    RETURN_BOOL(1);
}

// Return an array of the project data.
PHP_FUNCTION(gui_get_project)
{
    char *str;
    int len;
    long id;
    zval *result = malloc(sizeof(zval));
    
    if (zend_parse_parameters(2 TSRMLS_CC, "l|s", &id, &str, &len) == FAILURE) {
	WRONG_PARAM_COUNT;
    }

    // php_printf("DEBUG: Looking for %d, %s!<br>\n", id, str);
    array_init(result);
    if (len && str) {
	project_t *proj = gui_get_project(id, str);
	if (proj) {
	    add_next_index_string(result, proj->name, strlen(proj->name));
	    add_next_index_string(result, proj->description, strlen(proj->description));
	    add_next_index_double(result, proj->sunhours);
	    add_next_index_double(result, proj->windhours);
	    add_next_index_double(result, proj->windspeed);
	    if (proj->location) {
		add_next_index_string(result, proj->location, strlen(proj->location));
	    } else {
		add_next_index_string(result, "none", 4);
	    }
	    add_next_index_double(result, proj->latitude);
	    add_next_index_double(result, proj->longitude);
	} else {
	    php_printf("WARNING: didn't get anything back from gui_get_project!!<br>\n");
	}
    } else {
	php_printf("Invalid paramaters!");
    }
    
    // 2nd field, 0 is no copy, 3rd field is destruct before returning
    RETURN_ZVAL(result, 0, 1);    
}

PHP_FUNCTION(gui_erase_project)
{
    char *str;
    int len;
    long projid;
    zval *result = malloc(sizeof(zval));
    
    if (zend_parse_parameters(2 TSRMLS_CC, "l|s", &projid, &str, &len) == FAILURE) {
	WRONG_PARAM_COUNT;
    }

    gui_erase_project(projid, str);
}

// GUI support callbacks
PHP_FUNCTION(gui_list_names)
{
    char *str;
    int len;
    zval *result = malloc(sizeof(zval));
    
    if (zend_parse_parameters(1 TSRMLS_CC, "s", &str, &len) == FAILURE) {
	WRONG_PARAM_COUNT;
    }

    array_init(result);
    const char **names = 0;
    if (len && str) {
	names = (const char **)gui_list_names(str);
	if (names) {
	    int i = 0;
	    while (names[i] != 0) {
		add_next_index_string(result, names[i], 1);
		names++;
	    }
	} else {
	    php_printf("WARNING: didn't get anything back from gui_list_names!<br>\n");
	}
    } else {
	php_printf("Invalid paramater for name!");
    }
    
    // 2nd field, 0 is no copy, 3rd field is destruct before returning
    RETURN_ZVAL(result, 0, 1);
}

PHP_FUNCTION(gui_add_item)
{
    char *item = 0, *description = 0;
    // table_e type;
    long item_len = 0, des_len = 0;
    long id = 0, projid = 0;
    long days = 0, hours = 0, minutes = 0;
    char *type = 0;
    long type_len = 0;
    item_t nitem;

    if (zend_parse_parameters(8 TSRMLS_CC, "ls|ssllll", &projid, &item, &item_len,
			      &description, &des_len, &type, &type_len,
			      &id, &days, &hours, &minutes) == FAILURE) {
     	WRONG_PARAM_COUNT;
    }
    if (item) {
	nitem.item = strndup(item, item_len);
    } else {
	nitem.item = "none";
    }
    
    if (description) {
	nitem.description = strndup(description, des_len);
    } else {
	nitem.description = "none";
    }
    
    //GNUAE_G(items[GNUAE_G(count)]) = nitem;
    GNUAE_G(count)++;
    
    // nitem->type = type;
    nitem.id = id;
    nitem.type = LOAD; // (table_e)type;
    nitem.days = days;
    nitem.hours = hours;
    nitem.minutes = minutes;

    gui_add_item(projid, &nitem);
    
    RETURN_LONG(GNUAE_G(count));
}

PHP_FUNCTION(gui_erase_item)
{
    char *str;
    int len;
    long id, projid;
    zval *result = malloc(sizeof(zval));
    
    if (zend_parse_parameters(3 TSRMLS_CC, "ll|s", &projid, &id, &str, &len) == FAILURE) {
	WRONG_PARAM_COUNT;
    }

    gui_erase_item(projid, id, str);
}

// GUI support callbacks
PHP_FUNCTION(gui_list_items)
{
    item_t **items = (item_t **)gui_list_items();
    zval *result = malloc(sizeof(zval));
    array_init(result);
//    GNUAE_G(items[GNUAE_G(count)]) = nitem;
    
    if (items) {
	int i = 0;
	while (items[i] != 0) {
	    zval *item = malloc(sizeof(zval));
	    array_init(item);
	    item_t *it = items[i++];
	    if (it->item) {
		add_next_index_string(item, it->item, strlen(it->item));
		free(it->item);
	    } else {
		add_next_index_string(item, "n/a", 4);
	    }
	    if (it->description) {
		add_next_index_string(item, it->description, strlen(it->description));
		free(it->description);
	    } else {
		add_next_index_string(item, "n/a", 4);
	    }

	    add_next_index_long(item, it->id);
	    add_next_index_long(item, it->days);
	    add_next_index_long(item, it->hours);
	    add_next_index_long(item, it->minutes);
	    add_next_index_zval(result, item);
//	    free(it);
	}
    }

    free(items);
    
    // add_next_index_string(result, "foo", 3);
    
    // 2nd field, 0 is no copy, 3rd field is destruct before returning
    RETURN_ZVAL(result, 0, 1);
}

PHP_FUNCTION(gui_get_data)
{
    char *table = 0;
    int table_len = 0;
    char *name = 0;
    int name_len = 0;
    long id = 0;
    zval *result = malloc(sizeof(zval));
    
    if (zend_parse_parameters(3 TSRMLS_CC, "ls|s", &id, &name, &name_len, &table, &table_len) == FAILURE) {
	WRONG_PARAM_COUNT;
    }

    // If the optional table name isn't supplied, assume it's a load
    if (table_len == 0 || table == 0) {
	table = "loads";
    }
    
    array_init(result);
    if (name_len && name) {
	if (strcmp(table, "loads") == 0) {
	    load_t *load = (load_t *)gui_get_data(id, name, table);
	    if (load) {
		add_next_index_string(result, load->name, strlen(load->name));
		add_next_index_string(result, load->description, strlen(load->description));
		add_next_index_long(result, load->type);
		add_next_index_long(result, load->group);
		add_next_index_double(result, load->voltage);
		add_next_index_double(result, load->wattage);
		add_next_index_double(result, load->amperage);
	    }
	} else if (strcmp(table, "batteries") == 0) {
	    battery_t *batt = (battery_t *)gui_get_data(id, name, table);
	    if (batt) {
		add_next_index_string(result, batt->name, strlen(batt->name));
		add_next_index_string(result, batt->manufacturer, strlen(batt->manufacturer));
		add_next_index_long(result, batt->voltage);
		add_next_index_long(result, batt->rate20);
		add_next_index_long(result, batt->rate100);
	    }
	} else if (strcmp(table, "chargers") == 0) {
	    charger_t *charger = (charger_t *)gui_get_data(id, name, table);
	    if (charger) {
		add_next_index_string(result, charger->name, strlen(charger->name));
		add_next_index_string(result, charger->manufacturer, strlen(charger->manufacturer));
		add_next_index_long(result,   charger->amperage);
		add_next_index_long(result,   charger->volts_in);
		add_next_index_long(result,   charger->volts_out);
		add_next_index_double(result, charger->efficiency);
		add_next_index_double(result, charger->openmax);
		add_next_index_long(result,   charger->lcd);
		add_next_index_long(result,   charger->MPPT);
		add_next_index_long(result,   charger->PWM);
		add_next_index_long(result,   charger->tempsensor);
		add_next_index_long(result,   charger->remote);
	    }
	} else if (strcmp(table, "inverters") == 0) {
	    inverter_t *invert = (inverter_t *)gui_get_data(id, name, table);
	    if (invert) {
		add_next_index_string(result, invert->name, strlen(invert->name));
		add_next_index_string(result, invert->manufacturer, strlen(invert->manufacturer));
		add_next_index_long(result, invert->wattage);
		add_next_index_long(result, invert->voltage);
		add_next_index_long(result, invert->LCD);
		add_next_index_long(result, invert->charger);
		add_next_index_long(result, invert->remote);
		add_next_index_long(result, invert->tempsensor);
		add_next_index_long(result, invert->sinewave);
	    }    
	} else if (strcmp(table, "pumps") == 0) {
	    pump_t *pump = (pump_t *)gui_get_data(id, name, table);
	    if (pump) {
		add_next_index_string(result, pump->name, strlen(pump->name));
		add_next_index_string(result, pump->manufacturer, strlen(pump->manufacturer));
		add_next_index_long(result, pump->wattage);
		add_next_index_long(result, pump->voltage);
		add_next_index_long(result, pump->gpm);
	    }
	} else if (strcmp(table, "centers") == 0) {
	    center_t *center = (center_t *)gui_get_data(id, name, table);
	    if (center) {
		add_next_index_string(result, center->name, strlen(center->name));
		add_next_index_string(result, center->manufacturer, strlen(center->manufacturer));
		add_next_index_long(result, center->voltage);
	    }
	} else if (strcmp(table, "combiners") == 0) {
	    combiner_t *combiner = (combiner_t *)gui_get_data(id, name, table);
	    if (combiner) {
		add_next_index_string(result, combiner->name, strlen(combiner->name));
		add_next_index_string(result, combiner->manufacturer, strlen(combiner->manufacturer));
		add_next_index_long(result, combiner->circuits);
		add_next_index_long(result, combiner->conductors);
	    }
	} else if (strcmp(table, "wire") == 0) {
	    wire_t *wire = (wire_t *)gui_get_data(id, name, table);
	    if (wire) {
		add_next_index_string(result, wire->name, strlen(wire->name));
		add_next_index_double(result, wire->area_mm);
		add_next_index_long(result,   wire->area_mils);
		add_next_index_long(result,   wire->strand_qty);
		add_next_index_double(result, wire->strand_mm);
		add_next_index_double(result, wire->strans_in);
		add_next_index_double(result, wire->dia_mm);
		add_next_index_double(result, wire->dia_in);
		add_next_index_double(result, wire->sarea_mm);
		add_next_index_double(result, wire->sarea_in);
		add_next_index_double(result, wire->uncoated_km);
		add_next_index_double(result, wire->uncoated_kft);
		add_next_index_double(result, wire->coated_km);
		add_next_index_double(result, wire->coated_kft);
		add_next_index_double(result, wire->alum_km);
		add_next_index_double(result, wire->alum_kft);
	    }
	} else if (strcmp(table, "modules") == 0) {
	    pvpanel_t *pv = ( pvpanel_t *)gui_get_data(id, name, table);
	    if (pv) {
		add_next_index_string(result, pv->name, strlen(pv->name));
		add_next_index_string(result, pv->Vintage, strlen(pv->Vintage));
		add_next_index_double(result, pv->Area);
		add_next_index_string(result, pv->Material, strlen(pv->Material));
		add_next_index_long(result,   pv->Series_Cells);
		add_next_index_long(result,   pv-> Parallel_C_S);
		add_next_index_double(result, pv->Isco);
		add_next_index_double(result, pv->Voco);
		add_next_index_double(result, pv->Impo);
		add_next_index_double(result, pv->Vmpo);
		add_next_index_double(result, pv->aIsc);
		add_next_index_double(result, pv->aImp);
		add_next_index_double(result, pv->C0);
		add_next_index_double(result, pv->C1);
		add_next_index_double(result, pv->BVoco);
		add_next_index_double(result, pv->mBVoc);
		add_next_index_double(result, pv->BVmpo);
		add_next_index_double(result, pv->mBVmp);
		add_next_index_double(result, pv->n);
		add_next_index_double(result, pv->C2);
		add_next_index_double(result, pv->C3);
		add_next_index_double(result, pv->A0);
		add_next_index_double(result, pv->A1);
		add_next_index_double(result, pv->A2);
		add_next_index_double(result, pv->A3);
		add_next_index_double(result, pv->A4);
		add_next_index_double(result, pv->B0);
		add_next_index_double(result, pv->B1);
		add_next_index_double(result, pv->B2);
		add_next_index_double(result, pv->B3);
		add_next_index_double(result, pv->B4);
		add_next_index_double(result, pv->B5);
		add_next_index_double(result, pv->d_Tc);
		add_next_index_double(result, pv->fd);
		add_next_index_double(result, pv->a);
		add_next_index_double(result, pv->b);
		add_next_index_double(result, pv->C4);
		add_next_index_double(result, pv->C5);
		add_next_index_double(result, pv->Ixo);
		add_next_index_double(result, pv->Ixxo);
		add_next_index_double(result, pv->C6);
		add_next_index_double(result, pv->C7);
		add_next_index_string(result, pv->Picture, strlen(pv->Picture));
		add_next_index_string(result, pv->Description, strlen(pv->Description));
		add_next_index_string(result, pv->Manufacturer, strlen(pv->Manufacturer));
	    }
#if 0
	} else if (strcmp(table, "prices") == 0) {
	    price_t *cost = gui_get_data(id, name, table);
	    if (cost) {
	    }
	} else if (strcmp(table, "vendors") == 0) {
	    vendor_t *vendor = gui_get_data(id, name, table);
	    if (vendor) {
	    }
#endif
	}
    } else {
	php_printf("Invalid paramater for name!");
    }

    // 2nd field, 0 is no copy, 3rd field is destruct before returning
    RETURN_ZVAL(result, 0, 1);
}

// local Variables:
// mode: C++
// indent-tabs-mode: t
// End:
