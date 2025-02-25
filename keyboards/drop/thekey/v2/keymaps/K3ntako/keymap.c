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

const rgblight_segment_t PROGMEM layer_indicator_0[] = RGBLIGHT_LAYER_SEGMENTS({0, 5, HSV_GREEN} // All 5 LEDs set to green
);

const rgblight_segment_t PROGMEM layer_indicator_1[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_OFF}, {1, 1, HSV_WHITE}, {2, 3, HSV_OFF});

const rgblight_segment_t PROGMEM layer_indicator_2[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_OFF}, {2, 1, HSV_WHITE}, {3, 2, HSV_OFF});

const rgblight_segment_t PROGMEM layer_indicator_3[] = RGBLIGHT_LAYER_SEGMENTS({0, 3, HSV_OFF}, {3, 1, HSV_WHITE}, {4, 1, HSV_OFF});

const rgblight_segment_t PROGMEM layer_indicator_4[] = RGBLIGHT_LAYER_SEGMENTS({0, 4, HSV_OFF}, {4, 1, HSV_WHITE});

const rgblight_segment_t *const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(layer_indicator_0, layer_indicator_1, layer_indicator_2, layer_indicator_3, layer_indicator_4);

void keyboard_post_init_user(void) {
    /* Enable the LED layers */
    rgblight_layers = rgb_layers;
    rgblight_set_layer_state(0, true);
}
