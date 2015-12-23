#ifndef FILEMGR_H
#define FILEMGR_H
/////////////////////////////////////////////////////////////////////////////
// FileMgr.h - Saves filenames and paths to the Data Store. Performs search//
//		       And adds patterns in the pattern vector					   //
// ver 2.3                                                                 //
// ----------------------------------------------------------------------- //
// copyright ©   Sridhar Ganapathy                                         //
// All rights granted provided that this notice is retained                //
// ----------------------------------------------------------------------- //
// Language:    Visual C++ version 11, Visual Studio 2013                  //
// Platform:    Lenovo Z510, Core i7, Windows 8.1                          //
//									                                       //
// Enhanced by: Sridhar Ganapathy,CST,  Syracuse University                //
//				SUID: 266711369, Email_id: sganapat@syr.edu                //
/////////////////////////////////////////////////////////////////////////////
/*
Module Operations :
==================
This file provides declarations for the methods defined in the FileMgr.cpp file.
Below are the method name and functionalities of each method present in the FileMgr Class,

find: searches for the filenames and path to save them to the data store.

addPattern: all the patterns required forthe search are added into the pattern vector.

findnonrecursive: searches the for the filenames and paths based on the input given in teh current directory only.
search does not happen for the sub directories.

Public Interface:
==============
FileMgr(const std::string&, DataStore&);
using iterator = DataStore::iterator;
using patterns = std::vector<std::string>;
void find(std::string&);
void addPattern(const std::string&);
void findnonrecursive(std::string&);
void searchnonrecursive();
void search();
int filecountr, directorycount, counter;
std::string path_;
DataStore& store_;
patterns patterns_;

Required Files:
===============
DataStore.h, FileSystem.h, FileMgr.cpp


Build Command:
==============
cl /EHa /DTEST_FILEMANAGER FileMgr.cpp


Maintenance History:
====================
ver 2.3: 09 Feb 15
Created Test stubs and commented meaningful informations for each methods
* ver 2.2 : 06 Feb 15
*Started integrating this module with the remaining modules. Cleared are the link errors.
Removed the unwanted header files that caused link error
* ver 2.1 :
* created new methods findnonrecursive and searchnonrecursive to meetthe requirements
* ver 2.0 : 04 Feb 15
* - made a few small changes with find function with the help of Professor's code
* ver 1.0 : 23 Jan 15
* - first release
*/
#include"../Futures/FileSystem.h"
#include "../DataStore/DataStore.h"
class FileMgr
{
public:
	FileMgr(const std::string&, DataStore&);
	using iterator = DataStore::iterator;
	using patterns = std::vector<std::string>;
	void find(std::string&);
	void addPattern(const std::string&);
	void findnonrecursive(std::string&);
	void searchnonrecursive();
	void search();
	int filecountr = 0, directorycount = 1, counter = 1;
	std::string path_;
	DataStore& store_;
	patterns patterns_;
};

#endif
