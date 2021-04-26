const int delta = 0x9E3779B9;

void encipher(unsigned int value[2], unsigned int const key[4], unsigned int rounds)
{
    unsigned int l = value[0], r = value[1], sum = 0;
    for (int i = 0; i < rounds; i++)
    {
        l += (((r << 4) ^ (r >> 5)) + r) ^ (sum + key[sum & 3]);
        sum += delta;
        r += (((l << 4) ^ (l >> 5)) + l) ^ (sum + key[(sum >> 11) & 3]);
    }
    value[0] = l;
    value[1] = r;
}

void decipher(unsigned int value[2], unsigned int const key[4], unsigned int rounds)
{
    unsigned int l = value[0], r = value[1], sum = delta * rounds;
    for (int i = 0; i < rounds; i++)
    {
        r -= (((l << 4) ^ (l >> 5)) + l) ^ (sum + key[(sum >> 11) & 3]);
        sum -= delta;
        l -= (((r << 4) ^ (r >> 5)) + r) ^ (sum + key[sum & 3]);
    }
    value[0] = l;
    value[1] = r;
}
