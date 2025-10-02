#include "sym_word.h"
#include "defines.h"

static uint16_t sym_word_timer;
static bool _sym_word_enabled = false;

bool sym_word_enabled(void) {
    return _sym_word_enabled;
}

void enable_sym_word(void) {
    _sym_word_enabled = true;
    layer_on(_SYM);
}

void disable_sym_word(void) {
    _sym_word_enabled = false;
    layer_off(_SYM);
}

void process_sym_word_activation(const keyrecord_t *record) {
    if (record->event.pressed) {
        // Press: turn on layer immediately for hold
        layer_on(_SYM);
        sym_word_timer = timer_read();
    } else {
        if (timer_elapsed(sym_word_timer) < TAPPING_TERM) {
            // Tap: enable sticky sym_word
            _sym_word_enabled = true;
        } else {
            // Hold released: turn off again
            layer_off(_SYM);
        }
    }
}

bool process_sym_word(uint16_t keycode, const keyrecord_t *record) {
    if (!_sym_word_enabled) return true;

    // unwrap mod-tap, layer-tap, tap-dance into base kc if tapped
    switch (keycode) {
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            if (record->tap.count == 0) return true;
            keycode = keycode & 0xFF;
    }

    switch (keycode) {
        // allowed while sym_word is active
        case KC_0:
        case KC_1:
        case KC_2:
        case KC_3:
        case KC_4:
        case KC_5:
        case KC_6:
        case KC_7:
        case KC_8:
        case KC_9:
        case KC_DOT:
        case KC_BSPC:
            break;
        case SYMCANCEL:
            if (record->event.pressed) {
                disable_sym_word();
            }
            return false;
        default:
            if (record->event.pressed) {
                tap_code16(keycode);
                disable_sym_word();
            }
            return false;
    }

    return true;
}
