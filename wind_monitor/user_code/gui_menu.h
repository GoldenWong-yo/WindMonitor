/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2014  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.26 - Graphical user interface for embedded applications **
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only  be used  in accordance  with  a license  and should  not be  re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : GUIConf.h
Purpose     : Configuration of available features and default values
----------------------------------------------------------------------
*/

#ifndef GUI_MENU_H
#define GUI_MENU_H

#include "DIALOG.h"

WM_HWIN CreateMenu(void);

//更新风速值
void gui_speed_update(U16 speed);

//更新风向值
void gui_dire_update(U16 dire);

//获取风速采样值
U8 gui_speed_time_get(void);

//获取风向采样值
U8 gui_dire_time_get(void);

#endif  /* Avoid multiple inclusion */

/*************************** End of file ****************************/
