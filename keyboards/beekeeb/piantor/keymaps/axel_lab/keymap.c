// Copyright 2022 beekeeb
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Docs: https://docs.qmk.fm/

#include QMK_KEYBOARD_H
#include "defines.h"
#include "sym_word.h"

// TODO (future):
// - Oxidization: https://nullp.tr/posts/oxidising-my-keyboard/#the-fruits-of-our-labour

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* ,-----------------------------------------.                ,-----------------------------------------.
     * | TAB  |  J   |  B   |  G   |  D   |  K   |                |  Z   |  C   |  O   |  U   |  ,<  | BSPC |
     * |------+------+------+------+------+------|                |------+------+------+------+------+------|
     * |  Q   |  H   |  N   |  S   |  T   |  M   |                |  MAG | SMAG |  A   |  E   |  I   |  -_  |
     * |------+------+------+------+------+------|                |------+------+------+------+------+------|
     * | LSFT |  Y   |  P   |  F   |  V   |  X   |                |  '"  |  W   |  /?  |  ;:  |  .>  | EXTND|
     * `------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------|
     *                             | SYM  |  R   |  L   |  |ENTER |SPACE |  _   |
     *                             `--------------------'  `--------------------'
     *                                                                                                        */
    [_BASE] = LAYOUT_split_3x6_3(
    //|-----------------------------------------------------|                    |-----------------------------------------------------|
        KC_TAB,   KC_J,    KC_B,    KC_G,    KC_D,    KC_K,     /*-----------*/     KC_Z,    KC_C,    KC_O,    KC_U,  KC_COMMA,KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|    |AFTERBURNER|   |--------+--------+--------+--------+--------+--------|
         KC_Q,    KC_H,    KC_N,    KC_S,    KC_T,    KC_M,     /*-----------*/    QK_AREP, QK_SREP,  KC_A,    KC_E,   KC_I,   KC_MINS,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        OS_LSFT,  KC_Y,    KC_P,    KC_F,    KC_V,    KC_X,                       KC_QUOTE,  KC_W,   KC_SLSH, KC_SCLN, KC_DOT, OS_EXTND,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            SYMWORD,  KC_R,   KC_L,      KC_ENTER,KC_SPACE, KC_UNDS
    //                                    |--------------------------|  |--------------------------|
    //                                         |        |      |              |       |       |
    //                                         |        |      .--  OS_LCTL --.       |       |
    //                                         |        .---------  OS_LGUI ----------.       |
    //                                         .------------------  OS_LALT ------------------.
    ),
    /* NUM + SYMBOL LAYER
     * ,-----------------------------------------.                ,-----------------------------------------.
     * |   @  |   7  |   5  |   1  |   3  |  #   |                |   +  |   2  |   0  |   4  |  ,<  | BSPC |
     * |------+------+------+------+------+------|                |------+------+------+------+------+------|
     * |   %  |   {  |   }  |   (  |   )  |  &   |                |  MAG |   =  |   *  |   !  |   6  |  -_  |
     * |------+------+------+------+------+------|                |------+------+------+------+------+------|
     * | LSFT |   [  |   ]  |   \  |   9  |  |   |                |  '"  |   8  |  /?  |  ;:  |  .>  | EXTND|
     * `------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------|
     *                             |  SYM |  `~  |   ^  |  |ENTER |SPACE |   $  |
     *                             `--------------------'  `--------------------'
     *                                                                                                        */
    [_SYM] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_AT,     KC_7,    KC_5,    KC_1,    KC_3,  KC_HASH,                      KC_PLUS,   KC_2,    KC_0,    KC_4,  ________,________,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_PERC, KC_LCBR, KC_RCBR,  KC_LPRN, KC_RPRN,KC_AMPR,                      ________, KC_EQL, KC_ASTR, KC_EXLM,   KC_6,  ________,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       ________,KC_LBRC, KC_RBRC,  KC_BSLS,  KC_9,  KC_PIPE,                      ________,  KC_8,  ________,________,________,________,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           SYMCANCL, KC_GRV, KC_CIRC,    ________,________, KC_DLR
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
                                           ________,________,________,   ________,________,________
                                        //`--------------------------'  `--------------------------'
    ),

};

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

    // Symbol Bigrams
    case KC_LEFT_PAREN:        return KC_RIGHT_PAREN;       // ()
    case KC_LEFT_BRACKET:      return KC_RIGHT_BRACKET;     // []
    case KC_LEFT_CURLY_BRACE:  return KC_RIGHT_CURLY_BRACE; // {}
    case KC_RIGHT_PAREN:       return KC_SCLN;              // );
    case KC_RIGHT_BRACKET:     return KC_SCLN;              // ];
    case KC_RIGHT_CURLY_BRACE: return KC_SCLN;              // };
    case KC_QUESTION:          return KC_SCLN;              // ?;
    case KC_QUOTE:             return KC_COMMA;             // ', and ",
    case KC_MINS:              return KC_EQUAL;             // -=
    case KC_PLUS:              return KC_EQUAL;             // +=
    case KC_ASTERISK:          return KC_EQUAL;             // *=
    case KC_GT:                return KC_EQUAL;             // >=
    case KC_LT:                return KC_EQUAL;             // <=
    case KC_HASH:              return KC_LEFT_BRACKET;      // #[
    case KC_DOLLAR:            return KC_RIGHT_CURLY_BRACE; // ${

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
    // NOTE: this must be handled before everything else.
    if (keycode == SYMWORD) {
        process_sym_word_activation(record);
        return false;
    }

    // Let the helper decide if this keycode should be handled for us
    if (!process_sym_word(keycode, record)) {
        return false;
    }

    // switch (keycode) {
    // }

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
