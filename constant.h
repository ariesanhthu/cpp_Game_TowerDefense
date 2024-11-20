#pragma once

#ifndef __constant_h__
#define __constant_h__


#include <iostream>

// window variable 
extern const  int SCALE_FACTOR;
extern const  int CELL_SIZE;            // Pixel size
extern const  int GAME_WIDTH;     // Width in cells
extern const  int GAME_HEIGHT;    // Height in cells
extern const  int TIMER_INTERVAL ;      // Timer interval in milliseconds
#define WM_INIT_SCREEN (WM_USER
#define VM_CLEAR_SCREEN (WM_USER + 2)

// Bitmap file paths
//===========================================================================//
// MAIN SCREEN

// COVER 
// Background 
extern const  wchar_t* BMP_BACKGROUND_MAINSCREEN;
// board
extern const  wchar_t* BMP_BOARD;

// MENU OPTION 
// Button 
extern const  wchar_t* BMP_BUTTON;
// Hover effect
extern const  wchar_t* BMP_SELECTING_BUTTON;
// Onclick effect 
extern const  wchar_t* BMP_ONCLICK_BUTTON;
// login buton 
extern const  wchar_t* BMP_LOGIN_BUTTON; 
// login hover effect
extern const  wchar_t* BMP_LOGIN_BUTTON_SELECT; 
// login onclick effect
extern const  wchar_t* BMP_LOGIN_ONCLICK_BUTTON;

// MENU CHOOSE MAP
// option 
extern const  wchar_t* BMP_MAP_OPTION_1;
extern const  wchar_t* BMP_MAP_OPTION_2;
extern const  wchar_t* BMP_MAP_OPTION_3;
extern const  wchar_t* BMP_MAP_OPTION_4;
// border hover
extern const  wchar_t* BMP_BORDER;
// enter button
extern const  wchar_t* BMP_ENTER_BUTTON;

// MENU CONTINUE 

// MENU LEADERBOARD

// MENU SETTING

// MENU ABOUTUS





// GAME SCREEN
//MANAGE GAME LOGIC
extern bool PAUSE;
extern unsigned int GAME_TICK;
extern unsigned int TIME_PER_TICK;
extern unsigned int FPS;
extern unsigned int TIME_PER_FPS;

#define micro chrono::microseconds
#define micro(x) chrono::microseconds(x)
#define micro_cast(x) chrono::duration_cast<chrono::microseconds> (x)
#define time_point chrono::system_clock::time_point

// MAP1 

// MAP2 

// MAP3

// MAP4






// LOGIN SCREEN 






//===========================================================================//
#endif // !__extern const ant_h__