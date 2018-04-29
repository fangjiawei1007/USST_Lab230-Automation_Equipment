#ifndef _SYS_ROBOT_H_
#define _SYS_ROBOT_H_

#define Init_flag				(g_InteralMemory.KeepBit[500])

#define start_button			g_InteralMemory.KeepBit[13]
#define reset_button			g_InteralMemory.KeepBit[14]


#define X_Dev_addr				1
#define Y_Dev_addr				2
#define Z_Dev_addr				3


#define X_AXIS					1
#define Y_AXIS					2
#define Z_AXIS					3


#define HIGH					1
#define LOW						0

#define cylinder_HIGH			1
#define cylinder_LOW			0

#define CONFIRM					0

#define x_position_finish		15
#define y_position_finish		14
#define z_position_finish		13
//注：上述三个为伺服电机MEND借口

#define FINISH  				0
#define UNFINISH  				1

#define gongjian_hangshu		g_InteralMemory.KeepWord[20]
#define gongjian_lieshu			g_InteralMemory.KeepWord[21]
#define gongjian_hangjianju		g_InteralMemory.KeepWord[22]
#define gongjian_liejianju		g_InteralMemory.KeepWord[23]
#define jiajin_time				g_InteralMemory.KeepWord[26]
#define z_get_position			g_InteralMemory.KeepWord[27]
#define z_offset_position		g_InteralMemory.KeepWord[28]
#define z_work_position			g_InteralMemory.KeepWord[29]
#define x_offset_position		g_InteralMemory.KeepWord[19]
#define x_offset_speed			g_InteralMemory.KeepWord[18]

#define clear_extern_button					g_InteralMemory.KeepBit[15]
#define gripper_external_button				g_InteralMemory.KeepBit[20]

//yuandian_gongzuotai_distance 改为第一个工件至加工位置，宏定义修改复杂，直接在函数中修改
#define yuandian_gongzuotai_distance		g_InteralMemory.KeepWord[24]
#define yuandian_1_gongjian_distance		g_InteralMemory.KeepWord[25]


#define gongjian_total						g_InteralMemory.KeepWord[499]

#define gongjian_hangshu_monitor			g_InteralMemory.KeepWord[40]
#define gongjian_lieshu_monitor				g_InteralMemory.KeepWord[41]
#define gongjian_total_monitor				g_InteralMemory.KeepWord[42]


void parameters_init(void);
void Button_Init(void);

void PC_START_TRIGGER(char	AXIS);	//IO使能
//void Servo_Off(void);
void Trigger_Move(int DevAddr,char	AXIS,unsigned int Distance);	//触发信号
unsigned int finish_complete(void);
void condition_monitor(void);
void Button_mutex(unsigned char* button0, unsigned char* button1, unsigned int* status_record,  unsigned int condition_flag);

#endif