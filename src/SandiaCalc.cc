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

// This is generated by autoconf
#include "config.h"

#include <iostream>
#include <cmath>
#include "PVPanel.h"
#include "SandiaCalc.h"

using namespace gnuae;
using namespace std;

SandiaCalc::SandiaCalc(void)
{
}

SandiaCalc::~SandiaCalc(void)
{
}

// Calculate Absolute Air Mass (AMa)
// Zs - Solar Zenith angle in degress
// h  - Site altitude in meters
double
SandiaCalc::calcAMa(double Zs, double h, double e)
{
  double AM, Ama;

  AM = pow(pow(cos(Zs)+0.5057*(96.08-Zs), -1.634), -1);
  
  Ama = pow(e, (-0.0001184*h))*AM;
  
  return Ama;
}

// Calculate AOI (Angle Of Incidence)
//
// AOI = cos^1{ cos(Tm) * cos (Zs) + sim(Tm) * sin(Zs) * cos(AZs-AZm) }
// 
// Tm = tilt angle of modules, 0 degreess is horizontal
// Zs = zenith angle of the sun in degrees
// AZm = azimuth angle of the modules, 0 degrees is North, 90 is East
// AZs = azimuth angle of the sun in degrees
//
double
SandiaCalc::calcAOI(double Tm, double Zs, double AZm, double AZs)
{
  double cTm = cos(Tm);         // -0.66693806165226188
  double cZs = cos(Zs);         // -0.66693806165226188
  double cAZ = cos(AZs-AZm);    // 1
  double sTm = sin(Tm);         // 0.74511316047934883
  double sZs = sin(Zs);         // 0.74511316047934883
  double aoi;
  
  aoi = (cos(cos(Tm) * cos(Zs)) + (sin(Tm) * sin(Zs) * cos(AZs - AZm)));

  cerr << "AOI = " << aoi;
  cerr << ", cTm = " << cTm;
  cerr << ", cZs = " << cZs;
  cerr << ", cAZ = " << cAZ;
  cerr << ", sTm = " << sTm;
  cerr << ", sZs = " << sZs << endl;

  cerr << "COS = " << cTm * cZs + sTm * sZs << endl;
  cerr << "POW = " << pow(aoi, -1.) << endl;
  return aoi;
}

// Calculate Irradiance Values (E = POA irradiance(W/m^2))
// Eb = Edni * cos(AOI)
// E = Eb + Ed * fd
double
SandiaCalc::calcIrradianceValues(double Edni, double aoi) 
{
  //  Eb = Edni * cos(AOI);
  //  E = Eb + Ed * fd;
}

// Calculate Cell Temperature (Tc)
// Tm = E * (e^(a + b * ws)) + Ta
// Tc = Tm + (E/1000) * dto
double
SandiaCalc::calcCellTemperature(double ws, double Ta, double dto,
                                double a, double b)
{
  double Tm;

  //  Tm = E * (e^(a + b * ws)) + Ta;
  //  Tc = Tm + (E/1000) * dto;
}

// Calculate Absolute Air Mass (AMa)
// AM = (cos(Zs) + 0.5057 * (96.08 - Zs)^ - 1.634))^ - 1
// AMa = e^(-0.0001184  h) * AM
double
SandiaCalc::calcAbsAirMass(double Zs, double h)
{
  double AM;
  //  AM = (cos(Zs) + 0.5057 * (96.08 - Zs)^ - 1.634)^ - 1;
  //  Ama = e^(-0.0001184  h) * AM;
}

// Calculate f1(AMa)
// f1(Ama) = A0 + A1 * Ama + A2  * Ama^2 + A3 * Ama^3 + a4 * Ama^4
double
SandiaCalc::calcF1(double ama, double a0, double a1,
                   double a2, double a3, double a4)
{
  double f1;
  
  f1 = pow(pow(pow(a0+a1*ama+a2*ama, 2)+a3*ama, 2)+a4*ama, 4);

  return f1;
}

// Calculate f2(AOI)
// f1(AOI) = A0 + A1 * AOI + A2  * AOI^2 + A3 * AOI^3 + a4 * AOI^4
double
SandiaCalc::calcF2(double aoi, double b0, double b1, double b2,
                   double b3, double b4, double b5)
{
  double f2;
  double ba1, ba2, ba3, ba4, ba5;

  ba1 = b0+b1*aoi;
  ba2 = pow(ba1 + b2*aoi, 2);
  ba3 = pow(b3*aoi, 3);
  ba4 = pow(b4*aoi, 4);
  ba5 = pow(b5*aoi, 5);
  
  f2 = pow(pow(pow(pow(b0+b1*aoi+b2*aoi, 2)+b3*aoi, 3)+b4*aoi, 4)+b5*aoi, 5);
  //  f2 = ba2 + ba3 + ba4 +ba5;

  return f2;
}

// Calculate Isc(0) at operating temperature
// Isc(0) = Isc * ((Eb*f1(Ama)*f2(AOI)+fd*Ed)/1000)*(1+aIsc*(Tc-25))
double
SandiaCalc::calcIsco(double Eb, double f1_AMa, double f2_AOI, double fd,
                    double Ed, double aIsc, double Tc)
{
  double isco;

  isco = aIsc * (((Eb*f1_AMa*f2_AOI+fd*Ed)/1000)*(1+aIsc*(Tc-25)));

  return isco;
}

// Calculate Effective Irradiation (Ee)
// Isc(R) = Isc(0)/(1+aIsc*(Tc-25))
// Ee = Isc(R)/Isco
double
SandiaCalc::calcEffectiveIrradiance(double x)
{
}

double
SandiaCalc::calcImp(double x)
{
}

double
SandiaCalc::calcVoc(double x)
{
}

double
SandiaCalc::calcVmp(double x)
{
}

double
SandiaCalc::calcIx(double x)
{
}

double
SandiaCalc::calcIxx(double x)
{
}

SandiaCalc sc;

extern "C" {
  double
  sandia_calc_AMa(double Zs, double h, double e)
  {
    return sc.calcAMa(Zs, h, e);
  }
  double sandia_calc_AOI(double Tm, double Zs, double AZm, double AZs)
  {
    return sc.calcAOI(Tm, Zs, AZm, AZs);
  }
  
  double sandia_calc_irradiance_values(double wm, double aoi)
  {
    return sc.calcIrradianceValues(wm, aoi);
  }
  
  double sandia_calc_cell_temperature(double ws, double ta, double dto,
                                      double a, double b)
  {
    return sc.calcCellTemperature(ws, ta, dto, a, b);
  }
  
  double sandia_calc_abs_air_mass(double Zs, double h)
  {
    return sc.calcAbsAirMass(Zs, h);
  }
  
  double sandia_calc_F1(double ama, double a0, double a1, double a2,
                        double a3, double a4)
  {
    return sc.calcF1(ama, a0, a1, a2, a3, a4);
  }
  
  double sandia_calc_F2(double aoi, double b0, double b1,
                        double b2, double b3, double b4, double b5)
  {
    return sc.calcF2(aoi, b0, b1, b2, b3, b4, b5);
  }
}
