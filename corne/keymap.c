// Recovered from the keyboard firmware (flash dump). Custom actions (Luna/OLED) are not included.
#include QMK_KEYBOARD_H

enum layers { _QWERTY, _LOWER, _RAISE, _ADJUST, _COLEMAK };

tap_dance_action_t tap_dance_actions[] = {
    [0] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
    [1] = ACTION_TAP_DANCE_DOUBLE(KC_A, RALT(KC_2)),
    [2] = ACTION_TAP_DANCE_DOUBLE(KC_RCTL, KC_MCTL),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_split_3x6_3(
              TD(0),       KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,           KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,    KC_BSPC,
             KC_TAB,      TD(1),       KC_S,       KC_D,       KC_F,       KC_G,           KC_H,       KC_J,       KC_K,       KC_L,    KC_SCLN,    KC_QUOT,
            KC_LSFT,       KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,           KC_N,       KC_M,    KC_COMM,     KC_DOT,    KC_SLSH,    KC_RALT,
                                                KC_LGUI,      TT(1),     KC_SPC,         KC_ENT,      TT(2),      TD(2)
    ),
    [_LOWER] = LAYOUT_split_3x6_3(
              TD(0),       KC_1,       KC_2,       KC_3,       KC_4,       KC_5,           KC_6,       KC_7,       KC_8,       KC_9,       KC_0,    KC_BSPC,
             KC_TAB,    KC_WH_R,    KC_WH_D,    KC_BTN2,    KC_MS_U,    KC_BTN1,        KC_MCTL,      KC_UP,    KC_MRWD,    KC_MFFD,    KC_MUTE,    KC_MPLY,
            KC_LSFT,    KC_WH_L,    KC_WH_U,    KC_MS_L,    KC_MS_D,    KC_MS_R,        KC_LEFT,    KC_DOWN,    KC_RGHT,    KC_MCTL,    KC_LPAD,    KC_PSCR,
                                                KC_LGUI,    KC_TRNS,     KC_SPC,         KC_ENT,      TT(3),      TD(2)
    ),
    [_RAISE] = LAYOUT_split_3x6_3(
             KC_GRV, LSFT(KC_1), RALT(KC_2), RALT(KC_3), LSFT(KC_4), LSFT(KC_5),    LSFT(KC_LBRC), LSFT(KC_6),LSFT(KC_RBRC), LSFT(KC_8), LSFT(KC_9),    KC_BSPC,
             KC_TAB,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,        KC_SLSH, LSFT(KC_0),RALT(KC_LBRC),RALT(KC_RBRC),RALT(KC_GRV),    KC_LBRC,
            KC_LSFT,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,    LSFT(KC_SLSH),    KC_RBRC,RALT(KC_QUOT),RALT(KC_NUHS), RALT(KC_1), RALT(KC_4),
                                                KC_LGUI,      TT(3),     KC_SPC,         KC_ENT,    KC_TRNS,      TD(2)
    ),
    [_ADJUST] = LAYOUT_split_3x6_3(
            RGB_TOG,      TG(4),      KC_NO,      KC_NO,      KC_NO,      KC_NO,          KC_P7,      KC_P8,      KC_P9,    KC_SLSH, LSFT(KC_7),    KC_BSPC,
            RGB_MOD,    RGB_HUI,    RGB_SAI,    RGB_VAI,      KC_NO,      KC_NO,          KC_P4,      KC_P5,      KC_P6,    KC_RBRC,LSFT(KC_RBRC),      KC_NO,
            RGB_HUD,    RGB_SAD,    RGB_VAD,      KC_NO,      KC_NO,      KC_NO,          KC_P1,      KC_P2,      KC_P3, LSFT(KC_0), LSFT(KC_3),      KC_NO,
                                                KC_LGUI,    KC_TRNS,     KC_SPC,         KC_ENT,    KC_TRNS,      KC_P0
    ),
    [_COLEMAK] = LAYOUT_split_3x6_3(
              TD(0),       KC_Q,       KC_W,       KC_F,       KC_P,       KC_G,           KC_J,       KC_L,       KC_U,       KC_Y,    KC_SCLN,    KC_BSPC,
             KC_TAB,       KC_A,       KC_R,       KC_S,       KC_T,       KC_D,           KC_H,       KC_N,       KC_E,       KC_I,       KC_O,    KC_QUOT,
            KC_LSFT,       KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,           KC_K,       KC_M,    KC_COMM,     KC_DOT,    KC_SLSH,     KC_ESC,
                                                KC_LGUI,      TT(1),     KC_SPC,         KC_ENT,      TT(2),      TD(2)
    ),
};
