// 
//   Copyright (C) 2003, 2004, 2005, 2006, 2007, 2008,
//              2009 Free Software Foundation, Inc.
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

#ifndef __BATTERY_H__
#define __BATTERY_H__

// This is generated by autoconf
#include "config.h"
  
typedef struct
{
  char *name;
  char *manufacturer;
  double price;
  int voltage;
  int rate20;
  int rate100;
} battery_t;

#ifdef __cplusplus

#include <map>

namespace gnuae
{

class Battery {
public:
    Battery(void);
    ~Battery(void);      
    
    void dump();  
private:
    //      std::map<std::string, battery_t> batteries;
};

} // end of gnuae namespace

extern "C" {
#else
// C API goes here
  extern battery_t batteries[];
#endif

#ifdef __cplusplus
}
#endif
  
// __BATTERY_H__
#endif

// local Variables:
// mode: C++
// indent-tabs-mode: t
// End:
