#ifndef _AUTOMATION_H_
#define _AUTOMATION_H_

#define SIGNAL_FROM_MACHINE					0

#define start_status_no_use					g_InteralMemory.KeepWord[98]
#define finish_status						g_InteralMemory.KeepWord[99]

#define gongjian_hangshu_tmp				g_InteralMemory.KeepWord[100]
#define gongjian_lieshu_tmp					g_InteralMemory.KeepWord[101]

#define zero_start_status					g_InteralMemory.KeepWord[108]
#define zero_finish_status					g_InteralMemory.KeepWord[109]

#define loading_x_1_start_status			g_InteralMemory.KeepWord[110]
#define loading_x_1_finish_status 			g_InteralMemory.KeepWord[111]

#define loading_z_down_1_start_status		g_InteralMemory.KeepWord[112]
#define loading_z_down_1_finish_status 		g_InteralMemory.KeepWord[113]

#define gripper1_1_fastening_start_status	g_InteralMemory.KeepWord[114]
#define gripper1_1_fastening_finish_status 	g_InteralMemory.KeepWord[115]

#define loading_z_up_1_start_status			g_InteralMemory.KeepWord[116]
#define loading_z_up_1_finish_status 		g_InteralMemory.KeepWord[117]
//注：靠后的_1_,_2_表示位置，位置1位上料位置，位置2为下料位置
#define blanking_x_2_start_status			g_InteralMemory.KeepWord[118]
#define blanking_x_2_finish_status			g_InteralMemory.KeepWord[119]

#define cylinder_rotate_A_1_start_status	g_InteralMemory.KeepWord[120]
#define cylinder_rotate_A_1_finish_status	g_InteralMemory.KeepWord[121]

#define blanking_z_down_2_start_status			g_InteralMemory.KeepWord[122]
#define blanking_z_down_2_finish_status			g_InteralMemory.KeepWord[123]
#define gripper2_2_fastening_start_status		g_InteralMemory.KeepWord[124]
#define gripper2_2_fastening_finish_status		g_InteralMemory.KeepWord[125]
#define x_offset_out_start_status				g_InteralMemory.KeepWord[126]
#define x_offset_out_finish_status				g_InteralMemory.KeepWord[127]
#define cylinder_rotate_B_2_start_status		g_InteralMemory.KeepWord[128]
#define cylinder_rotate_B_2_finish_status		g_InteralMemory.KeepWord[129]
#define x_offset_in_start_status				g_InteralMemory.KeepWord[130]
#define x_offset_in_finish_status				g_InteralMemory.KeepWord[131]
#define gripper1_2_relaxing_start_status		g_InteralMemory.KeepWord[132]
#define gripper1_2_relaxing_finish_status		g_InteralMemory.KeepWord[133]
#define blanking_z_up_2_start_status			g_InteralMemory.KeepWord[134]
#define blanking_z_up_2_finish_status			g_InteralMemory.KeepWord[135]
#define cylinder_rotate_A_2_start_status		g_InteralMemory.KeepWord[136]
#define cylinder_rotate_A_2_finish_status		g_InteralMemory.KeepWord[137]
#define blowing_x_1_start_status				g_InteralMemory.KeepWord[138]
#define blowing_x_1_finish_status				g_InteralMemory.KeepWord[139]
#define blowing_z_down_1_start_status			g_InteralMemory.KeepWord[140]
#define blowing_z_down_1_finish_status			g_InteralMemory.KeepWord[141]
#define gripper2_1_relaxing_start_status		g_InteralMemory.KeepWord[142]
#define gripper2_1_relaxing_finish_status		g_InteralMemory.KeepWord[143]
#define blowing_z_up_1_start_status				g_InteralMemory.KeepWord[144]
#define blowing_z_up_1_finish_status			g_InteralMemory.KeepWord[145]
#define cylinder_rotate_B_1_start_status		g_InteralMemory.KeepWord[146]
#define cylinder_rotate_B_1_finish_status		g_InteralMemory.KeepWord[147]

#define z_up_offset_start						g_InteralMemory.KeepWord[148]
#define z_up_offset_finish						g_InteralMemory.KeepWord[149]
#define z_down_offset_start						g_InteralMemory.KeepWord[150]
#define z_down_offset_finish					g_InteralMemory.KeepWord[151]
#define z_up_offset_distance					g_InteralMemory.KeepWord[152]
#define pulse_signal							g_InteralMemory.KeepWord[153]
#define y_moving_finish							g_InteralMemory.KeepWord[154]

#define MACHINE_TRIGGER_TIME					g_InteralMemory.KeepWord[155]

#define x_offset_in_1st_start_status			g_InteralMemory.KeepWord[156]
#define x_offset_in_1st_finish_status			g_InteralMemory.KeepWord[157]
#define x_offset_in_3rd_start_status			g_InteralMemory.KeepWord[158]
#define x_offset_in_3rd_finish_status			g_InteralMemory.KeepWord[159]

#define Z_Limit_Port							10

void Loop_Robot(void);
void status_reset(void);
void RESET(void);
void start_status_reset(void);

#endif