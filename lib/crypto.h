

#ifndef crypto
#define crypto 
#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

 void XOR(char * payload ,size_t payload_size, char* key , size_t key_size ){
    int j = 0;
    
    for (int i = 0; i < payload_size; i++){

        if( j == key_size -1) j = 0;
        payload[i] ^= key[j];
        j++;
    }
} 

void XORS(char * payload ,size_t payload_size, char* keys , size_t keys_size ){
    size_t key_size; 
    
    for (int i = 0 ; i <3 ; i++){
        key_size = sizeof(keys[i]);
        XOR((char *)payload ,payload_size, keys + i,key_size);
    }
}
 void DXORS(char *payload, size_t payload_size, char *key, size_t key_size){
        for (int i = key_size -1 ; i >=0 ; i--){

        XOR((char *)payload ,payload_size, key + i,key_size);
    }
}

#endif
