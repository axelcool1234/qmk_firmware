#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define AFTERBURNER 0
#define NUMPAD      1
#define MEDIA_OSX   2
#define P9K_SYM     3
#define MACRO_OSX   4

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Afterburner
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Esc    |  7   |  8   |  9   |  0   |  5   |M-Bksp|           |M-Del |  6   |  1   |  2   |  3   |  4   |  \     |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |  J   |  B   |  G   |  V   |  X   | Alt  |           | Alt  |  '   |  W   |  O   |  U   |  ,   | Bksp   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Q      |  H   |  N   |  S   |  T   |  M   |------|           |------|Magic |SkpMgc|  A   |  E   |  I   |  -     |
 * |--------+------+------+------+------+------| Cmd  |           | Cmd  |------+------+------+------+------+--------|
 * | LShift |  Y   |  P   |  F   |  D   |  K   |      |           |      |  Z   |  C   |  /   |  ;   |  .   | RShift |
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
[AFTERBURNER] = LAYOUT_ergodox(
       // left hand
       KC_ESC,        KC_7,    KC_8,    KC_9,    KC_0,    KC_5,    LALT(KC_BSPC),
       KC_TAB,        KC_J,    KC_B,    KC_G,    KC_V,    KC_X,    KC_LALT,
       KC_Q,          KC_H,    KC_N,    KC_S,    KC_T,    KC_M,
       KC_LSFT,       KC_Y,    KC_P,    KC_F,    KC_D,    KC_K,    KC_LGUI,
       MO(MACRO_OSX), KC_BTN1, KC_BTN2, KC_DOWN, KC_UP,
                                        KC_LCTL, MO(MEDIA_OSX),
                                                 MO(NUMPAD),
                                  KC_R, KC_L,    MO(P9K_SYM),
       // right hand
  LALT(KC_DEL), KC_6,    KC_1,    KC_2,    KC_3,    KC_4,    KC_BSLS,
       KC_RALT, KC_QUOT, KC_W,    KC_O,    KC_U,    KC_COMM, KC_BSPC,
                QK_AREP, QK_SREP, KC_A,    KC_E,    KC_I,    KC_MINS,
       KC_RGUI, KC_Z,    KC_C,    KC_SLSH, KC_SCLN, KC_DOT,  KC_RSFT,
                         KC_LEFT, KC_RIGHT,KC_LBRC, KC_RBRC, KC_EQL,
       MO(MEDIA_OSX), KC_RCTL,
       MO(NUMPAD),
       MO(P9K_SYM), KC_ENT, KC_SPC
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

/* Paracetamak Symbols
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   <  |   >  |   {  |   }  |   \  |      |           |      |      |   ?  |   +  |   :  |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  =     |   !  |   @  |   #  |   $  |   %  |------|           |------|      |      |   *  |   (  |   )  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   `  |   ~  |   _  |   "  |   |  |      |           |      |   ^  |   &  |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 | Del  | Bksp |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[P9K_SYM] = LAYOUT_ergodox(
       // left hand
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_LABK, KC_RABK, KC_LCBR, KC_RCBR, KC_BSLS, KC_TRNS,
       KC_EQL,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,
       KC_TRNS, KC_GRV,  KC_TILD, KC_UNDS, KC_DQUO, KC_PIPE, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                        KC_TRNS, KC_TRNS,
                                                 KC_TRNS,
                               KC_DEL,  KC_BSPC, KC_TRNS,
       // right hand
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_QUES, KC_PLUS, KC_COLN, KC_TRNS, KC_TRNS,
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

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
};
