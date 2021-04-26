const int delta = 0x9E3779B9;

void encrypt(int* value, int* key, int round)
{
    int l = value[0], r = value[1], sum = 0;
    for(int i = 0; i < round; ++i)
    {
        l += ((r << 4) + key[0]) ^ (r + sum) ^ ((r >> 5) + key[1]);
        sum += delta;
        r += ((l << 4) + key[2]) ^ (l + sum) ^ ((l >> 5) + key[3]);
    }
    value[0] = l, value[1] = r;
}

void decrypt(int* value, int* key, int round)
{
    int l = value[0], r = value[1], sum = delta * round;
    for(int i = 0; i < round; ++i)
    {
        r -= ((l << 4) + key[2]) ^ (l + delta * i) ^ ((l >> 5) + key[3]);
        sum -= delta;
        l -= ((r << 4) + key[0]) ^ (r + delta * i) ^ ((r >> 5) + key[1]);
    }
    value[0] = l, value[1] = r;
}