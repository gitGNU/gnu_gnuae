//
//   Copyright (C) 2004 Free Software Foundation, Inc.
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program; if not, write to the Free Software
//   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gnome.h>
#include "PVPanel.h"

#include "interface.h"
#include "support.h"
#include "Loads.h"
#include "Battery.h"
#include "Inverters.h"
#include "Combiners.h"
#include "Pumps.h"
#include "Chargers.h"
#include "Centers.h"

GtkWidget *MainWindow;
GList *Modules = NULL;

extern pvpanel_t *currentpv;
extern struct gpv_panel *panel_data[100];
extern struct gpv_panel *currentgpv;
extern battery_t *current_battery;
extern inverter_t *current_inverter;
extern pump_t *current_pump;
extern charger_t *current_charger;
extern combiner_t *current_combiner;
extern center_t *current_center;


int
main (int argc, char *argv[])
{
  char *prevname;
  int i, pvnames;
  pvpanel_t *pvp;
  char *buf;

  gnome_init ("gpv", VERSION, argc, argv);

  // pvnames = read_module_data_csv("/home/rob/projects/gnu/gnuae/data/Modules.csv");
  pvnames = read_module_data_csv("");
  // Sort the names. As there are multiple entries for each module,
  // depending on the size of the array, or the year of the tests, we
  // have to make them unique so we can reference specific test data.
  prevname = "start";
  for (i=0; i<pvnames; i++) {
    pvp = get_pvpanel(i);
#if 1
    if (strcmp(prevname, pvp->Model) != 0) {
      buf = g_malloc(strlen(pvp->Model) + 10);
      sprintf(buf, "[%d] %s", i, pvp->Model);
      Modules = g_list_append (Modules, buf);
    } else {
      //      g_print("Duplicate entry for %s (index %d)\n", pvp->Model, i);
      Modules = g_list_append (Modules, (gpointer) pvp->Model);
    }
#else
    buf = strdup(pvp->Model);
    //    sprintf(buf, "[%d] %s", i, pvp->Model);
    Modules = g_list_append (Modules, (gpointer) buf);
    //    g_print("%s (index %d)\n", pvp->Model, i);
    }
#endif
    prevname = pvp->Model;    
  }

#if 0
  current_battery = &batteries[0];
  current_inverter = &inverters[0];
  current_pump = &pumps[0];
  current_charger = &chargers[0];
  current_combiner = &combiners[0];
  current_center = &centers[0];
#endif

  //  read_loads_CSV("~/.gnuae/loads.csv");
  
/*
   * The following code was added by Glade to create one of each component
   * (except popup menus), just so that you see something after building
   * the project. Delete any components that you don't want shown initially.
   */
  MainWindow = create_MainWindow ();
  gtk_widget_show (MainWindow);
  
  gtk_main ();
  return 0;
}

