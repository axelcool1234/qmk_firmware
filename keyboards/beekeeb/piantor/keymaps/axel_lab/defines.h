#pragma once

#include QMK_KEYBOARD_H

///--- Layers ---///
/// The following defines the layers of the keyboard in order. Used in `keymaps`.
/// BASE:   Base layer. Uses Afterburner alt keyboard layout. https://layouts.wiki/layouts/2025/afterburner/
/// SYM:    Symbol (and number) layer.
/// EXTEND: Extend layer. Used for modifiers and arrow key movement.
enum layers {
    _BASE,
    _SYM,
    _EXTEND,
};

enum keycodes {
    SYMWORD = SAFE_RANGE,
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
#define OS_EXTND OSL(_EXTEND)

///--- Combos ---///
/// Defines custom combos (pressing a combination of keys produces a unique output)
/// Macro API: COMBO_DEF(combo name, output, ...keys to press simultaneously)
#define COMBO_LIST \
    COMBO_DEF(LCTRL_COMBO,  OS_LCTL,      KC_L,    KC_ENTER) \
    COMBO_DEF(LGUI_COMBO,   OS_LGUI,      KC_R,    KC_SPACE) \
    COMBO_DEF(LALT_COMBO,   OS_LALT,      SYMWORD, KC_UNDS)
