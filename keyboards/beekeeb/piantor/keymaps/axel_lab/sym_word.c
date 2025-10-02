#include "sym_word.h"
#include "defines.h"

// BUG: Pressing SYM and several other keys nearly at the same time will lead to several consuming characters being sent without deactivating one-shot.
//      This isn't too big of a priority to fix because it's unlikely to happen without intentionally trying to do it.

static uint16_t sym_word_timer;

/** @brief True when Sym Word is active. */
static bool sym_word_one_shot = false;

/** @brief True when Sym's one-shot has been fired already (and thus the layer must be turned off). */
static bool sym_word_one_shot_consumed = false;

void sym_word_on(void) {
    if(sym_word_one_shot) return;

    sym_word_one_shot = true;
    layer_on(_SYM);
}

void sym_word_off(void) {
    if(!sym_word_one_shot) return;

    sym_word_one_shot = false;
    layer_off(_SYM);
}

void sym_word_toggle(void) {
    if (sym_word_one_shot) {
        sym_word_off();
    } else {
        sym_word_on();
    }
}

bool is_sym_word_on(void) {
    return sym_word_one_shot;
}

void process_sym_word_activation(const keyrecord_t *record) {
    // Key DOWN (pressed down)
    if (record->event.pressed) {
        // Press: turn on layer immediately for hold
        layer_on(_SYM);
        sym_word_timer = timer_read();
        sym_word_one_shot_consumed = false; // Start of SYMWORD press, so one-shot can't be consumed yet.
    // Key UP (release)
    } else {
        // If the one-shot wasn't consumed, flag that one-shot mode is now on (one-shot mode is on only if SYMWORD was tapped).
        if (!sym_word_one_shot_consumed && timer_elapsed(sym_word_timer) < TAPPING_TERM) {
            sym_word_one_shot = true;

        // If SYMWORD was not tapped, or one-shot was already consumed, turn off the SYM layer.
        } else {
            layer_off(_SYM);
        }
    }
}


bool _sym_word_no_consume(uint16_t keycode) {
    // The following keys does not consume one-shot mode.
    // So if SYM layer is in one-shot, these keys can be pressed multiple times without deactivating it.
    switch (keycode) {
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
            return true;
        default:
            return false;
    }

}

bool process_sym_word(uint16_t keycode, const keyrecord_t *record) {
    // If sym word isn't in one-shot mode, let key be processed normally
    if (!sym_word_one_shot) {
        // If sym word isn't in one shot mode and the sym layer is on and it's a consuming key,
        // flag that if this were to become one shot mode, the one shot has been consumed.
        if (layer_state_is(_SYM) && !_sym_word_no_consume(keycode)) {
             sym_word_one_shot_consumed = true;
        }
        return true;
    }

    // If key that's pressed is consuming, tap the key and then turn off the SYM layer.
    if(!_sym_word_no_consume(keycode)) {
        if (record->event.pressed) {
            if (keycode != SYMCANCL) {
                tap_code16(keycode);
            }
            sym_word_off();
        }
        return false;
    }

    // If key that's pressed isn't consuming, let key be processed normally.
    return true;
}
