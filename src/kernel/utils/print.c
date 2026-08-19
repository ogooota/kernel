#include "varargs.h"
#include "utils.h"

#include <kernel/drivers/video/video.h>

int vsprintf(char *out, const char *fmt, va_list args)
{
        if (out == NULL ||
            fmt == NULL)
        {
                return -1;
        }

        char *str = out;

        for (const char *p = fmt; *p; p++)
        {
                if (*p != '%')
                {
                        *str = *p;
                        str++;
                        continue;
                }

                /**
                 * Passando do '%'
                 */
                p++;

                switch (*p)
                {
                case 'c':
                {
                        /**
                         * Preservando só o último byte do char
                         */
                        char c = (char)(va_arg(args, int) & 0xff);
                        *str = c;
                        str++;
                } break;

                case 's':
                {
                        char *s = va_arg(args, char *);
                        while (*s)
                        {
                                *str = *s;
                                str++;
                                s++;
                        }
                } break;

                case 'd':
                {
                        int i = va_arg(args, int);
                        itoa(str, i);
                        str++;
                } break;

                default:
                        *str = *p;
                        str++;
                        break;
                }
        }

        *str = 0;

        return str - out;
}

void printk(const char *fmt, ...)
{
        if (fmt == NULL)
        {
                return;
        }

        va_list args;
        va_start(args, fmt);
        char buf[1024];
        int err;

        if ((err = vsprintf(buf, fmt, args)) >= (int)sizeof(buf))
        {
                vidputs("fmt string too long\n");
                va_end(args);
                return;
        }

        if (err < 0)
        {
                vidputs("an error ocurred\n");
                va_end(args);
                return;
        }

        va_end(args);

        vidputs(buf);
}









