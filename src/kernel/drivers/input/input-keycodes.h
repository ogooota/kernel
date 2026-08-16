#ifndef __INPUT_KEYCODES_H
#define __INPUT_KEYCODES_H

enum keycode
{
        /**
         * Qualquer código recebido em
         * portas I/O que não possua uma abstração
         * será considerado 'Unknown' até que
         * seja devidamente implementado
         */
        KEYCODE_UNKNOWN = 0,

        /**
         * Alfabeto
         */
        KEYCODE_A,
        KEYCODE_B,
        KEYCODE_C,
        KEYCODE_D,
        KEYCODE_E,
        KEYCODE_F,
        KEYCODE_G,
        KEYCODE_H,
        KEYCODE_I,
        KEYCODE_J,
        KEYCODE_K,
        KEYCODE_L,
        KEYCODE_M,
        KEYCODE_N,
        KEYCODE_O,
        KEYCODE_P,
        KEYCODE_Q,
        KEYCODE_R,
        KEYCODE_S,
        KEYCODE_T,
        KEYCODE_U,
        KEYCODE_V,
        KEYCODE_W,
        KEYCODE_X,
        KEYCODE_Y,
        KEYCODE_Z,

        /**
         * Fim
         */
        KEYCODE_SIZE
};

#endif
