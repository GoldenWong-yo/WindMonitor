


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

#ifndef GUI_HISTORY_H
#define GUI_HISTORY_H

#include "DIALOG.h"

WM_HWIN CreateHistory(void);

//显示历史数据
//p_buf：数据
//size：数据组数
//all_page：总页数
//now_page：当前页数
void gui_history_dataupdata(U8 *p_buf,U8 size, U8 now_page, U8 all_page);

//获取状态上一页  返回1  下一页返回2  无操作返回0
U8 gui_gistory_state_get(void);

#endif  /* Avoid multiple inclusion */

/*************************** End of file ****************************/
