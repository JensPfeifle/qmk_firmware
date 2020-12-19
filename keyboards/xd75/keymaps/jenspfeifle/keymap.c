
/* Copyright 2020 Jens Pfeifle */

#include QMK_KEYBOARD_H

#define ________ KC_TRNS
#define ___xx___ KC_NO

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number { _QWERTY = 0, _LOWER, _RAISE, _ADJUST };

enum custom_keycodes { QWERTY = SAFE_RANGE, LOWER, RAISE, ADJUST, RGBRST };

// unicode characters
enum unicode_names {
    UE,   // ü
    UEU,  // Ü
    AE,   // ä
    AEU,  // Ä
    OE,   // ö
    OEU,  // Ö
    SS,   // ß
    SNEK  // 🐍
};

const uint32_t PROGMEM unicode_map[] = {
    // use single character in keymap with X(i), or shifted with XP(i,j), where
    // i and j are the mapping table indices of the lower and upper case
    // character, respectively.
    [UE]   = 0x00FC,  // ü
    [UEU]  = 0x00DC,  // Ü
    [AE]   = 0x00E4,  // ä
    [AEU]  = 0x00C4,  // Ä
    [OE]   = 0x00F6,  // ö
    [OEU]  = 0x00D6,  // Ö
    [SS]   = 0x00DF,  // ß
    [SNEK] = 0x1F40   // 🐍
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_ortho_5x15( \
      KC_ESC,          KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   _______,  _______,_______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV, \
      KC_TAB,          KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   _______,  _______,_______, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    LSFT(KC_QUOT), \
      LCTL_T(KC_ESC),  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   _______,  _______,_______, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
      KC_LSPO,         KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LBRC, _______,KC_RBRC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC , \
      ADJUST,          KC_LCTL, KC_LGUI, KC_LALT, KC_LGUI, KC_ENT,  LOWER,   _______,RAISE,   KC_SPC,  KC_BSPC, _______, _______, _______, _______ \
      ),

  [_LOWER] = LAYOUT_ortho_5x15( \
      _______, KC_F1,       KC_F2,   KC_F3,       KC_F4,       KC_F5,   _______, _______,  _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, \
      KC_TILD, KC_EXLM,     KC_AT,   KC_HASH,     KC_DLR,      KC_PERC, _______, _______,  _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_F12, \
      _______, XP(AE, AEU), X(SS),  XP(OE, OEU), XP(UE, UEU),  _______, _______, _______,  _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
      KC_CAPS, _______,     _______, _______,     _______,     _______, _______, _______, _______,  _______,  _______, _______, KC_HOME, KC_END,  _______, \
      _______, _______,     _______, _______,     _______,     _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
      ),

  [_RAISE] = LAYOUT_ortho_5x15( \
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,_______, _______, KC_F6,   KC_F7,         KC_F8,         KC_F9,        KC_F10,  KC_DEL, \
      _______, _______, _______, _______, _______, _______, _______,_______, _______, KC_HOME, LCTL(KC_LEFT), LCTL(KC_RGHT), KC_END,       _______, KC_F12, \
      _______, _______, _______, _______, _______, _______, _______,_______, _______, KC_LEFT, KC_DOWN,       KC_UP,         KC_RGHT,      _______, KC_BSLS, \
      KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, KC_MINS, KC_UNDS,       KC_EQL,        LSFT(KC_EQL), _______, _______, \
      _______, _______, _______, _______, _______, _______, _______,_______, _______, _______, _______,       _______,       _______,      _______, _______ \
      ),

  [_ADJUST] =  LAYOUT_ortho_5x15( \
      RESET,   RGBRST,  _______, _______, _______, _______,  _______,_______, _______,_______, _______, _______, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______,_______, _______, _______, _______, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______,_______, _______, QWERTY,  _______, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______,_______, _______, _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
      _______, _______, _______, _______, _______, _______, _______, _______,_______, _______, _______, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD \
      )
};


void persistent_default_layer_set(uint16_t default_layer) {
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void activate_triple_layer(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
    if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
        layer_on(layer3);
    } else {
        layer_off(layer3);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                persistent_default_layer_set(1UL << _QWERTY);
            }
            return false;
            break;
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                activate_triple_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                activate_triple_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                activate_triple_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                activate_triple_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
            break;
        case RGBRST:
            #ifdef RGBLIGHT_ENABLE
                if (record->event.pressed) {
                    eeconfig_update_rgblight_default();
                    rgblight_enable();
                }
            #endif
            break;
    }
    return true;
}
