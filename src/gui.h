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

#ifndef __GUI_H__
#define __GUI_H__

// This is generated by autoconf
#include "config.h"

#ifdef __cplusplus

// #include "log.h"
// #include "gnuae.h"

// namespace gnuae {

// class Gui {
// public:
//     Gui(void);
//     ~Gui(void);
//     void dump();
// private:
//     //      std::map<std::string, centers_t> batteries;
// };

// } // end of gnuae namespace

extern "C" {
#else
// C API goes here
    int gui_list_names(const char *name);
    void gui_init();
#endif
    
#ifdef __cplusplus
}
#endif
  
// __GUI_H__
#endif

// local Variables:
// mode: C++
// indent-tabs-mode: t
// End:
