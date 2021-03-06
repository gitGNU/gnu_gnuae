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

#ifndef __COMBINERS_H__
#define __COMBINERS_H__

// This is generated by autoconf
#include "config.h"
  
typedef struct
{
    const char *name;
    const char *manufacturer;
    int circuits;                 /* The number of input circuits the box supports */
    int conductors;               /* Some combiner boxes have multiple output lines */
} combiner_t;

#ifdef __cplusplus

#include <map>

#include "DataType.h"
#include "Database.h"

namespace gnuae {
class Combiners : public DataTypeMethods<combiner_t> {
public:
    Combiners(void);

    ~Combiners(void);
    
    int readCSV(std::string);
    int readSQL(Database &db);
    
    void dump();
    void dump(combiner_t *comp);
private:
    //      std::map<std::string, combiners_t> batteries;
};

} // end of gnuae namespace

#endif	// end of cpluplus

// __COMBINERS_H__
#endif

// local Variables:
// mode: C++
// indent-tabs-mode: t
// End:
