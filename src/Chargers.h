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

#ifndef __CHARGERS_H__
#define __CHARGERS_H__

// This is generated by autoconf
#include "config.h"

typedef enum { NONE, YES, NO, OPTIONAL, DEFAULT } feature_e;

typedef struct
{
  char *name;
  char *manufacturer;
  double price;
  int amperage;
  int volts_in;
  int volts_out;
  double efficiency;
  double openmax;
  feature_e lcd;
  feature_e MPPT;
  feature_e PWM;
  feature_e tempsensor;
  feature_e remote;
} charger_t;

#ifdef __cplusplus

#include <map>

namespace gnuae
{
  class Chargers
    {
    public:
      Chargers(void);
      ~Chargers(void);      
    private:
      //      std::map<std::string, chargers_t> batteries;
    };
};

extern "C" {
#else
// C API goes here
  extern charger_t chargers[];
#endif

#ifdef __cplusplus
}
#endif
  
// __CHARGERS_H__
#endif
