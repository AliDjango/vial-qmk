VIA_ENABLE = yes
VIAL_ENABLE = yes
SRC += usb_recovery.c
WPM_ENABLE = yes
LTO_ENABLE = yes            # Link Time Optimization enabled
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes        # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes            # N-Key Rollover
NKRO_DEFAULT_ON = yes
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output
RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight.
SWAP_HANDS_ENABLE = no      # Enable one-hand typing
OLED_ENABLE = yes           # OLED display
OPENRGB_ENABLE = yes
VIALRGB_ENABLE = yes
RGB_MATRIX_ENABLE = yes
SPLIT_TRANSPORT = serial  # or i2c, depending on your hardware
# Keep ChibiOS suspend handling; USB recovery also runs from its suspend hook.
NO_USB_STARTUP_CHECK = no
# Let initialization finish even when the hub has not enumerated the device.
USB_WAIT_FOR_ENUMERATION = no

# RAW_ENABLE = yes #NEVER ENABLE IN VIAL
Link_Time_Optimization = yes # Reduce size of firmware by optimizing at link time
EXTRAFLAGS += -flto

# If you want to change the display of OLED, you need to change here
SRC +=  ./lib/rgb_state_reader.c \
        ./lib/layer_state_reader.c \
        ./lib/logo_reader.c \
        ./lib/keylogger.c \
        # ./lib/bongocat.c  \
        # ./lib/mode_icon_reader.c \
        # ./lib/host_led_state_reader.c \
        # ./lib/timelogger.c \
