// using as reference
// https://docs.qmk.fm/#/keymap

// thanks to atlacat, hailbreno, itsaferbie and weeheavy...

// and special thanks to  AGausmann and drashna for the layer-activated RGB underglow
// https://www.reddit.com/r/olkb/comments/6t1vdu/update_layeractivated_rgb_underglow/
// https://github.com/AGausmann/qmk_firmware/blob/agausmann-v3.x/keyboards/nyquist/keymaps/agausmann/keymap.c

#include QMK_KEYBOARD_H
#include "keymap_german.h"


// Helpful defines
#define _______ KC_TRNS
#define XXXXXXX KC_NO

/*
* Each layer gets a name for readability.
* The underscores don't mean anything - you can
* have a layer called STUFF or any other name.
* Layer names don't all need to be of the same
* length, and you can also skip them entirely
* and just use numbers.
*
*/
#define BL    0     // Base Layer
#define FL    1     // Function Layer

// rgb mode for BL layer
#define RGB_BL_MODE    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT)
//rgb light for BL layer
#define RGB_BL_LIGHT   rgblight_sethsv_noeeprom_turquoise()
//
// rgb mode for FL layer
#define RGB_FL_MODE    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT)
//rgb light for FL layer
#define RGB_FL_LIGHT   rgblight_sethsv_noeeprom_orange()
//


// Row 1: 15 keys
// Row 2: 13 keys
// Row 3: 14 keys
// Row 4: 13 keys
// Row 5: 11 keys

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Keymap BL: Base Layer (Default Layer)
   *  Graphic is not up to date!
   * ,-----------------------------------------------------------.
   * | ' | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = | B | D |
   * |-----------------------------------------------------------|
   * | Tab | q | w | e | r | t | y | u | i | o | p | [ | ] |enter|
   * |------------------------------------------------------     |
   * | Caps  | a | s | d | f | g | h | j | k | l | ; | ' | # |   |
   * |-----------------------------------------------------------|
   * |Shft   | z | x | c | v | b | n | m | , | . | / | Shft |GAME|
   * |-----------------------------------------------------------|
   * |Ctrl|Gui |Alt |  BSPC  | FN |  Space  |Alt |Gui | NL |Ctrl |
   * `-----------------------------------------------------------'
   */
   [BL] = LAYOUT_60_ansi_split_iso_enter(
	//  1          2          3          4          5          6          7          8          9          10         11         12         13         14         15
	    KC_ESC,    KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_MINS,   KC_EQL,    KC_BSPC, KC_DEL,
      KC_TAB ,   KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,      KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,      KC_LBRC,   KC_RBRC,
  LCTL_T(KC_ENT),KC_A,      KC_S,      KC_D,      KC_F,      KC_G,      KC_H,      KC_J,      KC_K,      KC_L,      KC_SCLN,   KC_QUOT,   KC_NUHS,   KC_ENT,
      KC_LSPO,   KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      KC_N,      KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,   KC_RSPC,   TG(FL),
      KC_LCTL,   KC_LGUI,   KC_LALT,   KC_BSPC,   MO(FL),    KC_SPC,   MO(FL),     KC_LEFT,   KC_DOWN,   KC_UP,     KC_RIGHT),

  /* Keymap FL: Function Layer
   * Graphic is not up to date!
   * ,-----------------------------------------------------------.
   * |ESC|F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|  DEL  |
   * |-----------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   |   |prt|   |   |     |
   * |------------------------------------------------------     |
   * |       |m l|m d|m u|m r|   |   | l | d | u | r |   |   |   |
   * |-----------------------------------------------------------|
   * |    |   |   |   |   |mb1|mb2|   |hm |pgd|pgu|end|          |
   * |-----------------------------------------------------------|
   * |    |    |    |        |    |         |    |    |    |     |
   * `-----------------------------------------------------------'
   */
   [FL] = LAYOUT_60_ansi_split_iso_enter(
	//  1          2          3          4          5          6          7          8          9          10         11         12         13         14         15
	    KC_GRV,    KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,    KC_F12,   KC_BSPC, KC_DEL,
      _______ ,  DE_AE,   _______,     KC_END ,   _______,   _______,   DE_UE,  KC_MS_LEFT,KC_MS_DOWN,KC_MS_UP, KC_MS_RIGHT,   DE_UE  ,   _______,
      _______,   KC_HOME,  KC_PGDOWN,  KC_PGUP,   KC_END,  KC_MS_BTN2, KC_MS_BTN1, KC_LEFT,   KC_DOWN,   KC_UP,    KC_RIGHT,   DE_OE  ,   DE_AE  ,   _______,
      _______,   KC_LEFT,   KC_DOWN,   KC_UP,     KC_RIGHT,  _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
      _______,   _______,   _______,   KC_DEL,    _______,  S(KC_ENT),  _______,   _______,   _______,   _______,   _______),

};


void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Custom Functions
const uint16_t PROGMEM cfunc[] = {
  //[0] = ACTION_FUNCTION(0),  // Calls action_function()
};

// layer-activated RGB underglow
// gets called each time layers get changed
uint32_t layer_state_set_user(uint32_t state) {

  #ifdef RGBLIGHT_ENABLE
  switch (biton32(state)) {
    case FL:
      RGB_FL_MODE;
      RGB_FL_LIGHT;
      break;
    default: //default layer or any undefined layers
      RGB_BL_MODE;
      RGB_BL_LIGHT;
      break;
  }
  #endif //RGBLIGHT_ENABLE

  return state;
}
