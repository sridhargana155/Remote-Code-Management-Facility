/////////////////////////////////////////////////////////////////////////////
// FileMgr.cpp - Saves filenames and paths to the Data Store. Performs search//
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
#include"FileMgr.h"

//-----------------------------<Copies the object of data store here with the help of constructor>-------------------------------------------

FileMgr::FileMgr(const std::string& path, DataStore& ds) : path_(path), store_(ds)
{
	patterns_.push_back("*.*");
}

//-----------------------------<Saves the filenames and paths recursively in to the data store with the paths>-------------------------------------------
void FileMgr::find(std::string& path)
{

	std::vector<std::string> drts = FileSystem::Directory::getDirectories(path);
	for (auto dt : drts)
	{
		if (dt != "."&&dt != ".."&& drts.size()>2)//If there are folders(directories) in the current path
		{
			for (auto patt : patterns_)
			{
				std::vector<std::string> subfiles = FileSystem::Directory::getFiles(path, patt);
				for (auto sbf : subfiles)
				{
					store_.save(sbf, path);
				}
			}
			std::string nm = FileSystem::Path::fileSpec(path, dt);
			find(nm);
		}
		else//If no directories are found
		{
			if (dt != "..")
			{
				for (auto patt : patterns_)
				{
					std::vector<std::string> subfiles = FileSystem::Directory::getFiles(path, patt);
					for (auto sbf : subfiles)
					{
						store_.save(sbf, path);
					}
				}
			}
		}
	}
}
//-----------------------------<Saves the filenames and paths nonrecursively in to the data store with the paths>-------------------------------------------
void FileMgr::findnonrecursive(std::string& path)
{
	for (auto patt : patterns_)
	{
		std::vector<std::string> subfiles = FileSystem::Directory::getFiles(path, patt);
		for (auto sbf : subfiles)
		{
			store_.save(sbf, path);
		}
	}
}
//-----------------------------<Adds pattern into the pattern vector>------------------------------------------------------------------------
void FileMgr::addPattern(const std::string& patt)
{
	if (patterns_.size() == 1 && patterns_[0] == "*.*")
		patterns_.pop_back();
	patterns_.push_back(patt);
}

//-----------------------------<Calls the find for recursively search>---------------------------------------------------------------------
void FileMgr::search()
{
	find(path_);
}

//-----------------------------<Calls the find for non-recursively search>------------------------------------------------------------------
void FileMgr::searchnonrecursive()
{
	findnonrecursive(path_);
}

//--------------------------------<Test Stub>-----------------------------------------------------------------------------------------------

#ifdef TEST_FILEMANAGER
#include"../DataStore/DataStore.h"
#include"../Display/Display.h"
int main()
{
	Display disp;
	string path = "./TestCheck";
	DataStore ds;
	FileMgr fmg1(path, ds);
	fmg1.find(path);
	fmg1.findnonrecursive(path);
	fmg1.addPattern("*.*");
	fmg1.search();
	fmg1.searchnonrecursive();
	disp.display(ds);

}
#endif