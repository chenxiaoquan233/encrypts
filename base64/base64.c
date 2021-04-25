#include <string.h>

char table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

unsigned char src_buf[3];
unsigned char des_buf[4];

void convert(const char* src, char* des)
{
    des[0] = src[0] >> 2;
    des[1] = (src[0] << 4 | src[1] >> 4) & 0x3F;
    des[2] = (src[1] & 0x0F) << 2 | src[2] >> 6;
    des[3] = src[2] & 0x3F;
}

void encode(const char* input, char* output)
{
    int len = strlen(input);
    int i = 0, j = 0, k = 0;
    while(i < len)
    {
        src_buf[j++] = input[i++];
        
        if(j == 3)
        {
            convert(src_buf, des_buf);

            for(int l = 0; l < 4; ++l)
            {
                output[k++] = table[des_buf[l]];
            }

            memset(src_buf, 0, sizeof(src_buf));

            j ^= j;
        }
    }

    if(j)
    {
        convert(src_buf, des_buf);

        output[k++] = table[des_buf[0]];
        output[k++] = table[des_buf[1]];

        if(j == 2) output[k++] = table[des_buf[2]];
        else output[k++] = '=';

        output[k++] = '=';
    }
}

void decode(char* input, char* output)
{
    
}