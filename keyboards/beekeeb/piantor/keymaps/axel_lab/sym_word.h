// sym_word.h
#pragma once

#include QMK_KEYBOARD_H

/** @brief Gets whether currently active. */
bool is_sym_word_on(void);

/** @brief Activates Sym Word. */
void sym_word_on(void);

/** @brief Deactivates Sym Word. */
void sym_word_off(void);

/** @brief Toggles Sym Word. */
void sym_word_toggle(void);

// Hook helpers
void process_sym_word_activation(const keyrecord_t *record);
bool process_sym_word(uint16_t keycode, const keyrecord_t *record);
