/////////////////////////////////////////////////////////////////////////////
// ApplicationHelper.cpp - Helps  to Display the content more effectively  //
// ver 2.0                                                                 //
// ----------------------------------------------------------------------- //
//copyright ©															   //
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2010                             //
// Platform:    Lenovo Z510, Core i7, Windows 8.1                          //
// Author: Professor Jim Fawcett		                                   //
// Modified by:      Sridhar Ganapathy, CST 4-187, Syracuse University     //
//              SUID: 266711369, Email_id: sganapat@syr.edu                //
/////////////////////////////////////////////////////////////////////////////
#include "ApplicationHelper.h"
#include <string>
#include <iostream>

bool ApplicationHelper::Verbose::showState_ = false;
const bool ApplicationHelper::always = true;

std::mutex mtx;
std::unique_lock<std::mutex> iolock(mtx, std::defer_lock);

void ApplicationHelper::title(const std::string& msg, char underline)
{
	iolock.lock();
	std::cout << "\n  " << msg;
	std::cout << "\n " << std::string(msg.size() + 2, underline);
	iolock.unlock();
}

void ApplicationHelper::putLine(const std::string& msg)
{
	iolock.lock();
	std::cout << "\n" + msg;
	iolock.unlock();
}

ApplicationHelper::Verbose::Verbose(bool showState)
{
	showState_ = showState;
	/*if (showState)
		putLine("\nVerbose mode turned on \n");*/
}

void ApplicationHelper::Verbose::show(const std::string& msg, bool always)
{
	if (always == true || showState_ == true)
	{
		std::string temp = std::string("\n  ") + msg;
		iolock.lock();
		std::cout << temp;
		std::cout.flush();
		iolock.unlock();
	}
}

//------------------- Test stub for testing the current package-------------------------------//

#ifdef TEST_APPLICATIONHELPERS
#include"ApplicationHelper.h"
using namespace ApplicationHelper;
int main()
{
	Verbose vb;
	vb.show("Testing mode turned onn!!", true);
}

#endif
