////--------------------------------------------------------------
//// File     : stm32_ub_tiled.h
////--------------------------------------------------------------
//
////--------------------------------------------------------------
//#ifndef __STM32F4_UB_TILED_H
//#define __STM32F4_UB_TILED_H
//
//
////--------------------------------------------------------------
//// Includes
////--------------------------------------------------------------
//#include "stm32f4xx.h"
//#include "stm32f4xx_tim.h"
//#include "misc.h"
////#include "stm32_ub_tiled_map.h"
////#include "stm32_ub_tiled_player.h"
////#include "stm32_ub_tiled_obj.h"
//
//
//
////--------------------------------------------------------------
//// Timings [USER_01]
//// (alle Angaben in ms)
////--------------------------------------------------------------
//#define   TILED_LCD_REFRESH_MS      50  // Display-Refresh
//#define   TILED_OBJ_SPEED_MS        50  // Geschwindigkeit der Objekte
//#define   TILED_INPUT_DEVICE_MS     30  // Abfrage Geschwindigkeit vom Input Device
//
//
////--------------------------------------------------------------
//// USER : ab hier keine Aenderungen notwendig
////--------------------------------------------------------------
//
//
//
//
//
////--------------------------------------------------------------
//// Einstellungen fuer TIMER und NVIC
//// Timer7
//// F_TIM = 84 MHz / (prescaler+1) / (periode+1)
//// Soll-Frq = 1kHz (1ms)
////--------------------------------------------------------------
//#define   TILED_TIMER_NAME        TIM7
//#define   TILED_TIMER_CLK         RCC_APB1Periph_TIM7
//#define   TILED_TIMER_PRESCALE    41
//#define   TILED_TIMER_PERIOD      1999
//#define   TILED_TIMER_IRQ         TIM7_IRQn
//#define   TILED_TIMER_IRQHANDLER  TIM7_IRQHandler
//
//
////--------------------------------------------------------------
//// enum fuer Events
////--------------------------------------------------------------
//typedef enum {
//  TILED_EVENT_NONE =0,
//  TILED_EVENT_GOAL,
//  TILED_EVENT_DEADLY_TERRAIN,
//  TILED_EVENT_DEADLY_COLLISION,
//  TILED_EVENT_COLLECTABLE_COLLISION
//}TILED_EVENT_t;
//
//
////--------------------------------------------------------------
//// externe Struktur fuer Tiled
////--------------------------------------------------------------
//typedef struct {
//  uint32_t game_time_sec;    // abgelaufene Zeit seit PowerOn
//  TILED_EVENT_t event;       // aufgetretenes Event
//}TILED_t;
//TILED_t TILED;
//
//
////--------------------------------------------------------------
//// interne Struktur fuer Tiled
////--------------------------------------------------------------
//typedef struct {
//  bool enable;               // spiel enable oder disable
//  uint32_t lcd_refresh_cnt;  // Counter fuer LCD-Refresh
//  uint32_t game_time_cnt;    // Counter fuer Game-Zeit
//  uint32_t obj_speed_cnt;    // Counter fuer Objekt-Speed
//  uint32_t input_device_cnt; // Counter fuer Input Device
//  uint8_t obj_event;         // merker fuer Objekt Event
//  uint8_t player_event;      // merker fuer Player Event
//}TILED_GAME_t;
//
//
////--------------------------------------------------------------
//// Globale Funktionen
////--------------------------------------------------------------
//ErrorStatus UB_Tiled_Init(bool check_map);
//void UB_Tiled_Do(void);
//void UB_Tiled_Stop(void);
//TILED_DIR_t UB_Tiled_MovePlayer(TILED_DIR_t direction, uint32_t distance);
//bool UB_Tiled_CheckGoal(void);
//bool UB_Tiled_CheckDeadlyTerrain(void);
//bool UB_Tiled_CheckDeadlyCollision(uint32_t *obj_nr, uint8_t *obj_typ);
//bool UB_Tiled_CheckCollectableCollision(uint32_t *obj_nr, uint8_t *obj_typ);
//void UB_Tiled_DisableObjekt(uint32_t obj_nr);
//void UB_Tiled_EnableObjekt(uint32_t obj_nr);
////--------------------------------------------------------------
//// CallBack Funktionen fuer den User
////--------------------------------------------------------------
//void UB_Tiled_1ms_ISR_CallBack(void);        // Diese Funktion muss extern benutzt werden !!
//void UB_Tiled_Input_Device_CallBack(void);   // Diese Funktion muss extern benutzt werden !!
//void UB_Tiled_LCD_CallBack(void);            // Diese Funktion muss extern benutzt werden !!
//void UB_Tiled_Event_CallBack(void);          // Diese Funktion muss extern benutzt werden !!
//
//
//
////--------------------------------------------------------------
//#endif // __STM32F4_UB_TILED_H
