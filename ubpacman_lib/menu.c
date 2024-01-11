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

char connected[] =    "Keyboard found       ";
char disconnected[] = "Keyboard disconnected";
uint32_t isConnected = 0;
//--------------------------------------------------------------
// init and start endless pacman gameplay
//--------------------------------------------------------------
void menu_start(void)
{
  uint32_t ok=0;
  uint32_t aktpos=0, aktiv=0;
  uint32_t joy=GUI_JOY_NONE;
  uint16_t srand_init=0;

  GUI.refresh_value=GUI_REFRESH_VALUE;
  GUI.refresh_buttons=GUI_REFRESH_VALUE;

  gui_clear_screen();

  UB_Font_DrawString(60,5,"    GAME PACMAN",&Arial_7x10,FONT_COL,BACKGROUND_COL);
  UB_Font_DrawString(30,20,"  Project Embedded System",&Arial_7x10,FONT_COL,BACKGROUND_COL);

  menu_redraw(aktpos);

  do {
    srand_init++;
//    if(Gui_Touch_Timer_ms==0) {
//      Gui_Touch_Timer_ms=GUI_TOUCH_INTERVALL_MS;
//      joy=gui_check_touch();
//      gui_draw_buttons(joy);
//    }
    if(aktiv==0) {
      if(akt_usb_status==USB_HID_KEYBOARD_CONNECTED) {
    	  if(isConnected == 0){
    		 isConnected = 1;
    	     menu_redraw(aktpos);
    	     aktiv=1;
    	  }
    	  if(UB_USB_HID_HOST_GetKeyAnz()>0) {
    		    sprintf(key, "Pressed key %u",USB_KEY_DATA.akt_key1);
    	        // Nhan dang phim tu keyboard
    	        if(USB_KEY_DATA.akt_key1==79) {
    	        	menu_dec_value(aktpos);
    	        	menu_redraw(aktpos);
    	        	aktiv=1;
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
    	        	else if (aktpos == MENUE_MAX_POS - 1){
    	        		Game.debug_mode = 1;
    	        		ok = 1;
    	        	}
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
//      if(joy==GUI_JOY_DOWN) {
//        if(aktpos<MENUE_MAX_POS) aktpos++;
//        menu_redraw(aktpos);
//        aktiv=1;
//      }
//      else if(joy==GUI_JOY_UP) {
//        if(aktpos>0) aktpos--;
//        menu_redraw(aktpos);
//        aktiv=1;
//      }
//      else if(joy==GUI_JOY_RIGHT) {
//        menu_inc_value(aktpos);
//        menu_redraw(aktpos);
//        aktiv=1;
//        if(aktpos==MENUE_MAX_POS) ok=1;
//      }
//      else if(joy==GUI_JOY_LEFT) {
//        menu_dec_value(aktpos);
//        menu_redraw(aktpos);
//        aktiv=1;
//        if(aktpos==MENUE_MAX_POS) ok=1;
//      }
    	if(isConnected == 1){
    		isConnected = 0;
    		menu_redraw(aktpos);
   	        aktiv=1;
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
//  char buf1[20];
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

  UB_Font_DrawString(xp,yp,key,&Arial_7x10,MENUE_COL_OFF,BACKGROUND_COL);

//  yp+=MENUE_DELTA1;
//  UB_Font_DrawString(xp,yp,"Controller      : ",&Arial_7x10,c[0],BACKGROUND_COL);

  yp+=MENUE_DELTA1;
  UB_Font_DrawString(xp,yp,"Start level      : ",&Arial_7x10,c[0],BACKGROUND_COL);

//  yp+=MENUE_DELTA1;
//  UB_Font_DrawString(xp,yp,"Bots number      : ",&Arial_7x10,c[1],BACKGROUND_COL);

  yp+=MENUE_DELTA1;
  UB_Font_DrawString(xp,yp,"Debug",&Arial_7x10,c[1],BACKGROUND_COL);
  yp+=MENUE_DELTA1+MENUE_DELTA1;
  UB_Font_DrawString(xp,yp,"Start",&Arial_7x10,c[2],BACKGROUND_COL);

  yp+=MENUE_DELTA1+MENUE_DELTA1;
  UB_Font_DrawString(xp,yp,isConnected == 1 ? connected : disconnected,&Arial_7x10,MENUE_COL_OFF,BACKGROUND_COL);

  //-------------------------
  // right side
  //-------------------------

  xp=MENUE_STARTX2;
  yp=MENUE_STARTY;
//  yp+=MENUE_DELTA1;
//  if(Game.controller==GAME_CONTROL_TOUCH) {
//    UB_Font_DrawString(xp,yp,"Touch   ",&Arial_7x10,MENUE_COL_VALUE,BACKGROUND_COL);
//  }
//  else {
//    UB_Font_DrawString(xp,yp,"4 Button",&Arial_7x10,MENUE_COL_VALUE,BACKGROUND_COL);
//  }
  yp+=MENUE_DELTA1;
  sprintf(buf,"%d ",(int)(Player.level));
  UB_Font_DrawString(xp,yp,buf,&Arial_7x10,MENUE_COL_VALUE,BACKGROUND_COL);


//  yp+=MENUE_DELTA1;
//  sprintf(buf1,"%d ",(int)(Game.numberOfBots));
//  UB_Font_DrawString(xp,yp,buf1,&Arial_7x10,MENUE_COL_VALUE,BACKGROUND_COL);
}

//--------------------------------------------------------------
// increase one value
//--------------------------------------------------------------
void menu_inc_value(uint32_t aktpos)
{
//  if(aktpos==0) {
//    if(Game.controller<1) Game.controller++;
//  }
  if(aktpos==0) {
    if(Player.level<10) Player.level++;
  }
//  else if(aktpos==1) {
//      if(Game.numberOfBots<4) Game.numberOfBots++;
//  }
}


//--------------------------------------------------------------
// decrease one value
//--------------------------------------------------------------
void menu_dec_value(uint32_t aktpos)
{
//  if(aktpos==0) {
//    if(Game.controller>0) Game.controller--;
//  }
  if(aktpos==0) {
    if(Player.level>2) Player.level--;
  }
//  else if(aktpos==1) {
//    if(Game.numberOfBots>1) Game.numberOfBots--;
//  }
}
