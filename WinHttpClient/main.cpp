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
		std::cout << "fail request.SendHttpRequest(L\"POST\")" << std::endl;
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
	sendResultsToReportServer(L"{Som data in json format by HTTP}", L"http://localhost:9000", false);

	sendResultsToReportServer(L"{Som data in json format by HTTPS}", L"https://localhost:9001", true);

	//from https://developers.google.com/chart/image/docs/post_requests
 //    std::wstring  strReq = L"<input type=\"hidden\" name=\"cht\" value=\"lc\"  /><input type=\"hidden\" name=\"chtt\" value=\"This is | my chart\"  />";
	//strReq += L"<input type='hidden' name='chs' value='300x200' /><input type=\"hidden\" name=\"chxt\" value=\"x\" /><input type='hidden' name='chd' value='t:40,20,50,20,100'/>";
 //   strReq += L"<input type=\"submit\"  />";
	//sendResultsToReportServer(strReq, L"https://chart.googleapis.com/chart", true);

	sendResultsToReportServer(L"{TestProba HTTPS}", L"https://192.168.82.148:9001", true);

//	std::system("Pause");
	return 0;
}

