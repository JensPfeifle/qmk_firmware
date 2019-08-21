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

enum my_layers {
    QRY,
    RS,
    LW,
    FN,
};

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


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTZ */
[QRY] = {
{ KC_GESC,  KC_F1,    KC_F2,   KC_F4,   KC_F5,   KC_F6,      KC_7,     KC_8,     KC_9 ,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL   },
{ KC_TAB,   KC_Q,     KC_W,     KC_E,   KC_R,     KC_T,      KC_4,     KC_5,     KC_6 ,    KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_NUHS  },
{ LCTL_T(KC_LBRC),  KC_A,     KC_S,     KC_D,   KC_F,     KC_G,      KC_1,     KC_2,     KC_3 ,    KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN, RCTL_T(KC_RBRC)  },
{ KC_LSPO,  KC_Z,     KC_X,     KC_C,   KC_V,     KC_B,      KC_MINS,  KC_0,     KC_EQL,   KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSPC  },
{KC_LCTL,MO(FN),  KC_LGUI,  KC_LALT,  MO(RS),  KC_SFTENT,  KC_LGUI,  LSFT(KC_LGUI), MO(LW) ,  KC_SPC,  KC_BSPC,   KC_LEFT,  KC_DOWN,  KC_UP,    KC_RIGHT },
},

/* RS Layer - Left thumbkey*/
[RS] = {
{ KC_ESC,   KC_F1,     KC_F2,    KC_F3,      KC_F4,      KC_F5,    ________, ________, ________, KC_F6,         KC_F7,         KC_F8,    KC_F9,        KC_F10,    ________ },
{ ________, KC_MPRV,   KC_VOLD,  KC_VOLU,    KC_MNXT,    KC_MPLY,  ________, ________, ________, LSFT(KC_PGUP), KC_PGDN,       KC_PGUP,  ________,     ________ , ________ },
{ ________, KC_HOME, C(KC_LEFT), C(KC_RGHT), KC_END,     ________, ________, ________, ________, ________,      KC_LEFT,       KC_DOWN,  KC_UP,        KC_RIGHT,  ________ },
{ ________, ________,  ________,  KC_QUOT, LSFT(KC_QUOT),________, ________, ________, ________, LSFT(KC_PGDN), LSFT(KC_MINS), KC_EQL,   LSFT(KC_EQL), ________,  ________ },
{ ________, ________, ________, ________,   ________,    ________, ________, ________, ________, ________,      ________,      ________, ________,     ________,  ________ },
},

/* LW Layer - right thumbkey */
[LW] = {
{ ________, ________, ________, ________,   ________, ________, ________, ________, ________, ________,      ________, ________, ________, ________,  ________ },
{ ________, ________, ________, ________,   ________, ________, ________, ________, ________, LSFT(KC_PGUP), KC_PGDN,  KC_PGUP,  ________, ________,  ________ },
{ ________, KC_HOME, C(KC_LEFT), C(KC_RGHT), KC_END,  ________, ________, ________, ________, ________,      KC_LEFT,  KC_DOWN,  KC_UP,    KC_RIGHT,  ________ },
{ ________, ________,  ________,  ________, ________, ________, ________, ________, ________, LSFT(KC_PGDN), ________, ________, ________, ________,  ________ },
{ ________, ________, ________, ________,   ________, ________, ________, ________, ________, ________,      ________, ________, ________, ________,  ________ },
},
/* FN */
[FN] = {
{ RESET   , ___xx___, ___xx___, ___xx___, ___xx___, ___xx___,  RGB_TOG,  RGB_M_P,   RGB_MOD,  ___xx___, ___xx___, ___xx___, ___xx___, ___xx___, ___xx___ },
{ ___xx___, DF(QRY) , ___xx___, ___xx___, ___xx___, ___xx___,  RGB_HUI,  RGB_SAI,   RGB_VAI,  ___xx___, XP(UE,UEU),  KC_INS , XP(OE,OEU), KC_PAUS, ___xx___ },
{ ___xx___, XP(AE,AEU) , X(SS), ___xx___, ___xx___, ___xx___,  RGB_HUD,  RGB_SAD,   RGB_VAD,  ___xx___, ___xx___, ___xx___, ___xx___, ___xx___, ___xx___ },
{ KC_ASTG , ___xx___, ___xx___, ___xx___, ___xx___, ___xx___,  UNI_LNX, ___xx___,   UNI_WIN,   KC_NLCK, ___xx___, ___xx___, ___xx___, ___xx___, KC_ASTG  },
{ ___xx___, ___xx___, ___xx___, ___xx___, ___xx___, ___xx___, ___xx___, ___xx___,  ___xx___,  ___xx___, ___xx___, ___xx___, ___xx___, ___xx___, ___xx___ },
}

};

void matrix_init_user(){
    // unucode input mode
    set_unicode_input_mode(UC_LNX);
    // lighting
    RGB_DEFAULT_MODE;
    RGB_DEFAULT_LIGHT;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case UNI_LNX:
            set_unicode_input_mode(UC_LNX);
            return false;
            break;
        case UNI_WIN:
            set_unicode_input_mode(UC_WINC);
            return false;
            break;
        case UNI_MAC:
            set_unicode_input_mode(UC_OSX);
            return false;
            break;
    }
    return true;
}
