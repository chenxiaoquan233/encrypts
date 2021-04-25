const int delta = 0x9E3779B9;

void encrypt(int* value, int* key, int round)
{
    int l = value[0], r = value[1];
    for(int i = 1; i <= round; ++i)
    {
        l += ((r << 4) + key[0]) ^ (r + delta * i) ^ ((r >> 5) + key[1]);
        r += ((l << 4) + key[2]) ^ (l + delta * i) ^ ((l >> 5) + key[3]);
    }
    value[0] = l, value[1] = r;
}

void decrypt(int* value, int* key, int round)
{
    int l = value[0], r = value[1];
    for(int i = round; i > 0; --i)
    {
        r -= ((l << 4) + key[2]) ^ (l + delta * i) ^ ((l >> 5) + key[3]);
        l -= ((r << 4) + key[0]) ^ (r + delta * i) ^ ((r >> 5) + key[1]);
    }
    value[0] = l, value[1] = r;
}