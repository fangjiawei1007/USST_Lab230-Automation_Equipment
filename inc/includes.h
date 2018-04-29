#ifndef _INCLUDES_H_
#define _INCLUDES_H_
#include <stdarg.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "def.h"
#include "2416addr.h"
#include "2416lib.h"
#include "option.h"
#include "LCD.h"
#include "mmu.h"
#include "Nand.h"
#include "..\inc\download.h"
#include "..\inc\systemconf.h"
#include "..\inc\systemmenu.h"
#include "..\inc\function.h"
#include "..\inc\jiema.h"
#include "..\inc\communication.h"
#include "..\inc\test.h"
#include "..\inc\Rtc.h"
#include "..\inc\encrypt.h"

#include "..\inc\app.h"
#include "..\inc\appBase.h"

#include "sys_robot.h"
#include "485test.h"
#include "test_485.h"
#include "Automation.h"
#include "Peripheral.h"

extern INTERALMEMORY g_InteralMemory;
extern SYSTEMCONFIG g_SystemConf;
extern TIMER2_V g_Timer2Uart;



extern unsigned int move_x_status;
extern unsigned int move_y_status;
extern unsigned int move_z_status;

extern unsigned int reset_button_status;
extern unsigned int start_b_robot_status;


extern unsigned int handwheel_position;

extern unsigned int handwheel_x_status;
extern unsigned int handwheel_y_status;
extern unsigned int handwheel_z_status;

#endif