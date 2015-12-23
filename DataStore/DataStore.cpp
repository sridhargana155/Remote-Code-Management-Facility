/////////////////////////////////////////////////////////////////////////////
// DataStore.cpp - Saves and Stores files and path into the datastore map  //
// ver 2.3                                                                 //
// ----------------------------------------------------------------------- //
// copyright ©		Sridhar Ganapathy                                      //
// All rights granted provided that this notice is retained                //
// ----------------------------------------------------------------------- //
// Language:    Visual C++ version 11, Visual Studio 2013                  //
// Platform:    Lenovo Z510, Core i7, Windows 8.1                          //
//									                                       //
// Enhanced by: Sridhar Ganapathy,CST,  Syracuse University                //
//				SUID: 266711369, Email_id: sganapat@syr.edu                //
/////////////////////////////////////////////////////////////////////////////
#include "DataStore.h"
#include <iostream>

//------------------<Saves all the filenames along with the paths into the map>------------------------
void DataStore::save(const std::string& filename, const std::string& path)
{
	it = paths.insert(path);
	iterator mapitr = store.find(filename);
	if (mapitr != store.end())//this is to handle duplicates
	{
		ListOfIters::iterator lstitr = mapitr->second.begin();
		while (lstitr != mapitr->second.end())
		{
			if (**(lstitr) == path)
				return;
			else
				lstitr++;
		}
		mapitr->second.push_back(it.first);
	}

	else// this for other than duplicates
	{
		ListOfIters ltr;
		//pitr = paths.begin();
		ltr.push_back(it.first);
		store[filename] = ltr;
	}
}

//------------------<Searches for the matching text for the given text searched>-----------------------------------------------------------

std::vector<std::string> DataStore::searchtext(string searchtext)
{
	std::vector<std::string> flnmvtr;
	//std::string nm = FileSystem::Path::fileSpec(path, dt);
	std::string check;
	for (iterator st = store.begin(); st != store.end(); ++st)
	{
		for (ListOfIters::iterator litr = st->second.begin(); litr != st->second.end(); litr++)
		{

			check = FileSystem::Path::fileSpec(**(litr), st->first);
			//std::cout << check << "\n";
			fstream flopn;
			//string searchtext = "class";
			size_t pos;// npos is of type size_t
			std::string line;
			flopn.open(check);
			if (!flopn)
			{
				cout << "Unable to open file" << endl;
				exit(1);
			}
			while (flopn.good())// return true if none of the stream's error state is set.
			{
				getline(flopn, line); // get line from file
				pos = line.find(searchtext); // search
				if (pos != string::npos) // string::npos is returned if string is not found
				{
					//cout << "Found!";
					flnmvtr.push_back(st->first);
					flnmvtr.push_back(**(litr));
					break;
				}
			}
		}
	}
	cout << "\nThe search text < " << searchtext << " > is present in the below files along with its path \n";
	return flnmvtr;
}

//------------<Searches for the text present in the data store when the end user gives input from the console>------------------------------------------

std::vector<std::string> DataStore::userfilenamesforsearchtext(string searchtext, string userpattern)
{
	//std::map<string, string> ufilenmandpath;
	std::vector<std::string> uflnmvtr;
	//std::vector<std::string> upathvtr;
	//std::string nm = FileSystem::Path::fileSpec(path, dt);
	std::string check; int cntr = 0;
	for (iterator st = store.begin(); st != store.end(); ++st)
	{
		if (st->first.find(userpattern) != string::npos)
		{
			cntr++;
			for (ListOfIters::iterator litr = st->second.begin(); litr != st->second.end(); litr++)
			{

				check = FileSystem::Path::fileSpec(**(litr), st->first);
				//std::cout << check << "\n";
				fstream flopn;
				//string searchtext = "class";
				size_t pos;// npos is of type size_t
				std::string line;
				flopn.open(check);
				if (!flopn)
				{
					cout << "Unable to open file" << endl;
					exit(1);
				}
				while (flopn.good())// return true if none of the stream's error state is set.
				{
					getline(flopn, line); // get line from file
					pos = line.find(searchtext); // search
					if (pos != string::npos) // string::npos is returned if string is not found
					{
						//cout << "Found!";
						uflnmvtr.push_back(st->first);
						uflnmvtr.push_back(**(litr));
						//ufilenmandpath[st->first] = check;
						break;
					}
				}
			}
		}
	}
	if (cntr == 0)
		cout << "Please give the existing pattern available in data stored";
	else
		cout << "The search text for the user input < " << searchtext << " > given is present in the below files along with its path \n";
	//userpathforsearchtext(upathvtr);
	return uflnmvtr;
}

//-----------------------------<TEST STUB>---------------------------------------------------------------------------------
#ifdef TEST_DATASTORE
#include"../Display/Display.h"
int main()
{
	DataStore ds;
	string filename = "Display.h", path = "../Display", searchstring = "class", user_pattern = ".h";
	ds.save(filename, path);
	ds.searchtext(searchstring);
	ds.userfilenamesforsearchtext(searchstring, user_pattern);
	Display disp;
	disp.display(ds);
}
#endif
