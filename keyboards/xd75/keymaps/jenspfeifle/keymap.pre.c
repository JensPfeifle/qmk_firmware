/* Copyright 2019 Jens Pfeifle
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "keymap_german.h"

#define ________ KC_TRNS
#define ___xx___ KC_NO

enum my_ucis {
    UNI_LNX,
    UNI_MAC,
    UNI_WIN,
};

enum unicode_names {
    UE,     // ü
    UEU,    // Ü
    AE,     // ä
    AEU,    // Ä
    OE,     // ö
    OEU,    // Ö
    SS,     // ß
};

const uint32_t PROGMEM unicode_map[] = {
    // use with X(i)
    // shifted with XP(i,j)
    [UE]  = 0x00FC,
    [UEU] = 0x00DC,
    [AE]  = 0x00E4,
    [AEU] = 0x00C4,
    [OE]  = 0x00F6,
    [OEU] = 0x00D6,
    [SS]  = 0x00DF
};

// rgb mode
#define RGB_DEFAULT_MODE    rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_MOOD)
//rgb light
#define RGB_DEFAULT_LIGHT   rgblight_setrgb(0,0,0)
