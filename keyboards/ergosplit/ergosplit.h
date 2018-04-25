#ifndef ERGOSPLIT_H
#define ERGOSPLIT_H

#include "quantum.h"

#elif KEYBOARD_lets_split_sockets
    #include "sockets.h"
#endif


#ifdef USE_I2C
#include <stddef.h> 
#ifdef __AVR__
	#include <avr/io.h>
	#include <avr/interrupt.h>
#endif
#endif


#define LAYOUT( \
    /* spatial positons */ \
	L00, L01, L02, L03, L04, L05,             R00, R01, R02, R03, R04, R05, \
	L10, L11, L12, L13, L14, L15,             R10, R11, R12, R13, R14, R15, \
	L20, L21, L22, L23, L24, L25,             R20, R21, R22, R23, R24, R25, \
	L30, L31, L32, L33, L34, L35, L36,   R36, R30, R31, R32, R33, R34, R35, \
    L40, L41, L42, L43, L44,     L46,     R46,     R41, R42, R43, R44, R45 \
	) \
    /* matrix positions */ \
	{ \
		{ L00, L01, L02, L03, L04, L05,   KC_NO}, \
		{ L10, L11, L12, L13, L14, L15,   KC_NO}, \
		{ L20, L21, L22, L23, L24, L25,   KC_NO}, \
		{ L30, L31, L32, L33, L34, L35,   L36}, \
        { L40, L41, L42, L43, L44, KC_NO, L46}, \
		{ R05, R04, R03, R02, R01, R00,   KC_NO }, \
		{ R15, R14, R13, R12, R11, R10,   KC_NO }, \
		{ R25, R24, R23, R22, R21, R20,   KC_NO }, \
		{ R35, R34, R33, R32, R31, R30,   R36 }, \
        { R45, R44, R43, R42, R41, KC_NO, R46 } \
	}

#define LAYOUT_ergosplit LAYOUT