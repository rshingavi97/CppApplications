
/*
Purpose : Demo of creating Config.json file at following locations:
		  WIN32:
				\ProgramData\Testing\Config.json
		  Linux:
				//usr//local//share//apps//Testing//Config.json
		 Note: Above "Testing" is a temporary directory gets created if not exist.
			   Particular JSON file gets created with temporary data.	

Linux :  g++ FileHandling.cpp -o FileHandling  [Command to build it on Linux]
Note: This is platform independent code base.
*/

#ifdef _WIN32
#include <Windows.h>
#elif __linux__
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#endif
#include <cstring>
#include<iostream>
#include<fstream>
using namespace std;

#ifdef _WIN32
#define JSON_FILE "\\Config.json" 
#define JSON_DIR  "\\Testing"
#elif __linux__
#define  JSON_FILE  "//Config.json"  
#define JSON_DIR  "//usr//local//share//apps//Testing"
#endif

/*
Purpose :  Verifying whether given file is existed or not.
*/
bool IsFileExist(std::string m_szJsonFile)
{
	bool bResult=true;
	//lets check about directory first.
	std::ifstream in(m_szJsonFile.c_str(),std::ifstream::binary);
	bResult=in.fail();
	in.close();
	return bResult;
}

/*
Purpose :  Verifying whether given directory is existed or not.
		   If not , then creating it.
*/
bool IsDirtoryExist(std::string m_szDir)
{
	bool bResult = true;
#if _WIN32
	bResult = CreateDirectory( m_szDir.c_str(),NULL);
	if ( bResult == false )
	{
		DWORD error = GetLastError();
		if (ERROR_ALREADY_EXISTS == error)
		{
			std::cout << strerror ( error);
		    bResult = true;
		}
		else
		{
			std::cout << strerror ( error);
		}
	}
	std::cout << m_szDir.c_str() <<" directory is created" << std::endl;
#elif __linux__
	int result = mkdir(m_szDir.c_str(), 0777);
	if ( result == -1 )
	{
		if ( errno == EEXIST)
		{
			bResult = true;	  
			std::cout << strerror(errno) <<std::endl;
		}
	 else
		{
			 bResult = false;
			 __pragma(warning(push))
		__pragma(warning(disable:4996))
			std::cout << strerror(errno) <<std::endl;
		__pragma(warning(push))
			
		}
	}
#endif
 return bResult;
}

int main()
{
std::string m_szJsonFile;
#ifdef _WIN32
char *pszBuff = getenv("ProgramData");
m_szJsonFile += std::string(pszBuff);
#elif __linux__
m_szJsonFile += std::string(JSON_DIR);
#endif
if ( IsDirtoryExist(m_szJsonFile) )
	{
		std::cout << std::endl << " Config.json file is not present. Lets create it";
		m_szJsonFile += std::string(JSON_FILE);
		if (IsFileExist(m_szJsonFile))
		{
		std::ofstream out(m_szJsonFile.c_str(),std::ofstream::binary);
		if (out.fail())
			{
				std::cout << "Config.Json could not be created";
				return false;
			}
		out << "Hello Rupesh ,\n\tThanks for doing this";
		out.close();
		std::cout << std::endl << "Config file has been created ";
		}
	}
getchar();
return 0;
}