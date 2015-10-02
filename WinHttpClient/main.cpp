// WinHttpClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "WinHttpClient.h"

bool sendResultsToReportServer(std::tstring strJsonResults, std::tstring serverURL, bool securityConnection )
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
	if ( !request.SendHttpRequest(L"POST", false, securityConnection))
	{
		std::wcout << L"fail request.SendHttpRequest(L\"POST\") - " << request.GetStatusCode()<< std::endl;
		return false;
	}

	wstring httpResponseCode = request.GetResponseStatusCode();
	wstring httpResponseHeader = request.GetResponseHeader();
	wstring httpResponseContent = request.GetResponseContent();
		
	if ( httpResponseCode != L"200" ) 
	{
		std::wcout << L"fail httpResponseCode != L\"200\" " << httpResponseCode << std::endl;
		return false;
	}

	std::cout << "Good" << std::endl;
	return true;
}


int _tmain(int argc, _TCHAR* argv[])
{
	// How to use
	sendResultsToReportServer(L"{Some data in json format by HTTP}", L"http://localhost:9000", false);

	sendResultsToReportServer(L"{Some data in json format by HTTPS}", L"https://localhost:9001", true);

//	from https://developers.google.com/chart/image/docs/post_requests
    std::wstring  strReq = L"Test Google";
	sendResultsToReportServer(strReq, L"https://chart.googleapis.com/chart", true); //response 400 error is normal

	sendResultsToReportServer(L"{TestProba HTTP}", L"http://192.168.82.148:9000", false);
	sendResultsToReportServer(L"{TestProba HTTPS}", L"https://192.168.82.148", true); //default 443 port - WireShark sees TLS packets  only from 443 port

//	std::system("Pause");
	return 0;
}

