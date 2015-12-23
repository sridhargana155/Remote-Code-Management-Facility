#include "Receiver.h"
/////////////////////////////////////////////////////////////////////////////
// Receiver.cpp - Receives the request from peer and sends a response from the Server//
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

//-----------------------------This method is instantiated in the Server Side to handle Client requests------------//
//-----------------------Blocking queue is implemented to handle multiple Clients and Servers----------------------//
bool ClientHandler::testClientStringHandling(Socket& socket_)
{
	title("Server Receiving Message from the Client");
	MessagePasrer mp;
	while (true)
	{
		if (socket_.bytesWaiting() == 0)
			break;
		std::string str = socket_.recvString();
		mp.messageParsing(str);
		if (str.find("TEST_STOP") != std::string::npos) //once all the packets are sent then the Sender instance is created
		{
			HandleUploadSend1(str,mp);
		}
		if (str.find("Download") != std::string::npos)
		{
			HandleDownloadSend1(str);
		}
		if (str.find("FileSearch")!=std::string::npos)
		{
			RequestFileSearch(str);
		}
		if (str.find("TextSearch") != std::string::npos)
		{
			RequestforTextSearch(str); // Text Search performed at the server's side
		}
		if (socket_ == INVALID_SOCKET)
			return false;
		if (str.size() > 0)// && !(str.find("TEST_STOP") != std::string::npos))
		{

		}
		else
			break;
	}
	return true;
}

//----------------this method takes care of the request for textsearch from the Client in the Server side----------------------------------//
void ClientHandler::RequestforTextSearch(std::string str)
{
	//cout << "I'm from the ServerSide TextSearch\n";
	std::vector<string> FilesforTextSearch;
	std::string path;
	std::string nwsmlone1 = "Path: "; // Extract Client Port Number
	size_t index1 = str.find("Path: ");
	for (size_t i = index1 + nwsmlone1.size(); i < str.find(" Pattern: "); i++)
		path += str[i];
	std::string pattern;
	std::string nwsmlone2 = "Pattern: ";
	size_t index2 = str.find("Pattern: ");
	for (size_t i = index2 + nwsmlone2.size(); i < str.find(" TextSearch: "); i++)
		pattern += str[i];
	std::string textsearch;
	std::string nwsmlone3 = "TextSearch: ";
	size_t index3 = str.find("TextSearch: ");
	for (size_t i = index3 + nwsmlone3.size(); i < str.size(); i++)
		textsearch += str[i];
	DataStore ds1;
	FileMgr fm1(path, ds1);
	fm1.addPattern(pattern);
	fm1.search();
	FilesforTextSearch = ds1.searchtext(textsearch);
	//cout << "The Files for the textsearch are as follows\n";
	for (auto tmp : FilesforTextSearch)
	{
		TextSearchresults += tmp;
		TextSearchresults += ":";
	}
	//cout << TextSearchresults;
	Sender snd1;
	snd1.ReceiveStringfromServerforTextSearch(SvrPrt, ClientPrt, searchfilename);
}

//---------------------------------This method takes care of the File Search Requests from the Client in the server side---------------------------------------------------------------------//
void ClientHandler::RequestFileSearch(std::string str)
{
	//cout << "\nThis the FileSearch";
	std::string path;
	std::string nwsmlone1 = "Path: "; // Extract Client Port Number
	size_t index1 = str.find("Path: ");
	for (size_t i = index1 + nwsmlone1.size(); i < str.find(" Pattern: "); i++)
		path += str[i];
	std::string pattern;
	std::string nwsmlone2 = "Pattern: ";
	size_t index2 = str.find("Pattern: ");
	for (size_t i = index2 + nwsmlone2.size(); i < str.size(); i++)
		pattern += str[i];
	DataStore ds;
	FileMgr fm(path, ds);
	fm.addPattern(pattern);
	fm.search();
	for (ds.itr = ds.store.begin(); ds.itr != ds.store.end(); ++ds.itr)
	{
		searchfilename += ds.itr->first;
		searchfilename += ":";
		for (ds.litr = ds.itr->second.begin(); ds.litr != ds.itr->second.end(); ds.litr++)
		{
			searchfilename += **(ds.litr);
			searchfilename += ":";
		}
	}
	//cout <<"searchfilename \n" <<searchfilename;
	Sender snd1;
	snd1.ReceiveStringfromServerforFileSearch(SvrPrt,ClientPrt, searchfilename);

}

//----------------------------Thismethod processes the download request from the Client and responds back to the Client---------------//
void ClientHandler::HandleDownloadSend1(std::string str)
{
	//cout << "Download successfully\n"<<str;
	std::string flnm;
	std::string nwsmlone = "Filename: "; // Extract Client Port Number
	size_t index = str.find("Filename: ");
	for (size_t i = index + nwsmlone.size(); i < str.size(); i++)
		flnm += str[i];
	std::string nwsmlone2 = "Source Port: "; // Extract Client Port Number
	size_t index2 = str.find("Source Port: ");
	for (size_t i = index2 + nwsmlone2.size(); i < str.find(" Destination Port: "); i++)
	ClientPrt += str[i];
	std::string nwsmlone1 = "Destination Port: "; // Extract Client Port Number
	size_t index1 = str.find("Destination Port: ");
	for (size_t i = index1 + nwsmlone1.size(); i < str.find(" Source Address: "); i++)
		SvrPrt += str[i];
	//Verbose::show("File Downloaded Successfully", always);
	Sender snd;
	snd.ReceiveStringfromServerforDownload(ClientPrt, SvrPrt, flnm);
}

//--------------------This method is used to send the response back to the Client from the server side--------------------------------------// 
void ClientHandler::HandleUploadSend1(std::string str, MessagePasrer &mp)
{
	//Verbose::show("server recvd : " + str, always); //Threads in the Blocking queue to handle multiple Clients and Servers
	thread thr1(&BlockingQueue<string>::enQ, &sbq, str);
	promise<string> p;
	thread tr2(&ClientHandler::deqFromBQ, this, std::ref(p));
	thr1.join();
	tr2.join();
	std::string smltrg;
	std::string nwsmlone = "ClientPort: "; // Extract Client Port Number
	size_t index = str.find("ClientPort: ");
	for (size_t i = index + nwsmlone.size(); i < str.find("ServerPort: "); i++)
		smltrg += str[i];
	std::string smltrg1;
	std::string nwsmlone1 = "ServerPort: ";  // Extract Server Port Number
	size_t index1 = str.find("ServerPort: ");
	for (size_t j = index1 + nwsmlone1.size(); j < str.find("TEST_STOP"); j++)
		smltrg1 += str[j];
	mp.FileWritingforUpload();
	Sender snd;
	snd.ServerSendermain(smltrg, smltrg1,"acknowledgement");
}

//--------------------Dequeueing the threads in the Blocking Queue in Server side--------------------------------------------//
void ClientHandler::deqFromBQ(std::promise<std::string> &p)
{
	p.set_value(sbq.deQ());
}

//--------------------Operator overloading in the Server side using Client handler-------------------------------------------//
void ClientHandler::operator()(Socket& socket_)
{
	while (true)
	{
		std::string command = socket_.recvString();
		if (command.size() == 0)
			break;
		//Verbose::show("Server first Command rcvd from Client: " + command);
		if (testClientStringHandling(socket_))
				Verbose::show("----Server Message receiving test passed", always);
			else
			{
				Verbose::show("----Server Message receiving test failed", always);
				break;
			}
    }
	//Verbose::show("ClientHandler socket connection closing");
	socket_.shutDown();
	socket_.close();
	//Verbose::show("ClientHandler thread terminating");
}

//-------------------------File upload received in the Server side------------------------------//
void Receiver::ReceiverforUploadfromServer(std::string serverportnumber, std::string clientportnumber)
{
	title("Server listening to \t" + serverportnumber);
	try
	{
		std::istringstream iss(serverportnumber);
		size_t svrport;
		iss >> svrport;
		Verbose v(true);
		SocketSystem ss;
		SocketListener sl(svrport, Socket::IP6);
		ClientHandler cp;
		sl.start(cp);
		//Verbose::show("press key to exit: ", always);
		std::cout.flush();
		std::cin.get();
	}
	catch (std::exception& ex)
	{
		Verbose::show("  Exception caught:", always);
		Verbose::show(std::string("\n  ") + ex.what() + "\n\n");
	}
}

//----------------------------Client Receiving acknowledgement from Server----------------------------//
void Receiver::ReceiverforUploadtoClient(std::string clientportnumber, std::string serverportnumber, std::string Path, std::string Pattern, std::string TextSearch, std::string category, std::string dwnfile)
{
	
	title("Client listening to \t" + clientportnumber);
	try
	{
		std::istringstream ciss(clientportnumber);
		size_t clientport;
		ciss >> clientport;
		Verbose v(true);
		SocketSystem css;
		SocketListener csl(clientport, Socket::IP6);
		ServerHandler cp;
		cp.getpathpatterntextsearch(Path, Pattern, TextSearch, category, dwnfile);
		csl.start(cp);
		//Verbose::show("press key to exit: ", always);
		std::cout.flush();
		std::cin.get();
	}
	catch (std::exception& ex)
	{
		Verbose::show("  Exception caught:", always);
		Verbose::show(std::string("\n  ") + ex.what() + "\n\n");
	}
}

//-------This method gets the path pattern and text search from the Client------------------------------------//
void ServerHandler::getpathpatterntextsearch(std::string Path, std::string Pattern, std::string TextSearch, std::string category, std::string dwnldfile)
{
	sPath = Path;
	sPattern = Pattern;
	sTextsearch = TextSearch;
	sdwnldflnm = dwnldfile;
	scategory = category;
}

//----------------------Operator overloading in the Client side using Server Handler-----------------------//

void ServerHandler::operator()(Socket& socket_)
{


	while (true)
	{
		std::string command = socket_.recvString();
		if (command.size() == 0)
			break;
		//Verbose::show("Client command Received From Server: " + command);
		if (testServerStringHandling(socket_))
			Verbose::show("----Client Message Receiving test passed", always);
		else
		{
			Verbose::show("----Client Message Receiving test failed", always);
			break;
		}
	}
	//Verbose::show("ServerHandler socket connection closing");
	socket_.shutDown();
	socket_.close();
	//Verbose::show("ServerHandler thread terminating");
}

//---------------------------------Dequeueing the threads in Blocking queue in Client side----------------------------//

void ServerHandler::deqFromBQ(std::promise<std::string> &p)
{
	p.set_value(sbq.deQ());
}

//-----------------------------This method is instantiated in the Client Side to handle Server response------------//
//-----------------------Blocking queue is implemented to handle multiple Clients and Servers----------------------//

bool ServerHandler::testServerStringHandling(Socket& socket_)
{
	title("Client Receiving message from Server");
	MessagePasrer mp1;
	while (true)
	{
		if (socket_.bytesWaiting() == 0)
			break;
		std::string str = socket_.recvString();
		if (socket_ == INVALID_SOCKET)
			return false;
		if (str.size() > 0)
		{
			thread thrs1(&BlockingQueue<string>::enQ, &sbq, str);
			promise<string> p;
			thread trs2(&ServerHandler::deqFromBQ, this, std::ref(p));
			thrs1.join();
			trs2.join();
		}
		if (str.find("uploaded Succcessfully") != std::string::npos)
		{
			HandleUploadClientend(str);
		}
		if (str.find("Download") != std::string::npos) //once all the packets are sent then the Sender instance is created
		{
			HandleDownloadClientend(str,mp1);
		}
		if (str.find("FileEndSearch") != std::string::npos)
		{
			HandleFileSearchClientend(str);
		}
		if (str.find("FileFinishSearch") != std::string::npos) // now sending request for the Text Search from the Client 
		{
			string pathandcategory1 = sPath + scategory;
			Sender clientsnd3; // initiating request for text search from the Client
			string textsearch = sTextsearch;
			clientsnd3.CopypathpatterntextforSileSearch(pathandcategory1, sPattern);
			clientsnd3.CopyTextSearch(textsearch);
			clientsnd3.ClientSendermain(SrvrPrt, ClntPrt, sdwnldflnm, "TextSearch");
		}
		if (str.find("TextEndSearch") != std::string::npos)
		{
			HandleTextSearchClientend(str);
		}
		if (str.size() > 0)
		{
		}
		else
		break;
	}
	return true;
}
//--------------------This method handles the download and initiates request fro file search from the Server in the Client Side------------------------------------------//
void ServerHandler::HandleDownloadClientend(std::string str, MessagePasrer &mp1)
{
	mp1.messageParsing(str);
	if (str.find("TEST_STOP") != std::string::npos)
	{
		//after test_stop we write into the file and send back acknowledgement
		HandleDownloadbywriting(str, mp1); // 
		Sender clientsnd2; // initiating request for FileSearch from the Client
		string pathandcategory = sPath + scategory;
		clientsnd2.CopypathpatterntextforSileSearch(pathandcategory, sPattern);
		clientsnd2.ClientSendermain(SrvrPrt, ClntPrt, sdwnldflnm, "FileSearch");
	}
}

//--------------------After the FileUpload, the next request for the download is initiated from the Client----------------------------//
void ServerHandler::HandleUploadClientend(std::string str)
{
	std::string nwsmlone = "Destination Port: "; // Extract Server Port Number
	size_t index = str.find("Destination Port: ");
	for (size_t i = index + nwsmlone.size(); i < str.find("  Source Address:"); i++)
		SrvrPrt += str[i];
	std::string nwsmlone1 = "Source Port: "; // Extract Server Port Number
	size_t index1 = str.find("Source Port: ");
	for (size_t i = index1 + nwsmlone1.size(); i < str.find("  Destination Port:"); i++)
		ClntPrt += str[i];
	Sender clientsnd; // initiating request for download from the Client
	clientsnd.ClientSendermain(SrvrPrt, ClntPrt, sdwnldflnm, "Download");
}

//----------------------This method handes the textSearch from the Client Side------------------------------------------------------//

void ServerHandler::HandleTextSearchClientend(std::string str)
{
	//cout << "Going to handle textSearch here\n";
	std::string smltrg;
	std::string nwsmlone = " Message: "; // Extract Client Port Number
	size_t index = str.find(" Message: ");
	for (size_t i = index + nwsmlone.size(); i < str.size(); i++)
		smltrg += str[i];
	string tmp = "";
	title("TextSearch Results in Client side showing the filenames and their corresponding paths as shown below:", '=');
	//Verbose::show("TextSearch Results in Client side showing the filenames and their corresponding paths are as follows:", always);
	//cout << "TextSearch Results in Client side are as follows:";
	for (size_t i = 0; i < smltrg.size(); i++)
	{
		if (smltrg[i] == ':')
		{
			if (tmp.size()>0)
				Verbose::show(tmp, always);
			i++;
			tmp = "";
		}
		tmp += smltrg[i];
	}
}
//---------------------here we are parsing the Output of FileSearch to display in client side-----------------------------------//
void ServerHandler::HandleFileSearchClientend(std::string str)
{

	std::string smltrg;
	std::string nwsmlone = " Message: "; // Extract Client Port Number
	size_t index = str.find(" Message: ");
	for (size_t i = index + nwsmlone.size(); i < str.size(); i++)
		smltrg += str[i];
	string tmp = "";
	title("FileSearch Results in Client side showing the filenames and their corresponding paths as shown below:",'=');

	//Verbose::show("FileSearch Results in Client side showing the filenames and their corresponding paths are as follows:", always);
	//cout << "\nFileSearch Results in Client side are as follows:\n";
	for (size_t i = 0; i < smltrg.size();i++)
	{
		if (smltrg[i] ==':')
		{
			if (tmp.size()>0)
		Verbose::show(tmp, always);
			i++;
			tmp = "";
		}
		tmp += smltrg[i];	
	}
}

//-------------------------Download File and Send Acknowledgement from the Client for the successful download--------------------//
void ServerHandler::HandleDownloadbywriting(std::string str, MessagePasrer &mp)
{
	Verbose::show("server recvd : " + str, always); //Threads in the Blocking queue to handle multiple Clients and Servers
	thread thr1(&BlockingQueue<string>::enQ, &sbq, str);
	promise<string> p;
	thread tr2(&ServerHandler::deqFromBQ, this, std::ref(p));
	thr1.join();
	tr2.join();
	std::string smltrg;
	std::string nwsmlone = "ClientPort: "; // Extract Client Port Number
	size_t index = str.find("ClientPort: ");
	for (size_t i = index + nwsmlone.size(); i < str.find("ServerPort: "); i++)
		smltrg += str[i];
	std::string smltrg1;
	std::string nwsmlone1 = "ServerPort: ";  // Extract Server Port Number
	size_t index1 = str.find("ServerPort: ");
	for (size_t j = index1 + nwsmlone1.size(); j < str.find("TEST_STOP"); j++)
		smltrg1 += str[j];
	mp.FileWritingforDownload();
	//Clientsendermain
	//Verbose::show("The download has been completed successfully", always);
	//cout << "The download has been completed successfully\n";

}

//------------------- Test stub for testing the current package-------------------------------//

#ifdef Test_Receiver
#include"Receiver.h"
int main()
{
	Receiver rcvr;
	rcvr.ReceiverforUploadfromServer("9076","9075");
	rcvr.ReceiverforUploadtoClient("9076","9075","../Server/Repository","*.h","class","Header_file","../Sample1.cpp");
	return 0;
}

#endif // Test_Receiver