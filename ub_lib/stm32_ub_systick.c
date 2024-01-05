//--------------------------------------------------------------
// File     : stm32_ub_systick.c
// Datum    : 12.11.2013
// Version  : 1.0
// Autor    : UB
// EMail    : mc-4u(@)t-online.de
// Web      : www.mikrocontroller-4u.de
// CPU      : STM32F429
// IDE      : CooCox CoIDE 1.7.4
// GCC      : 4.7 2012q4
// Module   : keine
// Funktion : Pausen- Timer- und Counter-Funktionen
//            Zeiten im [us,ms,s] Raster
//--------------------------------------------------------------

//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "stm32_ub_systick.h"



#if ((SYSTICK_RESOLUTION!=1) && (SYSTICK_RESOLUTION!=1000))
  #error print WRONG SYSTICK RESOLUTION !
#endif


//--------------------------------------------------------------
// Globale Pausen-Variabeln
//--------------------------------------------------------------
static volatile uint32_t Systick_Delay;  // Globaler Pausenzaehler





//--------------------------------------------------------------
// Init vom System-Counter
// entweder im 1us-Takt oder 1ms-Takt
//--------------------------------------------------------------
void UB_Systick_Init(void) {
  RCC_ClocksTypeDef RCC_Clocks;

  // alle Variabeln zur�cksetzen
  Systick_Delay=0;
  keyboard_timer=0;
  Player_Systick_Timer_ms=0;
  Gui_Touch_Timer_ms=0;
  Blinky_Systic_Timer_ms=0;
  Mode_Systic_Timer_ms=0;
  akt_usb_status=USB_HID_DEV_DETACHED;


  #if SYSTICK_RESOLUTION==1
    // Timer auf 1us einstellen
    RCC_GetClocksFreq(&RCC_Clocks);
    SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000000);
  #else
    // Timer auf 1ms einstellen
    RCC_GetClocksFreq(&RCC_Clocks);
    SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);
  #endif
}


#if SYSTICK_RESOLUTION==1
//--------------------------------------------------------------
// Pausenfunktion (in us)
// die CPU wartet bis die Zeit abgelaufen ist
//--------------------------------------------------------------
void UB_Systick_Pause_us(volatile uint32_t pause)
{

  Systick_Delay = pause;

  while(Systick_Delay != 0);
}
#endif


//--------------------------------------------------------------
// Pausenfunktion (in ms)
// die CPU wartet bis die Zeit abgelaufen ist
//--------------------------------------------------------------
void UB_Systick_Pause_ms(volatile uint32_t pause)
{
  #if SYSTICK_RESOLUTION==1
    uint32_t ms;

    for(ms=0;ms<pause;ms++) {
      UB_Systick_Pause_us(1000);
    }
  #else
    Systick_Delay = pause;

    while(Systick_Delay != 0);
  #endif
}


//--------------------------------------------------------------
// Pausenfunktion (in s)
// die CPU wartet bis die Zeit abgelaufen ist
//--------------------------------------------------------------
void UB_Systick_Pause_s(volatile uint32_t pause)
{
  uint32_t s;

  for(s=0;s<pause;s++) {
    UB_Systick_Pause_ms(1000);
  }
}





//--------------------------------------------------------------
// Systic-Interrupt
//--------------------------------------------------------------
void SysTick_Handler(void)
{
  // Tick f�r Pause
  if(Systick_Delay != 0x00) {
    Systick_Delay--;
  }

  // USB bearbeiten
  akt_usb_status=UB_USB_HID_HOST_Do();

  // Keyboard Timer
  if(keyboard_timer!=0) keyboard_timer--;

  if(Gui_Touch_Timer_ms!=0) {
    Gui_Touch_Timer_ms--;
  }

  if(Mode_Systic_Timer_ms!=0) {
    Mode_Systic_Timer_ms--;
  }

  if(Player_Systick_Timer_ms!=0) {
    Player_Systick_Timer_ms--;
  }

  if(Blinky_Systic_Timer_ms!=0) {
    Blinky_Systic_Timer_ms--;
  }

  if(Pinky_Systic_Timer_ms!=0) {
    Pinky_Systic_Timer_ms--;
  }

  if(Inky_Systic_Timer_ms!=0) {
    Inky_Systic_Timer_ms--;
  }

  if(Clyde_Systic_Timer_ms!=0) {
    Clyde_Systic_Timer_ms--;
  }
}


