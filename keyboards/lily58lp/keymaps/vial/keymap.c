#include QMK_KEYBOARD_H
#include "lib/bongocat.c"
#include "lib/logo.c"

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
  _NUMPAD,
};

#define L_BASE 0
#define L_LOWER (1 << 1)
#define L_RAISE (1 << 2)
#define L_ADJUST (1 << 3)
#define L_NUMPAD (1 << 4)

#define L_ADJUST_TRI (L_ADJUST | L_RAISE | L_LOWER )

// // Home‐Row Mod-Taps on QWERTY
// Left-hand home row mods
#define HOME_A LGUI_T(KC_A)
#define HOME_S LALT_T(KC_S)
#define HOME_D LCTL_T(KC_D)
#define HOME_F LSFT_T(KC_F)

// Right-hand home row mods
#define HOME_J RSFT_T(KC_J)
#define HOME_K RCTL_T(KC_K)
#define HOME_L LALT_T(KC_L)
#define HOME_SCLN RGUI_T(KC_SCLN)

// KC_LCTL, MT_LCTL_A, MT_LALT_S, MT_LGUI_D, MT_LSFT_F,    KC_G,                     KC_H,    MT_RSFT_J,    MT_RGUI_K,    MT_RALT_L,    MT_RCTL_SCLN, KC_QUOT,
static uint8_t tap_count = 0;
static uint16_t last_tap_time = 0;
enum custom_keycodes {
  TAP_LAYER = SAFE_RANGE
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | LOWER| LALT | /Space  /       \Enter \  |BackSP| RAISE| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      | DEL  |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  KC_LCTL,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, RCTL_T(KC_QUOT),
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                        KC_LGUI,KC_LALT,MO(_LOWER), KC_SPC, KC_ENT,     MO(_RAISE),KC_BSPC, KC_RGUI
 ),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
*  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   -  |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      | MPRV | NEXT | NEXT |      |      |-------|    |-------|      |   _  |   +  |   {  |   }  |   |  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LOWER|LGUI  | /Space  /       \Enter \  |BackSP| RAISE| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'       ----''--------------------'
 */
[_LOWER] = LAYOUT(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                    KC_CIRC, KC_AMPR, KC_ASTR, KC_GRV,  KC_TILD, _______,
  _______, LCTL(KC_B), KC_LCBR, KC_MINUS, KC_LPRN, KC_EQUAL,                   KC_PIPE, KC_RPRN, KC_EQUAL, KC_RCBR, _______, _______,
  _______, LCTL(KC_I), LCTL(KC_DOT), KC_UNDS, KC_PLUS, KC_SLASH, KC_DELETE, KC_DELETE, KC_BSLS, _______, _______, _______, _______, _______,
                             _______, _______, _______,  _______, _______,  _______, _______, _______
),
  // _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD,
  // _______, KC_MPRV, KC_MNXT, KC_MPLY, KC_VOLD, KC_VOLU, _______, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,



/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    | PRSC |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | VOL+ |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |-------.    ,-------| CAPS | Left | Down |  Up  |Right | VOL- |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  | F10  | F11  | F12  |-------|    |-------|   +  |   -  |   =  |   [  |   ]  |   \  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LOWER|LGUI  | /Space  /       \Enter \  |BackSP| RAISE| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_RAISE] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                        KC_PSCR, KC_SCRL, KC_PAUSE, KC_INS, KC_HOME, KC_PGUP,
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_MPRV, KC_MPLY, KC_MNXT, KC_DEL, KC_END, KC_PGDN,
  _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                        KC_CAPS, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, _______,
  _______, KC_PLUS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC,_______, KC_DELETE, KC_WREF, KC_VOLU, KC_VOLD,  KC_MUTE,   _______,  _______,
                             _______, _______, _______,  _______, _______,  _______, _______, _______
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | BOOT |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |   MODE+   | HUE+ | SAT+ |SPEED+|
 * |------+------+------+------+------+------|       |    |RGB ON |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      | MODE- | HUE- | SAT- |SPEED-|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LOWER|LGUI  | /Space  /       \Enter \  |BackSP| RAISE| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT(
  QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SLEP,                   KC_WAKE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
  _______, XXXXXXX, KC_BRIU, XXXXXXX, XXXXXXX, XXXXXXX,                    RGB_MOD, RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI,_______,
  _______, XXXXXXX, KC_BRID, KC_MYCM, KC_CALC, XXXXXXX,                    RGB_RMOD, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD,_______,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
                             _______, _______, _______, _______, _______,  _______, _______, _______
  ),
  /* NUMPAD
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LOWER|LGUI  | /Space  /       \Enter \  |BackSP| RAISE| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_NUMPAD] = LAYOUT(
  KC_F1,  KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,                   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  _______, KC_NUM, KC_KP_7, KC_KP_8, KC_KP_9, XXXXXXX,                   XXXXXXX, KC_KP_ASTERISK, KC_KP_SLASH, _______, _______, _______,
  _______, KC_KP_0, KC_KP_4, KC_KP_5, KC_KP_6, KC_F5,                   XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
  _______, KC_KP_DOT, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_ENTER, XXXXXXX, XXXXXXX,XXXXXXX, KC_KP_EQUAL, KC_KP_PLUS, KC_KP_MINUS, XXXXXXX, XXXXXXX,
                             _______, _______, _______, _______, _______,  _______, _______, _______
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE
static uint32_t splash_start_time;
static bool     splash_done = false;


oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  splash_start_time = timer_read32();
  splash_done       = false;
  if (is_keyboard_master())
    return OLED_ROTATION_270;  // flips the display 180 degrees if offhand
  return rotation;
}


// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);
#define OLED_FONT_H "lib/glcdfont_lily.c"



bool oled_task_user(void) {
  if (!splash_done) {
    oled_set_brightness(128);
    // Calculate elapsed time since init
    uint32_t elapsed = timer_elapsed32(splash_start_time);
    if (elapsed < 2500) {
        // Still within first 5 seconds: draw splash
        if (is_keyboard_master()) oled_write_raw_P(ALISH_LOGO_270, sizeof(ALISH_LOGO_270));
        else oled_write_raw_P(ALISH_LOGO_0, sizeof(ALISH_LOGO_0));
    } else {
        // 5 seconds have passed: bail out of splash
        splash_done = true;
        oled_clear();
        oled_render_dirty(true);
    }
} else {
  if (last_input_activity_elapsed() > OLED_TIMEOUT) {
      oled_off();
  } else {
      oled_on();
  }
  // display_housekeeping_task();
    if (is_keyboard_master()) {
        oled_clear();
        oled_set_cursor(0,1);
        uint8_t n = get_current_wpm();
        char    wpm_counter[4];
        wpm_counter[3] = '\0';
        wpm_counter[2] = '0' + n % 10;
        wpm_counter[1] = (n /= 10) % 10 ? '0' + (n) % 10 : (n / 10) % 10 ? '0' : ' ';
        wpm_counter[0] = n / 10 ? '0' + n / 10 : ' ';
        oled_write_P(PSTR("WPM:"), false);
        oled_write(wpm_counter, false);
        oled_set_cursor(0,3);
        char buffer[16];
        snprintf(buffer, sizeof(buffer), "oled: %d", OLED_TIMEOUT);
        oled_write_ln(buffer, false);
        led_t led_state = host_keyboard_led_state();
        if(led_state.caps_lock) {
          // oled_set_cursor(0,6);
          // oled_write_raw_P(CAPS_LOGO, sizeof(CAPS_LOGO));
          oled_set_cursor(0,10);
          oled_write_ln("CAPS",false);
        }
        if(led_state.num_lock) {
          // oled_set_cursor(3,6);
          // oled_write_raw_P(NUM_LOGO, sizeof(NUM_LOGO));
          oled_set_cursor(0,11);
          oled_write_ln("NumLk",false);
        }
        // char lock_status[4]; // C, N, S, null terminator
    
        // lock_status[0] = led_state.caps_lock   ? 'C' : ' ';
        // lock_status[1] = led_state.num_lock    ? 'N' : ' ';
        // lock_status[2] = led_state.scroll_lock ? 'S' : ' ';
        // lock_status[3] = '\0'; // End string
    
        // oled_write_ln(lock_status, false);

        oled_set_cursor(0,12);
        switch (get_highest_layer(layer_state)) {
          case _QWERTY:
            oled_write_raw_P(bmp_big_B, sizeof(bmp_big_B));
            break;
          case _RAISE:
            oled_write_raw_P(bmp_big_R, sizeof(bmp_big_R));
            break;
          case _LOWER:
            oled_write_raw_P(bmp_big_L, sizeof(bmp_big_L));
            break;
          case _ADJUST:
            oled_write_raw_P(bmp_big_A, sizeof(bmp_big_A));
            break;
          case _NUMPAD:
            oled_write_raw_P(bmp_big_N, sizeof(bmp_big_N));
            break;
          default:
            oled_write_raw_P(bmp_big_U, sizeof(bmp_big_U));
            break;
          }
        // oled_set_cursor(0,3);
        // oled_write_ln(read_layer_state(), false);
        // char buffer[16];
        // snprintf(buffer, sizeof(buffer), "Lines: %d", oled_max_lines());
        // oled_set_cursor(0,5);
        // oled_write_ln(buffer, false);
        // char buffer2[16];
        // snprintf(buffer, sizeof(buffer2), "chars: %d", oled_max_chars());
        // oled_set_cursor(0,7);
        // oled_write_ln(buffer, false);
        
        
    } else {
      render_bongocat();
    }
  }
    return false;
}
// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//   if (record->event.pressed) {
//       extern uint32_t tap_timer;
//       tap_timer = timer_read32();
//   }
//   return true;
// }
#endif // OLED_DRIVER_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
      case MO(_LOWER):
          if (record->event.pressed) {
              uint16_t now = timer_read();

              // If last tap was over 1.5s ago, reset count
              if (timer_elapsed(last_tap_time) > 500) {
                  tap_count = 0;
              }

              tap_count++;
              last_tap_time = now;

              if (tap_count >= 5) {
                  // Toggle the layer
                  if (layer_state_is(_NUMPAD)) {
                      layer_off(_NUMPAD);
                  } else {
                      layer_on(_NUMPAD);
                  }

                  tap_count = 0; // Reset counter after switching
                  return false;
              }
          }
          // return false; // Skip normal processing of this key
  }
  return true;
}

void oled_render_boot(bool bootloader) {
  oled_clear();
      if (bootloader) {
          oled_write_P(PSTR("Awaiting New Firmware "), false);
      } else {
          oled_write_P(PSTR("Rebooting "), false);
      }

  oled_render_dirty(true);
}

bool shutdown_user(bool jump_to_bootloader) {
  oled_render_boot(jump_to_bootloader);
  return jump_to_bootloader;
}

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//   if (record->event.pressed) {
// #ifdef OLED_ENABLE
//     set_keylog(keycode, record);
// #endif
//     // set_timelog();
//   }

//   switch (keycode) {
//     case L_BASE:
//       if (record->event.pressed) {
//         set_single_persistent_default_layer(_QWERTY);
//       }
//       return false;
//       break;
//     case L_LOWER:
//       if (record->event.pressed) {
//         layer_on(_LOWER);
//         update_tri_layer(_LOWER, _RAISE, _ADJUST);
//       } else {
//         layer_off(_LOWER);
//         update_tri_layer(_LOWER, _RAISE, _ADJUST);
//       }
//       return false;
//       break;
//     case L_RAISE:
//       if (record->event.pressed) {
//         layer_on(_RAISE);
//         update_tri_layer(_LOWER, _RAISE, _ADJUST);
//       } else {
//         layer_off(_RAISE);
//         update_tri_layer(_LOWER, _RAISE, _ADJUST);
//       }
//       return false;
//       break;
//     case L_ADJUST:
//         if (record->event.pressed) {
//           layer_on(_ADJUST);
//         } else {
//           layer_off(_ADJUST);
//         }
//         return false;
//         break;
//   }
//   return true;
// }