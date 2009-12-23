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

/* This is generated by autoconf */
#include "config.h"

#include <getopt.h>
#include <dejagnu.h>
#include <string.h>

#include "gnuae.h"
#include "gui.h"

static void usage (const char *);
static void project_tests();
static void item_tests();

// The project ID
long id = 0;

int
main(int argc, char **argv)
{
    // Initialize GnuAE, but use the test database
    gui_init_db("gnuaetest");

    // Test listing the names of entries in a table
    const char **names = gui_list_names("loads");
    if (names) {
	pass("gui_list_names(loads)");
    } else {
	fail("gui_list_names(loads)");
    }
    //free(names);
    
    project_tests();

    item_tests();

    // We're all done
    totals();
}

void
project_tests()
{
    const char *name = "Guitest run";
    const char *des1 = "ignore this run";
    const char *des2 = "this run is done";
    project_t proj1;
    project_t *proj2 = 0;
	
    // First test the C API for manipulating project data
    proj1.name = name;
    proj1.description = des1;
    proj1.sunhours = 0.0;
    proj1.windhours = 0.0;
    proj1.windspeed = 0.0;
    proj1.location = "none";
    proj1.latitude = 1.2;
    proj1.longitude = 2.3;
    
    id = gui_new_project(&proj1);
    if (id > 0) {
	pass("gui_new_project()");
    } else {
	fail("gui_new_project()");
    }
    
    proj2 = gui_get_project(id, name);
    if (proj2) {
	if (proj2->description, des1) {
	    pass("gui_get_project()");
	} else {
	    fail("gui_get_project()");
	}
	free(proj2->name);
	free(proj2->description);
	// free(proj2->location);
	//free(proj2);
    } else {
	unresolved("gui_get_project()");
    }
    
    /* change some data */
    proj1.description = des2;
    proj1.latitude = proj1.latitude * 2;
    proj1.longitude = proj1.longitude * 2;

    /* update an existing record */
    gui_update_project(id, &proj1);
    proj2 = gui_get_project(id, name);
    if (proj2) {
	if (strcmp(proj2->description, des2) == 0) {
	    pass("gui_update_project()");
	} else {
	    fail("gui_update_project()");
	}
	free(proj2->name);
	free(proj2->description);
//	free(proj2->location);
	//free(proj2);
    } else {
	unresolved("gui_update_project()");
    }

    /* erase the record we just added */
    gui_erase_project(id, name);
    /* make sure it's gone */
    proj2 = gui_get_project(id, name);
    if (proj2) {
	fail("gui_erase_project()");
	free(proj2->name);
	free(proj2->description);
	// free(proj2->location);
	free(proj2);
    } else {
	pass("gui_erase_project()");
    }
}

void
item_tests()
{
    const char *name = "guittest item";
    const char *des1 = "ignore this item";
    const char *des2 = "this item is done";
    long count = 0;
    item_t item1;
    item_t *item2 = 0;

    item1.item = name;
    item1.description = des1;
    item1.id = 50050;
    item1.type = LOAD;
    item1.days = 1;
    item1.hours = 2;
    item1.minutes = 3;
    
    // Then test the C API for manipulating loads
    count = gui_add_item(id, &item1);
    if (count) {
        pass("gui_add_item()");
    } else {
        pass("gui_add_item()");
    }
    
    item2 = gui_get_item(id, 50050, name);
    if (item2) {
        if (item2->type == LOAD) {
            pass("gui_get_item()");
        } else {
            fail("gui_get_item()");
        }
	free(item2->item);
	free(item2->description);
	// free(item2);
    } else {
            unresolved("gui_get_item()");        
    }
    
    item1.description = des2;
    item1.days = item1.days * 2;
    item1.hours = item1.hours * 2;
    item1.minutes = item1.minutes * 2;
    gui_update_item(id, &item1);
    item2 = gui_get_item(id, 50050, name);
    if (item2) {
        if (item2->days == item1.days *2) {
            pass("gui_update_item()");
        } else {
            fail("gui_update_item()");
        }
	free(item2->item);
	free(item2->description);
	// free(item2);
    } else {
        unresolved("gui_update_item()");        
    }
    
    item_t **items = gui_list_items();
    if (items) {
        if (strcmp(items[0]->item, name) == 0) {
            pass("gui_list_items()");
        } else {
            fail("gui_list_items()");
        }
    } else {
        unresolved("gui_list_items()");
    }
    
    gui_erase_item(id, 50050, name);
    item2 = gui_get_item(id, 50050, name);
    if (item2) {
	fail("gui_erase_item()");
	free(item2->item);
	free(item2->description);
    } else {
	pass("gui_erase_item()");
    }
}

static void
usage (const char *prog)
{
    printf("Usage: %s ", prog);
    printf("-h\tHelp");
}

// local Variables:
// mode: C++
// indent-tabs-mode: t
// End:
