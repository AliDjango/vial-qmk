#!/bin/bash

# === CONFIGURATION ===
KEYBOARD="lily58lp"    # e.g., "crkbd/rev1"
KEYMAP="vial"            # e.g., "default"
UF2_FILENAME="${KEYBOARD}_${KEYMAP}.uf2"
BUILD_PATH="/home/alish/vial-qmk/"
MOUNT_POINT=""

# === BUILD ===
echo "🔧 Building QMK firmware..."
cd "/home/alish/vial-qmk"
make "$KEYBOARD:$KEYMAP" -j 8 || { echo "❌ Build failed"; exit 1; }

# === FIND UF2 FILE ===
UF2_PATH=$(find "$BUILD_PATH" -name "$UF2_FILENAME" | head -n 1)
if [[ ! -f "$UF2_PATH" ]]; then
    echo "❌ UF2 file not found. Did the build succeed? expected file name $UF2_FILENAME"
    exit 1
fi

# === FIND RP2040 MOUNT ===
echo "🔍 Looking for RP2040 device..."
for i in /media/$USER/* /run/media/$USER/* /Volumes/*; do
    if [[ -d "$i" && -f "$i/INFO_UF2.TXT" ]]; then
        MOUNT_POINT="$i"
        break
    fi
done

# Prompt if not found
if [[ -z "$MOUNT_POINT" ]]; then
    echo "⚠️ RP2040 not found. Please put it into BOOTSEL mode and press enter..."
    read -r
    for i in /media/$USER/* /run/media/$USER/* /Volumes/*; do
        if [[ -d "$i" && -f "$i/INFO_UF2.TXT" ]]; then
            MOUNT_POINT="$i"
            break
        fi
    done
fi

# Still not found?
if [[ -z "$MOUNT_POINT" ]]; then
    echo "❌ RP2040 device not found. Exiting."
    exit 1
fi

# === COPY UF2 ===
echo "📁 Copying firmware $UF2_FILENAME to $MOUNT_POINT"
cp "$UF2_FILENAME" "$MOUNT_POINT" && echo "✅ Firmware flashed!" || echo "❌ Copy failed"

