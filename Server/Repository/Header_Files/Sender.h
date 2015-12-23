#ifndef Sender_Header
#define Sender_Header
/////////////////////////////////////////////////////////////////////////////
// Sender.h - Sends the request to peer and waits for a response.          //
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
* This module provides classes, File, FileInfo, Path, Directory, and
* FileSystemSearch.
*
* Public Interface:
* =================
*void ReceiveStringfromClient(std::string, std::string, std::string);
*void ClientSendermain(std::vector<string> resultantvector, std::string ClientPort, std::string ServerPort, std::string FileName);
void ServerSendermain(std::string ClientPort, std::string ServerPort);
void deqFromBQ(std::promise<std::string> &p);

* Required Files:
* ===============
* ApplicationHelper.h, MessageHandler.h, Cpp11_BlockingQueue.h, Sender.cpp
*
* Build Command:
* ==============
* cl /EHa /DTest_Sender Sender.cpp
*
* Maintenance History:
* ====================
* ver 2.2 : 13 Apr 15
* - passed the parameters in the methods as arguments without hard coding
* ver 2.1 : 09 Apr 15
* included additional functionality to send the request.
* ver 2.0 : 04 Apr 15
* - made a few small changes to methods used in the code
** ver 1.0 : 02 Apr 15
* - first release
*/


#include"../Socket/Socket.h"
#include"../ApplicationHelpers/ApplicationHelper.h"
#include"../MessageHandler/MessageHandler.h"
#include"../Cpp11-BlockingQueue/Cpp11_BlockingQueue.h"
#include<string>
#include<iostream>
#include<string>
#include<fstream>
#include <sstream>
#include<future>
using namespace std;
using namespace ApplicationHelper;
using namespace std;


class Sender
{
public:
	// for client
	void ReceiveStringfromClientforUpload(std::string, std::string, std::string);
	//void clientTestStringHandling(Socket& si);
	void ClientSendermain(std::string ClientPort, std::string ServerPort, std::string FileName, std::string Keyword);

	// for Server
	void ServerSendermain(std::string ClientPort, std::string ServerPort, std::string Keyword);
	void deqFromBQ(std::promise<std::string> &p);
	void SendUpload(std::vector<string> resultantvector, std::string ServerPort, std::string ClientPort, std::string FileName, SocketConnecter &si);
	void Senddownload(std::string ServerPort, std::string ClientPort, std::string FileName, SocketConnecter &si);
	void ReceiveStringfromServerforDownload(std::string ServerPort, std::string ClientPort, std::string FileName);
	void ClientSendermainforfilesearch(std::string ServerPort, std::string ClientPort, std::string Keyword);
private:
	std::string Filename = "";
	std::string FilenameforServer = "";
	BlockingQueue<std::string> sbq;
	std::vector<string> resultantvector;
	std::vector<string> resultantvector2;
};


#endif

