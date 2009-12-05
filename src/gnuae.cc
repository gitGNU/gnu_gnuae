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

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib>
#include <vector>
#include "gnuae.h"
#include "log.h"

using namespace std;

namespace gnuae {

static LogFile& dbglogfile = LogFile::getDefaultInstance();

GnuAE&
GnuAE::getDefaultInstance()
{
    // DEBUGLOG_REPORT_FUNCTION;
    static GnuAE gae;
    return gae;
}    

GnuAE::GnuAE() 
    : _usesql(false),
      _usecsv(false)
{
    // DEBUGLOG_REPORT_FUNCTION;
    char *home = getenv("HOME");
    if (home) {
        // The default data directory is the user's home config directory.
        _datadir = home;
        _datadir += "/.gnuae";
    } else {
        _datadir = "/etc/gnuae/";
    }

    _project.name = "none";
    _project.description = "none";
    _project.sunhours = 0;
    _project.windhours = 0;
    _project.windspeed = 0;
    _project.location = "none";
    _project.latitude = 0.0;
    _project.longitude = 0.0;
}

GnuAE::~GnuAE()
{
    // DEBUGLOG_REPORT_FUNCTION;
}

bool
GnuAE::loadData()
{
    // DEBUGLOG_REPORT_FUNCTION;
    if (_usecsv) {
        dbglogfile << "Loading CSV files as data source." << endl;
        _loads.readLoadsCSV();
        dbglogfile << "Loaded " << _loads.dataSize() << "records from loads table." << endl;
    } else {
        dbglogfile << "Loading from SQL Database as data source." << endl;
        _loads.readLoadsSQL(*this);
        _inverters.readSQL(*this);
        _batteries.readSQL(*this);
        _centers.readSQL(*this);
        _pvpanels.readSQL(*this);
        _chargers.readSQL(*this);
        _combiners.readSQL(*this);
        _pumps.readSQL(*this);
        // Wire data is static, and in the NEC spec, so it's not in
        // the SQL database or CSV files.
        // _wire.readSQL(*this);
    }

}

// As this function is to support the GUIs, which are usually only C
// based, we return a C array instead of an std::vector of strings.
const char **
GnuAE::list_names(const char *table)
{
    // DEBUGLOG_REPORT_FUNCTION;    
    vector<string> *data = 0;
    
    if (strncmp(table, "load", 2) == 0) {
        data = _loads.dataNames();
    } else if (strncmp(table, "center", 2) == 0) {
        data = _centers.dataNames();
    } else if (strncmp(table, "charger", 2) == 0) {
        data = _chargers.dataNames();
    } else if (strncmp(table, "combiner", 2) == 0) {
        data = _combiners.dataNames();
    } else if (strncmp(table, "inverter", 2) == 0) {
        data = _inverters.dataNames();
    } else if (strncmp(table, "pump", 2) == 0) {
        data = _pumps.dataNames();
    } else if (strncmp(table, "wire", 2) == 0) {
        data = _wire.dataNames();
    } else if (strncmp(table, "pvpanel", 2) == 0) {
        data = _pvpanels.dataNames();
    } else if (strncmp(table, "battery", 2) == 0) {
        data = _batteries.dataNames();
    }

    if (data) {
        const char **result = new const char *[data->size()+1];
        vector<string>::iterator it;
        int i = 0;
        for (it = data->begin(); it != data->end(); ++it) {
            result[i++] = (*it).c_str();
        }
        // Terminate the array, since we're not using std::vector
        result[i] = 0;
        return result;
    }

    return 0;
}

void *
GnuAE::getLoadData(const char *item)
{
    // DEBUGLOG_REPORT_FUNCTION;
    return _loads.findEntry(item);
}

// Create or redefine the overall project settings
void
GnuAE::newProject(std::string &name, std::string &description, int sunhours,
                  int windhours, int windspeed, std::string &location,
                  double latitude, double longitude)
{
    // DEBUGLOG_REPORT_FUNCTION;
}

// Add an item to the array
void
GnuAE::addItem(string &item, string &description, GnuAE::table_e type,
              int id, int days, int hours, int minutes)
{
    // DEBUGLOG_REPORT_FUNCTION;
    item_t *nitem = new item_t;
    
    nitem->item = item.c_str();
    nitem->description = description.c_str();
    // nitem->type = type;
    nitem->id = id;
    nitem->days = days;
    nitem->hours = hours;
    nitem->minutes = minutes;
    
    _chosen_items.push_back(nitem);
}

void
GnuAE::dump()
{
    // DEBUGLOG_REPORT_FUNCTION;
    _loads.dump();
    _batteries.dump();
    _centers.dump();
    _inverters.dump();
    _chargers.dump();
    _combiners.dump();
    _pumps.dump();
    _wire.dump();
    _pvpanels.dump();

    if (_usesql) {
        cerr << "Using SQL Queries" << endl;
    } else {
        cerr << "Not using SQL Queries" << endl;
    }

    if (_usecsv) {
        cerr << "Using CSV files to load memory" << endl;
    } else {
        cerr << "Using SQL Queries to load memory" << endl;
    }
    cerr << "Project name: " << _project.name << endl;
    cerr << "Description:" << _project.description << endl;
    cerr << "Hours of sun per day: " << _project.sunhours;
    cerr << ", Hours of wind per day: " << _project.windhours;
    cerr << ", Average wind speed: " << _project.windspeed << endl;
    cerr << "Latitude: " << _project.latitude;
    cerr << ", Longitude: " << _project.longitude;
    cerr << ", Location: " << _project.location << endl;

    std::vector<item_t *>::iterator it;
    for (it = _chosen_items.begin(); it != _chosen_items.end(); ++it) {
        item_t *item = *it;
        cerr << "Chosen Item is: " << item->item;
        cerr << "Description" << item->description << endl;
        // cerr << "itemID: " << item->id;
        cerr << "Time: " << item->days << ":" << item->hours << ":" << item->minutes << endl;
    }
}


} // end of gnuae namespace

// local Variables:
// mode: C++
// indent-tabs-mode: t
// End:
