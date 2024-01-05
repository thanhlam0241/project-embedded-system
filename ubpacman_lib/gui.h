//--------------------------------------------------------------
// File     : gui.h
//--------------------------------------------------------------

//--------------------------------------------------------------
#ifndef __STM32F4_UB_GUI_H
#define __STM32F4_UB_GUI_H


//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "stm32f4xx.h"
#include "stm32_ub_lcd_ili9341.h"
#include "stm32_ub_graphic2d.h"
#include "stm32_ub_font.h"
#include "stm32_ub_touch_stmpe811.h"
#include "stm32_ub_systick.h"
#include "stm32_ub_uart.h"
#include "stm32_ub_button.h"
#include "stm32_ub_usb_hid_host.h"
#include "pacman.h"
#include "maze.h"
#include "skin.h"
#include "player.h"
#include "blinky.h"
#include "pinky.h"
#include "inky.h"
#include "clyde.h"




//--------------------------------------------------------------
// gui structure
//--------------------------------------------------------------
typedef struct {
  uint32_t refresh_value;
  uint32_t refresh_buttons;
}GUI_t;
GUI_t GUI;


//--------------------------------------------------------------
// UART debug
//--------------------------------------------------------------
#define  USE_GUI_UART_DEBUG    0  // 1=enable, 0=disble debug over uart


//--------------------------------------------------------------
// color defines
//--------------------------------------------------------------
#define  BACKGROUND_COL     RGB_COL_BLACK

#define  ROOM_COL        RGB_COL_GREY
#define  WALL_COL        RGB_COL_BLUE
#define  ERR_COL         RGB_COL_RED
#define  BUTTON_COL_OFF  RGB_COL_BLUE
#define  BUTTON_COL_ON   RGB_COL_RED
#define  FONT_COL        RGB_COL_BLUE
#define  FONT_COL2       RGB_COL_YELLOW
#define  FONT_COL3       RGB_COL_GREY





//--------------------------------------------------------------
// screen positions
//--------------------------------------------------------------
#define  GUI_MAZE_STARTX  8
#define  GUI_MAZE_STARTY  5

#define  GUI_BTN_UP_X   170
#define  GUI_BTN_UP_Y   255

#define  GUI_BTN_DOWN_X   170
#define  GUI_BTN_DOWN_Y   280

#define  GUI_BTN_RIGHT_X   200
#define  GUI_BTN_RIGHT_Y   270

#define  GUI_BTN_LEFT_X   140
#define  GUI_BTN_LEFT_Y   270

//--------------------------------------------------------------
#define  GUI_JOY_NONE    0
#define  GUI_JOY_UP      1
#define  GUI_JOY_RIGHT   2
#define  GUI_JOY_DOWN    3
#define  GUI_JOY_LEFT    4


//--------------------------------------------------------------
#define  GUI_TOUCH_INTERVALL_MS    50


//--------------------------------------------------------------
#define  GUI_REFRESH_VALUE   3  // dont change this value



//--------------------------------------------------------------
// Globale Funktionen
//--------------------------------------------------------------
void gui_clear_screen(void);
void gui_draw_debugmaze(void);
void gui_draw_maze(void);
void gui_draw_errmaze(void);
void gui_clear_bots(void);
void gui_draw_bots(void);
void gui_draw_gui(uint32_t joy);
uint32_t gui_check_touch(void);
uint32_t gui_check_button(void);
uint32_t gui_check_keyboard(void);
void gui_draw_buttons(uint32_t joy);
void gui_debug_uart(char *ptr);



//--------------------------------------------------------------
#endif // __STM32F4_UB_GUI_H
