// 
//   Copyright (C) 2004 Free Software Foundation, Inc.
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program; if not, write to the Free Software
//   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//

// Power Loss = Voltage drop as a percentage x load in amps
//

// This is generated by autoconf
#include "config.h"

#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cmath>

#include "Centers.h"

using namespace std;
using namespace gnuae;

extern "C" {
  
  center_t centers[] = {
    { "None",                      "None",       0.0, 0 },
    { "Trace SW4024/S",            "Xantrax", 4995.0, 24 },
    { "Trace SW4048/S",            "Xantrax", 4995.0, 48 },
    { "Trace SW5548/S",            "Xantrax", 5695.0, 48 },
    { "Trace SW4024/D",            "Xantrax", 8995.0, 24 },
    { "Trace SW4048/D",            "Xantrax", 9137.0, 48 },
    { "Trace SW5548/D",            "Xantrax", 9999.0, 48 },
    { "Trace DR1512/S",            "Xantrax", 1979.0, 12 },
    { "Trace DR1512/D",            "Xantrax", 3637.0, 12 },
    { "Trace DR2412/S",            "Xantrax", 2295.0, 12 },
    { "Trace DR2412/D",            "Xantrax", 4337.0, 12 },
    { "Trace DR1524/S",            "Xantrax", 1879.0, 24 },
    { "Trace DR1524/D",            "Xantrax", 3529.0, 24 },
    { "Trace DR2424/S",            "Xantrax", 2295.0, 24 },
    {                0,                    0,      0,  0 }
  };
};
