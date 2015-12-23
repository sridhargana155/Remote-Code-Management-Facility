/////////////////////////////////////////////////////////////////////////////
// Executive.cpp - Controls the main flow of execution. Initiates the Client//
// ver 2.6                                                       and Server//
// ----------------------------------------------------------------------- //
// copyright ©  Sridhar Ganapathy                                          //
// All rights granted provided that this notice is retained                //
// ----------------------------------------------------------------------- //
// Language:    Visual C++ version 11, Visual Studio 2013                  //
// Platform:    Lenovo Z510, Core i7, Windows 8.1                          //
//									                                       //
// Author: Sridhar Ganapathy,CST,  Syracuse University		               //
//				SUID: 266711369, Email_id: sganapat@syr.edu                //
/////////////////////////////////////////////////////////////////////////////
#include<iostream>
#include<vector>
#include<string>
#include <fstream>
#include <thread>
using namespace std;
#include"../Client/Client.h"
#include"../Server/Server.h"

//------------Inititating the server--------------------------------------------------------//
void ServerSend(string serverprt, string clientprt )
{
	Server snd;
	snd.FileuploadReceiveandSend(serverprt, clientprt);
}

//-------------------------------------------Initiating the Client-----------------------------------------//
void ClientSend(string serverprt, string clientprt, string filename, string dwnldflnm, string path, string category, string pattern, string textsearch)
{
	Client ct;
	ct.FileuploadfromClient(serverprt, clientprt, filename, dwnldflnm, path, category, pattern, textsearch);
}

//-------------------The main initiates the Client and Server to communicate between each other---------------------//

int main(int argc, char* argv[])
{	
	if (argc == 1) // when nothing is given as command line input
	{
		cout << "Please Enter the SourcePort, DestinationPort, UploadFilename, DownloadFilename, Path, Pattern, Category, TextSearch in the commandline\n";
	}
	else // when the command line has the required input from user
	{
		thread t1(ServerSend, argv[4], argv[2]); // Getting the Port numbers and Filename through commandline arguments
		thread t2(ClientSend, argv[4], argv[2],argv[6], argv[8],argv[10],argv[12],argv[14],argv[16]);
		t1.join();
		t2.join();
	}
	return 0;

}
