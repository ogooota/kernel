#include "utils.h"

void itoa(char *out, int n)
{
        if (n == 0)
        {
                out[0] = '0';
                out[1] = 0;
                return;
        }

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


/**
 * Usado para conversões utilizando %x e %X
 */
const char hex[] = {
        'a',
        'b',
        'c',
        'd',
        'e',
        'f'
};

void itox(char *out, int n)
{
        int i, j;
        for (i = 28, j = 0;
             i >= 0;
             i -= 4, j++)
        {
                int nib = (n >> i) & 0x0F;
                if (nib > 9)
                {
                        out[j] = hex[nib - 10];
                }
                else
                {
                        out[j] = nib + '0';
                }
        }

        out[j] = 0;
}
