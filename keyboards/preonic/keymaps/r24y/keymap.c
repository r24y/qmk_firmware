#include "preonic.h"
#include "action_layer.h"
#include "eeconfig.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

// Custom keys.
#define _RY_DLLR 0 // Dollar sign; shift gives tilde
#define _RY_ASPD 1 // Asperand; shift gives caret
#define _VM_X 2 // Vim mode X
#define _VM_C 3 // Vim mode C
#define _VM_B 4 // Vim mode B
#define _VM_W 5 // Vim mode W
#define _RY_PPSI 6 // Paren-paren-semi
#define _RY_CCCM 7 // Curly-curly-comma

#define RY_DLLR M(_RY_DLLR)
#define RY_ASPD M(_RY_ASPD)
#define VM_X    M(_VM_X)
#define RY_ECTL CTL_T(KC_ESC)
#define RY_CURLY_CURLY_COMMA MACRO( I(10), D(LSFT), T(LCBR), T(RCBR), U(LSFT), T(COMMA), T(LEFT), T(LEFT), END )
#define RY_PAREN_PAREN_SEMI MACRO( I(10), D(LSFT), T(LPRN), T(RPRN), U(LSFT), T(SCOLON), T(LEFT), T(LEFT), END )
#define RY_CCCM M(_RY_CCCM)
#define RY_PPSI M(_RY_PPSI)

#define MODS_SHFT_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  BACKLIT
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   -  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl |  A   |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |Shift |  Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Shift (Enter when tapped)
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Ctl/Esc| Vim | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  {KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_BSPC},
  {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS},
  {KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SFT_T(KC_ENT)},
  {RY_ECTL, XXXXXXX, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   `  |      |      |   $  |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   $  |      |      |   #  |   !  |      |   &  |   *  |   +  |   =  |   ^  |  @   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   ~  |   ]  |   }  |   '  |  >   |  <   |   -  |   {  |   [  |   _  |  ^   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   '  |   %  |      |   )  |      |      |   (  |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Caps |      |      |      |      |             |      | Home | PgDn | PgUp | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = {
  {KC_GRV,  XXXXXXX, XXXXXXX, KC_DLR , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______},
  {KC_DLR,  XXXXXXX, XXXXXXX, KC_HASH, KC_EXLM, XXXXXXX, KC_AMPR, KC_ASTR, KC_PLUS, KC_EQL,  KC_CIRC, RY_ASPD},
  {_______, KC_TILD, KC_RBRC, KC_RCBR, KC_QUOT, KC_RABK, KC_LABK, KC_MINS, KC_LCBR, KC_LBRC, KC_UNDS, KC_CIRC},
  {_______, KC_QUOT, KC_PERC, _______, KC_RPRN, _______, _______, KC_LPRN, _______, _______, _______, _______},
  {KC_CAPS, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END}
},

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      | ();  |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |  {}, |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, RY_PPSI, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, RY_CCCM, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
},

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset|      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = {
  {KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12},
  {_______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
}


};

#ifdef AUDIO_ENABLE
float tone_startup[][2] = {
  {NOTE_B5, 20},
  {NOTE_B6, 8},
  {NOTE_DS6, 20},
  {NOTE_B6, 8}
};

float tone_qwerty[][2]     = SONG(QWERTY_SOUND);

float tone_goodbye[][2] = SONG(GOODBYE_SOUND);

float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);

// Yes, I'm using the designated "num lock" sounds to represent Caps Lock.
// The num lock tones are a lot clearer and easier to hear, so there's no
// doubt as to the state of the keyboard. I'm not using Num Lock at the moment
// so there's no issue.
float tone_caps_on[][2] = SONG(NUM_LOCK_ON_SOUND);
float tone_caps_off[][2] = SONG(NUM_LOCK_OFF_SOUND);

// I'm using the designated "caps lock" sounds to warn myself that I've pressed
// the "GUI" key (Command, Super, or Windows, depending on platform).
float tone_super_on[][2] = SONG(CAPS_LOCK_ON_SOUND);
float tone_super_off[][2] = SONG(CAPS_LOCK_OFF_SOUND);

#endif

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case KC_LGUI:
          #ifdef AUDIO_ENABLE
            if (record->event.pressed) {
              PLAY_NOTE_ARRAY(tone_super_on, false, 0);
            }
          #endif
          break;
        case LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case BACKLIT:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
          } else {
            unregister_code(KC_RSFT);
          }
          return false;
          break;
      }
    return true;
};

// Macro actions for each corresponding ID.
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch(id) {
    case _RY_ASPD:
      if (record->event.pressed) {
        register_code(KC_LSFT);
          register_code(KC_2);
          unregister_code(KC_2);
        unregister_code(KC_LSFT);
      }
      break;
    case _RY_PPSI:
      if (record->event.pressed) {
        return RY_PAREN_PAREN_SEMI;
      }
    case _RY_CCCM:
      if (record->event.pressed) {
        return RY_CURLY_CURLY_COMMA;
      }
    case _VM_X:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          music_scale_user();
        #endif
      }
    }
  return MACRO_NONE;
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
}

#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
    PLAY_NOTE_ARRAY(tone_startup, false, 0);
}

void shutdown_user()
{
    PLAY_NOTE_ARRAY(tone_goodbye, false, 0);
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_NOTE_ARRAY(music_scale, false, 0);
}

void led_set_user(uint8_t usb_led)
{
    static uint8_t old_usb_led = 0;

    _delay_ms(10); // gets rid of tick

    if (!is_playing_notes())
    {
        if ((usb_led & (1<<USB_LED_CAPS_LOCK)) && !(old_usb_led & (1<<USB_LED_CAPS_LOCK)))
        {
                // If CAPS LK LED is turning on...
                PLAY_NOTE_ARRAY(tone_caps_on,  false, LEGATO);
        }
        else if (!(usb_led & (1<<USB_LED_CAPS_LOCK)) && (old_usb_led & (1<<USB_LED_CAPS_LOCK)))
        {
                // If CAPS LK LED is turning off...
                PLAY_NOTE_ARRAY(tone_caps_off, false, LEGATO);
        }
    }

    old_usb_led = usb_led;
}


#endif
