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
#include "..\inc\wdt.h"	//WDT���� by ����ΰ 2017/4/1


#include "..\inc\app.h"
#include "..\inc\appBase.h"

#include "includes.h"



//extern INTERALMEMORY g_InteralMemory;

//extern GLOBALVAR g_GlobalVar;

//extern INT16U PreScrNum;


extern unsigned int InPulseCount[7];		//��¼6·�����������������

extern unsigned int OutPulse_PreSet[4];	// 3·���������  ����Ԥ��ֵ
extern volatile unsigned int OutPulse_Counter[4];	// 3·���������  ��ǰ���������

extern INTERALMEMORY g_InteralMemory;




////�Ӵ˿�ʼ����û�����//////////////////////////////////

//unsigned char model_work;

	
	
	
	
	
	
	
	
	
///////////////////////////////////////////////////////////////
//////	��ʼ��     //////////////////////////////////////////
//////	ÿ���ϵ�App_Init ִֻ��һ��	 //////////////////
//////////////////////////////////////////////////////////////
void App_Init(void)
{
	int i;
	
	X_In_Init();
	Y_Out_Init();
	Pulse_In_Init();
	Pulse_Out_Init();

	servo_uart_init();
	parameters_init();
	manual_init();//���������øߣ�����֮���˶�
	handwheel_init();
	Button_Init();
	//pulse_signal = 0;
	/////////////����ʹ������///////////////////
	// status_reset();
	// zero_finish_status = 0;
	// zero_start_status = 0;	
	////////////////////////////////////////////
	
	//wdt_feed_dog();

	//move_x_status = 0;
	
	//	DA0_10_Init();

	// ���������ʼ��
	for(i=0; i<7; i++)
	{
		InPulseCount[i] = 0;
	}
	//parameter_input();
	
}


///////////////////////////////////////////////////////////////
//////	Ӧ��������     //////////////////////////////////////////
//////	ϵͳÿ��ѭ�������һ��App_Operation	 //////////////////
//////////////////////////////////////////////////////////////
void App_Operation(void)
{

//////********************************************////
	//�˴�������Ӿ�̬���� by FJW

	
	unsigned int start_mode = 0;
	unsigned int handwheel_mode = 0;
	
//////////////////////////////////////////////////////////////
/////////////////////�Ӵ˿�ʼ����û�����/////////////////////
//////////////////////////////////////////////////////////////
	Button_mutex(&start_button,&reset_button,&start_mode,0);
	Button_mutex(&handwheel_y,&handwheel_z,&handwheel_mode,0);
	set_speed_distance_485();
	
	condition_monitor();
	//set_speed_test();
	
	//�����ⲿ�ܿ��ؾ�Ϊ�㣬һֱɨ�裬�ж��Ƿ��ֶ����ı��ٶ�
	if(start_button == 0 && reset_button == 0 && handwheel_start_button == 0)
	{
		//Beep(1);
		move_manually();
		zero_confirm();
		
		//TEST_fun()
		
		if(gripper_external_button == 1)
		{
			gripper_relaxing(gripper1_port);
			gripper_relaxing(gripper2_port);
		}
		
		manual_gripper_1();
		manual_gripper_2();
		manual_cylinder_A();
		
	}
	
	//����ģʽȡ��
	if(handwheel_start_button == 0)
	{
		handwheel_x_status = 0;
		handwheel_y_status = 0;
		handwheel_z_status = 0;
	}
	
	//����ģʽ
	if(start_button == 0 && reset_button == 0 && handwheel_start_button == 1)
	{
		handwheel_set_speed();
		/**************Y��status(�жϷ���������������/ֹͣ)******************/
		if(handwheel_y == 1 && handwheel_z == 0)
		{
			handwheel_y_status = 1;
			handwheel_z_status = 0;
		}
		
		
		/**************X��status(�жϷ���������������/ֹͣ)******************/
		if(handwheel_x == 1)
		{
			handwheel_x_status = 1;
		}
		
		
		/**************Z��status(�жϷ���������������/ֹͣ)******************/
		if(handwheel_y == 0 && handwheel_z == 1)
		{
			handwheel_y_status = 0;
			handwheel_z_status = 1;
		}
		
	
		/**********************X���õ�ǰλ��****************************/
		if(position_x_get == 1)
		{
			SERVO_GET_POSITION(X_Dev_addr);
			Delay(1000000);
			
			handwheel_x_position = handwheel_position;
			
			position_x_get = 0;
		}
	
		/**********************Y���õ�ǰλ��****************************/
		if(position_y_get == 1)
		{
			SERVO_GET_POSITION(Y_Dev_addr);
			Delay(1000000);
			
			handwheel_y_position = handwheel_position;
			
			position_y_get = 0;
		}

		/**********************Z���õ�ǰλ��****************************/
		if(position_z_get == 1)
		{
			SERVO_GET_POSITION(Z_Dev_addr);
			Delay(1000000);
			
			handwheel_z_position = handwheel_position;
			
			position_z_get = 0;
		}
	
	}
	//reset���ؽ��и�λ�˶�
	if(start_button == 0 && reset_button == 1 && handwheel_start_button == 0)
	{
		RESET();	
		if(finish_complete() == 1 && reset_button_status == 1)
		{
			  status_reset(); 
			  
			  finish_status = 0;
			  start_b_robot_status = 0;
			  
			  reset_button = 0;
			  reset_button_status = 0;
		}
	}
	
	//ѭ����ʼ����
	if(start_button == 1 && finish_status == 0 && handwheel_start_button == 0)//&& start_status_no_use == 0 
	{
		start_b_robot_status = 1;//��ͣ��־λ
		Alarm_Lamp_Off();
		
		Loop_Robot();
	}
	
	else if(start_button == 0 && start_b_robot_status == 1 && handwheel_start_button == 0)
	{
		//Beep(1);
		start_status_reset();	//��ͣ����Ҫ�ı�ı���
		start_b_robot_status = 0;
		pulse_signal = 1;
	}
	
	if(finish_status == 1)
	{
		Alarm_Lamp_On();
		status_reset();
		
		start_button = 0;
		start_b_robot_status = 0;
		finish_status = 0;
		
		gongjian_hangshu_tmp = 1;
		gongjian_lieshu_tmp = 1;	//������Ϊ��ʼ��1.
	}
/*
g_InteralMemory.Bit[]
g_InteralMemory.KeepBit[]
g_InteralMemory.Word[]
g_InteralMemory.KeepWord[]
*/	
	
}





