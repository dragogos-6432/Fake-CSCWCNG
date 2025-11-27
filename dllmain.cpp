//CSCDummy 1.2 - Fake CSCWCNG.DLL for testing ATM malware made for Wincor Nixdorf/Diebold Nixdorf ATMs.
//Based off CSCWCNG-fake-dll by Archi73ct.
#include "pch.h"
#include <stdio.h>
#include <windows.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>
#include <atomic>
#include <condition_variable>
#include <thread>
#include <chrono>
#pragma warning(disable : 4996)
#define DllExport   __declspec( dllexport )

typedef struct test {
    int a;
    int b;
    int c;
    int d;
    int e;
    char* string;
} _unk_struct;

//The console window has been removed in this version. If you still need it, uncomment the following lines below and the printf lines.

//CONSOLE_SCREEN_BUFFER_INFO coninfo;
//BOOL APIENTRY DllMain(HMODULE hModule,
//    DWORD  ul_reason_for_call,
//    LPVOID lpReserved
//)
//{
//    //For output console
//    FILE* pFile = nullptr;
//    switch (ul_reason_for_call)
//    {
//    case DLL_PROCESS_ATTACH:
//    case DLL_THREAD_ATTACH:
//        //Alloc a new console and set the STDOUT to it
//        AllocConsole();
//        SetConsoleTitle(L"CNG Device Driver Window");
//        freopen_s(&pFile, "CONOUT$", "w", stdout);
//        break;
//    case DLL_THREAD_DETACH:
//    case DLL_PROCESS_DETACH:
//        break;
//    }
//    return TRUE;
//}

typedef enum {
	LOG_TRACE,
	LOG_DEBUG,
	LOG_INFO,
	LOG_WARNING,
	LOG_ERROR,
	LOG_FATAL
} LogLevel;

// Log level strings
static const char* level_strings[] = {
	"TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
};

void logger(const char* log_path, LogLevel level, const char* file, int line, const char* format, ...) {
	// Don't proceed if log path isn't provided
	if (log_path == NULL || log_path[0] == '\0') {
		return;
	}

	// Get current time
	time_t t = time(NULL);
	struct tm* lt = localtime(&t);
	char time_str[32];
	strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", lt);

	// Open log file in append mode
	FILE* log_file = fopen(log_path, "a");
	if (!log_file) {
		// If we can't open the file, optionally output to debugger
#ifdef _WIN32
		OutputDebugStringA("Failed to open log file!\n");
#endif
		return;
	}

	// Write log metadata
	fprintf(log_file, "%s [%s] %s:%d: ",
		time_str, level_strings[level], file, line);

	// Write log message
	va_list args;
	va_start(args, format);
	vfprintf(log_file, format, args);
	va_end(args);

	// Ensure each log entry is on its own line
	fprintf(log_file, "\n");

	// Close the file
	fclose(log_file);
}

const char* log_path = "C:\\CNG.log";

void log_host_application(const char* log_path)
{
	char process_path[MAX_PATH] = { 0 };

	// This version uses GetModuleFileName instead
	if (GetModuleFileNameA(NULL, process_path, MAX_PATH)) {
		logger(log_path, LOG_INFO, __FILE__, __LINE__,
			"DLL loaded by: %s", process_path);
	}
	else {
		logger(log_path, LOG_WARNING, __FILE__, __LINE__,
			"Failed to get host application name. Error: %lu", GetLastError());
	}
}

extern "C" DllExport BOOL _cdecl CscCngOpen() {
	log_host_application(log_path);
	logger(log_path, LOG_INFO, __FILE__, __LINE__, "CscCngOpen - Opened access to the device.");
    //printf("CscCngOpen - Ready\n");
    return 0;
}
extern "C" DllExport BOOL _cdecl CscCngStatusRead(_unk_struct * data) {
    //printf("CscCngStatusRead - Received status query\n");
	logger(log_path, LOG_INFO, __FILE__, __LINE__, "CscCngStatusRead - Received status query");
    sprintf_s(data->string, 523, "LEN=0511,RSTA=R,RACT=0131,RRET=00,1STA=R,1NUM=444444,1CUR=EUR,1REL=0000,1VAL=00000050,1LEN=000,1TOL=00,1ACT=1024,1NDV=1097,1LOW=0000,1L_D=00,1REJ=000,2STA=M,2NUM=*******,2CUR=EUR,2REL=0000,2VAL=00000100,2LEN=000,2TOL=00,2ACT=1048,2NDV=1049,2LOW=0000,2L_D=00,2REJ=000,3STA=R,3NUM=1445320,3CUR=EUR,3REL=0000,3VAL=00000200,3LEN=000,3TOL=00,3ACT=1485,3NDV=1528,3LOW=0000,3L_D=00,3REJ=000,4STA=R,4NUM=0022222,4CUR=EUR,4REL=0000,4VAL=00000500,4LEN=000,4TOL=00,4ACT=1371,4NDV=1386,4LOW=0000,4L_D=00,4REJ=000,SRACT=00");
    return 0;
}
extern "C" DllExport BOOL _cdecl CscCngClose() {
    //printf("CscCngClose - CLOSED\n");
	logger(log_path, LOG_INFO, __FILE__, __LINE__, "CscCngClose - Closed access to the device.");
    Sleep(1000);
    return 0;
}
extern "C" DllExport BOOL _cdecl CscCngDispense() {
    //printf("CscCngDispense - Dispensing...\n");
	logger(log_path, LOG_INFO, __FILE__, __LINE__, "CscCngDispense - Dispensing cash...");
    Sleep(2000);
    return 0;
}
extern "C" DllExport BOOL _cdecl CscCngTransport() {
	logger(log_path, LOG_INFO, __FILE__, __LINE__, "CscCngTransport - Transporting cash to the customer...");
	Sleep(1000);
    return 0;
}
extern "C" DllExport BOOL _cdecl CscCngReset() {
	logger(log_path, LOG_INFO, __FILE__, __LINE__, "CscCngReset - Device reset.");
    return 0;
}

extern "C" DllExport BOOL _cdecl CscCngUnlock() {
    //printf("CscCngUnlock - UNLOCKED\n");
	logger(log_path, LOG_INFO, __FILE__, __LINE__, "CscCngUnlock - The CNG driver is no longer under exclusive control by the application.");
    Sleep(1000);
    return 0;
}
extern "C" DllExport BOOL _cdecl CscCngLock() {
    //printf("CscCngLock - LOCKED\n");
	logger(log_path, LOG_INFO, __FILE__, __LINE__, "CscCngLock - The CNG driver is now under exclusive control by the application.");
    Sleep(1000);
    return 0;
}
extern "C" DllExport BOOL _cdecl CscCngShutter() {
	logger(log_path, LOG_INFO, __FILE__, __LINE__, "CscCngShutter - Dispenser shutter control function");
    Sleep(1000);
    return 0;
}
