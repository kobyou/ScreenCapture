#include "CLog.h"

wchar_t * char2wchar(const char* cchar)
{
	wchar_t *wchar;
	int len = MultiByteToWideChar(CP_ACP, 0, cchar, strlen(cchar), NULL, 0);
	wchar = new wchar_t[len + 1];
	MultiByteToWideChar(CP_ACP, 0, cchar, strlen(cchar), wchar, len);
	wchar[len] = '\0';
	return wchar;
}

char * wchar2char(const wchar_t* wchar)
{
	char * CChar;
	int len = WideCharToMultiByte(CP_ACP, 0, wchar, wcslen(wchar), NULL, 0, NULL, NULL);
	CChar = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, wchar, wcslen(wchar), CChar, len, NULL, NULL);
	CChar[len] = '\0';
	return CChar;
}

CLog::CLog()
{
}


CLog::~CLog()
{
}



void CLog::SetLogSaveDays(int days)
{
	LogSaveDays = days;
}

void CLog::SetDebugMode(UINT8 mode)
{
	if(mode <= DEBUG_MODE_MESSAGE) {
		debugMode = mode;
	}
	else {
		debugMode = DEBUG_MODE_NONE;
	}
}

std::string CLog::format(const char * _Format, ...)
{
	std::string tmp;

	va_list marker = NULL;
	va_start(marker, _Format);

	size_t num_of_chars = _vscprintf(_Format, marker);

	if(num_of_chars > tmp.capacity()) {
		tmp.resize(num_of_chars + 1);
	}

	vsprintf_s((char *)tmp.data(), tmp.capacity(), _Format, marker);

	va_end(marker);

	return tmp.c_str();
}

TCHAR* CLog::mctimelocal(BYTE mode)
{
	SYSTEMTIME tm;
	static char strtime[29];
	GetLocalTime(&tm);

	if(mode == 0) {
		_snprintf_s(strtime, sizeof(strtime), _TRUNCATE, "[%04d-%02d-%02d %02d:%02d:%02d %03d] ",
		            tm.wYear,
		            tm.wMonth,
		            tm.wDay,
		            tm.wHour,
		            tm.wMinute,
		            tm.wSecond,
		            tm.wMilliseconds
		           );
	}
	else if(mode == 1) {
		_snprintf_s(strtime, sizeof(strtime), _TRUNCATE, "%02d%02d%02d%02d",
		            tm.wMonth,
		            tm.wDay,
		            tm.wHour,
		            tm.wMinute
		            //tm.wSecond
		           );
	}
	else if(mode == 2) {
		_snprintf_s(strtime, sizeof(strtime), _TRUNCATE, "%04d%02d%02d",
		            tm.wYear,
		            tm.wMonth,
		            tm.wDay
		           );
	}
	return char2wchar(strtime);
}


void CLog::MsgOut(const char* _Format, ...)
{
	if(debugMode == DEBUG_MODE_NONE) {
		return;
	}
	static int flag = TRUE;
	static TCHAR file[MAX_PATH];
	char str_tmp[512] = { 0 };
	static int FileHandle = 0;
	unsigned long wrote;


	if(flag) {
		TCHAR fileName[MAX_PATH] = { 0 };
		TCHAR* ptrEnd;
		::GetModuleFileName(NULL, file, MAX_PATH);
		if((ptrEnd = _tcsrchr(file, '\\')) != NULL) {
			*ptrEnd = '\0';
			_tcscat_s(file, MAX_PATH, _T("\\Log"));
			if(_access((char*)file, 0) == -1) {
				CreateDirectory(file, NULL);
			}

			_tcscpy_s(fileName, file);


			_tcscat_s(fileName, MAX_PATH, _T("\\"));
			_tcscat_s(fileName, MAX_PATH, mctimelocal(2));
			if(_access((CHAR *)fileName, 0) == -1) {
				CreateDirectory(fileName, NULL);
			}

			_tcscat_s(fileName, MAX_PATH, _T("\\ScrShots_"));
			_tcscat_s(fileName, MAX_PATH, mctimelocal(2));
			_tcscat_s(fileName, MAX_PATH, _T(".log"));
		}

		int dwShareMode = FILE_SHARE_READ;
		FileHandle = (int)CreateFile(fileName, GENERIC_WRITE, dwShareMode, NULL,
		                             CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if(!(FileHandle > 0)) {
			SetDebugMode(DEBUG_MODE_NONE);
		}

		//DeleteFile(file);
		flag = FALSE;
	}
	else {
		//每天生成一个文件夹
		TCHAR fileDir[MAX_PATH] = { 0 };
		_tcscpy_s(fileDir, file);

		_tcscat_s(fileDir, MAX_PATH, _T("\\"));
		_tcscat_s(fileDir, MAX_PATH, mctimelocal(2));
		if(_access((CHAR*)fileDir, 0) == -1) {
			flag = true;
		}
	}

	TCHAR *strtime = mctimelocal(0);
	//printf(strtime);

	va_list vArgList;
	va_start(vArgList, _Format);
	_vsnprintf_s(str_tmp, 512, _Format, vArgList);
	va_end(vArgList);

	//printf(str_tmp);

	if(debugMode == DEBUG_MODE_MESSAGE) {
		WriteFile((HANDLE)FileHandle, wchar2char(strtime), strlen(wchar2char(strtime)), &wrote, NULL);
		WriteFile((HANDLE)FileHandle, str_tmp, strlen((str_tmp)), &wrote, NULL);
	}
}