#pragma once
#include<Windows.h>
void SaveToClipboard(const char *str)
{
	if (OpenClipboard(NULL))
	{
		HGLOBAL clipbuffer;
		char *buffer;
		EmptyClipboard();
		clipbuffer = GlobalAlloc(GMEM_MOVEABLE, strlen(str) + 1);
		buffer = (char*)GlobalLock(clipbuffer);
		strcpy_s(buffer, strlen(str) + 1, (LPCSTR)str);
		GlobalUnlock(clipbuffer);
		SetClipboardData(CF_TEXT, clipbuffer);
		CloseClipboard();
	}
}