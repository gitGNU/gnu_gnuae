// 
//   Copyright (C) 2009 Free Software Foundation, Inc.
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

#ifndef __GUI_H__
#define __GUI_H__

// #include "log.h"
#include "gnuae.h"

#ifdef __cplusplus

// namespace gnuae {

// class Gui {
// public:
//     Gui(void);
//     ~Gui(void);
//     void dump();
// private:
//     //      std::map<std::string, centers_t> batteries;
// };

// } // end of gnuae namespace

// C API goes here
extern "C" {
    // Initialize the gui, which loads the data
    void gui_init();
    // This is only used to change the default password for testing
    void gui_init_db(const char *dbname);
    
    // This just sets the name, but doesn't initialize anything. This
    // is primarily only used for testing, so test results don't contaminate
    // the regular database in any way.
    void gui_set_dbname(const char *name);
    
    // get a list of names for a table. This works for any of the
    // tables, including the project data and the profile data.
    const char **gui_list_names(const char *name);

    // Project functions go here

    // Add a new project to the database
    long gui_new_project(project_t *proj);
    // Update an existing project
    bool gui_update_project(long id, project_t *proj);
    // get the project data
    project_t *gui_get_project(long id, const char *name);
    // delete a project from the database
    bool gui_erase_project(long id, const char *name);

    // Profile functions go here
    
    // Add to the list of items in the profile.
    long gui_add_item(long projid, item_t *item);
    // Update the data for an existing item in the profile
    bool gui_update_item(long projid, item_t *item);
    // Get the data for a specific item in the profile
    item_t *gui_get_item(long projid, long id, const char *name);
    // delete a load from the profile database
    bool gui_erase_item(long projid, long id, const char *name);
    // Get a list of the chosen items in the profile
    item_t **gui_list_items();
    
    // List of loads stuff goes here.
    
    
}
#endif	// end of __cplusplus
  
// __GUI_H__
#endif

// local Variables:
// mode: C++
// indent-tabs-mode: t
// End:
