

#include "lib/crypto.h"
#include "lib/matx.h"
#include "lib/wizard.h"




int main (){
    // char *keys[] = {"somthing went wrong","just another key","hello world"};
    // char key[] = "somthing went wrong";
    // size_t tab_size = sizeof(dt_buf);
    // unsigned int key_size = sizeof(key);
    // // printf("%d", &key_size);
    // XOR((char *)dt_buf ,tab_size, (char *)key,key_size);
    // pr_tab_hex((char *)dt_buf, tab_size);

    // // XOR((char *)buf ,tab_size, (char *)key,key_size);
    //  // pr_tab_hex((char *)buf, tab_size);
    int bin[] = {1,0,0,0,0,0,0,1};
    int res = bin_byte(bin);
    printf("%#04x",res );
}