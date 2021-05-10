const unsigned int delta = 0x9E3779B9;

void encrypt(unsigned int* value, unsigned int* key, int round)
{
    unsigned int l = value[0], r = value[1], sum = 0;
    for(int i = 0; i < round; ++i)
    {
        sum += delta;
        l += ((r << 4) + key[0]) ^ (r + sum) ^ ((r >> 5) + key[1]);
        r += ((l << 4) + key[2]) ^ (l + sum) ^ ((l >> 5) + key[3]);
    }
    value[0] = l, value[1] = r;
}

void decrypt(unsigned int* value, unsigned int* key, int round)
{
    unsigned int l = value[0], r = value[1], sum = delta * round;
    for(int i = 0; i < round; ++i)
    {
        r -= ((l << 4) + key[2]) ^ (l + sum) ^ ((l >> 5) + key[3]);
        l -= ((r << 4) + key[0]) ^ (r + sum) ^ ((r >> 5) + key[1]);
        sum -= delta;
    }
    value[0] = l, value[1] = r;
}