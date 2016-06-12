#include <stdio.h>
#include <stdlib.h>
#include "md5.h"
#include <string.h>
#include "md5.c"

int main(int argc, char *argv[])
{
    int i;
    unsigned char encrypt[100];
    scanf("%s", encrypt);
    unsigned char decrypt[16];
    MD5_CTX md5;
    MD5Init(&md5);
    MD5Update(&md5,encrypt,strlen((char *)encrypt));
    MD5Final(&md5,decrypt);
    printf("Encryption:%s\nDecryption:",encrypt);
    for(i=0;i<16;i++)
    {
        printf("%02x",decrypt[i]);
    }
    printf("\n");


    return 0;
}
