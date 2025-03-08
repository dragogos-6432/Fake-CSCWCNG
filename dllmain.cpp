//CSCDummy 1.0 - Fake CSCWCNG.DLL for testing ATM malware made for Wincor Nixdorf/Diebold Nixdorf ATMs.
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
#define DllExport   __declspec( dllexport )

typedef struct test {
    int a;
    int b;
    int c;
    int d;
    int e;
    char* string;
} _unk_struct;

CONSOLE_SCREEN_BUFFER_INFO coninfo;
BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    //For output console
    FILE* pFile = nullptr;
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
        //Alloc a new console and set the STDOUT to it
        AllocConsole();
        SetConsoleTitle(L"CNG Device Driver Window");
        freopen_s(&pFile, "CONOUT$", "w", stdout);
        break;
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


extern "C" DllExport BOOL _cdecl CscCngOpen() {
    printf("CscCngOpen - Ready\n");
    return 0;
}
extern "C" DllExport BOOL _cdecl CscCngStatusRead(_unk_struct * data) {
    printf("CscCngStatusRead - Received status query\n");
    //sprintf_s(data->string, 523, "1NDV=00009999,2NDV=00009999,3NDV=00009999,4NDV=00009999");
    sprintf_s(data->string, 523, "LEN=0511,RSTA=R,RACT=0131,RRET=00,1STA=R,1NUM=444444,1CUR=EUR,1REL=0000,1VAL=00000050,1LEN=000,1TOL=00,1ACT=1024,1NDV=1097,1LOW=0000,1L_D=00,1REJ=000,2STA=M,2NUM=*******,2CUR=EUR,2REL=0000,2VAL=00000100,2LEN=000,2TOL=00,2ACT=1048,2NDV=1049,2LOW=0000,2L_D=00,2REJ=000,3STA=R,3NUM=1445320,3CUR=EUR,3REL=0000,3VAL=00000200,3LEN=000,3TOL=00,3ACT=1485,3NDV=1528,3LOW=0000,3L_D=00,3REJ=000,4STA=R,4NUM=0022222,4CUR=EUR,4REL=0000,4VAL=00000500,4LEN=000,4TOL=00,4ACT=1371,4NDV=1386,4LOW=0000,4L_D=00,4REJ=000,SRACT=00");
    return 0;
}
extern "C" DllExport BOOL _cdecl CscCngClose() {
    printf("CscCngClose - CLOSED\n");
    Sleep(1000);
    return 0;
}
extern "C" DllExport BOOL _cdecl CscCngDispense() {
    printf("CscCngDispense - Dispensing...\n");
    Sleep(2000);
    return 0;
}
extern "C" DllExport BOOL _cdecl CscCngTransport() {
    return 0;
}
extern "C" DllExport BOOL _cdecl CscCngReset() {
    return 0;
}

extern "C" DllExport BOOL _cdecl CscCngUnlock() {
    printf("CscCngUnlock - UNLOCKED\n");
    Sleep(1000);
    return 0;
}
extern "C" DllExport BOOL _cdecl CscCngLock() {
    printf("CscCngLock - LOCKED\n");
    Sleep(1000);
    return 0;
}
extern "C" DllExport BOOL _cdecl CscCngShutter() {
    Sleep(1000);
    return 0;
}
