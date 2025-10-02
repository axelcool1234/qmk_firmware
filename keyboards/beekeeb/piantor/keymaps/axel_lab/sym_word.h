// sym_word.h
#pragma once

#include QMK_KEYBOARD_H

// Query state
bool sym_word_enabled(void);

// Control functions
void enable_sym_word(void);
void disable_sym_word(void);

// Hook helpers
void process_sym_word_activation(const keyrecord_t *record);
bool process_sym_word(uint16_t keycode, const keyrecord_t *record);
