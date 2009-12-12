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

#ifndef __GNUAE_H__
#define __GNUAE_H__ 1

typedef struct {
    const char *name;
    long id;
    const char *description;
    long sunhours;
    long windhours;
    long windspeed;
    const char *location;
    double latitude;
    double longitude;
} project_t;

typedef struct {
    const char *item;     // the item name which is used as an index
			  // into all the data tables. 
    const char *description; // the description of this item, often
			  // a location of other custom data.
    // GnuAE::table_e type;  // the type of the item.
    int id;		  // a numerical ID, currently unused.
    int days;		  // the days per week this load item is used.
    int hours;		  // the days per week this load item is used.
    int minutes;	  // the days per week this load item is used.
} item_t;

#ifdef __cplusplus

#include "Database.h"
#include "Battery.h"
#include "Centers.h"
// #include "Chargers.h"
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
    typedef enum { BATTERY, CENTER, CHARGER, COMBINER, INVERTER,
		   LOAD, PVPANEL, PUMP, WIRE} table_e; 
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

    const char **list_names(const char *table);
    void *getLoadData(const char *item);

    // Create or redefine the overall project settings
    void newProject(std::string &name, std::string &description, int sunhours,
		    int windhours, int windspeed, std::string &location,
		    double latitude, double longitude);
    // Add an item to the array
    void addItem(const char *item, const char *description, table_e type,
		 int id, int days, int hours, int minutes);
    void addItem(item_t *item);
    std::vector<item_t *> &listItems() { return _chosen_items; };

    bool queryInsert(std::vector<item_t *> data);
    bool queryInsert(item_t * data);

    void dump();
private:
    Battery	_batteries;
    Centers	_centers;
    Chargers	_chargers;
    Combiners	_combiners;
    Inverters	_inverters;
    Loads	_loads;
    PVPanels	_pvpanels;
    Pumps	_pumps;
    Wire	_wire;
    bool	_usesql;
    bool	_usecsv;
    std::string _datadir;
    // these are all the project related data variables
    project_t   _project;
    std::vector<item_t *> _chosen_items;
};

} // end of gnuae namespace

#endif	// __cplusplus

#endif  // end of __GNUAE_H__

// local Variables:
// mode: C++
// indent-tabs-mode: t
// End:
