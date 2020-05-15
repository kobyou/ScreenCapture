#pragma once
#include "stdafx.h"
//add print message function
static FILE *fp;
static const UINT8 DEBUG_MODE_NONE = 0;
static const UINT8 DEBUG_MODE_MESSAGE = 1;

static UINT8 debugMode = DEBUG_MODE_MESSAGE;
static int LogSaveDays = 90;

char * wchar2char(const wchar_t* wchar);
wchar_t * char2wchar(const char* cchar);

class CLog {
public:
	CLog();
	~CLog();
public:
	void MsgOut(const char* _Format, ...);

private:
	TCHAR *mctimelocal(BYTE mode);
	std::string format(const char * _Format, ...);
	void SetDebugMode(UINT8 mode);
	void SetLogSaveDays(int days);
};

