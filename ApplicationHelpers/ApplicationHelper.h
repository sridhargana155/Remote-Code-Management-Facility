#ifndef APPHELPERS_H
#define APPHELPERS_H
/////////////////////////////////////////////////////////////////////////////
// ApplicationHelper.h - Helps  to Display the content more effectively    //
// ver 2.0                                                                 //
// ----------------------------------------------------------------------- //
//copyright ©															   //
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2010                             //
// Platform:    Lenovo Z510, Core i7, Windows 8.1                          //
// Author: Professor Jim Fawcett		                                   //
// Modified by:      Sridhar Ganapathy,            Syracuse University     //
//              SUID: 266711369, Email_id: sganapat@syr.edu                //
/////////////////////////////////////////////////////////////////////////////
/*
* Module Operations:
* ==================
* Helps to Display the content more effectively.
* Helps in the conversion of wstring to string and vice versa.
*
* Public Interface: NA.
* =================
*
* Required Files:
* ===============
* ApplicationHelper.cpp
*
* Build Command:
* ==============
* cl /EHa /DTest_ApplicationHelper ApplicationHelper.cpp
*
* Maintenance History:
* ====================
* ver 2.0 : 13 Apr 15
* - created teststub to test the module.
** ver 1.0 : 02 Apr 15
* - first release
*/

#include <string>
#include <iostream>
#include <sstream>
#include <mutex>

namespace ApplicationHelper
{
	void title(const std::string& msg, char underline = '-');

	template<typename T>
	std::string toString(T t)
	{
		std::ostringstream out;
		out << t;
		return out.str();
	}

	void putLine(const std::string& msg = "");

	extern const bool always;

	class Verbose
	{
	public:
		Verbose(bool showState = true);
		void static show(const std::string& msg, bool always = false);
	private:
		static bool showState_;
	};
}

#endif
