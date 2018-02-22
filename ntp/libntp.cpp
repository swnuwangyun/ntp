#include "libntp.h"
#include <Winsock2.h>
#include <winsock.h>

#pragma comment(lib,"ws2_32.lib")

namespace libntp
{
	struct NTP_Packet  
	{  
		int      Control_Word;
		int      root_delay;
		int      root_dispersion;
		int      reference_identifier;
		__int64  reference_timestamp;
		__int64  originate_timestamp;
		__int64  receive_timestamp;
		int      transmit_timestamp_seconds;
		int      transmit_timestamp_fractions;
	}; 

	long int seconds()
	{  
		WORD    wVersionRequested = MAKEWORD(1, 1);  
		WSADATA wsaData;  

		if (0!=WSAStartup(wVersionRequested, &wsaData))   
		{  
			WSACleanup();  
			return 0;  
		} 

		if (LOBYTE(wsaData.wVersion)!=1 || HIBYTE(wsaData.wVersion)!=1)   
		{  
			WSACleanup();  
			return 0;  
		}

		SOCKET soc=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);  
		struct sockaddr_in addrSrv;  

		struct hostent *ph = gethostbyname("time.windows.com");
		in_addr addr;  
		memcpy(&addr, ph->h_addr_list[0], sizeof(in_addr));
		char *ip = inet_ntoa(addr);

		addrSrv.sin_addr.S_un.S_addr=inet_addr(ip);  
		addrSrv.sin_family=AF_INET;  
		addrSrv.sin_port=htons(123);  

		NTP_Packet NTP_Send,NTP_Recv;   
		NTP_Send.Control_Word					= htonl(0x0B000000);     
		NTP_Send.root_delay						= 0;     
		NTP_Send.root_dispersion				= 0;     
		NTP_Send.reference_identifier			= 0;     
		NTP_Send.reference_timestamp			= 0;     
		NTP_Send.originate_timestamp			= 0;     
		NTP_Send.receive_timestamp				= 0;     
		NTP_Send.transmit_timestamp_seconds     = 0;     
		NTP_Send.transmit_timestamp_fractions   = 0;   

		if(SOCKET_ERROR==sendto(soc,(const char*)&NTP_Send,sizeof(NTP_Send), 0, (struct sockaddr*)&addrSrv, sizeof(addrSrv)))  
		{  
			closesocket(soc);  
			return 0;  
		}

		int sockaddr_Size =sizeof(addrSrv);  
		if(SOCKET_ERROR==recvfrom(soc,(char*)&NTP_Recv,sizeof(NTP_Recv), 0, (struct sockaddr*)&addrSrv, &sockaddr_Size))  
		{  
			closesocket(soc);  
			return 0;  
		}  
		closesocket(soc);
		WSACleanup();

		time_t ntp_time = ntohl(NTP_Recv.transmit_timestamp_seconds) - 2208988800;

		return (long int)ntp_time;
	}
}