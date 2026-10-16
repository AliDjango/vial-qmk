# Lily58LP Vial USB recovery

Build with `make lily58lp:vial` from the QMK root, or use
`compile_lily58lp.sh`. Flash the same newly built UF2 to **both halves**.
The split watchdog adds a communication transaction, so both halves must use
matching firmware. The existing EEPROM handedness is still used.

## Recovery behavior

- If USB is not ready during startup and both halves become secondaries, the
  split watchdog resets an unpaired secondary after five seconds and retries
  USB detection. Detection itself can take another two seconds.
- The primary retries USB enumeration after ten seconds without configuration,
  including when failed enumeration leaves it suspended.
- Ordinary laptop sleep does not trigger periodic USB disconnects. If the
  laptop is awake but USB remains stuck suspended, hold any key on the
  **USB-connected half** for at least three seconds to restart its USB
  connection. This fallback needs the firmware's suspend loop to be running.
- Recovery runs independently of OLED rendering.

After flashing both halves, verify typing, shut the laptop down with the
keyboard still connected, then boot it again. Allow about fifteen seconds
after the operating system starts. Repeat, and also check sleep and wake.
If automatic recovery fails, try the held-key fallback before unplugging USB.

Software simulations cover role detection, watchdog timing and handshakes,
enumeration retries, normal suspend, held-key recovery, and timer wraparound.
They do not replace the laptop power-cycle check.
