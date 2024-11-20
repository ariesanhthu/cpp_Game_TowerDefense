#pragma once
#include "Game/cgame.h"
#include "genSetUP.h"
#include <thread>
#include <chrono>

#include <windows.h>
#include <TowerDefense.h>

// Alphabet A-Z
#define KEY_A 65
#define KEY_B 66
#define KEY_C 67
#define KEY_D 68
#define KEY_E 69
#define KEY_F 70
#define KEY_G 71
#define KEY_H 72
#define KEY_I 73
#define KEY_J 74
#define KEY_K 75
#define KEY_L 76
#define KEY_M 77
#define KEY_N 78
#define KEY_O 79
#define KEY_P 80
#define KEY_Q 81
#define KEY_R 82
#define KEY_S 83
#define KEY_T 84
#define KEY_U 85
#define KEY_V 86
#define KEY_W 87
#define KEY_X 88
#define KEY_Y 89
#define KEY_Z 90

// Numbers 0-9
#define KEY_0 48
#define KEY_1 49
#define KEY_2 50
#define KEY_3 51
#define KEY_4 52
#define KEY_5 53
#define KEY_6 54
#define KEY_7 55
#define KEY_8 56
#define KEY_9 57

// Special Characters
#define KEY_SPACE 32
#define KEY_EXCLAMATION 33    // !
#define KEY_AT 64             // @
#define KEY_HASH 35           // #
#define KEY_DOLLAR 36         // $
#define KEY_PERCENT 37        // %
#define KEY_CARET 94          // ^
#define KEY_AMPERSAND 38      // &
#define KEY_ASTERISK 42       // *
#define KEY_LEFT_PAREN 40     // (
#define KEY_RIGHT_PAREN 41    // )
#define KEY_MINUS 45          // -
#define KEY_UNDERSCORE 95     // _
#define KEY_PLUS 43           // +
#define KEY_EQUAL 61          // =
#define KEY_LEFT_BRACKET 91   // [
#define KEY_RIGHT_BRACKET 93  // ]
#define KEY_LEFT_CURLY 123    // {
#define KEY_RIGHT_CURLY 125   // }
#define KEY_SEMICOLON 59      // ;
#define KEY_COLON 58          // :
#define KEY_QUOTE 39          // '
#define KEY_DOUBLE_QUOTE 34   // "
#define KEY_COMMA 44          // ,
#define KEY_PERIOD 46         // .
#define KEY_SLASH 47          // /
#define KEY_BACKSLASH 92      // \
#define KEY_PIPE 124          // |
#define KEY_LESS_THAN 60      // <
#define KEY_GREATER_THAN 62   // >
#define KEY_QUESTION 63       // ?
#define KEY_TILDE 126         // ~
#define KEY_GRAVE 96          // `

// Control Keys
#define KEY_ESC 27            // Escape
#define KEY_ENTER 13          // Enter
#define KEY_BACKSPACE 8       // Backspace
#define KEY_TAB 9             // Tab
#define KEY_DELETE 127        // Delete

// Arrow Keys (use _getch() to read twice in Windows)
#define KEY_ARROW_PREFIX 224  // Prefix for arrow keys
#define KEY_UP 72             // Arrow Up
#define KEY_DOWN 80           // Arrow Down
#define KEY_LEFT 75           // Arrow Left
#define KEY_RIGHT 77          // Arrow Right
