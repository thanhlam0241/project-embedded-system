////--------------------------------------------------------------
//// File     : stm32_ub_tiled.c
//// Datum    : 21.09.2014
//// Version  : 1.0
//// Autor    : UB
//// EMail    : mc-4u(@)t-online.de
//// Web      : www.mikrocontroller-4u.de
//// CPU      : STM32F429
//// IDE      : CooCox CoIDE 1.7.4
//// GCC      : 4.7 2012q4
//// Module   : STM32_UB_GRAPHIC2D, TIM, MISC
////            TILED_MAP, TILED_PLAYER, TILED_OBJ
//// Funktion : 2D-Game per Tiled
////
//// Hinweise :
////
//// Tiled Editor : http://www.mapeditor.org/
//// Tilesets     : http://opengameart.org/
////--------------------------------------------------------------
//
//
////--------------------------------------------------------------
//// Includes
////--------------------------------------------------------------
//#include "stm32_ub_tiled.h"
//
//
//
////--------------------------------------------------------------
//// USER : ab hier keine Aenderungen notwendig
////--------------------------------------------------------------
//
//
////--------------------------------------------------------------
//TILED_GAME_t TILED_GAME;
//
//
////--------------------------------------------------------------
//// interne Funktionen
////--------------------------------------------------------------
//void P_Tiled_InitLCD(void);
//void P_Tiled_TimerStart(void);
//void P_Tiled_InitTimer(void);
//void P_Tiled_InitNVIC(void);
//void P_Tiled_DrawAll(void);
//
//
//
////--------------------------------------------------------------
//// init aller Tiled Komponenten
////
//// check_map : true => prueft ob Daten der MAP ok sind
////
//// ret_wert : SUCCESS = init ok
////            ERROR   = Fehler (siehe  TILED_STATUS.err_nr)
////--------------------------------------------------------------
//ErrorStatus UB_Tiled_Init(bool check_map)
//{
//  // init aller Variabeln
//  TILED_GAME.enable=true;
//  TILED_GAME.lcd_refresh_cnt=TILED_LCD_REFRESH_MS;
//  TILED_GAME.game_time_cnt=0;
//  TILED_GAME.obj_speed_cnt=TILED_OBJ_SPEED_MS;
//  TILED_GAME.input_device_cnt=TILED_INPUT_DEVICE_MS;
//  TILED_GAME.obj_event=0;
//  TILED_GAME.player_event=0;
//
//  // Tiled Variabeln
//  TILED.game_time_sec=0;
//  TILED.event=TILED_EVENT_NONE;
//
//  // init vom LCD
//  P_Tiled_InitLCD();
//
//  // init und start vom Timer
//  P_Tiled_TimerStart();
//
//  // init der MAP
//  UB_Tiled_Map_Init(check_map);
//
//  // init vom Player
//  UB_Tiled_Player_Init();
//
//  // init aller Objekte
//  UB_Tiled_Obj_Init();
//
//  if(TILED_STATUS.error==false) {
//    return(SUCCESS);
//  }
//  else {
//    TILED_GAME.enable=false;
//    return(ERROR);
//  }
//}
//
//
////--------------------------------------------------------------
//// bearbeitet alle Tiled Prozesse
//// muss ständig aufgerufen werden
////--------------------------------------------------------------
//void UB_Tiled_Do(void)
//{
//  uint32_t obj_nr=0;
//  uint8_t obj_typ=0;
//
//  // check error
//  if(TILED_STATUS.error==true) return;
//
//  // kiem tra bo dem dau vao da het han chua
//  if(TILED_GAME.input_device_cnt>=TILED_INPUT_DEVICE_MS) {
//    TILED_GAME.input_device_cnt=0;
//
//    // User CallBack aufrufen
//  if(TILED_GAME.enable==true) UB_Tiled_Input_Device_CallBack();
// }
//
//  // kiem tra xem cac doi tuong co nen duoc di chuyen
//  if(TILED_GAME.obj_speed_cnt>=TILED_OBJ_SPEED_MS) {
//    TILED_GAME.obj_speed_cnt=0;
//
//    if(TILED_GAME.enable==true) {
//      // di chuyen tat ca
//      UB_Tiled_Obj_MoveAll();
//
//      TILED_GAME.obj_event=1;
//    }
//  }
//
//  // Kiem tra xem thoi gian lam moi man hinh
//  if(TILED_GAME.lcd_refresh_cnt>=TILED_LCD_REFRESH_MS) {
//    TILED_GAME.lcd_refresh_cnt=0;
//
//    // Render lai
//    P_Tiled_DrawAll();
//
//    // Goi lai ham
//    UB_Tiled_LCD_CallBack();
//
//    // LCD Refresh
//    UB_LCD_Refresh();
//  }
//
//  // Kiem tra su kien
//  if((TILED_GAME.obj_event!=0) || (TILED_GAME.player_event!=0)) {
//    // cho trang thai la khong co su kien
//    TILED.event=TILED_EVENT_NONE;
//
//    // Su kien doi tuong
//    if(TILED_GAME.obj_event!=0) {
//      if(UB_Tiled_CheckDeadlyCollision(&obj_nr, &obj_typ)==true)
//    	  TILED.event=TILED_EVENT_DEADLY_COLLISION;
//      TILED_GAME.obj_event=0;
//    }
//
//    // Trang thai nguoi choi
//    if(TILED_GAME.player_event!=0) {
//      if(UB_Tiled_CheckGoal()==true) TILED.event=TILED_EVENT_GOAL;
//      if(UB_Tiled_CheckCollectableCollision(&obj_nr, &obj_typ)==true)
//    	  TILED.event=TILED_EVENT_COLLECTABLE_COLLISION;
//      if(UB_Tiled_CheckDeadlyCollision(&obj_nr, &obj_typ)==true)
//    	  TILED.event=TILED_EVENT_DEADLY_COLLISION;
//      if(UB_Tiled_CheckDeadlyTerrain()==true)
//    	  TILED.event=TILED_EVENT_DEADLY_TERRAIN;
//      TILED_GAME.player_event=0;
//    }
//
//    // Goi lai ham
//    if(TILED.event!=TILED_EVENT_NONE) UB_Tiled_Event_CallBack();
//  }
//}
//
//
////--------------------------------------------------------------
//// Dung lai
////--------------------------------------------------------------
//void UB_Tiled_Stop(void)
//{
//  TILED_GAME.enable=false;
//}
//
//
////--------------------------------------------------------------
//// bewegt den Player um (distance) Pixel in eine Richtung
//// (bewegt auch die MAP falls notwendig)
////
//// ret_wert : Richtung in der sich der Player bewegt hat
////--------------------------------------------------------------
//TILED_DIR_t UB_Tiled_MovePlayer(TILED_DIR_t direction, uint32_t distance)
//{
//  TILED_DIR_t ret_wert=DIR_NONE;
//
//  if(TILED_GAME.enable!=true) return(DIR_NONE);
//
//  ret_wert = UB_Tiled_Player_Move(direction, distance);
//
//  if(ret_wert!=DIR_NONE) {
//    // nach Bewegung merker setzen
//    TILED_GAME.player_event=1;
//  }
//
//  return(ret_wert);
//}
//
//
////--------------------------------------------------------------
//// check ob Siegposition erreicht ist
////--------------------------------------------------------------
//bool UB_Tiled_CheckGoal(void)
//{
//  bool ret_wert=false;
//  uint32_t ziel_adr,tile_adr;
//  uint32_t xp,yp;
//
//  // ziel_adr vom Tile bestimmten
//  ziel_adr=(TILED_PLAYER_ZIELY*TILED_MAP_ANZX)+TILED_PLAYER_ZIELX;
//
//  // check der linken oberen Ecke
//  xp=SPRITE_PLAYER.px_posx;
//  yp=SPRITE_PLAYER.px_posy;
//  // tile adresse in der map bestimmen
//  tile_adr=UB_Tiled_Map_GetTileAdr(xp,yp);
//  if(tile_adr==ziel_adr) return(true);
//
//  // check der rechten oberen Ecke
//  xp=SPRITE_PLAYER.px_posx+TILESET_PLAYER.tilewidth-1;
//  yp=SPRITE_PLAYER.px_posy;
//  // tile adresse in der map bestimmen
//  tile_adr=UB_Tiled_Map_GetTileAdr(xp,yp);
//  if(tile_adr==ziel_adr) return(true);
//
//  // check der linken unteren Ecke
//  xp=SPRITE_PLAYER.px_posx;
//  yp=SPRITE_PLAYER.px_posy+TILESET_PLAYER.tileheight-1;
//  // tile adresse in der map bestimmen
//  tile_adr=UB_Tiled_Map_GetTileAdr(xp,yp);
//  if(tile_adr==ziel_adr) return(true);
//
//  // check der rechten unteren Ecke
//  xp=SPRITE_PLAYER.px_posx+TILESET_PLAYER.tilewidth-1;
//  yp=SPRITE_PLAYER.px_posy+TILESET_PLAYER.tileheight-1;
//  // tile adresse in der map bestimmen
//  tile_adr=UB_Tiled_Map_GetTileAdr(xp,yp);
//  if(tile_adr==ziel_adr) return(true);
//
//  return(ret_wert);
//}
//
//
////--------------------------------------------------------------
//// check ob aktuelle Player-Position
//// mit einem toedlichem Terrain Kollidiert
//// (geprueft wird nur der sichtbare bereich)
////
//// ret_wert : true   = toedliches Terrain
////--------------------------------------------------------------
//bool UB_Tiled_CheckDeadlyTerrain(void)
//{
//  bool ret_wert=false;
//  uint32_t pl_xp1,pl_yp1,pl_xp2,pl_yp2;
//  uint8_t terrain;
//
//  // Playerpos
//  pl_xp1=SPRITE_PLAYER.px_posx;
//  pl_yp1=SPRITE_PLAYER.px_posy;
//  pl_xp2=SPRITE_PLAYER.px_posx+TILESET_PLAYER.tilewidth-1;
//  pl_yp2=SPRITE_PLAYER.px_posy+TILESET_PLAYER.tileheight-1;
//
//  // check auf toedliches terrain
//  terrain=UB_Tiled_Map_GetTerrain(pl_xp1,pl_yp1);
//  if(PLAYER_TERRAIN[terrain]==TERRAIN_DEADLY) return(true);
//  terrain=UB_Tiled_Map_GetTerrain(pl_xp2,pl_yp1);
//  if(PLAYER_TERRAIN[terrain]==TERRAIN_DEADLY) return(true);
//  terrain=UB_Tiled_Map_GetTerrain(pl_xp1,pl_yp2);
//  if(PLAYER_TERRAIN[terrain]==TERRAIN_DEADLY) return(true);
//  terrain=UB_Tiled_Map_GetTerrain(pl_xp2,pl_yp2);
//  if(PLAYER_TERRAIN[terrain]==TERRAIN_DEADLY) return(true);
//
//  return(ret_wert);
//}
//
////--------------------------------------------------------------
//// check ob aktuelle Player-Position
//// mit einem toedlichen Objekt Kollidiert
//// (geprueft wird nur der sichtbare bereich)
////
//// ret_wert : true   = toedliche Kollision
////           obj_nr  = nr vom toedlichen Objekt
////           obj_typ = typ vom toedlichen Objekt
////--------------------------------------------------------------
//bool UB_Tiled_CheckDeadlyCollision(uint32_t *obj_nr, uint8_t *obj_typ)
//{
//  bool ret_wert=false;
//  uint32_t pl_xp1,pl_yp1,pl_xp2,pl_yp2;
//  uint32_t ob_xp1,ob_yp1,ob_xp2,ob_yp2;
//  uint32_t nr;
//  uint8_t typ;
//
//  *obj_nr=0;
//  *obj_typ=0;
//
//  // Playerpos
//  pl_xp1=SPRITE_PLAYER.px_posx;
//  pl_yp1=SPRITE_PLAYER.px_posy;
//  pl_xp2=SPRITE_PLAYER.px_posx+TILESET_PLAYER.tilewidth-1;
//  pl_yp2=SPRITE_PLAYER.px_posy+TILESET_PLAYER.tileheight-1;
//
//  // alle Objekte prüfen
//  for(nr=0;nr<TILED_OBJ_ANZ;nr++) {
//    // check ob enable und sichtbar
//    if((TILED_OBJ[nr].enable==true) && (SPRITE_OBJ[nr].visible==true)) {
//      // Typ bestimmen
//      typ=TILED_OBJ[nr].typ;
//      // check ob typ toedlich ist
//      if(COLLISION_OBJ[typ]==OBJ_DEADLY) {
//        // Objektposition
//        ob_xp1=SPRITE_OBJ[nr].px_posx;
//        ob_yp1=SPRITE_OBJ[nr].px_posy;
//        ob_xp2=SPRITE_OBJ[nr].px_posx+TILESET_OBJ[typ].tilewidth-1;
//        ob_yp2=SPRITE_OBJ[nr].px_posy+TILESET_OBJ[typ].tileheight-1;
//        // check auf Kollision
//        if((pl_xp1<ob_xp2) && (ob_xp1<pl_xp2) && (pl_yp1<ob_yp2) && (ob_yp1<pl_yp2)) {
//          ret_wert=true;
//        }
//      }
//    }
//    if(ret_wert==true) { // Kollision gefunden
//      *obj_nr=nr;
//      *obj_typ=typ;
//      break;
//    }
//  }
//
//  return(ret_wert);
//}
//
//
////--------------------------------------------------------------
//// check ob aktuelle Player-Position
//// mit einem sammelbaren Objekt Kollidiert
//// (geprueft wird nur der sichtbare bereich)
////
//// ret_wert :  true  = sammelbare Kollision
////           obj_nr  = nr vom sammelbaren Objekt
////           obj_typ = typ vom sammelbaren Objekt
////--------------------------------------------------------------
//bool UB_Tiled_CheckCollectableCollision(uint32_t *obj_nr, uint8_t *obj_typ)
//{
//  bool ret_wert=false;
//  uint32_t pl_xp1,pl_yp1,pl_xp2,pl_yp2;
//  uint32_t ob_xp1,ob_yp1,ob_xp2,ob_yp2;
//  uint32_t nr;
//  uint8_t typ;
//
//  *obj_nr=0;
//  *obj_typ=0;
//
//  // Playerpos
//  pl_xp1=SPRITE_PLAYER.px_posx;
//  pl_yp1=SPRITE_PLAYER.px_posy;
//  pl_xp2=SPRITE_PLAYER.px_posx+TILESET_PLAYER.tilewidth-1;
//  pl_yp2=SPRITE_PLAYER.px_posy+TILESET_PLAYER.tileheight-1;
//
//  // alle Objekte prüfen
//  for(nr=0;nr<TILED_OBJ_ANZ;nr++) {
//    // check ob enable und sichtbar
//    if((TILED_OBJ[nr].enable==true) && (SPRITE_OBJ[nr].visible==true)) {
//      // Typ bestimmen
//      typ=TILED_OBJ[nr].typ;
//      // check ob typ sammelbar ist
//      if(COLLISION_OBJ[typ]==OBJ_COLLECTABLE) {
//        // Objektposition
//        ob_xp1=SPRITE_OBJ[nr].px_posx;
//        ob_yp1=SPRITE_OBJ[nr].px_posy;
//        ob_xp2=SPRITE_OBJ[nr].px_posx+TILESET_OBJ[typ].tilewidth-1;
//        ob_yp2=SPRITE_OBJ[nr].px_posy+TILESET_OBJ[typ].tileheight-1;
//        // check auf Kollision
//        if((pl_xp1<ob_xp2) && (ob_xp1<pl_xp2) && (pl_yp1<ob_yp2) && (ob_yp1<pl_yp2)) {
//       	  ret_wert=true;
//        }
//      }
//    }
//    if(ret_wert==true) { // Kollision gefunden
//      *obj_nr=nr;
//      *obj_typ=typ;
//      break;
//    }
//  }
//
//  return(ret_wert);
//}
//
//
////--------------------------------------------------------------
//// deaktiviert ein Objekt
//// obj_nr = nr des Objektes [0...TILED_OBJ_ANZ-1]
////--------------------------------------------------------------
//void UB_Tiled_DisableObjekt(uint32_t obj_nr)
//{
//  if(obj_nr<TILED_OBJ_ANZ) TILED_OBJ[obj_nr].enable=false;
//}
//
//
////--------------------------------------------------------------
//// aktiviert ein Objekt
//// obj_nr = nr des Objektes [0...TILED_OBJ_ANZ-1]
////--------------------------------------------------------------
//void UB_Tiled_EnableObjekt(uint32_t obj_nr)
//{
//  if(obj_nr<TILED_OBJ_ANZ) TILED_OBJ[obj_nr].enable=true;
//}
//
//
////--------------------------------------------------------------
//// interne Funktion
//// init vom LCD
////--------------------------------------------------------------
//void P_Tiled_InitLCD(void)
//{
//  UB_LCD_Init();
//  UB_LCD_LayerInit_Fullscreen();
//  // auf Hintergrund schalten
//  UB_LCD_SetLayer_1();
//  // Hintergrund komplett mit Farbe füllen
//  UB_LCD_FillLayer(TILED_BG_COLOR);
//  // auf Vordergrund schalten
//  UB_LCD_SetLayer_2();
//  // Vordergrund komplett mit Farbe füllen
//  UB_LCD_FillLayer(TILED_BG_COLOR);
//}
//
//
////--------------------------------------------------------------
//// interne Funktion
//// init und start vom Timer
////--------------------------------------------------------------
//void P_Tiled_TimerStart(void)
//{
//  // init vom Timer
//  P_Tiled_InitTimer();
//
//  // init vom NVIC
//  P_Tiled_InitNVIC();
//
//  // start vom Timer
//  TIM_Cmd(TILED_TIMER_NAME, ENABLE);
//}
//
//
////--------------------------------------------------------------
//// interne Funktion
//// init vom Timer
////--------------------------------------------------------------
//void P_Tiled_InitTimer(void)
//{
//  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//
//  // Clock enable
//  RCC_APB1PeriphClockCmd(TILED_TIMER_CLK, ENABLE);
//
//  // Timer disable
//  TIM_Cmd(TILED_TIMER_NAME, DISABLE);
//
//  // Timer init
//  TIM_TimeBaseStructure.TIM_Period =  TILED_TIMER_PERIOD;
//  TIM_TimeBaseStructure.TIM_Prescaler = TILED_TIMER_PRESCALE;
//  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
//  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
//  TIM_TimeBaseInit(TILED_TIMER_NAME, &TIM_TimeBaseStructure);
//
//  // Timer preload enable
//  TIM_ARRPreloadConfig(TILED_TIMER_NAME, ENABLE);
//}
//
//
////--------------------------------------------------------------
//// interne Funktion
//// init vom NVIC
////--------------------------------------------------------------
//void P_Tiled_InitNVIC(void)
//{
//  NVIC_InitTypeDef NVIC_InitStructure;
//
//  // Update Interrupt enable
//  TIM_ITConfig(TILED_TIMER_NAME,TIM_IT_Update,ENABLE);
//
//  // NVIC konfig
//  NVIC_InitStructure.NVIC_IRQChannel = TILED_TIMER_IRQ;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);
//}
//
//
////--------------------------------------------------------------
//// zeichnet die Karte und alle Sprites
//// auf den Screen
////--------------------------------------------------------------
//void P_Tiled_DrawAll(void)
//{
//  // zuerst die MAP zeichnen
//  UB_Tiled_Map_Draw();
//
//  // Objekte zeichnen
//  UB_Tiled_Obj_Draw();
//
//  // Player zeichnen
//  UB_Tiled_Player_Draw();
//}
//
//
////--------------------------------------------------------------
//// Timer-Interrupt
//// wird alle 1ms aufgerufen
////--------------------------------------------------------------
//void TILED_TIMER_IRQHANDLER(void)
//{
//  if (TIM_GetITStatus(TILED_TIMER_NAME, TIM_IT_Update) != RESET) {
//    // wenn Interrupt aufgetreten
//    TIM_ClearITPendingBit(TILED_TIMER_NAME, TIM_IT_Update);
//
//    // USER CallBack-Funktion
//    UB_Tiled_1ms_ISR_CallBack();
//
//    // Counter fuer LCD-Refresh
//    TILED_GAME.lcd_refresh_cnt++;
//    // Counter fuer Game-Zeit
//    TILED_GAME.game_time_cnt++;
//    if(TILED_GAME.game_time_cnt>=1000) {
//      TILED_GAME.game_time_cnt=0;
//      if(TILED_GAME.enable==true) TILED.game_time_sec++;
//    }
//    // Counter fuer Objekt Speed
//    TILED_GAME.obj_speed_cnt++;
//    // Counter fuer Input Device
//    TILED_GAME.input_device_cnt++;
//  }
//}
//
//
//
