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

#include "nec_tables.h"

extern "C" {
  
  const double awglist[] = { 18, 16, 14, 12, 10, 8, 6, 4, 3, 2, 1,
                             -1, -2, -3, -4,
                             250, 300, 350, 400, 500, 600
  };
  
  /*
    NEC Table 690.7: Voltage correction factors for crystaline and
    multicrystaline silicon PV modules.
  */
  struct nec_table_690_7 _table_690_7[] =
    {
      { 25,   10, 1.06, 77, 50 },
      { 9,     0, 1.10, 49, 32 },
      { -1,  -10, 1.13, 31, 14 },
      { -11, -20, 1.17, 13, -4 },
      { -21, -40, 1.25, -5, -40 },
      {   0,   0,    0,  0,   0 }
    };
  
  /* NEC Table 8: DC resistance @ 167F (75C), 1000 feet stranded */
  struct nec_table8 _table8[] = 
    {
      { 18,   7,   1620, 0.046,  7.95,    8.45 },
      { 16,   7,   2580, 0.058,  4.99,    5.29 },
      { 14,   7,   4110, 0.073,  3.14,    3.26 },
      { 12,   7,   6530, 0.92,   1.98,    2.05 },
      { 10,   7,  10380, 0.116,  1.24,    1.29 },
      { 8,    7,  16510, 0.146, 0.778,  0.8090 },
      { 6,    7,  26240, 0.184, 0.491,  0.5100 },
      { 4,    7,  41740, 0.232, 0.308,  0.3210 },
      { 3,    7,  52620, 0.260, 0.245,  0.2540 },
      { 2,    7,  66360, 0.292, 0.194,  0.2010 },
      { 1,    7,  83690, 0.332, 0.154,  0.1600 },
      { -1,  19, 105600, 0.372, 0.122,  0.1270 },
      { -2,  19, 133100, 0.418, 0.0967, 0.1010 },
      { -3,  19, 167800, 0.470, 0.0766, 0.0797 },
      { -4,  19, 211600, 0.528, 0.0608, 0.0626 },
      { 250, 37,     -1, 0.575, 0.0515, 0.0535 },
      { 300, 37,     -1, 0.630, 0.0429, 0.0446 },
      { 350, 37,     -1, 0.681, 0.0367, 0.0382 },
      { 400, 37,     -1, 0.728, 0.0321, 0.0331 },
      { 500, 37,     -1, 0.813, 0.0258, 0.0265 },
      { 600, 61,     -1, 0.893, 0.0214, 0.0223 },
      {   0,  0,      0,     0,      0,      0 }
    };
  
  /*
    NEC Table 310.11. This is the derating for the number of
    conductors in a conduit.
  */
  struct nec_table_310_11 _table310_11[] =
    {
      { 4,   6, 80 },
      { 7,   9, 70 },
      { 10, 24, 70 },
      { 25, 42, 60 },
      { 43, 85, 50 },
      { 0,   0,  0 }
    };
  
  /*
    NEC Table 310.15(B)(2)(a). Adjustment factors for more than Three
    Current Carrying conductors in a Raceway or Cable.
  */
  struct nec_table_310_15B2 _table310_15B2[] =
    {
      { 4,   6, 80 },
      { 7,   9, 70 },
      { 10, 20, 50 },
      { 21, 30, 45 },
      { 31, 40, 40 },
      { 41, MAXINT, 35 },
      { 0,   0,  0 }
    };
  
  /*
    NEC Table 310.15(b)(6): Conductor types and sizes for 120/240 volt,
    3 wire, single-phase dwelling services and feeders. Conductor types
    RHH, RHW, RHW-2, THHN, THHW, THW, THW-2, THWN, THWN-2,
    XHHW. XHHW-2, SE, USE, USE-2.
  */
  struct nec_table_310_15B6 _table_310_15B6[] =
    {
      {   4,   2, 100 },
      {   3,   1, 110 },
      {   2,  -1, 125 },
      {   1,  -2, 150 },
      {  -1,  -3, 175 },
      {  -2,  -4, 200 },
      {  -3, 250, 225 },
      {  -4, 300, 250 },
      { 250, 350, 300 },
      { 350, 500, 350 },
      { 400, 600, 400 },
      { 0,     0,   0 }    
    };
  
  /*
    NEC Table 310.16: Allowable ampacities of Insulated conductors rated
    0 through 2000 volts. Not more than 3 current carrying conductors in
    raceway, cable, or buried. Based on ambient temperature of
    86F. (30C)
  */
  struct nec_table_310_16 _table310_16[] =
    {
      { 18,   0,    0,  14 },
      { 16,   0,    0,  18 },
      { 14,   20,  20,  25 },
      { 12,   25,  25,  30 },
      { 10,   30,  35,  40 },
      {  8,   40,  50,  55 },
      {  6,   55,  65,  75 },
      {  4,   70,  85,  95 },
      {  3,   85, 115, 130 },
      {  2,   95, 115, 130 },
      {  1,  110, 130, 150 },
      { -1,  125, 150, 170 },
      { -2,  145, 175, 195 },
      { -3,  165, 200, 225 },
      { -4,  195, 230, 260 },
      {  0,    0,   0,   0 }
    };
  
  /*
    NEC Table 310.17: Allowable ampacities of Insulated conductors rated
    0 through 2000 volts in free air Based on ambient temperature of
    86F. (30C)
  */
  struct nec_table_310_16 _nec_table_310_17[] =
    {
      { 18,   0,    0,  18 },
      { 16,   0,    0,  24 },
      { 14,   25,  30,  35 },
      { 12,   30,  35,  40 },
      { 10,   40,  50,  55 },
      {  8,   60,  70,  80 },
      {  6,   80,  95, 105 },
      {  4,  105, 125, 140 },
      {  3,  120, 145, 165 },
      {  2,  140, 170, 190 },
      {  1,  165, 230, 220 },
      { -1,  195, 265, 260 },
      { -2,  225, 310, 300 },
      { -3,  260, 360, 350 },
      { -4,  300, 230, 405 },
      {  0,    0,   0,   0 }
    };
  
  /*
    Correction factors for temperature
  */
  struct derate _derate[] =
    {
      { 21, 25, 1.08, 1.05, 1.04,  70,  77 },
      { 26, 30, 1.00, 1.00, 1.00,  79,  86 },
      { 31, 35, 0.91, 0.94, 0.96,  88,  95 },
      { 36, 40, 0.82, 0.88, 0.87,  97, 104 },
      { 41, 45, 0.71, 0.82, 0.87, 106, 113 },
      { 46, 50, 0.58, 0.75, 0.82, 115, 122 },
      { 51, 55, 0.41, 0.67, 0.76, 124, 131 },
      { 56, 60,    0, 0.58, 0.71, 133, 140 },
      { 61, 70,    0, 0.33, 0.58, 142, 158 },
      { 71, 80,    0,    0, 0.41, 160, 176 },
      {  0,  0,    0,    0,    0,  0,  0 }
    };
  
  /*
    NEC Table 690.31(C): Temperature correction factors for flexible
    cables on the moving parts of a tracking PV array.
  */
  struct nec_table_690_31C _table_690_31C[] =
    {
      {  0, 30,  1.0,  1.0,  1.0,  1.0,   0,  86 },
      { 31, 35, 0.91, 0.94, 0.96, 0.97,  87,  95 },
      { 36, 40, 0.82, 0.88, 0.91, 0.93,  96, 104 },
      { 41, 45, 0.71, 0.82, 0.87, 0.89, 105, 113 },
      { 46, 50, 0.58, 0.75, 0.82, 0.86, 114, 122 },
      { 51, 55, 0.41, 0.67, 0.76, 0.82, 123, 131 },
      { 56, 60,    0, 0.58, 0.71, 0.77, 132, 140 },
      { 61, 70,    0, 0.33, 0.58, 0.68, 141, 158 },
      { 71, 80,    0,    0, 0.41, 0.58, 159, 176 },
      {  0,  0,    0,    0,    0,  0,  0 }
    };  
} // end of extern "C"
