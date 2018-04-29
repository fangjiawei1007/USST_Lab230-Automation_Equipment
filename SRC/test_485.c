#include "includes.h"



unsigned int move_x_status = 0;	//用于记录当前位置，主要用于判断上电的起始与结束位置，即开始结束位置
unsigned int move_y_status = 0;
unsigned int move_z_status = 0;

unsigned int handwheel_x_status = 0;
unsigned int handwheel_y_status = 0;
unsigned int handwheel_z_status = 0;

void set_speed_test(void)
{
	if(speed_set_number_x != speed_set_number_tmp_x)
	{
		SERVO_SET_SPEED(1,speed_set_number_x);
		
		speed_set_number_tmp_x = speed_set_number_x;
	}
	
	if(distance_set_number_x != distance_set_number_tmp_x)
	{
		SERVO_SET_DISTANCE(1,distance_set_number_x);
		
		distance_set_number_tmp_x = distance_set_number_x;
	}
	
	if(move_x_button == 1)
	{
		Set_Y_Value(1,0);
	}
	
	/* if(Get_X_Value(14) == 1)
		X_14 = 0;
	else 
		X_14 = 1;
	
	if(Get_X_Value(15) == 1)
		X_15 = 0;
	else 
		X_15 = 1; */
}

void manual_init(void)
{
	Set_Y_Value(X_AXIS,HIGH);
	Set_Y_Value(Y_AXIS,HIGH);
	Set_Y_Value(Z_AXIS,HIGH);
	
	SERVO_SET_SPEED(X_Dev_addr,speed_set_number_x);
	Delay(1000000);
	SERVO_SET_SPEED(Y_Dev_addr,speed_set_number_y);
	Delay(1000000);
	SERVO_SET_SPEED(Z_Dev_addr,speed_set_number_z);
	Delay(1000000);
	
}
void set_speed_distance_485(void)
{
	
	//设置x速度
	if(speed_set_number_x != speed_set_number_tmp_x)

	{
		SERVO_SET_SPEED(X_Dev_addr,speed_set_number_x);
		
		speed_set_number_tmp_x = speed_set_number_x;
	}
	
	//设置y速度
	if(speed_set_number_y != speed_set_number_tmp_y)

	{
		SERVO_SET_SPEED(Y_Dev_addr,speed_set_number_y);
		
		speed_set_number_tmp_y = speed_set_number_y;
	}
	
	//设置z速度
	if(speed_set_number_z != speed_set_number_tmp_z)

	{
		SERVO_SET_SPEED(Z_Dev_addr,speed_set_number_z);
		
		speed_set_number_tmp_z = speed_set_number_z;
	}
	
	
	//设置x距离
	if(distance_set_number_x != distance_set_number_tmp_x)

	{
		SERVO_SET_DISTANCE(X_Dev_addr,distance_set_number_x);
		
		distance_set_number_tmp_x = distance_set_number_x;
	}
	
	//设置y距离
	if(distance_set_number_y != distance_set_number_tmp_y)

	{
		SERVO_SET_DISTANCE(Y_Dev_addr,distance_set_number_y);
		
		distance_set_number_tmp_y = distance_set_number_y;
	}
	
	//设置z距离
	if(distance_set_number_z != distance_set_number_tmp_z)

	{
		SERVO_SET_DISTANCE(Z_Dev_addr,distance_set_number_z);
		
		distance_set_number_tmp_z = distance_set_number_z;
	}
	
}


void move_manually(void)
{
	
///////////////////////////////X轴运动////////////////////////////////////////////////	
	if(move_x_button == 1 && (Get_X_Value(x_position_finish) == FINISH) && move_x_status == 0)
	{
		PC_START_TRIGGER(X_AXIS);
		
		move_x_status = 1;	//记录当前状态
	}
	
	else if(move_x_button == 0 && (Get_X_Value(x_position_finish) == UNFINISH) &&  move_x_status == 1)
	{
		//SERVO_STOP(X_Dev_addr);
		// SERVO_STOP_1(0x01);
		// SERVO_STOP_2(0x01);
		
		move_x_status = 0;
	}
	
	else if(move_x_button == 1 && (Get_X_Value(x_position_finish) == FINISH) && move_x_status == 1)
	{
		
		move_x_status = 0;	//记录当前状态
		move_x_button = 0;
	}
	
//////////////////////////////Y轴运动////////////////////////////////////////////////////////	
	if(move_y_button == 1 && (Get_X_Value(y_position_finish) == FINISH) && move_y_status == 0)
	{
		PC_START_TRIGGER(Y_AXIS);
		move_y_status = 1;	//记录当前状态
	}
	
	else if(move_y_button == 0 && (Get_X_Value(y_position_finish) == UNFINISH) &&  move_y_status == 1)
	{
		//SERVO_STOP(Y_Dev_addr);
		move_y_status = 0;
	}
	
	else if(move_y_button == 1 && (Get_X_Value(y_position_finish) == FINISH) && move_y_status == 1)
	{
		move_y_button = 0;
		move_y_status = 0;	//记录当前状态
	}
	
/////////////////////////////Z轴运动//////////////////////////////////////////////////////////////	
	if(move_z_button == 1 && (Get_X_Value(z_position_finish) == FINISH) && move_z_status == 0)
	{
		PC_START_TRIGGER(Z_AXIS);
		move_z_status = 1;	//记录当前状态
	}
	
	else if(move_z_button == 0 && (Get_X_Value(z_position_finish) == UNFINISH) &&  move_z_status == 1)
	{
		//SERVO_STOP(Z_Dev_addr);//
		move_z_status = 0;
	}
	
	else if(move_z_button == 1 && (Get_X_Value(z_position_finish) == FINISH) && move_z_status == 1)
	{
		move_z_button = 0;
		move_z_status = 0;	//记录当前状态
	}
}


void zero_confirm(void)
{
	if(x_zero_confirm_button == 1)
	{
		zero_x = distance_set_number_x;
	}
	
	if(y_zero_confirm_button == 1)
	{
		zero_y = distance_set_number_y;
	}
	
	if(z_zero_confirm_button == 1)
	{
		zero_z = distance_set_number_z;
	}
}


void handwheel_parament_init(void)
{
	handwheel_x_speed = 500;
	handwheel_y_speed = 500;
	handwheel_z_speed = 500;
	
	handwheel_x_position = 0;
	handwheel_y_position = 0;
	handwheel_z_position = 0;
	
	handwheel_x_speed_tmp = handwheel_x_speed;
	handwheel_y_speed_tmp = handwheel_y_speed;
	handwheel_z_speed_tmp = handwheel_z_speed;
}

void handwheel_init(void)
{
	SERVO_SET_SPEED(X_Dev_addr,handwheel_x_speed);
	Delay(1000000);
	SERVO_SET_SPEED(Y_Dev_addr,handwheel_y_speed);
	Delay(1000000);
	SERVO_SET_SPEED(Z_Dev_addr,handwheel_z_speed);
	Delay(1000000);
	
	SERVO_GET_POSITION(X_Dev_addr);
	Delay(1000000);
	SERVO_GET_POSITION(Y_Dev_addr);
	Delay(1000000);
	SERVO_GET_POSITION(Z_Dev_addr);
	Delay(1000000);
	
}


void handwheel_set_speed(void)
{
	//设置x速度
	if(handwheel_x_speed != handwheel_x_speed_tmp)

	{
		SERVO_SET_SPEED(X_Dev_addr,handwheel_x_speed);
		
		handwheel_x_speed_tmp = handwheel_x_speed;
	}
	
	//设置y速度
	if(handwheel_y_speed != handwheel_y_speed_tmp)

	{
		SERVO_SET_SPEED(X_Dev_addr,handwheel_y_speed);
		
		handwheel_y_speed_tmp = handwheel_y_speed;
	}
	
	//设置z速度
	if(handwheel_z_speed != handwheel_z_speed_tmp)

	{
		SERVO_SET_SPEED(X_Dev_addr,handwheel_z_speed);
		
		handwheel_z_speed_tmp = handwheel_z_speed;
	}
}

void handwheel_x_stop(void)
{
	
}

void handwheel_y_stop(void)
{
	
}

void handwheel_z_stop(void)
{
	
}