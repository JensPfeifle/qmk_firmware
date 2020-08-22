#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

// unicode characters
enum unicode_names {
    UE,     // ü
    UEU,    // Ü
    AE,     // ä
    AEU,    // Ä
    OE,     // ö
    OEU,    // Ö
    SS,     // ß
    SNEK    // 🐍
};

const uint32_t PROGMEM unicode_map[] = {
    // use single character in keymap with X(i), or shifted with XP(i,j), where
    // i and j are the mapping table indices of the lower and upper case
    // character, respectively.
    [UE]  = 0x00FC,  // ü
    [UEU] = 0x00DC,  // Ü
    [AE]  = 0x00E4,  // ä
    [AEU] = 0x00C4,  // Ä
    [OE]  = 0x00F6,  // ö
    [OEU] = 0x00D6,  // Ö
    [SS]  = 0x00DF,  // ß
    [SNEK]  = 0x1F40 // 🐍
};

//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT( \
      KC_ESC,          KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV, \
      KC_TAB,          KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    LSFT(KC_QUOT), \
      LCTL_T(KC_ESC),  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
      KC_LSPO,         KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LBRC, KC_RBRC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC , \
      ADJUST,          KC_LCTL, KC_LGUI, KC_LALT, KC_LGUI, KC_ENT,  LOWER,   RAISE,   KC_SPC,  KC_BSPC, _______, _______, _______, _______ \
      ),

  [_LOWER] = LAYOUT( \
      _______, KC_F1,       KC_F2,   KC_F3,       KC_F4,       KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, \
      KC_TILD, KC_EXLM,     KC_AT,   KC_HASH,     KC_DLR,      KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_F12, \
      _______, XP(AE, AEU), X(SS),  XP(OE, OEU), XP(UE, UEU), _______,                   _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
      KC_CAPS, _______,     _______, _______,     _______,     _______, _______, _______,  _______,  _______, _______, KC_HOME, KC_END,  _______, \
      _______, _______,     _______, _______,     _______,     _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
      ),

  [_RAISE] = LAYOUT( \
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,         KC_F8,         KC_F9,        KC_F10,  KC_DEL, \
      _______, _______, _______, _______, _______, _______,                   KC_HOME, LCTL(KC_LEFT), LCTL(KC_RGHT), KC_END,       _______, KC_F12, \
      _______, _______, _______, _______, _______, _______,                   KC_LEFT, KC_DOWN,       KC_UP,         KC_RGHT,      _______, KC_BSLS, \
      KC_CAPS, _______, _______, _______, _______, _______, _______, _______, KC_MINS, KC_UNDS,       KC_EQL,        LSFT(KC_EQL), _______, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,       _______,       _______,      _______, _______ \
      ),

  [_ADJUST] =  LAYOUT( \
      RESET,   RGBRST,  _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______,                   _______, QWERTY,  _______, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD \
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
        persistent_default_layer_set(1UL<<_QWERTY);
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

void matrix_init_user(void) {
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}




//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

void matrix_scan_user(void) {
     iota_gfx_task();  // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_LOWER (1<<_LOWER)
#define L_RAISE (1<<_RAISE)
#define L_ADJUST (1<<_ADJUST)
#define L_ADJUST_TRI (L_ADJUST|L_RAISE|L_LOWER)


static void render_logo(struct CharacterMatrix *matrix) {

  static const char helix_logo[] PROGMEM ={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  matrix_write_P(matrix, helix_logo);
}


static void render_rgbled_status(struct CharacterMatrix *matrix) {
  char buf[30];
  if (RGBLIGHT_MODES > 1 && rgblight_is_enabled()) {
    snprintf(buf, sizeof(buf), " RGB M%-2d H%-2d S%-2d V%d",
              rgblight_get_mode(),
              rgblight_get_hue()/RGBLIGHT_HUE_STEP,
              rgblight_get_sat()/RGBLIGHT_SAT_STEP,
              rgblight_get_val()/RGBLIGHT_VAL_STEP);
    matrix_write(matrix, buf);
  } else {
    matrix_write_P(matrix, PSTR(" RGB OFF "));
  }
}


static void render_layer_status(struct CharacterMatrix *matrix) {
  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  char buf[10];
  matrix_write_P(matrix, PSTR(" LAYER: "));
    switch (layer_state) {
        case L_BASE:
           matrix_write_P(matrix, PSTR("DEFAULT"));
           break;
        case L_RAISE:
           matrix_write_P(matrix, PSTR("RAISE"));
           break;
        case L_LOWER:
           matrix_write_P(matrix, PSTR("LOWER"));
           break;
        case L_ADJUST:
        case L_ADJUST_TRI:
           matrix_write_P(matrix, PSTR("ADJUST"));
           break;
        default:
           matrix_write_P(matrix, PSTR("UNDEF-"));
           snprintf(buf,sizeof(buf), "%ld", layer_state);
           matrix_write(matrix, buf);
    }
}


static void render_keylock_status(struct CharacterMatrix *matrix) {
  matrix_write_P(matrix, PSTR(" "));
  matrix_write_P(matrix, (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ?
                 PSTR("CAPS") : PSTR("    "));
  matrix_write_P(matrix, (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ?
                 PSTR("NUMLOCK") : PSTR("       "));
  matrix_write_P(matrix, (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ?
                 PSTR("SCLK") : PSTR("    "));
}


void render_status(struct CharacterMatrix *matrix) {
  matrix_write_P(matrix, PSTR("\n"));
  render_layer_status(matrix);
  matrix_write_P(matrix, PSTR("\n"));

  render_rgbled_status(matrix);
  matrix_write_P(matrix, PSTR("\n"));

  render_keylock_status(matrix);
}


void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

  matrix_clear(&matrix);
  if(is_master){
    render_status(&matrix);
  }else{
    render_logo(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif
