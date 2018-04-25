#include "ergosplit.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "keymap_german.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2

#define TAPPING_TERM 200
//Tap Dance Declarations
//enum {
//s};
/* https://docs.qmk.fm/features/tap-dance#tap-dance:-a-single-key-can-do-3-5-or-100-different-things */

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty
 * ,-----------------------------------------,                ,-----------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |                |   6  |   7  |   8  |   9  |   0  | PgUp |
 * |------+------+------+------+------+-------                -------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                |   Y  |   U  |   I  |   O  |   P  |   Ü  |
 * |------+------+------+------+------+-------                -------+------+------+------+------+------|
 * | F5   |   A  |   S  |   D  |   F  |   G  |                |   H  |   J  |   K  |   L  |   Ö  |  Ä   |
 * |------+------+------+------+------+------|------,  ,----  -------+------+------+------+------+------|
 * | <>|  |   Z  |   X  |   C  |   V  |   B  | Win |  | AltGr |   N  |   M  |   ,  |   .  |  -_  | PgDn |
 * |------+------+------+------+------+------|-------  --------------+------+------+------+------+------|
 * |  F1  | Ctrl | Alt  | Lower| Raise|      | Shift|  |  Spc |      | BckSp| Del  |  F10 |  F11 |  F12 |
 * `------------------------------------------------'  '------------------------------------------------'
 */
[_QWERTY] = LAYOUT(
   KC_ESC ,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,   KC_7,   KC_8,     KC_9,    KC_0,   KC_PGUP, \
   KC_TAB ,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      DE_Z,   KC_U,   KC_I,     KC_O,    KC_P,    DE_UE, \
   KC_F5  ,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,   KC_J,   KC_K,     KC_L,    DE_OE,   DE_AE, \
   DE_LESS,  DE_Y,    KC_X,    KC_C,    KC_V,    KC_B,   KC_BSPC, KC_ENT,   KC_N,   KC_M,  KC_COMM,  KC_DOT, DE_MINS, KC_PGDN, \
   KC_LCTL, KC_LALT, KC_LCMD, KC_LSFT, LOWER,           KC_LSFT, RSFT_T(KC_SPC),           RAISE, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \

),

/* Lower */
[_LOWER] = LAYOUT(
   DE_CIRC, DE_EXLM ,DE_DQOT, DE_HASH, DE_DLR , DE_PERC,                   DE_AMPR, DE_SLSH, _______, _______, DE_EQL , _______, \
   _______,  DE_AT , _______, DE_EURO, DE_LESS, DE_MORE,                   _______, DE_LBRC, DE_RBRC, DE_ASTR, _______, _______, \
   _______, _______, _______, _______, DE_QST , DE_QUOT,                   DE_HASH, DE_LPRN, DE_RPRN, _______, _______, DE_QUOT, \
   _______, _______, _______, _______, DE_EXLM, _______, KC_DEL , _______, _______, DE_LCBR, DE_RCBR, _______, _______, _______, \
   KC_LCTL, KC_LALT, KC_LSFT, KC_LCMD,   LOWER,          _______, _______,           RAISE , _______, _______, _______, _______ \
),
/*
[_LOWER] = LAYOUT( \
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL, \
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,S(KC_NUHS),S(KC_NUBS),_______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
),
*/

/* Raise */
[_RAISE] = LAYOUT(
   KC_F12 ,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 ,  KC_F5 ,                    KC_F6 ,  KC_F7 ,  KC_F8 ,  KC_F9 ,  KC_F10, KC_VOLU, \
   _______, _______, _______,  KC_UP , _______, _______,                   KC_PGUP,  KC_7 ,  KC_8 ,  KC_9 , KC_PMNS,  KC_F11, \
   _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______,                   KC_HOME,  KC_4 ,  KC_5 ,  KC_6 , KC_PPLS,  KC_F12, \
   _______, _______, _______, _______, _______, _______, KC_DEL, _______, KC_PGDN,  KC_1 ,  KC_2 ,  KC_3 , KC_PENT, KC_VOLD, \
   KC_LCTL, KC_LALT, KC_LCMD, KC_LSFT,   LOWER,         _______, _______,            RAISE,  KC_P0 , KC_MPRV, KC_MPLY, KC_MNXT \
)

/*[_RAISE] = LAYOUT( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL, \
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
)*/

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      return false;
      break;
  }
  return true;
}
