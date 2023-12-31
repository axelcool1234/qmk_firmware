// Copyright 2022 beekeeb
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "oneshot.h"

/* TODO:
 * Vim layer?
 * LaTeX layer?
 * Common macros in the _FUN layer?
 * Replace repeat with alt repeat (Magic Semimak)?
 * Implement leader key (put in empty spot of symbol layer or empty spot in Semimak layer)?
 * Implement GPIO manipulation to control LED light on the WeAct RP2040s
 * Mess with combos at some point? Maybe common LaTeX or other programming language boilerplate can be printed via combos?
 * Implement SHIFT + QK_AREP = KC_ENT as a key override
 * Additional extend stack layers?
*/

/* Layers */
enum layers {
    // base
    _SEMIMAK,
    _QWERTY,
    _GAME,
    // tri layer
    _EXTEND,
    _SYM,
    // extend stack
    _MOUSE,
    _MEDIA,
    _FUN,
};

/* Key Codes */
enum keycodes {
    // Custom oneshot mod implementation with no timers, courtesy of Callum's mods.
    OS_GUI = SAFE_RANGE,
    OS_ALT,
    OS_SFT,
    OS_CTL,
    OS_HYP,

    /* Lower and Raise for tri layer */
    LA_SYM,
    LA_EXTEND
};

/* Misc */
#define XXXXXXXX  XXXXXXX
#define ________  _______
#define VOL_DOWN  KC_KB_VOLUME_DOWN
#define VOL_UP    KC_KB_VOLUME_UP
#define CL_EEP    QK_CLEAR_EEPROM
#define HOME_CAP  QK_CAPS_WORD_TOGGLE

/* Custom keys */
#define PASTE     LCTL(KC_V)
#define COPY      LCTL(KC_C)
#define CUT       LCTL(KC_X)
#define UNDO      LCTL(KC_Z)
#define REDO      LCTL(KC_Y)
#define P_FUN     OSL(_FUN)

/* Switch base */
#define D_QWERTY  DF(_QWERTY)
#define D_GAMING  DF(_GAME)
#define D_SEMIMAK DF(_SEMIMAK)

/* Switch layer */
#define MS_ON     TO(_MOUSE)
#define MS_OFF    TG(_MOUSE)
#define MED_ON    TO(_MEDIA)
#define MED_OFF   TG(_MEDIA)

/* Keymaps */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base Layers */
    [_SEMIMAK] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,   KC_F,   KC_L,     KC_H,    KC_V,    KC_Z,       /*-------*/       KC_Q,    KC_W,    KC_U,    KC_O,   KC_Y,    KC_ESC,
    //|--------+--------+--------+--------+--------+--------|     |SEMIMAK|      |--------+--------+--------+--------+--------+--------|
       HOME_CAP, KC_S,   KC_R,     KC_N,    KC_T,    KC_K,       /*-------*/       KC_C,    KC_D,    KC_E,    KC_A,   KC_I,    KC_ENT,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       P_FUN,    KC_X,   KC_QUOT,  KC_B,    KC_M,    KC_J,                         KC_P,    KC_G,    KC_COMM, KC_DOT, KC_SLSH, XXXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           LA_EXTEND, KC_BSPC, LA_SYM,   KC_LSFT, KC_SPC,  QK_AREP
                                        //`--------------------------'  `--------------------------'
    ),

    [_QWERTY] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        /*------*/       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_ESC,
    //|--------+--------+--------+--------+--------+--------|      |QWERTY|      |--------+--------+--------+--------+--------+--------|
       HOME_CAP, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        /*------*/       KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, KC_ENT,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       P_FUN,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_LSFT, KC_BSPC,LA_SYM,     LA_EXTEND,KC_SPC,  QK_AREP
                                        //`--------------------------'  `--------------------------'
    ),

    [_GAME] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXXX,  KC_G,   KC_Q,    KC_W,    KC_E,    KC_R,        /*------*/      XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,
    //|--------+--------+--------+--------+--------+--------|      |Gaming|      |--------+--------+--------+--------+--------+--------|
       XXXXXXXX, KC_LSFT, KC_S,    KC_A,    KC_D,    KC_F,        /*------*/      XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXXX,XXXXXXXX, KC_Z,    KC_X,    KC_C,   XXXXXXXX,                     XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,D_SEMIMAK,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXXX, KC_SPC, XXXXXXXX,   XXXXXXXX,XXXXXXXX,XXXXXXXX
                                        //`--------------------------'  `--------------------------'
    ),

    /* Tri Layer */
    [_EXTEND] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       ________,________,________,________,________,________,                     ________,________,________,________,________,________,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        MED_ON,  OS_GUI,  OS_ALT,  OS_SFT,  OS_CTL,  MS_ON,                       ________,KC_LEFT, KC_DOWN,  KC_UP,  KC_RIGHT,________,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       ________, UNDO,    CUT,     COPY,    PASTE,   REDO,                        ________,________,________,________,________,________,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           ________,________,________,   ________,________,________
                                        //`--------------------------'  `--------------------------'
    ),
    [_SYM] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
    //,________,KC_9,    KC_5,    KC_1,    KC_3,    KC_7,                         KC_6,    KC_2,    KC_0,    KC_4,    KC_8,    ________,
       ________,KC_TILD, KC_AT,   KC_LBRC, KC_LCBR, KC_BSLS,                      KC_CIRC, KC_RCBR, KC_RBRC, KC_PERC, KC_GRV,  ________,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       ________,OS_GUI,  OS_ALT,  OS_SFT,  OS_CTL,  KC_COLN,                      KC_SCLN, KC_UNDS, KC_EQL,  KC_MINS, KC_ASTR, ________,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       ________,KC_EXLM, KC_DQT,  KC_DLR,  KC_HASH, KC_PIPE,                      KC_AMPR, KC_PLUS, KC_LT,   KC_GT,   KC_QUES, ________,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           ________,________,________,   ________,KC_LPRN, KC_RPRN
                                        //`--------------------------'  `--------------------------'
    ),
    /* Extend Stack */
    [_MOUSE] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       ________,________,________,________,________,________,                       REDO,  KC_PASTE, KC_COPY, KC_CUT,  KC_UNDO, KC_ACL0,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       MED_ON,  OS_GUI,  OS_ALT,  OS_SFT,  OS_CTL,  MS_OFF,                       ________,KC_MS_L,  KC_MS_D, KC_MS_U, KC_MS_R, KC_ACL1,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       ________,________,________,________,________,________,                     ________,KC_WH_L,  KC_WH_D, KC_WH_U, KC_WH_R, KC_ACL2,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           ________,________,________,   ________,________,________
                                        //`--------------------------'  `--------------------------'
    ),
    [_MEDIA] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       ________,________,________,________,________,________,                     ________,________,________,________,________,________,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       MED_OFF, OS_GUI,  OS_ALT,  OS_SFT,  OS_CTL,  MS_ON,                         KC_MPLY,KC_MRWD, VOL_DOWN, VOL_UP, KC_MFFD, ________,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       ________,________,________,________,________,________,                     ________,________,KC_BRID,  KC_BRIU,________,________,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           ________,________,________,   ________,________,________
                                        //`--------------------------'  `--------------------------'
    ),
    [_FUN] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      D_SEMIMAK, KC_F9,   KC_F5,   KC_F1,   KC_F3,   KC_F7,                        KC_F6,   KC_F2,   KC_F10,  KC_F4,   KC_F8,  CL_EEP,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       D_QWERTY, OS_GUI,  OS_ALT,  OS_SFT,  OS_CTL,  KC_F11,                       KC_F12,  DM_PLY1, DM_PLY2,XXXXXXXX,XXXXXXXX,QK_MAKE,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       D_GAMING,  UNDO,    CUT,     COPY,   PASTE,    REDO,                        DM_RSTP, DM_REC1, DM_REC2,XXXXXXXX,XXXXXXXX,QK_BOOT,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           ________,________,________,   ________,________,________
                                        //`--------------------------'  `--------------------------'
    ),
};

/* Thumb Cluster Overrides */
const key_override_t space_key_override =       ko_make_basic(MOD_MASK_SHIFT, KC_SPC,  KC_TAB);

/* Number Row Overrides */
const key_override_t tilde_override =           ko_make_basic(MOD_MASK_SHIFT, KC_TILD, KC_9);
const key_override_t at_override =              ko_make_basic(MOD_MASK_SHIFT, KC_AT,   KC_5);
const key_override_t open_bracket_override =    ko_make_basic(MOD_MASK_SHIFT, KC_LBRC, KC_1);
const key_override_t open_brace_override =      ko_make_basic(MOD_MASK_SHIFT, KC_LCBR, KC_3);
const key_override_t backslash_override =       ko_make_basic(MOD_MASK_SHIFT, KC_BSLS, KC_7);

const key_override_t caret_override =           ko_make_basic(MOD_MASK_SHIFT, KC_CIRC, KC_6);
const key_override_t close_brace_override =     ko_make_basic(MOD_MASK_SHIFT, KC_RCBR, KC_2);
const key_override_t close_bracket_override =   ko_make_basic(MOD_MASK_SHIFT, KC_RBRC, KC_0);
const key_override_t percent_override =         ko_make_basic(MOD_MASK_SHIFT, KC_PERC, KC_4);
const key_override_t grave_override =           ko_make_basic(MOD_MASK_SHIFT, KC_GRV,  KC_8);

const key_override_t **key_overrides = (const key_override_t *[]){
    &space_key_override,

    &tilde_override,
    &at_override,
    &open_bracket_override,
    &open_brace_override,
    &backslash_override,

    &caret_override,
    &close_brace_override,
    &close_bracket_override,
    &percent_override,
    &grave_override,
    NULL // Null terminate the array of overrides!
};

/* Combos
const uint16_t PROGMEM delete_combo[] = {KC_SPC, KC_BSPC, COMBO_END};
combo_t key_combos[] = {
    COMBO(delete_combo, KC_DEL),
};
*/

/* Callum Oneshots */
bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_EXTEND:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_EXTEND:
    case KC_LSFT:
    case OS_GUI:
    case OS_ALT:
    case OS_SFT:
    case OS_CTL:
        return true;
    default:
        return false;
    }
}

oneshot_state os_sft_state = os_up_unqueued;
oneshot_state os_ctl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_gui_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    /* Callum Oneshots */
    update_oneshot(
            &os_sft_state, KC_LSFT, OS_SFT,
            keycode, record
            );
    update_oneshot(
            &os_ctl_state, KC_LCTL, OS_CTL,
            keycode, record
            );
    update_oneshot(
            &os_alt_state, KC_LALT, OS_ALT,
            keycode, record
            );
    update_oneshot(
            &os_gui_state, KC_LGUI, OS_GUI,
            keycode, record
            );
    switch (keycode) {
        /* Tri Layer */
        case LA_EXTEND:
            if (record->event.pressed) {
                layer_on(_EXTEND);
                //update_tri_layer(_SYM, _EXTEND, _NUM);
            }
            else {
                layer_off(_EXTEND);
                //update_tri_layer(_SYM, _EXTEND, _NUM);
            }
            return false;
        case LA_SYM:
            if (record->event.pressed) {
                layer_on(_SYM);
                //update_tri_layer(_SYM, _EXTEND, _NUM);
            }
            else {
                layer_off(_SYM);
                //update_tri_layer(_SYM, _EXTEND, _NUM);
            }
            return false;
        }
    return true;
}

/* Alt Repeat Key */
/*
uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
    bool shifted =    (mods & MOD_MASK_SHIFT);  // Was SFT held?
    switch (keycode) {

    }
    return KC_TRNS;
}
*/
