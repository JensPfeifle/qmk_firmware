#include "ergosplit.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "keymap_german.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTZ 0
#define _LOWER 1
#define _RAISE 2

enum custom_keycodes {
  LOWER, 
  RAISE 
};

// Fillers to make layering more clear
#define ______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwertz
 * ,-----------------------------------------------------------------------------------------.
 * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  \  |  `  |
 * |-----------------------------------------------------------------------------------------+
 * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Z  |  U  |  I  |  O  |  P  |  [  |  ]  |  |     |
 * |-----------------------------------------------------------------------------------------+
 * | Ctrl    |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |     |  |    |
 * |-----------------------------------------------------------------------------------------+
 * | Shift |    |  Y  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |    | Del |      |
 * |-----------------------------------------------------------------------------------------+
 * | Ctrl  | LGUI | LAlt  | Lower | Bcsp | Enter | Shift | Space | Raise |     |     |     |     |
 * `-----------------------------------------------------------------------------------------'
 */
  [_QWERTZ] = LAYOUT( /* Basic QWERTY */ 
        KC_ESC,   DE_CIRC,    KC_1,    KC_2,    KC_3,  KC_4,   KC_5,              KC_6,    KC_7,    KC_8,    KC_9,    KC_0, DE_SS, DE_ACUT, 
        KC_TAB,        DE_Q,    DE_W,    DE_E,    DE_R,    DE_T,           DE_Z,    DE_U,    DE_I,    DE_O,    DE_P,    DE_UE, DE_PLUS, 
        KC_CAPS,        DE_A,    DE_S,    DE_D,    DE_F,    DE_G,           DE_H,    DE_J,    DE_K,    DE_L,    DE_OE,   DE_AE, DE_HASH, 
        KC_LSFT, DE_LESS, DE_Y,    DE_X,    DE_C,    DE_V,           DE_B,    DE_N,    DE_M,    DE_COMM, DE_DOT,  DE_MINS,    KC_DEL, 
        KC_LCTL, KC_LGUI, KC_LALT, LOWER,   KC_BSPC,  KC_ENT,         KC_RSFT, KC_SPC, RAISE, KC_DEL, KC_RALT, KC_RGUI, KC_RCTL 
),
  [_LOWER] = LAYOUT( /* Basic QWERTY */
        ______, ______, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, \
        ______, ______,______, ______, ______, ______ ,         ______, KC_PSCR, KC_SLCK, KC_PAUS, KC_UP, ______, ______, \
        ______, KC_VOLD,KC_VOLU,KC_MUTE,______, ______,         KC_PAST,KC_PSLS,KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT, KC_INS,  \
        ______, ______, KC_MPRV,KC_MPLY,KC_MNXT,______,         ______, KC_PPLS,KC_PMNS,KC_END,  KC_PGDN, KC_DOWN, KC_DEL, \
        ______, ______, ______, ______, ______, ______,         ______, ______, ______, ______, ______, ______, ______ \
),
  [_RAISE] = LAYOUT( /* Basic QWERTY */
        ______, ______, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, \
        ______, ______,______, ______, ______, ______ ,         ______, KC_PSCR, KC_SLCK, KC_PAUS, KC_UP, ______, ______, \
        ______, KC_VOLD,KC_VOLU,KC_MUTE,______, ______,         KC_PAST,KC_PSLS,KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT, KC_INS, \
        ______, ______, KC_MPRV,KC_MPLY,KC_MNXT,______,         ______, KC_PPLS,KC_PMNS,KC_END,  KC_PGDN, KC_DOWN, KC_DEL, \
        ______, ______, ______, ______, ______, ______,         ______, ______, ______, ______, ______, ______, ______ \
)
};

/*
void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
} */

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
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
