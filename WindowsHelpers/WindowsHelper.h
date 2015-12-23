#ifndef Windows_Header
#define Windows_Header
/////////////////////////////////////////////////////////////////////////////
// WindowsHelper.h - Helps in conversion and to Display the content more   //
// ver 2.2                                            effectively          //
// ----------------------------------------------------------------------- //
//copyright ©															   //
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2010                             //
// Platform:    Lenovo Z510, Core i7, Windows 8.1                          //
// Author: Professor Jim Fawcett		                                   //
// Modified by:      Sridhar Ganapathy,  Syracuse University			   //
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
* WindowsHelper.cpp
*
* Build Command:
* ==============
* cl /EHa /DTest_WindowsHelper WindowsHelper.cpp
*
* Maintenance History:
* ====================
* ver 2.0 : 13 Apr 15
* - created teststub to test the module.
** ver 1.0 : 02 Apr 15
* - first release
*/


#include <string>
#include <vector>

namespace WindowsHelper
{
	std::string wstringToString(const std::wstring& wstr);
	std::wstring stringToWideString(const std::string& str);
	std::string GetLastMsg(bool wantSocketMessage);

}

#endif