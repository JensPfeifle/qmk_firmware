
/* Copyright 2020 Jens Pfeifle
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

// 2 taps to lock layer
#define TAPPING_TOGGLE 2

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
    [0] = LAYOUT_ortho_5x15(    KC_ESC    , KC_1 ,  KC_2  ,  KC_3  , KC_4 ,  KC_5 ,   ___xx___   ,    KC_DEL   ,   ___xx___   ,  KC_6 ,  KC_7  ,  KC_8  ,  KC_9 ,  KC_0  ,    KC_GRV    ,
                                KC_TAB    , KC_Q ,  KC_W  ,  KC_E  , KC_R ,  KC_T , LSFT(KC_LBRC),   KC_PGUP   , LSFT(KC_RBRC),  KC_Y ,  KC_U  ,  KC_I  ,  KC_O ,  KC_P  , LSFT(KC_QUOT),
                            LCTL_T(KC_ESC), KC_A ,  KC_S  ,  KC_D  , KC_F ,  KC_G ,    KC_LBRC   ,   KC_PGDN   ,    KC_RBRC   ,  KC_H ,  KC_J  ,  KC_K  ,  KC_L , KC_SCLN,    KC_QUOT   ,
                               KC_LSPO    , KC_Z ,  KC_X  ,  KC_C  , KC_V ,  KC_B ,  LSFT(KC_9)  ,   ___xx___  ,  LSFT(KC_0)  ,  KC_N ,  KC_M  , KC_COMM, KC_DOT, KC_SLSH,    KC_RSPC   ,
                               KC_LCTL    , MO(3), KC_LGUI, KC_LALT, MO(1), KC_ENT,    KC_LGUI   , LSFT(KC_ENT),     TT(2)    , KC_SPC, KC_BSPC,  KC_F5 , KC_F10, KC_F11 , LSFT(KC_F11) ),
    [1] = LAYOUT_ortho_5x15( SGUI(KC_Q)  ,     KC_F1    ,     KC_F2    ,    KC_F3   ,     KC_F4    ,    KC_F5    ,   ___xx___  , ___xx___, ___xx___,  KC_F6  ,  KC_F7  ,  KC_F8  ,  KC_F9  ,  KC_F10 ,  KC_F11 ,
                            LGUI(KC_BSPC),  LGUI(KC_1)  ,  LGUI(KC_2)  , LGUI(KC_3) ,  LGUI(KC_4)  ,  LGUI(KC_5) , LGUI(KC_ENT), ___xx___, ___xx___, ___xx___, ___xx___, ___xx___, ___xx___, ___xx___,  KC_F12 ,
                            LCTL(KC_ESC) , LGUI(KC_LEFT), LGUI(KC_DOWN), LGUI(KC_UP), LGUI(KC_RGHT), LGUI(KC_SPC),   ___xx___  , ___xx___, ___xx___, ___xx___, ___xx___, ___xx___, ___xx___, ___xx___, KC_RCTL ,
                               KC_LSFT   ,  LGUI(KC_6)  ,  LGUI(KC_7)  , LGUI(KC_8) ,  LGUI(KC_9)  ,  LGUI(KC_0) , SGUI(KC_ENT), ___xx___, ___xx___, ___xx___, KC_RSFT , ___xx___, ___xx___, ___xx___, KC_RSFT ,
                               KC_LCTL   ,    KC_TRNS   ,   ___xx___   ,  ___xx___  ,    KC_TRNS   ,   ___xx___  ,   ___xx___  , ___xx___, KC_TRNS , ___xx___, ___xx___, ___xx___, ___xx___, ___xx___, ___xx___),
    [2] = LAYOUT_ortho_5x15(___xx___,  KC_F1  ,  KC_F2  ,  KC_F3  ,  KC_F4  ,  KC_F5  ,  KC_P7  ,  KC_P8  ,  KC_P9 ,  KC_F6  ,     KC_F7    ,     KC_F8    ,    KC_F9    ,  KC_F10 ,  KC_F11 ,
                            ___xx___, ___xx___, ___xx___, ___xx___, ___xx___, KC_PPLS ,  KC_P4  ,  KC_P5  ,  KC_P6 , KC_HOME , LCTL(KC_LEFT), LCTL(KC_RGHT),    KC_END   , ___xx___,  KC_F12 ,
                            ___xx___, ___xx___, ___xx___, ___xx___, ___xx___, KC_PAST ,  KC_P1  ,  KC_P2  ,  KC_P3 , KC_LEFT ,    KC_DOWN   ,     KC_UP    ,   KC_RGHT   , ___xx___, ___xx___,
                            ___xx___, ___xx___, ___xx___, ___xx___, ___xx___, KC_PSLS ,  KC_P0  , KC_PDOT , KC_PENT, KC_MINS , LSFT(KC_MINS),    KC_EQL    , LSFT(KC_EQL), ___xx___, ___xx___,
                            ___xx___, KC_TRNS , ___xx___, ___xx___, KC_TRNS , ___xx___, ___xx___, ___xx___, KC_TRNS, ___xx___,   ___xx___   ,   ___xx___   ,   ___xx___  , ___xx___, ___xx___),
    [3] = LAYOUT_ortho_5x15( RESET  , EEP_RST , ___xx___, ___xx___, ___xx___, ___xx___, RGB_SPI , RGB_TOG , RGB_SPD, ___xx___, ___xx___, ___xx___, ___xx___, ___xx___, ___xx___,
                            ___xx___, ___xx___, ___xx___, ___xx___, ___xx___, ___xx___, RGB_VAI , RGB_MOD , RGB_VAD, ___xx___, ___xx___, ___xx___, ___xx___, ___xx___, ___xx___,
                            ___xx___, ___xx___, ___xx___, ___xx___, ___xx___, ___xx___, RGB_HUI , RGB_RMOD, RGB_HUD, ___xx___, ___xx___, ___xx___, ___xx___, ___xx___, ___xx___,
                            ___xx___, ___xx___, ___xx___, ___xx___, ___xx___, ___xx___, RGB_SAI , ___xx___, RGB_SAD, ___xx___, ___xx___, ___xx___, ___xx___, ___xx___, ___xx___,
                            ___xx___, KC_TRNS , ___xx___, ___xx___, KC_TRNS , ___xx___, ___xx___, ___xx___, KC_TRNS, ___xx___, ___xx___, ___xx___, ___xx___, ___xx___, ___xx___)
};

void matrix_init_user(){
    // unicode input mode
    set_unicode_input_mode(UC_LNX);
    // lighting
    RGB_DEFAULT_MODE;
    RGB_DEFAULT_LIGHT;

  // set numlock to "on" by default
  if (!(host_keyboard_leds() & (1<<USB_LED_NUM_LOCK))) {
      register_code(KC_NUMLOCK);
      unregister_code(KC_NUMLOCK);
  }
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
