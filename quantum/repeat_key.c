// Copyright 2022-2023 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "repeat_key.h"
#include "quantum_keycodes.h"
#include "action_util.h"

// History entry tracking both user input and generated output
typedef struct {
    keyrecord_t user_record;        // What the user actually pressed
    uint8_t     user_mods;          // Mods when user pressed the key
    keyrecord_t generated_record;   // What was actually generated/processed
    uint8_t     generated_mods;     // Mods for the generated key
} keypress_history_entry_t;

// History buffer: [0] = most recent, [1] = second most recent
static keypress_history_entry_t keypress_history[2] = {0};
// Signed count of the number of times the last key has been repeated or
// alternate repeated: it is 0 when a key is pressed normally, positive when
// repeated, and negative when alternate repeated.
static int8_t last_repeat_count = 0;
// The repeat_count, but set to 0 outside of repeat_key_invoke() so that it is
// nonzero only while a repeated key is being processed.
static int8_t processing_repeat_count = 0;
// The keycode of the repeat key currently being processed (KC_NO when not processing)
static uint16_t processing_repeat_keycode = KC_NO;

uint16_t get_last_keycode(void) {
    return keypress_history[0].generated_record.keycode;
}

uint8_t get_last_mods(void) {
    return keypress_history[0].generated_mods;
}

void set_last_keycode(uint16_t keycode) {
    set_last_record(keycode, &(keyrecord_t){
#ifndef NO_ACTION_TAPPING
                                 .tap.interrupted = false,
                                 .tap.count       = 1,
#endif
                             });
}

void set_last_mods(uint8_t mods) {
    keypress_history[0].generated_mods = mods;
}

keyrecord_t* get_last_record(void) {
    return &keypress_history[0].generated_record;
}

void set_last_record(uint16_t keycode, keyrecord_t* record) {
    // Shift history: current becomes previous
    keypress_history[1] = keypress_history[0];
    
    uint8_t mods = get_mods() | get_weak_mods();
#ifndef NO_ACTION_ONESHOT
    mods |= get_oneshot_mods();
#endif

    if (processing_repeat_count != KC_NO) {
        // We're processing a generated key from a repeat operation
        keypress_history[0].user_record = *record;
        keypress_history[0].user_record.keycode = processing_repeat_keycode;
        keypress_history[0].generated_record = *record;
        keypress_history[0].generated_record.keycode = keycode;
        keypress_history[0].user_mods = mods;
        keypress_history[0].generated_mods = mods;
    } else {
        // Normal key: user and generated are the same
        keypress_history[0].user_record = *record;
        keypress_history[0].user_record.keycode = keycode;
        keypress_history[0].generated_record = *record;
        keypress_history[0].generated_record.keycode = keycode;
        keypress_history[0].user_mods = mods;
        keypress_history[0].generated_mods = mods;
    }
    
    last_repeat_count = 0;
}

/** @brief Updates `last_repeat_count` in direction `dir`. */
static void update_last_repeat_count(int8_t dir) {
    if (dir * last_repeat_count < 0) {
        last_repeat_count = dir;
    } else if (dir * last_repeat_count < 127) {
        last_repeat_count += dir;
    }
}

int8_t get_repeat_key_count(void) {
    return processing_repeat_count;
}

void repeat_key_invoke(const keyevent_t* event) {
    // It is possible (e.g. in rolled presses) that the last key changes while
    // the Repeat Key is pressed. To prevent stuck keys, it is important to
    // remember separately what key record was processed on press so that the
    // the corresponding record is generated on release.
    static keyrecord_t registered_record       = {0};
    static int8_t      registered_repeat_count = 0;
    // Since this function calls process_record(), it may recursively call
    // itself. We return early if `processing_repeat_count` is nonzero to
    // prevent infinite recursion.
    if (processing_repeat_count || !keypress_history[0].generated_record.keycode) {
        return;
    }

    if (event->pressed) {
        update_last_repeat_count(1);
        // On press, apply the last mods state, stacking on top of current mods.
        register_weak_mods(keypress_history[0].generated_mods);
        registered_record       = keypress_history[0].generated_record;
        registered_repeat_count = last_repeat_count;
    }

    // Generate a keyrecord and plumb it into the event pipeline.
    registered_record.event = *event;
    processing_repeat_keycode = QK_REPEAT_KEY;
    processing_repeat_count = registered_repeat_count;
    process_record(&registered_record);
    processing_repeat_count = 0;
    processing_repeat_keycode = KC_NO;

    // On release, restore the mods state.
    if (!event->pressed) {
        unregister_weak_mods(keypress_history[0].generated_mods);
    }
}

#ifndef NO_ALT_REPEAT_KEY
/**
 * @brief Find alternate keycode from a table of opposing keycode pairs.
 * @param table Array of pairs of basic keycodes, declared as PROGMEM.
 * @param table_size_bytes The size of the table in bytes.
 * @param target The basic keycode to find.
 * @return The alternate basic keycode, or KC_NO if none was found.
 *
 * @note The table keycodes and target must be basic keycodes.
 *
 * This helper is used several times below to define alternate keys. Given a
 * table of pairs of basic keycodes, the function finds the pair containing
 * `target` and returns the other keycode in the pair.
 */
static uint8_t find_alt_keycode(const uint8_t (*table)[2], uint8_t table_size_bytes, uint8_t target) {
    const uint8_t* keycodes = (const uint8_t*)table;
    for (uint8_t i = 0; i < table_size_bytes; ++i) {
        if (target == pgm_read_byte(keycodes + i)) {
            // Xor (i ^ 1) the index to get the other element in the pair.
            return pgm_read_byte(keycodes + (i ^ 1));
        }
    }
    return KC_NO;
}

uint16_t get_alt_repeat_key_keycode(bool allow_recursion) {
    uint16_t keycode = keypress_history[0].user_record.keycode;
    uint8_t  mods    = keypress_history[0].user_mods;

    // Call the user callback first to give it a chance to override the default
    // alternate key definitions that follow.
    uint16_t alt_keycode = get_alt_repeat_key_keycode_user(keycode, mods);

    if (alt_keycode != KC_TRANSPARENT) {
        // If user returned a repeat keycode and recursion is allowed, re-execute that operation
        if (allow_recursion && alt_keycode == QK_SKIP_ALT_REPEAT_KEY) {
            return get_skip_alt_repeat_key_keycode(false);
        }
        if (allow_recursion && alt_keycode == QK_ALT_REPEAT_KEY) {
            // Re-execute alt repeat with the generated keycode from the target
            return get_alt_repeat_key_keycode_user(keypress_history[0].generated_record.keycode, keypress_history[0].generated_mods);
        }
        return alt_keycode;
    }

    // Convert 8-bit mods to the 5-bit format used in keycodes. This is lossy:
    // if left and right handed mods were mixed, they all become right handed.
    mods = ((mods & 0xf0) ? /* set right hand bit */ 0x10 : 0)
           // Combine right and left hand mods.
           | (((mods >> 4) | mods) & 0xf);

    switch (keycode) {
        case QK_MODS ... QK_MODS_MAX: // Unpack modifier + basic key.
            mods |= QK_MODS_GET_MODS(keycode);
            keycode = QK_MODS_GET_BASIC_KEYCODE(keycode);
            break;

#    ifndef NO_ACTION_TAPPING
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
            break;
#        ifndef NO_ACTION_LAYER
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
            break;
#        endif // NO_ACTION_LAYER
#    endif     // NO_ACTION_TAPPING

#    ifdef SWAP_HANDS_ENABLE
        case QK_SWAP_HANDS ... QK_SWAP_HANDS_MAX:
            if (IS_SWAP_HANDS_KEYCODE(keycode)) {
                return KC_NO;
            }
            keycode = QK_SWAP_HANDS_GET_TAP_KEYCODE(keycode);
            break;
#    endif // SWAP_HANDS_ENABLE
    }

    if (IS_QK_BASIC(keycode)) {
        if ((mods & (MOD_LCTL | MOD_LALT | MOD_LGUI))) {
            // The last key was pressed with a modifier other than Shift.
            // The following maps
            //   mod + F <-> mod + B
            // and a few others, supporting several core hotkeys used in
            // Emacs, Vim, less, and other programs.
            // clang-format off
            static const uint8_t pairs[][2] PROGMEM = {
                {KC_F   , KC_B   },  // Forward / Backward.
                {KC_D   , KC_U   },  // Down / Up.
                {KC_N   , KC_P   },  // Next / Previous.
                {KC_A   , KC_E   },  // Home / End.
                {KC_O   , KC_I   },  // Older / Newer in Vim jump list.
            };
            // clang-format on
            alt_keycode = find_alt_keycode(pairs, sizeof(pairs), keycode);
        } else {
            // The last key was pressed with no mods or only Shift. The
            // following map a few more Vim hotkeys.
            // clang-format off
            static const uint8_t pairs[][2] PROGMEM = {
                {KC_J   , KC_K   },  // Down / Up.
                {KC_H   , KC_L   },  // Left / Right.
                // These two lines map W and E to B, and B to W.
                {KC_W   , KC_B   },  // Forward / Backward by word.
                {KC_E   , KC_B   },  // Forward / Backward by word.
            };
            // clang-format on
            alt_keycode = find_alt_keycode(pairs, sizeof(pairs), keycode);
        }

        if (!alt_keycode) {
            // The following key pairs are considered with any mods.
            // clang-format off
            static const uint8_t pairs[][2] PROGMEM = {
                {KC_LEFT, KC_RGHT},  // Left / Right Arrow.
                {KC_UP  , KC_DOWN},  // Up / Down Arrow.
                {KC_HOME, KC_END },  // Home / End.
                {KC_PGUP, KC_PGDN},  // Page Up / Page Down.
                {KC_BSPC, KC_DEL },  // Backspace / Delete.
                {KC_LBRC, KC_RBRC},  // Brackets [ ] and { }.
#ifdef EXTRAKEY_ENABLE
                {KC_WBAK, KC_WFWD},  // Browser Back / Forward.
                {KC_MNXT, KC_MPRV},  // Next / Previous Media Track.
                {KC_MFFD, KC_MRWD},  // Fast Forward / Rewind Media.
                {KC_VOLU, KC_VOLD},  // Volume Up / Down.
                {KC_BRIU, KC_BRID},  // Brightness Up / Down.
#endif  // EXTRAKEY_ENABLE
#ifdef MOUSEKEY_ENABLE
                {MS_LEFT, MS_RGHT},  // Mouse Cursor Left / Right.
                {MS_UP,   MS_DOWN},  // Mouse Cursor Up / Down.
                {MS_WHLL, MS_WHLR},  // Mouse Wheel Left / Right.
                {MS_WHLU, MS_WHLD},  // Mouse Wheel Up / Down.
#endif  // MOUSEKEY_ENABLE
            };
            // clang-format on
            alt_keycode = find_alt_keycode(pairs, sizeof(pairs), keycode);
        }

        if (alt_keycode) {
            // Combine basic keycode with mods.
            return (mods << 8) | alt_keycode;
        }
    }

    return KC_NO; // No alternate key found.
}

void alt_repeat_key_invoke(const keyevent_t* event) {
    static keyrecord_t registered_record       = {0};
    static int8_t      registered_repeat_count = 0;
    // Since this function calls process_record(), it may recursively call
    // itself. We return early if `processing_repeat_count` is nonzero to
    // prevent infinite recursion.
    if (processing_repeat_count) {
        return;
    }

    if (event->pressed) {
        registered_record = (keyrecord_t){
#    ifndef NO_ACTION_TAPPING
            .tap.interrupted = false,
            .tap.count       = 0,
#    endif
            .keycode = get_alt_repeat_key_keycode(true),
        };
    }

    // Early return if there is no alternate key defined.
    if (!registered_record.keycode) {
        return;
    }

    if (event->pressed) {
        update_last_repeat_count(-1);
        registered_repeat_count = last_repeat_count;
    }

    // Generate a keyrecord and plumb it into the event pipeline.
    registered_record.event = *event;
    processing_repeat_keycode = QK_ALT_REPEAT_KEY;
    processing_repeat_count = registered_repeat_count;
    process_record(&registered_record);
    processing_repeat_count = 0;
    processing_repeat_keycode = KC_NO;
}

// Default implementation of get_alt_repeat_key_keycode_user().
__attribute__((weak)) uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
    return KC_TRANSPARENT;
}

uint16_t get_skip_alt_repeat_key_keycode(bool allow_recursion) {
    uint16_t keycode = keypress_history[1].user_record.keycode;
    uint8_t  mods    = keypress_history[1].user_mods;

    // Call the user callback first to give it a chance to override the default
    // alternate key definitions that follow.
    uint16_t alt_keycode = get_skip_alt_repeat_key_keycode_user(keycode, mods);

    if (alt_keycode != KC_TRANSPARENT) {
        // If user returned a repeat keycode and recursion is allowed, re-execute that operation
        if (allow_recursion && alt_keycode == QK_ALT_REPEAT_KEY) {
            return get_alt_repeat_key_keycode(false);
        }
        if (allow_recursion && alt_keycode == QK_SKIP_ALT_REPEAT_KEY) {
            // Re-execute skip alt repeat with the generated keycode from the target
            return get_skip_alt_repeat_key_keycode_user(keypress_history[1].generated_record.keycode, keypress_history[1].generated_mods);
        }
        return alt_keycode;
    }

    // Use the same logic as get_alt_repeat_key_keycode() for the second-to-last key
    // Convert 8-bit mods to the 5-bit format used in keycodes. This is lossy:
    // if left and right handed mods were mixed, they all become right handed.
    mods = ((mods & 0xf0) ? /* set right hand bit */ 0x10 : 0)
           // Combine right and left hand mods.
           | (((mods >> 4) | mods) & 0xf);

    switch (keycode) {
        case QK_MODS ... QK_MODS_MAX: // Unpack modifier + basic key.
            mods |= QK_MODS_GET_MODS(keycode);
            keycode = QK_MODS_GET_BASIC_KEYCODE(keycode);
            break;

#    ifndef NO_ACTION_TAPPING
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
            break;
#        ifndef NO_ACTION_LAYER
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
            break;
#        endif // NO_ACTION_LAYER
#    endif     // NO_ACTION_TAPPING

#    ifdef SWAP_HANDS_ENABLE
        case QK_SWAP_HANDS ... QK_SWAP_HANDS_MAX:
            if (IS_SWAP_HANDS_KEYCODE(keycode)) {
                return KC_NO;
            }
            keycode = QK_SWAP_HANDS_GET_TAP_KEYCODE(keycode);
            break;
#    endif // SWAP_HANDS_ENABLE
    }

    if (IS_QK_BASIC(keycode)) {
        if ((mods & (MOD_LCTL | MOD_LALT | MOD_LGUI))) {
            // The second-to-last key was pressed with a modifier other than Shift.
            // The following maps
            //   mod + F <-> mod + B
            // and a few others, supporting several core hotkeys used in
            // Emacs, Vim, less, and other programs.
            // clang-format off
            static const uint8_t pairs[][2] PROGMEM = {
                {KC_F   , KC_B   },  // Forward / Backward.
                {KC_D   , KC_U   },  // Down / Up.
                {KC_N   , KC_P   },  // Next / Previous.
                {KC_A   , KC_E   },  // Home / End.
                {KC_O   , KC_I   },  // Older / Newer in Vim jump list.
            };
            // clang-format on
            alt_keycode = find_alt_keycode(pairs, sizeof(pairs), keycode);
        } else {
            // The second-to-last key was pressed with no mods or only Shift. The
            // following map a few more Vim hotkeys.
            // clang-format off
            static const uint8_t pairs[][2] PROGMEM = {
                {KC_J   , KC_K   },  // Down / Up.
                {KC_H   , KC_L   },  // Left / Right.
                // These two lines map W and E to B, and B to W.
                {KC_W   , KC_B   },  // Forward / Backward by word.
                {KC_E   , KC_B   },  // Forward / Backward by word.
            };
            // clang-format on
            alt_keycode = find_alt_keycode(pairs, sizeof(pairs), keycode);
        }

        if (!alt_keycode) {
            // The following key pairs are considered with any mods.
            // clang-format off
            static const uint8_t pairs[][2] PROGMEM = {
                {KC_LEFT, KC_RGHT},  // Left / Right Arrow.
                {KC_UP  , KC_DOWN},  // Up / Down Arrow.
                {KC_HOME, KC_END },  // Home / End.
                {KC_PGUP, KC_PGDN},  // Page Up / Page Down.
                {KC_BSPC, KC_DEL },  // Backspace / Delete.
                {KC_LBRC, KC_RBRC},  // Brackets [ ] and { }.
#ifdef EXTRAKEY_ENABLE
                {KC_WBAK, KC_WFWD},  // Browser Back / Forward.
                {KC_MNXT, KC_MPRV},  // Next / Previous Media Track.
                {KC_MFFD, KC_MRWD},  // Fast Forward / Rewind Media.
                {KC_VOLU, KC_VOLD},  // Volume Up / Down.
                {KC_BRIU, KC_BRID},  // Brightness Up / Down.
#endif  // EXTRAKEY_ENABLE
#ifdef MOUSEKEY_ENABLE
                {MS_LEFT, MS_RGHT},  // Mouse Cursor Left / Right.
                {MS_UP,   MS_DOWN},  // Mouse Cursor Up / Down.
                {MS_WHLL, MS_WHLR},  // Mouse Wheel Left / Right.
                {MS_WHLU, MS_WHLD},  // Mouse Wheel Up / Down.
#endif  // MOUSEKEY_ENABLE
            };
            // clang-format on
            alt_keycode = find_alt_keycode(pairs, sizeof(pairs), keycode);
        }

        if (alt_keycode) {
            // Combine basic keycode with mods.
            return (mods << 8) | alt_keycode;
        }
    }

    return KC_NO; // No alternate key found.
}

void skip_alt_repeat_key_invoke(const keyevent_t* event) {
    static keyrecord_t registered_record       = {0};
    static int8_t      registered_repeat_count = 0;
    // Since this function calls process_record(), it may recursively call
    // itself. We return early if `processing_repeat_count` is nonzero to
    // prevent infinite recursion.
    if (processing_repeat_count) {
        return;
    }

    if (event->pressed) {
        registered_record = (keyrecord_t){
#    ifndef NO_ACTION_TAPPING
            .tap.interrupted = false,
            .tap.count       = 0,
#    endif
            .keycode = get_skip_alt_repeat_key_keycode(true),
        };
    }

    // Early return if there is no skip alternate key defined.
    if (!registered_record.keycode) {
        return;
    }

    if (event->pressed) {
        update_last_repeat_count(-1);
        registered_repeat_count = last_repeat_count;
    }

    // Generate a keyrecord and plumb it into the event pipeline.
    registered_record.event = *event;
    processing_repeat_keycode = QK_SKIP_ALT_REPEAT_KEY;
    processing_repeat_count = registered_repeat_count;
    process_record(&registered_record);
    processing_repeat_count = 0;
    processing_repeat_keycode = KC_NO;
}

// Default implementation of get_skip_alt_repeat_key_keycode_user().
__attribute__((weak)) uint16_t get_skip_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
    return KC_TRANSPARENT;
}
#endif // NO_ALT_REPEAT_KEY
