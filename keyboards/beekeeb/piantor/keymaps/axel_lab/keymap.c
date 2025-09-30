// Copyright 2022 beekeeb
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Docs: https://docs.qmk.fm/

#include QMK_KEYBOARD_H

// TODO (future):
// - Oxidization: https://nullp.tr/posts/oxidising-my-keyboard/#the-fruits-of-our-labour
//
// TODO (now):
// - Change SYM layer
// - Change OS_NUM to a layer key with CAPSWORD functionality. It can additionally be turned off by pressing the key again or by pressing OS_SYM.
// - Figure out changing OS_SYM to some other layer trick. One-shot is not good enough for multi-character symbols.

///--- Layers ---///
/// The following defines the layers of the keyboard in order. Used in `keymaps`.
/// BASE:   Base layer. Uses Afterburner alt keyboard layout. https://layouts.wiki/layouts/2025/afterburner/
/// SYM:    Symbol layer. Mirrored version of Pascal Getreuer's symbol layer.
/// NUM:    Number layer. Numbers are on homerow, assigned to fingers based off how common it is.
/// EXTEND: Extend layer. Used for modifiers and arrow key movement.
enum layers {
    _BASE,
    _SYM,
    _NUM,
    _EXTEND,
};

///--- Keycodes ---///
/// Defines custom keycodes
/// M_UP_DIR: types ../
/// M_DCOLN:  types ::
enum keycodes {
    // Custom oneshot mod implementation with no timers, courtesy of Callum's mods.
    /* Macros */
    M_UP_DIR = SAFE_RANGE,
    M_DCOLN,
};

///--- Alias Macros ---////
/// i.e., alternative names for other defined macros.
#define XXXXXXXX XXXXXXX
#define ________ _______

/* Switch layer
 * LT means Layer-Tap
 * LA means Layer-Activate (the same as an MO() call, deactivates upon keyup)
 * OSL means Oneshot-Layer
 * TD means Tapdance
 * */
#define OS_SYM   OSL(_SYM)
#define OS_NUM   OSL(_NUM)
#define OS_EXTND OSL(_EXTEND)

///--- Combos ---///
/// Defines custom combos (pressing a combination of keys produces a unique output)
/// Macro API: COMBO_DEF(combo name, output, ...keys to press simultaneously)
#define COMBO_LIST \
    COMBO_DEF(LCTRL_COMBO,  OS_LCTL,      KC_L,   KC_ENTER) \
    COMBO_DEF(LGUI_COMBO,   OS_LGUI,      KC_R,   KC_SPACE) \
    COMBO_DEF(LALT_COMBO,   OS_LALT,      OS_SYM, OS_NUM)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base Layers */
    [_BASE] = LAYOUT_split_3x6_3(
    //|-----------------------------------------------------|                    |-----------------------------------------------------|
        KC_TAB,   KC_J,    KC_B,    KC_G,    KC_D,    KC_K,     /*-----------*/     KC_Z,    KC_C,    KC_O,    KC_U,  KC_COMMA,KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|    |AFTERBURNER|   |--------+--------+--------+--------+--------+--------|
         KC_Q,    KC_H,    KC_N,    KC_S,    KC_T,    KC_M,     /*-----------*/    QK_AREP, QK_SREP,  KC_A,    KC_E,   KC_I,   KC_MINS,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        OS_LSFT,  KC_Y,    KC_P,    KC_F,    KC_V,    KC_X,                       KC_QUOTE,  KC_W,   KC_SLSH, KC_SCLN, KC_DOT, OS_EXTND,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            OS_SYM,   KC_R,   KC_L,      KC_ENTER,KC_SPACE, OS_NUM
    //                                    |--------------------------|  |--------------------------|
    //                                         |        |      |              |       |       |
    //                                         |        |      .--  OS_LCTL --.       |       |
    //                                         |        .---------  OS_LGUI ----------.       |
    //                                         .------------------  OS_LALT ------------------.
    ),
    [_SYM] = LAYOUT_split_3x6_3( // Mirrored version of Pascal Getreuer's symbol layer, with the opening and closing braces flipped for inward rolls.
                                 // Additionally, having it flipped means KC_MINS/KC_SLSH can be swapped with KC_PLUS/KC_ASTR, since those are more
                                 // common symbols and should be on the middle finger. The arrow operator -> will not be a SFB as it would be if it
                                 // were not mirrored.
                                 // Downsides to this change:
                                 // - The arrow operator -> is now an outward roll rather than an inward roll.
                                 // - The opening braces (, [, { are no longer on the middle finger, but the ring finger, despite these being
                                 //   more common than the closing braces ), ], } which are no longer on the ring finger, but the middle finger.
                                 // Upsides to this change:
                                 // - Symbols ../, /, and \ are now all next to each other.
                                 // - (), [], and {} are now inward rolls rather than outward rolls.
                                 // - Symbols - and / are now on a more dominant finger (which is good since they're more common than + and *).
                                 //
                                 // The reason the upsides outweigh the downsides (justifying the mirroring):
                                 // - Vim usage means autoclosing braces aren't helpful, so closing braces will be typed anyways, meaning the frequency of
                                 //   opening and closing brace typed should be around the same. This also means the middle and ring finger will get equal
                                 //   usage. A plus is now these symbols (), [], {} are inward rolls!
                                 // - Easier mental compartmentalization of the symbol layer with the slashes and directory macro being grouped together.
                                 // - The arrow operator -> being an outward roll is arguably better than (), [], and {} being outward rolls. Even if the
                                 //   usage of each in programming were equal, this mirroring of Getreuer's symbol layer has gained two more additional
                                 //   inward rolls. The arrow operator -> would have to be more common than (), [], and {} combined for this to be considered
                                 //   a downside.
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       ________,KC_PERC, KC_LBRC, KC_RBRC, M_DCOLN, KC_AMPR,                      KC_DOT,  KC_DQT,  KC_LT,   KC_GT,   KC_QUOT, ________,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       ________,KC_QUES, KC_LPRN, KC_RPRN, KC_COLN, KC_PIPE,                      KC_HASH, KC_EQL,  KC_MINS, KC_PLUS, KC_EXLM, ________,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       ________,KC_AT,   KC_LCBR, KC_RCBR, KC_DLR,  KC_TILD,                      M_UP_DIR,KC_BSLS, KC_SLSH, KC_ASTR, KC_CIRC, ________,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           ________,________,________,    ________,KC_UNDS, KC_SCLN
                                        //`--------------------------'  `--------------------------'
    ),
    [_NUM] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       ________, KC_PERC, KC_PLUS, KC_MINS, KC_EQL,  KC_COMM,                       KC_DOT, KC_AMPR,  KC_LT,   KC_GT, KC_PIPE, ________,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       ________,  KC_9,   KC_5,    KC_1,    KC_3,    KC_7,                          KC_6,    KC_2,    KC_0,    KC_4,    KC_8,  ________,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       ________,OS_LGUI, OS_LALT, OS_LSFT, OS_LCTL,  KC_EQL,                       KC_MINS, KC_PLUS, KC_SLSH, KC_ASTR, KC_CIRC,________,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           ________,________,________,   KC_COMM,  KC_BSPC, KC_DOT
                                        //`--------------------------'  `--------------------------'
    ),
    [_EXTEND] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       ________,________,________,________,________,________,                     ________,________,________,________,________,________,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       ________,OS_LGUI, OS_LALT, OS_LSFT, OS_LCTL, ________,                     ________, KC_LEFT, KC_DOWN,  KC_UP, KC_RIGHT,QK_MAKE,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       ________,________,________,________,________,________,                     ________,________,________,________,________,QK_BOOT,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            _______,________,________,   ________,________,________
                                        //`--------------------------'  `--------------------------'
    ),

};

/* TEMP SYM + NUM layer
 * ,-----------------------------------------.                ,-----------------------------------------.
 * |      |      |      |      |      |      |                |  '"  |      |      |      |  ,<  | BSPC |
 * |------+------+------+------+------+------|                |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                |      |      |      |      |      |  -_  |
 * |------+------+------+------+------+------|                |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                |      |      |  /?  |  ;:  |  .>  |      |
 * `------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------|
 *                             |  LAY |      |      |  |  ENT | SPC  |  _   |
 *                             `--------------------'  `--------------------'
 * NEED: !@#$%^&*()+=[]{}|\~`
 * "LAY" is key need to be held to be here
 *                                                                                                        */

uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
    // Pure repeat if any modifiers besides shift
    if ((mods & (MOD_MASK_CTRL | MOD_MASK_ALT | MOD_MASK_GUI))) {
        return keycode;
    }

    // Optimal mappings:
    // PROTOC_INCLUDE='./proto/' pq --protofile proto/corpus.proto --msgtype corpus.Ngrams < corpora/reddit_small.ngrams.protobuf | jq '.bigrams | [ .[] | select(.key | test("[#]{2}")) ] | sort_by(.value)'
    switch (keycode) {
    case KC_A: return KC_O;
    case KC_G: return KC_S;
    case KC_I:  {
        uint8_t effective_mods = get_mods() | get_oneshot_mods();

        register_mods(effective_mods);
        tap_code(KC_O);
        tap_code(KC_U);
        unregister_mods(effective_mods);
        return KC_NO;
    }
    case KC_H: return KC_Y;
    case KC_U: return KC_E;
    case KC_Y: return KC_H;
    case KC_X: return KC_T;
    default: return keycode;
    }
}

uint16_t get_skip_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
    // Pure repeat if any modifiers besides shift
    if ((mods & (MOD_MASK_CTRL | MOD_MASK_ALT | MOD_MASK_GUI))) {
        return keycode;
    }

    // Optimal mappings:
    // PROTOC_INCLUDE='./proto/' pq --protofile proto/corpus.proto --msgtype corpus.Ngrams < corpora/reddit_small.ngrams.protobuf | jq '.trigrams | [ .[] | select(.key | startswith("#")) | { skipgram: (.key[0:1] + .key[2:3]), v: .value } ] | group_by(.skipgram) | [ .[] | reduce .[] as $item ( { s: "", v: 0 }; { s: $item.skipgram, v: (.v + $item.v) } ) ] | sort_by(.v)'
    switch (keycode) {
    case KC_A: return KC_O;
    case KC_B: return KC_N;
    case KC_D: return KC_T;
    case KC_F: return KC_S;
    case KC_G: return KC_S;
    case KC_H: return KC_Y;
    case KC_J: return KC_Y;
    case KC_K: return KC_T;
    case KC_L: return KC_R;
    case KC_M: return KC_K;
    case KC_O: return KC_A;
    case KC_P: return KC_N;
    case KC_Q: return KC_E;
    case KC_R: return KC_L;
    case KC_U: return KC_E;
    case KC_V: return KC_T;
    case KC_X: return KC_T;
    case KC_Y: return KC_H;
    case KC_COMM: return KC_I;
    case KC_DOT: return KC_I;
    case KC_MINS: return KC_I;
    case KC_SLSH: return KC_A;
    case KC_SCLN: return KC_E;
    default: return keycode;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        /* Macros */
        case M_UP_DIR:
            if (record->event.pressed) {
                SEND_STRING("../");
            }
            else {

            }
            return false;
        case M_DCOLN:
            if (record->event.pressed) {
                SEND_STRING("::");
            }
            else {

            }
            return false;
    }
    return true;
}


// Macro expansion junk
enum combo_events {
#define COMBO_DEF(name, output, ...) name,
    COMBO_LIST
#undef COMBO_DEF
};
#define COMBO_DEF(name, output, ...) const uint16_t PROGMEM name##_combo[] = { __VA_ARGS__, COMBO_END };
    COMBO_LIST
#undef COMBO_DEF

combo_t key_combos[] = {
#define COMBO_DEF(name, output, ...) [name] = COMBO(name##_combo, output),
    COMBO_LIST
#undef COMBO_DEF
};
