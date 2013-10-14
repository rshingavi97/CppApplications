
/*
Purpose : Demo of reading IP address [both IPv4 & IPv6].

Linux :  g++ ReadingIP.cpp -o ReadingIP  [Command to build it on Linux]

Note: This is platform independent code base.
*/

#if _WIN32
#include <winsock.h>
#elif __linux__
#include <netdb.h>
#include <sys/unistd.h>
#include <arpa/inet.h>
#endif
#include <cstdio>
#include <iostream>
using namespace std;

/*
Purpose: Reading IP of existing machine.
*/
void GetIP(std::string &IP)
{
	const hostent* host_info = 0 ;
	char host[128]; //IPv6 & IPv4
    if (gethostname(host, sizeof(host)) == SOCKET_ERROR) 
	{
		DWORD iError = GetLastError()
        std::cout << strerror
    }
  cout << "Host name is " << host << "." << endl;
  host_info = gethostbyname(host) ;
  if(host_info)
  {
    const in_addr* address = (in_addr*)host_info->h_addr_list[0] ;
	IP = inet_ntoa( *address );
  }
  else
  perror( "error" ) ;
  
}
int main()
{
  std::string IP;
#if _WIN32
   WSAData wsaData;
    if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) 
	{
        return 255;
    }
#endif
  GetIP(IP);
  cout << endl<<endl << "IP ::"<<IP.c_str();
  getchar();
  return 0;
}
