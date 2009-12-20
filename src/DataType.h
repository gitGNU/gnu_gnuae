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

#ifndef __DATATYPE_H__
#define __DATATYPE_H__

// Nothing in this file is used by the C API at all, but we're
// included by other header files, so be safe and do nothing.
#ifdef __cplusplus

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <memory>

namespace gnuae {

template <typename datatype>
class DataTypeMethods
{
public:
    DataTypeMethods(void)  { };
    ~DataTypeMethods(void) {
	if (_data.size()) {
	    typename std::map<std::string, datatype *>::const_iterator it;
	    for (it = _data.begin(); it != _data.end(); it++) {
		datatype *entry = it->second;
		if (entry) {
		    delete entry;
		}
	    }
	}
    }
    
    void addEntry(datatype *entry) {
        // _data.insert( make_pair( entry->name, entry) );
        _data[entry->name] = entry;
    }
    void editEntry(datatype *entry) {
        _data[entry->name] = entry;
    }
    
    int dataSize(void) {
        return _data.size();
    }
    
    void clearData(void) {
        _data.clear();
    }
    
    datatype *findEntry(std::string name) {
        return _data[name];
    }
    
    std::auto_ptr<std::vector<std::string> > dataNames(void) {
        // std::map<std::string, datatype *>::const_iterator itttt;
        // std::map<std::string, void *>::const_iterator it ;
	std::auto_ptr<std::vector<std::string> > entrynames;
	entrynames.reset(new std::vector<std::string>);
        datatype *entry;
        
        if (!_data.size()) {
            std::cerr << "No data in memory!" << std::endl;
            return entrynames;
        }
	typename std::map<std::string, datatype *>::const_iterator it;
        for (it = _data.begin(); it != _data.end(); it++) {
            entry = static_cast<datatype *>(it->second);
            entrynames->push_back(entry->name);
        }
        return entrynames;
    }
    
    void addData (void) {
#if 0
        int i;
        
        for (i=0; loads[i].name!=0; i++) {
                _data.insert( make_pair( loads[i].name, (load_t *)&loads[i]) );
                //      _data.push_back(&loads[i]);
            }
#endif
    }
    
#if 0
    datatype *operator [] (std::string name)
        {
            return _data[name];
        }
#endif   
private:
    std::map<std::string, datatype *> _data;
};

} // end of gnuae namespace

#endif  // end of __cplusplus

// __DATATYPE_H__
#endif

// local Variables:
// mode: C++
// indent-tabs-mode: t
// End:
