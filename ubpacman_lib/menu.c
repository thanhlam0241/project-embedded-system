//--------------------------------------------------------------
// File     : menu.c
// Datum    : 22.11.2013
// Version  : 1.0
// Autor    : UB
// EMail    : mc-4u(@)t-online.de
// Web      : www.mikrocontroller-4u.de
// CPU      : STM32F429
// IDE      : CooCox CoIDE 1.7.4
// GCC      : 4.7 2012q4
// Module   : keine
// Funktion : Menu
//--------------------------------------------------------------


//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "menu.h"
#include <stdlib.h>
#include <stdio.h>

//--------------------------------------------------------------
// interne Funktionen
//--------------------------------------------------------------
void menu_redraw(uint32_t aktpos);
void menu_inc_value(uint32_t aktpos);
void menu_dec_value(uint32_t aktpos);

char key[20] = "";


//--------------------------------------------------------------
// init and start endless pacman gameplay
//--------------------------------------------------------------
void menu_start(void)
{
  uint32_t ok=0;
  uint32_t aktpos=0, aktiv=0;
  uint32_t joy=GUI_JOY_NONE;
  uint16_t srand_init=0;

  // init vom USB (als USB-HID-Host)
//  UB_USB_HID_HOST_Init();

  // init der Systick
//  UB_Systick_Init();

  GUI.refresh_value=GUI_REFRESH_VALUE;
  GUI.refresh_buttons=GUI_REFRESH_VALUE;

  gui_clear_screen();

  UB_Font_DrawString(60,5,"GAME PACMAN",&Arial_7x10,FONT_COL,BACKGROUND_COL);
  UB_Font_DrawString(30,20,"Hello World",&Arial_7x10,FONT_COL,BACKGROUND_COL);

  menu_redraw(aktpos);

  do {
    srand_init++;
    if(Gui_Touch_Timer_ms==0) {
      Gui_Touch_Timer_ms=GUI_TOUCH_INTERVALL_MS;
      joy=gui_check_touch();
      gui_draw_buttons(joy);
    }
    if(aktiv==0) {
      if(akt_usb_status==USB_HID_KEYBOARD_CONNECTED) {
    	  if(UB_USB_HID_HOST_GetKeyAnz()>0) {
    		    sprintf(key, "Pressed key %u",USB_KEY_DATA.akt_key1);
    	        // Nhan dang phim tu keyboard
    	        if(USB_KEY_DATA.akt_key1==79) {
    	        	menu_dec_value(aktpos);
    	        	menu_redraw(aktpos);
    	        	aktiv=1;
//    	        	if(aktpos==MENUE_MAX_POS) ok=1;
    	        }  // 79=cursor left
    	        if(USB_KEY_DATA.akt_key1==89) {
    	        	menu_inc_value(aktpos);
    	        	menu_redraw(aktpos);
    	        	aktiv=1;
    	        	if(aktpos==MENUE_MAX_POS) ok=1;
    	        } // 89=cursor right
    	        if(USB_KEY_DATA.akt_key1==83) {
    	        	if(aktpos>0) aktpos--;
    	        	menu_redraw(aktpos);
    	        	aktiv=1;
    	        }    // 83=cursor up
    	        if(USB_KEY_DATA.akt_key1==84) {
    	        	if(aktpos<MENUE_MAX_POS) aktpos++;
    	        	menu_redraw(aktpos);
    	        	aktiv=1;
    	        }  // 84=cursor down
    	        if(USB_KEY_DATA.akt_key1==43) {
    	        	if(aktpos==MENUE_MAX_POS) ok=1;
    	        	else menu_redraw(aktpos);
    	        	aktiv=1;
    	        }
    	        else {
    	        	menu_redraw(aktpos);
    	        	aktiv=1;
    	        }

    	        UB_Systick_Pause_ms(150);
    	  } else {}
      }
      else {
      if(joy==GUI_JOY_DOWN) {
        if(aktpos<MENUE_MAX_POS) aktpos++;
        menu_redraw(aktpos);
        aktiv=1;
      }
      else if(joy==GUI_JOY_UP) {
        if(aktpos>0) aktpos--;
        menu_redraw(aktpos);
        aktiv=1;
      }
      else if(joy==GUI_JOY_RIGHT) {
        menu_inc_value(aktpos);
        menu_redraw(aktpos);
        aktiv=1;
        if(aktpos==MENUE_MAX_POS) ok=1;
      }
      else if(joy==GUI_JOY_LEFT) {
        menu_dec_value(aktpos);
        menu_redraw(aktpos);
        aktiv=1;
        if(aktpos==MENUE_MAX_POS) ok=1;
      }
      }
    }
    else {
      if(joy==GUI_JOY_NONE) aktiv=0;
    }
  }
  while(ok==0);

  // init rand-function
  srand(srand_init);
}


//--------------------------------------------------------------
// redraw menu
//--------------------------------------------------------------
void menu_redraw(uint32_t aktpos)
{
  char buf[20];
  uint32_t yp,xp;
  uint32_t c[MENUE_MAX_POS+1];

  for(xp=0;xp<=MENUE_MAX_POS;xp++) {
    c[xp]=MENUE_COL_OFF;
  }

  c[aktpos]=MENUE_COL_ON;


  //-------------------------
  // left side
  //-------------------------

  xp=MENUE_STARTX1;
  yp=MENUE_STARTY;

  UB_Font_DrawString(xp,yp,key,&Arial_7x10,c[0],BACKGROUND_COL);

  yp+=MENUE_DELTA1;
  UB_Font_DrawString(xp,yp,"Controller      : ",&Arial_7x10,c[0],BACKGROUND_COL);

  yp+=MENUE_DELTA1;
  UB_Font_DrawString(xp,yp,"Startlevel      : ",&Arial_7x10,c[1],BACKGROUND_COL);

  yp+=MENUE_DELTA1;
  UB_Font_DrawString(xp,yp,"Blinky strategy : ",&Arial_7x10,c[2],BACKGROUND_COL);

  yp+=MENUE_DELTA1;
  UB_Font_DrawString(xp,yp,"Pinky strategy  : ",&Arial_7x10,c[3],BACKGROUND_COL);

  yp+=MENUE_DELTA1;
  UB_Font_DrawString(xp,yp,"Inky strategy   : ",&Arial_7x10,c[4],BACKGROUND_COL);

  yp+=MENUE_DELTA1;
  UB_Font_DrawString(xp,yp,"Clyde strategy  : ",&Arial_7x10,c[5],BACKGROUND_COL);

  yp+=MENUE_DELTA1+MENUE_DELTA1;
  UB_Font_DrawString(xp,yp,"Start",&Arial_7x10,c[6],BACKGROUND_COL);

  //-------------------------
  // right side
  //-------------------------

  xp=MENUE_STARTX2;
  yp=MENUE_STARTY;
  yp+=MENUE_DELTA1;
  if(Game.controller==GAME_CONTROL_TOUCH) {
    UB_Font_DrawString(xp,yp,"Touch   ",&Arial_7x10,MENUE_COL_VALUE,BACKGROUND_COL);
  }
  else {
    UB_Font_DrawString(xp,yp,"4 Button",&Arial_7x10,MENUE_COL_VALUE,BACKGROUND_COL);
  }

  yp+=MENUE_DELTA1;
  sprintf(buf,"%d ",(int)(Player.level));
  UB_Font_DrawString(xp,yp,buf,&Arial_7x10,MENUE_COL_VALUE,BACKGROUND_COL);

  yp+=MENUE_DELTA1;
  if(Blinky.strategy==GHOST_STRATEGY_RANDOM) {
    UB_Font_DrawString(xp,yp,"RANDOM ",&Arial_7x10,MENUE_COL_VALUE,BACKGROUND_COL);
  }
  else if(Blinky.strategy==GHOST_STRATEGY_BLINKY) {
    UB_Font_DrawString(xp,yp,"Blinky ",&Arial_7x10,MENUE_COL_VALUE,BACKGROUND_COL);
  }
  else if(Blinky.strategy==GHOST_STRATEGY_PINKY) {
    UB_Font_DrawString(xp,yp,"Pinky  ",&Arial_7x10,MENUE_COL_VALUE,BACKGROUND_COL);
  }
  else if(Blinky.strategy==GHOST_STRATEGY_INKY) {
    UB_Font_DrawString(xp,yp,"Inky   ",&Arial_7x10,MENUE_COL_VALUE,BACKGROUND_COL);
  }
  else {
    UB_Font_DrawString(xp,yp,"Clyde  ",&Arial_7x10,MENUE_COL_VALUE,BACKGROUND_COL);
  }

  yp+=MENUE_DELTA1;
  if(Pinky.strategy==GHOST_STRATEGY_RANDOM) {
    UB_Font_DrawString(xp,yp,"RANDOM ",&Arial_7x10,MENUE_COL_VALUE,BACKGROUND_COL);
  }
  else if(Pinky.strategy==GHOST_STRATEGY_BLINKY) {
    UB_Font_DrawString(xp,yp,"Blinky ",&Arial_7x10,MENUE_COL_VALUE,BACKGROUND_COL);
  }
  else if(Pinky.strategy==GHOST_STRATEGY_PINKY) {
    UB_Font_DrawString(xp,yp,"Pinky  ",&Arial_7x10,MENUE_COL_VALUE,BACKGROUND_COL);
  }
  else if(Pinky.strategy==GHOST_STRATEGY_INKY) {
    UB_Font_DrawString(xp,yp,"Inky   ",&Arial_7x10,MENUE_COL_VALUE,BACKGROUND_COL);
  }
  else {
    UB_Font_DrawString(xp,yp,"Clyde  ",&Arial_7x10,MENUE_COL_VALUE,BACKGROUND_COL);
  }

  yp+=MENUE_DELTA1;
  if(Inky.strategy==GHOST_STRATEGY_RANDOM) {
    UB_Font_DrawString(xp,yp,"RANDOM ",&Arial_7x10,MENUE_COL_VALUE,BACKGROUND_COL);
  }
  else if(Inky.strategy==GHOST_STRATEGY_BLINKY) {
    UB_Font_DrawString(xp,yp,"Blinky ",&Arial_7x10,MENUE_COL_VALUE,BACKGROUND_COL);
  }
  else if(Inky.strategy==GHOST_STRATEGY_PINKY) {
    UB_Font_DrawString(xp,yp,"Pinky  ",&Arial_7x10,MENUE_COL_VALUE,BACKGROUND_COL);
  }
  else if(Inky.strategy==GHOST_STRATEGY_INKY) {
    UB_Font_DrawString(xp,yp,"Inky   ",&Arial_7x10,MENUE_COL_VALUE,BACKGROUND_COL);
  }
  else {
    UB_Font_DrawString(xp,yp,"Clyde  ",&Arial_7x10,MENUE_COL_VALUE,BACKGROUND_COL);
  }

  yp+=MENUE_DELTA1;
  if(Clyde.strategy==GHOST_STRATEGY_RANDOM) {
    UB_Font_DrawString(xp,yp,"RANDOM ",&Arial_7x10,MENUE_COL_VALUE,BACKGROUND_COL);
  }
  else if(Clyde.strategy==GHOST_STRATEGY_BLINKY) {
    UB_Font_DrawString(xp,yp,"Blinky ",&Arial_7x10,MENUE_COL_VALUE,BACKGROUND_COL);
  }
  else if(Clyde.strategy==GHOST_STRATEGY_PINKY) {
    UB_Font_DrawString(xp,yp,"Pinky  ",&Arial_7x10,MENUE_COL_VALUE,BACKGROUND_COL);
  }
  else if(Clyde.strategy==GHOST_STRATEGY_INKY) {
    UB_Font_DrawString(xp,yp,"Inky   ",&Arial_7x10,MENUE_COL_VALUE,BACKGROUND_COL);
  }
  else {
    UB_Font_DrawString(xp,yp,"Clyde  ",&Arial_7x10,MENUE_COL_VALUE,BACKGROUND_COL);
  }
}


//--------------------------------------------------------------
// increase one value
//--------------------------------------------------------------
void menu_inc_value(uint32_t aktpos)
{
  if(aktpos==0) {
    if(Game.controller<1) Game.controller++;
  }
  else if(aktpos==1) {
    if(Player.level<10) Player.level++;
  }
  else if(aktpos==2) {
    if(Blinky.strategy<4) Blinky.strategy++;
  }
  else if(aktpos==3) {
    if(Pinky.strategy<4) Pinky.strategy++;
  }
  else if(aktpos==4) {
    if(Inky.strategy<4) Inky.strategy++;
  }
  else if(aktpos==5) {
    if(Clyde.strategy<4) Clyde.strategy++;
  }
}


//--------------------------------------------------------------
// decrease one value
//--------------------------------------------------------------
void menu_dec_value(uint32_t aktpos)
{
  if(aktpos==0) {
    if(Game.controller>0) Game.controller--;
  }
  else if(aktpos==1) {
    if(Player.level>2) Player.level--;
  }
  else if(aktpos==2) {
    if(Blinky.strategy>0) Blinky.strategy--;
  }
  else if(aktpos==3) {
    if(Pinky.strategy>0) Pinky.strategy--;
  }
  else if(aktpos==4) {
    if(Inky.strategy>0) Inky.strategy--;
  }
  else if(aktpos==5) {
    if(Clyde.strategy>0) Clyde.strategy--;
  }
}
