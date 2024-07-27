#ifndef WIZARD
#define WIZARD

int bin_byte(int bin[]){
    int byte = 0;
    unsigned int power = 1;
    for (int i = 7; i >=0;i--){
        byte += (bin[i] * power);
        power *= 2;
    }
    return byte;
}



#endif