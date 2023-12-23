// Copyright 2022 beekeeb
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

/* Layers */
enum layers {
    _SEMIMAK,
    _QWERTY,
    _GAME,
    _SYM,
    _NAV,
    _FUN
};

/* Keycodes */

/* Combos */

/* Keymaps */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base Layers */
    [_SEMIMAK] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_ESC,   KC_F,   KC_L,     KC_H,    KC_V,    KC_Z,      /*-------*/        KC_Q,    KC_W,    KC_U,    KC_O,   KC_Y,    KC_ESC,
    //|--------+--------+--------+--------+--------+--------|     |SEMIMAK|      |--------+--------+--------+--------+--------+--------|
        KC_LCTL,  KC_S,   KC_R,     KC_N,    KC_T,    KC_K,      /*-------*/        KC_C,    KC_D,    KC_E,    KC_A,   KC_I,    KC_SCLN,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LSFT,  KC_X,   KC_QUOT,  KC_B,    KC_M,    KC_J,                         KC_P,    KC_G,    KC_COMM, KC_DOT, KC_SLSH, DF(_QWERTY),
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           MO(_NAV),MO(_SYM), KC_ENT,    KC_BSPC, KC_SPC, KC_RSFT
                                        //`--------------------------'  `--------------------------'
    ),

    [_QWERTY] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        /*------*/       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|      |QWERTY|      |--------+--------+--------+--------+--------+--------|
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        /*------*/       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, DF(_GAME),
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_LGUI, KC_SPC, KC_BSPC,    KC_ENT, KC_SPC, KC_RALT
                                        //`--------------------------'  `--------------------------'
    ),

    [_GAME] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_NO,   KC_NO,    KC_Q,    KC_W,    KC_E,    KC_R,       /*------*/        KC_NO,  KC_NO,   KC_NO,   KC_NO,    KC_NO,  KC_NO,
    //|--------+--------+--------+--------+--------+--------|      |Gaming|      |--------+--------+--------+--------+--------+--------|
        KC_NO,   KC_G,     KC_S,    KC_A,    KC_D,    KC_F,       /*------*/        KC_NO,  KC_NO,   KC_NO,   KC_NO,    KC_NO,  DF(_QWERTY),
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_NO,   KC_NO,    KC_Z,    KC_X,    KC_C,    KC_NO,                        KC_NO,  KC_NO,   KC_NO,   KC_NO,    KC_NO,  DF(_SEMIMAK),
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_NO,  MO(_SYM),  KC_NO,    KC_DEL, KC_SPC, KC_RSFT
                                        //`--------------------------'  `--------------------------'
    ),

    /* Stack Layers */
    [_SYM] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_NO,   KC_9,    KC_5,     KC_1,    KC_3,   KC_7,        /*-------*/      KC_6,     KC_2,   KC_0,     KC_4,   KC_8,     KC_NO,
    //|--------+--------+--------+--------+--------+--------|      |Symbols|     |--------+--------+--------+--------+--------+--------|
        KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,  KC_NO,       /*-------*/      KC_NO,    KC_NO,  KC_NO,    KC_NO,  KC_NO,    KC_NO,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,  KC_NO,                        KC_NO,    KC_NO,  KC_NO,    KC_NO,  KC_NO,    KC_NO,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS
                                        //`--------------------------'  `--------------------------'
    ),

    [_NAV] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,     /*----------*/     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    //|--------+--------+--------+--------+--------+--------|    |Navigation|    |--------+--------+--------+--------+--------+--------|
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,     /*----------*/     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_TRNS, KC_TRNS, KC_TRNS,   MO(_FUN), KC_TRNS, KC_TRNS
                                        //`--------------------------'  `--------------------------'
    ),

    [_FUN] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_NO,   KC_NO,    KC_NO,   KC_NO,  KC_NO,   KC_NO,      /*---------*/     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  QK_CLEAR_EEPROM,
    //|--------+--------+--------+--------+--------+--------|     |Functions|    |--------+--------+--------+--------+--------+--------|
        KC_NO,   KC_NO,    KC_NO,   KC_NO,  KC_NO,   KC_NO,      /*---------*/     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  QK_MAKE,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_NO,   KC_NO,    KC_NO,   KC_NO,  KC_NO,   KC_NO,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  QK_BOOT,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS
                                        //`--------------------------'  `--------------------------'
    )
};

/* Additional Functionality */
