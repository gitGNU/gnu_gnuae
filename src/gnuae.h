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

namespace gnuae 
{

class GnuAE
{
public:
    GnuAE();
private:
    Database	_db;
    Battery	_batteries;
    Centers	_centers;
    Chargers	_chargers;
    Combiners	_combiners;
    Inverters	_inverters;
    Loads	_loads;
    PVPanels	_pvpanels;
    Pumps	_pumps;
    Wire	_wire;
};

    
} // end of gnuae namespace

#endif  // end of __GNUAE_H__

// local Variables:
// mode: C++
// indent-tabs-mode: t
// End:
