// EVA_BREATH: ALPHAS_MODS colors (alphas = hue, modifiers and underglow = hue + speed) that breathe
// between 40% and 100% of the current brightness.
RGB_MATRIX_EFFECT(EVA_BREATH)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool EVA_BREATH(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    hsv_t hsv = rgb_matrix_config.hsv;
    hsv.v     = scale8(hsv.v, 102 + scale8(sin8(g_rgb_timer / 12), 153));
    rgb_t rgb1 = rgb_matrix_hsv_to_rgb(hsv);
    hsv.h += rgb_matrix_config.speed;
    rgb_t rgb2 = rgb_matrix_hsv_to_rgb(hsv);

    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
            rgb_matrix_set_color(i, rgb2.r, rgb2.g, rgb2.b);
        } else {
            rgb_matrix_set_color(i, rgb1.r, rgb1.g, rgb1.b);
        }
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
