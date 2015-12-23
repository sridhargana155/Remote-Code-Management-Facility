#include "Server.h"
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

//-----------------------------------Thread for Server Listening port------------------------//
void Server::FileuploadReceiveandSend(std::string clientportnumber, std::string serverportnumber)
{
	clientportnmb = clientportnumber;
	serverportnmb = serverportnumber;
	thread t5(&Server::ServerReceiver, this);
	t5.join();
}

//-----------------------------Requirement 7-------------------------------------------------//
//-------------------------Facility to Receive on Server side-------------//

//-----------------------Calls the receiver to receive messages from the sneder--------------------//
void Server::ServerReceiver()
{
	Receiver rnd;
	rnd.ReceiverforUploadfromServer(clientportnmb, serverportnmb);
}

//------------------- Test stub for testing the current package-------------------------------//

#ifdef Test_Server
#include"Server.h"
int main()
{
	Server svr;
	svr.FileuploadReceiveandSend("9076","9075");
	svr.ServerReceiver();
	return 0;
}


#endif // Test_Server