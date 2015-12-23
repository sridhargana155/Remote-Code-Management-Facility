#ifndef Server_Header
#define Server_Header
/////////////////////////////////////////////////////////////////////////////
// Server.h - Receives the processed request from the receivved and stores it.//
// ver 2.2 Calls the Sender to send the acknowledgement back to the receiver.//
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
* Receives the processed request from the received and stores it. 
* Calls the Sender to send the acknowledgement back to the receiver.
*
* Public Interface:
* =================
*void FileuploadReceiveandSend(std::string clientportnumber, std::string serverportnumber);
*void ServerReceiver();
*
* Required Files:
* ===============
* Receiver.h, Sender.h, Server.cpp
*
* Build Command:
* ==============
* cl /EHa /DTest_Server Server.cpp
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


#include"../Receiver/Receiver.h"
#include"../Sender/Sender.h"
#include<thread>
#include<string>
#include<iostream>
using namespace std;
class Server
{
public:
	void FileuploadReceiveandSend(std::string clientportnumber, std::string serverportnumber);
	void ServerReceiver();
private:
	std::string clientportnmb = "";
	std::string serverportnmb = "";
};

#endif