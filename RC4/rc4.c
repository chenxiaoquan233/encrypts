#ifndef _STRING_H
#include <string.h>
#endif

void swap(unsigned char *a, unsigned char *b)
{
    unsigned char tmp = *a;
    *a = *b;
    *b = tmp;
}

void KSA(char *key, unsigned char *S)
{
    int key_len = strlen(key);
    unsigned char j;

    for(int i = 0; i < 256; ++i)
        S[i] = i;

    for(int i = 0; i < 256; ++i)
    {
        j += S[i] + key[i % key_len];
        swap(&S[i], &S[j]);
    }
}

void PRGA(unsigned char *S, char *plain, unsigned char *cipher)
{
    unsigned char i = 0, j = 0; 
    int len = strlen(plain);
    for(int index = 0; index < len; ++index)
    {
        i++;
        j += S[i];

        swap(&S[i], &S[j]);

        cipher[index] = S[(S[i] + S[j]) % 256] ^ plain[index];
    }
}

void RC4(char *key, char *plain, unsigned char *cipher)
{
    unsigned char S[256];
    KSA(key, S);
    PRGA(S, plain, cipher);
}