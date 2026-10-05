#include QMK_KEYBOARD_H

// ──────────────── Слои
enum Layers {
    _BASE,   // [0] Базовый слой
    _NAV,    // [1] Слой навигации и управления подсветкой
    _NUM,    // [2] Numpad слой
    _FN,     // [3] Функциональный слой
    _PUNCT   // [4] Знаки пунктуации
};

// ──────────────── Короткие названия для действий в layout

// слои
#define L_A         LT(_NAV,   KC_A)
#define L_F         LT(_NUM,   KC_F)
#define L_SPC       LT(_FN,    KC_SPC)
#define L_FN        LT(_FN,    KC_MUTE)
#define L_BSPC      LT(_PUNCT, KC_BSPC)
#define L_CTRL      LT(_NAV,   KC_END)

// яркость (с помощью Twinkle Tray)
#define BR_DOWN     C(S(KC_F1))
#define BR_UP       C(S(KC_F2))

// прочее
#define CAPS        TD(TD_CAPS)
#define CLEAR       QK_CLEAR_EEPROM
#define X______     KC_NO
#define X           KC_NO    // заглушка для отсутствующих свитчей
#define SWITCH      KC_PAUS

// ──────────────── Tap Dance

enum {
    TD_CAPS = 0
};

// Caps-Lock
void td_caps_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code16(LALT(KC_LSFT));   // Alt+Shift
    } else if (state->count == 2) {
        tap_code(KC_CAPS);           // Caps Lock
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_caps_finished, NULL)
};

// ──────────────── Раскладка
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT_all(
        KC_ESC,      KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSLS,  KC_DEL,
        KC_TAB,      KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,            KC_BSPC,
        TD(TD_CAPS), L_A,      KC_S,     KC_D,     L_F,      KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            X,        KC_ENT,
        KC_LSFT, X,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,      RSFT_T(KC_UP),  L_FN,     KC_PGDN,
        KC_LCTL,     KC_LGUI,  KC_LALT,            L_SPC,    KC_ENT,   L_BSPC,             KC_RALT,                      KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_END
    ),

    [_NAV] = LAYOUT_all(
        KC_GRV,      KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_GRV,   A(KC_4),
        X______,     X______,  KC_LGUI,  KC_F2,    KC_F4,    X______,  X______,  KC_HOME,  KC_UP,    KC_PGUP,  A(KC_4),  A(KC_4),  X______,            SWITCH,
        KC_CAPS,     X______,  KC_LCTL,  KC_LSFT,  KC_LALT,  X______,  KC_ENT,   KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_BSPC,  KC_DEL,             X,        KC_ENT,
        X______, X,  C(KC_Z),  C(KC_X),  C(KC_C),  C(KC_V),  A(KC_1),  X______,  KC_END,   X______,  KC_PGDN,  X______,            KC_PGUP,  X______,  X______,
        X______,     X______,  X______,            KC_ESC,   X______,  X______,            X______,                      KC_HOME,  KC_PGDN,  KC_END,   X______
    ),

    [_NUM] = LAYOUT_all(
        KC_GRV,      X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  A(KC_4),
        X______,     X______,  G(KC_L),  KC_F2,    KC_F4,    X______,  KC_PSLS,  KC_P7,    KC_P8,    KC_P9,    KC_PMNS,  X______,  X______,            X______,
        KC_CAPS,     X______,  KC_PSLS,  KC_PAST,  X______,  X______,  KC_ENT,   KC_P4,    KC_P5,    KC_P6,    KC_PPLS,  KC_BSPC,            X,        KC_PENT,
        X______, X,  X______,  X______,  X______,  X______,  X______,  KC_PAST,  KC_P1,    KC_P2,    KC_P3,    KC_PDOT,            X______,  X______,  X______,
        X______,     X______,  X______,            KC_LALT,  X______,  KC_P0,              X______,                      X______,  X______,  X______,  X______
    ),

    [_FN] = LAYOUT_all(
        QK_BOOT,     C(KC_1),  C(KC_2),  C(KC_3),  C(KC_4),  C(KC_5),  C(KC_6),  C(KC_7),  C(KC_8),  C(KC_9),  C(KC_0),  BR_DOWN,  BR_UP,    X______,  A(KC_4),
        CLEAR,       A(KC_F4), C(KC_W),  G(KC_E),  C(KC_R),  C(KC_T),  C(KC_Y),  X______,  KC_INS,   X______,  X______,  X______,  X______,            X______,
        KC_CAPS,     C(KC_A),  C(KC_S),  G(KC_D),  C(KC_F),  X______,  KC_ENT,   X______,  X______,  G(KC_L),  X______,  KC_MPLY,            X,        X______,
        KC_LSFT, X,  C(KC_Z),  C(KC_X),  C(KC_C),  C(KC_V),  A(KC_1),  X______,  X______,  BL_DOWN,  BL_UP,    BL_TOGG,            KC_VOLU,  X______,  KC_PGUP,
        X______,     X______,  KC_LALT,            X______,  X______,  X______,            X______,                      KC_MPRV,  KC_VOLD,  KC_MNXT,  KC_HOME
    ),

    [_PUNCT] = LAYOUT_all(
        KC_GRV,      KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_GRV,   A(KC_4),
        X______,     X______,  X______,  X______,  X______,  X______,  X______, S(KC_MINS),S(KC_EQL),KC_MINS,  KC_EQL,   X______,  X______,            X______,
        KC_CAPS,     S(KC_1),  S(KC_2),  S(KC_3),  S(KC_4),  S(KC_5),  S(KC_6),  S(KC_7),  S(KC_8),  S(KC_9),  S(KC_0),  KC_MINS,            X,        X______,
        X______, X,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  KC_PDOT,            X______,  X______,  X______,
        X______,     X______,  X______,            X______,  X______,  X______,            X______,                      X______,  X______,  X______,  X______
    )

};



// ──────────────── Дополнительные функции

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Выход в бутлодер с QK_BOOT работает только вместе с левым Shift
    if (keycode == QK_BOOT) {
        if (record->event.pressed &&
            (get_mods() & MOD_BIT(KC_LSFT))) {
            backlight_set(0);
            reset_keyboard();
        }

        return false;
    }

    return true;
}

bool is_flow_tap_key(uint16_t keycode) {
    // Определяет для каких клавиш Flow Tap НЕ РАБОТАЕТ
    switch (keycode) {
        case LT(_FN, KC_SPC):
            return false;
    }
    // Иначе работает для всех остальных клавиш
    return true;
}

