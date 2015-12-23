#define WIN32_LEAN_AND_MEAN
/////////////////////////////////////////////////////////////////////////////
// WindowsHelper.cpp - Helps in conversion and to Display the content more //
// ver 2.0                                            effectively          //
// ----------------------------------------------------------------------- //
//copyright ©															   //
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2010                             //
// Platform:    Lenovo Z510, Core i7, Windows 8.1                          //
// Author: Professor Jim Fawcett		                                   //
// Modified by:      Sridhar Ganapathy,  Syracuse University               //
//              SUID: 266711369, Email_id: sganapat@syr.edu                //
/////////////////////////////////////////////////////////////////////////////
#include "WindowsHelper.h"
#include <Windows.h>
#include <string>
#include <winsock2.h>
using namespace WindowsHelper;
#pragma comment(lib, "Ws2_32.lib")


std::string WindowsHelper::wstringToString(const std::wstring& wstr)
{
	std::string rtn;
	for (auto ch : wstr)
		rtn += static_cast<char>(ch);
	rtn += '\0';
	return rtn;
}

std::wstring WindowsHelper::stringToWideString(const std::string& str)
{
	std::wstring rtn;
	for (auto ch : str)
		rtn += ch;
	rtn += static_cast<wchar_t>('\0');
	return rtn;
}

std::string WindowsHelper::GetLastMsg(bool WantSocketMsg) {

	// ask system what type of error occurred

	DWORD errorCode;
	if (WantSocketMsg)
		errorCode = WSAGetLastError();
	else
		errorCode = GetLastError();
	if (errorCode == 0)
		return "no error";

	// map errorCode into a system defined error string

	DWORD dwFlags =
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER;
	LPCVOID lpSource = NULL;
	DWORD dwMessageID = errorCode;
	DWORD dwLanguageId = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US);
	LPSTR lpBuffer;
	DWORD nSize = 0;
	va_list *Arguments = NULL;

	FormatMessage(
		dwFlags, lpSource, dwMessageID, dwLanguageId,
		(LPTSTR)&lpBuffer, nSize, Arguments
		);

	std::string _msg(lpBuffer);
	LocalFree(lpBuffer);
	return _msg;
}

#ifdef Test_WindowsHelper
using namespace WindowsHelper;
#include<iostream>
int main()
{
	const std::string test = "This is a test string";
	std::string test1 = "";
	std::wstring wstrng;
	wstrng = WindowsHelper::stringToWideString(test);
	test1 = WindowsHelper::wstringToString(wstrng);
	std::cout << test1;
	return 0;
}


#endif // WindowsHelper