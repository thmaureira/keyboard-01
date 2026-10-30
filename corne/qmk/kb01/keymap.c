// KB-01: Corne rev1 keymap recovered from the old firmware, with three changes:
//  1. COLEMAK is a default (base) layer toggled from ADJUST, so LOWER/RAISE/ADJUST keep working
//     on top of it and the same key goes back to QWERTY (before, TG(4) on the top layer trapped you).
//     LEDs use an EVA-01 palette per layer (see layer_colors).
//  2. Every layer change taps F16..F20 so the Mac on-screen help can follow the active layer.
//  3. Two taps lock LOWER/RAISE/ADJUST (TAPPING_TOGGLE 2 in config.h).
// OLED: EVA-01 style. Left: layer, Caps Lock and an EVA-01 silhouette (stands, walks, runs, gets a halo
// from 70 wpm, draws the rifle with Caps Lock, grows wings on COLEMAK). Right: the KB-01 plate and a SYNC bar (100 wpm = full sync).
#include QMK_KEYBOARD_H
#include "lib/lib8tion/lib8tion.h"

// COLEMAK sits right above QWERTY: QMK ORs the default layer into the active ones, so as a base
// layer it has to stay below LOWER/RAISE/ADJUST or it would cover them.
enum layers { _QWERTY, _COLEMAK, _LOWER, _RAISE, _ADJUST };
enum custom_keycodes { CLMK_TG = SAFE_RANGE };

tap_dance_action_t tap_dance_actions[] = {
    [0] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
    [1] = ACTION_TAP_DANCE_DOUBLE(KC_A, RALT(KC_2)),
    [2] = ACTION_TAP_DANCE_DOUBLE(KC_RCTL, KC_MCTL),
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_split_3x6_3(
              TD(0),       KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,           KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,    KC_BSPC,
             KC_TAB,      TD(1),       KC_S,       KC_D,       KC_F,       KC_G,           KC_H,       KC_J,       KC_K,       KC_L,    KC_SCLN,    KC_QUOT,
            KC_LSFT,       KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,           KC_N,       KC_M,    KC_COMM,     KC_DOT,    KC_SLSH,    KC_RALT,
                                                KC_LGUI,      TT(_LOWER),     KC_SPC,         KC_ENT,      TT(_RAISE),      TD(2)
    ),
    [_LOWER] = LAYOUT_split_3x6_3(
              TD(0),       KC_1,       KC_2,       KC_3,       KC_4,       KC_5,           KC_6,       KC_7,       KC_8,       KC_9,       KC_0,    KC_BSPC,
             KC_TAB,    MS_WHLR,    MS_WHLD,    MS_BTN2,    MS_UP,      MS_BTN1,        KC_MCTL,      KC_UP,    KC_MRWD,    KC_MFFD,    KC_MUTE,    KC_MPLY,
            KC_LSFT,    MS_WHLL,    MS_WHLU,    MS_LEFT,    MS_DOWN,    MS_RGHT,        KC_LEFT,    KC_DOWN,    KC_RGHT,    KC_MCTL,    KC_LPAD,    KC_PSCR,
                                                KC_LGUI,    KC_TRNS,     KC_SPC,         KC_ENT,      TT(_ADJUST),      TD(2)
    ),
    [_RAISE] = LAYOUT_split_3x6_3(
             KC_GRV, LSFT(KC_1), RALT(KC_2), RALT(KC_3), LSFT(KC_4), LSFT(KC_5),    LSFT(KC_LBRC), LSFT(KC_6),LSFT(KC_RBRC), LSFT(KC_8), LSFT(KC_9),    KC_BSPC,
             KC_TAB,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,        KC_SLSH, LSFT(KC_0),RALT(KC_LBRC),RALT(KC_RBRC),RALT(KC_GRV),    KC_LBRC,
            KC_LSFT,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,    LSFT(KC_SLSH),    KC_RBRC,RALT(KC_QUOT),RALT(KC_NUHS), RALT(KC_1), RALT(KC_4),
                                                KC_LGUI,      TT(_ADJUST),     KC_SPC,         KC_ENT,    KC_TRNS,      TD(2)
    ),
    [_ADJUST] = LAYOUT_split_3x6_3(
            RM_TOGG,    CLMK_TG,      KC_NO,      KC_NO,      KC_NO,      KC_NO,          KC_P7,      KC_P8,      KC_P9,    KC_SLSH, LSFT(KC_7),    KC_BSPC,
            RM_NEXT,    RM_HUEU,    RM_SATU,    RM_VALU,      KC_NO,      KC_NO,          KC_P4,      KC_P5,      KC_P6,    KC_RBRC,LSFT(KC_RBRC),      KC_NO,
            RM_HUED,    RM_SATD,    RM_VALD,      KC_NO,      KC_NO,      KC_NO,          KC_P1,      KC_P2,      KC_P3, LSFT(KC_0), LSFT(KC_3),      KC_NO,
                                                KC_LGUI,    KC_TRNS,     KC_SPC,         KC_ENT,    KC_TRNS,      KC_P0
    ),
    [_COLEMAK] = LAYOUT_split_3x6_3(
              TD(0),       KC_Q,       KC_W,       KC_F,       KC_P,       KC_G,           KC_J,       KC_L,       KC_U,       KC_Y,    KC_SCLN,    KC_BSPC,
             KC_TAB,       KC_A,       KC_R,       KC_S,       KC_T,       KC_D,           KC_H,       KC_N,       KC_E,       KC_I,       KC_O,    KC_QUOT,
            KC_LSFT,       KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,           KC_K,       KC_M,    KC_COMM,     KC_DOT,    KC_SLSH,     KC_ESC,
                                                KC_LGUI,      TT(_LOWER),     KC_SPC,         KC_ENT,      TT(_RAISE),      TD(2)
    ),
};
// clang-format on

// ---------- Layer report + LED colors ----------
// EVA-01 palette on EVA_BREATH (rgb_matrix_user.inc, ALPHAS_MODS that breathes): alpha keys take the layer hue, modifier keys and underglow take
// hue + speed (the accent). COLEMAK keeps the QWERTY colors; Esc and Backspace breathe red instead.
typedef struct { uint8_t hue, sat, spd; } layer_color_t;
static const layer_color_t PROGMEM layer_colors[] = {
    [_QWERTY]  = {190, 255, 130}, // EVA purple, lime green edges
    [_COLEMAK] = {190, 255, 130},
    [_LOWER]   = { 14, 255, 176}, // orange, purple edges
    [_RAISE]   = { 64, 255, 126}, // lime green, purple edges
    [_ADJUST]  = {112, 150, 168}, // mint, orange edges
};
// F16 QWERTY, F17 LOWER, F18 RAISE, F19 ADJUST, F20 COLEMAK (base)
static const uint8_t PROGMEM layer_fkey[] = {
    [_QWERTY] = KC_F16, [_COLEMAK] = KC_F20, [_LOWER] = KC_F17, [_RAISE] = KC_F18, [_ADJUST] = KC_F19,
};

static uint8_t shown_layer = 255;
static void layer_changed(uint8_t layer) {
    if (layer == shown_layer) return;
    shown_layer = layer;
    if (is_keyboard_master()) tap_code(pgm_read_byte(&layer_fkey[layer]));
    rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_EVA_BREATH);
    rgb_matrix_sethsv_noeeprom(pgm_read_byte(&layer_colors[layer].hue), pgm_read_byte(&layer_colors[layer].sat), rgb_matrix_get_val());
    rgb_matrix_set_speed_noeeprom(pgm_read_byte(&layer_colors[layer].spd));
}

static uint8_t current_layer(void) {
    uint8_t top = get_highest_layer(layer_state);
    return top > _COLEMAK ? top : get_highest_layer(default_layer_state);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t top = get_highest_layer(state);
    layer_changed(top > _COLEMAK ? top : get_highest_layer(default_layer_state));
    return state;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    uint8_t top = get_highest_layer(layer_state);
    layer_changed(top > _COLEMAK ? top : get_highest_layer(state));
    return state;
}

void keyboard_post_init_user(void) {
    shown_layer = 255;
    layer_changed(current_layer());
}

// The slave half gets the layers over split transport; follow them for the LED colors.
void housekeeping_task_user(void) {
    if (!is_keyboard_master()) layer_changed(current_layer());
}

// COLEMAK warning: Esc and Backspace breathe red while COLEMAK is the base and no other layer is on.
bool rgb_matrix_indicators_user(void) {
    if (current_layer() == _COLEMAK) {
        uint8_t v = scale8(sin8(timer_read() / 8), rgb_matrix_get_val());
        rgb_matrix_set_color(g_led_config.matrix_co[0][0], v, 0, 0); // Esc
        rgb_matrix_set_color(g_led_config.matrix_co[4][0], v, 0, 0); // Backspace (right half, mirrored)
    }
    return false;
}

#ifdef OLED_ENABLE
#    include "eva_sprites.h"

// OLED (both halves rotated, 32x128). Left: layer, Caps Lock and an EVA-01 silhouette that follows
// the typing speed. Right: the KB-01 plate and the SYNC bar (100 wpm = full sync).
#    define OLED_W 32
#    define FULL_SYNC 100
#    define HALO_WPM  70   // from here on the EVA runs with the halo

static void put_byte(uint8_t page, uint8_t x, uint8_t v) { oled_write_raw_byte(v, page * OLED_W + x); }

// Hazard stripes on the 6 px of a page: top = rows 0-5 of page 0, bottom = rows 2-7 of page 15.
static void hazard(uint8_t page, uint8_t first_row) {
    for (uint8_t x = 0; x < OLED_W; x++) {
        uint8_t v = 0;
        for (uint8_t b = first_row; b < first_row + 6; b++) {
            uint8_t y = page * 8 + b;
            if (((x + y) / 4) % 2 == 0) v |= 1 << b;
        }
        put_byte(page, x, v);
    }
}

// Draws a sprite so its last page lands on page 14 and clears the pages above it down to page 5
// (page 4 is the CAPS label).
// lift (0-7) moves it up that many pixels (the jump), dx shifts it sideways.
static void draw_eva(const char *spr, uint8_t npages, uint8_t lift, int8_t dx) {
    uint8_t top = 15 - npages;
    for (uint8_t p = 5; p < top - 1; p++)
        for (uint8_t x = 0; x < OLED_W; x++) put_byte(p, x, 0);
    for (int8_t p = -1; p < npages; p++) {
        for (uint8_t x = 0; x < OLED_W; x++) {
            int8_t  sx = x - dx;
            uint8_t v  = 0;
            if (sx >= 0 && sx < OLED_W) {
                uint8_t cur   = p >= 0 ? pgm_read_byte(spr + p * OLED_W + sx) : 0;
                uint8_t below = p + 1 < npages ? pgm_read_byte(spr + (p + 1) * OLED_W + sx) : 0;
                v             = lift ? (cur >> lift) | (below << (8 - lift)) : cur;
            }
            put_byte(top + p, x, v);
        }
    }
}

// Layer name at double height (6x16 per letter) in a white box on rows 9-26, clear of the hazard stripe.
extern const unsigned char font[] PROGMEM;
static uint8_t stretch(uint8_t nibble) {
    uint8_t v = 0;
    for (uint8_t b = 0; b < 4; b++)
        if (nibble & (1 << b)) v |= 3 << (2 * b);
    return v;
}
static void write_tall(const char *str) {
    for (uint8_t x = 0; x < OLED_W; x++) {
        uint8_t  i = x / 6, c = i < 5 ? pgm_read_byte(str + i) : 0;
        uint8_t  col = c ? pgm_read_byte(&font[c * 6 + x % 6]) : 0;
        uint32_t letters = (uint32_t)(stretch(col & 0x0F) | (uint16_t)stretch(col >> 4) << 8) << 2;   // rows 10-25
        uint32_t v = 0x7FFFEUL & ~letters;                                                            // box rows 9-26
        put_byte(1, x, v);
        put_byte(2, x, v >> 8);
        put_byte(3, x, v >> 16);
    }
}

// With the rifle out (Caps Lock), every key fires a bullet from the muzzle (x 22, y 94) to the right edge.
#    define MUZZLE_X 22
#    define MUZZLE_Y 94
static uint8_t  bullets[3];   // x of each bullet in flight, 0 = free
static uint16_t bullet_timer;
static void fire(void) {
    for (uint8_t i = 0; i < 3; i++)
        if (!bullets[i]) {
            bullets[i] = MUZZLE_X;
            return;
        }
}
static void draw_bullets(uint8_t lift) {
    bool step = timer_elapsed(bullet_timer) > 25;
    if (step) bullet_timer = timer_read();
    for (uint8_t i = 0; i < 3; i++) {
        if (!bullets[i]) continue;
        oled_write_pixel(bullets[i], MUZZLE_Y - lift, true);
        oled_write_pixel(bullets[i] + 1, MUZZLE_Y - lift, true);
        if (step && (bullets[i] += 3) >= OLED_W) bullets[i] = 0;
    }
}

static uint16_t jump_timer;
static bool     jumping;
// Space makes the EVA jump: up to 6 px and back down in 300 ms.
static uint8_t jump_lift(void) {
    if (!jumping) return 0;
    uint16_t t = timer_elapsed(jump_timer);
    if (t >= 300) {
        jumping = false;
        return 0;
    }
    return 6 - (t > 150 ? t - 150 : 150 - t) / 25;
}

static void render_left(uint8_t wpm, bool tick) {
    hazard(0, 0);
    switch (get_highest_layer(layer_state)) {
        case _LOWER:  write_tall(PSTR("LOWER")); break;
        case _RAISE:  write_tall(PSTR("RAISE")); break;
        case _ADJUST: write_tall(PSTR("ADJST")); break;
        default:      write_tall(get_highest_layer(default_layer_state) == _COLEMAK ? PSTR("CLMAK") : PSTR("QWRTY"));
    }
    uint8_t j = jump_lift();
    oled_set_cursor(0, 4);
    oled_write_P(host_keyboard_led_state().caps_lock ? PSTR("CAPS") : PSTR("    "), host_keyboard_led_state().caps_lock);
    if (host_keyboard_led_state().caps_lock) {
        draw_eva(eva_caps, EVA_CAPS_PAGES, j ? j : tick, 0);                  // pallet rifle out
        draw_bullets(j ? j : tick);
    } else if (get_highest_layer(default_layer_state) == _COLEMAK) {
        draw_eva(eva_wings, EVA_WINGS_PAGES, j ? j : tick, 0);                // floating
    } else if (j) {
        draw_eva(eva_walk1, EVA_WALK1_PAGES, j, 0);                           // jump, legs apart
    } else if (wpm == 0) {
        draw_eva(eva_stand, EVA_STAND_PAGES, 0, 0);
    } else if (wpm < 50) {
        draw_eva(tick ? eva_walk2 : eva_walk1, EVA_WALK1_PAGES, 0, 0);        // stride, then passing step
    } else if (wpm < HALO_WPM) {
        draw_eva(tick ? eva_run2 : eva_run1, EVA_RUN1_PAGES, 0, 0);            // leaning stride
    } else {
        draw_eva(tick ? eva_sync2 : eva_sync1, EVA_SYNC1_PAGES, 0, 0);        // 70+ wpm: running with the halo
    }
    hazard(15, 2);
}

static void render_right(uint8_t wpm) {
    oled_write_raw_P(kb01_plate, sizeof(kb01_plate));
    uint8_t fill = (uint16_t)(wpm > FULL_SYNC ? FULL_SYNC : wpm) * 28 / FULL_SYNC;
    for (uint8_t x = 0; x < fill; x++)
        for (uint8_t y = 93; y < 96; y++) oled_write_pixel(2 + x, y, true);
    char s[4] = {wpm >= 100 ? '0' + wpm / 100 : ' ', wpm >= 10 ? '0' + (wpm / 10) % 10 : ' ', '0' + wpm % 10, 0};
    oled_set_cursor(0, 13);
    oled_write(s, false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

bool oled_task_user(void) {
    static uint16_t anim_timer = 0;
    static bool     tick       = false;
    uint8_t         wpm        = get_current_wpm();
    if (timer_elapsed(anim_timer) > (wpm >= 50 ? 150 : 250)) {
        anim_timer = timer_read();
        tick       = !tick;
    }
    if (is_keyboard_master()) {
        render_left(wpm, tick);
    } else {
        oled_set_cursor(0, 0);
        render_right(wpm);
    }
    return false;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CLMK_TG:
            if (record->event.pressed) {
                // Swap the base layer; not saved, so unplugging always comes back on QWERTY.
                default_layer_set(get_highest_layer(default_layer_state) == _COLEMAK ? 1UL << _QWERTY : 1UL << _COLEMAK);
            }
            return false;
#ifdef OLED_ENABLE
        case KC_SPC:
            if (record->event.pressed && !jumping) {
                jumping    = true;
                jump_timer = timer_read();
            }
            break;
        default:
            if (record->event.pressed && host_keyboard_led_state().caps_lock) fire();
            break;
#endif
    }
    return true;
}
