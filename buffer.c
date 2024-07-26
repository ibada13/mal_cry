

#include "lib/crypto.h"
#include "lib/matx.h"





int main (){
    char *key[] = {"somthing went wrong","just another key","hello world"};

    size_t tab_size = sizeof(buf) / sizeof(buf[0]);
    unsigned int key_size = sizeof(key) / sizeof(key[0]);
    XORS((char *)buf ,tab_size, (char *)key,key_size);
    DXORS((char *)buf ,tab_size, (char *)key,key_size);
    

        pr_tab_hex((char *)buf, tab_size);

}