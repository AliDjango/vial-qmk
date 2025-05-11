#pragma once

#define OLED_FONT_H "lib/glcdfont_lily.c"

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1

#define I2C_DRIVER I2CD0 // I2CD1 = I2C1
#define I2C1_SDA_PIN GP12
#define I2C1_SCL_PIN GP13


//#define WS2812_LED_COUNT 58

//#define RGBLIGHT_LED_COUNT 58


//#define SPLIT_POINTING_ENABLE
#define MASTER_RIGHT

#define SERIAL_USART_PIN_SWAP

/* any side can be master by default, enable split sync to support it */
#define EE_HANDS
#define SPLIT_POINTING_ENABLE