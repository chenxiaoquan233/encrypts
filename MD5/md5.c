#ifndef _STDLIB_H
#include <stdlib.h>
#endif

#ifndef _STDINT_H
#include <stdint.h>
#endif

#define A 0x67452301
#define B 0xefcdab89
#define C 0x98badcfe
#define D 0x10325476

#define F(X, Y, Z) ((X & Y) | (~X & Z))
#define G(X, Y, Z) ((X & Z) | (Y & ~Z))
#define H(X, Y, Z) (X ^ Y ^ Z)
#define I(X, Y, Z) (Y ^ (X | ~Z))

static const uint32_t S[] = 
{
    7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
    5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

static const uint32_t K[] = 
{
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

static const uint8_t PADDING[] = 
{
    0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

uint32_t rotateLeft(uint32_t x, uint32_t n)
{
	return (x << n) | (x >> (32 - n));
}

typedef struct
{
    uint64_t length;
    uint32_t a, b, c, d;
    uint8_t input[64];
    uint8_t digest[16];
}MD5Context;

void md5Init(MD5Context *ctx)
{
    ctx->length = 0;
    ctx->a = A;
    ctx->b = B;
    ctx->c = C;
    ctx->d = D;
}

void md5Step(MD5Context *ctx, uint8_t *input)
{
    uint32_t AA = ctx->a;
	uint32_t BB = ctx->b;
	uint32_t CC = ctx->c;
	uint32_t DD = ctx->d;

	uint32_t E;

	size_t j;

	for(size_t i = 0; i < 64; ++i)
    {
		if(0 <= i && i <= 15)
		{
            E = F(BB, CC, DD);
            j = i;
        }
		else if(16 <= i && i <= 31)
		{
            E = G(BB, CC, DD);
            j = ((i * 5) + 1) % 16;
        }
		else if(32 <= i && i <= 47)
		{
            E = H(BB, CC, DD);
			j = ((i * 3) + 5) % 16;
		}
        else if(48 <= i && i <= 63)
        {
            E = I(BB, CC, DD);
			j = (i * 7) % 16;
		}

		uint32_t temp = DD;
		DD = CC;
		CC = BB;
		BB = BB + rotateLeft(AA + E + K[i] + input[j], S[i]);
		AA = temp;
	}

	ctx->a += AA;
	ctx->b += BB;
	ctx->c += CC;
	ctx->d += DD;
}

void md5Update(MD5Context *ctx, uint8_t *input, size_t input_len)
{
    uint32_t input[16];
    size_t offset = ctx->length % 64;
    ctx->length += input_len;

    for(size_t i = 0; i < input_len; ++i)
    {
        ctx->input[offset++] = input[i];

        if(offset % 64 == 0)
        {
            for(size_t j = 0; j < 16; ++j)
            {
                input[j] = (ctx->input[(j * 4) + 3]) << 24 | 
                           (ctx->input[(j * 4) + 2]) << 16 | 
                           (ctx->input[(j * 4) + 1]) <<  8 | 
                           (ctx->input[(j * 4)]);
            }
            md5Step(ctx, input);
            offset = 0;
        }
    }
}

uint32_t convertEndian(uint32_t a)
{
    return (a & 0x000000FF) << 24 |
           (a & 0x0000FF00) << 8  |
           (a & 0x00FF0000) >> 8  |
           (a & 0xFF000000) >> 24;
}

void md5Finalize(MD5Context *ctx)
{
    uint32_t input[16];
    size_t offset = ctx->length % 64;
    size_t padding_len = offset < 56 ? (56 - offset) : (64 + 56 - offset);

    md5Update(ctx, PADDING, padding_len);
    ctx->length -= padding_len;

    for(size_t i = 0; i < 14; ++i)
    {
        input[i] = (ctx->input[(i * 4) + 3]) << 24 |
		           (ctx->input[(i * 4) + 2]) << 16 |
		           (ctx->input[(i * 4) + 1]) <<  8 |
		           (ctx->input[(i * 4)]);
    }
    input[14] = (uint32_t)(ctx->length * 8);
    input[15] = (uint32_t)((ctx->length * 8) >> 32);

    md5Step(ctx, input);

    *(uint32_t*)(ctx->digest +  0) = convertEndian(ctx->a);
    *(uint32_t*)(ctx->digest +  4) = convertEndian(ctx->b);
    *(uint32_t*)(ctx->digest +  8) = convertEndian(ctx->c);
    *(uint32_t*)(ctx->digest + 12) = convertEndian(ctx->d);
}