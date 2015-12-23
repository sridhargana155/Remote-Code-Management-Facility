#include "MessageHandler.h"
/////////////////////////////////////////////////////////////////////////////
// MessageHandler.cpp - The message packets are parsed and handled  on both  //
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

//------------------------Opening a file and reading the strings from the Client Side----------------------------------------------//
//------------------------------Requirement 5------------------------------------------------------------//
//----------Transporting the Text File as well as the Binary File from one peer to another-----------------//

std::vector<string> MessageHandler::ProcessingtoFullStringforUpload(std::string FileName, std::string ServerPort, std::string ClientPort)
{
	std::string path = "./";
	std::string Pathandfilename = path + FileName;
	std::string line; std::vector<string> holdscontent, stringreceivd;
	fstream flopn;
	string changer = FileSystem::Path::getFullFileSpec(Pathandfilename);
	string container;
	for (size_t j = 0; j < changer.size(); j++)
	{
		if (changer[j] == '\\') // change the slash to get abosolute address
			changer[j] = '/';
	}
	flopn.open(changer,ios::binary|ios::in); // to handle both binary and text files
	if (!flopn)
	{
		cout << "Unable to open file" << endl;
		exit(1);
	}
	while (flopn.good())// return true if none of the stream's error state is set.
	{
		getline(flopn, line); // get line from file
		container += line;
	}
	//cout << "container" << container;
	holdscontent = BreakStrings(container);
	stringreceivd = PreparedSendStringforUpload(holdscontent, ServerPort, ClientPort, FileName);
	return stringreceivd;
}

//------------------This method takes care of the downloading part from the Server--------------------------------------//

std::vector<string> MessageHandler::ProcessingtoFullStringforDownload(std::string FileName, std::string ServerPort, std::string ClientPort)
{
	std::string path = "./"; // should be changed accordingly when running from run.bat
	std::string Pathandfilename = path + FileName;
	std::string line; std::vector<string> holdscontent, stringreceivd;
	fstream flopn;
	string changer = FileSystem::Path::getFullFileSpec(Pathandfilename);
	string container;
	for (size_t j = 0; j < changer.size(); j++)
	{
		if (changer[j] == '\\') // change the slash to get abosolute address
			changer[j] = '/';
	}
	flopn.open(changer, ios::binary | ios::in); // to handle both binary and text files
	if (!flopn)
	{
		cout << "Unable to open file" << endl;
		exit(1);
	}
	while (flopn.good())// return true if none of the stream's error state is set.
	{
		getline(flopn, line); // get line from file
		container += line;
	}
	//cout << "container" << container;
	holdscontent = BreakStrings(container);
	stringreceivd = PreparedSendStringforDownload(holdscontent, ServerPort, ClientPort, FileName);
	return stringreceivd;
}




//--------------------------Breaking the Strings in to Blocks of 10 bytes---------------------------------------------
std::vector<std::string> MessageHandler::BreakStrings(std::string wholeString)
{
	//cout << "I'm from BreakStrings\t" << temp;
	std::vector<std::string> StringCutter;
	string brokenword = "";
	size_t blocks = 10, limiter = wholeString.size();
	for (size_t i = 0; i < blocks; i++)
	{
		if (i == limiter - 1)
		{
			StringCutter.push_back(brokenword);
			break;
		}
		brokenword += wholeString[i];
		if (i == blocks - 1)
		{
			StringCutter.push_back(brokenword);
			brokenword = "";
			blocks = blocks + 10;
		}
	}
	return StringCutter;
}

std::vector<string> MessageHandler::PreparedSendStringforDownload(std::vector<string> containscontent, std::string ServerPort, std::string ClientPort, std::string FileName)
{
	string cmd = " Command : Download";
	string flnm = " FileName : " + FileName;
	string SourcePort = " ClientPort: " + ClientPort;
	string DestnPort = " ServerPort: " + ServerPort;
	string SourceAddress = " localhost";
	string DestinationAddress = " localhost";
	string wholecontent = cmd + flnm + SourcePort + SourceAddress + DestnPort + DestinationAddress;
	string FinalString = "";
	//string ContentLength;
	string indexsize;
	std::vector<string> Packets;
	for (auto tmp : containscontent)
	{
		stringstream s1;
		s1 << tmp.size();
		string getnw = s1.str();
		/*	cout << "getnw" << getnw;*/
		FinalString = wholecontent + " ContentLength: " + getnw + "bytes Body: " + tmp;
		Packets.push_back(FinalString);
	}

	//title("HTTP messages constructed from Server's side", '=');
	//for (auto i : Packets)
	//	cout << "\n" << i;
	return Packets;
}

//---------------------------Creating HTTP Packets to send it across to the receiver from the sender----------------//
std::vector<string> MessageHandler::PreparedSendStringforUpload(std::vector<string> containscontent, std::string ServerPort, std::string ClientPort, std::string FileName)
{
	string cmd = " Command : Upload";
	string flnm = " FileName : " + FileName;
	string SourcePort = " ClientPort: " + ClientPort;
	string DestnPort = " ServerPort: " + ServerPort;
	string SourceAddress = " localhost";
	string DestinationAddress = " localhost";
	string wholecontent = cmd + flnm + SourcePort + SourceAddress + DestnPort + DestinationAddress;
	string FinalString = "";
	//string ContentLength;
	string indexsize;
	std::vector<string> Packets;
	for (auto tmp : containscontent)
	{
		stringstream s1;
		s1 << tmp.size();
		string getnw = s1.str();
		/*	cout << "getnw" << getnw;*/
		FinalString = wholecontent + " ContentLength: " + getnw +"bytes Body: " + tmp;
		Packets.push_back(FinalString);
	}
	/*title("HTTP messages constructed from Client's side",'=');
	for (auto i : Packets)
		cout <<"\n"<<i;*/
	return Packets;
}

//---------------------------Parsing the message on the server side to filter out the body content and Port details-----------------------//
void MessagePasrer::messageParsing(std::string temp)
{
	//Extract body
	std::string smlone = "Body: ";
	if (temp.find("Body: ") != std::string::npos)
	{
		size_t index = temp.find("Body: ");
		for (size_t i = index + smlone.size(); i < temp.size(); i++)
			bigstring += temp[i];
	}
	//Extract FileName: 
	if (temp.find("TEST_STOP") != std::string::npos)
	{
		std::string flnmcpy;
		std::string nwsmlone = "FileName: ";
		size_t index = temp.find("FileName: ");
		for (size_t i = index + nwsmlone.size(); i < temp.find("ClientPort: "); i++)
			flnmcpy += temp[i];
		filnm = flnmcpy;
	}
}
//--------File writing on the server side------------//
void MessagePasrer::FileWritingforUpload()
{
	//appends the filename  with the path here
	string pathtmp = "./Server/Uploaded_Files/";   // should be changed accordingly when running from run.bat
	string pathwtfinm = pathtmp + filnm;
	ofstream outputFile;
	outputFile.open(pathwtfinm);
	title("\nFile Uploading is Successfull from the Client to the Server.!!The Uploaded file is present in this path: Server/Uploaded_Files",'=');
	outputFile << bigstring;
}

void MessagePasrer::FileWritingforDownload()
{
	string pathtmp = "./Client/Downloaded_Files/"; // should be changed accordingly when running from run.bat
	string pathwtfinm = pathtmp + filnm;
	ofstream outputFile;
	outputFile.open(pathwtfinm);
	title("\nFile Downloading is Successfull from the Server to the Client.!!The downloaded file is present in this path: Client/Downloaded_Files",'=');
	outputFile << bigstring;

}

//------------------- Test stub for testing the current package-------------------------------//
#ifdef Test_MessageHandler
#include"MessageHandler.h"
int main()
{
	MessageHandler msghd;
	std::vector<string> testvctr;
	std::vector<string> testvctr2;
	testvctr2.push_back("Syracuse University");
	testvctr2.push_back("Slocum Hall");
	std::string teststrng = "All that glitters are not gold.";
	msghd.PreparedSendStringforUpload(testvctr2, "9076", "9075", "Sample.txt");
	testvctr = msghd.BreakStrings(teststrng);
	msghd.ProcessingtoFullStringforUpload("Sample.txt", "9076", "9075");

	return 0;
}
#endif // Test_MessageHandler