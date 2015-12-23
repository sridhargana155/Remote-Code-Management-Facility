#include "Sender.h"
/////////////////////////////////////////////////////////////////////////////
// Sender.cpp - Sends the request to peer and waits for a response.        //
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


//---------------------Display to terminate-----------------------------//
struct Cosmetic
{
	~Cosmetic()
	{
		cout << "\n  press key to exit: ";
		cin.get();
		cout << "\n\n";
	}
} aGlobalForCosmeticAction;

//------------------Calls the message parsing for constructiing the message-----------------------------//
void Sender::ReceiveStringfromClientforUpload(std::string ServerPort, std::string ClientPort, std::string FileName)
{
	MessageHandler mh;
	std::string cmd1 = "Upload";
	resultantvector = mh.ProcessingtoFullStringforUpload(FileName, ServerPort, ClientPort);
	ClientSendermain(ServerPort, ClientPort, FileName, cmd1);
}

//------------------------receiving the request for the download operation, processing it from the server side----------------//
void Sender::ReceiveStringfromServerforDownload(std::string ServerPort, std::string ClientPort, std::string FileName)
{
	MessageHandler md;
	std::string cmd1 = "Download";
	FilenameforServer = FileName;
	resultantvector2 = md.ProcessingtoFullStringforDownload(FileName, ServerPort, ClientPort);
	ServerSendermain(ServerPort, ClientPort, cmd1);
}

//--------------------receiving the Request for text search and Processing the request inthe server side-----------------------//
void Sender::ReceiveStringfromServerforTextSearch(std::string ServerPort, std::string ClientPort, std::string TextSearchFiles)
{
	std::string cmd1 = "TestSearch";
	FilenamesforTextSearch = TextSearchFiles;	
	ServerSendermain(ClientPort, ServerPort, cmd1);
}

//-----------------------Gets the searched filenames and send it to Sender---------------------------//

void Sender::ReceiveStringfromServerforFileSearch(std::string ServerPort, std::string ClientPort, std::string SearchedFilenames)
{
	std::string cmd1 = "FileSearch";
	FilenameSearches = SearchedFilenames;
	ServerSendermain(ClientPort, ServerPort, cmd1);
}



//-----------function that sends all the packets to the receiver from Client--------------------------------//
void Sender::ClientSendermain(std::string ServerPort, std::string ClientPort, std::string FileName, std::string Keyword)
{
	//title("Uploading File in the form of HTTP Packets from the Client to the Server", '=');
	try
	{
		std::istringstream iss(ServerPort);
		size_t sverport;
		iss >> sverport;
		Verbose v(true);
		SocketSystem ss;
		SocketConnecter si;
		while (!si.connect("localhost", sverport))
		{
			Verbose::show("client waiting to connect");
			::Sleep(100);
		}
		if (Keyword=="Upload")
		{
			SendUpload(resultantvector, ServerPort, ClientPort, FileName, si);
		}
		if (Keyword == "Download")
		{
			Senddownload(ServerPort, ClientPort, FileName, si);
		}
		if (Keyword=="FileSearch")
		{
			SendFileSearch(ServerPort, ClientPort, FileName, si);
		}
		if (Keyword == "TextSearch")
		{
			SendTextSearch(ServerPort, ClientPort, FileName, si);
		}
		si.shutDownSend();
	}
	catch (std::exception& ex)
	{
		Verbose::show("  Exception caught:", always);
		Verbose::show(std::string("\n  ") + ex.what() + "\n\n");
	}
}

//-----------------------this method is to copy the textsearch-------------------------------------------//
void Sender::CopyTextSearch(std::string txtsrch)
{
	sendrtextSearch = txtsrch;
}

//-----------------Sending TextSearch Request from the Client---------------------------------------//
void Sender::SendTextSearch(std::string ServerPort, std::string ClientPort, std::string FileName, SocketConnecter &si)
{
	string txt = "Seding_TextSearch";
	string cnt = "Command: TextSearch Source Port: " + ClientPort + " Destination Port: " + ServerPort + " Source Address: localhost Destination Address: localhost Body: " + txt;
	si.sendString(cnt);
	string cnt1 = "Command: TextSearch Source Port: " + ClientPort + " Destination Port: " + ServerPort + " Source Address: localhost Destination Address: localhost Path: " + sendrpath + " Pattern: " + sendrpattern + " TextSearch: " + sendrtextSearch;
	si.sendString(cnt1);
}

//-----------------------this method copies the path and pattern----------------------------------------------//
void Sender::CopypathpatterntextforSileSearch(std::string path, std::string pattern)
{
	sendrpath = path;
	sendrpattern = pattern;
}

//---------------------Sending FileSearch from Client---------------------------------------------------//
void Sender::SendFileSearch(std::string ServerPort, std::string ClientPort, std::string FileName, SocketConnecter &si)
{
	string txt = "FileSearch";
	string cnt = "Command: FileSearch Source Port: " + ClientPort + " Destination Port: " + ServerPort + " Source Address: localhost Destination Address: localhost Body: " + txt;
	si.sendString(cnt);
	string cnt1 = "Command: FileSearch Source Port: " + ClientPort + " Destination Port: " + ServerPort + " Source Address: localhost Destination Address: localhost Path: " + sendrpath + " Pattern: "+sendrpattern;
	si.sendString(cnt1);

}
//-----------------------------Request for Download from the Client------------------------------------------------------------//
void Sender::Senddownload(std::string ServerPort, std::string ClientPort, std::string FileName, SocketConnecter &si)
{
	string cnt = "Command: Download Source Port: " + ClientPort + " Destination Port: " + ServerPort + " Source Address: localhost Destination Address: localhost";
	si.sendString(cnt);
	string cnt1 = "Command: Download Source Port: " + ClientPort + " Destination Port: " + ServerPort + " Source Address: localhost Destination Address: localhost Filename: " + FileName;
	si.sendString(cnt1);
}
//---------------------FileUpload from the client------------------------------------------------//
void Sender::SendUpload(std::vector<string> resultantvector, std::string ServerPort, std::string ClientPort, std::string FileName, SocketConnecter &si)
{

	string cnt = "Command: Upload Source Port: " + ClientPort + " Destination Port: " + ServerPort + " Source Address: localhost Destination Address: localhost";
	cout << "\n";
	si.sendString(cnt);
	for (auto sngl : resultantvector)
	{
		thread th1(&BlockingQueue<string>::enQ, &sbq, sngl);
		promise<string> p;
		thread t2(&Sender::deqFromBQ, this, std::ref(p));
		th1.join();
		t2.join();
		si.sendString(sngl);
	}
	si.sendString("Command: Upload FileName: " + FileName + " ClientPort: " + ClientPort + " ServerPort: " + ServerPort + " TEST_STOP");
}

//--------------------Dequeueing the threads in the Blocking Queue in while sending--------------------------------------------//

void Sender::deqFromBQ(std::promise<std::string> &p)
{
	p.set_value(sbq.deQ());
}


//--------------------main function for sending Acknowledgement from the server---------------------------------------//
void Sender::ServerSendermain(std::string ClientPort, std::string ServerPort, std::string Keyword)
{
	try
	{
		std::istringstream iss(ClientPort);
		size_t clientport;
		iss >> clientport;
		Verbose v(true);
		SocketSystem ss;
		SocketConnecter si;
		while (!si.connect("localhost", clientport))
		{
			Verbose::show("Server waiting to connect");
			::Sleep(100);
		}
		cout << "\n";
		if (Keyword == "acknowledgement")
		{
			HandleAcknowledgementforUploadSendSvr(ClientPort, ServerPort, si);
		}
		if (Keyword == "Download")
		{
			HandleDownloadSendSvr(ClientPort, ServerPort, si);
		
		}		
		if (Keyword == "FileSearch")
		{
			HandleFileSearchSendSvr(ClientPort, ServerPort, si);
		}
		if (Keyword == "TestSearch")
		{
			HandleTextSearchSendSvr(ClientPort, ServerPort, si);
		}
			si.shutDownSend();
	}
	catch (std::exception& ex)
	{
		Verbose::show("  Exception caught:", always);
		Verbose::show(std::string("\n  ") + ex.what() + "\n\n");
	}
}

//----------------------Sends back the acknowledgement to the Client after uploading is compeleted-------------------------------//
void Sender::HandleAcknowledgementforUploadSendSvr(std::string ClientPort, std::string ServerPort, SocketConnecter &si)
{
	string sendstr1 = "Acknowledgement";
	string sendstr2 = "The File has been uploaded Succcessfully";
	string text1 = "\nCommand: Upload Source Port: " + ClientPort + " Destination Port: " + ServerPort + " Source Address: localhost Destination Address: localhost Message: " + sendstr1;
	string text2 = "\nCommand: Upload Source Port: " + ClientPort + " Destination Port: " + ServerPort + " Source Address: localhost Destination Address: localhost Message: " + sendstr2;
	si.sendString(text1);
	thread th3(&BlockingQueue<string>::enQ, &sbq, text2); //Threads in the Blocking queue to handle multiple Clients and Servers
	promise<string> p;
	thread t4(&Sender::deqFromBQ, this, std::ref(p));
	th3.join();
	t4.join();
	si.sendString(text2);
}

//---------------------Sends back the response for the Download to the Client from the Server-----------------------------------------//
void Sender::HandleDownloadSendSvr(std::string ClientPort, std::string ServerPort, SocketConnecter &si)
{
	string svr = "Command: Download Source Port: " + ClientPort + " Destination Port: " + ServerPort + " Source Address: localhost Destination Address: localhost";
	cout << "\n";
	si.sendString(svr);
	for (auto sn : resultantvector2)
	{
		thread th1(&BlockingQueue<string>::enQ, &sbq, sn);
		promise<string> p;
		thread t2(&Sender::deqFromBQ, this, std::ref(p));
		th1.join();
		t2.join();
		si.sendString(sn);
	}
	string dnr = "Command: Download FileName: " + FilenameforServer + " ClientPort: " + ClientPort + " ServerPort: " + ServerPort + " TEST_STOP";
	si.sendString(dnr);
}

//---------------------------Sends back the response to the Client for the FileSearch Request from the Server----------------------//
void Sender::HandleFileSearchSendSvr(std::string ClientPort, std::string ServerPort, SocketConnecter &si)
{
	string sendstr3 = "Sending_FileSearch";
	string sendstr4 = FilenameSearches;
	string text3 = "Command: FileSearch Source Port: " + ClientPort + " Destination Port: " + ServerPort + " Source Address: localhost Destination Address: localhost Message: " + sendstr3;
	string text4 = "Command: FileEndSearch Source Port: " + ClientPort + " Destination Port: " + ServerPort + " Source Address: localhost Destination Address: localhost Message: " + sendstr4;
	si.sendString(text3);
	thread thflsrch(&BlockingQueue<string>::enQ, &sbq, text4); //Threads in the Blocking queue to handle multiple Clients and Servers
	promise<string> p;
	thread thflsrch1(&Sender::deqFromBQ, this, std::ref(p));
	thflsrch.join();
	thflsrch1.join();
	si.sendString(text4);
	si.sendString("Command: FileFinishSearch Source Port: " + ClientPort + " Destination Port: " + ServerPort + " Source Address: localhost Destination Address: localhost Message: FileSearch_TEST_STOP");

}

//--------------------Sends back the response to the Client for the textSearch request from the Server--------------------------------//
void Sender::HandleTextSearchSendSvr(std::string ClientPort, std::string ServerPort, SocketConnecter &si)
{
	string sendstr5 = "Sending_TextSearch";
	string sendstr6 = FilenamesforTextSearch;
	string text5 = "Command: TextSearch Source Port: " + ClientPort + " Destination Port: " + ServerPort + " Source Address: localhost Destination Address: localhost Message: " + sendstr5;
	string text6 = "Command: TextEndSearch Source Port: " + ClientPort + " Destination Port: " + ServerPort + " Source Address: localhost Destination Address: localhost Message: " + sendstr6;
	si.sendString(text5);
	thread thflsrch(&BlockingQueue<string>::enQ, &sbq, text6); //Threads in the Blocking queue to handle multiple Clients and Servers
	promise<string> p;
	thread thflsrch1(&Sender::deqFromBQ, this, std::ref(p));
	thflsrch.join();
	thflsrch1.join();
	si.sendString(text6);
	si.sendString("Command: TextFinishSearch Source Port: " + ClientPort + " Destination Port: " + ServerPort + " Source Address: localhost Destination Address: localhost Message: TextSearch_TEST_STOP");
}

//------------------- Test stub for testing the current package-------------------------------//
#ifdef Test_Sender
#include"Sender.h"

int main(){
	Sender snd;
	snd.ReceiveStringfromClientforUpload("9076", "9075", "../Executive/Sample1.cpp");
	snd.ClientSendermain("9076", "9075", "../Executive/Sample1.cpp","acknowledgement");
	snd.ServerSendermain("9076", "9075","acknowledgement");
	cout << "Testing Sender\n";

	return 0;
}

#endif // Test_Sender
