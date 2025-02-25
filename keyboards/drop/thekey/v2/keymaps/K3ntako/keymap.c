// Copyright 2023 Massdrop, Inc.
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {[0] = LAYOUT(KC_LCTL, KC_ESCAPE, UG_TOGG)};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LCTL:
            if (record->event.pressed) {
                SEND_STRING("1234\n");
            }
            return false;
        case KC_ESCAPE:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_LCMD);
                register_code(KC_Q);
                send_keyboard_report();
                unregister_code(KC_Q);
                unregister_code(KC_LCMD);
                unregister_code(KC_LCTL);
                send_keyboard_report();

                wait_ms(300);

                register_code(KC_ESC);
                send_keyboard_report();
                unregister_code(KC_ESC);
                send_keyboard_report();
            }
            return false;
    }

    return true;
}

void keyboard_post_init_user(void) {
    rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL + 5); // Set to static color mode
}
