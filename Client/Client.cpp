/////////////////////////////////////////////////////////////////////////////
// Client.cpp - Calls the sender to upload a file to the server            //
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
#include "Client.h"

//---------------File upload request from the Client side using mutithreading ------------------------------//

void Client::FileuploadfromClient(string serverprt, string clientprt, string filename, string dwnldflnm, string path, string category, string pattern, string textsearch)
{
	cPath = path;
	cPattern = pattern;
	cTextSearch = textsearch;
	dwnfilenm = dwnldflnm;
	clcategory = category;
	serverportnmb = serverprt;
	clientportnmb = clientprt;
	filenm = filename;
	thread t3(&Client::ClientSender,this);
	thread t4(&Client::ClientReceiver, this);
	t3.join();
	t4.join();
}

//-----------------------------Requirement 7-------------------------------------------------//
//-------------------------Facility to Send on Client side-------------//

//---------------File upload request from the Client side through sender ------------------------------//

void Client::ClientSender()
{
	Sender snd;
	snd.ReceiveStringfromClientforUpload(serverportnmb, clientportnmb, filenm);
}

//---------------Initiating response for File upload from the server to client ------------------------------//


//-----------------------------Requirement 7-------------------------------------------------//
//-------------------------Facility to Receive on Client side-------------//

void Client::ClientReceiver()
{
	Receiver rcv;
	rcv.ReceiverforUploadtoClient(clientportnmb, serverportnmb, cPath, cPattern, cTextSearch, clcategory, dwnfilenm);
}

//------------------- Test stub for testing the current package-------------------------------//
#ifdef Test_Client
#include"Client.h"
int main(){
	Client ct;
	cout << "Testing the Client module\t";
	ct.FileuploadfromClient("9076","9075","Sample.txt","Sample1.cpp","./Server/Repository/","Header_Files","*.h","class");
	ct.ClientReceiver();
	ct.ClientSender();
	return 0;
}

#endif // Test_Client

