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
#include <memory>

#include "gnuae.h"
#include "log.h"

#ifdef __STDC_HOSTED__
#include <sstream>
#else
#include <strstream>
#endif

using namespace std;

namespace gnuae {

static const char *types[] = {
    "Battery",
    "Center",
    "Charger",
    "Combiner",
    "Inverter",
    "Load",
    "PVPanel",
    "Pump",
    "Wire"
};

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

    _project.name = const_cast<char *>("none");
    _project.description = const_cast<char *>("none");
    _project.sunhours = 0.0;
    _project.windhours = 0.0;
    _project.windspeed = 0.0;
    _project.location = const_cast<char *>("none");
    _project.latitude = 0.0;
    _project.longitude = 0.0;
}

GnuAE::~GnuAE()
{
    // DEBUGLOG_REPORT_FUNCTION;

    closeDB();
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
        //_centers.readSQL(*this);
        _modules.readSQL(*this);
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
GnuAE::listTableNames(const char *table)
{
    // DEBUGLOG_REPORT_FUNCTION;    
    auto_ptr<vector<string> > data;
    
    if (strncmp(table, "loads", 2) == 0) {
        data = _loads.dataNames();
    } else if (strncmp(table, "centers", 2) == 0) {
        data = _centers.dataNames();
    } else if (strncmp(table, "chargers", 2) == 0) {
        data = _chargers.dataNames();
    } else if (strncmp(table, "combiners", 2) == 0) {
        data = _combiners.dataNames();
    } else if (strncmp(table, "inverters", 2) == 0) {
        data = _inverters.dataNames();
    } else if (strncmp(table, "pumps", 2) == 0) {
        data = _pumps.dataNames();
    } else if (strncmp(table, "wire", 2) == 0) {
        data = _wire.dataNames();
    } else if (strncmp(table, "modules", 2) == 0) {
        data = _modules.dataNames();
    } else if (strncmp(table, "batteries", 2) == 0) {
        data = _batteries.dataNames();
    }

    if (data.get()) {
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

// Create or redefine the overall project settings
long
GnuAE::newProject(const char *name, const char *description,
		  double sunhours, double windhours, double windspeed,
		  const char *location, double latitude, double longitude)
{
    // DEBUGLOG_REPORT_FUNCTION;
    long id;
    
    project_t *project = new project_t;
    
    project->name = const_cast<char *>(name);
    project->description = const_cast<char *>(description);
    project->sunhours = sunhours;
    project->windhours = windhours;
    project->windspeed = windspeed;
    project->location = const_cast<char *>(location);
    project->latitude = latitude;
    project->longitude = longitude;

    string query = "SELECT COUNT(id) FROM projects;";

    // Get the count of how many current projects there are
    vector<vector<string> > *result1 = Database::queryResults(query);
    vector<vector<string> >::iterator it = result1->begin();
    vector<string> &row = *it;
    id = strtol(row[0].c_str(), NULL, 0) + 1;
    
    vector<vector<string> > *result2 = 0;
    if (id > 1) {
	query = "SELECT MAX(id) FROM projects;";
	
	// Get the count of how many current projects there are
	result2 = Database::queryResults(query);
	vector<vector<string> >::iterator it = result2->begin();
	vector<string> &row = *it;
	project->id = strtol(row[0].c_str(), NULL, 0) + 1;
	id = project->id;
    } else {
	project->id = id;
    }
    
    // Add ourselves to the database
    queryInsert(project);

    delete project;

    // We can't delete the temporary memory till it's added to the database.
    delete result1;
    delete result2;
    
    return id;
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
    Database::queryInsert(str);
}

// Look up an existing project by name or ID or both.
std::auto_ptr<project_t>
GnuAE::getProject(long id, const char *name)
{
    // DEBUGLOG_REPORT_FUNCTION;
#ifdef __STDC_HOSTED__
    ostringstream  query;
#else
    ostrstream     query;
#endif
    
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
    auto_ptr<project_t> proj(new project_t);
    if (result->size()) {
	//proj = new project_t;
	//proj = (project_t *)malloc(sizeof(project_t));
	vector<string> &row = *it;
	proj->id =          strtol(row[0].c_str(), NULL, 0) + 1;
	proj->name =        strdup(row[1].c_str());
	proj->description = strdup(row[2].c_str());
	proj->sunhours  =   strtof(row[3].c_str(), NULL);
	proj->windhours =   strtof(row[4].c_str(), NULL);
	proj->windspeed =   strtof(row[5].c_str(), NULL);
	// proj->location  = strtof(row[6].c_str(), NULL);
	proj->latitude  =   strtof(row[6].c_str(), NULL);
	proj->longitude =   strtof(row[7].c_str(), NULL);
    } else {
	proj.reset();
    }

    delete result;
    
    return proj;
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
    Database::queryInsert(str);

    // Delete all the entries for this project from the
    // profiles table.
    query.str("");
    query << "DELETE FROM profiles WHERE ";
    query << " projectID = " << id;
    query << ends;

#ifdef __STDC_HOSTED__
    str = query.str().c_str();
#else
    str = query.str();
#endif
    
    return Database::queryInsert(str);
}

// Add an item to the array
long
GnuAE::addItem(long projid, item_t *nitem)
{
    // DEBUGLOG_REPORT_FUNCTION;
//    _chosen_items.push_back(nitem);

    // string query = "SELECT COUNT() FROM profiles;";
    
    queryInsert(projid, nitem);
}

long
GnuAE::addItem(long projid, const char *item, const char *description,
	       table_e type, int id, int days, int hours, int minutes)
{
    // DEBUGLOG_REPORT_FUNCTION;

    item_t nitem;
    if (item) {
	nitem.item = const_cast<char *>(item);
    } else {
	nitem.item = 0;
    }
    if (description) {
	nitem.description = const_cast<char *>(description);
    } else {
	nitem.description = 0;
    }
    nitem.type = type;
    nitem.id = id;
    nitem.days = days;
    nitem.hours = hours;
    nitem.minutes = minutes;
    
    return addItem(projid, &nitem);
}

// Update an existing item in the profile
bool
GnuAE::updateItem(long projid, item_t *item)
{
    // DEBUGLOG_REPORT_FUNCTION;
    // DEBUGLOG_REPORT_FUNCTION;
#ifdef __STDC_HOSTED__
    ostringstream  query;
#else
    ostrstream     query;
#endif

    query.str("");
    query << "UPDATE profiles SET ";
#if 0
    // FIXME: don't allow name changes for now
    if (proj->name) {
	query << "name = \'"        << item->item << "\'";
    }
#endif
    if (item->description) {
	query << " description = \'" << item->description << "\'";
    }
    query << ", type = \'" << types[item->type] << "\'";
//    query << ", quantity = "    << 0;
    query << ", hours = "    << item->hours;
    query << ", days = "    << item->days;
    query << ", minutes = "    << item->minutes;
    query << " WHERE";
    query << " projectID = " << projid;
    query << " and itemID = " << item->id;
    query << " and name = \'" << item->item << "\'";
    query << ends;
    
#ifdef __STDC_HOSTED__
    string str = query.str().c_str();
#else
    string str = query.str();
#endif
    
    // Execute the query
    return Database::queryInsert(str);
}

void *
GnuAE::getData(long id, const char *item, const char *table)
{
// DEBUGLOG_REPORT_FUNCTION;

    // If no table is specified, use the loads table as a default
    if (!table) {
	table = "loads";
    }

    void *result;
    if (strncmp(table, "loads", 2) == 0) {
	result = _loads.findEntry(item);
    } else if (strncmp(table, "batteries", 2) == 0) {
	result = _batteries.findEntry(item);
    } else if (strncmp(table, "chargers", 2) == 0) {
	result = _chargers.findEntry(item);
    } else if (strncmp(table, "inverters", 2) == 0) {
	result = _inverters.findEntry(item);
    } else if (strncmp(table, "modules", 2) == 0) {
	result = _modules.findEntry(item);
    } else if (strncmp(table, "pumps", 2) == 0) {
	result = _pumps.findEntry(item);
    } else if (strncmp(table, "centers", 2) == 0) {
	result = _centers.findEntry(item);
    } else if (strncmp(table, "combiners", 2) == 0) {
	result = _combiners.findEntry(item);
    } else if (strncmp(table, "wire", 2) == 0) {
	result = _wire.findEntry(item);
#if 0
    } else if (strcmp(table, "prices") == 0) {
	result = _prices.findEntry(item);
    } else if (strcmp(table, "vendors") == 0) {
	result = _vendors.findEntry(item);
#endif
    }
	
    return result;
}

#if 0
void *
GnuAE::getData(long projid, long id, const char *name, const char *table)
{
    // DEBUGLOG_REPORT_FUNCTION;

#ifdef __STDC_HOSTED__
    ostringstream  query;
#else
    ostrstream     query;
#endif
    
    query.str("");
    query << "SELECT * FROM " << table << " WHERE ";
    if (id != 0 && name != 0) {
	query << " itemID = " << id;
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
    item_t *item = 0;
    if (result->size()) {
	item = new item_t;
	// item = (item_t *)malloc(sizeof(item_t));
	vector<string> &row = *it;
	// ignore row[0], as it's just our project ID
	item->id =          strtol(row[1].c_str(), NULL, 0);
	item->item =        strdup(row[2].c_str());
	item->description = strdup(row[3].c_str());
//	item->quantity = strtol(row[5].c_str(), NULL, 0);
	item->days =    strtol(row[6].c_str(), NULL, 0);
	item->hours =   strtol(row[7].c_str(), NULL, 0);
	item->minutes = strtol(row[8].c_str(), NULL, 0);
    }

    if (result) {
	delete result;
    }
    
    return item;
}
#endif

// Look up an existing project by name or ID or both.
item_t *
GnuAE::getItem(long projid, long id, const char *name)
{
    // DEBUGLOG_REPORT_FUNCTION;
#ifdef __STDC_HOSTED__
    ostringstream  query;
#else
    ostrstream     query;
#endif
    item_t *item = 0;
    
    query.str("");
    query << "SELECT * FROM profiles WHERE ";
    query << "projectID = " << projid;
    if (id != 0 && name != 0) {
	query << " and itemID = " << id;
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
	item = new item_t;
	// item = (item_t *)malloc(sizeof(item_t));
	vector<string> &row = *it;
	// ignore row[0], as it's just our project ID
	item->id =          strtol(row[1].c_str(), NULL, 0);
	item->item =        strdup(row[2].c_str());
	item->description = strdup(row[3].c_str());
	if (row[4] == "Battery") {
	    item->type = BATTERY;
	} else if (row[4] == "Center") {
	    item->type = CENTER;
	} else if (row[4] == "Charger") {
	    item->type = CHARGER;
	} else if (row[4] == "Combiner") {
	    item->type = COMBINER;
	} else if (row[4] == "Inverter") {
	    item->type = INVERTER;
	} else if (row[4] == "Load") {
	    item->type = LOAD;
	} else if (row[4] == "PVPanel") {
	    item->type = PVPANEL;
	} else if (row[4] == "Pump") {
	    item->type = PUMP;
	} else if (row[4] == "Wire") {
	    item->type = WIRE;
	}
//	item->quantity = strtol(row[5].c_str(), NULL, 0);
	item->days =    strtol(row[6].c_str(), NULL, 0);
	item->hours =   strtol(row[7].c_str(), NULL, 0);
	item->minutes = strtol(row[8].c_str(), NULL, 0);
    }

    if (result) {
	delete result;
    }
    
    return item;
}

// Get a list of all the items in the profile along with their data.
auto_ptr<vector<item_t *> >
GnuAE::listItems()
{
    // DEBUGLOG_REPORT_FUNCTION;
    return listItems(0);
}

auto_ptr<vector<item_t *> >
GnuAE::listItems(long projid)
{
    // DEBUGLOG_REPORT_FUNCTION;
#ifdef __STDC_HOSTED__
    ostringstream  query;
#else
    ostrstream     query;
#endif
    auto_ptr<vector<item_t *> > items(new vector<item_t *>);

    query.str("");
    query << "SELECT * FROM profiles";
    if (projid) {
	query << " WHERE projectID = " << projid;
    }
    query << " ORDER BY name";
    query << ends;
    
#ifdef __STDC_HOSTED__
    string str = query.str().c_str();
#else
    string str = query.str();
#endif

    vector<vector<string> > *result = Database::queryResults(str);
    vector<vector<string> >::iterator it;
    if (result->size()) {
	for (it = result->begin(); it != result->end(); ++it) {
	    item_t *item = new item_t;
	    //item_t *item = (item_t *)malloc(sizeof(item_t));
	    vector<string> &row = *it;
	    // ignore row[0], as it's just our project ID
	    item->id =          strtol(row[1].c_str(), NULL, 0);
	    item->item =        strdup(row[2].c_str());
	    item->description = strdup(row[3].c_str());
	    item->days =        strtol(row[6].c_str(), NULL, 0);
	    item->hours =       strtol(row[7].c_str(), NULL, 0);
	    item->minutes =     strtol(row[8].c_str(), NULL, 0);
	    items->push_back(item);
	}
    } else {
	items.reset();
	return items;
    }

    delete result;

    return items;
}

// Erase an item fromn the profile
bool
GnuAE::eraseItem(long projid, long id, const char *name)
{
    // DEBUGLOG_REPORT_FUNCTION;
    // DELETE from projects where id=id and name = name;
#ifdef __STDC_HOSTED__
    std::ostringstream    query;
#else
    std::ostrstream       query;
#endif
    
    query.str("");
    query << "DELETE FROM profiles WHERE ";
    query << "projectID = " << projid << " and ";
    if (id != 0 && name != 0) {
	query << " itemID = " << id;
	query << " and name = \'" << name << "\'";
    } else if (id == 0 && name != 0) {
	query << " name = \'" << name << "\'";
    } else if (id != 0 && name == 0) {
	query << " itemID = " << id;
    }
    query << ends;
    
#ifdef __STDC_HOSTED__
    string str = query.str().c_str();
#else
    string str = query.str();
#endif
    
    // Execute the query
    return Database::queryInsert(str);
}

bool
GnuAE::queryInsert(long projid, vector<item_t *> data)
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
	queryInsert(projid, data[i]);
    }
    
    return true;  
}

bool
GnuAE::queryInsert(long projid, item_t *data)
{
    // DEBUGLOG_REPORT_FUNCTION;
    // Can't insert data if their is no data
    if (!data) {
	dbglogfile << "ERROR: no data to INSERT for project "
		   << projid << "!" << endl;
	return false;
    }
    
#ifdef __STDC_HOSTED__
    std::ostringstream    query;
#else
    std::ostrstream       query;
#endif
    
    query.str("");
    query << "INSERT INTO profiles () VALUES (";
    query << projid << ",";
    query << data->id << ",";
    query << "'" << data->item << "',";
    query << "'" << data->description << "',";
    query << "'" << types[data->type] << "',";
    query << 0 << ",";		// FIXME: should be quantity
    query << data->hours << ",";
    query << data->minutes << ",";
    query << data->days  << ")";
    query << ends;
    
#ifdef __STDC_HOSTED__
    string str = query.str().c_str();
#else
    string str = query.str();
#endif
    
    // Execute the query
    return Database::queryInsert(str);
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
    return Database::queryInsert(str);
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
    _modules.dump();

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
#if 0
    for (it = _chosen_items.begin(); it != _chosen_items.end(); ++it) {
        item_t *item = *it;
        cerr << "Chosen Item is: " << item->item;
        cerr << "Description" << item->description << endl;
        // cerr << "itemID: " << item->id;
        cerr << "Time: " << item->days << ":" << item->hours << ":" << item->minutes << endl;
    }
#endif
}


} // end of gnuae namespace

// local Variables:
// mode: C++
// indent-tabs-mode: t
// End:
