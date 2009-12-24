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

#ifndef __PVPANEL_H__
#define __PVPANEL_H__

// This is generated by autoconf
#include "config.h"

typedef struct {
    char *name;
    long Vintage;                /* The year the test was done */
    double Area;                  /* The area in square feet */
    char *Material;
    int Series_Cells;
    int Parallel_C_S;
    double Isco;                  /* Short Circuit Current */
    double Voco;                  /* Open Circuit Voltage */
    double Impo;                  /* Nominal Current */
    double Vmpo;                  /* Nominal Voltage */
    double aIsc;                  /* Isc Temperature Coefficient */
    double aImp;                  /* Imp Temperature Coefficient */
    double C0;                    /* Coeficient relating Isc to irradiance */
    double C1;                    /* Coeficient relating Voc to irradiance */
    double BVoco;                 /*  */
    double mBVoc;                 /* Voc Temperature Coefficient */
    double BVmpo;                 /*  */
    double mBVmp;                 /* Vmp Temperature Coefficient */
    double n;                     /* Total cells in array */
    double C2;                    /* Coeficient relating Vmp to irradiance */
    double C3;                    /* Coeficient relating Vmp to irradiance */
    double A0;                    /*  */
    double A1;                    /*  */
    double A2;                    /*  */
    double A3;                    /*  */
    double A4;                    /*  */
    double B0;                    /*  */
    double B1;                    /*  */
    double B2;                    /*  */
    double B3;                    /*  */
    double B4;                    /*  */
    double B5;                    /*  */
    double d_Tc;                  /* temperature of cells in Celcius */
    double fd;                    /*  */
    double a;                     /*  */
    double b;                     /*  */
    double C4;                    /*  */
    double C5;                    /*  */
    double Ixo;                   /*  */
    double Ixxo;                  /*  */
    double C6;                    /*  */
    double C7;                    /*  */
    char *Picture;
    char *Description;
    /* Enhanced fields */
    char *manufacturer;           /* The company that makes this panel */  
} pvpanel_t;

extern const int LINELEN;
extern const int FIELDLEN;

#ifdef __cplusplus

#include <string>
#include <vector>
#include "NEC.h"
#include "DataType.h"
#include "Database.h"

namespace gnuae {

    class PVPanels: public DataTypeMethods<pvpanel_t> // , NEC
{
public:
    PVPanels(void);
    ~PVPanels(void);
    
    // int readCSV(std::string);
    int readModuleDataCSV(std::string filespec);
    int readModuleDataXML(std::string filespec);

    int readSQL(Database &db);    
    
    std::vector<pvpanel_t *> getPVPanels(void) { return _pvdata; };
  
    void setPVPanels(std::vector<struct pvpanel *>);
    std::vector<std::string> *names(void);
    
    // Dump the data
    void dump(void);
    void dump(pvpanel_t *pv);
    void dump(pvpanel_t *pv, bool enhanced);
    void writeDatabase(std::string);
    
    void add(pvpanel_t *pv);
    std::vector<struct pvpanel *> *search(std::string str);
    pvpanel_t *operator [] (int x) { return _pvdata[x]; };
    
    int dataSize(void) { return _pvdata.size(); };
    float fuseSize(float amps) {
	// return NEC::ampacity(amps);
    };

    float ampacity(pvpanel_t *pv, int parallel) {
	//return pv->Isco * parallel * NEC::ampacity();
    };
    float overCurrent(pvpanel_t *pv, int parallel) {
	return ampacity(pv, parallel);
    };
  
    float maxCurrent(pvpanel_t *pv, int parallel) {
	//return pv->Isco * parallel * NEC::maxCurrent();
    };
  
    float crystalCompensation(pvpanel_t *pv, float temp) {
	// return pv->Voco * NEC::crystalCompensation(temp);
    };
  
    float maxCurrent(pvpanel_t *pv, float temp) {
	return crystalCompensation(pv, temp);
    };
  
    void pv_write(const char *filespec) {
	writeDatabase(filespec);
    };
private:
    bool _debug;
    bool _enhanced;
    std::vector<pvpanel_t *> _pvdata;
};

// #if 0
// extern "C" {
// #else
//   /* C API */
//   int pv_data_size(void);
//   int read_module_data_csv(const char *filespec);
//   int read_module_data_xml(const char *filespec);
//   pvpanel_t **getPVPanels(void);
//   void pv_add(pvpanel_t *pv);
//   void pv_dump(pvpanel_t *pv);
//   pvpanel_t **search(const char *str);
//   pvpanel_t *get_pvpanel(int x);
//   int module_names(const char **);
//   void pv_write(const char *filespec);
// #endif
    
// #ifdef __cplusplus
// }
// #endif
} // end of gnuae namespace
#endif 

// __PVPANEL_H__
#endif

// local Variables:
// mode: C++
// indent-tabs-mode: t
// End:
