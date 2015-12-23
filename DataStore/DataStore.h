#ifndef DATASTORE_H
#define DATASTORE_H
/////////////////////////////////////////////////////////////////////////////
// DataStore.h - Saves and Stores files and path into the datastore map    //
// ver 2.3                                                                 //
// ----------------------------------------------------------------------- //
// copyright © Sridhar Ganapathy                                           //
// All rights granted provided that this notice is retained                //
// ----------------------------------------------------------------------- //
// Language:    Visual C++ version 11, Visual Studio 2013                  //
// Platform:    Lenovo Z510, Core i7, Windows 8.1                          //
//									                                       //
// Enhanced by: Sridhar Ganapathy,CST,  Syracuse University                //
//				SUID: 266711369, Email_id: sganapat@syr.edu                //
/////////////////////////////////////////////////////////////////////////////
/*
* Module Operations :
* ==================
* This file provides declarations for the methods defined in the DataStore.cpp file.
Below are the method name and functionalities of each method present in the Data Store Class,

save(): This method saves the files and paths into a map both norecursively and recursive depending on the users
input.

searchtext(): This method searches for the text given after /f in the commandline
and displays the filenames along with path as the output.

userfilenamesforsearchtext(): This method searches for the text based on the pattern given from the
console from the end user and displays the file names along the paths.


Public Interface:
==============
using Path = std::string;
using Paths = std::set<Path>;
using PathIter = Paths::iterator;
using ListOfIters = std::list<PathIter>;
using File = std::string;
using Store = std::map<File, ListOfIters>;
using iterator = Store::iterator;
void save(const std::string&, const std::string&);
std::vector<std::string> userfilenamesforsearchtext(string, string);
std::vector<std::string> searchtext(string);
iterator itr;
std::pair<PathIter, bool> it;
Store store;
Paths paths;
PathIter pitr;
ListOfIters::iterator litr;

Required Files:
===============
DataStore.h, DataStore.cpp, FileSystem.h

Build Command:
==============
cl /EHa /DTEST_DATASTORE DataStore.cpp

Maintenance History:
====================
ver 2.3: 09 Feb 15
Created Test stubs and commented meaningful informations for each meathods
* ver 2.2 : 06 Feb 15
*Started integrating this module with the remaining modules. Cleared are the link errors.
Removed the unwanted header files that caused link error
* ver 2.1 :
* moved the files in the map and stored them.
* ver 2.0 : 04 Feb 15
* - made a few small changes to convert the data to be stored in map
with the help of Professor's code
* ver 1.0 : 23 Jan 15
* - first release
*/
#include <vector>
#include<set>
#include<list>
#include<map>
#include<string>
#include<iostream>
#include <fstream>
#include"../Futures/FileSystem.h"
using namespace std;

class DataStore
{
public:
	using Path = std::string;
	using Paths = std::set<Path>;
	using PathIter = Paths::iterator;
	using ListOfIters = std::list<PathIter>;
	using File = std::string;
	using Store = std::map<File, ListOfIters>;
	using iterator = Store::iterator;
	void save(const std::string&, const std::string&);
	std::vector<std::string> userfilenamesforsearchtext(string, string);
	std::vector<std::string> searchtext(string);
	iterator itr;
	std::pair<PathIter, bool> it;
	Store store;
	Paths paths;
	PathIter pitr;
	ListOfIters::iterator litr;
};
#endif