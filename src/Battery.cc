// 
//   Copyright (C) 2003, 2004, 2005, 2006, 2007, 2008,
//              2009, 2010 Free Software Foundation, Inc.
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

// This is generated by autoconf
#include "config.h"

#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cmath>

#include "log.h"
#include "gnuae.h"
#include "Battery.h"

using namespace std;

namespace gnuae {

static LogFile& dbglogfile = LogFile::getDefaultInstance();
static GnuAE& gdata = GnuAE::getDefaultInstance();

Battery::Battery()
{

};

Battery::~Battery()
{
};

int
Battery::readCSV(std::string)
{
    DEBUGLOG_REPORT_FUNCTION;
}

int
Battery::readSQL(Database &db)
{
    // DEBUGLOG_REPORT_FUNCTION;
    if (db.getState() == Database::DBOPENED) {
	string query = "SELECT * from batteries";
	vector<vector<string> > *result = db.queryResults(query);
	vector<vector<string> >::iterator it;
	for (it=result->begin(); it!=result->end(); ++it) {
	    battery_t *thisbat = new battery_t;
	    vector<string> &row = *it;
	    if (!row[1].empty()) {
		thisbat->name = strdup(row[1].c_str());
	    }
	    if (!row[2].empty()) {
		thisbat->manufacturer = strdup(row[2].c_str());
	    }
//	    thisbat->price = strtof(row[3].c_str(), NULL);
	    thisbat->voltage = strtol(row[4].c_str(), NULL, 0);
	    thisbat->rate20 = strtol(row[5].c_str(), NULL, 0);
	    thisbat->rate100 = strtol(row[6].c_str(), NULL, 0);
	    addEntry(thisbat);
	}
	delete result;
    }

    dbglogfile << "Loaded " << dataSize() << " records from batteries table." << endl;

    return dataSize();
}

void
Battery::dump()
{
    // DEBUGLOG_REPORT_FUNCTION;
    if (!dataSize()) {
	cerr << "No Battery data in memory." << endl;
    } else {
	vector<string>::iterator it;
	auto_ptr<vector<string> > loadnames = dataNames();
	for (it = loadnames->begin(); it != loadnames->end(); ++it) {
	    dump(findEntry(*it));
	}
    }
}

void
Battery::dump(battery_t *bat)
{
    // DEBUGLOG_REPORT_FUNCTION;
    if (bat) {
	dbglogfile << "Battery Name is: " << bat->name;
	dbglogfile << ", Manufacturer is: " << bat->manufacturer << endl;
	dbglogfile << "\tVoltage is: "<< bat->voltage;
	dbglogfile << ", Rate20 is: " << bat->rate20;
	dbglogfile << ", Rate100 is: " << bat->rate100 << endl;
    } else {
	dbglogfile << "No Battery data in memory." << endl;
    }
}

} // end of gnuae namespace

// local Variables:
// mode: C++
// indent-tabs-mode: t
// End:
