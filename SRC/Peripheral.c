#include "includes.h"
unsigned int reset_button_status = 0;
unsigned int zero_move_allow_status = 0;

unsigned int manual_gripper_1_status = 0;
unsigned int manual_gripper_2_status = 0;

unsigned int manual_cylinder_A_status = 0;

void everythig_get_zero(void)
{
	
	//Beep(1);

		SERVO_SET_DISTANCE(Z_Dev_addr,zero_z);
		Delay(1000000);
		PC_START_TRIGGER(Z_AXIS);				
		
		if(Get_X_Value(z_position_finish) == UNFINISH || (loading_z_up_1_finish_status == 1)  
		  || (blanking_z_up_2_finish_status == 1))
			zero_move_allow_status = 1;
	
	if(Get_X_Value(z_position_finish) == FINISH && zero_move_allow_status == 1)
	{
		//Beep(1);
		SERVO_SET_DISTANCE(X_Dev_addr,zero_x);
		Delay(1000000);
		PC_START_TRIGGER(X_AXIS);
		
		SERVO_SET_DISTANCE(Y_Dev_addr,zero_y);
		Delay(1000000);
		PC_START_TRIGGER(Y_AXIS);
	
		cylinder_get_zero();
		gripper_get_zero(gripper1_port);
		gripper_get_zero(gripper2_port);
	
	}

	if(finish_complete() == 1 && zero_move_allow_status == 1)
	{
		start_status_reset();
		zero_move_allow_status = 0;
		
		zero_start_status = 1;//防止LOOP不回零结束就直接往下走
		reset_button_status = 1;
	}
}

void cylinder_get_zero(void)
{
	cylinder_B_posix();
}


void gripper_get_zero(unsigned int gripper_number)
{
	Set_Y_Value(gripper_number,RELAXING);
}


void gripper_fastening(unsigned int gripper_number)
{
	Set_Y_Value(gripper_number,FASTENING);
	Delay(jiajin_time*100000);
}


void gripper_relaxing(unsigned int gripper_number)
{
	Set_Y_Value(gripper_number,RELAXING);
}


unsigned char gripper_relaxing_confirm(unsigned int gripper_confirm_port)
{
	return (Get_X_Value(gripper_confirm_port));
}


void Alarm_Lamp_On(void)
{
	Set_Y_Value(lamp_port,LAMP_ON);
}

void Alarm_Lamp_Off(void)
{
	Set_Y_Value(lamp_port,LAMP_OFF);
}

unsigned char signal_from_machine(unsigned char machine_port)
{
	return Get_X_Value(machine_port); 
}

void cylinder_A_posix(void)
{
	Set_Y_Value(cylinder_A_port,cylinder_HIGH);
	Set_Y_Value(cylinder_B_port,cylinder_LOW);
	//Delay(15000000);
}

void cylinder_B_posix(void)
{
	Set_Y_Value(cylinder_B_port,cylinder_HIGH);
	Set_Y_Value(cylinder_A_port,cylinder_LOW);
	//Delay(15000000);
}

unsigned char cylinder_A_posix_confirm()
{
	return Get_X_Value(cylinder_A_confirm_port);
}

unsigned char cylinder_B_posix_confirm()
{
	return Get_X_Value(cylinder_B_confirm_port);
}

void give_machine_signal(void)
{
	Set_Y_Value(give_machine_signal_port,MACHINE_HIGH);
	Delay(MACHINE_TRIGGER_TIME*100000);
	Set_Y_Value(give_machine_signal_port,MACHINE_LOW);
	
}

void gassing_start(void)
{
	Set_Y_Value(blowing_port,BLOWING_ON);
}

void gassing_off(void)
{
	Set_Y_Value(blowing_port,BLOWING_OFF);
}

void manual_gripper_1(void)
{
	if(gripper_1_button == 1 && manual_gripper_1_status == 0)
	{
		gripper_fastening(gripper1_port);
		
		manual_gripper_1_status = 1;
	}
	
	else if(gripper_1_button == 0 && manual_gripper_1_status == 1)
	{
		gripper_relaxing(gripper1_port);
		manual_gripper_1_status = 0;
	}
}

void manual_gripper_2(void)
{
	if(gripper_2_button == 1 && manual_gripper_2_status == 0)
	{
		gripper_fastening(gripper2_port);
		
		manual_gripper_2_status = 1;
	}
	
	else if(gripper_2_button == 0 && manual_gripper_2_status == 1)
	{
		gripper_relaxing(gripper2_port);
		manual_gripper_2_status = 0;
	}
}

void manual_cylinder_A(void)
{
	if(cylinder_A_button == 1 && manual_cylinder_A_status == 0)
	{
		cylinder_A_posix();
		manual_cylinder_A_status = 1;
	}
	else if(cylinder_A_button == 0 && manual_cylinder_A_status == 1)
	{
		cylinder_B_posix();
		manual_cylinder_A_status = 0;
	}
}
