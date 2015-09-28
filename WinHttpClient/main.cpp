// WinHttpClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "WinHttpClient.h"

bool sendResultsToReportServer(std::tstring strJsonResults, std::tstring serverURL )
{
	WinHttpClient request(serverURL);
	wchar_t szSize[50] = L"";

	// Set post data.
	request.SetAdditionalDataToSend((BYTE *)strJsonResults.c_str(), strJsonResults.length()*sizeof(TCHAR));
	swprintf_s(szSize, L"%d", strJsonResults.length()*sizeof(TCHAR));

	// Set request headers.
	wstring headers = L"Content-Length: ";
	headers += szSize;
	headers += L"\r\nContent-Type: binary/octet-stream\r\n";
	request.SetAdditionalRequestHeaders(headers);
	

	// Send http post request.
	if ( !request.SendHttpRequest(L"POST") )
		return false;

	wstring httpResponseCode = request.GetResponseStatusCode();
	wstring httpResponseHeader = request.GetResponseHeader();
	wstring httpResponseContent = request.GetResponseContent();
		
	if ( httpResponseCode != L"200" ) 
		return false;

	return true;
}


int _tmain(int argc, _TCHAR* argv[])
{
	// How to use
	sendResultsToReportServer(L"{Som data in json format}", L"http:\\localhost:9000");
	return 0;
}

