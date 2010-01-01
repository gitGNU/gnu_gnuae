// 
//   Copyright (C) 2009, 2010 Free Software Foundation, Inc.
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

#ifndef __GNUAE_H__
#define __GNUAE_H__ 1

typedef enum { BATTERY, CENTER, CHARGER, COMBINER, INVERTER,
	       LOAD, PVPANEL, PUMP, WIRE} table_e; 

typedef struct {
    long id;
    char *name;
    char *description;
    double sunhours;
    double windhours;
    double windspeed;
    char *location;
    double latitude;
    double longitude;
} project_t;

typedef struct {
    char *item;           // the item name which is used as an index
			  // into all the data tables. 
    char *description;   // the description of this item, often
			  // a location of other custom data.
    table_e type;	  // the type of the item.
    int id;		  // a numerical ID, currently unused.
    int days;		  // the days per week this load item is used.
    int hours;		  // the days per week this load item is used.
    int minutes;	  // the days per week this load item is used.
} item_t;

#ifdef __cplusplus

#include <memory>

#include "Database.h"
#include "Battery.h"
#include "Centers.h"
#include "Chargers.h"
#include "Combiners.h"
#include "Inverters.h"
#include "Loads.h"
#include "PVPanel.h"
#include "Pumps.h"
#include "Wire.h"

namespace gnuae {

class Chargers;

class GnuAE : public Database {
public:
    static GnuAE& getDefaultInstance();
    GnuAE();
    ~GnuAE();
    
    void useSQL(bool x) { _usesql = x; };
    bool useSQL() { return _usesql; };

    void useCSV(bool x) { _usecsv = x; };
    bool useCSV() { return _usecsv; };

    /// Set and get the default directory for data files.
    void setDataDir(std::string &x) { _datadir = x; };
    std::string &getDataDir() { return _datadir; };

    /// Load all the data from either disk based files or an SQL
    /// database.
    bool loadData();

    const char **listTableNames(const char *table);
    void *getData(long id, const char *item, const char *table);

    // Project functions
    
    // Create a new project, returning the new project ID
    long newProject(const char *name, const char *description,
		    double sunhours, double windhours, double windspeed,
		    const char *location,
		    double latitude, double longitude);

    // Look up an existing project by name or ID or both.
    std::auto_ptr<project_t> getProject(long id, const char *name);
    
    // Update an existing project    
    bool updateProject(long id, project_t *proj);
    
    // delete a project from the database
    bool eraseProject(long id, const char *name);

    // Profile functions
    
    // Add an item to the profile
    long addItem(long projid, const char *item, const char *description,
		 table_e type, int id, int days, int hours, int minutes);
    long addItem(long id, item_t *item);

    // Get an item and it's data from the profiles database
    item_t *getItem(long projid, long id, const char *name);

    // Update an existing item in the profile
    bool updateItem(long projid, item_t *item);

    // Erase an item from the profile
    bool eraseItem(long projid, long id, const char *name);

    // Get a list of all the items in the profile along with their data.
    // std::vector<item_t *> &listItems() { return _chosen_items; };
    std::auto_ptr<std::vector<item_t *> > listItems();
    std::auto_ptr<std::vector<item_t *> > listItems(long projid);

    // Query the database to add or update data
    bool queryInsert(long projid, std::vector<item_t *> data);
    bool queryInsert(long projid, item_t *data);

    bool queryInsert(project_t *data);

    void dump();
private:
    Battery	_batteries;
    Centers	_centers;
    Chargers	_chargers;
    Combiners	_combiners;
    Inverters	_inverters;
    Loads	_loads;
    PVPanels	_modules;
    Pumps	_pumps;
    Wire	_wire;
    bool	_usesql;
    bool	_usecsv;
    std::string _datadir;
    // these are all the project related data variables
    project_t   _project;
//    std::vector<item_t *> _chosen_items;
};

} // end of gnuae namespace

#endif	// __cplusplus

#endif  // end of __GNUAE_H__

// local Variables:
// mode: C++
// indent-tabs-mode: t
// End:
