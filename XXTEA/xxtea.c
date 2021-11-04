const int delta = 0x9e3779b9; 

#define MX ((z >> 5 ^ y << 2) + (y >> 3 ^ z << 4) ^ (sum ^ y) + (key[p & 3 ^ e] ^ z))

void encrypt(unsigned int* value, unsigned int n, unsigned int key[4])
{
    int sum = 0, q = 6 + 52 / n, y = 0, z = value[n - 1], e = 0, p = 0;
    while(q--)
    {
        sum += delta;
        e = (sum >> 2) & 3;
        for(p = 0; p < n - 1; ++p)
        {
            y = value[p + 1];
            z = value[p] += MX;
        }
        y = value[0];
        z = value[n - 1] += MX;
    }
}

void decrypt(unsigned int* value, unsigned int n, unsigned int key[4])
{
    int q = 6 + 52 / n, sum = q * delta, y = value[0], z = value[n - 1], e = 0, p = 0;
    while(sum)
    {
        e = (sum >> 2) & 3;
        for(p = n - 1; p > 0; --p)
        {
            z = value[p - 1];
            y = value[p] -= MX;
        }
        z = value[n - 1];
        y = value[0] -= MX;
        sum -= delta;
    }
}