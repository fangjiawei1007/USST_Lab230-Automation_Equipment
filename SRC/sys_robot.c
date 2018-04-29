#include "includes.h"

void parameters_init(void)
{
	if (Init_flag != 1)
	{
		finish_status = 0;
		
		speed_set_number_tmp_x= 0;
		speed_set_number_x = 0;
		
		distance_set_number_tmp_x = 0;
		distance_set_number_x = 0;
		
		speed_set_number_tmp_y= 0;
		speed_set_number_y = 0;
		
		distance_set_number_tmp_y = 0;
		distance_set_number_y = 0;
		
		speed_set_number_tmp_z= 0;
		speed_set_number_z = 0;
		
		distance_set_number_tmp_z = 0;
		distance_set_number_z = 0;
		
		zero_x = 0;
		zero_y = 0;
		zero_z = 0;
		
		gongjian_hangshu = 10;
		gongjian_lieshu = 10;
		gongjian_hangjianju = 10;
		gongjian_liejianju = 10;
		
		yuandian_gongzuotai_distance = 10000;
		yuandian_1_gongjian_distance = 1000;
		
		jiajin_time = 10;
		
		z_get_position = 100;
		z_offset_position = 20;
		
		z_work_position = 70;
		x_offset_position = 10;
		
		gongjian_hangshu_tmp = 1;
		gongjian_lieshu_tmp = 1;
		
		gongjian_total = 0;
		
		x_offset_speed = 500;
		z_up_offset_distance = 500;
		
		MACHINE_TRIGGER_TIME = 350;
		
		status_reset();
		zero_finish_status = 0;
		zero_start_status = 0;
		pulse_signal = 0;
		
		handwheel_parament_init();
	}
	
	Init_flag = 1;
}


void PC_START_TRIGGER(char	AXIS)
{
		Set_Y_Value(AXIS,LOW);
		
		Delay(1000000);	//此处不延时会导致，伺服电机驱动器反应速度不够，无法运行。
		
		Set_Y_Value(AXIS,HIGH);
}

void Trigger_Move(int DevAddr, char AXIS, unsigned int Distance)
{
	SERVO_SET_DISTANCE(DevAddr,Distance);
	Delay(100000);
	
	PC_START_TRIGGER(AXIS);
	
}
/* void Servo_Off(void)
{
	Set_Y_Value(Servo_port,HIGH);
} */

void Button_Init(void)
{
	start_button = 0;
	reset_button = 0;
	
	move_x_button = 0;
	move_y_button = 0;
	move_z_button = 0;
	
	gripper_1_button = 0;
	gripper_2_button = 0;
	cylinder_A_button = 0;
	
	handwheel_start_button = 0;
	
	handwheel_x = 0;
	handwheel_y = 0;
	handwheel_z = 0;
	
	position_x_get = 0;
	position_y_get = 0;
	position_z_get = 0;

}

unsigned int finish_complete(void)
{
	if(Get_X_Value(x_position_finish) == FINISH && Get_X_Value(y_position_finish) == FINISH && Get_X_Value(z_position_finish) == FINISH
		&& gripper_relaxing_confirm(gripper1_port) == RELAXING && gripper_relaxing_confirm(gripper2_port) == RELAXING
		&& cylinder_B_posix_confirm() == CONFIRM)
		return 1;

	else
		return 0;

}

void condition_monitor(void)
{
	if(clear_extern_button == 1)
		gongjian_total = 0;
		
	gongjian_hangshu_monitor = gongjian_hangshu_tmp;
	gongjian_lieshu_monitor = gongjian_lieshu_tmp;
	gongjian_total_monitor = gongjian_total;
	
	
}

void Button_mutex(unsigned char* button0, unsigned char* button1, unsigned int* status_record,  unsigned int condition_flag)
{
	
	if(*button0 == 1 || *button1 ==1)
	{
		if(*status_record == 0)
		{
				if(*button1 == 1)
				{
					*button0 =0;
					*status_record = 1;
				}
		}
		
		else 
		{
			if(*button0 == 1)
			{
				*button1 = 0;
				*status_record = 0;
			}
		}
		condition_flag = 1;		//condition_flag用于判断点动同时停和启动条件
	}
	
	else if((*button0 == 0) && (*button1 == 0))		//此处修改= 为== 之前有逻辑小错误。2017.2.7 下午进行测试
	{
		
		*status_record = 0;
		condition_flag = 0;
		
	}
	
	
}