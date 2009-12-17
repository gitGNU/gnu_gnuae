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

#ifdef __STDC_HOSTED__
#include <sstream>
#else
#include <strstream>
#endif

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
    _project.sunhours = 0.0;
    _project.windhours = 0.0;
    _project.windspeed = 0.0;
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
    load_t *load = _loads.findEntry(item);
    return (void *)load;
}

// Create or redefine the overall project settings
long
GnuAE::newProject(const char *name, const char *description, double sunhours,
                  double windhours, double windspeed, const char *location,
                  double latitude, double longitude)
{
    // DEBUGLOG_REPORT_FUNCTION;
    long id;
    
    project_t *project = new project_t;
    
    project->name = name;
    project->description = description;
    project->sunhours = sunhours;
    project->windhours = windhours;
    project->windspeed = windspeed;
    project->location = location;
    project->latitude = latitude;
    project->longitude = longitude;

    string query = "SELECT COUNT(id) FROM projects;";

    // Get the count of how many current projects there are
    vector<vector<string> > *result = Database::queryResults(query);
    vector<vector<string> >::iterator it = result->begin();
    vector<string> &row = *it;
    id = strtol(row[0].c_str(), NULL, 0) + 1;

    if (id > 1) {
	query = "SELECT MAX(id) FROM projects;";
	
	// Get the count of how many current projects there are
	vector<vector<string> > *result = Database::queryResults(query);
	vector<vector<string> >::iterator it = result->begin();
	vector<string> &row = *it;
	project->id = strtol(row[0].c_str(), NULL, 0) + 1;
    } else {
	project->id = id;
    }
    
    // Add ourselves to the database
    queryInsert(project);
    
    return project->id;
}

// Update an existing project    
bool
GnuAE::updateProject(long id, project_t *proj)
{
    // DEBUGLOG_REPORT_FUNCTION;
#ifdef __STDC_HOSTED__
    ostringstream  query;
#else
    ostrstream     query;
#endif

    query.str("");
    query << "UPDATE projects SET ";
    if (proj->name) {
	query << "name = \'"        << proj->name << "\'";
    }
    if (proj->description) {
	query << ", description = \'" << proj->description << "\'";
    }
    query << ", sunhours = "    << proj->sunhours;
    query << ", windhours = "   << proj->windhours;
    query << ", windspeed = "   << proj->windspeed;
#if 0
    if (proj->location) {
	query << ", location = \'"    << proj->location << "\'";
    }
#endif
    query << ", latitude = "    << proj->latitude;
    query << ", longitude = "   << proj->longitude;
    query << " WHERE";
    query << " id = " << id;
    query << ends;
    
#ifdef __STDC_HOSTED__
    string str = query.str().c_str();
#else
    string str = query.str();
#endif
    
    // Execute the query
    Database::queryInsert(str.c_str());
}

// delete a project from the database
bool
GnuAE::eraseProject(long id, const char *name)
{
    // DEBUGLOG_REPORT_FUNCTION;
    // DELETE from projects where id=id and name = name;
#ifdef __STDC_HOSTED__
    std::ostringstream    query;
#else
    std::ostrstream       query;
#endif
    
    query.str("");
    query << "DELETE FROM projects WHERE ";
    if (id != 0 && name != 0) {
	query << "id = " << id;
	query << " and name = \'" << name << "\'";
    } else if (id == 0 && name != 0) {
	query << " name = \'" << name << "\'";
    } else if (id != 0 && name == 0) {
	query << " id = " << id;
    }
    query << ends;
    
#ifdef __STDC_HOSTED__
    string str = query.str().c_str();
#else
    string str = query.str();
#endif
    
    // Execute the query
    Database::queryInsert(str.c_str());
    
    return true;
}

// Add an item to the array
void
GnuAE::addItem(item_t *nitem)
{
    // DEBUGLOG_REPORT_FUNCTION;
    _chosen_items.push_back(nitem);

    queryInsert(nitem);
}

void
GnuAE::addItem(const char *item, const char *description, GnuAE::table_e type,
              int id, int days, int hours, int minutes)
{
    // DEBUGLOG_REPORT_FUNCTION;
    item_t *nitem = new item_t;
    nitem->item = item;
    nitem->description = description;
    // nitem->type = type;
    nitem->id = id;
    nitem->days = days;
    nitem->hours = hours;
    nitem->minutes = minutes;
    
    addItem(nitem);
}

bool
GnuAE::queryInsert(vector<item_t *> data)
{
    // DEBUGLOG_REPORT_FUNCTION;
    
    size_t	i;
    //char           query[QUERYLEN];
    //char           *ptr;
#ifdef __STDC_HOSTED__
    ostringstream  query;
#else
    ostrstream     query;
#endif
    
    if (data.size() == 0) {
	dbglogfile << "No data to insert." << endl;
	return false;
    }
    
    for (i=0; i< data.size(); i++) {
	queryInsert(data[i]);
    }
    
    return true;  
}

bool
GnuAE::queryInsert(item_t *data)
{
    // DEBUGLOG_REPORT_FUNCTION;
    
#ifdef __STDC_HOSTED__
    std::ostringstream    query;
#else
    std::ostrstream       query;
#endif
    
    query.str("");
    query << "INSERT INTO profiles () VALUES (";
    query << _project.id << ",";
    query << data->id << ",";
    query << "'" << data->item << "',";
    query << "'" << data->description << "',";
    query << 0 << ",";		// FIXME: should be quantity
    query << data->hours << ",";
    query << data->minutes << ",";
    query << data->days << ")";
    query << ends;
    
#ifdef __STDC_HOSTED__
    string str = query.str().c_str();
#else
    string str = query.str();
#endif
    
    // Execute the query
    Database::queryInsert(str.c_str());
    
    return true;
}

bool
GnuAE::queryInsert(project_t *data)
{
    // DEBUGLOG_REPORT_FUNCTION;
    
#ifdef __STDC_HOSTED__
    std::ostringstream    query;
#else
    std::ostrstream       query;
#endif
    
    query.str("");
    query << "INSERT INTO projects () VALUES (";
    query << data->id << ",";
    query << "'" << data->name << "',";
    query << "'" << data->description << "',";
    query << data->sunhours  << ",";
    query << data->windhours << ",";
    query << data->windspeed << ",";
    query << data->latitude  << ",";
    query << data->longitude << ")";
    query << ends;
    
#ifdef __STDC_HOSTED__
    string str = query.str().c_str();
#else
    string str = query.str();
#endif
    
    // Execute the query
    Database::queryInsert(str.c_str());
    
    return true;
}

// Look up an existing project by name or ID or both.
project_t *
GnuAE::getProject(long id, const char *name)
{
    // DEBUGLOG_REPORT_FUNCTION;
#ifdef __STDC_HOSTED__
    ostringstream  query;
#else
    ostrstream     query;
#endif
    project_t *proj = 0;
    
    query.str("");
    query << "SELECT * FROM projects WHERE ";
    if (id != 0 && name != 0) {
	query << "id = " << id;
	query << " and name = \'" << name << "\'";
    } else if (id == 0 && name != 0) {
	query << " name = \'" << name << "\'";
    } else if (id != 0 && name == 0) {
	query << " id = " << id;
    }
    query << ends;

#ifdef __STDC_HOSTED__
    string str = query.str().c_str();
#else
    string str = query.str();
#endif
    vector<vector<string> > *result = Database::queryResults(str);
    vector<vector<string> >::iterator it = result->begin();
    if (result->size()) {
	proj = new project_t;
	vector<string> &row = *it;
	proj->id = strtol(row[0].c_str(), NULL, 0) + 1;
	proj->name =             row[1].c_str();
	proj->description =      row[2].c_str();
	proj->sunhours  = strtof(row[3].c_str(), NULL);
	proj->windhours = strtof(row[4].c_str(), NULL);
	proj->windspeed = strtof(row[5].c_str(), NULL);
	// proj->location  = strtof(row[6].c_str(), NULL);
	proj->latitude  = strtof(row[6].c_str(), NULL);
	proj->longitude = strtof(row[7].c_str(), NULL);
    }

    return proj;
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
