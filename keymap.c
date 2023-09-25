#include QMK_KEYBOARD_H

// Home row mods.
#define CTRL_W MT(MOD_LCTL, KC_W)
#define ALT_F MT(MOD_LALT, KC_F)
#define GUI_P MT(MOD_LGUI, KC_P)
#define SHIFT_T MT(MOD_LSFT, KC_T)
#define SHIFT_N MT(MOD_RSFT, KC_N)
#define GUI_L MT(MOD_LGUI, KC_L)
#define ALT_U MT(MOD_LALT, KC_U)
#define CTRL_Y MT(MOD_LCTL, KC_Y)

// Layer keys
#define SPACE_LEFT LT(LEFT_LAYER, KC_SPACE)
#define ENTER_RIGHT LT(RIGHT_LAYER, KC_ENTER)
#define BSPC_NUM LT(NUM_LAYER, KC_BSPC)

enum my_layers {
  BASE_LAYER,
  LEFT_LAYER,
  RIGHT_LAYER,
  NUM_LAYER,
  NAV_LAYER
};

enum my_keycodes {
  M_ALTT = SAFE_RANGE,
  M_NDESK,
  M_PDESK,
  M_XTAB,
  M_APP1,
  M_APP2,
  M_APP3,
  M_APP4,
  M_1PASS,
  M_NTRM,
  M_EMOJI,
  M_DDS,
  M_ISCROS,
  M_ISWIN
};

// Tap-hold tap dances require custom types and functions.

typedef enum {
  TD_NONE,
  TD_UNKNOWN,
  TD_SINGLE_TAP,
  TD_DOUBLE_TAP,
  TD_HOLD
} td_state_t;

typedef struct {
  td_state_t state;
} td_tap_t;

static td_tap_t td_shift_nav = {
  .state = TD_NONE
};

td_state_t td_get_state(tap_dance_state_t *state);

void shift_nav_finished(tap_dance_state_t *state, void *user_data);
void shift_nav_reset(tap_dance_state_t *state, void *user_data);

// Tap Dance definitions

enum {
  TD_SHIFT_NAV,
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_SHIFT_NAV] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shift_nav_finished, shift_nav_reset),
};

// Combos for missing keys and other useful combinations.

enum my_combos {
  CAPSWORD_COMBO,
  Q_COMBO,
  Z_COMBO,
  V_COMBO,
  K_COMBO,
  SEMI_COMBO,
  SLASH_COMBO,
  COMBO_LENGTH
};

uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM capsword_combo[] = {SHIFT_T, SHIFT_N, COMBO_END};
const uint16_t PROGMEM q_combo[] = {CTRL_W, ALT_F, COMBO_END};
const uint16_t PROGMEM z_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM v_combo[] = {KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM k_combo[] = {KC_H, KC_COMMA, COMBO_END};
const uint16_t PROGMEM semi_combo[] = {KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM slash_combo[] = {KC_COMMA, KC_DOT, COMBO_END};

combo_t key_combos[] = {
  [CAPSWORD_COMBO] = COMBO(capsword_combo, CW_TOGG),
  [Q_COMBO] = COMBO(q_combo, KC_Q),
  [Z_COMBO] = COMBO(z_combo, KC_Z),
  [V_COMBO] = COMBO(v_combo, KC_V),
  [K_COMBO] = COMBO(k_combo, KC_K),
  [SEMI_COMBO] = COMBO(semi_combo, KC_SCLN),
  [SLASH_COMBO] = COMBO(slash_combo, KC_SLSH)
};

// Stores state of M_ALTT macro - true if we are currently tabbing between
// windows.
static bool m_altt_pressed = false;

// Toggle for keys that affect the the desktop - value can be changed in
// function layer
static bool m_is_chromebook = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [BASE_LAYER] = LAYOUT_split_3x5_2(
    KC_NO,             CTRL_W,      ALT_F,        GUI_P,    KC_B,   KC_J,   GUI_L,    ALT_U,    CTRL_Y,  KC_NO,
    KC_A,              KC_R,        KC_S,         SHIFT_T,  KC_G,   KC_M,   SHIFT_N,  KC_E,     KC_I,    KC_O,
    TD(TD_SHIFT_NAV),  KC_X,        KC_C,         KC_D,     KC_NO,  KC_NO,  KC_H,     KC_COMM,  KC_DOT,  BSPC_NUM,
    KC_NO,             SPACE_LEFT,  ENTER_RIGHT,  KC_NO
  ),

  [LEFT_LAYER] = LAYOUT_split_3x5_2(
    KC_NO,     KC_GRV,        HYPR(KC_M),  HYPR(KC_A),  HYPR(KC_K),  KC_DEL,   M_1PASS,  LSFT(LCTL(KC_C)),  KC_NO,   KC_NO,
   KC_NO,      KC_NO,         KC_NO,       KC_NO,       KC_NO,       KC_BSPC,  M_APP1,   M_APP2,            M_APP3,  M_APP4,
    KC_NO,     LCTL(KC_X),    LCTL(KC_C),  LCTL(KC_V),  KC_NO,       KC_NO,    KC_NO,    M_EMOJI,           M_DDS,   KC_NO,
    KC_TRNS,   KC_TRNS,       KC_ESC,     KC_TRNS
  ),

  [RIGHT_LAYER] = LAYOUT_split_3x5_2(
    KC_NO,          LSFT(KC_2),  LSFT(KC_3),  KC_DLR,   KC_PERC,  KC_CIRC,  KC_AMPR,        KC_ASTR,        KC_EXLM,  KC_NO,
    LSFT(KC_NUBS),  KC_LBRC,     KC_LCBR,     KC_LPRN,  KC_SCLN,  KC_COLN,  LSFT(KC_QUOT),  LSFT(KC_BSLS),  KC_UNDS,  KC_PLUS,
    KC_NUBS,        KC_RBRC,     KC_RCBR,     KC_RPRN,  KC_NO,    KC_NO,    KC_QUOT,        KC_BSLS,        KC_MINS,  KC_EQL,
    KC_TRNS,        KC_TAB,     KC_TRNS,     KC_TRNS
  ),

  [NUM_LAYER] = LAYOUT_split_3x5_2(
    KC_NO,    KC_1,    KC_2,     KC_3,    KC_PPLS,  KC_NO,  KC_F1,  KC_F2,  KC_F3,  KC_NO,
    KC_PSLS,  KC_4,    KC_5,     KC_6,    KC_PMNS,  KC_NO,  KC_F4,  KC_F5,  KC_F6,  KC_F10,
    KC_0,     KC_7,    KC_8,     KC_9,    KC_NO,    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_TRNS,  KC_TAB,  KC_TRNS,  KC_TRNS
  ),

  [NAV_LAYER] = LAYOUT_split_3x5_2(
    KC_NO,    KC_PSCR,  KC_MPLY,   KC_VOLU,  KC_BRIU,  M_PDESK,  LCTL(KC_TAB),  M_ALTT,   M_NDESK,  KC_NO,
    KC_NO,    KC_MNXT,  KC_MUTE,   KC_VOLD,  KC_BRID,  KC_NO,    KC_LEFT,       KC_DOWN,  KC_UP,    KC_RIGHT,
    KC_NO,    KC_MPRV,  M_ISCROS,  M_ISWIN,  KC_NO,    KC_NO,    KC_HOME,       KC_PGDN,  KC_PGUP,  KC_END,
    KC_TRNS,  KC_TRNS,  KC_ESC,    KC_TRNS
  )

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  // Stop pressing the alt key once a key other than the alt-tab macro has been
  // pressed.
  if (keycode != M_ALTT && m_altt_pressed) {
    unregister_code(KC_LALT);
    m_altt_pressed = false;
  }

  // Ensure shift is not pressed when the left and right layers are active.
  if (IS_LAYER_ON(LEFT_LAYER) || IS_LAYER_ON(RIGHT_LAYER)) {
    switch (keycode) {
      case KC_Z:
      case KC_SLSH:
        break;
      default:
        del_mods(MOD_MASK_SHIFT);
        del_oneshot_mods(MOD_MASK_SHIFT);
    }
  }

  switch (keycode) {
    case M_ALTT:
      if (record->event.pressed) {
        if (!m_altt_pressed) {
          register_code(KC_LALT);
          m_altt_pressed = true;
        }
        tap_code(KC_TAB);
      }
      break;
    case M_APP1:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LALT));
          SEND_STRING(SS_TAP(X_1));
          SEND_STRING(SS_UP(X_LALT));
        } else {
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LCTL)SS_DOWN(X_LALT)SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_1));
          SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LALT)SS_UP(X_LCTL)SS_UP(X_LSFT));
        }
      }
      break;
    case M_APP2:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LALT));
          SEND_STRING(SS_TAP(X_2));
          SEND_STRING(SS_UP(X_LALT));
        } else {
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LCTL)SS_DOWN(X_LALT)SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_2));
          SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LALT)SS_UP(X_LCTL)SS_UP(X_LSFT));
        }
      }
      break;
    case M_APP3:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LALT));
          SEND_STRING(SS_TAP(X_3));
          SEND_STRING(SS_UP(X_LALT));
        } else {
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LCTL)SS_DOWN(X_LALT)SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_3));
          SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LALT)SS_UP(X_LCTL)SS_UP(X_LSFT));
        }
      }
      break;
    case M_APP4:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LALT));
          SEND_STRING(SS_TAP(X_4));
          SEND_STRING(SS_UP(X_LALT));
        } else {
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LCTL)SS_DOWN(X_LALT)SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_4));
          SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LALT)SS_UP(X_LCTL)SS_UP(X_LSFT));
        }
      }
      break;
    case M_1PASS:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LALT)SS_TAP(X_1)SS_UP(X_LALT));
          SEND_STRING(SS_DELAY(100));
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LCTL));
          SEND_STRING(SS_TAP(X_X));
          SEND_STRING(SS_UP(X_LCTL)SS_UP(X_LSFT));
        } else {
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LCTL));
          SEND_STRING(SS_TAP(X_SPC));
          SEND_STRING(SS_UP(X_LCTL)SS_UP(X_LSFT));
        }
      }
      break;
    case M_NDESK:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_RBRC));
          SEND_STRING(SS_UP(X_LGUI));
        } else {
          SEND_STRING(SS_DOWN(X_LCTL)SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_RGHT));
          SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LCTL));
        }
      }
      break;
    case M_PDESK:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_LBRC));
          SEND_STRING(SS_UP(X_LGUI));
        } else {
          SEND_STRING(SS_DOWN(X_LCTL)SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_LEFT));
          SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LCTL));
        }
      }
      break;
    case M_XTAB:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LCTL)SS_TAP(X_W)SS_UP(X_LCTL));
        } else {
          SEND_STRING(SS_DOWN(X_LCTL)SS_TAP(X_F4)SS_UP(X_LCTL));
        }
      }
      break;
    case M_NTRM:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LCTL)SS_TAP(X_T)SS_UP(X_LCTL));
        } else {
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LCTL));
          SEND_STRING(SS_TAP(X_1));
          SEND_STRING(SS_UP(X_LCTL)SS_UP(X_LSFT));
        }
      }
      break;
    case M_EMOJI:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_SPC));
          SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LSFT));
        } else {
          SEND_STRING(SS_DOWN(X_LGUI)SS_TAP(X_SCLN)SS_UP(X_LGUI));
        }
      }
      break;
    case M_DDS:
      if (record->event.pressed) {
        SEND_STRING("../");
      }
      break;
    case M_ISCROS:
      if (record->event.pressed) {
        m_is_chromebook = true;
      }
      break;
    case M_ISWIN:
      if (record->event.pressed) {
        m_is_chromebook = false;
      }
      break;
  }

  return true;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // Set the tapping term for the homerow mods.
    case CTRL_W:
    case ALT_F:
    case GUI_P:
    case SHIFT_T:
    case SHIFT_N:
    case GUI_L:
    case ALT_U:
    case CTRL_Y:
      return TAPPING_TERM_MODS;
    case TD(TD_SHIFT_NAV):
      return TAPPING_TERM_TDS;
    default:
      return TAPPING_TERM;
  }
}

td_state_t td_get_state(tap_dance_state_t *state) {

  if (state->count == 1) {
    // If the keypress has been interrupted by another keypress or is no longer
    // held down by the end of the tap time, then we know it was just a single
    // tap.
    if (state->interrupted || !state->pressed)
      return TD_SINGLE_TAP;
    else
      // If it is still held at the end of the tap time, then it is a hold.
      return TD_HOLD;
  } else if (state->count > 1) {
    // In the case where there has been more than one tap in the tap time, we
    // have to make a judgement call. If the key is still held down we will
    // assume it was a flutter and call it a hold.
    if (state->pressed)
      return TD_HOLD;
    // If the keypress has finished or has been interrupted then we will assume
    // that there was some actual fast typing going on and issue two taps, which
    // will be the most common scenario.
    if (state->interrupted || !state->pressed)
      return TD_DOUBLE_TAP;
  }

  return TD_UNKNOWN;
}

void shift_nav_finished(tap_dance_state_t *state, void *user_data) {
  td_shift_nav.state = td_get_state(state);
  switch (td_shift_nav.state) {
    case TD_SINGLE_TAP:
      set_oneshot_mods(MOD_LSFT);
      break;
    case TD_DOUBLE_TAP:
      register_code(KC_Z);
      break;
    case TD_HOLD:
      layer_on(NAV_LAYER);
      break;
    default:
      break;
  }
}

void shift_nav_reset(tap_dance_state_t *state, void *user_data) {
  switch (td_shift_nav.state) {
    case TD_SINGLE_TAP:
      // Do nothing - the oneshot mod will switch itself off after another key
      // has been pressed.
      break;
    case TD_DOUBLE_TAP:
      unregister_code(KC_Z);
      break;
    case TD_HOLD:
      layer_off(NAV_LAYER);
    default:
      break;
  }
  td_shift_nav.state = TD_NONE;
}
