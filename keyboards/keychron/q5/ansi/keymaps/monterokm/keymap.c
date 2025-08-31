/* Copyright 2022 @ Keychron (https://www.keychron.com)
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
#define __NOK__ KC_NO

// clang-format off

enum layers{
  BASE,
  FN
};

typedef enum {
    OS_WIN,
    OS_MAC
} os_t;

enum custom_keycodes {
    SCRSHOT = SAFE_RANGE,
    // otros si quieres...
};



os_t current_os = OS_WIN;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_ansi_100(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,      KC_F11,     KC_F12,  KC_DEL,   KC_HOME,  KC_END,   KC_PGUP,  KC_PGDN,  RM_NEXT,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,        KC_MINS,    KC_EQL,   KC_BSPC,           SCRSHOT,  KC_PSLS,  KC_PAST,  KC_PMNS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,        KC_LBRC,    KC_RBRC,  KC_BSLS,            KC_P7,    KC_P8,    KC_P9,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,     KC_QUOT,              KC_ENT,             KC_P4,    KC_P5,    KC_P6,    KC_PPLS,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,      KC_SLSH,              KC_RSFT,  KC_UP,    KC_P1,    KC_P2,    KC_P3,
        KC_LCTL,  KC_LOPT,  KC_LCMD,                                KC_SPC,                                 KC_RCTL,     KC_ROPT,     MO(FN),      KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_P0,    KC_PDOT,  KC_PENT),
    [FN] = LAYOUT_ansi_100(
        __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__,    __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__,     __NOK__,    __NOK__,   __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__,
        __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__,    __NOK__,  __NOK__,            __NOK__,  __NOK__,  __NOK__,  KC_VOLD,
        __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__,    __NOK__,  __NOK__,            __NOK__,  __NOK__,  __NOK__,
        __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__,              __NOK__,            __NOK__,  __NOK__,  __NOK__,  KC_VOLU,
        __NOK__,            __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__,              __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__,
        __NOK__,  __NOK__,  __NOK__,                                __NOK__,                                __NOK__,  __NOK__,    __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__,  __NOK__),
};

#ifdef RGB_MATRIX_ENABLE


bool rgb_matrix_indicators_user(void) {
    // Apaga todos los LEDs
    rgb_matrix_set_color_all(0, 0, 0);

    // Si la capa FN está activa, colorea todo de azul
    if (layer_state_is(FN)) {
        for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
            rgb_matrix_set_color(i, 60, 60, 215); // azul
        }
    }

    // Caps Lock activa → rojo
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(CAPS_LOCK_LED_INDEX, 255, 255, 255);
    }

    return false; // ignora efectos RGB predeterminados
}
#endif

void keyboard_post_init_user(void) {
    if (!host_keyboard_led_state().num_lock) {
        tap_code(KC_NUM);
    }
}


bool dip_switch_update_kb(uint8_t index, bool active) {
    if (index == 0) {
        current_os = active ? OS_MAC : OS_WIN;
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (keycode == KC_NUM && record->event.pressed) {
        if (!host_keyboard_led_state().num_lock) {
            tap_code(KC_NUM);
        }
        return false;
    }
    if (!record->event.pressed) return true;

    switch (keycode) {
        case SCRSHOT:
            if (current_os == OS_WIN) {
               // tap_code16(G(S(KC_S)));   // Windows: Win+Shift+S
                tap_code16(KC_W);   // Windows: Win+Shift+S
            } else {
                //tap_code16(C(S(KC_4)));   // Mac: Cmd+Shift+4
                tap_code16(KC_M);   // Mac: Cmd+Shift+4
            }
            return false;
    }
    return true;
}