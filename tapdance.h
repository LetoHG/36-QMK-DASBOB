#pragma once

#include <sys/types.h>
#include <stddef.h>
#include QMK_KEYBOARD_H

typedef struct {
    bool    is_press_action;
    uint8_t step;
} tap;

enum { SINGLE_TAP = 1, SINGLE_HOLD, DOUBLE_TAP, DOUBLE_HOLD, DOUBLE_SINGLE_TAP, MORE_TAPS };

static tap dance_state = {.is_press_action = true, .step = 0};

#define ADD_ACTION_TAP_DANCE(Name) ACTION_TAP_DANCE_FN_ADVANCED(on_##Name, Name##_finished, Name##_reset)

#define DEFINE_TAP_DANCE_SIMPLE(Name, TapCode, HoldCode) DEFINE_TAP_DANCE(Name, TapCode, HoldCode, TapCode, TapCode)
#define DEFINE_TAP_DANCE(Name, TapCode, HoldCode, DoubleTapCode, DoubleSingleTapCode)      \
    void    on_##Name(tap_dance_state_t *state, void *user_data);                          \
    uint8_t Name##_dance_step(tap_dance_state_t *state);                                   \
    void    Name##_finished(tap_dance_state_t *state, void *user_data);                    \
    void    Name##_reset(tap_dance_state_t *state, void *user_data);                       \
    DEFINE_TAP_DANCE_ON(Name, TapCode, HoldCode, DoubleTapCode, DoubleSingleTapCode)       \
    DEFINE_TAP_DANCE_STEP(Name, TapCode, HoldCode, DoubleTapCode, DoubleSingleTapCode)     \
    DEFINE_TAP_DANCE_FINISHED(Name, TapCode, HoldCode, DoubleTapCode, DoubleSingleTapCode) \
    DEFINE_TAP_DANCE_RESET(Name, TapCode, HoldCode, DoubleTapCode, DoubleSingleTapCode)

#define DEFINE_TAP_DANCE_ON(Name, TapCode, HoldCode, DoubleTapCode, DoubleSingleTapCode) \
    void on_##Name(tap_dance_state_t *state, void *user_data) {                          \
        if (state->count == 3) {                                                         \
            tap_code16(TapCode);                                                         \
            tap_code16(TapCode);                                                         \
            tap_code16(TapCode);                                                         \
        }                                                                                \
        if (state->count > 3) {                                                          \
            tap_code16(TapCode);                                                         \
        }                                                                                \
    }

#define DEFINE_TAP_DANCE_STEP(Name, TapCode, HoldCode, DoubleTapCode, DoubleSingleTapCode) \
    uint8_t Name##_dance_step(tap_dance_state_t *state) {                                  \
        if (state->count == 1) {                                                           \
            if (state->interrupted || !state->pressed)                                     \
                return SINGLE_TAP;                                                         \
            else                                                                           \
                return SINGLE_HOLD;                                                        \
        } else if (state->count == 2) {                                                    \
            if (state->interrupted)                                                        \
                return DOUBLE_SINGLE_TAP;                                                  \
            else if (state->pressed)                                                       \
                return DOUBLE_HOLD;                                                        \
            else                                                                           \
                return DOUBLE_TAP;                                                         \
        }                                                                                  \
        return MORE_TAPS;                                                                  \
    }

#define DEFINE_TAP_DANCE_FINISHED(Name, TapCode, HoldCode, DoubleTapCode, DoubleSingleTapCode) \
    void Name##_finished(tap_dance_state_t *state, void *user_data) {                          \
        dance_state.step = Name##_dance_step(state);                                           \
        switch (dance_state.step) {                                                            \
            case SINGLE_TAP:                                                                   \
                register_code16(TapCode);                                                      \
                break;                                                                         \
            case SINGLE_HOLD:                                                                  \
                register_code16(HoldCode);                                                     \
                break;                                                                         \
            case DOUBLE_TAP:                                                                   \
                register_code16(DoubleTapCode);                                                \
                register_code16(DoubleTapCode);                                                \
                break;                                                                         \
            case DOUBLE_SINGLE_TAP:                                                            \
                tap_code16(DoubleSingleTapCode);                                               \
                register_code16(DoubleSingleTapCode);                                          \
                break;                                                                         \
        }                                                                                      \
    }

#define DEFINE_TAP_DANCE_RESET(Name, TapCode, HoldCode, DoubleTapCode, DoubleSingleTapCode) \
    void Name##_reset(tap_dance_state_t *state, void *user_data) {                          \
        wait_ms(10);                                                                        \
        switch (dance_state.step) {                                                         \
            case SINGLE_TAP:                                                                \
                unregister_code16(TapCode);                                                 \
                break;                                                                      \
            case SINGLE_HOLD:                                                               \
                unregister_code16(HoldCode);                                                \
                break;                                                                      \
            case DOUBLE_TAP:                                                                \
                unregister_code16(DoubleTapCode);                                           \
                break;                                                                      \
            case DOUBLE_SINGLE_TAP:                                                         \
                unregister_code16(DoubleSingleTapCode);                                     \
                break;                                                                      \
        }                                                                                   \
        dance_state.step = 0;                                                               \
    }

#define ADD_ACTION_TAP_DANCE_CMD(Name) ACTION_TAP_DANCE_FN_ADVANCED(on_##Name, Name##_finished, Name##_reset)

#define DEFINE_TAP_DANCE_CMD(Name, TapCode, HoldCmd, DoubleHoldCmd)                        \
    void    on_##Name(tap_dance_state_t *state, void *user_data);                          \
    uint8_t Name##_dance_step(tap_dance_state_t *state);                                   \
    void    Name##_finished(tap_dance_state_t *state, void *user_data);                    \
    void    Name##_reset(tap_dance_state_t *state, void *user_data);                       \
    DEFINE_TAP_DANCE_ON(Name, TapCode, HoldCmd, TapCode, TapCode)                          \
    DEFINE_TAP_DANCE_STEP(Name, TapCode, HoldCmd, TapCode, TapCode)                        \
    DEFINE_TAP_DANCE_FINISHED_CMD(Name, TapCode, HoldCmd, DoubleHoldCmd, TapCode, TapCode) \
    DEFINE_TAP_DANCE_RESET_CMD(Name, TapCode, HoldCmd, DoubleHoldCmd, TapCode, TapCode)

#define DEFINE_TAP_DANCE_FINISHED_CMD(Name, TapCode, HoldCmd, DoubleHoldCmd, DoubleTapCode, DoubleSingleTapCode) \
    void Name##_finished(tap_dance_state_t *state, void *user_data) {                                            \
        dance_state.step = Name##_dance_step(state);                                                             \
        switch (dance_state.step) {                                                                              \
            case SINGLE_TAP:                                                                                     \
                register_code16(TapCode);                                                                        \
                break;                                                                                           \
            case SINGLE_HOLD:                                                                                    \
                HoldCmd;                                                                                         \
                break;                                                                                           \
            case DOUBLE_HOLD:                                                                                    \
                DoubleHoldCmd;                                                                                   \
                break;                                                                                           \
            case DOUBLE_TAP:                                                                                     \
                register_code16(DoubleTapCode);                                                                  \
                register_code16(DoubleTapCode);                                                                  \
                break;                                                                                           \
            case DOUBLE_SINGLE_TAP:                                                                              \
                tap_code16(DoubleSingleTapCode);                                                                 \
                register_code16(DoubleSingleTapCode);                                                            \
                break;                                                                                           \
        }                                                                                                        \
    }

#define DEFINE_TAP_DANCE_RESET_CMD(Name, TapCode, HoldCode, DoubleHoldCmd, DoubleTapCode, DoubleSingleTapCode) \
    void Name##_reset(tap_dance_state_t *state, void *user_data) {                                             \
        wait_ms(10);                                                                                           \
        switch (dance_state.step) {                                                                            \
            case SINGLE_TAP:                                                                                   \
                unregister_code16(TapCode);                                                                    \
                break;                                                                                         \
            case SINGLE_HOLD:                                                                                  \
                break;                                                                                         \
            case DOUBLE_TAP:                                                                                   \
                unregister_code16(DoubleTapCode);                                                              \
                break;                                                                                         \
            case DOUBLE_HOLD:                                                                                  \
                break;                                                                                         \
            case DOUBLE_SINGLE_TAP:                                                                            \
                unregister_code16(DoubleSingleTapCode);                                                        \
                break;                                                                                         \
        }                                                                                                      \
        dance_state.step = 0;                                                                                  \
    }

enum tap_dance_codes {
    DOT_EXLM,
    EXLM_QUES,
    COMMA_MINUS,
    SLASH_UNDS,
    TAB_WINTAB,
    LEFT__CTRL_LEFT,
    RIGHT__CTRL_RIGHT,
    SL_BKSL,
    DQUOTE_QUOTE,
    HASH_AT,
    DLR_PERC,
    HEX_NUMPAD_1_A,
    HEX_NUMPAD_2_B,
    HEX_NUMPAD_3_C,
    HEX_NUMPAD_4_D,
    HEX_NUMPAD_5_E,
    HEX_NUMPAD_6_F,
    HEX_NUMPAD_0_X,
    DEC_DOT_COMMA,
    CIRC_QUIT_VIM,
    ESC_FORCE_QUIT_VIM,
};
