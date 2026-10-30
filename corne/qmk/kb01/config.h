#pragma once

#define MASTER_LEFT
#define TAPPING_TERM 200
#define TAPPING_TOGGLE 2          // two taps on LOWER/RAISE/ADJUST lock the layer

// Layer report to the Mac: on every layer change the keyboard taps F16..F20 (see keymap.c).
// The on-screen help (Hammerspoon) listens for them and swallows them.

#define SPLIT_LAYER_STATE_ENABLE  // the slave half needs the layer for the LED colors
#define SPLIT_WPM_ENABLE

// RGB matrix: EVA_BREATH (rgb_matrix_user.inc), colors set per layer in keymap.c (EVA-01 palette).
// No reactive (keypress) effects are enabled, so RGB_MATRIX_KEYPRESSES is left out.
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CUSTOM_EVA_BREATH
#define RGB_MATRIX_DEFAULT_HUE 190
#define RGB_MATRIX_DEFAULT_SAT 255
#define RGB_MATRIX_DEFAULT_VAL 120   // the board caps brightness at 120 (USB power)
#define RGB_MATRIX_DEFAULT_SPD 130
#define RGB_MATRIX_SLEEP
#define ENABLE_RGB_MATRIX_BREATHING

#define OLED_TIMEOUT 60000

// Flash is tight (28 KB): features this keymap does not use are compiled out.
#define NO_ACTION_ONESHOT         // no one-shot keys
#define LAYER_STATE_8BIT          // 5 layers fit in 8 bits
