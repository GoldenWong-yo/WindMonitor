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

** emWin V5.24 - Graphical user interface for embedded applications **
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : GUIDEMO_Start.c
Purpose     : GUIDEMO initialization
----------------------------------------------------------------------
*/

/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
*
* Copyright (c) 2001-2016 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief 按键控件演示不例，
 *
 * - 实验现象:
 *   1. 按键控制LED灯亮与灭
 *
 * \par 源代码
 * \snippet demo_emwin_buttontest.c src_emwin_buttontest
 *
 * \internal
 * \par Modification history
 * - 0.10 16-11-19  nwt, first implementation.
 * \endinternal
 */

#include "GUI.h"
#include "LCDConf.h"
#include "ICONVIEW.h"
#include "DIALOG.h"
#include "gui_menu.h"
#include "gui_entry.h"
#include "gui_title.h"
#include "gui_history.h"

gui_dev_t g_gui_dev;

void __gui_data_init(void)
{
	g_gui_dev.dire = 0;
	g_gui_dev.speed = 1.1f;
	g_gui_dev.time_dire = 1;
	g_gui_dev.time_speed = 1;
}
/*********************************************************************
*
*       MainTask
*/
void gui_init(void) 
{
//	U8 data[30] = { 100,1,2,100,1,2,
//					102,1,2,100,1,2,
//					120,1,64,100,1,2,
//					104,1,86,100,1,2,
//					150,1,34,100,1,2,};


	__gui_data_init();

	GUI_Clear();
	g_gui_dev.hTitleWin = CreateTitle();
	g_gui_dev.hMenuWin = CreateMenu();
	
//	gui_history_dataupdata(data, 10, 3, 10);
}




/*************************** End of file ****************************/

