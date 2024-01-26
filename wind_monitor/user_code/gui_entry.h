


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

#ifndef GUI_ENTRY_H
#define GUI_ENTRY_H

#include "DIALOG.h"

typedef struct {
	WM_HWIN hTitleWin;
	WM_HWIN hMenuWin;
	WM_HWIN hMenuHistory;

	U16    speed;
	U8     time_speed;
	U16    dire;
	U8     time_dire;
}gui_dev_t;


void gui_init(void);

#endif  /* Avoid multiple inclusion */

/*************************** End of file ****************************/
