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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_wrapper.h"
#include "NEC.h"
#include "gui.h"
#include "PVPanel.h"
#include "Loads.h"

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
    PHP_FE(gui_add_item, NULL)
    PHP_FE(gui_list_items, NULL)
    PHP_FE(gui_get_load_data, NULL)
    {NULL, NULL, NULL}
};

zend_module_entry gnuae_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_GNUAE_WORLD_EXTNAME,
    gnuae_functions,
    PHP_MINIT(gnuae),
    PHP_MSHUTDOWN(gnuae),
    PHP_RINIT(gnuae),
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

PHP_MINIT_FUNCTION(gnuae)
{

    // REGISTER_INI_ENTRIES();
    // php_error(E_WARNING, __LINE__);
    
    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(gnuae)
{
    
    // UNREGISTER_INI_ENTRIES();
    
    return SUCCESS;
}

PHP_RINIT_FUNCTION(gnuae)
{
    gui_init();
    
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
  
  if (zend_parse_parameters(2 TSRMLS_CC, "d", &amps) == FAILURE) {
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
	// } else {
	//     php_printf("ERROR: didn't get anything back from gui_list_names!\n");
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
    long type = 0, id = 0;
    long days = 0, hours = 0, minutes = 0;
    item_t *nitem = (item_t *)malloc(sizeof(item_t));

    if (zend_parse_parameters(6 TSRMLS_CC, "s|sllll", &item, &item_len,
			      &description, &des_len,
			      &id, &days, &hours, &minutes) == FAILURE) {
     	WRONG_PARAM_COUNT;
    }

    if (item) {
	nitem->item = strndup(item, item_len);
    } else {
	nitem->item = "none";
    }
    
    if (description) {
	nitem->description = strndup(description, des_len);
    } else {
	nitem->description = "none";
    }
    
    // nitem->type = type;
    nitem->id = id;
    nitem->days = days;
    nitem->hours = hours;
    nitem->minutes = minutes;

    gui_add_item(nitem);
}

// GUI support callbacks
PHP_FUNCTION(gui_list_items)
{
    item_t **items = (item_t **)gui_list_items();
    zval *result = malloc(sizeof(zval));
    array_init(result);
    
    if (items) {
	int i = 0;
	while (items[i] != 0) {
	    zval *item = malloc(sizeof(zval));
	    array_init(item);
	    item_t *it = items[i++];
	    if (it->item) {
		add_next_index_string(item, it->item, strlen(it->item));
	    } else {
		add_next_index_string(item, "n/a", 4);
	    }
	    if (it->description) {
		add_next_index_string(item, it->description, strlen(it->description));
	    } else {
		add_next_index_string(item, "n/a", 4);
	    }

	    add_next_index_long(item, it->id);
	    add_next_index_long(item, it->days);
	    add_next_index_long(item, it->hours);
	    add_next_index_long(item, it->minutes);
	    add_next_index_zval(result, item);
	}
    }
    
    // add_next_index_string(result, "foo", 3);
    
    // 2nd field, 0 is no copy, 3rd field is destruct before returning
    RETURN_ZVAL(result, 0, 1);
}

PHP_FUNCTION(gui_get_load_data)
{
    char *str;
    int len;
    zval *result = malloc(sizeof(zval));
    
    if (zend_parse_parameters(1 TSRMLS_CC, "s", &str, &len) == FAILURE) {
	WRONG_PARAM_COUNT;
    }

    array_init(result);
    if (len && str) {
	load_t *load = (load_t *)gui_get_load_data(str);
	if (load) {
	    add_next_index_string(result, load->name, strlen(load->name));
	    add_next_index_string(result, load->description, strlen(load->description));
	    add_next_index_long(result, load->type);
	    add_next_index_long(result, load->group);
	    add_next_index_double(result, load->voltage);
	    add_next_index_double(result, load->wattage);
	    add_next_index_double(result, load->amperage);
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
