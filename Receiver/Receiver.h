#ifndef Receiver_Header
#define Receiver_Header
/////////////////////////////////////////////////////////////////////////////
// Receiver.h - Receives the request from the sender and processes it.     //
// ver 2.2                                                                 //
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
* This module takes care of receiving the requests from the sender. The requests are
then processed and the processed response is sent back to the Client(peer) from the Sender.
*
* Public Interface:
* =================
//Server Reveiver
void ReceiverforUploadfromServer(std::string clientportnumber, std::string serverportnumber);
//Client receiver
void ReceiverforUploadtoClient(std::string clientportnumber, std::string serverportnumber);
void getserverclientport(std::string, std::string);
void operator()(Socket& socket_);
bool testClientStringHandling(Socket& socket_);
void deqFromBQ(std::promise<std::string> &p);
void operator()(Socket& socket_);
bool testServerStringHandling(Socket& socket_);
void deqFromBQ(std::promise<std::string> &p);
* Required Files:
* ===============
* ApplicationHelper.h, MessageHandler.h, Cpp11_BlockingQueue.h, Receiver.cpp,FileSystem.h
*
* Build Command:
* ==============
* cl /EHa /DTest_Receiver Receiver.cpp
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


#include"../Socket/Socket.h"
#include"../ApplicationHelpers/ApplicationHelper.h"
#include"../Futures/FileSystem.h"
#include"../Sender/Sender.h"
#include"../Cpp11-BlockingQueue/Cpp11_BlockingQueue.h"
#include"../FileMgr/FileMgr.h"
#include"../DataStore/DataStore.h"
#include<future>
#include<iostream>
#include<sstream>
#include<fstream>
#include<iomanip>
#include<string>
using namespace FileSystem;
using namespace ApplicationHelper;
using namespace std;

//-------------------------------this class handles all the messages from the Client and Server-----------------------------------//
class Receiver
{
public:
	//Server Reveiver
	void ReceiverforUploadfromServer(std::string clientportnumber, std::string serverportnumber);
	//Client receiver
	void ReceiverforUploadtoClient(std::string clientportnumber, std::string serverportnumber, std::string Path, std::string Pattern, std::string TextSearch, std::string category, std::string dwnfile);
};


//-----------------this class handles all the request from Client in the Server side, so it named as Client Handler------------------------------------//
class ClientHandler
{
public:
	void getserverclientport(std::string, std::string);
	void operator()(Socket& socket_);
	bool testClientStringHandling(Socket& socket_);
	void deqFromBQ(std::promise<std::string> &p);
	void HandleUploadSend1(std::string str, MessagePasrer &mp);
	void HandleDownloadSend1(std::string str);
	void RequestFileSearch(std::string str);
	void ResponseforFileSearch(std::string str);
	void HandleFileSearch(std::string str);
	void RequestforTextSearch(std::string str);
private:
	std::string ClientPrt = "";
	std::string SvrPrt = "";
	std::string searchfilename = "";
	BlockingQueue<std::string> sbq;
	std::string TextSearchresults = "";
	
};

//-----------------this class handles all the request from Server in the Client side, so it named as Server Handler------------------------------------//
class ServerHandler
{
public:
	void operator()(Socket& socket_);
	bool testServerStringHandling(Socket& socket_);
	void deqFromBQ(std::promise<std::string> &p);
	void HandleDownloadbywriting(std::string str, MessagePasrer &mp);
	void HandleFileSearchClientend(std::string str);
	void HandleTextSearchClientend(std::string str);
	void getpathpatterntextsearch(std::string Path, std::string Pattern, std::string TextSearch, std::string category, std::string dwnldfile);
	void HandleUploadClientend(std::string str);
	void HandleDownloadClientend(std::string str, MessagePasrer &mp1);
private:
	BlockingQueue<std::string> sbq;
	std::string SrvrPrt = "";
	std::string ClntPrt = "";
	std::string sPath = "";
	std::string sPattern = "";
	std::string sTextsearch = "";
	std::string sdwnldflnm = "";
	std::string scategory = "";

};
#endif
