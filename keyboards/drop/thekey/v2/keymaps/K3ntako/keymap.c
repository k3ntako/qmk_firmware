// Copyright 2023 Massdrop, Inc.
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum custom_keycodes {
    LAYER_SWITCH = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(KC_LCTL, KC_ESCAPE, UG_NEXT),
    [0] = LAYOUT(LAYER_SWITCH, KC_LCTL, KC_ESCAPE),
    [1] = LAYOUT(LAYER_SWITCH, UG_TOGG, UG_NEXT),
    [2] = LAYOUT(LAYER_SWITCH, UG_VALD, UG_VALU),
};

uint16_t layer = 0;

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
        case LAYER_SWITCH:
            if (record->event.pressed) {
                if (layer > 0) {
                    layer_off(layer);
                }

                layer = (layer + 1) % 5;

                if (layer > 0) {
                    layer_on(layer);
                }
            }
            return false;
    }

    return true;
}

void keyboard_post_init_user(void) {
    rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL + 5); // Set to static color mode
}
