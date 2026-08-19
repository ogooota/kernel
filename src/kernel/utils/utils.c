#include "utils.h"

void itoa(char *out, int n)
{
        int size = 0;
        int i    = 0;
        char rev[10];

        while (n)
        {
                rev[size++] = (n % 10) + '0';
                n /= 10;
        }

        while (i < size)
        {
                out[i] = rev[size - i - 1];
                i++;
        }

        out[i] = 0;
}
