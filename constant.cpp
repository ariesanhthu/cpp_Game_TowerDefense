#pragma once

#ifndef __constant_h__
#define __constant_h__


#include <iostream>

// window variable 
 const  int SCALE_FACTOR = 3;
 const  int CELL_SIZE = 1;            // Pixel size
 const  int GAME_WIDTH = 395 * 3;     // Width in cells
 const  int GAME_HEIGHT = 213 * 3;    // Height in cells
 const  int TIMER_INTERVAL = 30;      // Timer interval in milliseconds
#define WM_INIT_SCREEN (WM_USER + 1) 
#define VM_CLEAR_SCREEN (WM_USER + 2)

// Bitmap file paths
//===========================================================================//
// MAIN SCREEN

// COVER 
// Background 
 const  wchar_t* BMP_BACKGROUND_MAINSCREEN = L"Assets/map/map/map4.bmp";
// board
 const  wchar_t* BMP_BOARD = L"Assets/board/board/board.bmp";

// MENU OPTION 
// Button 
 const  wchar_t* BMP_BUTTON = L"Assets/button/button/button_up.bmp";
// Hover effect
 const  wchar_t* BMP_SELECTING_BUTTON = L"Assets/button/button/selectbox.bmp";
// Onclick effect 
 const  wchar_t* BMP_ONCLICK_BUTTON = L"Assets/button/button/button_down.bmp";
// login buton 
 const  wchar_t* BMP_LOGIN_BUTTON;
// login hover effect
 const  wchar_t* BMP_LOGIN_BUTTON_SELECT;
// login onclick effect
 const  wchar_t* BMP_LOGIN_ONCLICK_BUTTON;

// MENU CHOOSE MAP
// option 
 const  wchar_t* BMP_MAP_OPTION_1 = L"Assets/map/map/map1_scaleDown.bmp";
 const  wchar_t* BMP_MAP_OPTION_2 = L"Assets/map/map/map2_scaleDown.bmp";
 const  wchar_t* BMP_MAP_OPTION_3 = L"Assets/map/map/map3_scaleDown.bmp";
 const  wchar_t* BMP_MAP_OPTION_4 = L"Assets/map/map/map4_scaleDown.bmp";
// border hover
 const  wchar_t* BMP_BORDER = L"Assets/board/board/border.bmp";
// enter button
 const  wchar_t* BMP_ENTER_BUTTON;

// MENU CONTINUE 

// MENU LEADERBOARD

// MENU SETTING

// MENU ABOUTUS





// GAME SCREEN
//MANAGE GAME LOGIC
 bool PAUSE = false;
 unsigned int GAME_TICK = 64;
 unsigned int TIME_PER_TICK = (1000000 / GAME_TICK); // microsecond
 unsigned int FPS = 30;
 unsigned int TIME_PER_FPS = (1000000 / FPS); // microsecond

//#define micro(x) chrono::microseconds(x)
//#define micro_cast(x) chrono::duration_cast<chrono::microseconds> (x)
//#define time_point chrono::system_clock::time_point

// MAP1 

// MAP2 

// MAP3

// MAP4






// LOGIN SCREEN 






//===========================================================================//
#endif // !__ const ant_h__