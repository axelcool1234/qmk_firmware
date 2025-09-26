// Copyright 2022 beekeeb
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Docs: https://docs.qmk.fm/

#include QMK_KEYBOARD_H

// TODO:
// - Oxidization: https://nullp.tr/posts/oxidising-my-keyboard/#the-fruits-of-our-labour

///--- Layers ---///
/// The following defines the layers of the keyboard in order. Used in `keymaps`.
/// BUNYA:       Base layer. Uses Bunya alt keyboard layout. https://layouts.wiki/layouts/2023/bunya/
enum layers {
    _BUNYA,
};

///--- Alias Macros ---////
/// i.e., alternative names for other defined macros.
#define XXXXXXXX  XXXXXXX
#define ________  _______

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base Layers */
    [_BUNYA] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXXX,  KC_B,    KC_L,    KC_M,    KC_C,    KC_Z,      /*-------*/        KC_X,    KC_F,    KC_O,    KC_U,  KC_COMMA,XXXXXXXX,
    //|--------+--------+--------+--------+--------+--------|     | BUNYA |      |--------+--------+--------+--------+--------+--------|
       XXXXXXXX,  KC_N,    KC_R,    KC_T,    KC_D,    KC_P,      /*-------*/        KC_Y,    KC_H,    KC_A,    KC_E,    KC_I,  KC_MINUS,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXXX, KC_SCLN,  KC_J,    KC_Q,    KC_G,    KC_W,                         KC_K,    KC_V,  KC_QUOTE,KC_SLASH, KC_DOT, XXXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXXX,  KC_S,  XXXXXXXX,   XXXXXXXX,XXXXXXXX,XXXXXXXX
                                        //`--------------------------'  `--------------------------'
    ),
};
