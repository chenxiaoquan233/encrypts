#ifndef _STRING_H
#include <string.h>
#endif

char table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

unsigned char buf3B[3];
unsigned char buf4B[4];

unsigned char indexof(unsigned char ch)
{
    if('A' <= ch && ch <= 'Z') return ch - 'A';
    if('a' <= ch && ch <= 'z') return ch - 'a' + 26;
    if('0' <= ch && ch <= '9') return ch - '0' + 52;
    if(ch == '+') return 62;
    if(ch == '/') return 63;
} 

void convert_3to4(const unsigned char* src, unsigned char* dest)
{
    /*
    from: 76543210 76543210 76543210
      to: 765432 107654 321076 543210
    */
    dest[0] = src[0] >> 2;
    dest[1] = (src[0] << 4 | src[1] >> 4) & 0x3F;
    dest[2] = (src[1] & 0x0F) << 2 | src[2] >> 6;
    dest[3] = src[2] & 0x3F;
}

void convert_4to3(const unsigned char* src, unsigned char* dest)
{
    /*
    from: 765432 107654 321076 543210
      to: 76543210 76543210 76543210 
    */
    dest[0] = (src[0] << 2) | (src[1] >> 4);
    dest[1] = (src[1] << 4) & 0x3f | (src[2] >> 2);
    dest[2] = (src[2] << 6) & 0x3f | src[3];
}

void encode(const char* input, char* output)
{
    int len = strlen(input);
    int input_len = (len + 2) / 3 * 3;
    char* input_buf = (char*)malloc(input_len);
    memset(input_buf, 0, input_len);
    memcpy(input_buf, input, len);
    for(int i = 0; i < len; i += 3)
    {
        int j = i / 3 * 4;
        convert_3to4(input_buf + i, output + j);
        if(len - i >= 3)
        {
            for(int l = 0; l < 4; ++l)
            {
                output[j + l] = table[output[j + l]];
            }
        }
        else
        {
            int l = 0, k = len % 3;
            for(; l <= k; ++l)
            {
                output[j + l] = table[output[j + l]];
            }
            for(; l < 4; ++l)
            {
                output[j + l] = '=';
            }
        }
    }
    free(input_buf);
}

void decode(const char* input, char* output)
{
    int len = strlen(input);
    for(int i = 0; i < len; i += 4)
    {
        int j = i / 4 * 3;
        int eq_num = 0;
        memcpy(buf4B, input + i, 4);
        for(int l = 0; l < 4; ++l) 
        {
            if(buf4B[l] != '=') buf4B[l] = indexof(buf4B[l]);
            else eq_num++;
        }
        convert_4to3(buf4B, buf3B);
        memcpy(output + j, buf3B, 3 - eq_num);
    }
}