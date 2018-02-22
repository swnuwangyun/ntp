// ntp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <map>
#include <Windows.h>
#include "libtimestamp.h"
#include "libntp.h"
#include "libtext.h"
#include "libpath.h"
#include "libfile.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{  
	wstring path = libpath::combine(libpath::getTempPath(), L"ntp_local_ref.ini");
	
	libfile::deleteFile(path);

	long int ntp = libntp::seconds();
	long int sec = libtimestamp::seconds();

	if(ntp)
	{
		map<wstring, wstring> dict;
		dict[L"ntp_timestamp_seconds"] = libtext::Int64ToWString(ntp);
		dict[L"local_timestamp_seconds"] = libtext::Int64ToWString(sec);
		dict[L"local_ticks"] = libtext::Int64ToWString(GetTickCount());

		libtext::writeKeyValuesToFile(path, dict);
	}

	return 0;  
}