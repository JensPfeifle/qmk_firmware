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
