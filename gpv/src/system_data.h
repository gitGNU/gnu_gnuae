/*
 *   Copyright (C) 2004 Free Software Foundation, Inc.
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
//#ifdef  __SYSTEM_DATA_H__
//#define __SYSTEM_DATA_H__

/* This is generated by autoconf */
#include "config.h"

#include <stdio.h>

int read_system(const char *filespec);
int write_system(const char *filespec);

struct wire_data
{
  int distance;
  int awg;
  int conductors;
};

typedef struct
{
  struct wire_data pv2pv;
  struct wire_data combiner2charger;
  struct wire_data wind2charger;
  struct wire_data charger2battery;
  struct wire_data battery2invert;
  struct wire_data invert2bld120;
  struct wire_data invert2bld12;
  struct wire_data invert2bld24;
  struct wire_data ground;
} wire_data_t;

void read_system_wiring(FILE *, wire_data_t *data);
void write_system_wiring(FILE *, wire_data_t *data);

/* eof __SYSTEM_DATA_H__ */
//#endif
