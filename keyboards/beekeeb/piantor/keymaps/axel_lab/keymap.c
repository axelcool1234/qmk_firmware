// Copyright 2022 beekeeb
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Docs: https://docs.qmk.fm/

#include QMK_KEYBOARD_H

// TODO:
// - Oxidization: https://nullp.tr/posts/oxidising-my-keyboard/#the-fruits-of-our-labour

///--- Layers ---///
/// The following defines the layers of the keyboard in order. Used in `keymaps`.
/// BASE:       Base layer. Uses Recurva-colstag2 alt keyboard layout. https://layouts.wiki/layouts/2023/recurva/
enum layers {
    _BASE,
};

///--- Alias Macros ---////
/// i.e., alternative names for other defined macros.
#define XXXXXXXX  XXXXXXX
#define ________  _______

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base Layers */
    [_BASE] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXXX,  KC_F,    KC_R,    KC_D,    KC_P,    KC_V,      /*-------*/        KC_Q,    KC_L,    KC_U,    KC_O,    KC_Y,  XXXXXXXX,
    //|--------+--------+--------+--------+--------+--------|     |RECURVA|      |--------+--------+--------+--------+--------+--------|
       XXXXXXXX,  KC_S,    KC_N,    KC_T,    KC_C,    KC_B,      /*-------*/        KC_M,    KC_H,    KC_E,    KC_A,    KC_I,  XXXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXXX,  KC_Z,    KC_X,    KC_K,    KC_G,    KC_W,                         KC_J,   KC_DOT,  KC_SCLN,KC_QUOTE,KC_COMMA,XXXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXXX,KC_SPACE,XXXXXXXX,   XXXXXXXX, QK_REP, XXXXXXXX
                                        //`--------------------------'  `--------------------------'
    ),
};
