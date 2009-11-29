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

#ifndef __NEC_TABLES_H__
#define __NEC_TABLES_H__

#include "config.h"

#ifdef HAVE_VALUES_H
#include <values.h>
#endif

const float FEEDERDROP   = 5.0;     // The allowable percentage for feeder lines
const float BRANCHDROP   = 3.0;     // The allowable percentage for branch lines
const float COPPERDROP   = 12.9;    // The Approximate K for copper
const float ALUMINUMDROP = 21.2;    // The Approximate K for copper
const float COPPERTEMP   = 0.00323; // The temperature factor for copper
const float ALUMINUMTEMP = 0.00330; // The temperature factor for copper
const float MAXCURRENT   = 1.25;    // This is the NEC max current factor
const float MAXAMPICITY  = 1.56;    // This is the NEC wire ampicity factor
const int   NOMINALTEMP  = 75;      // The Celcius temperature NEC Table 8 uses

//const double awglist[] = { 18, 16, 14, 12, 10, 8, 6, 4, 3, 2, 1,
//                        -1, -2, -3, -4,
//                        250, 300, 350, 400, 500, 600
//};


/*
  This enum contains bit mask values for the wire types. We use
  bitmaps because each table has columns that support multiple wire types..
 */
typedef enum { NOTYPE=0, RHH=1, RHW=2, RHW2=4, THHN=8, THHW=32, THW=64, THW2=128,
                THWN=256, THWN2=512, XHHW=1024, XHHW2=2048, SE=4096,
                USE=8192, USE2=16384, TW=32768, UF=65536, TBS=131072,
                SA=262144, SIS=524288, FEP=1048576, FEPB=2097152,
                MI=4194304, XHH=8388608, ZW2=16777216 } wiretype_t;

struct wiredata 
{
  unsigned int typeflags;
  float value;
};


typedef enum { NOMETAL, COPPER, ALUMINUM } wiremetal_t;

typedef enum { EMT, ENT, FMC, IMC, LFNC_B, LFNC_A, LFMC, RMC, RNC,
               PVC_80, PVC_40, PVC_A, PVC_EB } conduit_type_t;

/*
  NEC Table 690.7: Voltage correction factors for crystaline and
  multicrystaline silicon PV modules.
*/
struct nec_table_690_7
{
  int hightempC;
  int lowtempC;
  float compensation;
  int hightempF;
  int lowtempF;
};

/* NEC Table 8: DC resistance @ 167F (75C), 1000 feet stranded */
struct nec_table8
{
  int awg;
  int conductors;
  float mils;
  float dia;
  float uncoated;
  float coated; 
  float aluminum;
};

/* NEC Table 9: AC resistance 3 phase @ 167F (75C), 1000 feet stranded.
   Ohms to Neutral per 1000 feet.
*/
struct conduit_type 
{
  float pvc;
  float aluminum;
  float steel;
};

struct nec_table9
{
  int awg;
  struct conduit_type Xl;
  struct conduit_type copper;
  struct conduit_type aluminum;
  struct conduit_type copperZ;
  struct conduit_type aluminumZ;
};

/*
  NEC Table 310.11. This is the derating for the number of
  conductors in a conduit.
*/
struct nec_table_310_11
{
  int lowconductors;
  int highconductors;
  float adjust;
};

/*
  NEC Table 310.15(B)(2)(a). Adjustment factors for more than Three
  Current Carrying conductors in a Raceway or Cable.
 */
struct nec_table_310_15B2
{
  int lowconductors;
  int highconductors;
  float adjust;
};
/*
  NEC Table 310.15(b)(6): Conductor types and sizes for 120/240 volt,
  3 wire, single-phase dwelling services and feeders. Conductor types
  RHH, RHW, RHW-2, THHN, THHW, THW, THW-2, THWN, THWN-2,
  XHHW. XHHW-2, SE, USE, USE-2.
*/
struct nec_table_310_15B6
{
  int copper;
  int aluminum;
  float maxcurrent;
};

/*
  NEC Table 310.16: Allowable ampacities of Insulated conductors rated
  0 through 2000 volts. Not more than 3 current carrying conductors in
  raceway, cable, or buried. Based on ambient temperature of
  86F. (30C)
 */
struct nec_table_310_16
{
  int awg;
  float R60C_140F;
  float R75C_167F;
  float R90C_194F;
};

#if 0
struct nec_table_310_16 _table_310_16[] =
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
#endif

/*
  Correction factors for temperature
*/
struct derate
{
  int lowtempC;
  int hightempC;
  float R60C_140F;
  float R75C_167F;
  float R90C_194F;
  int lowtempF;
  int hightempF;
};

#if 0
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
#endif

/*
  NEC Table 690.31(C): Temperature correction factors for flexible
  cables on the moving parts of a tracking PV array.
 */
struct nec_table_690_31C
{
  int lowtempC;
  int hightempC;
  float R60C_140F;
  float R75C_167F;
  float R90C_194F;
  float R105C_221F;
  int lowtempF;
  int hightempF;
};

struct nec_table4
{
  float tradesize;
  float id;
  float area;
  float area60;
  float wire1;
  float wire2;
  float wireover;
  
};

struct nec_table5
{
  int type;
  int awg;
  float dia;
  float area;
};


#ifdef __cplusplus
extern "C" {
#endif
extern struct nec_table8 _table8[];
extern struct derate _derate[];
extern struct nec_table_690_7 _table_690_7[];
extern struct nec_table_310_11 _table_310_11[];
extern struct nec_table_310_15B2 _table_310_15B2[];
extern struct nec_table_310_15B6 _table_310_15B6[];
extern struct nec_table_310_16 _table_310_16[];
extern struct nec_table_310_16 _table_310_17[];
extern struct nec_table_690_31C _table_690_31C[];
#ifdef __cplusplus
}
#endif

#if 0
extern struct nec_table4 _nec_table4_emt;
extern struct nec_table4 _nec_table4_ent;
extern struct nec_table4 _nec_table4_fmc;
extern struct nec_table4 _nec_table4_imc;
extern struct nec_table4 _nec_table4_lfnc_b;
extern struct nec_table4 _nec_table4_lfnc_a;
extern struct nec_table4 _nec_table4_lfmc;
extern struct nec_table4 _nec_table4_rmc;
extern struct nec_table4 _nec_table4_rnc;
extern struct nec_table4 _nec_table4_pvc_80;
extern struct nec_table4 _nec_table4_pvc_40;
extern struct nec_table4 _nec_table4_pvc_a;
extern struct nec_table4 _nec_table4_pvc_eb;
extern struct nec_table4 *_nec_table4s;
#endif
 
// EOF __NEC_TABLES_H__
#endif
