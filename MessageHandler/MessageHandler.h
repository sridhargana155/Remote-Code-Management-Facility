#ifndef Message_Handler
#define Message_Handler
/////////////////////////////////////////////////////////////////////////////
// MessageHandler.h - The message packets are parsed and handled  on both  //
// ver 2.2                                        the receiver and sender  //
// ----------------------------------------------------------------------- //
//copyright ©	Sridhar Ganapathy										   //
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2010                             //
// Platform:    Lenovo Z510, Core i7, Windows 8.1                          //
//										                                   //
// Author:      Sridhar Ganapathy, CST 4-187, Syracuse University          //
//              SUID: 266711369, Email_id: sganapat@syr.edu                //
/////////////////////////////////////////////////////////////////////////////
/*
* Module Operations:
* ==================
* This module provides facility for handling the messages from both the sender and receiver.
*
* Public Interface:
* =================
void messageParsing(std::string temp);
void FileWriting();
std::vector<string> ProcessingtoFullStringforUpload(std::string temp, std::string ClientPort, std::string ServerPort);
std::vector<string> PreparedSendStringforUpload(std::vector<string> containscontent, std::string ClientPort, std::string ServerPort, std::string FileName);
std::vector<std::string> BreakStrings(std::string temp);
*
* Required Files:
* ===============
* ApplicationHelper.h, MessageHandler.cpp, FileSystem.h
*
* Build Command:
* ==============
* cl /EHa /DTest_MessageHandler MessageHandler.cpp
*
* Maintenance History:
* ====================
* ver 2.2 : 13 Apr 15
* - passed the parameters in the methods as arguments without hard coding.
* ver 2.1 : 09 Apr 15
* moved the functionalities from the receiver and sender to a separate package here.
* ver 2.0 : 04 Apr 15
* - made a few small changes to methods used in the code
** ver 1.0 : 02 Apr 15
* - first release
*/

#include"../Futures/FileSystem.h"
#include"../ApplicationHelpers/ApplicationHelper.h"
#include<string>
#include<vector>
#include<fstream>
#include <sstream>
#include<iostream>
using namespace std;
using namespace FileSystem;
using namespace ApplicationHelper;
//--------------------------------------Requirement 4-------------------------------------------------------//
//----------------------------Class for Constructing the Message--------------------------------------------//
class MessageHandler
{
public:
	std::vector<string> ProcessingtoFullStringforUpload(std::string temp, std::string ClientPort, std::string ServerPort);
	std::vector<string> PreparedSendStringforUpload(std::vector<string> containscontent, std::string ClientPort, std::string ServerPort, std::string FileName);
	//returns the vector of strings in blocks
	std::vector<std::string> BreakStrings(std::string temp);
	std::vector<string> ProcessingtoFullStringforDownload(std::string FileName, std::string ServerPort, std::string ClientPort);
	std::vector<string> PreparedSendStringforDownload(std::vector<string> containscontent, std::string ServerPort, std::string ClientPort, std::string FileName);
};

//--------------------------------------Requirement 4-------------------------------------------------------//
//----------------------------Class for Interpreting the the Message--------------------------------------------//

class MessagePasrer
{
public:
	//void FileCopying();
	void messageParsing(std::string temp);
	void FileWritingforUpload();
	void FileWritingforDownload();

private:
	std::string bigstring = "";
	std::string filnm = "";
	//std::string filnm2 = "";
};

#endif