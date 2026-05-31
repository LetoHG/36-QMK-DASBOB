
#include <sys/types.h>
#include QMK_KEYBOARD_H
#include "tapdance.h"

// extern bool g_suspend_state;
// #define GET_TAP_KC(dual_role_key) dual_role_key & 0xFF
// uint16_t last_keycode = KC_NO;
// uint8_t  last_modifier = 0;

DEFINE_TAP_DANCE_SIMPLE(COMMA_MINUS, KC_COMMA, KC_MINS)
DEFINE_TAP_DANCE_SIMPLE(DOT_EXLM, KC_DOT, KC_EXLM)
DEFINE_TAP_DANCE_SIMPLE(EXLM_QUES, KC_EXLM, KC_QUES)
DEFINE_TAP_DANCE_SIMPLE(SLASH_UNDS, KC_SLASH, KC_UNDS)
DEFINE_TAP_DANCE_SIMPLE(TAB_WINTAB, KC_TAB, LGUI(KC_TAB))
DEFINE_TAP_DANCE_SIMPLE(LEFT__CTRL_LEFT, KC_LEFT, LCTL(KC_LEFT))
DEFINE_TAP_DANCE_SIMPLE(RIGHT__CTRL_RIGHT, KC_RIGHT, LCTL(KC_RIGHT))
DEFINE_TAP_DANCE_SIMPLE(SL_BKSL, KC_SLASH, KC_BSLS)
DEFINE_TAP_DANCE_SIMPLE(DQUOTE_QUOTE, KC_DQUO, KC_QUOT)
DEFINE_TAP_DANCE_SIMPLE(HASH_AT, KC_HASH, KC_AT)
DEFINE_TAP_DANCE_SIMPLE(DLR_PERC, KC_DLR, KC_PERC)

DEFINE_TAP_DANCE_SIMPLE(HEX_NUMPAD_1_A, KC_1, KC_A)
DEFINE_TAP_DANCE_SIMPLE(HEX_NUMPAD_2_B, KC_2, KC_B)
DEFINE_TAP_DANCE_SIMPLE(HEX_NUMPAD_3_C, KC_3, KC_C)
DEFINE_TAP_DANCE_SIMPLE(HEX_NUMPAD_4_D, KC_4, KC_D)
DEFINE_TAP_DANCE_SIMPLE(HEX_NUMPAD_5_E, KC_5, KC_E)
DEFINE_TAP_DANCE_SIMPLE(HEX_NUMPAD_6_F, KC_6, KC_F)
DEFINE_TAP_DANCE_SIMPLE(HEX_NUMPAD_0_X, KC_0, KC_X)
DEFINE_TAP_DANCE_SIMPLE(DEC_DOT_COMMA, KC_DOT, KC_COMMA)

// Tap Dance for (^, :q)  to quit NVim
#define VIM_QUIT_CMD     \
    tap_code16(KC_ESC);  \
    tap_code16(KC_COLN); \
    tap_code16(KC_Q);

#define VIM_WRITE_CMD    \
    tap_code16(KC_ESC);  \
    tap_code16(KC_COLN); \
    tap_code16(KC_W);    \
    tap_code16(KC_ENT);

DEFINE_TAP_DANCE_CMD(CIRC_QUIT_VIM, KC_CIRC, VIM_QUIT_CMD, VIM_WRITE_CMD)

#define VIM_FORCE_QUIT_CMD \
    tap_code16(KC_ESC);    \
    tap_code16(KC_COLN);   \
    tap_code16(KC_Q);      \
    tap_code16(KC_EXLM);   \
    tap_code16(KC_ENT);
DEFINE_TAP_DANCE_CMD(ESC_FORCE_QUIT_VIM, KC_ESC, VIM_FORCE_QUIT_CMD, tap_code16(KC_NO))

tap_dance_action_t tap_dance_actions[] = {
    [DOT_EXLM]           = ADD_ACTION_TAP_DANCE(DOT_EXLM),
    [EXLM_QUES]          = ADD_ACTION_TAP_DANCE(EXLM_QUES),
    [COMMA_MINUS]        = ADD_ACTION_TAP_DANCE(COMMA_MINUS),
    [SLASH_UNDS]         = ADD_ACTION_TAP_DANCE(SLASH_UNDS),
    [TAB_WINTAB]         = ADD_ACTION_TAP_DANCE(TAB_WINTAB),
    [LEFT__CTRL_LEFT]    = ADD_ACTION_TAP_DANCE(LEFT__CTRL_LEFT),
    [RIGHT__CTRL_RIGHT]  = ADD_ACTION_TAP_DANCE(RIGHT__CTRL_RIGHT),
    [SL_BKSL]            = ADD_ACTION_TAP_DANCE(SL_BKSL),
    [DQUOTE_QUOTE]       = ADD_ACTION_TAP_DANCE(DQUOTE_QUOTE),
    [HASH_AT]            = ADD_ACTION_TAP_DANCE(HASH_AT),
    [DLR_PERC]           = ADD_ACTION_TAP_DANCE(DLR_PERC),
    [HEX_NUMPAD_1_A]     = ADD_ACTION_TAP_DANCE(HEX_NUMPAD_1_A),
    [HEX_NUMPAD_2_B]     = ADD_ACTION_TAP_DANCE(HEX_NUMPAD_2_B),
    [HEX_NUMPAD_3_C]     = ADD_ACTION_TAP_DANCE(HEX_NUMPAD_3_C),
    [HEX_NUMPAD_4_D]     = ADD_ACTION_TAP_DANCE(HEX_NUMPAD_4_D),
    [HEX_NUMPAD_5_E]     = ADD_ACTION_TAP_DANCE(HEX_NUMPAD_5_E),
    [HEX_NUMPAD_6_F]     = ADD_ACTION_TAP_DANCE(HEX_NUMPAD_6_F),
    [HEX_NUMPAD_0_X]     = ADD_ACTION_TAP_DANCE(HEX_NUMPAD_0_X),
    [DEC_DOT_COMMA]      = ADD_ACTION_TAP_DANCE(DEC_DOT_COMMA),
    [CIRC_QUIT_VIM]      = ADD_ACTION_TAP_DANCE(CIRC_QUIT_VIM),
    [ESC_FORCE_QUIT_VIM] = ADD_ACTION_TAP_DANCE(ESC_FORCE_QUIT_VIM),
};

#define DE_ADIA UC(0x00E4)
#define DE_SS UC(0x00DF)
#define DE_ODIA UC(0x00F6)
#define DE_UDIA UC(0x00FC)

enum custom_layers {
    _GRAPHITE,
    _ISRT,
    _COLEMAK_DH,
    _QWERTY,
    _SPECIAL,
    _NUMBERS,
    _NAVIGATION,
    _FUNCTION,
    _MOUSE,
    _LAYOUT_SELECTION,
};

// Custom keycodes
enum custom_keycodes {
    GRAPHITE = SAFE_RANGE,
    ISRT,
    COLEMAK_DH,
    QWERTY,
    GO_ALPHA,
};

//==============================================================================

// Tracks the current base layer
uint8_t current_alpha_layer = _GRAPHITE;

bool handle_layout_switch(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case GRAPHITE:
            if (record->event.pressed) {
                current_alpha_layer = _GRAPHITE;
                layer_move(current_alpha_layer);
            }
            return false;

        case ISRT:
            if (record->event.pressed) {
                current_alpha_layer = _ISRT;
                layer_move(current_alpha_layer);
            }
            return false;
        case COLEMAK_DH:
            if (record->event.pressed) {
                current_alpha_layer = _COLEMAK_DH;
                layer_move(current_alpha_layer);
            }
            return false;
        case QWERTY:
            if (record->event.pressed) {
                current_alpha_layer = _QWERTY;
                layer_move(current_alpha_layer);
            }
            return false;
        case GO_ALPHA:
            if (record->event.pressed) {
                layer_move(current_alpha_layer); // or layer_on/off/toggle depending on use
            }
            return false;
        default:
            break;
    }
    return true;
}

//==============================================================================

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case GRAPHITE:
        case ISRT:
        case COLEMAK_DH:
        case QWERTY:
        case GO_ALPHA:
            return handle_layout_switch(keycode, record);
        default:
            break;
    }
    return true;
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_GRAPHITE] = LAYOUT(
// ┌───────────────────────────── Left hand ─────────────────────────────┐    ┌────────────────────────────────── Right hand ─────────────────────────────────────┐
    KC_B, KC_L,               KC_D,              KC_W,              KC_Z, /**/ KC_BSPC, KC_F,              KC_O,              KC_U,               KC_J,            // Row 1
    MT(MOD_LSFT,KC_N), MT(MOD_LALT,KC_R), MT(MOD_LCTL,KC_T), MT(MOD_LGUI,KC_S), KC_G, /**/ KC_Y, MT(MOD_RGUI,KC_H), MT(MOD_RCTL,KC_A), MT(MOD_RALT,KC_E), MT(MOD_RSFT,KC_I),            // Row 2
    KC_Q, KC_X,               KC_M,              KC_C,              KC_V, /**/ KC_K,    KC_P,              TD(COMMA_MINUS),   TD(DOT_EXLM),       TD(SLASH_UNDS),  // Row 3
    // THUMB_LEFT_3, THUMB_LEFT_1, THUMB_LEFT_2, /**/ THUMB_RIGHT_2, THUMB_RIGHT_1, THUMB_RIGHT_3  // Thumbs
    LT(_NAVIGATION, KC_ENT), LT(_SPECIAL, KC_SPC), OSM(MOD_LSFT), KC_BSPC, KC_SPC, KC_ENT
  ),

  [_ISRT] = LAYOUT(
// ┌────────────────────── Left hand ──────────────────────┐    ┌─────────────────────────── Right hand ──────────────────────────────┐
    KC_Y, KC_C, KC_L,              KC_M,              KC_K, /**/ KC_Z, KC_F,              KC_U,              TD(COMMA_MINUS), KC_BSPC, // Row 1
    KC_I, KC_S, MT(MOD_LSFT,KC_R), MT(MOD_LALT,KC_T), MT(MOD_LCTL,KC_G), /**/ MT(MOD_RGUI,KC_P), MT(MOD_RCTL,KC_N), MT(MOD_RALT,KC_E), MT(MOD_RSFT,KC_A), MT(MOD_RGUI,KC_O),    // Row 2
    KC_Q, KC_V, KC_W,              KC_D,              KC_J, /**/ KC_B, KC_H,              TD(SLASH_UNDS),    TD(DOT_EXLM),    KC_X,    // Row 3
    // THUMB_LEFT_3, THUMB_LEFT_1, THUMB_LEFT_2, /**/ THUMB_RIGHT_2, THUMB_RIGHT_1, THUMB_RIGHT_3  // Thumbs
    LT(_NAVIGATION, KC_ENT), LT(_SPECIAL, KC_SPC), OSM(MOD_LSFT), KC_BSPC, KC_SPC, KC_ENT
  ),

  [_COLEMAK_DH] = LAYOUT(
// ┌────────────────────── Left hand ──────────────────────┐    ┌───────────────────────────── Right hand ────────────────────────────────┐
    KC_Q, KC_W, KC_F,              KC_P,              KC_B, /**/ KC_J, KC_L,              KC_U,              KC_Y,         KC_BSPC,        // Row 1
    KC_A, KC_R, MT(MOD_LSFT,KC_S), MT(MOD_LALT,KC_T), MT(MOD_LCTL,KC_G), /**/ MT(MOD_RGUI,KC_M), MT(MOD_RCTL,KC_N), MT(MOD_RALT,KC_E), MT(MOD_RSFT,KC_I), MT(MOD_RGUI,KC_O),           // Row 2
    KC_Z, KC_X, KC_C,              KC_D,              KC_V, /**/ KC_K, KC_H,              TD(COMMA_MINUS),   TD(DOT_EXLM), TD(SLASH_UNDS), // Row 3
    // THUMB_LEFT_3, THUMB_LEFT_1, THUMB_LEFT_2, /**/ THUMB_RIGHT_2, THUMB_RIGHT_1, THUMB_RIGHT_3  // Thumbs
    LT(_NAVIGATION, KC_ENT), LT(_SPECIAL, KC_SPC), OSM(MOD_LSFT), KC_BSPC, KC_SPC, KC_ENT
  ),

  [_QWERTY] = LAYOUT(
// ┌────────────────────── Left hand ──────────────────────┐    ┌───────────────────────────── Right hand ────────────────────────────────┐
    KC_Q, KC_W, KC_E,              KC_R,              KC_T, /**/ KC_Y, KC_U,              KC_I,              KC_O,         KC_P,           // Row 1
    KC_A, KC_S, MT(MOD_LSFT,KC_D), MT(MOD_LALT,KC_F), MT(MOD_LCTL,KC_G), /**/ MT(MOD_RGUI,KC_H), MT(MOD_RCTL,KC_J), MT(MOD_RALT,KC_K), MT(MOD_RSFT,KC_L),         MT(MOD_RGUI,KC_SCLN),        // Row 2
    KC_Z, KC_X, KC_C,              KC_V,              KC_B, /**/ KC_N, KC_M,              TD(COMMA_MINUS),   TD(DOT_EXLM), TD(SLASH_UNDS), // Row 3
    // THUMB_LEFT_3, THUMB_LEFT_1, THUMB_LEFT_2, /**/ THUMB_RIGHT_2, THUMB_RIGHT_1, THUMB_RIGHT_3  // Thumbs
    LT(_NAVIGATION, KC_ENT), LT(_SPECIAL, KC_SPC), OSM(MOD_LSFT), KC_BSPC, KC_SPC, KC_ENT
  ),

  [_SPECIAL] = LAYOUT(
// ┌──────────────────────────────── Left hand ───────────────────────────────┐    ┌─────────────────────────── Right hand ─────────────────────────────┐
    TD(ESC_FORCE_QUIT_VIM), KC_UNDS,      KC_LBRC, KC_RBRC, TD(CIRC_QUIT_VIM), /**/ KC_PLUS,       KC_LABK, KC_RABK,          KC_EQUAL, KC_BSPC,         // Row 1
    KC_TAB,                 TD(SL_BKSL),  KC_LCBR, KC_RCBR, KC_ASTR,           /**/ KC_MINS,       KC_LPRN, KC_RPRN,          KC_SCLN,  KC_ENT,          // Row 2
    TD(HASH_AT),            TD(DLR_PERC), KC_PIPE, KC_TILD, KC_GRV,            /**/ TD(EXLM_QUES), KC_AMPR, TD(DQUOTE_QUOTE), KC_COLN,  TO(_NUMBERS), // Row 3
    // THUMB_LEFT_3, THUMB_LEFT_1, THUMB_LEFT_2, /**/ THUMB_RIGHT_2, THUMB_RIGHT_1, THUMB_RIGHT_3  // Thumbs
    LT(_NAVIGATION, KC_ENT), LT(_SPECIAL, KC_SPC), OSM(MOD_LSFT), KC_BSPC, KC_SPC, KC_ENT
  ),

  [_NUMBERS] = LAYOUT(
// ┌──────────────────────────────────────── Left hand ──────────────────────────────────────────────────┐    ┌──────────────────────────────────────── Right hand ──────────────────────────────────────────┐
    KC_ESCAPE,          KC_MEDIA_PLAY_PAUSE, KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK, KC_SLASH,          /**/ KC_PLUS,            KC_7,               KC_8,               KC_9,               KC_BSPC,       // Row 1
    KC_TAB,             KC_LALT,             KC_LSFT,             KC_LCTL,             KC_ASTR,           /**/ KC_MINS,            TD(HEX_NUMPAD_4_D), TD(HEX_NUMPAD_5_E), TD(HEX_NUMPAD_6_F), KC_ENT,        // Row 2
    KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP,    KC_AUDIO_VOL_DOWN,   KC_AUDIO_VOL_UP,     TD(DEC_DOT_COMMA), /**/ TD(HEX_NUMPAD_0_X), TD(HEX_NUMPAD_1_A), TD(HEX_NUMPAD_2_B), TD(HEX_NUMPAD_3_C), TO(_FUNCTION), // Row 3
    // THUMB_LEFT_3, THUMB_LEFT_1, THUMB_LEFT_2, /**/ THUMB_RIGHT_2, THUMB_RIGHT_1, THUMB_RIGHT_3  // Thumbs
    LT(_NAVIGATION, KC_ENT), LT(_SPECIAL, KC_SPC), OSM(MOD_LSFT), KC_BSPC, KC_SPC, KC_ENT
  ),

  [_NAVIGATION] = LAYOUT(
// ┌─────────────────────── Left hand ─────────────────────────┐    ┌───────────────── Right hand ────────────────────┐
    KC_ESC,     KC_BSPC,      KC_WBAK,    KC_WFWD,    KC_NO,      /**/ KC_PGUP, KC_HOME,    KC_END, KC_PGDN,  KC_BSPC,   // Row 1
    KC_TAB,     KC_LALT,    KC_LSFT,    KC_LCTL,    LCTL(KC_S), /**/ KC_LEFT, KC_DOWN,    KC_UP,  KC_RIGHT, KC_ENT,    // Row 2
    LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), LCTL(KC_Y), /**/ KC_NO,   TO(_MOUSE), KC_NO,  KC_NO,    KC_DELETE, // Row 3
    // THUMB_LEFT_3, THUMB_LEFT_1, THUMB_LEFT_2, /**/ THUMB_RIGHT_2, THUMB_RIGHT_1, THUMB_RIGHT_3  // Thumbs
    LT(_NAVIGATION, KC_ENT), LT(_SPECIAL, KC_SPC), OSM(MOD_LSFT), KC_BSPC, KC_SPC, KC_ENT
  ),

  [_FUNCTION] = LAYOUT(
// ┌────────────────────── Left hand ────────────────────────┐    ┌──────────── Right hand ─────────────┐
    KC_ESC, KC_BSPC,   KC_NO,   KC_NO,   TO(_LAYOUT_SELECTION), /**/ KC_NO, KC_F1, KC_F2,  KC_F3,  KC_F4,  // Row 1
    KC_NO,  KC_LALT, KC_LSFT, KC_LCTL,      KC_NO,            /**/ KC_NO, KC_F5, KC_F6,  KC_F7,  KC_F8,  // Row 2
    KC_NO,  KC_NO,   KC_NO,   KC_NO,        KC_NO,            /**/ KC_NO, KC_F9, KC_F10, KC_F11, KC_F12, // Row 3
// └────────────────────── Left hand ────────────────────────┘    └──────────── Right hand ─────────────┘
    // THUMB_LEFT_3, THUMB_LEFT_1, THUMB_LEFT_2, /**/ THUMB_RIGHT_2, THUMB_RIGHT_1, THUMB_RIGHT_3  // Thumbs
    LT(_NAVIGATION, KC_ENT), LT(_SPECIAL, KC_SPC), OSM(MOD_LSFT), KC_BSPC, KC_SPC, KC_ENT
  ),

  [_MOUSE] = LAYOUT(
// ┌────────────── Left hand ────────────────┐    ┌─────────────── Right hand ───────────────┐
    KC_ESC, KC_BSPC,   MS_UP,   KC_NO,   KC_NO, /**/ MS_WHLU, KC_LCTL, KC_LSFT, KC_LALT, KC_NO, // Row 1
    KC_NO,  MS_LEFT, MS_DOWN, MS_RGHT, KC_NO, /**/ MS_WHLD, MS_BTN1, MS_BTN2, KC_NO,   KC_NO, // Row 2
    KC_NO,  MS_BTN3, MS_WHLL, MS_WHLR, KC_NO, /**/ KC_NO,   MS_ACL0, MS_ACL1, MS_ACL2, KC_NO, // Row 3
// └────────────── Left hand ────────────────┘    └─────────────── Right hand ───────────────┘
    // THUMB_LEFT_3, THUMB_LEFT_1, THUMB_LEFT_2, /**/ THUMB_RIGHT_2, THUMB_RIGHT_1, THUMB_RIGHT_3  // Thumbs
    LT(_NAVIGATION, KC_ENT), LT(_SPECIAL, KC_SPC), OSM(MOD_LSFT), KC_BSPC, KC_SPC, KC_ENT
  ),

  [_LAYOUT_SELECTION] = LAYOUT(
// ┌────────────── Left hand ─────────────────┐    ┌─────────────── Right hand ───────────────┐
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, /**/ KC_NO,  KC_NO,   KC_NO,   KC_NO,    KC_NO,  // Row 1
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, /**/ KC_NO, GRAPHITE, ISRT,  COLEMAK_DH, QWERTY, // Row 2
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, /**/ KC_NO,  KC_NO,   KC_NO,   KC_NO,    KC_NO,  // Row 3
// └────────────── Left hand ─────────────────┘    └─────────────── Right hand ───────────────┘
    // THUMB_LEFT_3, THUMB_LEFT_1, THUMB_LEFT_2, /**/ THUMB_RIGHT_2, THUMB_RIGHT_1, THUMB_RIGHT_3  // Thumbs
    LT(_NAVIGATION, KC_ENT), LT(_SPECIAL, KC_SPC), KC_LGUI, OSM(MOD_LSFT), TO(_SPECIAL), GO_ALPHA
  ),

};

// clang-format on
