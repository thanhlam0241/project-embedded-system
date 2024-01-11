//--------------------------------------------------------------
// File     : pacman.h
//--------------------------------------------------------------

//--------------------------------------------------------------
#ifndef __STM32F4_UB_PACMAN_H
#define __STM32F4_UB_PACMAN_H


//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "misc.h"
#include "stm32_ub_lcd_ili9341.h"
#include "stm32_ub_graphic2d.h"
#include "stm32_ub_touch_stmpe811.h"
#include "maze.h"
#include "maze_generate.h"
#include "gui.h"
#include "stm32_ub_font.h"
#include "stm32_ub_systick.h"
#include "menu.h"
#include "stm32_ub_usb_hid_host.h"


//--------------------------------------------------------------
// level structur
//--------------------------------------------------------------
typedef struct {
  uint32_t player_speed;
  uint32_t blinky_speed;
  uint32_t pinky_speed;
  uint32_t inky_speed;
  uint32_t clyde_speed;
}Level_t;

#define  GAME_MAX_LEVEL   10


//--------------------------------------------------------------
// Einstellungen fuer TIMER und NVIC
// Timer7
// F_TIM = 84 MHz / (prescaler+1) / (periode+1)
// Soll-Frq = 1kHz (1ms)
//--------------------------------------------------------------
#define   TILED_TIMER_NAME        TIM7
#define   TILED_TIMER_CLK         RCC_APB1Periph_TIM7
#define   TILED_TIMER_PRESCALE    41
#define   TILED_TIMER_PERIOD      1999
#define   TILED_TIMER_IRQ         TIM7_IRQn
#define   TILED_TIMER_IRQHANDLER  TIM7_IRQHandler


//--------------------------------------------------------------
#define  GAME_MODE_TIMER       100  // 100ms
#define  GAME_SCATTER_TIME     70   // (70*100ms) 7sec
#define  GAME_CHASE_TIME       200  // (200*100ms) 20sec
#define  GAME_FRIGHTENED_TIME  60   // (60*100ms) 6sec
#define  GAME_FRIGHTENED_BLINK 20   // (20*100ms) 2sec


//--------------------------------------------------------------
#define  GAME_POINTS_NORMAL  10
#define  GAME_POINTS_ENERGY  50



//--------------------------------------------------------------
#define  GAME_FRIGHTENED_START_POINTS  200


//--------------------------------------------------------------
#define  GAME_RUN          0
#define  GAME_PLAYER_WIN   1
#define  GAME_PLAYER_LOSE  2
#define  GAME_OVER         3

//--------------------------------------------------------------
#define  MOVE_NOBODY  0x00  
#define  MOVE_PLAYER  0x01  // Bit0
#define  MOVE_BLINKY  0x02  // Bit1
#define  MOVE_PINKY   0x04  // Bit2
#define  MOVE_INKY    0x08  // Bit3
#define  MOVE_CLYDE   0x10  // Bit4


//--------------------------------------------------------------
#define  BOOL_FALSE   0
#define  BOOL_TRUE    1    


//--------------------------------------------------------------
#define  GAME_CONTROL_TOUCH    0
#define  GAME_CONTROL_4BUTTON  1
 

//--------------------------------------------------------------
#define  GAME_MODE_SCATTER     0
#define  GAME_MODE_CHASE       1


//--------------------------------------------------------------
// Main Game Structure
//--------------------------------------------------------------
typedef struct {
  uint32_t collision;
  uint32_t controller;
  uint32_t mode;
  uint32_t mode_timer;
  uint32_t frightened;
  uint32_t frightened_timer;
  uint32_t frightened_points;
  uint32_t debug_mode;
  uint32_t numberOfBots;
}Game_t;
Game_t Game;



//--------------------------------------------------------------
// Globale Funktionen
//--------------------------------------------------------------
void pacman_start(void);
uint32_t pacman_hw_init(void);
void pacman_init(uint32_t mode);
void pacman_set_level(void);
uint32_t pacman_play(void);
void pacman_dec_mode_timer(void);

void UB_Tiled_1ms_ISR_CallBack(void);        // Diese Funktion muss extern benutzt werden !!
void UB_Tiled_Input_Device_CallBack(void);   // Diese Funktion muss extern benutzt werden !!
void UB_Tiled_LCD_CallBack(void);            // Diese Funktion muss extern benutzt werden !!
void UB_Tiled_Event_CallBack(void);          // Diese Funktion muss extern benutzt werden !!




//--------------------------------------------------------------
#endif // __STM32F4_UB_PACMAN_H
