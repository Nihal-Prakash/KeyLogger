# Linux Keyboard Event Logger (Raw Input, C)

A low-level C program that reads **raw keyboard events directly from the Linux kernel** and prints human-readable key names when keys are pressed.

This project intentionally avoids X11, Wayland, GUI toolkits, or higher-level libraries. It communicates directly with `/dev/input/event*` devices to understand how keyboard input actually flows from hardware to user space on Linux.

---

## What this project can do

- Read **raw keyboard events** from Linux input devices
- Detect **key press events** (not releases or repeats)
- Translate Linux key codes (`KEY_A`, `KEY_ENTER`, `KEY_F1`, etc.) into readable strings
- Print key presses in real time
- Work independently of desktop environment (X11 / Wayland / TTY)

---

## What this project does NOT do (by design)

- Does **not** convert keys into characters (`a` vs `A`, `1` vs `!`)
- Does **not** track modifier state (Shift, Ctrl, Alt combinations)
- Does **not** hook into GUI frameworks or input methods
- Does **not** attempt stealth, persistence, or background execution

This is a **kernel-input learning project**, not a text logger.

---

## Why this project exists

Most keyboard-related examples rely on:
- X11 hooks
- GUI libraries
- Desktop-specific APIs

Those abstractions hide how Linux **actually delivers input events**.

This project exists to understand:
- The Linux input subsystem
- What `/dev/input/event*` devices contain
- How `struct input_event` is produced by the kernel
- How raw device input differs from character input

---

## Why this was hard

Working with raw input devices on Linux is non-trivial:

1. **No characters, only codes**  
   The kernel emits numeric key codes, not characters.  
   Mapping them correctly requires understanding `input-event-codes.h`.

2. **Strict permissions**  
   `/dev/input/event*` devices require root access or custom udev rules.

3. **Multiple event types**  
   A single key interaction generates:
   - press
   - release
   - repeat  
   These must be filtered explicitly.

4. **No standard translation helpers**  
   There is no built-in libc function to convert key codes to readable names.

This project deliberately handles these issues directly instead of hiding them.

---

## How it works (high-level flow)

1. Open a Linux input device file (`/dev/input/eventX`)
2. Continuously read `struct input_event` from the kernel
3. Filter only:
   - `EV_KEY` events
   - `value == 1` (key pressed)
4. Translate the numeric key code using a `switch` mapping
5. Print the readable key name to stdout

---

## Build instructions

### Requirements
- Linux
- GCC or Clang
- Kernel input headers (`linux/input.h`)

### Compile

```bash
gcc -O2 -Wall -Wextra main.c -o keylogger
