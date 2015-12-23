#ifndef Client_Header
#define Client_Header

/////////////////////////////////////////////////////////////////////////////
// Client.h - Calls the sender to upload a file to the server              //
// ver 2.2																   //
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
This module provides facility to uplaod a file to the server. The process is taken forward by the sender.

* Public Interface:
* =================
*void FileuploadfromClient(string clientportnumber, string serverportnumber, string Filename);
*void ClientSender();
*void ClientReceiver();
*
* Required Files:
* ===============
* Client.cpp, Sender.h, Receiver.h
*
* Build Command:
* ==============
* cl /EHa /DTest_Client Client.cpp
*
* Maintenance History:
* ====================
* ver 2.2 : 13 Apr 15
* - passed the parameters in the methods as arguments without hard coding.
* Added functionalities to demostrate requirements
* ver 2.1 : 09 Apr 15
* included additional functionality to receive the request. Made facility to call message parsing package
* ver 2.0 : 04 Apr 15
* - made a few small changes to methods used in the code
** ver 1.0 : 02 Apr 15
* - first release
*/
#include<iostream>
#include<string>
#include<thread>
#include"../Sender/Sender.h"
#include"../Receiver/Receiver.h"
#include<string>
using namespace std;
class Client
{
public:
	void FileuploadfromClient(string serverprt, string clientprt, string filename, string dwnldflnm, string path, string category, string pattern, string textsearch);
	void ClientSender();
	void ClientReceiver();

private:
	string clientportnmb = "";
	string serverportnmb = "";
	string filenm = "";
	string cPath = "";
	string cPattern = "";
	string cTextSearch = "";
	string dwnfilenm = "";
	string clcategory = "";
};

#endif