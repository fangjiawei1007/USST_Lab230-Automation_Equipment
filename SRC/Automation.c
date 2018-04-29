#include "includes.h"

unsigned int y_trigger_status = 0;
unsigned int add_status = 0;
unsigned int start_b_robot_status = 0;	//用作暂停功能

void Loop_Robot(void)
{
	
	//做完一轮小循环来此处判断一下，并将循环所需要用到的status 置零
	if(add_status == 1 && gongjian_hangshu_tmp < gongjian_hangshu)
	{
		Trigger_Move(Y_Dev_addr,Y_AXIS,(zero_y+(gongjian_hangjianju*(gongjian_hangshu_tmp))));
		
		if((Get_X_Value(y_position_finish) == UNFINISH))
		{
			//Delay(20000000);
			y_trigger_status = 1;
		}

		
		if(y_trigger_status == 1)
		{
			if ((Get_X_Value(y_position_finish) == FINISH))
			{
				y_trigger_status = 0;
				gongjian_hangshu_tmp ++;//运动完之后一轮之后，行数++。
				gongjian_lieshu_tmp = 1;
				add_status = 0;
				
				status_reset();
			}

		}
		
	}
	else if(add_status == 1 && gongjian_hangshu_tmp == gongjian_hangshu)
	{
		//此处为finish所有工作
		//Beep(1);
		everythig_get_zero();
	
		if(finish_complete() == 1)
		{
			finish_status = 1;
			add_status = 0;
		}
	}
		
		
	if((gongjian_hangshu_tmp <= gongjian_hangshu) && (gongjian_lieshu_tmp <= gongjian_liejianju) && finish_status == 0)
	{
			//
			if(gongjian_lieshu_tmp <= gongjian_lieshu)
			{
				
				//2nd X轴移动到达第n个工件位置
				if((loading_x_1_start_status == 0) && (loading_x_1_finish_status == 0) && (y_moving_finish == 0)  )
				{
					
					Trigger_Move(X_Dev_addr,X_AXIS,(yuandian_1_gongjian_distance + (gongjian_lieshu_tmp - 1)*gongjian_liejianju));
					
					if((Get_X_Value(x_position_finish) == UNFINISH)  || pulse_signal == 1)	//当X轴未开始的时候，继续发送命令，此处UNFINISH为开始
					{
						loading_x_1_start_status = 1;

						if (pulse_signal == 1)
							pulse_signal = 0;
					}
					else
						loading_x_1_start_status = 0; 
				}
				
				
				else if(loading_x_1_start_status == 1 && (Get_X_Value(x_position_finish) == FINISH)  )	//此处UNFINISH为测试用 FINISH为实际用)
				{
					
					loading_x_1_start_status = 0;
					loading_x_1_finish_status = 1;
				}
				
				
					
				//3rd Z轴下移到工位(取样)
				if((loading_x_1_finish_status == 1) && (loading_z_down_1_start_status == 0) && (loading_z_down_1_finish_status == 0))
				{
					//Beep(1);
					Trigger_Move(Z_Dev_addr,Z_AXIS,(z_get_position));
					
					if((Get_X_Value(z_position_finish) == UNFINISH)  || pulse_signal == 1)
					{
						loading_z_down_1_start_status = 1;
						if (pulse_signal == 1)
							pulse_signal = 0;
					}
					else
						loading_z_down_1_start_status = 0;
				}
				
				else if((loading_z_down_1_start_status == 1) &&  (Get_X_Value(z_position_finish) == FINISH))
				{
					Delay(10000000);
					loading_z_down_1_start_status = 0;
					loading_z_down_1_finish_status = 1;
				}
				
				//4th 机械手1在上料处夹紧
				if(loading_z_down_1_finish_status == 1 && gripper1_1_fastening_start_status == 0 && gripper1_1_fastening_finish_status == 0)
				{
					gripper_fastening(gripper1_port);
					
					gripper1_1_fastening_start_status = 1;
				}
				
				else if((gripper1_1_fastening_start_status == 1) && (gripper_relaxing_confirm(gripper1_confirm_port) == FASTENING))
				{
					gripper1_1_fastening_start_status = 0;
					gripper1_1_fastening_finish_status = 1;
				}
				
				//5th Z轴上移到位 零点位置()
				if((gripper1_1_fastening_finish_status == 1) && (loading_z_up_1_start_status == 0)  && (loading_z_up_1_finish_status == 0))
				{
					Trigger_Move(Z_Dev_addr,Z_AXIS,(zero_z));
					
					if((Get_X_Value(z_position_finish) == UNFINISH)  || pulse_signal == 1)//UNFINISH 此处表示已经开始
					{
						loading_z_up_1_start_status = 1;
						if(pulse_signal == 1)
							pulse_signal = 0;
					}
					
					else
						loading_z_up_1_start_status = 0;
				}
				
				else if(loading_z_up_1_start_status == 1 && (Get_X_Value(z_position_finish) == FINISH)  )
				{
					loading_z_up_1_start_status = 0;
					loading_z_up_1_finish_status = 1;
				}
				/* 
				//6th 气缸旋转到位置A，位置A为ADVANCED，取夹成品
				if(loading_z_up_1_finish_status == 1 && cylinder_rotate_A_1_start_status == 0 && cylinder_rotate_A_1_finish_status == 0)
				{
					cylinder_A_posix();
					Delay(15000000);
					
					cylinder_rotate_A_1_start_status = 1;
				}
				
				else if(cylinder_rotate_A_1_start_status == 1 && (cylinder_A_posix_confirm() == CONFIRM))
				{
					cylinder_rotate_A_1_start_status = 0;
					cylinder_rotate_A_1_finish_status = 1;
				}
				 */
				
				//7th X轴移动到工作位置-OFFSET,因为夹具原因
				if(loading_z_up_1_finish_status == 1 && blanking_x_2_start_status == 0 && blanking_x_2_finish_status == 0  )//cylinder_rotate_A_1_finish_status
				{
					Trigger_Move(X_Dev_addr,X_AXIS,(yuandian_gongzuotai_distance + yuandian_1_gongjian_distance - x_offset_position));
					
					if((Get_X_Value(x_position_finish) == UNFINISH) || pulse_signal == 1)
					{
						blanking_x_2_start_status = 1;
						
						if(pulse_signal == 1)
							pulse_signal = 0;
					}
					else
						blanking_x_2_start_status = 0;
				}
				
				else if(blanking_x_2_start_status == 1 && (Get_X_Value(x_position_finish) == FINISH)  )
				{
					blanking_x_2_start_status = 0;
					blanking_x_2_finish_status = 1;
				}
				
				//8th Z轴到达位置2 工作台，Z轴下
				if(blanking_x_2_finish_status == 1 && blanking_z_down_2_start_status == 0 && blanking_z_down_2_finish_status == 0 
				  && signal_from_machine(signal_from_machine_port) == SIGNAL_FROM_MACHINE  )
				{
					Trigger_Move(Z_Dev_addr,Z_AXIS,(z_work_position));	
					
					if((Get_X_Value(z_position_finish) == UNFINISH) || pulse_signal == 1)//此处UNFINISH 为启动信号
					{
						blanking_z_down_2_start_status = 1;
						if(pulse_signal == 1)
							pulse_signal = 0;
					}
					else 
						blanking_z_down_2_start_status = 0;
				}
				
				else if(blanking_z_down_2_start_status == 1 && (Get_X_Value(z_position_finish) == FINISH)  )
				{
					blanking_z_down_2_start_status = 0;
					blanking_z_down_2_finish_status = 1;
				}
				//8.5th X轴进入偏移位置
				if(blanking_z_down_2_finish_status == 1 && x_offset_in_1st_start_status == 0 && x_offset_in_1st_finish_status == 0  )
				{

					Trigger_Move(X_Dev_addr,X_AXIS,(yuandian_gongzuotai_distance + yuandian_1_gongjian_distance));

					if((Get_X_Value(x_position_finish) == UNFINISH) || pulse_signal == 1)
					{
						x_offset_in_1st_start_status = 1;
						if(pulse_signal == 1)
							pulse_signal = 0;
					}
					else 
						x_offset_in_1st_start_status = 0;
				}
					
				else if(x_offset_in_1st_start_status == 1 && (Get_X_Value(x_position_finish) == FINISH)  )
				{
					x_offset_in_1st_start_status = 0;
					x_offset_in_1st_finish_status = 1;
				}
				
				//9th 机械手2夹紧
				if(x_offset_in_1st_finish_status == 1 && gripper2_2_fastening_start_status == 0 &&  gripper2_2_fastening_finish_status == 0  )
				{
					gripper_fastening(gripper2_port);
					gripper2_2_fastening_start_status = 1;	
				}
				
				else if(gripper2_2_fastening_start_status == 1 && (gripper_relaxing_confirm(gripper2_confirm_port) == FASTENING)  )
				{
					gripper2_2_fastening_start_status = 0;
					gripper2_2_fastening_finish_status = 1;

				}
				
				//10th X轴移动出去
				if(gripper2_2_fastening_finish_status == 1 && x_offset_out_start_status == 0 && x_offset_out_finish_status == 0  )
				{
					Trigger_Move(X_Dev_addr,X_AXIS,(yuandian_gongzuotai_distance + yuandian_1_gongjian_distance -x_offset_position));
					
					if((Get_X_Value(x_position_finish) == UNFINISH) || pulse_signal == 1)
					{
						x_offset_out_start_status = 1;
						if(pulse_signal == 1)
							pulse_signal = 0;
					}
					else
						x_offset_out_start_status = 0;
				}
				
				else if(x_offset_out_start_status == 1 && (Get_X_Value(x_position_finish) == FINISH)  )
				{
					x_offset_out_start_status = 0;
					x_offset_out_finish_status = 1;
				}
				
				//10.5th Z轴向上移动偏移量50-150mm
				if(x_offset_out_finish_status == 1 && z_up_offset_start == 0 && z_up_offset_finish == 0  )
				{
					Trigger_Move(Z_Dev_addr,Z_AXIS,(z_work_position - z_up_offset_distance));	
					
					if((Get_X_Value(z_position_finish) == UNFINISH) || pulse_signal == 1)//此处UNFINISH 为启动信号
					{
						z_up_offset_start = 1;
						if(pulse_signal == 1)
							pulse_signal = 0;
					}
					else 
						z_up_offset_start = 0;
					
				}
				
				else if(z_up_offset_start == 1 && z_up_offset_finish == 0 && (Get_X_Value(z_position_finish) == FINISH)  )
				{
					z_up_offset_start = 0;
					z_up_offset_finish = 1;
				}
				
				//11th 气缸旋转到位置A, 装毛坯
				if(z_up_offset_finish == 1 && cylinder_rotate_B_2_start_status == 0 && cylinder_rotate_B_2_finish_status == 0  )
				{
					SERVO_SET_SPEED(X_Dev_addr,x_offset_speed);		//进去的速度为慢速，多做几次以保障发送成功
					cylinder_A_posix();
					Delay(15000000);
					
					//SERVO_SET_SPEED(X_Dev_addr,x_offset_speed);		//进去的速度为慢速，多做几次以保障发送成功
					Delay(15000000);
					cylinder_rotate_B_2_start_status = 1;
				}
				
				else if(cylinder_rotate_B_2_start_status == 1 && cylinder_A_posix_confirm() == CONFIRM  )
				{
					cylinder_rotate_B_2_start_status = 0;
					cylinder_rotate_B_2_finish_status = 1;
				}
				
				//11.5th Z轴向下移动偏移量50-150mm
				if(cylinder_rotate_B_2_finish_status == 1 && z_down_offset_start == 0 && z_down_offset_finish == 0  )
				{
					Trigger_Move(Z_Dev_addr,Z_AXIS,(z_work_position));
					
					if((Get_X_Value(z_position_finish) == UNFINISH) || pulse_signal == 1)//此处UNFINISH 为启动信号
					{
						z_down_offset_start = 1;
						if(pulse_signal == 1)
							pulse_signal = 0;
					}
					else 
						z_down_offset_start = 0;
					
				}
				
				else if(z_down_offset_start == 1 && z_down_offset_finish == 0 && (Get_X_Value(z_position_finish) == FINISH)  )
				{
					//SERVO_SET_SPEED(X_Dev_addr,x_offset_speed);//进去的速度为慢速，多做几次以保障发送成功
					Delay(10000000);
					z_down_offset_start = 0;
					z_down_offset_finish = 1;
				}
				
				
				//12th X轴移动进去偏移量，装紧夹具
				if(z_down_offset_finish == 1 && x_offset_in_start_status == 0 && x_offset_in_finish_status == 0  )
				{

					Trigger_Move(X_Dev_addr,X_AXIS,(yuandian_gongzuotai_distance + yuandian_1_gongjian_distance));

					if((Get_X_Value(x_position_finish) == UNFINISH) || pulse_signal == 1)
					{
						x_offset_in_start_status = 1;
						if(pulse_signal == 1)
							pulse_signal = 0;
					}
					else 
						x_offset_in_start_status = 0;
				}
					
				else if(x_offset_in_start_status == 1 && (Get_X_Value(x_position_finish) == FINISH)  )
				{
					x_offset_in_start_status = 0;
					x_offset_in_finish_status = 1;
				}
				
				//13th 机械手1 松开
				if(x_offset_in_finish_status == 1 && gripper1_2_relaxing_start_status == 0 && gripper1_2_relaxing_finish_status == 0  )
				{
					gripper_relaxing(gripper1_port);
					Delay(15000000);
					gripper1_2_relaxing_start_status = 1;
				}
				
				else if(gripper1_2_relaxing_start_status == 1 && (gripper_relaxing_confirm(gripper1_confirm_port) == RELAXING)  )
				{
					gripper1_2_relaxing_start_status = 0;
					gripper1_2_relaxing_finish_status = 1;
				}
				
				
				//13.5th X轴需要移动出去偏移量X_OFFSET
				if(gripper1_2_relaxing_finish_status == 1 && x_offset_in_3rd_start_status == 0 && x_offset_in_3rd_finish_status == 0  )
				{
					Trigger_Move(X_Dev_addr,X_AXIS,(yuandian_gongzuotai_distance + yuandian_1_gongjian_distance - x_offset_position));

					if((Get_X_Value(x_position_finish) == UNFINISH) || pulse_signal == 1)
					{
						x_offset_in_3rd_start_status = 1;
						if(pulse_signal == 1)
							pulse_signal = 0;
					}
					else 
						x_offset_in_3rd_start_status = 0;
				}
					
				else if(x_offset_in_3rd_start_status == 1 && (Get_X_Value(x_position_finish) == FINISH)  )
				{
					x_offset_in_3rd_start_status = 0;
					x_offset_in_3rd_finish_status = 1;
				}
				
				//14th Z轴到位 2 上
				if(x_offset_in_3rd_finish_status == 1 && blanking_z_up_2_start_status == 0 && blanking_z_up_2_finish_status == 0  )
				{
					Trigger_Move(Z_Dev_addr,Z_AXIS,(zero_z));	
							//X轴恢复原来速度为快速，多做几次以保证发送成功
					
					if((Get_X_Value(z_position_finish) == UNFINISH) || pulse_signal == 1)
					{
						blanking_z_up_2_start_status = 1;
						if(pulse_signal == 1)
							pulse_signal = 0;
					}
					else
						blanking_z_up_2_start_status = 0;
				}
				
				else if(blanking_z_up_2_start_status == 1 && (Get_X_Value(z_position_finish) == FINISH) && (Get_X_Value(Z_Limit_Port) == 0))
				{
					blanking_z_up_2_start_status = 0;
					blanking_z_up_2_finish_status = 1;
					SERVO_SET_SPEED(X_Dev_addr,speed_set_number_x);
					give_machine_signal();
					
					Delay(1000000);
				}
				
				//15th 气缸旋转到位置A，由于夹具原因，此处不需要旋转 2017.8.17 
			/* 	
				if(blanking_z_up_2_finish_status == 1 && cylinder_rotate_A_2_start_status == 0 && cylinder_rotate_A_2_finish_status == 0)
				{
					// gassing_off();
					cylinder_A_posix();
					// SERVO_SET_SPEED(X_Dev_addr,speed_set_number_x);//X轴恢复原来速度为快速，多做几次以保证发送成功
					Delay(15000000);
					
					cylinder_rotate_A_2_start_status = 1;
				}
				
				else if(cylinder_rotate_A_2_start_status == 1 && cylinder_A_posix_confirm() == CONFIRM)
				{
					cylinder_rotate_A_2_start_status = 0;
					cylinder_rotate_A_2_finish_status = 1;
				} */
				
				
				//16th X轴右移到达下料位置
				if(blanking_z_up_2_finish_status == 1 && blowing_x_1_start_status == 0 && blowing_x_1_finish_status == 0 && (Get_X_Value(Z_Limit_Port) == 0))//cylinder_rotate_A_2_finish_status
				{
					//SERVO_SET_SPEED(X_Dev_addr,speed_set_number_x);//X轴恢复原来速度为快速，多做几次以保证发送成功
					Trigger_Move(X_Dev_addr,X_AXIS,(yuandian_1_gongjian_distance + (gongjian_lieshu_tmp-1)*gongjian_liejianju));
					// Beep(1);
					// Delay(100000000);
					// Beep(0);
					if((Get_X_Value(x_position_finish) == UNFINISH) || pulse_signal == 1)
					{
						blowing_x_1_start_status = 1;
						if(pulse_signal == 1)
							pulse_signal = 0;
					}
					else 
						blowing_x_1_start_status = 0;
				}
				
				else if(blowing_x_1_start_status == 1 && (Get_X_Value(x_position_finish) == FINISH)  )	
				{
					blowing_x_1_start_status = 0;
					blowing_x_1_finish_status = 1;
				}
				
				//17th Z轴到达放料位置
				if(blowing_x_1_finish_status == 1 && blowing_z_down_1_start_status == 0 && blowing_z_down_1_finish_status == 0  )
				{
					Trigger_Move(Z_Dev_addr,Z_AXIS,(z_get_position - 50)); 
					
					if((Get_X_Value(z_position_finish) == UNFINISH) || pulse_signal == 1)
					{
						blowing_z_down_1_start_status = 1;
						if(pulse_signal == 1)
							pulse_signal = 0;
					}
						
					else
						blowing_z_down_1_start_status = 0;
				}
				
				else if(blowing_z_down_1_start_status == 1 && (Get_X_Value(z_position_finish) == FINISH)  )
				{
					blowing_z_down_1_start_status = 0;
					blowing_z_down_1_finish_status = 1;
				}
				
				//18th 机械手2放松
				if(blowing_z_down_1_finish_status == 1 && gripper2_1_relaxing_start_status == 0 && gripper2_1_relaxing_finish_status == 0  )
				{
					gripper_relaxing(gripper2_port);
					Delay(15000000);
					gripper2_1_relaxing_start_status = 1;
				}
				
				else if(gripper2_1_relaxing_start_status == 1 && (gripper_relaxing_confirm(gripper2_confirm_port) == RELAXING)  )
				{
					gripper2_1_relaxing_start_status = 0;
					gripper2_1_relaxing_finish_status = 1;
				}
				
				//19th Z轴上移到位
				if(gripper2_1_relaxing_finish_status == 1 && blowing_z_up_1_start_status == 0 && blowing_z_up_1_finish_status == 0  )
				{
					Trigger_Move(Z_Dev_addr,Z_AXIS,(z_get_position-z_offset_position));
					
					if((Get_X_Value(z_position_finish) == UNFINISH) || pulse_signal == 1)
					{
						blowing_z_up_1_start_status = 1;
						if(pulse_signal == 1)
							pulse_signal = 0;
					}	
					else 
						blowing_z_up_1_start_status = 0;
				}
				
				else if(blowing_z_up_1_start_status == 1 && (Get_X_Value(z_position_finish) == FINISH)  )
				{
					Delay(10000000);
					Delay(10000000);
					blowing_z_up_1_start_status = 0;
					blowing_z_up_1_finish_status = 1;
				}
				
				//20th 旋转气缸至B位置
				if(blowing_z_up_1_finish_status == 1 && cylinder_rotate_B_1_start_status == 0 && cylinder_rotate_B_1_finish_status == 0  )
				{
					cylinder_B_posix();
					Delay(15000000);
					Delay(15000000);
					cylinder_rotate_B_1_start_status = 1;
				}
				
				else if(cylinder_rotate_B_1_start_status == 1 && (cylinder_B_posix_confirm() == CONFIRM)  )
				{
					cylinder_rotate_B_1_start_status = 0;
					cylinder_rotate_B_1_finish_status = 1;
				}
				
				//finish
				if(cylinder_rotate_B_1_finish_status == 1)
				{
					status_reset();
					
					if(gongjian_lieshu_tmp == gongjian_lieshu)
					{
						add_status = 1;
						y_moving_finish = 1;
					}
					
					if(gongjian_lieshu_tmp < gongjian_lieshu && add_status == 0)
						gongjian_lieshu_tmp ++;
					
					gongjian_total ++;
				}
					
			}

	}
}


void status_reset(void)
{
	loading_x_1_start_status = 0;
	loading_x_1_finish_status = 0;
	
	loading_z_down_1_start_status = 0;
	loading_z_down_1_finish_status = 0;
	
	gripper1_1_fastening_start_status = 0;
	gripper1_1_fastening_finish_status = 0;
	
	loading_z_up_1_start_status = 0;
	loading_z_up_1_finish_status = 0;
	
	cylinder_rotate_A_1_start_status = 0;
	cylinder_rotate_A_1_finish_status = 0;
	
	blanking_x_2_start_status = 0;
	blanking_x_2_finish_status = 0;
	
	blanking_z_down_2_start_status = 0;
	blanking_z_down_2_finish_status = 0;
	
	gripper2_2_fastening_start_status = 0;
	gripper2_2_fastening_finish_status = 0;
	
	x_offset_out_start_status = 0;
	x_offset_out_finish_status = 0;
	
	cylinder_rotate_B_2_start_status = 0;
	cylinder_rotate_B_2_finish_status = 0;
	
	x_offset_in_start_status = 0;
	x_offset_in_finish_status = 0;
	
	gripper1_2_relaxing_start_status = 0;
	gripper1_2_relaxing_finish_status = 0;
	
	blanking_z_up_2_start_status = 0;
	blanking_z_up_2_finish_status = 0;
	
	cylinder_rotate_A_2_start_status = 0;
	cylinder_rotate_A_2_finish_status = 0;
	
	blowing_x_1_start_status = 0;
	blowing_x_1_finish_status = 0;
	
	blowing_z_down_1_start_status = 0;
	blowing_z_down_1_finish_status = 0;
	
	gripper2_1_relaxing_start_status = 0;
	gripper2_1_relaxing_finish_status = 0;
	
	blowing_z_up_1_start_status = 0;
	blowing_z_up_1_finish_status = 0;
	
	cylinder_rotate_B_1_start_status = 0;
	cylinder_rotate_B_1_finish_status = 0;

	z_up_offset_start = 0;
	z_up_offset_finish = 0;
	
	z_down_offset_start	= 0;
	z_down_offset_finish =0;
	
	y_moving_finish = 0;
	
	x_offset_in_1st_start_status = 0;
	x_offset_in_1st_finish_status = 0;
	
	x_offset_in_3rd_start_status = 0;
	x_offset_in_3rd_finish_status = 0;
}

void start_status_reset(void)
{
	loading_x_1_start_status = 0;

	loading_z_down_1_start_status = 0;

	gripper1_1_fastening_start_status = 0;

	loading_z_up_1_start_status = 0;

	blanking_x_2_start_status = 0;

	cylinder_rotate_A_1_start_status = 0;

	blanking_z_down_2_start_status = 0;

	gripper2_2_fastening_start_status = 0;

	x_offset_out_start_status = 0;

	cylinder_rotate_B_2_start_status = 0;

	x_offset_in_start_status = 0;

	gripper1_2_relaxing_start_status = 0;

	blanking_z_up_2_start_status = 0;

	cylinder_rotate_A_2_start_status = 0;

	blowing_x_1_start_status = 0;

	blowing_z_down_1_start_status = 0;

	gripper2_1_relaxing_start_status = 0;

	blowing_z_up_1_start_status = 0;

	cylinder_rotate_B_1_start_status = 0;
	
	z_up_offset_start = 0;
	
	z_down_offset_start	= 0;
	
	x_offset_in_1st_start_status = 0;
	
	x_offset_in_3rd_start_status = 0;
	
}
void RESET(void)
{
	if(gripper_relaxing_confirm(gripper1_confirm_port )== RELAXING 
		&& gripper_relaxing_confirm(gripper1_confirm_port )== RELAXING)
	{
		everythig_get_zero();
	}
	
	gongjian_hangshu_tmp = 1;
	gongjian_lieshu_tmp = 1;
	
}