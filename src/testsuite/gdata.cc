// 
//   Copyright (C) 2009, 2010 Free Software Foundation, Inc.
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

// This is generated by autoconf
#include "config.h"

#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <getopt.h>
#include <iostream>

#include "gnuae.h"
#include "Battery.h"
#include "Centers.h"
#include "Chargers.h"
#include "Combiners.h"
#include "Inverters.h"
#include "Loads.h"
#include "PVPanel.h"
#include "Pumps.h"
#include "Wire.h"
#include "log.h"
#include "tcpip.h"
#include "Database.h"
#include "dejagnu.h"

#include "gui.h"

using namespace std;
using namespace gnuae;

static void usage (const char *);

static LogFile& dbglogfile = LogFile::getDefaultInstance();
static GnuAE& gdata = GnuAE::getDefaultInstance();

TestState runtest;

int
main(int argc, char **argv) {
    int c, status, result;
    bool logopen = false;
    const char *errmsg;
    char buf[30];
    bool dump = false;
    string mod_filespec, search;
    PVPanels pv;
    pvpanel_t *entry;
    
    string      hostname;
    string      user;
    string      passwd;
    
    // scan for the two main standard GNU options
    for (c=0; c<argc; c++) {
	if (strcmp("--help", argv[c]) == 0) {
	    usage(argv[0]);
	    exit(0);
	}
	if (strcmp("--version", argv[c]) == 0) {
	    cerr << "GnuAE version: " << VERSION << endl;
	    // fprintf (stderr, "GnuAE version: %s\n", VERSION);
	    exit(0);
	}
    }
    
    while ((c = getopt (argc, argv, "vr:u:p:xc")) != -1) {
	switch (c) {
	  case 'h':
	      usage (argv[0]);
	      break;
	      
	  case 'v':
	      dbglogfile.set_verbosity();
	      break;
	      
	  case 'r':
	      hostname = optarg;
	      gdata.dbHostSet(hostname);
	      break;
	      
	      // Specify database user name.
	  case 'u': 
	      user = optarg;
	      gdata.dbUserSet(user);
	      break;
	      
	      // Specify database user password.
	  case 'p':
	      passwd = optarg;
	      gdata.dbPasswdSet(passwd);
	      break;
	      
	  case 'x':
	      gdata.useSQL(true);
	      dbglogfile << "Will use SQL queries instead of memory resident" << endl;
	      break;
	      
	  case 'c':
	      gdata.useCSV(true);
	      dbglogfile << "Will use CSV files to load memory resident" << endl;
	      break;
	      
	  default:
	      usage (argv[0]);
	      exit(0);
	}
    }
    
    if (!logopen) {
	dbglogfile.Open (DEFAULT_LOGFILE);
    }
#if 0
    if (mod_filespec.size() == 0) {
	mod_filespec = "/home/rob/projects/gnu/gnuae/data/Modules.csv";
    }
#endif

    gdata.dbNameSet("gnuaetest");
    if (gdata.openDB() == false) {
	runtest.untested("Couldn't open the database!");
	exit(1);
    }
    
    gdata.loadData();
    
    // Dump the data in the data base
    if (dump) {
	gdata.dump();
    }

    const char *projname = "My Project";
    const char *projdes = "all mine";
    long projid = 0;
    double projlat = 40.0;
    double projlon = 105.0;

    // Project tests
    long id = gdata.newProject(projname, projdes,
                              1.2, 2.3, 3.4, "none", 0.0, 0.0);
    if (id) {
	runtest.pass("GnuAE::newProject()");
    } else {
	runtest.fail("GnuAE::newProject()");
    }

    auto_ptr<project_t> myproj = gdata.getProject(id, "My Project");
    if (myproj.get()) {
        if ((memcmp(myproj->name, projname, 10) == 0)
            && (memcmp(myproj->description, projdes, 8) == 0)
            && ((myproj->sunhours > 1.1) && (myproj->sunhours < 1.3))
	    && ((myproj->windhours > 2.2) && (myproj->windhours < 2.4))
	    && ((myproj->windspeed > 3.3) && (myproj->windspeed < 3.5))) {
            runtest.pass("GnuAE::getProject()");
        } else {
            runtest.fail("GnuAE::getProject()");
        }
    } else {
        runtest.unresolved("GnuAE::getProject()");
    }
    
    myproj->sunhours = myproj->sunhours * 2;
    myproj->windhours = myproj->windhours * 2;
    gdata.updateProject(id, myproj.get());
    auto_ptr<project_t> myproj2 = gdata.getProject(id, "My Project");
    if ((myproj2->sunhours == myproj->sunhours)
	&& (myproj2->sunhours == myproj->sunhours)) {
	runtest.pass("GnuAE::updateProject()");
    } else {
	runtest.fail("GnuAE::updateProject()");
    }
    gdata.eraseProject(id, projname);
    if (gdata.getProject(id, "My Project").get()) {
	runtest.fail("GnuAE::eraseProject()");
    } else {
	runtest.pass("GnuAE::eraseProject()");
    }

    // Load Item tests
    gdata.addItem(id, "all TV", "sucks", LOAD, 0, 1, 2, 3);
    gdata.addItem(id, "My Stereo", "is great", LOAD, 0, 1, 2, 3);
    auto_ptr<vector<item_t *> > names = gdata.listItems(id);
    if (names.get()) {
	// There will be only two entries in the profiles table
	item_t *node0 = names->at(0);
	item_t *node1 = names->at(1);
	if ((strcmp(node0->item, "all TV") == 0) 
	    && (strcmp(node1->item, "My Stereo") == 0)
	    && (strcmp(node0->description, "sucks") == 0)
	    && (strcmp(node1->description, "is great") == 0)
	    ) {
	    runtest.pass("GnuAE::listItems()");
	} else {
	    runtest.fail("GnuAE::listItems()");
	}
	free(node0->item);
	free(node0->description);
	delete node0;

	free(node1->item);
	free(node1->description);
	delete node1;
    } else {
        runtest.unresolved("GnuAE::listItems()");
    }

    free(myproj->name);
    free(myproj->description);    

    free(myproj2->name);
    free(myproj2->description);
}

static void
usage (const char *prog)
{
    cerr << "Usage: " << prog << "[dlhvrup]" << endl;
    cerr << "-h\tHelp" << endl;
    cerr << "-v\tVerbose mode" << endl;
    cerr << "-r\tRemote Machine (localhost)" << endl;
    cerr << "-u\tRemote Machine user" << endl;
    cerr << "-p\tRemote Machine password" << endl;
    exit (-1);
}

// local Variables:
// mode: C++
// indent-tabs-mode: t
// End:
