#include <Windows.h>
#include <winhttp.h>
#include<iostream>
#pragma comment(lib,"winhttp.lib")

int main() {
	LPSTR pszData = "WinHttpWriteData Example";
	DWORD dwBytesWritten = 0;
	BOOL  bResults = FALSE;
	HINTERNET hSession = NULL,
		hConnect = NULL,
		hRequest = NULL;

	// Use WinHttpOpen to obtain a session handle.
	hSession = WinHttpOpen(L"A WinHTTP Example Program/1.0",
		WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
		WINHTTP_NO_PROXY_NAME,
		WINHTTP_NO_PROXY_BYPASS, 0);

	// Specify an HTTP server.
	if (hSession)
		hConnect = WinHttpConnect(hSession, L"www.wingtiptoys.com",
			INTERNET_DEFAULT_HTTP_PORT, 0);

	// Create an HTTP Request handle.
	if (hConnect)
		hRequest = WinHttpOpenRequest(hConnect, L"GET",
			L"/writetst.txt",
			NULL, WINHTTP_NO_REFERER,
			WINHTTP_DEFAULT_ACCEPT_TYPES,
			0);

	// Send a Request.
	if (hRequest)
		bResults = WinHttpSendRequest(hRequest,
			WINHTTP_NO_ADDITIONAL_HEADERS,
			0, WINHTTP_NO_REQUEST_DATA, 0,
			(DWORD)strlen(pszData), 0);

	// Write data to the server.
	if (bResults)
		bResults = WinHttpWriteData(hRequest, pszData,
			(DWORD)strlen(pszData),
			&dwBytesWritten);

	// End the request.
	if (bResults)
		bResults = WinHttpReceiveResponse(hRequest, NULL);

	// Report any errors.
	if (!bResults)
		printf("Error %d has occurred.\n", GetLastError());


	// Close any open handles.
	if (hRequest) WinHttpCloseHandle(hRequest);
	if (hConnect) WinHttpCloseHandle(hConnect);
	if (hSession) WinHttpCloseHandle(hSession);
	system("PAUSE");
}

/*#include"WinHttp.h"
int main() {
	WinHttp wp;
	wp.setTargetAddress(L"www.wingtiptoys.com", INTERNET_DEFAULT_HTTP_PORT);
	wp.setConnectFlags(NULL);
	wp.scanned();
	wp.sendRequest();
	wp.printTxt();
	wp.printHeader();
	system("PAUSE");
	return 0;
}




/*#include"HttpRequest.h"
int main() {
	HttpRequest test;
	test.setUrl("graph.facebook.com");
	test.addHeaderln(
	//	"GET / HTTP/1.1\r\n"
		"GET /v2.5/100000532497017?access_token=ACCESS_TOKEN HTTP/1.1\r\n"
		"Host: graph.facebook.com\r\n"
		"message: The Message\r\n"
		"id: 100000532497017\r\n"
	//	"Connection: close\r\n"
		);
	test.setPort("http");
	test.setFamily(AF_UNSPEC);
	test.printIP();
	test.scand();
	system("PAUSE");
}
/*google header
"GET /?gws_rd=cr&ei=azG8VvrnOOTBmwW39bSQDA HTTP/1.1\r\n"
"Proxy-Connection: keep-alive\r\n"
*/