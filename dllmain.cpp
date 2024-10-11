//CSCDummy 1.0 - Fake CSCWCNG.DLL for testing ATM malware made for Wincor Nixdorf/Diebold Nixdorf ATMs.
//Based off CSCWCNG-fake-dll by Archi73ct.
#include "pch.h"
#include <stdio.h>
#include <windows.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>
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
        freopen_s(&pFile, "CONOUT$", "w", stdout);
        break;
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
//Some of these exports have been pulled out of a CSCWCNG DLL which turned out to be a XWIZARD sample. Some exports won't be used by anything. 
//I can't 100% confirm this for now due to not having a proper copy of the actual CSCWCNG DLL. The only exports that I have seen samples use is
//exports starting with "CSC" and hInst, but I haven't tested this DLL with everything yet.
//I have no idea what some exports need to output. Some samples that need, for example, CngDllLibName to output a specifc string or if used with actual ProBase you will have problems.
extern "C" DllExport BOOL _cdecl CngDllLibName(_unk_struct * deta) {
    printf("ProBase 1.14");
    //sprintf_s(deta->string, 523, "ProBase 1.14");
    return 0;
}
extern "C" DllExport BOOL _cdecl CngLogicalName() {
    printf("Logical ProBase 1.14\n");
    return 0;
}
extern "C" DllExport BOOL _cdecl CscDhlPara() {
    printf("CscDhlPara - OK\n");
    return 0;
}
extern "C" DllExport BOOL _cdecl RetCode() {
    printf("1\n");
    return 0;
}
extern "C" DllExport BOOL _cdecl StatusReadBuffer() {
    printf("StatusReadBuffer - OK\n");
    return 0;
}
extern "C" DllExport BOOL _cdecl updateInfoP() {
    printf("updateInfoP - OK\n");
    return 0;
}
extern "C" DllExport BOOL _cdecl getCassetteIdByNum(_unk_struct * dfta) {
    printf("getCassetteIdByNum - OK\n");
    sprintf_s(dfta->string, 523, "1NDV,2NDV,3NDV,4NDV");
    return 0;
}
extern "C" DllExport BOOL _cdecl CscCngOpen() {
    return 0;
}
extern "C" DllExport BOOL _cdecl CscCngStatusRead(_unk_struct * data) {
    printf("Received status query\n");
    //sprintf_s(data->string, 523, "1NDV=00009999,2NDV=00009999,3NDV=00009999,4NDV=00009999");
    sprintf_s(data->string, 523, "LEN=0511,RSTA=R,RACT=0131,RRET=00,1STA=R,1NUM=444444,1CUR=RON,1REL=0000,1VAL=00001000,1LEN=000,1TOL=00,1ACT=1024,1NDV=1097,1LOW=0000,1L_D=00,1REJ=000,2STA=M,2NUM=*******,2CUR=RON,2REL=0000,2VAL=00000500,2LEN=000,2TOL=00,2ACT=1048,2NDV=1049,2LOW=0000,2L_D=00,2REJ=000,3STA=R,3NUM=1445320,3CUR=RON,3REL=0000,3VAL=00000200,3LEN=000,3TOL=00,3ACT=1485,3NDV=1528,3LOW=0000,3L_D=00,3REJ=000,4STA=R,4NUM=0022222,4CUR=RON,4REL=0000,4VAL=00000500,4LEN=000,4TOL=00,4ACT=1371,4NDV=1386,4LOW=0000,4L_D=00,4REJ=000,SRACT=00");
    return 0;
}
extern "C" DllExport BOOL _cdecl CscCngClose() {
    printf("Connection closed\n");
    return 0;
}
extern "C" DllExport BOOL _cdecl CscCngDispense() {
    printf("Dispensing\n");
    return 0;
}
extern "C" DllExport BOOL _cdecl CscCngTransport() {
    return 0;
}
extern "C" DllExport BOOL _cdecl CscCngReset() {
    return 0;
}

extern "C" DllExport BOOL _cdecl isNumericChar() {
    printf("No\n");
    return 0;
}
extern "C" DllExport BOOL _cdecl printBalances() {
    printf("1000,500,200,500");
    return 0;
}
extern "C" DllExport BOOL _cdecl manual_strtok_r() {
    printf("manual_strtok_r - OK\n");
    return 0;
}

extern "C" DllExport BOOL _cdecl inv_crypt() {
    printf("inv_crypt - OK\n");
    return 0;
}
extern "C" DllExport BOOL _cdecl cassette_current() {
    printf("cassette_current - OK\n");
    return 0;
}
extern "C" DllExport BOOL _cdecl cassettes() {
    printf("1,2,3,4");
    return 0;
}
extern "C" DllExport BOOL _cdecl cassettesAmounts() {
    printf("4\n");
    return 0;
}
extern "C" DllExport BOOL _cdecl cassettesCurr() {
    printf("RON\n");
    return 0;
}
extern "C" DllExport BOOL _cdecl cassettesSummary() {
    printf("No\n");
    return 0;
}
extern "C" DllExport BOOL _cdecl cassettesValues() {
    printf("0\n");
    return 0;
}
extern "C" DllExport BOOL _cdecl CscCngUnlock() {
    printf("Unlocked.\n");
    return 0;
}
extern "C" DllExport BOOL _cdecl hCng() {
    printf("hCng - OK\n");
    return 0;
}
extern "C" DllExport BOOL _cdecl hInst() {
    printf("Initializing...\n");
    return 0;
}
extern "C" DllExport BOOL _cdecl hLibCNG() {
    printf("hLibCNG - OK\n");
    return 0;
}
extern "C" DllExport BOOL _cdecl CscCngLock() {
    return 0;
}
