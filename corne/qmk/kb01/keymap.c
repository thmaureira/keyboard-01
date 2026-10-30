// KB-01: Corne rev1 keymap, rebuilt from the recovered firmware with Miryoku-style layers (see below) and:
//  1. COLEMAK is a default (base) layer toggled from ADJUST, so LOWER/RAISE/ADJUST keep working
//     on top of it and the same key goes back to QWERTY (before, TG(4) on the top layer trapped you).
//     LEDs use an EVA-01 palette per layer (see layer_colors).
//  2. Every layer change taps F16..F20 so the Mac on-screen help can follow the active layer.
//  3. Two taps lock LOWER/RAISE/ADJUST (TAPPING_TOGGLE 2 in config.h).
// OLED: EVA-01 style. Left: layer, Caps Lock and an EVA-01 silhouette (faces the front when idle, walks, runs,
// gets a halo from 70 wpm, holds the rifle with Caps Lock, crouches on Space, carries the lance on COLEMAK). Right: the KB-01 plate and a SYNC bar (100 wpm = full sync).
#include QMK_KEYBOARD_H
#include "lib/lib8tion/lib8tion.h"

// COLEMAK sits right above QWERTY: QMK ORs the default layer into the active ones, so as a base
// layer it has to stay below LOWER/RAISE/ADJUST or it would cover them.
enum layers { _QWERTY, _COLEMAK, _LOWER, _RAISE, _ADJUST };
enum custom_keycodes { CLMK_TG = SAFE_RANGE, ES_TILD };
// macOS treats the board as ISO and swaps two keycodes: KC_GRV types < and KC_NUBS types º (so ⌥KC_NUBS is \).
// ES_TILD types ~, which is the dead key ⌥ñ followed by a space.

tap_dance_action_t tap_dance_actions[] = {
    [0] = ACTION_TAP_DANCE_DOUBLE(KC_A, RALT(KC_2)),   // 2×A: @
    [1] = ACTION_TAP_DANCE_DOUBLE(KC_RCTL, KC_CAPS),   // 2×Ctrl: Caps Lock
};

// Miryoku-style: each layer is held with one thumb and its keys sit on the other hand.
// LOWER (left thumb): numpad on the right hand (its Backspace deletes a word, ⌥⌫), arrows (↑ on W), . and , around ↑, line start/end and modifiers on the left.
// RAISE (right thumb): symbols on the left hand; Mission Control, paste, copy, cut, undo and modifiers on the right.
// ADJUST (both): COLEMAK and the mouse on the left; Rectangle window shortcuts and media on the right.
// Symbols follow macOS with the Spanish ISO layout.
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_split_3x6_3(
             KC_ESC,       KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,           KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,    KC_BSPC,
             KC_TAB,      TD(0),       KC_S,       KC_D,       KC_F,       KC_G,           KC_H,       KC_J,       KC_K,       KC_L,    KC_SCLN,    KC_QUOT,
            KC_LSFT,       KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,           KC_N,       KC_M,    KC_COMM,     KC_DOT,    KC_SLSH,    KC_RALT,
                                                KC_LGUI, TT(_LOWER),     KC_SPC,         KC_ENT, TT(_RAISE),      TD(1)
    ),
    [_LOWER] = LAYOUT_split_3x6_3(
             KC_ESC,     KC_DOT,      KC_UP,    KC_COMM,      KC_NO,      KC_NO,  LSFT(KC_RBRC),       KC_7,       KC_8,       KC_9,    KC_SLSH,LALT(KC_BSPC),
             KC_TAB,    KC_LEFT,    KC_DOWN,    KC_RGHT,LGUI(KC_LEFT),LGUI(KC_RGHT),     LSFT(KC_7),       KC_4,       KC_5,       KC_6,    KC_RBRC, LSFT(KC_0),
            KC_LSFT,    KC_LGUI,    KC_LALT,    KC_LCTL,      KC_NO,      KC_NO,           KC_0,       KC_1,       KC_2,       KC_3,     KC_DOT,    KC_COMM,
                                                KC_LGUI,    KC_TRNS,     KC_SPC,         KC_ENT,TT(_ADJUST),      TD(1)
    ),
    [_RAISE] = LAYOUT_split_3x6_3(
            KC_LBRC, RALT(KC_2), RALT(KC_3),RALT(KC_LBRC),RALT(KC_RBRC), RALT(KC_1),        KC_MCTL, LGUI(KC_V), LGUI(KC_C), LGUI(KC_X), LGUI(KC_Z),    KC_BSPC,
            KC_MINS,     KC_EQL,LSFT(KC_MINS), LSFT(KC_8), LSFT(KC_9), LSFT(KC_7),          KC_NO,    KC_RSFT,    KC_RCTL,    KC_RALT,    KC_RGUI,      KC_NO,
             KC_GRV,    ES_TILD,RALT(KC_NUBS),RALT(KC_QUOT),RALT(KC_NUHS),  KC_NUBS,          KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
                                                KC_RBRC,TT(_ADJUST), LSFT(KC_0),         KC_ENT,    KC_TRNS,      TD(1)
    ),
    [_ADJUST] = LAYOUT_split_3x6_3(
            CLMK_TG,    MS_BTN1,      MS_UP,    MS_WHLU,    MS_WHLD,      KC_NO,          KC_NO,  LCA(KC_U), LCA(KC_UP),  LCA(KC_I),      KC_NO,    KC_MNXT,
              KC_NO,    MS_LEFT,    MS_DOWN,    MS_RGHT,      KC_NO,      KC_NO,  LCAG(KC_RGHT),LCA(KC_LEFT),LCA(KC_ENT),LCA(KC_RGHT),  KC_VOLU,    KC_MPLY,
              KC_NO,      KC_NO,    MS_BTN2,      KC_NO,      KC_NO,      KC_NO,          KC_NO,  LCA(KC_J),LCA(KC_DOWN),  LCA(KC_K),    KC_VOLD,    KC_MUTE,
                                                KC_LGUI,    KC_TRNS,     KC_SPC,         KC_ENT,    KC_TRNS,    RM_TOGG
    ),
    [_COLEMAK] = LAYOUT_split_3x6_3(
             KC_ESC,       KC_Q,       KC_W,       KC_F,       KC_P,       KC_G,           KC_J,       KC_L,       KC_U,       KC_Y,    KC_SCLN,    KC_BSPC,
             KC_TAB,       KC_A,       KC_R,       KC_S,       KC_T,       KC_D,           KC_H,       KC_N,       KC_E,       KC_I,       KC_O,    KC_QUOT,
            KC_LSFT,       KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,           KC_K,       KC_M,    KC_COMM,     KC_DOT,    KC_SLSH,     KC_ESC,
                                                KC_LGUI, TT(_LOWER),     KC_SPC,         KC_ENT, TT(_RAISE),      TD(1)
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

// OLED (both halves rotated, 32x128). Left: layer, Caps Lock and an EVA-01 silhouette: faces the front
// when idle, walks under 40 wpm, runs from 40 (with the halo from 70), holds the rifle with Caps Lock, crouches
// on Space and carries the lance on COLEMAK. Right: the KB-01 plate and the SYNC bar (100 wpm = full sync).
#    define OLED_W 32
#    define FULL_SYNC 100
#    define RUN_WPM   40   // from here on the EVA runs
#    define HALO_WPM  70   // and from here on with the halo

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
// lift (0-7) moves it up that many pixels, dx shifts it sideways.
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

// With the rifle out (Caps Lock), every key fires a bullet from the muzzle to the right edge. The muzzle is
// at (26, 83) standing and at (22, 94) crouched.
static uint8_t  bullets[3];   // x of each bullet in flight, 0 = free
static uint16_t bullet_timer;
static void fire(void) {
    for (uint8_t i = 0; i < 3; i++)
        if (!bullets[i]) {
            bullets[i] = 1;   // placed at the muzzle when drawn
            return;
        }
}
static void draw_bullets(uint8_t x0, uint8_t y) {
    bool step = timer_elapsed(bullet_timer) > 30;
    if (step) bullet_timer = timer_read();
    for (uint8_t i = 0; i < 3; i++) {
        if (!bullets[i]) continue;
        if (bullets[i] < x0) bullets[i] = x0;
        oled_write_pixel(bullets[i], y, true);
        oled_write_pixel(bullets[i] + 1, y, true);
        if (step && (bullets[i] += 2) >= OLED_W) bullets[i] = 0;
    }
}

// Space makes the EVA crouch for 300 ms.
static uint16_t crouch_timer;
static bool     crouching;
static bool crouched(void) {
    if (crouching && timer_elapsed(crouch_timer) >= 300) crouching = false;
    return crouching;
}

static void render_left(uint8_t wpm, bool tick) {
    hazard(0, 0);
    switch (get_highest_layer(layer_state)) {
        case _LOWER:  write_tall(PSTR("LOWER")); break;
        case _RAISE:  write_tall(PSTR("RAISE")); break;
        case _ADJUST: write_tall(PSTR("ADJST")); break;
        default:      write_tall(get_highest_layer(default_layer_state) == _COLEMAK ? PSTR("CLMAK") : PSTR("QWRTY"));
    }
    bool caps = host_keyboard_led_state().caps_lock;
    oled_set_cursor(0, 4);
    oled_write_P(caps ? PSTR("CAPS") : PSTR("    "), caps);
    if (crouched()) {
        draw_eva(eva_crouch, EVA_CROUCH_PAGES, 0, 0);                         // Space: crouch with the rifle
        if (caps) draw_bullets(22, 94);
    } else if (caps) {
        draw_eva(eva_gun, EVA_GUN_PAGES, 0, 0);                               // standing, rifle out
        draw_bullets(26, 83);
    } else if (get_highest_layer(default_layer_state) == _COLEMAK) {
        draw_eva(eva_lance, EVA_LANCE_PAGES, tick, 0);                        // lance, breathing
    } else if (wpm == 0) {
        draw_eva(eva_front, EVA_FRONT_PAGES, 0, 0);                           // idle: faces the front
    } else if (wpm < RUN_WPM) {
        draw_eva(tick ? eva_walk2 : eva_walk1, EVA_WALK1_PAGES, 0, 0);        // stride, then passing step
    } else if (wpm < HALO_WPM) {
        draw_eva(eva_run, EVA_RUN_PAGES, tick ? 2 : 0, 0);                    // sprint, bouncing 2 px
    } else {
        draw_eva(eva_sync, EVA_SYNC_PAGES, tick ? 2 : 0, 0);                  // 70+ wpm: sprint with the halo
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
    if (timer_elapsed(anim_timer) > (wpm >= RUN_WPM ? 150 : 250)) {
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
        case ES_TILD:
            if (record->event.pressed) {
                tap_code16(RALT(KC_SCLN));
                tap_code(KC_SPC);
            }
            return false;
        case CLMK_TG:
            if (record->event.pressed) {
                // Swap the base layer; not saved, so unplugging always comes back on QWERTY.
                default_layer_set(get_highest_layer(default_layer_state) == _COLEMAK ? 1UL << _QWERTY : 1UL << _COLEMAK);
            }
            return false;
#ifdef OLED_ENABLE
        case KC_SPC:
            if (record->event.pressed) {
                crouching    = true;
                crouch_timer = timer_read();
            }
            break;
        default:
            if (record->event.pressed && host_keyboard_led_state().caps_lock) fire();
            break;
#endif
    }
    return true;
}
