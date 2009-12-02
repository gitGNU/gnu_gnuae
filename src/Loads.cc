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

// Power Loss = Voltage drop as a percentage x load in amps
//

// This is generated by autoconf
#include "config.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <iterator>
#include <cmath>
#ifdef __STDC_HOSTED__
#include <sstream>
#else
#include <strstream>
#endif

#include "Loads.h"

using namespace std;
using namespace gnuae;

extern "C" {
  const char *load_strs[] =  {
    "NOLOAD",
    "AC",
    "DC"
  };
  
  const char *loadgroup_strs[]= {
  "NOGROUP",
  "HOUSEHOLD",
  "TOOLS",
  "KITCHEN",
  "DIGITAL"
  };

  const int LINELEN = 1024;
  const int FIELDLEN = 512;
  
  load_t loads[] = {
    // DC loads
    { "Wireless Phone", "Telemobile PTEL Wireless Phone",DC, HOUSEHOLD, 12.,    3., 0., 0, 1, 0.25, 1, 0 },
    { "DC Lights", "Compact Flourescent Light Bulb",     DC, HOUSEHOLD, 24.,   15., 0., 0, 1, 0.25, 1, 0 },
    { "SQ Flex Pump", "Grundfos SQ Flex Deep Well Pump", DC, HOUSEHOLD, 24.,  192., 0., 0, 1, 0.25, 1, 0 },
    { "ETA Pump", "Dankoff ETA Deep Well Pump",          DC, HOUSEHOLD, 24.,  192., 0., 0, 1, 0.25, 1, 0 },
    { "Pressure Booster", "Flowlight Pressure Booster",  DC, HOUSEHOLD, 24.,  180., 0., 0, 1, 0.25, 1, 0 },
    { "19' Refridgerator", "SunFrost 19'",               DC, HOUSEHOLD, 24.,  696., 0., 0, 1, 0.25, 1, 0 },
    { "16' Refridgerator", "SunFrost 16'",               DC, HOUSEHOLD, 24.,  696., 0., 0, 1, 0.25, 1, 0 },
    { "12' Refridgerator", "SunFrost 12'",               DC, HOUSEHOLD, 24.,  696., 0., 0, 1, 0.25, 1, 0 },
    // AC Loads
    { "AC Lights", "Compact Flourescent Light Bulb",     AC, HOUSEHOLD, 120.,  18., 0., 0, 1, 0.25, 1, 0 },
    { "Vacumn", "Old Hoover Upright Vacumn",             AC, HOUSEHOLD, 120., 800., 0., 0, 1, 0.25, 1, 0 },
    { "Stereo", "Stereo/Amp",                            AC, HOUSEHOLD, 120.,  18., 0., 0, 1, 0.25, 1, 0 },
    { "Alarm Clock", "Clock/Radio",                      AC, HOUSEHOLD, 120.,   1., 0., 0, 1, 0.25, 1, 0 },
    { "Tape Deck", "Harmon Kardon Tape Deck",            AC, HOUSEHOLD, 120.,  18., 0., 0, 1, 0.25, 1, 0 },
    { "TV", "", AC, HOUSEHOLD, 120., 18., 0., 0, 1, 0.25, 1, 0 },
    { "VCR", "", AC, HOUSEHOLD, 120., 18., 0., 0, 1, 0.25, 1, 0 },
    { "CD Player", "Harmon Kardon CD Player",            AC, HOUSEHOLD, 120., 18., 0., 0, 1, 0.25, 1, 0 },
    { "Clothes Washer", "", AC, HOUSEHOLD, 120., 18., 0., 0, 1, 0.25, 1, 0 },

    { "Dish Washer", "Apartment Sized Dish Washer",      AC, KITCHEN,   120., 687., 0., 0, 1, 0.25, 1, 0 },
    { "Coffee Grinder", "Coffe Grinder",                 AC, KITCHEN,   120.,  93., 0., 0, 1, 0.25, 1, 0 },
    { "Toaster Oven", "Toaster Oven",                    AC, HOUSEHOLD, 120., 240., 0., 0, 1, 0.25, 1, 0 },
    { "Blender", "Blender",                              AC, HOUSEHOLD, 120., 531., 0., 0, 1, 0.25, 1, 0 },
    // Tools
    { "Sewing Machine", "Singer Sewing Machine",         AC, TOOLS,     120.,  51., 0., 0, 1, 0.25, 1, 0 },
    { "Glue Gun", "Glue Gun",                            AC, TOOLS,     120.,   5., 0., 0, 1, 0.25, 1, 0 },
    { "Cordless Charger", "Dewalt 18V Battery Charger",  AC, TOOLS,     120.,  70., 0., 0, 1, 0.25, 1, 0 },
#if 0
    { "Soldering Iron", "Radio Shack Soldering Iron",    AC, TOOLS,     120.,   0., 0., 0, 1, 0.25, 1, 0 },
    { "Hand Saw", "Rotary Hand Saw",                     AC, TOOLS,     120.,   0., 0., 0, 1, 0.25, 1, 0 },
    { "Hand Drill", "Small Hand Drill",                  AC, TOOLS,     120.,   0., 0., 0, 1, 0.25, 1, 0 },
    { "Table Saw", "Table Saw",                          AC, TOOLS,     120.,   0., 0., 0, 1, 0.25, 1, 0 },
    { "Drill Press", "Drill Press",                      AC, TOOLS,     120.,   0., 0., 0, 1, 0.25, 1, 0 },
    { "Jigsaw", "Jigsaw",                                AC, TOOLS,     120.,   0., 0., 0, 1, 0.25, 1, 0 },
#endif
    { "Yaesu Charger", "Charger for Yaesu FT51",         AC, DIGITAL,   120.,   1., 0., 0, 1, 0.25, 1, 0 },
    { "Maxon Charger", "Charger for Maxon 201+3",        AC, DIGITAL,   120.,   1., 0., 0, 1, 0.25, 1, 0 },
    { "Nokia Charger", "Nokia 5660 Cell Phone Charger",  AC, DIGITAL,   120.,   3., 0., 0, 1, 0.25, 1, 0 },
    { "Laptop", "HP Omnibook6100 Laptop",                AC, DIGITAL,   120.,  24., 0., 0, 1, 0.25, 1, 0 },
    { "Laser Printer", "HP LaserJet 5MP",                AC, DIGITAL,   120., 200., 0., 0, 1, 0.25, 1, 0 },
    { "18\" LCD Monitor", "HP 1820 LCD Monitor",         AC, DIGITAL,   120.,  30., 0., 0, 1, 0.25, 1, 0 },
    { "Gateway Laptop", "gateway Solo 5150 Laptop",      AC, DIGITAL,   120.,  20., 0., 0, 1, 0.25, 1, 0 },
    { "Docking Station", "Gateway Docking Station",      AC, DIGITAL,   120.,  34., 0., 0, 1, 0.25, 1, 0 },
    { "21\" CRT", "Panisonic S21 CRT",                   AC, DIGITAL,   120., 103., 0., 0, 1, 0.25, 1, 0 },
    { "133Mhz Pentium", "133 Mgz Pentium I PC",          AC, DIGITAL,   120.,  53., 0., 0, 1, 0.25, 1, 0 },
    { "Terminal Server", "Livingston Port Master",       AC, DIGITAL,   120.,  20., 0., 0, 1, 0.25, 1, 0 },
    { "Zycel Modem", "Zycel 1496+ Modem",                AC, DIGITAL,   120.,   6., 0., 0, 1, 0.25, 1, 0 },
    { "US Robotics Modem", "56K US Robotics Modem",      AC, DIGITAL,   120.,   4., 0., 0, 1, 0.25, 1, 0 },
    { "PC Speakers", "Yamaha Speakers",                  AC, DIGITAL,   120.,   4., 0., 0, 1, 0.25, 1, 0 },
#if 0
    { "Dual 3.0Ghz Xeon", "HP wx6000, Dual Xeon PC",     AC, DIGITAL, 120., 0., 0., 0, 1, 0.25, 1, 0 },
    { "Sun Ultra 60", "Sun Ultra 60 Workstation",        AC, DIGITAL, 120., 0., 0., 0, 1, 0.25, 1, 0 },
    { "HP A500", "HP A500 PA-RISC Server",               AC, DIGITAL, 120., 0., 0., 0, 1, 0.25, 1, 0 },
    { "HP zx6000", "HP dual Itanium zx6000 Workstation", AC, DIGITAL, 120., 0., 0., 0, 1, 0.25, 1, 0 },
#endif
    { 0, 0, NOLOAD, NOGROUP, 0., 0., 0., 0, 0, 0., 0, 0 }
  };
};

Loads::Loads(void)
{
  int i;
  char *home;
  string loadfile;
  struct stat stats;

  home = getenv("HOME");

  if (home) {
    loadfile = home;
    loadfile += "/.gnuae/loads.csv";
    if (stat(loadfile.c_str(), &stats) == 0) {
      readLoadsCSV(loadfile);
      return;
    }
    loadfile = "/etc/gnuae/loads.csv";
    if (stat(loadfile.c_str(), &stats) == 0) {
      readLoadsCSV(loadfile);
      return;
    }
  }
  
  for (i=0; loads[i].name!=0; i++)
    {
      //      _loaddata.insert( make_pair( loads[i].name, (load_t *)&loads[i]) );
      addEntry(&loads[i]);
    }
}


Loads::~Loads(void)
{
}

void
Loads::dump(void)
{
  vector<string>::iterator it;
  vector<string> *loadnames;
  load_t *load;
  int i;
  
  cerr << endl << "Dumping System Loads" << endl;

  loadnames = dataNames();
  
  if (loadnames->size() == 0) {
    cerr << "No Load data in memory" << endl;
    return;
  }
  
  //    namelist[i++] = strdup("Hey Now");
  for (it = loadnames->begin(); it != loadnames->end(); it++) {
    dump(findEntry(*it));
  }
}

void
Loads::dump(struct load *entry)
{
  cerr << "Dumping System Load for " << entry->name << endl;

  if (entry->name != 0)
    cerr << "\tIs an " << load_strs[entry->type] << " device";
  else
    cerr << "\tThere is no device name" << endl;
  
  cerr << " in the " << loadgroup_strs[entry->group] << " category" << endl;
  cerr << "\tThe Quantity is " << entry->quantity << endl;
  cerr << "\tThe Voltage is " << entry->voltage;
  cerr << ", the Wattage is " << entry->wattage;
  cerr << ". The Amperage is " << entry->amperage << endl;
  cerr << "\tThis device is used for " << entry->hours << " hours and ";
  cerr << entry->minutes << " minutes per day" << endl;
  if (entry->active)
    cerr << "\tThis device is ACTIVE" << endl;
  else
    cerr << "\tThis device is INACTIVE" << endl;

  if (entry->description != NULL)
    cerr << "\tThe Description is \"" << entry->description << "\"" << endl;
  else
    cerr << "\tThere is no description" << endl;
}

// Dump the data as a comma delimited ASCII text file
void
Loads::writeLoads(string filespec)
{
  ofstream os;
  ostringstream tmpstr;
  int lines = -1;
  vector<string>::iterator it;
  vector<string> *loadnames;
  load_t *thisload;
  int i;
  char *home;
  string loadfile;
  struct stat stats;
  
  loadnames = dataNames();
  
  if (loadnames->size() == 0) {
    cerr << "No Load data in memory" << endl;
    return;
  }

  if (filespec.size() == 0) {

    home = getenv("HOME");
    
    if (home) {
      loadfile = home;
      loadfile += "/.gnuae/loads.csv";
      if (stat(loadfile.c_str(), &stats) == 0) {
        filespec = loadfile;
      } else {
        loadfile = "/etc/gnuae/loads.csv";
        if (stat(loadfile.c_str(), &stats) == 0) {
          filespec = loadfile;
        } else {
          filespec = "./data/loads.csv";
        }
      }
    }
  }

  cout << "Writing load database to:" << filespec << endl;
  
  os.open(filespec.c_str(), ios::out);

  // Write the headers so this can be imported easier into other programs, like a spreadsheet
  os << "\"name\",\"description\",\"type\",\"group\",\"voltage\",\"wattage\",\"amperage\"";
  os << "\"hours\",\"minutes\",\"days\",\"quantity\",\"active\"" << endl;
    
  for (it = loadnames->begin(); it != loadnames->end(); it++) {
    thisload = findEntry(*it);
    os << "\"" << thisload->name << "\",";
    if (thisload->description)
      os << "\"" << thisload->description << "\",";
    else
      os << "\"\",";
    
    os << "\"" << load_strs[thisload->type] << "\",";
    os << "\"" << loadgroup_strs[thisload->group] << "\",";

    os << thisload->voltage << ",";
    os << thisload->wattage << ",";
    os << thisload->amperage << ",";
    os << thisload->hours << ",";
    os << thisload->minutes << ",";
    os << thisload->days << ",";
    os << thisload->quantity << ",";
    os << thisload->active << endl;
  }

  os.close();
}

// Read the data from a comma delimited ASCII text file
int
Loads::readLoadsCSV(std::string filespec)
{
  load_t *thisload;
  char buf[LINELEN];
  float val;
  int i;
  ifstream in;
  char *home;
  string tmpbuf, loadfile;
  int lines = -1;
  struct stat stats;

  //  cerr << "Opening file: " << filespec << endl;
  if (filespec.size() == 0) {
    home = getenv("HOME");
    
    if (home) {
      loadfile = home;
      loadfile += "/.gnuae/loads.csv";
      if (stat(loadfile.c_str(), &stats) == 0) {
        filespec = loadfile;
      } else {
        loadfile = "/etc/gnuae/loads.csv";
        if (stat(loadfile.c_str(), &stats) == 0) {
          filespec = loadfile;
        }
      }
    }
  }

  cout << "Reading load database from:" << filespec << endl;

  in.open(filespec.c_str());

  clearData();

  if (!in) {
    cerr << "Couldn't open file: " << filespec << endl;
    return -1;
  }

  // Read in but ignore the first line, which are the headers in the
  // data file. We ignore those, cause we *know* what all the fields are.
  in.getline(buf, LINELEN);

  while (!in.eof())
    {
      lines++;
      // Get memory to hold the data
      thisload = new load_t;

      // Read in the name of the load
      in.getline(buf, LINELEN, ','); // Get a token from the line
      tmpbuf = buf;
      if (tmpbuf.size()) {
        // The string has double quote marks on each end, which is used by
        // the CSV format. So we drop them to have just the plain string left.
        tmpbuf.erase(0, 1);
        tmpbuf.erase(tmpbuf.size()-1, 1);
        thisload->name = new char[strlen(buf)+1];
        strcpy(thisload->name, tmpbuf.c_str());
      } else {
        return lines;
      }

      // Read in the description
      in.getline(buf, LINELEN, ','); // Get a token from the line
      tmpbuf = buf;

      if (tmpbuf == "\"\"") {
        thisload->description = NULL;
      } else {
        if (tmpbuf.size()) {
          // The string has double quote marks on each end, which is used by
          // the CSV format. So we drop them to have just the plain string left.
          tmpbuf.erase(0, 1);
          tmpbuf.erase(tmpbuf.size()-1, 1);
          thisload->description = new char[strlen(buf)+1];
          strcpy(thisload->description, tmpbuf.c_str());
        } else {
          return lines;
        }
      }

      // Read in the load type. This is either AC or DC
      in.getline(buf, LINELEN, ','); // Get a token from the line
      tmpbuf = buf;
      if (tmpbuf.size()) {
        // The string has double quote marks on each end, which is used by
        // the CSV format. So we drop them to have just the plain string left.
        tmpbuf.erase(0, 1);
        tmpbuf.erase(tmpbuf.size()-1, 1);
        if (tmpbuf == "AC")
          thisload->type = AC;
        else
          thisload->type = DC;
      }
      else {
        return lines;
      }
      
      // Read in the load group.
      in.getline(buf, LINELEN, ','); // Get a token from the line
      tmpbuf = buf;
      if (tmpbuf.size()) {
        // The string has double quote marks on each end, which is used by
        // the CSV format. So we drop them to have just the plain string left.
        tmpbuf.erase(0, 1);
        tmpbuf.erase(tmpbuf.size()-1, 1);
        if (tmpbuf == "HOUSEHOLD")
          thisload->group = HOUSEHOLD;
        if (tmpbuf == "DIGITAL")
          thisload->group = DIGITAL;
        if (tmpbuf == "TOOLS")
          thisload->group = TOOLS;
        if (tmpbuf == "KITCHEN")
          thisload->group = KITCHEN;
      }
      else {
        return lines;
      }
      
      in.getline(buf, LINELEN, ','); // Get a token from the line
      thisload->voltage = atof(buf);

      in.getline(buf, LINELEN, ','); // Get a token from the line
      thisload->wattage = atof(buf);

      in.getline(buf, LINELEN, ','); // Get a token from the line
      thisload->amperage = atof(buf);
      
      in.getline(buf, LINELEN, ','); // Get a token from the line
      thisload->hours = atoi(buf);

      in.getline(buf, LINELEN, ','); // Get a token from the line
      thisload->minutes = atoi(buf);

      in.getline(buf, LINELEN, ','); // Get a token from the line
      thisload->days = atof(buf);

      in.getline(buf, LINELEN, ','); // Get a token from the line
      thisload->quantity = atoi(buf);

      in.getline(buf, LINELEN); // Get a token from the line
      thisload->active = atoi(buf);      

      addEntry(thisload);
      //      dump(thisload);
    }

  in.close();
  return lines;
}

// Calculated Array values
int
Loads::calcArrayAmps(void)
{
  cerr << "FIXME: unimplemented!" << endl;
}

int
Loads::calcArraySeries(void)
{
  cerr << "FIXME: unimplemented!" << endl;
}

int
Loads::calcArrayParallel(void)
{
  cerr << "FIXME: unimplemented!" << endl;
}

int
Loads::calcArrayTotal(void)
{
  cerr << "FIXME: unimplemented!" << endl;
}


// Calculated Battery values
int
Loads::calcBatteryAmps(void)
{
  cerr << "FIXME: unimplemented!" << endl;
}

int
Loads::calcBatterySeries(void)
{
  cerr << "FIXME: unimplemented!" << endl;
}

int
Loads::calcBatteryParallel(void)
{
  cerr << "FIXME: unimplemented!" << endl;
}

int
Loads::calcBatteryTotal(void)
{
  cerr << "FIXME: unimplemented!" << endl;
}

// Calculate the daily watts used by this device profile
double
Loads::calcWatts(load_t *thisload)
{
  double watts = 0.0, hours;
  
  hours = calcHoursDaily(thisload);
  watts = thisload->wattage *  thisload->quantity * hours;
  // cerr << thisload->name << ": " << (thisload->wattage *  thisload->quantity *  thisload->days * hours ) / 7 << endl;

  return watts;
}

// These are the calculated Values
double
Loads::calcWatts(void)
{
  vector<string>::iterator it;
  vector<string> *loadnames;
  load_t *thisload;
  double watts = 0.0, hours;
  
  loadnames = dataNames();
  
  if (loadnames->size() == 0) {
    cerr << "No Load data in memory" << endl;
    return 0.0;
  }
  
  //    namelist[i++] = strdup("Hey Now");
  for (it = loadnames->begin(); it != loadnames->end(); it++) {
    thisload = findEntry(*it);
    if (thisload->active) {
      //      hours = thisload->hours + (thisload->minutes/60);
      watts += calcWatts(thisload); // (thisload->wattage *  thisload->quantity *  thisload->days * hours)/7;
#if 0
      cerr << "hours = " << thisload->hours << " , minutes = " << thisload->minutes
           << " sum = " <<  hours << endl;
      cerr << thisload->name << ": ";
      cerr << thisload->wattage << " * ";
      cerr << thisload->quantity << " * ";
      cerr << thisload->days << " * ";
      cerr << hours;
      cerr << thisload->name << ": " << (thisload->wattage *  thisload->quantity *  thisload->days * hours ) / 7;
      cerr << "watts:\ttotal watts is: " << watts << endl;
#endif
    }
  }

  // Adjust for inefficiencies
  watts *= 1.015;
  
  return watts;
}

double
Loads::calcAmps(load_t *load)
{
  cerr << "FIXME: unimplemented!" << endl;
}

double
Loads::calcAmps(void)
{
  cerr << "FIXME: unimplemented!" << endl;
}


// Calculate the daily watts used by this device profile
double
Loads::calcHoursDaily(load_t *thisload)
{
  double hours = 0.0;
  
      //      hours = thisload->hours + (thisload->minutes/60);

  hours = ((thisload->hours + (thisload->minutes/60)) * thisload->days) / 7;

#if 0
  cerr << "Hours used daily for " << thisload->name
       << " is " << hours
       << ", hours is " << thisload->hours
       << ", minutes is " << thisload->minutes
       << ", days is " << thisload->days
       << endl;
#endif
  return hours;
}


// These are the calculated Values
double
Loads::calcHoursDaily(void)
{
  vector<string>::iterator it;
  vector<string> *loadnames;
  load_t *thisload;
  double hours = 0.0;
  
  loadnames = dataNames();
  
  if (loadnames->size() == 0) {
    cerr << "No Load data in memory" << endl;
    return 0.0;
  }
  
  //    namelist[i++] = strdup("Hey Now");
  for (it = loadnames->begin(); it != loadnames->end(); it++) {
    thisload = findEntry(*it);
    if (thisload->active) {
      hours += calcHoursDaily(thisload);
#if 0
      cerr << "hours = " << thisload->hours << " , minutes = " << thisload->minutes
           << " sum = " <<  hours << endl;
      cerr << thisload->name << ": ";
      cerr << thisload->wattage << " * ";
      cerr << thisload->quantity << " * ";
      cerr << thisload->days << " * ";
      cerr << hours;
      cerr << minutes;
      cerr << thisload->name << ": " << (thisload->wattage *  thisload->quantity *  thisload->days * hours ) / 7;
      cerr << "watts:\ttotal watts is: " << watts << endl;
#endif
    }
  }
  
  return hours;
}

#if 0
vector<string> *
Loads::names(void)
{
  map<string, load_t *>::const_iterator it;;
  vector<string> *loadnames;
  load_t *entry;
  loadnames = new vector<string>;  
  
  if (_data.size() == 0) {
    cerr << "No Load data in memory!" << endl;
    return loadnames;
  }
  
  for (it = _data.begin(); it != _data.end(); it++) {
    entry = it->second;
    loadnames->push_back(entry->name);
  }
  
  return loadnames;
}
#endif


static Loads _sl;

extern "C" {

  void dump_loads(void)
  {
    _sl.dump();
  }
  
  void dump_load(load_t *load)
  {
    _sl.dump(load);
  }
  
  int load_size(void)
  {
    return _sl.dataSize();
  }

  int
  load_names(const char **namelist)
  {
    vector<string>::iterator it;
    vector<string> *loadnames;
    string entry;
    int i = 0;

    loadnames = _sl.dataNames();
    
    if (loadnames->size() == 0) {
      cerr << "No Load data in memory" << endl;
      return 0;
    }
    
    //    namelist[i++] = strdup("Hey Now");
    for (it = loadnames->begin(); it != loadnames->end(); it++) {
      entry = *it;
      namelist[i++] = strdup(entry.c_str());
      //      dbglog << "NAMELIST " << namelist[i-1] << endl;
    }
    namelist[i++] = "eof";

    return i;
  }

  // Add a new load into the database
  void add_load(load_t *load)
  {
    _sl.addEntry(load);
  }

  // Edit an existing load entry in the database
  void edit_load(load_t *load)
  {
    _sl.editEntry(load);
  }
  
  load_t *find_load(const char *name)
  {
    return _sl.findEntry(name);
  }

  int calc_array_amps(void)
  {
    return _sl.calcArrayAmps();
  }
  
  int calc_array_series(void)
  {
    return _sl.calcArraySeries();
  }
  
  int calc_array_parallel(void)
  {
    return _sl.calcArrayParallel();
  }
  
  int calc_array_total(void)
  {
    return _sl.calcArrayTotal();
  }

  int calc_battery_amps(void)
  {
    return _sl.calcBatteryAmps();
  }
  
  int calc_battery_series(void)
  {
    return _sl.calcBatterySeries();
  }
  
  int calc_battery_parallel(void)
  {
    return _sl.calcBatteryParallel();
  }
  
  int calc_battery_total(void)
  {
    return _sl.calcBatteryTotal();
  }
  
  double calc_watts_total(void)
  {
    return _sl.calcWatts();
  }
  
  double calc_watts(load_t *load)
  {
    return _sl.calcWatts(load);
  }
  
  double calc_amps_total(void)
  {
    return _sl.calcAmps();
  }

  double calc_amps(load_t *load)
  {
    return _sl.calcAmps(load);
  }

  double calc_hours_daily_total(void)
  {
    return _sl.calcHoursDaily();
  }

  double calc_hours_daily(load_t *load)
  {
    return _sl.calcHoursDaily(load);
  }

  void write_loads(const char *filespec) 
  {
    _sl.writeLoads(filespec);
  }
  
  int read_loads_CSV(const char *filespec) 
  {
    return _sl.readLoadsCSV(filespec);
  }
}

// local Variables:
// mode: C++
// indent-tabs-mode: t
// End:
