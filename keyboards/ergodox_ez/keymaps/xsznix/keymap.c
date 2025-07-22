#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define RSTHD_OSX   0
#define PARACETAMAK 1
#define QWERTY      2
#define NUMPAD      3
#define MEDIA_OSX   4
#define SPECIAL     5
#define P9K_SYM     6
#define MACRO_OSX   7

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* RSTHD for OS X
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   `    |   7  |   8  |   9  |   0  |   5  | LCtl |           | RCtl |   6  |   1  |   2  |   3  |   4  |   \    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   J  |   C  |   Y  |   F  |   K  | LAlt |           | RAlt |   Z  |   L  |   ,  |   U  |   Q  |   =    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Esc    |   R  |   S  |   T  |   H  |   D  |------|           |------|   M  |   N  |   A  |   I  |   O  |   '    |
 * |--------+------+------+------+------+------| LGui |           | RGui |------+------+------+------+------+--------|
 * | LShift |   /  |   V  |   G  |   P  |   B  |      |           |      |   X  |   W  |   .  |   ;  |   -  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | Macro|  M1  |  M2  | Down |  Up  |                                       | Left | Right| MSpc |QWERTY| ^Spc |
 *   `----------------------------------'                                       `----------------------------------'
 *                                       ,--------------.       ,--------------.
 *                                       | Numpad| Media|       | Media| Numpad|
 *                                ,------|-------|------|       |------+-------+-------.
 *                                |      |       | P9K  |       |QWERTY|       |       |
 *                                |  E   | Bksp  |------|       |------| Enter | Space |
 *                                |      |       | Speci|       | Speci|       |       |
 *                                `---------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[RSTHD_OSX] = LAYOUT_ergodox(
        // left hand
        KC_GRV,  KC_7,    KC_8, KC_9, KC_0, KC_5, KC_LCTL,
        KC_TAB,  KC_J,    KC_C, KC_Y, KC_F, KC_K, KC_LALT,
        KC_ESC,  KC_R,    KC_S,  KC_T, KC_H, KC_D,
        KC_LSFT, KC_SLSH, KC_V,  KC_G, KC_P, KC_B, KC_LGUI,
        MO(MACRO_OSX), KC_BTN1, KC_BTN2, KC_DOWN, KC_UP,
                                        MO(NUMPAD), MO(MEDIA_OSX),
                                                    TG(PARACETAMAK),
                                    KC_E,  KC_BSPC, MO(SPECIAL),
        // right hand
        KC_RCTL, KC_6, KC_1, KC_2,    KC_3,      KC_4,    KC_BSLS,
        KC_RALT, KC_Z, KC_L, KC_COMM, KC_U,      KC_Q,    KC_EQUAL,
                 KC_M, KC_N, KC_A,    KC_I,      KC_O,    KC_QUOTE,
        KC_RGUI, KC_X, KC_W, KC_DOT,  KC_SCLN, KC_MINS, KC_RSFT,
                       KC_LEFT, KC_RIGHT, LALT(KC_SPC), TG(QWERTY), LCTL(KC_SPC),
        MO(MEDIA_OSX),   MO(NUMPAD),
        TG(QWERTY),
        MO(SPECIAL), KC_ENT, KC_SPC
    ),

/* Paracetamak
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Esc    |  7   |  8   |  9   |  0   |  5   | CapW |           | CapW |  6   |  1   |  2   |  3   |  4   |  \     |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |  W   |  G   |  H   |  V   |  K   | Alt  |           | Alt  |  Z   |  '   |  U   |  O   |  J   |  /     |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Bksp   |  Y   |  S   |  N   |  T   |  M   |------|           |------|Magic |SkpMgc|  E   |  A   |  I   |  ,     |
 * |--------+------+------+------+------+------| Cmd  |           | Cmd  |------+------+------+------+------+--------|
 * | LShift |  P   |  F   |  B   |  D   |  Q   |      |           |      |  X   |  C   |  -   |  ;   |  .   | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | Macro|  M1  |  M2  | Down |  Up  |                                       | Left | Right|  [   |  ]   |  =   |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Ctrl | Num  |       |Media | Ctrl |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | P9K  |       |QWERTY|      |      |
 *                                 |  R   |  L   |------|       |------|Enter | Spc  |
 *                                 |      |      | Sym  |       | Sym  |      |      |
 *                                 `--------------------'       `--------------------'
 */
[PARACETAMAK] = LAYOUT_ergodox(
       // left hand
       KC_ESC,        KC_7,    KC_8,    KC_9,    KC_0,    KC_5,    CW_TOGG,
       KC_TAB,        KC_W,    KC_G,    KC_H,    KC_V,    KC_K,    KC_LALT,
       KC_BSPC,       KC_Y,    KC_S,    KC_N,    KC_T,    KC_M,
       KC_LSFT,       KC_P,    KC_F,    KC_B,    KC_D,    KC_Q,    KC_LGUI,
       MO(MACRO_OSX), KC_BTN1, KC_BTN2, KC_DOWN, KC_UP,
                                        KC_LCTL, MO(NUMPAD),
                                                 TG(PARACETAMAK),
                                  KC_R, KC_L,    MO(P9K_SYM),
       // right hand
       CW_TOGG,  KC_6,   KC_1,    KC_2,    KC_3,    KC_4,   KC_BSLS,
       KC_RALT, KC_Z,    KC_QUOT, KC_U,    KC_O,    KC_J,    KC_SLSH,
                QK_AREP, QK_SREP, KC_E,    KC_A,    KC_I,    KC_COMM,
       KC_RGUI, KC_X,    KC_C,    KC_MINS, KC_SCLN, KC_DOT,  KC_RSFT,
                         KC_LEFT, KC_RIGHT,KC_LBRC, KC_RBRC, KC_EQL,
       MO(MEDIA_OSX), KC_RCTL,
       TG(QWERTY),
       MO(P9K_SYM), KC_ENT, KC_SPC
    ),

/* QWERTY
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  |    =   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |   I  |   O  |   P  |    -   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |    '   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |   \  |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 | SPC  |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[QWERTY] = LAYOUT_ergodox(
       // left hand
       KC_TRNS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5, KC_TRNS,
       KC_TRNS, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, KC_TRNS,
       KC_TRNS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
       KC_TRNS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                        KC_TRNS, KC_TRNS,
                                                 KC_TRNS,
                                KC_SPC, KC_TRNS, KC_TRNS,
       // right hand
       KC_TRNS, KC_6, KC_7,    KC_8,   KC_9,    KC_0,     KC_EQUAL,
       KC_TRNS, KC_Y, KC_U,    KC_I,   KC_O,    KC_P,     KC_MINUS,
                KC_H, KC_J,    KC_K,   KC_L,    KC_SCLN,  KC_QUOT,
       KC_TRNS, KC_N, KC_M,    KC_COMM,KC_DOT,  KC_SLSH,  KC_TRNS,
                      KC_TRNS, KC_TRNS, KC_BSLS,KC_TRNS,  KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
    ),

/* Function and Numpad
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        | F13  | F14  | F15  | F16  |      |      |           |      |      |   7  |   8  |   9  |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |  F9  | F10  | F11  | F12  |      |      |           |      |      |   4  |   5  |   6  |   +  |    *   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  F5  |  F6  |  F7  |  F8  |      |------|           |------|      |   1  |   2  |   3  |   -  |    /   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  F1  |  F2  |  F3  |  F4  |      |      |           |      |      |   0  |  LF  |   .  |   =  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      | F17  | F18  | F19  | F20  |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------| Ent  |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[NUMPAD] = LAYOUT_ergodox(
       // left hand
       KC_TRNS, KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_TRNS, KC_TRNS,
       KC_TRNS, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_TRNS,
       KC_TRNS, KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_TRNS,
       KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_TRNS, KC_TRNS,
       KC_TRNS, KC_F17,  KC_F18,  KC_F19,  KC_F20,
                                        KC_TRNS, KC_TRNS,
                                                 KC_TRNS,
                               KC_TRNS, KC_TRNS, KC_TRNS,
       // right hand
       KC_TRNS, KC_TRNS, KC_KP_7, KC_KP_8, KC_KP_9,   KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_KP_4, KC_KP_5, KC_KP_6,   KC_KP_PLUS,  KC_KP_ASTERISK,
                KC_TRNS, KC_KP_1, KC_KP_2, KC_KP_3,   KC_KP_MINUS, KC_KP_SLASH,
       KC_TRNS, KC_TRNS, KC_KP_0, KC_TRNS, KC_KP_DOT, KC_KP_EQUAL, KC_TRNS,
                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_KP_ENTER, KC_TRNS
    ),

/* Media for OS X
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      | **6  | **7  | **8  | **9  |  **0   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      | INS  | HOM  | PGUP |C-S-tb|      |           |      |      | **1  | **2  | **3  | **4  |  **5   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      | DEL  | END  | PGDN |C-tab |------|           |------|      |  *6  |  *7  |  *8  |  *9  |   *0   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  ^z  |  ^x  |  ^c  |  ^v  |      |      |           |      |      |  *1  |  *2  |  *3  |  *4  |   *5   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      | Mute | Vol- | Vol+ |                                       | Back |Pause | Fwd  |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[MEDIA_OSX] = LAYOUT_ergodox(
       // left hand
       KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,
       KC_TRNS, KC_TRNS,    KC_INS,     KC_HOME,    KC_PGUP,    LCTL(LSFT(KC_TAB)), KC_TRNS,
       KC_TRNS, KC_TRNS,    KC_DEL,     KC_END,     KC_PGDN,    LCTL(KC_TAB),
       KC_TRNS, LGUI(KC_Z), LGUI(KC_X), LGUI(KC_C), LGUI(KC_V), KC_TRNS,            KC_TRNS,
       KC_TRNS, KC_TRNS,    KC_MUTE,    KC_VOLD,    KC_VOLU,
                                        KC_TRNS, KC_TRNS,
                                                 KC_TRNS,
                               KC_TRNS, KC_TRNS, KC_TRNS,
       // right hand
       KC_TRNS, KC_TRNS, LCTL(LALT(LSFT(KC_6))), LCTL(LALT(LSFT(KC_7))), LCTL(LALT(LSFT(KC_8))), LCTL(LALT(LSFT(KC_9))), LCTL(LALT(LSFT(KC_0))),
       KC_TRNS, KC_TRNS, LCTL(LALT(LSFT(KC_1))), LCTL(LALT(LSFT(KC_2))), LCTL(LALT(LSFT(KC_3))), LCTL(LALT(LSFT(KC_4))), LCTL(LALT(LSFT(KC_5))),
                KC_TRNS, LCTL(LALT(KC_6)),       LCTL(LALT(KC_7)),       LCTL(LALT(KC_8)),       LCTL(LALT(KC_9)),       LCTL(LALT(KC_0)),
       KC_TRNS, KC_TRNS, LCTL(LALT(KC_1)),       LCTL(LALT(KC_2)),       LCTL(LALT(KC_3)),       LCTL(LALT(KC_4)),       LCTL(LALT(KC_5)),
                         KC_MPRV,                KC_MPLY,                KC_MNXT,                KC_TRNS,                KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
    ),

/* Special
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   <  |   >  |   [  |   ]  |   \  |      |           |      |M-del |   :  |      |   {  |   }  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   !  |   @  |   #  |   $  |   %  |------|           |------|   ^  |   &  |   *  |   (  |   )  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |   ~  |   _  |   "  |   |  |      |           |      |   ?  |   +  |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[SPECIAL] = LAYOUT_ergodox(
       // left hand
       KC_TRNS, KC_TRNS,    KC_TRNS,   KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS,
       KC_TRNS, S(KC_COMM), S(KC_DOT), KC_LBRC, KC_RBRC,    KC_BSLS, KC_TRNS,
       KC_TRNS, KC_EXLM,    KC_AT,     KC_HASH,  KC_DLR,    KC_PERC,
       KC_TRNS, KC_TRNS,    KC_TILD,   KC_UNDS, S(KC_QUOT), KC_PIPE, KC_TRNS,
       KC_TRNS, KC_TRNS,    KC_TRNS,   KC_TRNS, KC_TRNS,
                                        KC_TRNS, KC_TRNS,
                                                 KC_TRNS,
                               KC_DEL,  KC_TRNS, KC_TRNS,
       // right hand
       KC_TRNS, KC_TRNS,       KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, LALT(KC_BSPC), KC_COLN,     KC_TRNS, KC_LCBR, KC_RCBR, KC_TRNS,
                KC_CIRC,       KC_AMPR,     KC_ASTR, KC_LPRN, KC_RPRN, KC_TRNS,
       KC_TRNS, S(KC_SLSH),    S(KC_EQUAL), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                               KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
    ),

/* Paracetamak Symbols
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   <  |   >  |   {  |   }  |   \  |      |           |      |   ?  |      |   =  |   :  |   +  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   !  |   @  |   #  |   $  |   %  |------|           |------|      |      |   *  |   (  |   )  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   `  |   ~  |   _  |   "  |   |  |      |           |      |   ^  |   &  |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[P9K_SYM] = LAYOUT_ergodox(
       // left hand
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_LABK, KC_RABK, KC_LCBR, KC_RCBR, KC_BSLS, KC_TRNS,
       KC_TRNS, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,
       KC_TRNS, KC_GRV,  KC_TILD, KC_UNDS, KC_DQUO, KC_PIPE, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                        KC_TRNS, KC_TRNS,
                                                 KC_TRNS,
                               KC_DEL,  KC_TRNS, KC_TRNS,
       // right hand
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_QUES, KC_TRNS, KC_EQL,  KC_COLN, KC_PLUS, KC_TRNS,
                KC_TRNS, KC_TRNS, KC_ASTR, KC_LPRN, KC_RPRN, KC_TRNS,
       KC_TRNS, KC_CIRC, KC_AMPR, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
    ),

/* Macros for OSX
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | M <- | M -> | GM<- | GM-> |      |------|           |------|      | BOOT |Restart|     |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | X <- | X -> | C up | C dn |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      | CSTab| CTab | G <- | G -> |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[MACRO_OSX] = LAYOUT_ergodox(
       // left hand
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, LALT(LGUI(KC_LEFT)), LALT(LGUI(KC_RIGHT)), LCTL(KC_UP), LCTL(KC_DOWN), KC_TRNS,
       KC_TRNS, LCTL(LSFT(KC_TAB)), LCTL(KC_TAB), LCTL(LALT(KC_LEFT)), LCTL(LALT(KC_RIGHT)), KC_TRNS, KC_TRNS,
       KC_TRNS, KC_BTN3, LALT(KC_TAB), LGUI(KC_LEFT), LGUI(KC_RIGHT),
                                        KC_TRNS, KC_TRNS,
                                                 KC_TRNS,
                    LCTL(LALT(KC_SPC)), KC_TRNS, KC_TRNS,
       // right hand
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                KC_TRNS, QK_BOOT, QK_RBT,  KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
    ),

/* Template
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// [NAME] = LAYOUT_ergodox(
//        // left hand
//        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
//        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
//        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
//        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
//        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
//                                         KC_TRNS, KC_TRNS,
//                                                  KC_TRNS,
//                                KC_TRNS, KC_TRNS, KC_TRNS,
//        // right hand
//        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
//        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
//                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
//        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
//                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
//        KC_TRNS, KC_TRNS,
//        KC_TRNS,
//        KC_TRNS, KC_TRNS, KC_TRNS
//     ),
};

const uint16_t PROGMEM fn_actions[] = {
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
    case KC_H: return KC_N;
    case KC_J: return KC_I;
    case KC_U: return KC_E;
    case KC_Y: return KC_P;
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
    case KC_F: return KC_G;
    case KC_G: return KC_F;
    case KC_H: return KC_N;
    case KC_J: return KC_I;
    case KC_K: return KC_T;
    case KC_L: return KC_R;
    case KC_M: return KC_T;
    case KC_O: return KC_A;
    case KC_P: return KC_Y;
    case KC_Q: return KC_E;
    case KC_R: return KC_L;
    case KC_U: return KC_E;
    case KC_V: return KC_D;
    case KC_W: return KC_Y;
    case KC_Y: return KC_W;
    case KC_COMM: return KC_I;
    case KC_DOT: return KC_I;
    case KC_SLSH: return KC_I;
    default: return keycode;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    if (layer_state & (1 << PARACETAMAK)) {
      ergodox_right_led_1_on();
    }

    if (layer_state & (1 << QWERTY)) {
      ergodox_right_led_2_on();
    }

    switch (layer) {
      case RSTHD_OSX:
      case PARACETAMAK:
      case QWERTY:
      break;

      default:
      ergodox_right_led_3_on();
    }
};
