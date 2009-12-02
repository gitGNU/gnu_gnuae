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
#include "gnuae.h"
#include "log.h"

using namespace std;

namespace gnuae {

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
}

GnuAE::~GnuAE()
{
    // DEBUGLOG_REPORT_FUNCTION;
}

void
GnuAE::dump()
{
    // DEBUGLOG_REPORT_FUNCTION;
    _loads.dump();
    _batteries.dump();
    _pvpanels.dump();
    _centers.dump();
    _inverters.dump();
    _chargers.dump();
    _combiners.dump();
    _pumps.dump();
    _wire.dump();

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
}

} // end of gnuae namespace

// local Variables:
// mode: C++
// indent-tabs-mode: t
// End:
